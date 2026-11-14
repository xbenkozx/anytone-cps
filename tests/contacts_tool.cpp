// Restore / check the DMR contact database using the application's own code paths.
//   contacts-tool dry    <codeplug.atd>          write to an in-memory image, read back, compare (no radio)
//   contacts-tool write  <port> <codeplug.atd>   Device::writeDigitalContacts to the radio (ONLY contacts regions)
//   contacts-tool verify <port> <codeplug.atd>   read every written block back from the radio and compare bytes
#include <QCoreApplication>
#include <QFile>
#include <QXmlStreamReader>
#include <QDebug>
#include <QSet>
#include "device.h"

using namespace Anytone;

class MemDevice : public Device {
public:
    QByteArray image = QByteArray(0x8000000, char(0xff));
    QByteArray readMemoryAddress(int a, int l) override { return image.mid(a, l); }
    void writeMemoryAddress(int a, QByteArray d) override { image.replace(a, d.size(), d); }
    std::vector<QString> readDeviceInfo() override { return {QString("ID878UV2"), QString("V101")}; }
};

class CapDevice : public MemDevice {
public:
    QVector<int> addrs;
    void writeMemoryAddress(int a, QByteArray d) override { addrs.push_back(a); MemDevice::writeMemoryAddress(a, d); }
};
class CountingSerial : public SerialDevice {
public:
    int n = 0, total = 0;
    void writeMemoryAddress(int a, QByteArray d) override {
        SerialDevice::writeMemoryAddress(a, d);
        if(++n % 20000 == 0) qInfo() << "written blocks:" << n << "/" << total;
    }
};
static QString key(DigitalContact *c){
    return QStringList{QString::number(c->radio_id), QString::number(c->call_type), QString::number(c->call_alert),
        c->name, c->city, c->callsign, c->state, c->country, c->remarks}.join("|");
}
static QSet<QString> keys(){
    QSet<QString> s;
    for(DigitalContact *c : Memory::digital_contacts) if(c->radio_id > 0) s.insert(key(c));
    return s;
}
static int used(){ int n = 0; for(DigitalContact *c : Memory::digital_contacts) if(c->radio_id > 0) n++; return n; }

static bool loadFile(const QString &path){
    Memory::radio_model = RadioModel::D878UVII_FW400;
    Memory::init();
    Memory::initDigitalContacts();
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly)) return false;
    QXmlStreamReader xml(&f);
    Memory::loadData(xml);
    Memory::radio_model = RadioModel::D878UVII_FW400;
    return !xml.hasError();
}
static QStringList expected_seq;
static bool compareToFile(Device &d, const QSet<QString> &expected, int expected_count){
    Memory::initDigitalContacts();
    d.readDigitalContacts();
    if(qEnvironmentVariableIsSet("CT_DEBUG")){
        int first_bad = -1;
        for(int i = 0; i < expected_seq.size() && i < Memory::digital_contacts.size(); i++){
            if(key(Memory::digital_contacts.at(i)) != expected_seq.at(i)){ first_bad = i; break; }
        }
        qInfo() << "first mismatching slot:" << first_bad;
        if(first_bad >= 0){
            for(int k = std::max(0, first_bad - 1); k <= first_bad; k++){
                qInfo().noquote() << " want[" << k << "]" << expected_seq.at(k);
                qInfo().noquote() << " read[" << k << "]" << key(Memory::digital_contacts.at(k));
            }
        }
    }
    const int got = used();
    const QSet<QString> have = keys();
    if(have != expected){
        int shown = 0;
        for(const QString &k : expected) if(!have.contains(k) && shown++ < 4) qInfo().noquote() << "only in file :" << k;
        shown = 0;
        for(const QString &k : have) if(!expected.contains(k) && shown++ < 4) qInfo().noquote() << "only in radio:" << k;
        qInfo() << "differences:" << (expected - have).size() << "/" << (have - expected).size();
    }
    qInfo() << "read back:" << got << "contacts, expected" << expected_count << "; identical content:" << (have == expected);
    return got == expected_count && have == expected;
}

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);
    if(argc < 3){ qCritical() << "usage: contacts-tool dry <atd> | write|verify <port> <atd>"; return 2; }
    const QString mode = argv[1];
    const QString atd = (mode == "dry") ? argv[2] : (argc > 3 ? argv[3] : "");
    if(!loadFile(atd)){ qCritical() << "cannot load" << atd; return 2; }
    const int n = used();
    const QSet<QString> expected = keys();
    {
        QVector<DigitalContact*> sorted = Memory::digital_contacts;
        std::stable_sort(sorted.begin(), sorted.end(), [](DigitalContact *a, DigitalContact *b){ return a->call_type > b->call_type; });
        for(DigitalContact *c : sorted) if(c->radio_id > 0) expected_seq << key(c);
    }
    qInfo() << "contacts in file:" << n;
    if(n < 100000){ qCritical() << "refusing: file has too few contacts"; return 2; }

    if(mode == "dry"){
        MemDevice d;
        d.writeDigitalContacts();
        if(qEnvironmentVariableIsSet("CT_DEBUG")){
            qInfo().noquote() << "image@data:" << d.image.mid(0x5500000, 0x60).toHex(' ');
        }
        return compareToFile(d, expected, n) ? 0 : 1;
    }
    CapDevice expected_img;               // what the writer produces, block by block
    expected_img.writeDigitalContacts();
    qInfo() << "blocks to write:" << expected_img.addrs.size();
    CountingSerial d;
    d.total = expected_img.addrs.size();
    if(!d.connect(argv[2])){ qCritical() << "cannot connect"; return 1; }
    const auto info = d.readDeviceInfo();
    qInfo().noquote() << "device:" << info[0] << info[1];
    if(info[0] != "ID878UV2" || info[1] != "V101"){ qCritical() << "unexpected device, aborting"; d.endProgMode(); return 1; }
    int rc = 0;
    if(mode == "write"){
        d.writeDigitalContacts();
        qInfo() << "write finished";
    }else if(mode == "verify"){
        int bad = 0, shown = 0, done = 0;
        for(int a : expected_img.addrs){
            const QByteArray want = expected_img.image.mid(a, 16);
            const QByteArray got = d.readMemoryAddress(a, 16);
            if(want != got){ bad++; if(shown++ < 5) qInfo().noquote() << QString("mismatch at 0x%1").arg(a, 0, 16) << "want" << want.toHex(' ') << "got" << got.toHex(' '); }
            if(++done % 50000 == 0) qInfo() << "verified blocks:" << done << "/" << expected_img.addrs.size() << "bad:" << bad;
        }
        qInfo() << "verify finished: blocks" << done << "mismatching" << bad;
        rc = bad == 0 ? 0 : 1;
    }
    d.endProgMode();
    return rc;
}
