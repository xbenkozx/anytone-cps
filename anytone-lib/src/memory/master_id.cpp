#include "master_id.h"
#include "memory/at_memory.h"

void Anytone::MasterId::decode(QByteArray data){
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
void Anytone::MasterId::decode_D878UVII(QByteArray data){
    dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
    used = static_cast<uint8_t>(data.at(0x4)) == 1;
    name = QString(data.mid(5, 0x15));
    name.remove(QChar('\0'));
}
void Anytone::MasterId::decode_D890UV(QByteArray data){
    dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
    used = static_cast<uint8_t>(data.at(0x4)) == 1;
    name = QString(data.mid(5, 0x2a));
    name.remove(QChar('\0'));
}
void Anytone::MasterId::decode_D168UV(QByteArray data){

}
QByteArray Anytone::MasterId::encode(){
    QByteArray data(0x20, 0);
    data.replace(0, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    data[4] = used;
    data.replace(5, 0x1b, 
        name.toUtf8().leftJustified(0x1b, '\0')
    );
    return data;
}

void Anytone::MasterId::save(QXmlStreamWriter &xml){
    xml.writeStartElement("MasterID");
    xml.writeAttribute("dmr_id", QString::number(dmr_id));
    xml.writeAttribute("used", QString::number(used));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::MasterId::load(QXmlStreamReader &xml){
    if (xml.name() == "AESCode"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("dmr_id"))
            dmr_id = attributes.value("dmr_id").toInt();
        if(attributes.hasAttribute("used"))
            used = attributes.value("used").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();

    }
}