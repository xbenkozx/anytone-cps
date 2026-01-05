#include "zone.h"

void Anytone::Zone::save(QDataStream &ds){
    ds << id;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
    ds << hide;
    ds << a_channel_idx;
    ds << b_channel_idx;

    uint8_t channel_count = channels.size();
    ds << channel_count;
    for(Channel *ch : channels){
        ds << ch->id;
    }

}

void Anytone::Zone::load(QDataStream &ds){
    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }

    ds >> hide;
    ds >> a_channel_idx;
    ds >> b_channel_idx;

    uint8_t channel_count;
    ds >> channel_count;
    for(int i = 0; i < channel_count; i++){
        uint16_t ch_idx;
        ds >> ch_idx;
        temp_member_channel_idxs.append(ch_idx);
    }
}