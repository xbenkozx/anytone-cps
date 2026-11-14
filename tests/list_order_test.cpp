// Headless test for Anytone::ListOrder (sort / move of channels, zones,
// talk groups, roaming channels and analog address book entries).
//
// For every list and a series of operations (move up/down/top/bottom, sort by
// name / frequency / id, reverse, random permutation) the test checks that
//   - every list keeps list[i]->id == i and VFO A/B (channels 4000/4001) stay,
//   - the object graph, with every reference resolved to the NAME of the entry
//     it points to, is unchanged (compared as multiset, so only the position
//     of an entry may change):
//       a) in memory (pointers and the stored index fields),
//       b) after the real write encoder (Device::writeOtherData) into an
//          in-memory radio image and decoding it again (Device::readOtherData),
//       c) after saving to .atd (XML) and loading it again,
//   - saving to .atd and loading again gives the identical object graph
//     (compared in order).
//
// No radio is touched: everything happens in an in-memory image.
//
// Usage: list_order_test synthetic | <codeplug.atd> [...]   ("synthetic" builds a codeplug in code)
// Build: cmake -B build -DANYTONE_BUILD_TESTS=ON && cmake --build build --target list-order-test

#include <QCoreApplication>
#include <QBuffer>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDebug>
#include <QSet>
#include <algorithm>
#include <random>
#include "device.h"
#include "memory/list_order.h"

using namespace Anytone;
using Kind = ListOrder::Kind;
using Move = ListOrder::Move;

static int g_failures = 0;
static int g_checks = 0;
#define CHECK(cond, msg) do { g_checks++; if(!(cond)){ g_failures++; qCritical().noquote() << "FAIL:" << msg << "(" #cond ")"; } } while(0)

// In-memory radio: writes land in the image, reads come from the image.
class MemDevice : public Device {
public:
    QByteArray image = QByteArray(0x5000000, char(0xff));
    QByteArray readMemoryAddress(int a, int l) override { return image.mid(a, l); }
    void writeMemoryAddress(int a, QByteArray d) override { image.replace(a, d.size(), d); }
    std::vector<QString> readDeviceInfo() override { return {QString("ID878UV2"), QString("V101")}; }
};

// ---------------------------------------------------------------------------
// Keys: an entry is identified by its content, never by its slot
// ---------------------------------------------------------------------------
static QString chKey(Channel *c){
    if(!c || c->rx_frequency == 0) return "-";
    return c->name + "|" + c->getRxFrequencyString() + "|" + c->getTxFrequencyString();
}
static QString tgKey(Talkgroup *t){
    if(!t || t->dmr_id == 0) return "-";
    return t->name + "|" + QString::number(t->dmr_id) + "|" + QString::number(t->call_type);
}
static QString zoneKey(Zone *z){
    if(!z || z->channels.size() == 0) return "-";
    return z->name;
}
static QString rcKey(RoamingChannel *c){
    if(!c || c->rx_frequency == 0) return "-";
    return c->name + "|" + c->getRxFrequencyString() + "|" + c->getTxFrequencyString();
}
static QString addrKey(AnalogAddress *a){
    if(!a || a->number == 0) return "-";
    return a->name + "|" + QString::number(a->number);
}
template<typename T> static T* at(const QVector<T*> &v, int i){ return (i >= 0 && i < v.size()) ? v.at(i) : nullptr; }

struct Graph {
    // multiset-comparable descriptors, one string per object
    QStringList channels, zones, scanlists, receive_groups, roaming_zones, talkgroups, roaming_channels, addresses, misc;
    QStringList all() const {
        QStringList l;
        for(const QString &s : channels) l << "CH " + s;
        for(const QString &s : zones) l << "ZN " + s;
        for(const QString &s : scanlists) l << "SL " + s;
        for(const QString &s : receive_groups) l << "RG " + s;
        for(const QString &s : roaming_zones) l << "RZ " + s;
        for(const QString &s : talkgroups) l << "TG " + s;
        for(const QString &s : roaming_channels) l << "RC " + s;
        for(const QString &s : addresses) l << "AD " + s;
        for(const QString &s : misc) l << "MS " + s;
        return l;
    }
};

