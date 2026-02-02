#include "tone2_settings.h"

void Anytone::Tone2EncodeItem::decode(QByteArray data){
    tone_frequency_1 = Int::fromBytes(data.mid(0, 2));
    tone_frequency_2 = Int::fromBytes(data.mid(2, 2));
    name = QString(data.mid(0x8, 0x7));
    name.remove(QChar('\0'));
}
QByteArray Anytone::Tone2EncodeItem::encode(){
    if(tone_frequency_1 == 0) return QByteArray(0x10, 0xff);
    QByteArray data(0x10, 0xff);
    data.replace(0x0, 2, 
        Int::toBytes(tone_frequency_1, 2)
    );
    data.replace(0x2, 2, 
        Int::toBytes(tone_frequency_2, 2)
    );
    data.replace(0x8, 7, 
        QByteArray::fromHex(name.rightJustified(7, '0').toUtf8())
    );
    return data;
}

void Anytone::Tone2EncodeItem::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Tone2EncodeItem");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("tone_frequency_1", QString::number(tone_frequency_1));
    xml.writeAttribute("tone_frequency_2", QString::number(tone_frequency_2));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::Tone2EncodeItem::load(QXmlStreamReader &xml){
    if (xml.name() == "Tone2EncodeItem"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("tone_frequency_1"))
            tone_frequency_1 = attributes.value("tone_frequency_1").toInt();
        if(attributes.hasAttribute("tone_frequency_2"))
            tone_frequency_2 = attributes.value("tone_frequency_2").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
    }
}


void Anytone::Tone2DecodeItem::decode(QByteArray data){
    tone_frequency_1 = Int::fromBytes(data.mid(0, 2));
    tone_frequency_2 = Int::fromBytes(data.mid(2, 2));
    decoding_response = static_cast<uint8_t>(data.at(0x4));
    name = QString(data.mid(0x5, 0x7));
    name.remove(QChar('\0'));
}
QByteArray Anytone::Tone2DecodeItem::encode(){
    if(tone_frequency_1 == 0) return QByteArray(0x10, 0xff);
    QByteArray data(0x10, 0);
    data.replace(0x0, 2, 
        Int::toBytes(tone_frequency_1, 2)
    );
    data.replace(0x2, 2, 
        Int::toBytes(tone_frequency_2, 2)
    );
    data[0x4] = decoding_response;
    data.replace(0x5, 7, 
        name.toUtf8().rightJustified(7, '\0')
    );
    return data;
}

void Anytone::Tone2DecodeItem::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Tone2DecodeItem");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("tone_frequency_1", QString::number(tone_frequency_1));
    xml.writeAttribute("tone_frequency_2", QString::number(tone_frequency_2));
    xml.writeAttribute("decoding_response", QString::number(decoding_response));
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::Tone2DecodeItem::load(QXmlStreamReader &xml){
    if (xml.name() == "Tone2DecodeItem"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("tone_frequency_1"))
            tone_frequency_1 = attributes.value("tone_frequency_1").toInt();
        if(attributes.hasAttribute("tone_frequency_2"))
            tone_frequency_2 = attributes.value("tone_frequency_2").toInt();
        if(attributes.hasAttribute("decoding_response"))
            decoding_response = attributes.value("decoding_response").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
    }
}

Anytone::Tone2Settings::Tone2Settings(){
    for(int i = 0; i < 24; i++){
        Tone2EncodeItem *item = new Tone2EncodeItem();
        item->id = i;
        encode_list.append(item);
    }

    for(int i = 0; i < 16; i++){
        Tone2DecodeItem *item = new Tone2DecodeItem();
        item->id = i;
        decode_list.append(item);
    }
}
void Anytone::Tone2Settings::decode(QByteArray data_24c1290){
    encode_tone_1_duration = static_cast<uint8_t>(data_24c1290.at(0x9));
    encode_tone_2_duration = static_cast<uint8_t>(data_24c1290.at(0xa));
    encode_long_tone_duration = static_cast<uint8_t>(data_24c1290.at(0xb));
    encode_gap_time = static_cast<uint8_t>(data_24c1290.at(0xc));
    encode_auto_reset_time = static_cast<uint8_t>(data_24c1290.at(0xd));
    encode_side_tone = static_cast<bool>(data_24c1290.at(0xe));
}
void Anytone::Tone2Settings::encode(QByteArray &data_24c1290){
    data_24c1290[0x9] = encode_tone_1_duration;
    data_24c1290[0xa] = encode_tone_2_duration;
    data_24c1290[0xb] = encode_long_tone_duration;
    data_24c1290[0xc] = encode_gap_time;
    data_24c1290[0xe] = encode_auto_reset_time;
    data_24c1290[0xf] = encode_side_tone;
}

void Anytone::Tone2Settings::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Tone2Settings");
    xml.writeAttribute("encode_tone_1_duration", QString::number(encode_tone_1_duration));
    xml.writeAttribute("encode_tone_2_duration", QString::number(encode_tone_2_duration));
    xml.writeAttribute("encode_long_tone_duration", QString::number(encode_long_tone_duration));
    xml.writeAttribute("encode_gap_time", QString::number(encode_gap_time));
    xml.writeAttribute("encode_auto_reset_time", QString::number(encode_auto_reset_time));
    xml.writeAttribute("encode_side_tone", QString::number(encode_side_tone));

    xml.writeStartElement("Tone2EncodeItemList");
    for(Tone2EncodeItem *item : encode_list){
        item->save(xml);
    }
    xml.writeEndElement();

    xml.writeStartElement("Tone2DecodeItemList");
    for(Tone2DecodeItem *item : decode_list){
        item->save(xml);
    }
    xml.writeEndElement();
    xml.writeEndElement();
}
void Anytone::Tone2Settings::load(QXmlStreamReader &xml){
    if (xml.name() == "Tone2Settings"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("encode_tone_1_duration"))
            encode_tone_1_duration = attributes.value("encode_tone_1_duration").toInt();
        if(attributes.hasAttribute("encode_tone_2_duration"))
            encode_tone_2_duration = attributes.value("encode_tone_2_duration").toInt();
        if(attributes.hasAttribute("encode_long_tone_duration"))
            encode_long_tone_duration = attributes.value("encode_long_tone_duration").toInt();
        if(attributes.hasAttribute("encode_gap_time"))
            encode_gap_time = attributes.value("encode_gap_time").toInt();
        if(attributes.hasAttribute("encode_auto_reset_time"))
            encode_auto_reset_time = attributes.value("encode_auto_reset_time").toInt();
        if(attributes.hasAttribute("encode_side_tone"))
            encode_side_tone = attributes.value("encode_side_tone").toInt();

        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        while (!xml.atEnd() && !xml.hasError()) {
            if(token == QXmlStreamReader::StartElement && (
                xml.name() == "Tone2EncodeItemList" || xml.name() == "Tone2DecodeItemList"
            )){

            }else if(token == QXmlStreamReader::StartElement && xml.name() == "Tone2EncodeItem"){
                attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < encode_list.size()) {
                    Tone2EncodeItem * item = encode_list.at(idx);
                    item->load(xml);
                }
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "Tone2DecodeItem"){
                attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < decode_list.size()) {
                    Tone2DecodeItem * item = decode_list.at(idx);
                    item->load(xml);
                }
            }else if(token == QXmlStreamReader::StartElement){
                break;
            }
            token = xml.readNext();
        }

    }
}