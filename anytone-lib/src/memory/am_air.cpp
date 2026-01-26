#include "am_air.h"
#include "anytone_memory.h"

using namespace Anytone;
void AmAir::decode(QByteArray data){
    if(Memory::radio_model == RadioModel::D890UV_FW103){
        decode_D890UV(data);
    }
}
void AmAir::decode_D890UV(QByteArray data){
    frequency = data.mid(0x0, 0x4).toHex().toInt();
    name = QString(data.mid(0x4, 0x20));
    name.remove(QChar('\0'));
}

QByteArray AmAir::encode(){
    if(Memory::radio_model == RadioModel::D890UV_FW103){
        return encode_D890UV();
    }
    return QByteArray();
}

QByteArray AmAir::encode_D890UV(){
    QByteArray data(0x40, 0);
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(frequency).rightJustified(8, '0').toUtf8())
    );
    data.replace(0x4, 0x20, Format::wideCharString(name).leftJustified(0x20, 0x0));

    return data;
}

QString AmAir::getFrequencyString(){
    return QString::number(double(frequency) / 100000, 'f', 5);
}

void AmAir::save(QXmlStreamWriter &xml){
    xml.writeStartElement("AmAir");
    xml.writeAttribute("id", QString::number(index));
    xml.writeAttribute("frequency", QString::number(frequency));
    xml.writeAttribute("name", name);    
    xml.writeEndElement();
}
void AmAir::load(QXmlStreamReader &xml){
    if (xml.name() == "AmAir"){
        QXmlStreamAttributes attributes = xml.attributes();

        if(attributes.hasAttribute("frequency"))
            frequency = attributes.value("frequency").toInt();
        
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
    }
}
