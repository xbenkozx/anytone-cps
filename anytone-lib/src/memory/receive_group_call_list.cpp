#include "receive_group_call_list.h"
#include "int.h"
#include "utils.h"
#include "anytone_memory.h"

void Anytone::ReceiveGroup::decode(QByteArray data){
    for(int i = 0; i < 64; i++){
        uint32_t idx = Int::fromBytes(data.mid(i*4, 4));
        if(idx == 0xffffffff) break;
        tg_idxs.append(idx);
    }

    name = QString(data.mid(0x100, 0x20));
    name.remove(QChar('\0'));
}

QByteArray Anytone::ReceiveGroup::encode(){
    QByteArray data(0x100, 0xff);

    for(int i = 0; i < talkgroups.size(); i++){
        Talkgroup *tg = talkgroups.at(i);
        data.replace(i*4, 4, Int::toBytes(tg->id, 4));
    }
    
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        data.append(name.toUtf8().leftJustified(0x20, 0));
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
        data.append(Format::wideCharString(name).leftJustified(0x20, 0));
    }
    

    return data;
}

void Anytone::ReceiveGroup::save(QXmlStreamWriter &xml){
    xml.writeStartElement("ReceiveGroup");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("name", name);
    QString tg_idx_str;
    for(Talkgroup *tg : talkgroups){
        tg_idx_str += "|" + QString::number(tg->id);
    }
    tg_idx_str.removeFirst();
    xml.writeAttribute("tg_list", tg_idx_str);
    xml.writeEndElement();
}
void Anytone::ReceiveGroup::load(QXmlStreamReader &xml){
    if (xml.name() == "ReceiveGroup"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
        if(attributes.hasAttribute("tg_list")){
            QString tg_idx_str = attributes.value("tg_list").toString();
            for(QString idx : tg_idx_str.split("|")){
                tg_idxs.append(static_cast<uint16_t>(idx.toInt()));
            }
        }
    }
}