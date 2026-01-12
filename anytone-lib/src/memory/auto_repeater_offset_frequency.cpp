#include "memory/auto_repeater_offset_frequency.h"

double Anytone::AutoRepeaterOffsetFrequency::getFrequencyDouble(){
    return double(frequency) / 100000;
}

QString Anytone::AutoRepeaterOffsetFrequency::getFrequencyString(){
    return QString::number(getFrequencyDouble(), 'f', 3);
}
void Anytone::AutoRepeaterOffsetFrequency::save(QXmlStreamWriter &xml){
    
    xml.writeStartElement("AutoRepeater");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("frequency", QString::number(frequency));
    xml.writeEndElement();
}
void Anytone::AutoRepeaterOffsetFrequency::load(QXmlStreamReader &xml){
    if (xml.name() == "AutoRepeater"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("frequency"))
            frequency = attributes.value("frequency").toInt();

    }
}