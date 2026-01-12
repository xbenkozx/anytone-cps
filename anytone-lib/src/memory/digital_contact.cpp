#include "memory/digital_contact.h"

void Anytone::DigitalContact::save(QXmlStreamWriter &xml){
    xml.writeStartElement("DigitalContact");
    QString info;

    info += QString::number(radio_id);
    info += "|" + QString::number(call_type);
    info += "|" + QString::number(call_alert);
    info += "|" + callsign;
    info += "|" + name;
    info += "|" + city;
    info += "|" + state;
    info += "|" + country;
    info += "|" + remarks;

    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("info", info);
    // xml.writeAttribute("id", QString::number(id));
    // xml.writeAttribute("radio_id", QString::number(radio_id));
    // xml.writeAttribute("call_type", QString::number(call_type));
    // xml.writeAttribute("call_alert", QString::number(call_alert));
    // xml.writeAttribute("callsign", callsign);
    // xml.writeAttribute("name", name);
    // xml.writeAttribute("city", city);
    // xml.writeAttribute("state", state);
    // xml.writeAttribute("country", country);
    // xml.writeAttribute("remarks", remarks);
    xml.writeEndElement();
}
void Anytone::DigitalContact::load(QXmlStreamReader &xml){
    if (xml.name() == "DigitalContact"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("info"))
            QString info = attributes.value("id").toString();

    }
}