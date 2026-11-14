#include "memory/list_order.h"

#include <algorithm>
#include <numeric>

#include "memory/anytone_memory.h"
#include "memory/channel.h"
#include "memory/zone.h"
#include "memory/talkgroup.h"
#include "memory/scanlist.h"
#include "memory/roaming_channel.h"
#include "memory/roaming_zone.h"
#include "memory/receive_group_call_list.h"
#include "memory/analog_address.h"
#include "memory/gps_roaming.h"
#include "memory/alarm_settings.h"
#include "memory/aprs_settings.h"
#include "memory/optional_settings.h"
#include "memory/hotkey.h"

using namespace Anytone;

namespace {
    // Channels 4000 and 4001 are VFO A and VFO B and must stay where they are.
    constexpr int CHANNEL_MOVABLE = 4000;

    int totalSize(ListOrder::Kind kind){
        switch(kind){
            case ListOrder::Kind::Channel: return Memory::channels.size();
            case ListOrder::Kind::Zone: return Memory::zones.size();
            case ListOrder::Kind::Talkgroup: return Memory::talkgroups.size();
            case ListOrder::Kind::RoamingChannel: return Memory::roaming_channels.size();
            case ListOrder::Kind::AnalogAddress: return Memory::analog_addresses.size();
        }
        return 0;
    }

    template<typename T, typename SetId>
    void permute(QVector<T*> &list, const QVector<int> &order, SetId set_id){
        const QVector<T*> old_list = list;
        for(int slot = 0; slot < order.size(); slot++){
            list[slot] = old_list.at(order.at(slot));
            set_id(list[slot], slot);
        }
    }

    // old slot -> new slot, identity for slots outside the permutation
    QVector<int> slotMap(const QVector<int> &order, int total){
        QVector<int> map(total);
        std::iota(map.begin(), map.end(), 0);
        for(int slot = 0; slot < order.size(); slot++){
            map[order.at(slot)] = slot;
        }
        return map;
    }

    // Translate a stored index; values outside the list (0xff = off, 0x0fa2 =
    // current channel, ...) are sentinels and stay as they are.
    template<typename T>
    T mapped(const QVector<int> &map, T value){
        const int v = int(value);
        if(v < 0 || v >= map.size()) return value;
        return T(map.at(v));
    }

    void remapChannelRefs(const QVector<int> &map){
        for(Zone *zone : Memory::zones){
            for(uint16_t &idx : zone->temp_member_channel_idxs) idx = mapped(map, idx);
        }
        for(ScanList *sc : Memory::scanlists){
            for(int &idx : sc->channel_member_idxs) idx = mapped(map, idx);
        }
        if(Memory::alarm_settings){
            AlarmSettings *a = Memory::alarm_settings;
            a->analog_emergency_channel = mapped(map, a->analog_emergency_channel);
            a->digital_emergency_channel = mapped(map, a->digital_emergency_channel);
        }
        if(Memory::aprs_settings){
            AprsSettings *a = Memory::aprs_settings;
            a->digital_report_channel_1 = mapped(map, a->digital_report_channel_1);
            a->digital_report_channel_2 = mapped(map, a->digital_report_channel_2);
            a->digital_report_channel_3 = mapped(map, a->digital_report_channel_3);
            a->digital_report_channel_4 = mapped(map, a->digital_report_channel_4);
            a->digital_report_channel_5 = mapped(map, a->digital_report_channel_5);
            a->digital_report_channel_6 = mapped(map, a->digital_report_channel_6);
            a->digital_report_channel_7 = mapped(map, a->digital_report_channel_7);
            a->digital_report_channel_8 = mapped(map, a->digital_report_channel_8);
        }
    }