// byIndex = resolve through the stored index fields instead of the pointers
static Graph graph(bool byIndex){
    Graph g;
    for(Channel *c : Memory::channels){
        if(c->rx_frequency == 0) continue;
        Talkgroup *tg = byIndex ? at(Memory::talkgroups, c->contact_idx) : c->contact;
        ScanList *sl = byIndex ? at(Memory::scanlists, c->scan_list_idx) : c->scanlist;
        RadioId *rid = at(Memory::radioids, c->radio_id_idx);
        ReceiveGroup *rg = at(Memory::receive_group_call_lists, c->receive_group_call_list_idx);
        g.channels << chKey(c) + " tg=" + tgKey(tg) + " rid=" + (rid ? rid->name : "") +
                      " sl=" + (sl ? sl->name : "") + " rg=" + (rg ? rg->name : "") +
                      " id<4000=" + (c->id < 4000 ? "y" : "n");
    }
    for(Zone *z : Memory::zones){
        if(z->channels.size() == 0 && z->name.isEmpty()) continue;
        QStringList m;
        for(Channel *c : z->channels) m << chKey(c);
        QString a = (z->a_channel_idx < z->channels.size()) ? chKey(z->channels.at(z->a_channel_idx)) : "?";
        QString b = (z->b_channel_idx < z->channels.size()) ? chKey(z->channels.at(z->b_channel_idx)) : "?";
        g.zones << z->name + " hide=" + QString::number(z->hide) + " [" + m.join(";") + "] a=" + a + " b=" + b;
        if(byIndex && z->temp_member_channel_idxs.size() > 0){
            QStringList t;
            for(uint16_t i : z->temp_member_channel_idxs) t << chKey(at(Memory::channels, i));
            g.zones << "IDX " + z->name + " [" + t.join(";") + "]";
        }
    }
    for(ScanList *s : Memory::scanlists){
        if(s->channels.size() == 0 && s->name.isEmpty()) continue;
        QStringList m;
        for(Channel *c : s->channels) m << chKey(c);
        g.scanlists << s->name + " [" + m.join(";") + "] p1=" + QString::number(s->priority_channel_1) +
                       " p2=" + QString::number(s->priority_channel_2) + " rev=" + QString::number(s->revert_channel) +
                       " sel=" + QString::number(s->priority_channel_select);
        if(byIndex && s->channel_member_idxs.size() > 0){
            QStringList t;
            for(int i : s->channel_member_idxs) t << chKey(at(Memory::channels, i));
            g.scanlists << "IDX " + s->name + " [" + t.join(";") + "]";
        }
    }
    for(ReceiveGroup *r : Memory::receive_group_call_lists){
        if(r->talkgroups.size() == 0 && r->name.isEmpty()) continue;
        QStringList m;
        if(byIndex){
            for(uint16_t i : r->tg_idxs) m << tgKey(at(Memory::talkgroups, i));
        }else{
            for(Talkgroup *t : r->talkgroups) m << tgKey(t);
        }
        g.receive_groups << r->name + " [" + m.join(";") + "]";
    }
    for(RoamingZone *z : Memory::roaming_zones){
        if(z->channels.size() == 0) continue;
        QStringList m;
        if(byIndex && z->channel_idxs.size() > 0){
            for(int i : z->channel_idxs) m << rcKey(at(Memory::roaming_channels, i));
        }else{
            for(RoamingChannel *c : z->channels) m << rcKey(c);
        }
        g.roaming_zones << z->name + " [" + m.join(";") + "]";
    }
    for(Talkgroup *t : Memory::talkgroups) if(t->dmr_id) g.talkgroups << tgKey(t);
    for(RoamingChannel *c : Memory::roaming_channels) if(c->rx_frequency) g.roaming_channels << rcKey(c) + " cc=" + QString::number(c->color_code);
    for(AnalogAddress *a : Memory::analog_addresses) if(a->number) g.addresses << addrKey(a);

    // plain index fields in the settings
    OptionalSettings *o = Memory::optional_settings;
    auto zn = [](int id){ return zoneKey(at(Memory::zones, id)); };
    auto zn1 = [&](int v){ return v == 0 ? QString("off") : zn(v - 1); };
    bool d878 = Memory::radio_model != RadioModel::D890UV_FW103;
    g.misc << "startup_zone " + zn(o->startup_zone_a) + "/" + zn(o->startup_zone_b);
    g.misc << "mem_zone " + zn(o->mem_zone_a) + "/" + zn(o->mem_zone_b);
    g.misc << "priority_zone " + (d878 ? zn1(o->priority_zone_a) + "/" + zn1(o->priority_zone_b)
                                       : zn(o->priority_zone_a) + "/" + zn(o->priority_zone_b));
    g.misc << "alarm_ch " + chKey(at(Memory::channels, Memory::alarm_settings->analog_emergency_channel)) + "/" +
                            chKey(at(Memory::channels, Memory::alarm_settings->digital_emergency_channel));
    AprsSettings *a = Memory::aprs_settings;
    int rc[8] = {a->digital_report_channel_1, a->digital_report_channel_2, a->digital_report_channel_3, a->digital_report_channel_4,
                 a->digital_report_channel_5, a->digital_report_channel_6, a->digital_report_channel_7, a->digital_report_channel_8};
    QStringList rcs;
    for(int v : rc) rcs << (v < 4002 ? chKey(at(Memory::channels, v)) : QString("cur"));
    g.misc << "aprs_ch " + rcs.join(";");
    for(GpsRoaming *gps : Memory::gps_roaming_list){
        if(gps->zone_idx == 0xff) continue;
        g.misc << "gps_zone " + QString::number(gps->radius) + " " + zn(gps->zone_idx);
    }
    for(HotkeyKey *k : Memory::hotkey->key_list){
        if(k->call_type == 2 && k->call_obj < uint32_t(Memory::talkgroups.size()))
            g.misc << "hotkey_tg " + k->name + " " + tgKey(Memory::talkgroups.at(k->call_obj));
    }
    for(int i = 0; i < Memory::hotkey->quick_call_list.size(); i++){
        AnalogQuickCall *q = Memory::hotkey->quick_call_list.at(i);
        g.misc << "quick_call" + QString::number(i) + " " + (q->call_id == 0xff ? QString("off") : addrKey(at(Memory::analog_addresses, q->call_id)));
    }
    return g;
}

