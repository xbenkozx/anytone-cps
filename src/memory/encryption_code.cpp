#include "encryption_code.h"

void Anytone::EncryptionCode::save(QDataStream &ds){
    ds << index;
    
    uint8_t id_len = id.size();
    ds << id_len;
    for(char c : id.toStdString()){
        ds << c;
    }

    uint8_t key_len = key.size();
    ds << key_len;
    for(char c : key.toStdString()){
        ds << c;
    }
}
void Anytone::EncryptionCode::load(QDataStream &ds){

    uint8_t str_size;
    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        id.append(c);
    }

    // qDebug() << str_size;

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        key.append(c);
    }

    // qDebug() << str_size;

    // qDebug() << id << key;
}