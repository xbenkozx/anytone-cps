#include "roaming_zone.h"
#include "memory/anytone_memory.h"

void Anytone::RoamingZone::decode(QByteArray data){
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

void Anytone::RoamingZone::decode_D878UVII(QByteArray data){
    name = QString(data.mid(0x40, 0x10));
    name.remove(QChar('\0'));
    for(uint8_t ch_idx : data.mid(0, 0x40)){
        if(ch_idx == 0xff) continue;
        channel_idxs.push_back(ch_idx);
    }
}
void Anytone::RoamingZone::decode_D890UV(QByteArray data){
    name = QString(data.mid(0x40, 0x20));
    name.remove(QChar('\0'));
    for(uint8_t ch_idx : data.mid(0, 0x40)){
        if(ch_idx == 0xff) continue;
        channel_idxs.push_back(ch_idx);
    }
}
void Anytone::RoamingZone::decode_D168UV(QByteArray data){

}

QByteArray Anytone::RoamingZone::encode(){
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
QByteArray Anytone::RoamingZone::encode_D878UVII(){
    QByteArray data(0x50, 0xff);
    data.replace(0x40, 0x10, 
        name.toUtf8().leftJustified(0x10, '\0')
    );
    for(int i=0; i < channels.size(); i++){
        RoamingChannel *rc = channels.at(i);
        if(rc->rx_frequency == 0) continue;
        data[i] = rc->id;
    }
    return data;
}
QByteArray Anytone::RoamingZone::encode_D890UV(){
    QByteArray data(0x50, 0xff);
    data.replace(0x40, 0x20, 
        Format::wideCharString(name).leftJustified(0x20, '\0')
    );
    for(int i=0; i < channels.size(); i++){
        RoamingChannel *rc = channels.at(i);
        if(rc->rx_frequency == 0) continue;
        data[i] = rc->id;
    }
    return data;
}

void Anytone::RoamingZone::save(QXmlStreamWriter &xml){
    xml.writeStartElement("RoamingZone");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("name", name);
    QString ch_idx_str;
    for(RoamingChannel *rc : channels){
        ch_idx_str += "|" + QString::number(rc->id);
    }
    ch_idx_str.removeFirst();
    xml.writeAttribute("channel_list", ch_idx_str);
    xml.writeEndElement();
}
void Anytone::RoamingZone::load(QXmlStreamReader &xml){
    if (xml.name() == "RoamingZone"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
        if(attributes.hasAttribute("channel_list")){
            QString ch_idx_str = attributes.value("channel_list").toString();
            for(QString idx : ch_idx_str.split("|")){
                channel_idxs.append(idx.toInt());
            }
        }

    }
}