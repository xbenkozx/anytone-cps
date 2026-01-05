#include "roaming_zone.h"

void Anytone::RoamingZone::decode(QByteArray data){
    name = QString(data.mid(0x40, 0x10));
    name.remove(QChar('\0'));
    for(uint8_t ch_idx : data.mid(0, 0x40)){
        if(ch_idx == 0xff) continue;
        channel_idxs.push_back(ch_idx);
    }
}
QByteArray Anytone::RoamingZone::encode(){
    QByteArray data(0x50, 0xff);
    auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());
    data.replace(0x40, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );
    for(int i=0; i < channels.size(); i++){
        RoamingChannel *rc = channels.at(i);
        if(rc->rx_frequency == 0) continue;
        bytes[i] = rc->id;
    }
    return data;
}

void Anytone::RoamingZone::save(QDataStream &ds){
    ds << id;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
    
    uint8_t tg_count = channels.size();
    ds << tg_count;
    for(RoamingChannel *ch : channels){
        ds << ch->id;
    }
}
void Anytone::RoamingZone::load(QDataStream &ds){
    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }

    uint8_t tg_count;
    ds >> tg_count;
    for(int i = 0; i < tg_count; i++){
        uint8_t tg_idx;
        ds >> tg_idx;
        channel_idxs.append(tg_idx);
    }
}