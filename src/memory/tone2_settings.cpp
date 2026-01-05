#include "tone2_settings.h"

void Anytone::Tone2EncodeItem::decode(QByteArray data){
    tone_frequency_1 = Int::fromBytes(data.mid(0, 2));
    tone_frequency_2 = Int::fromBytes(data.mid(2, 2));
    name = QString(data.mid(0x8, 0x7));
    name.remove(QChar('\0'));
}
QByteArray Anytone::Tone2EncodeItem::encode(){
    if(tone_frequency_1 == 0) return QByteArray(0x10, 0xff);
    QByteArray data(0x10, 0xff);
    data.replace(0x0, 2, 
        Int::toBytes(tone_frequency_1, 2)
    );
    data.replace(0x2, 2, 
        Int::toBytes(tone_frequency_2, 2)
    );
    data.replace(0x8, 7, 
        QByteArray::fromHex(name.rightJustified(7, '0').toUtf8())
    );
    return data;
}
void Anytone::Tone2EncodeItem::save(QDataStream &ds){
    ds << tone_frequency_1;
    ds << tone_frequency_2;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void Anytone::Tone2EncodeItem::load(QDataStream &ds){
    ds >> tone_frequency_1;
    ds >> tone_frequency_2;
    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}

void Anytone::Tone2DecodeItem::decode(QByteArray data){
    tone_frequency_1 = Int::fromBytes(data.mid(0, 2));
    tone_frequency_2 = Int::fromBytes(data.mid(2, 2));
    decoding_response = static_cast<uint8_t>(data.at(0x4));
    name = QString(data.mid(0x5, 0x7));
    name.remove(QChar('\0'));
}
QByteArray Anytone::Tone2DecodeItem::encode(){
    if(tone_frequency_1 == 0) return QByteArray(0x20, 0xff);
    QByteArray data(0x10, 0);
    data.replace(0x0, 2, 
        Int::toBytes(tone_frequency_1, 2)
    );
    data.replace(0x2, 2, 
        Int::toBytes(tone_frequency_2, 2)
    );
    data[0x4] = decoding_response;
    data.replace(0x5, 7, 
        QByteArray::fromHex(name.rightJustified(7, '0').toUtf8())
    );
    return data;
}
void Anytone::Tone2DecodeItem::save(QDataStream &ds){
    ds << tone_frequency_1;
    ds << tone_frequency_2;
    ds << decoding_response;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void Anytone::Tone2DecodeItem::load(QDataStream &ds){
    ds >> tone_frequency_1;
    ds >> tone_frequency_2;
    ds >> decoding_response;
    uint8_t name_len;
    ds >> name_len;
    for(int i = 0; i < name_len; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}

Anytone::Tone2Settings::Tone2Settings(){
    for(int i = 0; i < 24; i++){
        Tone2EncodeItem *item = new Tone2EncodeItem();
        item->id = i;
        encode_list.append(item);
    }

    for(int i = 0; i < 16; i++){
        Tone2DecodeItem *item = new Tone2DecodeItem();
        item->id = i;
        decode_list.append(item);
    }
}
void Anytone::Tone2Settings::decode(QByteArray data_24c1290){
    encode_tone_1_duration = static_cast<uint8_t>(data_24c1290.at(0x9));
    encode_tone_2_duration = static_cast<uint8_t>(data_24c1290.at(0xa));
    encode_long_tone_duration = static_cast<uint8_t>(data_24c1290.at(0xb));
    encode_gap_time = static_cast<uint8_t>(data_24c1290.at(0xc));
    encode_auto_reset_time = static_cast<uint8_t>(data_24c1290.at(0xd));
    encode_side_tone = static_cast<bool>(data_24c1290.at(0xe));
}
void Anytone::Tone2Settings::encode(QByteArray &data_24c1290){
    data_24c1290[0x9] = encode_tone_1_duration;
    data_24c1290[0xa] = encode_tone_2_duration;
    data_24c1290[0xb] = encode_long_tone_duration;
    data_24c1290[0xc] = encode_gap_time;
    data_24c1290[0xe] = encode_auto_reset_time;
    data_24c1290[0xf] = encode_side_tone;
}
void Anytone::Tone2Settings::save(QDataStream &ds){
    ds << encode_tone_1_duration;
    ds << encode_tone_2_duration;
    ds << encode_long_tone_duration;
    ds << encode_gap_time;
    ds << encode_auto_reset_time;
    ds << encode_side_tone;
    for(Tone2EncodeItem *item : encode_list){
        item->save(ds);
    }
    for(Tone2DecodeItem *item : decode_list){
        item->save(ds);
    }
}
void Anytone::Tone2Settings::load(QDataStream &ds){
    ds >> encode_tone_1_duration;
    ds >> encode_tone_2_duration;
    ds >> encode_long_tone_duration;
    ds >> encode_gap_time;
    ds >> encode_auto_reset_time;
    ds >> encode_side_tone;

    for(Tone2EncodeItem *item : encode_list){
        item->load(ds);
    }

    for(Tone2DecodeItem *item : decode_list){
        item->load(ds);
    }
}