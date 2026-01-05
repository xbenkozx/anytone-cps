#include "memory/scanlist.h"
using namespace Anytone;
void ScanList::decode(QByteArray data){
    priority_channel_select = static_cast<int>(data.at(0x1));
    priority_channel_1 = Int::fromBytes(data.mid(0x2, 2));
    priority_channel_2 = Int::fromBytes(data.mid(0x4, 2));
    lookback_time_a = Int::fromBytes(data.mid(0x6, 2)) - 5;
    lookback_time_b = Int::fromBytes(data.mid(0x8, 2)) - 5;
    dropout_delay_time = Int::fromBytes(data.mid(0xa, 2)) - 1;
    dwell_time = Int::fromBytes(data.mid(0xc, 2)) - 1;
    revert_channel = Int::fromBytes(data.mid(0xe, 2));
    name = QString(data.mid(0xf, 0x10));
    name.remove(QChar('\0'));
    
    for(int i = 0; i < 100; i+=2){
        int ch_idx = Int::fromBytes(data.mid(0x1f + i, 2), Endian::Big);
        if(ch_idx != 0xffff) channel_member_idxs.push_back(ch_idx);
    }

}
QByteArray ScanList::encode(){
    QByteArray data(0x1f, 0);
    QByteArray channel_data(0x65, 0xff);

    data.replace(0x1, 1, 
        Int::toBytes(priority_channel_select, 1)
    );
    data.replace(0x2, 2, 
        Int::toBytes(priority_channel_1, 2)
    );
    data.replace(0x4, 4, 
        Int::toBytes(priority_channel_2, 2)
    );
    data.replace(0x6, 4, 
        Int::toBytes(lookback_time_a + 5, 2)
    );
    data.replace(0x8, 4, 
        Int::toBytes(lookback_time_b + 5, 2)
    );
    data.replace(0xa, 4, 
        Int::toBytes(dropout_delay_time + 1, 2)
    );
    data.replace(0xc, 4, 
        Int::toBytes(dwell_time + 1, 2)
    );
    data.replace(0xe, 4, 
        Int::toBytes(revert_channel, 2)
    );
    data.replace(0xf, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );

    for(int i=0; i < channels.size(); i++){
        Channel *ch = channels.at(i);
        channel_data.replace(i*2, 2, 
            Int::toBytes(ch->id, 2, Endian::Big)
        );
    }
    channel_data.append(QByteArray(0xc, 0));
    data.append(channel_data);

    return data;
}

void ScanList::save(QDataStream &ds){
    ds << id;
    ds << scan_mode;
    ds << priority_channel_select;
    ds << priority_channel_1;
    ds << priority_channel_2;
    ds << revert_channel;
    ds << lookback_time_a;
    ds << lookback_time_b;
    ds << dropout_delay_time;
    ds << dwell_time;

    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void ScanList::load(QDataStream &ds){
    ds >> scan_mode;
    ds >> priority_channel_select;
    ds >> priority_channel_1;
    ds >> priority_channel_2;
    ds >> revert_channel;
    ds >> lookback_time_a;
    ds >> lookback_time_b;
    ds >> dropout_delay_time;
    ds >> dwell_time;

    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}