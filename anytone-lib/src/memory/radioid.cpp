#include "radioid.h"
#include "memory/anytone_memory.h"

void Anytone::RadioId::decode(QByteArray data){
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


void Anytone::RadioId::decode_D878UVII(QByteArray data){
    dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
    name = QString(data.mid(5, 26));
    name.remove(QChar('\0'));
}
void Anytone::RadioId::decode_D890UV(QByteArray data){
    dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
    name = QString(data.mid(4, 52));
    name.remove(QChar('\0'));
}
void Anytone::RadioId::decode_D168UV(QByteArray data){

}

QByteArray Anytone::RadioId::encode(){
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

QByteArray Anytone::RadioId::encode_D878UVII(){
    QByteArray data(0x20, 0);
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    data.replace(5, 26, 
        name.toUtf8().leftJustified(26, '\0')
    );

    return data;
}

QByteArray Anytone::RadioId::encode_D890UV(){
    QByteArray data(0x40, 0);
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    data.replace(4, 52, 
        Format::wideCharString(name).leftJustified(52, '\0')
    );

    return data;
}

void Anytone::RadioId::save(QXmlStreamWriter &xml){
    xml.writeStartElement("RadioId");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("dmr_id", QString::number(dmr_id));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::RadioId::load(QXmlStreamReader &xml){
    if (xml.name() == "RadioId"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("dmr_id"))
            dmr_id = attributes.value("dmr_id").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
    }
}