    void remapZoneRefs(const QVector<int> &map){
        OptionalSettings *o = Memory::optional_settings;
        if(o){
            o->startup_zone_a = mapped(map, o->startup_zone_a);
            o->startup_zone_b = mapped(map, o->startup_zone_b);
            o->mem_zone_a = mapped(map, o->mem_zone_a);
            o->mem_zone_b = mapped(map, o->mem_zone_b);
            if(Memory::radio_model == RadioModel::D890UV_FW103){
                // kept as the plain zone id (0xff = off)
                o->priority_zone_a = mapped(map, o->priority_zone_a);
                o->priority_zone_b = mapped(map, o->priority_zone_b);
            }else{
                // kept as zone id + 1, 0 = off (see OptionalSettings::decode)
                if(o->priority_zone_a > 0) o->priority_zone_a = mapped(map, uint8_t(o->priority_zone_a - 1)) + 1;
                if(o->priority_zone_b > 0) o->priority_zone_b = mapped(map, uint8_t(o->priority_zone_b - 1)) + 1;
            }
        }
        for(GpsRoaming *gps : Memory::gps_roaming_list){
            gps->zone_idx = mapped(map, gps->zone_idx);
        }
    }

    void remapTalkgroupRefs(const QVector<int> &map){
        for(Channel *ch : Memory::channels){
            ch->contact_idx = mapped(map, ch->contact_idx);
        }
        for(ReceiveGroup *rg : Memory::receive_group_call_lists){
            for(uint16_t &idx : rg->tg_idxs) idx = mapped(map, idx);
        }
        if(Memory::hotkey){
            for(HotkeyKey *key : Memory::hotkey->key_list){
                // call_type 2 = talk group, call_obj is its list index
                if(key->call_type == 2 && key->call_obj < uint32_t(map.size())){
                    key->call_obj = map.at(key->call_obj);
                }
            }
        }
    }

    void remapRoamingChannelRefs(const QVector<int> &map){
        for(RoamingZone *z : Memory::roaming_zones){
            for(int &idx : z->channel_idxs) idx = mapped(map, idx);
        }
    }

    void remapAnalogAddressRefs(const QVector<int> &map){
        if(Memory::hotkey){
            for(AnalogQuickCall *qc : Memory::hotkey->quick_call_list){
                qc->call_id = mapped(map, qc->call_id);
            }
        }
    }
}

int ListOrder::count(Kind kind){
    const int total = totalSize(kind);
    if(kind == Kind::Channel) return std::min(total, CHANNEL_MOVABLE);
    return total;
}

bool ListOrder::isEmpty(Kind kind, int slot){
    if(slot < 0 || slot >= totalSize(kind)) return true;
    switch(kind){
        case Kind::Channel: return Memory::channels.at(slot)->rx_frequency == 0;
        case Kind::Zone: return Memory::zones.at(slot)->channels.size() == 0;
        case Kind::Talkgroup: return Memory::talkgroups.at(slot)->dmr_id == 0;
        case Kind::RoamingChannel: return Memory::roaming_channels.at(slot)->rx_frequency == 0;
        case Kind::AnalogAddress: return Memory::analog_addresses.at(slot)->number == 0;
    }
    return true;
}

bool ListOrder::compacts(Kind kind){
    return kind == Kind::Zone || kind == Kind::AnalogAddress;
}