static QStringList sorted(QStringList l){ l.sort(); return l; }

// The D878 encoder writes the auto repeater range fields over the startup
// zone/channel bytes (0xcc..0xcf of 0x2500000), so those do not survive an
// encode/decode round trip no matter what ListOrder does. Left out there.
static QStringList forRadio(QStringList l){
    QStringList out;
    for(const QString &s : l) if(!s.startsWith("MS startup_zone")) out << s;
    return sorted(out);
}

// ---------------------------------------------------------------------------
// Memory helpers
// ---------------------------------------------------------------------------
// Synthetic codeplug: 120 channels (analog and digital, with gaps), 12 zones,
// 4 scan lists, 150 talk groups, 3 radio ids, receive groups, roaming channels
// and zones. Names are unique so every reference can be checked by name.
static void buildSynthetic(){
    Memory::radio_model = RadioModel::D878UVII_FW400;
    Memory::init();
    // the APRS encoder expects these to be non-empty
    Memory::aprs_settings->aprs_symbol = "/";
    Memory::aprs_settings->map_icon = ">";
    for(int i = 0; i < 3; i++){
        RadioId *r = Memory::radioids.at(i);
        r->dmr_id = 2600000 + i; r->name = "RID" + QString::number(i);
    }
    for(int i = 0; i < 150; i++){
        Talkgroup *t = Memory::talkgroups.at(i + (i >= 100 ? 40 : 0));   // gap of 40 slots
        t->dmr_id = 100 + i * 7; t->name = QString("TG%1").arg((i * 37) % 150, 3, 10, QChar('0'));
        t->call_type = i % 2;
    }
    for(int i = 0; i < 4; i++){
        ScanList *sl = Memory::scanlists.at(i);
        sl->name = "SCAN" + QString::number(i);
        sl->priority_channel_1 = 1; sl->priority_channel_2 = 2;
    }
    int n = 0;
    for(int i = 0; i < 130; i++){
        if(i % 11 == 10) continue;                        // empty slots
        Channel *c = Memory::channels.at(i);
        c->rx_frequency = 14400000 + (i * 37 % 97) * 2500;
        c->setFrequency(c->rx_frequency, c->rx_frequency);
        c->name = QString("CH%1").arg((i * 53) % 130, 3, 10, QChar('0'));
        c->channel_type = i % 3 == 0 ? 1 : 0;
        c->contact_idx = (i * 13) % 100;
        c->radio_id_idx = i % 3;
        c->scan_list_idx = i % 4;
        c->receive_group_call_list_idx = i % 2;
        n++;
    }
    for(int z = 0; z < 12; z++){
        Zone *zn = Memory::zones.at(z + (z >= 8 ? 5 : 0));   // gap of 5 slots
        zn->name = "ZONE" + QString::number((z * 5) % 12);
        for(int k = 0; k < 6; k++){
            int ch = (z * 9 + k * 4) % 130;
            if(ch % 11 == 10) ch++;
            zn->temp_member_channel_idxs.append(ch);
        }
        zn->a_channel_idx = 1; zn->b_channel_idx = 2;
    }
    for(int i = 0; i < 4; i++){
        for(int k = 0; k < 7; k++){
            int ch = (i * 20 + k * 3) % 130;
            if(ch % 11 == 10) ch++;
            Memory::scanlists.at(i)->channel_member_idxs.append(ch);
        }
    }
    for(int i = 0; i < 2; i++){
        ReceiveGroup *rg = Memory::receive_group_call_lists.at(i);
        rg->name = "RXG" + QString::number(i);
        for(int k = 0; k < 5; k++) rg->tg_idxs.append(k * 11 + i);
    }
    for(int i = 0; i < 40; i++){
        if(i % 7 == 6) continue;
        RoamingChannel *rc = Memory::roaming_channels.at(i);
        rc->rx_frequency = 43000000 + i * 12500; rc->tx_frequency = rc->rx_frequency;
        rc->name = QString("RC%1").arg((i * 17) % 40, 2, 10, QChar('0'));
        rc->color_code = i % 16; rc->slot = i % 2;
    }
    for(int i = 0; i < 3; i++){
        RoamingZone *rz = Memory::roaming_zones.at(i);
        rz->name = "RZ" + QString::number(i);
        for(int k = 0; k < 4; k++) rz->channel_idxs.append(i * 8 + k + (k + i * 8) / 6);
    }
    for(int i = 0; i < 10; i++){
        if(i == 4) continue;                              // no gaps handled by the radio, keep one hole out of the way
        AnalogAddress *a = Memory::analog_addresses.at(i);
        a->number = 2000 + i; a->name = QString("ADDR%1").arg((i * 3) % 10);
    }
    Memory::linkReferences();
    Memory::radio_model = RadioModel::D878UVII_FW400;
}

