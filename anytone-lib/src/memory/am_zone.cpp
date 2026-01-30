#include "am_zone.h"
#include "anytone_memory.h"
#include "am_air.h"

using namespace Anytone;
void AmZone::decode(QByteArray data){
    if(Memory::radio_model == RadioModel::D890UV_FW103){
        decode_D890UV(data);
    }
}
void AmZone::decode_D890UV(QByteArray data){
    name = QString(data.mid(0, 0x20));

    member_channel_idxs.clear();
    for(int i = 0; i < 0x40; i+=2){
        uint16_t ch_idx = Int::fromBytes(data.mid(0x22 + i, 2));
        if(ch_idx >= Memory::am_air_list.size()) continue;
        member_channel_idxs.append(ch_idx);
    }

    name.remove(QChar('\0'));
}

QByteArray AmZone::encode(){
    if(Memory::radio_model == RadioModel::D890UV_FW103){
        return encode_D890UV();
    }
    return QByteArray();
}

QByteArray AmZone::encode_D890UV(){
    QByteArray data;

    return data;
}

void AmZone::save(QXmlStreamWriter &xml){

    QString member;
    QString scan;

    for(Anytone::AmAir *am : member_channels){
        member += "|" + QString::number(am->index);
    }
    for(Anytone::AmAir *am : scan_channels){
        scan += "|" + QString::number(am->index);
    }
    member = member.removeAt(0);
    scan = scan.removeAt(0);
    xml.writeStartElement("AmZone");
    xml.writeAttribute("id", QString::number(index));
    xml.writeAttribute("name", name);
    xml.writeAttribute("aChannelIdx", QString::number(aChannelIdx));
    xml.writeAttribute("member", member);
    xml.writeAttribute("scan", scan);
    xml.writeEndElement();
}
void AmZone::load(QXmlStreamReader &xml){
    if (xml.name() == "AmZone"){
        QXmlStreamAttributes attributes = xml.attributes();

        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();

        if(attributes.hasAttribute("aChannelIdx"))
            aChannelIdx = attributes.value("aChannelIdx").toInt();
        
        if(attributes.hasAttribute("member")){
            QString member = attributes.value("member").toString();
            for(QString m : member.split("|")){
                member_channel_idxs.append(m.toInt());
            }
        }

        if(attributes.hasAttribute("scan")){
            QString scan = attributes.value("scan").toString();
            for(QString m : scan.split("|")){
                scan_channel_idxs.append(m.toInt());
            }
        }
    }
}