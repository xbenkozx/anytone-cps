#include <QDebug>
#include "arc4_encryption_code.h"

void Anytone::Arc4EncryptionCode::decode(QByteArray data){
    id = static_cast<uint8_t>(data.at(0));
    key = data.mid(1, 5).toHex().toUpper();
}

QByteArray Anytone::Arc4EncryptionCode::encode(){
    QByteArray data(0x10, 0x0);
    data[0] = id;
    QByteArray keyBytes = QByteArray::fromHex(key.rightJustified(10, '0').toUtf8());
    data.replace(0x1, 0x5, keyBytes);
    return data;
}

void Anytone::Arc4EncryptionCode::save(QDataStream &ds){
    ds << index;
    ds << id;

    uint8_t key_len = key.size();
    ds << key_len;
    for(char c : key.toStdString()){
        ds << c;
    }
}
void Anytone::Arc4EncryptionCode::load(QDataStream &ds){
    ds >> id;
    
    uint8_t key_length = 0;
    ds >> key_length;
    for(int i = 0; i < key_length; i++){
        char c;
        ds >> c;
        key.append(c);
    }
}