QVector<int> ListOrder::orderForMove(Kind kind, const QVector<int> &selected_slots, Move move){
    const int n = count(kind);
    QVector<char> selected(n, 0);
    for(int s : selected_slots){
        if(s >= 0 && s < n) selected[s] = 1;
    }

    // seq[pos] = slot of the entry that is at position pos after the packing
    QVector<int> seq(n);
    std::iota(seq.begin(), seq.end(), 0);
    if(compacts(kind)){
        std::stable_partition(seq.begin(), seq.end(), [kind](int slot){ return !isEmpty(kind, slot); });
    }

    QVector<char> sel(n, 0);
    bool any = false;
    for(int pos = 0; pos < n; pos++){
        sel[pos] = selected[seq[pos]] && !(compacts(kind) && isEmpty(kind, seq[pos]));
        any = any || sel[pos];
    }
    if(!any) return {};

    switch(move){
        case Move::Up:
            for(int pos = 1; pos < n; pos++){
                if(sel[pos] && !sel[pos - 1]){
                    std::swap(seq[pos], seq[pos - 1]);
                    std::swap(sel[pos], sel[pos - 1]);
                }
            }
            break;
        case Move::Down:
            for(int pos = n - 2; pos >= 0; pos--){
                if(sel[pos] && !sel[pos + 1]){
                    std::swap(seq[pos], seq[pos + 1]);
                    std::swap(sel[pos], sel[pos + 1]);
                }
            }
            break;
        case Move::Top: {
            QVector<int> out;
            for(int pos = 0; pos < n; pos++) if(sel[pos]) out.append(seq[pos]);
            for(int pos = 0; pos < n; pos++) if(!sel[pos]) out.append(seq[pos]);
            seq = out;
            break;
        }
        case Move::Bottom: {
            // "Bottom" is the end of the used part of the list, not slot n-1
            int lo = n, hi = -1;
            for(int pos = 0; pos < n; pos++){
                if(sel[pos]){ lo = std::min(lo, pos); hi = std::max(hi, pos); }
                else if(!isEmpty(kind, seq[pos])) hi = std::max(hi, pos);
            }
            QVector<int> out = seq.mid(0, lo);
            for(int pos = lo; pos <= hi; pos++) if(!sel[pos]) out.append(seq[pos]);
            for(int pos = lo; pos <= hi; pos++) if(sel[pos]) out.append(seq[pos]);
            out += seq.mid(hi + 1);
            seq = out;
            break;
        }
    }

    for(int pos = 0; pos < n; pos++){
        if(seq[pos] != pos) return seq;
    }
    return {};
}

QVector<int> ListOrder::orderForView(Kind kind, const QVector<int> &view_slots){
    if(view_slots.size() != totalSize(kind)) return {};
    QVector<int> order;
    for(int slot : view_slots){
        if(slot >= 0 && slot < count(kind)) order.append(slot);
    }
    std::stable_partition(order.begin(), order.end(), [kind](int slot){ return !isEmpty(kind, slot); });
    if(!isValidOrder(kind, order)) return {};
    return order;
}

bool ListOrder::isValidOrder(Kind kind, const QVector<int> &order){
    const int n = count(kind);
    if(order.size() != n) return false;
    QVector<char> seen(n, 0);
    for(int slot : order){
        if(slot < 0 || slot >= n || seen[slot]) return false;
        seen[slot] = 1;
    }
    return true;
}

bool ListOrder::apply(Kind kind, const QVector<int> &requested){
    if(!isValidOrder(kind, requested)) return false;

    // Lists the radio keeps packed never get gaps, whatever the caller asked for
    QVector<int> order = requested;
    if(compacts(kind)){
        std::stable_partition(order.begin(), order.end(), [kind](int slot){ return !isEmpty(kind, slot); });
    }
    const QVector<int> map = slotMap(order, totalSize(kind));

    switch(kind){
        case Kind::Channel:
            permute(Memory::channels, order, [](Channel *c, int slot){ c->id = slot; });
            remapChannelRefs(map);
            break;
        case Kind::Zone:
            permute(Memory::zones, order, [](Zone *z, int slot){ z->id = slot; });
            remapZoneRefs(map);
            break;
        case Kind::Talkgroup:
            permute(Memory::talkgroups, order, [](Talkgroup *t, int slot){ t->id = slot; });
            remapTalkgroupRefs(map);
            break;
        case Kind::RoamingChannel:
            permute(Memory::roaming_channels, order, [](RoamingChannel *c, int slot){ c->id = slot; });
            remapRoamingChannelRefs(map);
            break;
        case Kind::AnalogAddress:
            permute(Memory::analog_addresses, order, [](AnalogAddress *a, int slot){ a->id = slot; });
            remapAnalogAddressRefs(map);
            break;
    }
    return true;
}