static bool loadAtd(const QString &path){
    if(path == "synthetic"){ buildSynthetic(); return true; }
    Memory::radio_model = RadioModel::D878UVII_FW400;
    Memory::init();
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)) return false;
    QXmlStreamReader xml(&f);
    Memory::loadData(xml);
    f.close();
    Memory::radio_model = RadioModel::D878UVII_FW400;
    return !xml.hasError();
}

static QByteArray saveAtd(){
    QByteArray out;
    QBuffer buf(&out);
    buf.open(QIODevice::WriteOnly);
    QXmlStreamWriter w(&buf);
    w.setAutoFormatting(true);
    Memory::saveData(w);
    return out;
}
static void loadAtdBytes(const QByteArray &data){
    Memory::radio_model = RadioModel::D878UVII_FW400;
    Memory::init();
    QXmlStreamReader xml(data);
    Memory::loadData(xml);
    Memory::radio_model = RadioModel::D878UVII_FW400;
}

// encode like a write to the radio, wipe the memory, decode like a read
static void radioRoundTrip(){
    MemDevice d;
    d.writeOtherData();
    if(qEnvironmentVariableIsSet("LO_DEBUG")) qInfo() << "image 0x25000ca:" << d.image.mid(0x25000ca, 6).toHex(' ');
    Memory::init();
    Memory::radio_model = RadioModel::D878UVII_FW400;
    d.readOtherData();
    Memory::linkReferences();
}

