#include <QDebug>
#include "aes_encryption_code.h"

void Anytone::AesEncryptionCode::decode(QByteArray data){
    if(data.size() != 0x30){
        qDebug() << "AesEncryptionCode::decode incorrect data size";
        return;
    }

    id = static_cast<uint8_t>(data.at(0));
    key_length = static_cast<uint8_t>(data.at(0x22));
    key = data.mid(1, 0x21).toHex().mid(0x40 - key_length, key_length);
}
QByteArray Anytone::AesEncryptionCode::encode(){
    QByteArray data(0x30, 0x0);
    data[0] = id;
    QByteArray keyBytes = QByteArray::fromHex(key.rightJustified(0x40, '0').toUtf8());
    data.replace(0x1, keyBytes.size(), keyBytes);
    data[0x22] = key.length();
    return data;
}

void Anytone::AesEncryptionCode::save(QDataStream &ds){
    ds << index;
    ds << id;

    uint8_t key_len = key.size();
    ds << key_len;
    for(char c : key.toStdString()){
        ds << c;
    }
}
void Anytone::AesEncryptionCode::load(QDataStream &ds){
    ds >> id;
    ds >> key_length;
    
    for(int i = 0; i < key_length; i++){
        char c;
        ds >> c;
        key.append(c);
    }
}