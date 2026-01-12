#include "encryption_code.h"

void Anytone::EncryptionCode::save(QXmlStreamWriter &xml){
    xml.writeStartElement("EncryptionCode");
    xml.writeAttribute("index", QString::number(index));
    xml.writeAttribute("id", id);
    xml.writeAttribute("key", key);
    xml.writeEndElement();
}
void Anytone::EncryptionCode::load(QXmlStreamReader &xml){
    if (xml.name() == "EncryptionCode"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("id"))
            id = attributes.value("id").toString();
        if(attributes.hasAttribute("key"))
            key = attributes.value("key").toString();

    }
}