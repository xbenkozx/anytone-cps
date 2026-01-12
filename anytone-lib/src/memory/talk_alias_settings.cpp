#include "talk_alias_settings.h"

void Anytone::TalkAliasSettings::save(QXmlStreamWriter &xml){
    xml.writeStartElement("TalkAliasSettings");
    xml.writeAttribute("display_priority", QString::number(display_priority));
    xml.writeAttribute("data_format", QString::number(data_format));
    xml.writeEndElement();
}
void Anytone::TalkAliasSettings::load(QXmlStreamReader &xml){
    if (xml.name() == "TalkAliasSettings"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("display_priority"))
            display_priority = attributes.value("display_priority").toInt();
        if(attributes.hasAttribute("data_format"))
            data_format = attributes.value("data_format").toInt();
    }
}