static void checkInvariants(const QString &what){
    for(int i = 0; i < Memory::channels.size(); i++) CHECK(Memory::channels.at(i)->id == i, what + " channel id " + QString::number(i));
    for(int i = 0; i < Memory::zones.size(); i++) CHECK(Memory::zones.at(i)->id == i, what + " zone id " + QString::number(i));
    for(int i = 0; i < Memory::talkgroups.size(); i++) CHECK(Memory::talkgroups.at(i)->id == i, what + " tg id " + QString::number(i));
    for(int i = 0; i < Memory::roaming_channels.size(); i++) CHECK(Memory::roaming_channels.at(i)->id == i, what + " rc id " + QString::number(i));
    for(int i = 0; i < Memory::analog_addresses.size(); i++) CHECK(Memory::analog_addresses.at(i)->id == i, what + " addr id " + QString::number(i));
    // no object appears twice
    QSet<void*> seen;
    for(Channel *c : Memory::channels) seen.insert(c);
    CHECK(seen.size() == Memory::channels.size(), what + " channels unique");
    seen.clear();
    for(Talkgroup *c : Memory::talkgroups) seen.insert(c);
    CHECK(seen.size() == Memory::talkgroups.size(), what + " talkgroups unique");
}

static void report(const QString &what, const QStringList &a, const QStringList &b){
    if(a == b) return;
    QStringList onlyA = a, onlyB = b;
    for(const QString &s : b) onlyA.removeOne(s);
    for(const QString &s : a) onlyB.removeOne(s);
    qCritical().noquote() << "  " << what << ": before-only" << onlyA.size() << "after-only" << onlyB.size();
    for(int i = 0; i < qMin(3, int(onlyA.size())); i++) qCritical().noquote() << "    - " << onlyA[i];
    for(int i = 0; i < qMin(3, int(onlyB.size())); i++) qCritical().noquote() << "    + " << onlyB[i];
}

// Inject references the sample codeplugs may not contain, so every remap path
// is exercised (all of them survive encode/decode and the .atd format).
static void injectReferences(){
    auto firstUsed = [](auto &list, auto used, int skip){
        int n = 0;
        for(int i = 0; i < list.size(); i++) if(used(list.at(i)) && n++ >= skip) return i;
        return -1;
    };
    auto usedCh = [](Channel *c){ return c->rx_frequency > 0; };
    auto usedZone = [](Zone *z){ return z->channels.size() > 0; };
    auto usedTg = [](Talkgroup *t){ return t->dmr_id > 0; };
    auto usedAd = [](AnalogAddress *a){ return a->number > 0; };
    // the sample files hold at most one analog address: add a gap-free block
    // (the radio keeps the address book packed, quick calls index into it)
    for(int i = 0; i < 8; i++){
        AnalogAddress *ad = Memory::analog_addresses.at(i);
        if(ad->number == 0){
            ad->number = 1000 + i;
            ad->name = "Addr " + QString::number(i);
        }
    }
    int c1 = firstUsed(Memory::channels, usedCh, 3), c2 = firstUsed(Memory::channels, usedCh, 7);
    int z1 = firstUsed(Memory::zones, usedZone, 1), z2 = firstUsed(Memory::zones, usedZone, 2);
    int t1 = firstUsed(Memory::talkgroups, usedTg, 5);
    int a1 = firstUsed(Memory::analog_addresses, usedAd, 3);
    if(c1 >= 0 && c2 >= 0){
        Memory::alarm_settings->analog_emergency_channel = c1;
        Memory::alarm_settings->digital_emergency_channel = c2;
        Memory::aprs_settings->digital_report_channel_1 = c1;
        Memory::aprs_settings->digital_report_channel_2 = c2;
    }
    if(z1 >= 0 && z2 >= 0){
        Memory::optional_settings->startup_zone_a = z1;
        Memory::optional_settings->startup_zone_b = z2;
        Memory::optional_settings->mem_zone_a = z2;
        Memory::optional_settings->mem_zone_b = z1;
        Memory::optional_settings->priority_zone_a = z2 + 1;
        Memory::optional_settings->priority_zone_b = 0;
        Memory::gps_roaming_list.at(0)->zone_idx = z1;
        Memory::gps_roaming_list.at(0)->radius = 777;
        Memory::gps_roaming_list.at(1)->zone_idx = z2;
        Memory::gps_roaming_list.at(1)->radius = 888;
    }
    if(t1 >= 0){
        HotkeyKey *k = Memory::hotkey->key_list.at(0);
        k->call_type = 2;
        k->call_obj = t1;
        k->name = "injected";
    }
    if(a1 >= 0){
        Memory::hotkey->quick_call_list.at(0)->operation_type = 1;
        Memory::hotkey->quick_call_list.at(0)->call_id = a1;
    }
}

