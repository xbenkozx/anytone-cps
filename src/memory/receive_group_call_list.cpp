#include "receive_group_call_list.h"

void Anytone::ReceiveGroup::decode(QByteArray data){

}

QByteArray Anytone::ReceiveGroup::encode(){
    QByteArray data(0x10, 0);

    return data;
}

void Anytone::ReceiveGroup::save(QDataStream &ds){
    ds << id;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
    
    uint8_t tg_count = talkgroups.size();
    ds << tg_count;
    for(Talkgroup *tg : talkgroups){
        ds << tg->id;
    }
}
void Anytone::ReceiveGroup::load(QDataStream &ds){
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
        uint16_t tg_idx;
        ds >> tg_idx;
        tg_idxs.append(tg_idx);
    }
}