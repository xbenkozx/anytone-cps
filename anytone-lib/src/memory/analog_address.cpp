#include "memory/analog_address.h"
#include <QDebug>
#include "anytone_memory.h"
#include "utils.h"

void Anytone::AnalogAddress::decode(QByteArray data){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            decode_D878UVII(data);
            break;
        case Anytone::RadioModel::D890UV_FW103:
            decode_D890UV(data);
            break;
        case Anytone::RadioModel::D168UV:
            // decode_D168UV(data);
            break;
        default:
        break;
    }
}

void Anytone::AnalogAddress::decode_D878UVII(QByteArray data){
    uint8_t number_len = data[0x7];
    number = data.mid(0x0, 0x5).toHex().mid(0, number_len).toInt();
    name = QString(data.mid(0x8, 0xf));
    name.remove(QChar('\0'));
}

void Anytone::AnalogAddress::decode_D890UV(QByteArray data){
    uint8_t number_len = data[0x7];
    number = data.mid(0x0, 0x5).toHex().mid(0, number_len).toInt();
    name = QString(data.mid(0x8, 0x1e));
    name.remove(QChar('\0'));
}

QByteArray Anytone::AnalogAddress::encode(){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            return encode_D878UVII();
        case Anytone::RadioModel::D890UV_FW103:
            return encode_D890UV();
        case Anytone::RadioModel::D168UV:
            // return encode_D168UV();
        default:
            return QByteArray();
        break;
    }
}
QByteArray Anytone::AnalogAddress::encode_D878UVII(){
    QByteArray data(0x18, 0);
    QString num = QString::number(number);
    data.replace(0x0, 5, 
        QByteArray::fromHex(num.leftJustified(10, '0').toUtf8())
    );
    data[0x7] = num.size();
    data.replace(0x8, 0xf, 
        name.toUtf8().leftJustified(0xf, '\0')
    );

    return data;
}
QByteArray Anytone::AnalogAddress::encode_D890UV(){
    QByteArray data(0x40, 0);
    QString num = QString::number(number);
    data.replace(0x0, 5, 
        QByteArray::fromHex(num.leftJustified(10, '0').toUtf8())
    );
    data[0x7] = num.size();
    data.replace(0x8, 0x1e, 
        Format::wideCharString(name).leftJustified(0x1e, '\0')
    );

    return data;
}

void Anytone::AnalogAddress::save(QXmlStreamWriter &xml){
    xml.writeStartElement("AnalogAddress");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("number", QString::number(number));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::AnalogAddress::load(QXmlStreamReader &xml){
    if (xml.name() == "AnalogAddress"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("number"))
            number = attributes.value("number").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();

    }
}