struct Case { QString name; Kind kind; QString op; };

static QVector<int> usedSlots(Kind kind){
    QVector<int> v;
    for(int i = 0; i < ListOrder::count(kind); i++) if(!ListOrder::isEmpty(kind, i)) v << i;
    return v;
}

static QString sortKey(Kind kind, int slot, const QString &by){
    switch(kind){
        case Kind::Channel: {
            Channel *c = Memory::channels.at(slot);
            if(by == "freq") return QString("%1").arg(c->rx_frequency, 12, 10, QChar('0'));
            return c->name.toLower();
        }
        case Kind::Zone: return Memory::zones.at(slot)->name.toLower();
        case Kind::Talkgroup: {
            Talkgroup *t = Memory::talkgroups.at(slot);
            if(by == "dmr") return QString("%1").arg(t->dmr_id, 12, 10, QChar('0'));
            return t->name.toLower();
        }
        case Kind::RoamingChannel: return Memory::roaming_channels.at(slot)->name.toLower();
        case Kind::AnalogAddress: return Memory::analog_addresses.at(slot)->name.toLower();
    }
    return {};
}

// the same thing the UI does when "Apply sort order" is pressed
static QVector<int> viewOrder(Kind kind, const QString &by, bool descending){
    const int total = (kind == Kind::Channel) ? Memory::channels.size() :
                      (kind == Kind::Zone) ? Memory::zones.size() :
                      (kind == Kind::Talkgroup) ? Memory::talkgroups.size() :
                      (kind == Kind::RoamingChannel) ? Memory::roaming_channels.size() : Memory::analog_addresses.size();
    QVector<int> view(total);
    for(int i = 0; i < total; i++) view[i] = i;
    std::stable_sort(view.begin(), view.end(), [&](int a, int b){
        bool ea = ListOrder::isEmpty(kind, a), eb = ListOrder::isEmpty(kind, b);
        if(ea != eb) return eb;                   // empty last, either direction
        if(ea) return false;
        QString ka = sortKey(kind, a, by), kb = sortKey(kind, b, by);
        return descending ? ka > kb : ka < kb;
    });
    return view;
}

static QVector<int> randomSelection(Kind kind, std::mt19937 &rng, int n){
    QVector<int> used = usedSlots(kind);
    std::shuffle(used.begin(), used.end(), rng);
    return used.mid(0, qMin(n, int(used.size())));
}

static QVector<int> buildOrder(Kind kind, const QString &op, std::mt19937 &rng, QVector<int> *moved){
    if(op.startsWith("sort-") || op.startsWith("rsort-")){
        QString by = op.mid(op.indexOf('-') + 1);
        return ListOrder::orderForView(kind, viewOrder(kind, by, op.startsWith("rsort")));
    }
    if(op == "shuffle"){
        QVector<int> order;
        for(int i = 0; i < ListOrder::count(kind); i++) order << i;
        std::shuffle(order.begin(), order.end(), rng);
        return order;
    }
    QVector<int> sel;
    if(op.endsWith("-one")) sel = randomSelection(kind, rng, 1);
    else if(op.endsWith("-multi")) sel = randomSelection(kind, rng, 5);
    else if(op.endsWith("-first")) sel = usedSlots(kind).mid(0, 1);
    else if(op.endsWith("-last")) sel = usedSlots(kind).mid(usedSlots(kind).size() - 1);
    else if(op.endsWith("-empty")){
        for(int i = 0; i < ListOrder::count(kind); i++) if(ListOrder::isEmpty(kind, i)){ sel << i; break; }
    }
    *moved = sel;
    Move m = op.startsWith("up") ? Move::Up : op.startsWith("down") ? Move::Down : op.startsWith("top") ? Move::Top : Move::Bottom;
    return ListOrder::orderForMove(kind, sel, m);
}

