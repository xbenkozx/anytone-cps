#include "fm.h"

double Anytone::FM::getFrequencyDouble(){
    return double(frequency) / 10000;
};
QString Anytone::FM::getFrequencyString(){
    return QString::number(getFrequencyDouble(), 'f', 2);
};
void Anytone::FM::setFrequencyString(QString freq_str){
    frequency = int(freq_str.toDouble() * 10000);
}

void Anytone::FM::save(QXmlStreamWriter &xml){
    xml.writeStartElement("FM");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("frequency", QString::number(frequency));
    xml.writeAttribute("scan_add", QString::number(scan_add));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::FM::load(QXmlStreamReader &xml){
    if (xml.name() == "FM"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("frequency"))
            frequency = attributes.value("frequency").toInt();
        if(attributes.hasAttribute("scan_add"))
            scan_add = attributes.value("scan_add").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();

    }
}