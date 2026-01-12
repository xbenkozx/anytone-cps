#include <QDebug>
#include "memory/arc4_encryption_code.h"

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

void Anytone::Arc4EncryptionCode::save(QXmlStreamWriter &xml){
    xml.writeStartElement("ARC4Code");
    xml.writeAttribute("index", QString::number(index));
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("key", key);
    xml.writeEndElement();
}
void Anytone::Arc4EncryptionCode::load(QXmlStreamReader &xml){
    if (xml.name() == "ARC4Code"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("id"))
            id = attributes.value("id").toInt();
        if(attributes.hasAttribute("key"))
            key = attributes.value("key").toString();

    }
}