static const char *kindName(Kind k){
    switch(k){
        case Kind::Channel: return "channel";
        case Kind::Zone: return "zone";
        case Kind::Talkgroup: return "talkgroup";
        case Kind::RoamingChannel: return "roaming-channel";
        case Kind::AnalogAddress: return "analog-address";
    }
    return "?";
}

static void runCase(const QString &file, Kind kind, const QString &op, unsigned seed){
    const QString label = QString("%1 %2 %3").arg(file.section('/', -1).left(24), kindName(kind), op);
    std::mt19937 rng(seed);

    // baseline
    if(!loadAtd(file)){ CHECK(false, label + " load"); return; }
    injectReferences();
    Graph base_ptr = graph(false), base_idx = graph(true);
    const QByteArray base_atd = saveAtd();
    loadAtdBytes(base_atd);   // make the baseline what a save/load cycle yields
    Graph rt_before;
    {
        radioRoundTrip();
        rt_before = graph(false);
    }
    loadAtdBytes(base_atd);
    base_ptr = graph(false);
    base_idx = graph(true);

    // operation through the same code the UI uses
    QVector<int> moved;
    QVector<int> order = buildOrder(kind, op, rng, &moved);
    QVector<Channel*> chBefore = Memory::channels;
    bool identity = order.isEmpty();
    if(!identity){
        CHECK(ListOrder::isValidOrder(kind, order), label + " order valid");
        CHECK(ListOrder::apply(kind, order), label + " apply");
    }
    checkInvariants(label);

    // VFO channels must not move
    CHECK(Memory::channels.at(4000) == chBefore.at(4000) && Memory::channels.at(4001) == chBefore.at(4001), label + " VFO fixed");

    // expectations on the resulting order
    if(!identity && op.startsWith("up-one") && kind != Kind::Zone && kind != Kind::AnalogAddress){
        // the moved entry is one slot higher
        int s = moved.first();
        if(s > 0) CHECK(order[s - 1] == s, label + " moved up by one");
    }
    if(op.startsWith("sort-name") && !identity){
        QString prev;
        bool ok = true;
        for(int i = 0; i < ListOrder::count(kind) && !ListOrder::isEmpty(kind, i); i++){
            QString k = sortKey(kind, i, "name");
            if(k < prev) ok = false;
            prev = k;
        }
        CHECK(ok, label + " sorted ascending by name");
    }

    // a) in memory, pointers
    Graph after_ptr = graph(false);
    CHECK(sorted(after_ptr.all()) == sorted(base_ptr.all()), label + " graph (pointers) unchanged");
    if(sorted(after_ptr.all()) != sorted(base_ptr.all())) report(label + " ptr", sorted(base_ptr.all()), sorted(after_ptr.all()));
    // a2) in memory, stored index fields: must resolve to the very same entries
    Graph after_idx = graph(true);
    CHECK(sorted(after_idx.all()) == sorted(base_idx.all()), label + " graph (index fields) unchanged");
    if(sorted(after_idx.all()) != sorted(base_idx.all())) report(label + " idx", sorted(base_idx.all()), sorted(after_idx.all()));
    // a3) re-linking from the index fields gives the same pointers again
    {
        const QByteArray keep = saveAtd();
        Memory::linkReferences();
        Graph relinked = graph(false);
        CHECK(sorted(relinked.all()) == sorted(base_ptr.all()), label + " relink from index fields");
        if(sorted(relinked.all()) != sorted(base_ptr.all())) report(label + " relink", sorted(base_ptr.all()), sorted(relinked.all()));
        loadAtdBytes(keep);
        // restore the state after the operation for the next steps
    }

    // c) .atd save/load: identical graph, in order
    loadAtd(file);
    injectReferences();
    loadAtdBytes(saveAtd());
    {
        std::mt19937 rng2(seed);
        QVector<int> moved2;
        QVector<int> order2 = buildOrder(kind, op, rng2, &moved2);
        if(!order2.isEmpty()) ListOrder::apply(kind, order2);
    }
    Graph direct = graph(false);
    const QByteArray atd = saveAtd();
    loadAtdBytes(atd);
    Graph reloaded = graph(false);
    CHECK(direct.all() == reloaded.all(), label + " .atd save/load identical graph (ordered)");
    if(direct.all() != reloaded.all()) report(label + " atd", direct.all(), reloaded.all());
    CHECK(sorted(reloaded.all()) == sorted(base_ptr.all()), label + " .atd reload equals baseline");
    CHECK(saveAtd() == atd, label + " .atd second save byte-identical");
    checkInvariants(label + " reloaded");

    // b) real encoder -> in-memory radio image -> real decoder
    if(qEnvironmentVariableIsSet("LO_DEBUG")) qInfo() << "pre-roundtrip startup" << Memory::optional_settings->startup_zone_a << Memory::optional_settings->startup_zone_b << "mem" << Memory::optional_settings->mem_zone_a << Memory::optional_settings->mem_zone_b << "prio" << Memory::optional_settings->priority_zone_a;
    radioRoundTrip();
    if(qEnvironmentVariableIsSet("LO_DEBUG")) qInfo() << "post-roundtrip startup" << Memory::optional_settings->startup_zone_a << Memory::optional_settings->startup_zone_b << "mem" << Memory::optional_settings->mem_zone_a << Memory::optional_settings->mem_zone_b << "prio" << Memory::optional_settings->priority_zone_a;
    Graph rt_after = graph(false);
    CHECK(forRadio(rt_after.all()) == forRadio(rt_before.all()), label + " radio image round trip graph unchanged");
    if(forRadio(rt_after.all()) != forRadio(rt_before.all())) report(label + " radio", forRadio(rt_before.all()), forRadio(rt_after.all()));

    qInfo().noquote() << (identity ? "noop " : "ok   ") << label;
}

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);
    if(argc < 2){ qCritical() << "usage: list_order_test file.atd..."; return 2; }
    Memory::radio_model = RadioModel::D878UVII_FW400;
    Memory::init();
    Memory::initDigitalContacts();

    const QStringList ops = {
        "up-one", "up-multi", "up-first", "down-one", "down-multi", "down-last",
        "top-one", "top-multi", "bottom-one", "bottom-multi", "up-empty", "down-empty",
        "sort-name", "rsort-name", "sort-freq", "sort-dmr", "shuffle"
    };
    const QVector<Kind> kinds = { Kind::Channel, Kind::Zone, Kind::Talkgroup, Kind::RoamingChannel, Kind::AnalogAddress };

    // sanity of the sample data: scan list priority channel semantics
    for(int a = 1; a < argc; a++){
        const QString file = argv[a];
        if(!loadAtd(file)){ qCritical() << "cannot load" << file; return 2; }
        qInfo().noquote() << file << ": channels" << usedSlots(Kind::Channel).size() << "zones" << usedSlots(Kind::Zone).size()
                          << "talkgroups" << usedSlots(Kind::Talkgroup).size() << "roaming ch" << usedSlots(Kind::RoamingChannel).size()
                          << "addresses" << usedSlots(Kind::AnalogAddress).size();
        // re-opening a file must replace receive group lists already in memory
        if(file != "synthetic"){
            auto rx_state = []{
                QStringList s;
                for(auto *g : Memory::receive_group_call_lists){
                    QStringList names;
                    for(auto *tg : g->talkgroups) names << tg->name;
                    s << g->name + ":" + names.join(",");
                }
                return s;
            };
            const QStringList from_file = rx_state();
            const QByteArray atd_now = saveAtd();
            // dirty the lists the way a radio read does, then load the file again
            for(auto *g : Memory::receive_group_call_lists){
                if(g->id == 0) continue;
                g->name = "RADIO"; g->tg_idxs = {1, 2, 3};
            }
            Memory::receive_group_call_lists.at(0)->tg_idxs.append(5);
            {   // like MainWindow::openFile: loadData on the live memory, no init()
                QXmlStreamReader xml(atd_now);
                Memory::loadData(xml);
                Memory::linkReferences();
            }
            CHECK(rx_state() == from_file, "re-open replaces receive group lists");
        }
        unsigned seed = 1;
        for(Kind kind : kinds){
            for(const QString &op : ops){
                if(op == "sort-freq" && kind != Kind::Channel) continue;
                if(op == "sort-dmr" && kind != Kind::Talkgroup) continue;
                if(op.endsWith("-empty") && kind == Kind::Zone) continue;
                runCase(file, kind, op, seed++);
            }
        }
    }
    qInfo() << "checks:" << g_checks << "failures:" << g_failures;
    return g_failures == 0 ? 0 : 1;
}
