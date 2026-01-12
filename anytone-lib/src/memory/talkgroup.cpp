#include "memory/talkgroup.h"
#include "memory/at_memory.h"

#include "utils.h"
#include "int.h"

using namespace Anytone;

Talkgroup::Talkgroup(){}
void Talkgroup::decode(QByteArray data){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            decode_D878UVII(data);
            break;
        case Anytone::RadioModel::D890UV_FW103:
            decode_D890UV(data);
            break;
        case Anytone::RadioModel::D168UV:
            decode_D168UV(data);
            break;
        default:
        break;
    }
}

void Talkgroup::decode_D878UVII(QByteArray data){
    call_type = static_cast<uint8_t>(data.at(0));
    name = QString(data.mid(0x1, 0x10));
    call_alert= static_cast<uint8_t>(data.at(0x22));
    dmr_id = QString(data.mid(0x23, 0x4).toHex()).toInt();

    name.remove(QChar('\0'));
}
void Talkgroup::decode_D890UV(QByteArray data){
    call_type = static_cast<uint8_t>(data.at(0));
    name = QString(data.mid(0x6, 0x20));
    call_alert= Bit::test(data.at(0x01), 2);
    dmr_id = QString(data.mid(0x2, 0x4).toHex()).toInt();

    name.remove(QChar('\0'));
}
void Talkgroup::decode_D168UV(QByteArray data){

}
QByteArray Talkgroup::encode(){
    QByteArray data(0x64, 0);
    auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());

    data[0] = call_type;
    data.replace(1, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );
    data[0x22] = call_alert;
    data.replace(0x23, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    return data;
}

void Anytone::Talkgroup::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Talkgroup");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("dmr_id", QString::number(dmr_id));
    xml.writeAttribute("call_alert", QString::number(call_alert));
    xml.writeAttribute("call_type", QString::number(call_type));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::Talkgroup::load(QXmlStreamReader &xml){
    if (xml.name() == "Talkgroup"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("dmr_id"))
            dmr_id = attributes.value("dmr_id").toInt();
        if(attributes.hasAttribute("call_alert"))
            call_alert = attributes.value("call_alert").toInt();
        if(attributes.hasAttribute("call_type"))
            call_type = attributes.value("call_type").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
    }
}