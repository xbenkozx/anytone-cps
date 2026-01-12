#include "prefabricated_sms.h"

void Anytone::PrefabricatedSms::decode(QByteArray data){
    text = QString(data);
    text.remove(QChar('\0'));
}

QByteArray Anytone::PrefabricatedSms::encode(){
    return text.toUtf8().leftJustified(0xd0, '\0');
}

void Anytone::PrefabricatedSms::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Sms");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("text", text);
    xml.writeEndElement();
}
void Anytone::PrefabricatedSms::load(QXmlStreamReader &xml){
     if (xml.name() == "Sms"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("text"))
            text = attributes.value("text").toString();
    }
}