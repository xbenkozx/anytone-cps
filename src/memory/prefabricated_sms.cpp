#include "prefabricated_sms.h"

void Anytone::PrefabricatedSms::decode(QByteArray data){
    text = QString(data);
    text.remove(QChar('\0'));
}

QByteArray Anytone::PrefabricatedSms::encode(){
    return text.toUtf8().leftJustified(0xd0, '\0');
}

void Anytone::PrefabricatedSms::save(QDataStream &ds){
    ds << id;
    uint8_t str_size = text.size();
    ds << str_size;
    for(char c : text.toStdString()){
        ds << c;
    }
}
void Anytone::PrefabricatedSms::load(QDataStream &ds){
    uint8_t str_size;
    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        text.append(c);
    }
}