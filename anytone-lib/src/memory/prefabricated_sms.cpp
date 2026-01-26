#include "prefabricated_sms.h"
#include "utils.h"
#include "anytone_memory.h"

void Anytone::PrefabricatedSms::decode(QByteArray data){
    text = QString(data);
    text.remove(QChar('\0'));
}

QByteArray Anytone::PrefabricatedSms::encodeData(){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            return encode_D878UVII();
        case Anytone::RadioModel::D890UV_FW103:
            return encode_D890UV();
        case Anytone::RadioModel::D168UV:
            // return encode_D168UV();
        default:
            return QByteArray(0x80, 0);
        break;
    }
}

QByteArray Anytone::PrefabricatedSms::encode_D878UVII(){
    return text.toUtf8().leftJustified(0xd0, '\0');
}

QByteArray Anytone::PrefabricatedSms::encode_D890UV(){
    return Format::wideCharString(text).leftJustified(0x1a0, '\0');
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