#include "memory/analog_address.h"
#include <QDebug>

void Anytone::AnalogAddress::decode(QByteArray data){
    uint8_t number_len = data[0x7];
    number = data.mid(0x0, 0x5).toHex().mid(0, number_len).toInt();
    name = QString(data.mid(0x8, 0xf));
    name.remove(QChar('\0'));
}
QByteArray Anytone::AnalogAddress::encode(){
    QByteArray data(0x18, 0);
    QString num = QString::number(number);
    data.replace(0x0, 5, 
        QByteArray::fromHex(num.rightJustified(10, '0').toUtf8())
    );
    data[0x7] = num.size();
    data.replace(0x8, 0xf, 
        name.toUtf8().leftJustified(0xf, '\0')
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