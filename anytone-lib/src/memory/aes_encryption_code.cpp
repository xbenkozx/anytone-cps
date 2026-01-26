#include <QDebug>
#include "memory/aes_encryption_code.h"

void Anytone::AesEncryptionCode::decode(QByteArray data){
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

void Anytone::AesEncryptionCode::save(QXmlStreamWriter &xml){
    xml.writeStartElement("AESCode");
    xml.writeAttribute("index", QString::number(index));
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("key", key);
    xml.writeEndElement();
}
void Anytone::AesEncryptionCode::load(QXmlStreamReader &xml){
    if (xml.name() == "AESCode"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("id"))
            id = attributes.value("id").toInt();
        if(attributes.hasAttribute("key"))
            key = attributes.value("key").toString();

    }
}