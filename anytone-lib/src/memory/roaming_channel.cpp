#include "roaming_channel.h"
#include "memory/at_memory.h"

double Anytone::RoamingChannel::getRxFrequencyDouble(){
    return double(rx_frequency) / 100000;
};
QString Anytone::RoamingChannel::getRxFrequencyString(){
    return QString::number(getTxFrequencyDouble(), 'f', 5);
};
double Anytone::RoamingChannel::getTxFrequencyDouble(){
    return double(tx_frequency) / 100000;
};
QString Anytone::RoamingChannel::getTxFrequencyString(){
    return QString::number(getTxFrequencyDouble(), 'f', 5);
};

void Anytone::RoamingChannel::decode(QByteArray data){
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
void Anytone::RoamingChannel::decode_D878UVII(QByteArray data){
    rx_frequency = QString(data.mid(0x0, 4).toHex()).toInt();
    tx_frequency = QString(data.mid(0x4, 4).toHex()).toInt();
    color_code = static_cast<uint8_t>(data.at(0x8));
    slot = static_cast<uint8_t>(data.at(0x9));
    name = QString(data.mid(0xa, 0x10));
    name.remove(QChar('\0'));
}
void Anytone::RoamingChannel::decode_D890UV(QByteArray data){
    rx_frequency = QString(data.mid(0x0, 4).toHex()).toInt();
    tx_frequency = QString(data.mid(0x4, 4).toHex()).toInt();
    color_code = static_cast<uint8_t>(data.at(0x8));
    slot = static_cast<uint8_t>(data.at(0x9));
    name = QString(data.mid(0xa, 0x20));
    name.remove(QChar('\0'));
}
void Anytone::RoamingChannel::decode_D168UV(QByteArray data){

}
QByteArray Anytone::RoamingChannel::encode(){
    QByteArray data(0x20, 0);
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(rx_frequency).rightJustified(8, '0').toUtf8())
    );
    data.replace(0x4, 4, 
        QByteArray::fromHex(QString::number(tx_frequency).rightJustified(8, '0').toUtf8())
    );
    data.replace(0x8, 1, 
        Int::toBytes(slot, 1)
    );
    data.replace(0x9, 1, 
        Int::toBytes(slot, 1)
    );
    data.replace(0xa, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );
    
    return data;
}

void Anytone::RoamingChannel::save(QXmlStreamWriter &xml){
    xml.writeStartElement("RoamingChannel");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("rx_frequency", QString::number(rx_frequency));
    xml.writeAttribute("tx_frequency", QString::number(tx_frequency));
    xml.writeAttribute("color_code", QString::number(color_code));
    xml.writeAttribute("slot", QString::number(slot));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::RoamingChannel::load(QXmlStreamReader &xml){
    if (xml.name() == "RoamingChannel"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("rx_frequency"))
            rx_frequency = attributes.value("rx_frequency").toInt();
        if(attributes.hasAttribute("tx_frequency"))
            tx_frequency = attributes.value("tx_frequency").toInt();
        if(attributes.hasAttribute("color_code"))
            color_code = attributes.value("color_code").toInt();
        if(attributes.hasAttribute("slot"))
            slot = attributes.value("slot").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
    }
}