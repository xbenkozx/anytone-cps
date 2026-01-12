#include "zone.h"

void Anytone::Zone::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Zone");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("name", name);
    xml.writeAttribute("hide", QString::number(hide));
    xml.writeAttribute("a_channel_idx", QString::number(a_channel_idx));
    xml.writeAttribute("b_channel_idx", QString::number(b_channel_idx));
    QString ch_idx_str;
    for(Channel *ch : channels){
        ch_idx_str += "|" + QString::number(ch->id);
    }
    ch_idx_str.removeFirst();
    xml.writeAttribute("channel_list", ch_idx_str);
    xml.writeEndElement();
}
void Anytone::Zone::load(QXmlStreamReader &xml){
    if (xml.name() == "Zone"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
        if(attributes.hasAttribute("hide"))
            hide = attributes.value("hide").toInt();
        if(attributes.hasAttribute("a_channel_idx"))
            a_channel_idx = attributes.value("a_channel_idx").toInt();
        if(attributes.hasAttribute("b_channel_idx"))
            b_channel_idx = attributes.value("b_channel_idx").toInt();

        if(attributes.hasAttribute("channel_list")){
            QString ch_idx_str = attributes.value("channel_list").toString();
            for(QString idx : ch_idx_str.split("|")){
                temp_member_channel_idxs.append(static_cast<uint16_t>(idx.toInt()));
            }
        }
    }
}