#include "talkgroup_whitelist.h"

using namespace Anytone;

void TalkgroupWhitelist::save(QXmlStreamWriter &xml){
    xml.writeStartElement("TalkgroupWhitelist");
    xml.writeAttribute("id", QString::number(index));
    xml.writeAttribute("dmr_id", QString::number(dmr_id));
    xml.writeAttribute("call_type", QString::number(call_type));
    xml.writeEndElement();
}

void TalkgroupWhitelist::load(QXmlStreamReader &xml){
    if (xml.name() == "TalkgroupWhitelist"){
        QXmlStreamAttributes attributes = xml.attributes();

        if(attributes.hasAttribute("dmr_id"))
            dmr_id = attributes.value("dmr_id").toInt();
        if(attributes.hasAttribute("call_type"))
            call_type = attributes.value("call_type").toInt();
    }
}