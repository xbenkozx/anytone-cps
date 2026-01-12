#include "tone5_settings.h"
#include "int.h"

void Anytone::Tone5Settings::decode(QByteArray data_24c1000){

    uint8_24c1031 = static_cast<uint8_t>(data_24c1000.at(0x31));

    for(int i=0; i < 0x20; i+=2){
        uint16_t hz = static_cast<uint16_t>(Int::fromBytes(data_24c1000.mid(i, 2)));
        unknown_freq_hz.push_back(hz);
    }

    for(uint8_t i = 0; i < static_cast<uint8_t>(data_24c1000.at(0x23)); i++){
        self_id += hex_char.at(static_cast<uint8_t>(data_24c1000.at(0x25 + i)));
    }

    decode_standard = static_cast<uint8_t>(data_24c1000.at(0x22));
    decoding_response = static_cast<uint8_t>(data_24c1000.at(0x21));
    decode_tone_time = static_cast<uint8_t>(data_24c1000.at(0x24));
    decode_time = static_cast<uint8_t>(data_24c1000.at(0x34));
    dec_units = static_cast<uint8_t>(data_24c1000.at(0x37));
    dis_anyid = static_cast<bool>(data_24c1000.at(0x38));
    pretime = static_cast<uint8_t>(data_24c1000.at(0x36));
    auto_reset_time = static_cast<uint8_t>(data_24c1000.at(0x2e));
    time_after_decode = static_cast<uint8_t>(data_24c1000.at(0x2c));
    pause_time = static_cast<uint8_t>(data_24c1000.at(0x2d));
    first_tone_length = static_cast<uint8_t>(data_24c1000.at(0x2f));
    stop_code = static_cast<uint8_t>(data_24c1000.at(0x32));
    stop_time_length = static_cast<uint8_t>(data_24c1000.at(0x33));
    first_tone_after_stop = static_cast<uint8_t>(data_24c1000.at(0x35));
    encode_side_tone = static_cast<bool>(data_24c1000.at(0x30));
    ptt_bot_standard = static_cast<uint8_t>(data_24c1000.at(0x41));
    ptt_bot_decode_time = static_cast<uint8_t>(data_24c1000.at(0x43));
    ptt_eot_standard = static_cast<uint8_t>(data_24c1000.at(0x61));
    ptt_eot_decode_time = static_cast<uint8_t>(data_24c1000.at(0x63));

    for(uint8_t i = 0; i < static_cast<uint8_t>(data_24c1000.at(0x42)); i++){
        ptt_bot_encode_id += hex_char.at(static_cast<uint8_t>(data_24c1000.at(0x44 + i)));
    }
    for(uint8_t i = 0; i < static_cast<uint8_t>(data_24c1000.at(0x62)); i++){
        ptt_eot_encode_id += hex_char.at(static_cast<uint8_t>(data_24c1000.at(0x64 + i)));
    }
}
void Anytone::Tone5Settings::encode(QByteArray &data_24c1000){

    data_24c1000[0x23] = self_id.size();
    for(int i=0; i < self_id.size(); i++){
        uint8_t c = hex_char.indexOf(self_id.at(i));
        data_24c1000[0x25+i] = c;
    }
    data_24c1000[0x22] = decode_standard;
    data_24c1000[0x21] = decoding_response;
    data_24c1000[0x24] = decode_tone_time;
    data_24c1000[0x34] = decode_time;
    data_24c1000[0x37] = dec_units;
    data_24c1000[0x38] = dis_anyid;
    data_24c1000[0x36] = pretime;
    data_24c1000[0x2e] = auto_reset_time;
    data_24c1000[0x2c] = time_after_decode;
    data_24c1000[0x2d] = pause_time;
    data_24c1000[0x2f] = first_tone_length;
    data_24c1000[0x32] = stop_code;
    data_24c1000[0x33] = stop_time_length;
    data_24c1000[0x35] = first_tone_after_stop;
    data_24c1000[0x30] = encode_side_tone;
    data_24c1000[0x41] = ptt_bot_standard;
    data_24c1000[0x43] = ptt_bot_decode_time;
    data_24c1000[0x61] = ptt_eot_standard;
    data_24c1000[0x63] = ptt_eot_decode_time;

    data_24c1000[0x42] = ptt_bot_encode_id.size();
    for(int i=0; i < ptt_bot_encode_id.size(); i++){
        uint8_t c = hex_char.indexOf(ptt_bot_encode_id.at(i));
        data_24c1000[0x44+i] = c;
    }

    data_24c1000[0x62] = ptt_eot_encode_id.size();
    for(int i=0; i < ptt_eot_encode_id.size(); i++){
        uint8_t c = hex_char.indexOf(ptt_eot_encode_id.at(i));
        data_24c1000[0x64+i] = c;
    }

    qDebug() << unknown_freq_hz.size();
    
    // Unknown 5 Tone Freq Hz. It doesn't appear that this data changed. May be from older FW.
    // Just in case we will store the data.
    // 0x24c1000, 0x20
    // 0x24c1031 = 0xd
    data_24c1000[0x31] = uint8_24c1031;
    for(int i=0; i < 16; i++){
        data_24c1000.replace(i*2, 2, Int::toBytes(unknown_freq_hz.at(i), 2));
    }
}

void Anytone::InformationCode::save(QXmlStreamWriter &xml){
    xml.writeStartElement("InfoCode");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("function_option", QString::number(function_option));
    xml.writeAttribute("decoding_response", QString::number(decoding_response));
    xml.writeAttribute("information_id", information_id);
    xml.writeAttribute("function_name", function_name);
    xml.writeEndElement();
}
void Anytone::InformationCode::load(QXmlStreamReader &xml){
    if (xml.name() == "InfoCode"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("function_option"))
            function_option = attributes.value("function_option").toInt();
        if(attributes.hasAttribute("decoding_response"))
            decoding_response = attributes.value("decoding_response").toInt();
        if(attributes.hasAttribute("information_id"))
            information_id = attributes.value("information_id").toString();
        if(attributes.hasAttribute("function_name"))
            function_name = attributes.value("function_name").toString();

    }
}

void Anytone::SpecialCall::save(QXmlStreamWriter &xml){
    xml.writeStartElement("SpecialCall");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("standard", QString::number(standard));
    xml.writeAttribute("tone_time", QString::number(tone_time));
    xml.writeAttribute("encode_id", encode_id);
    xml.writeAttribute("name", name);
    xml.writeEndElement();
}
void Anytone::SpecialCall::load(QXmlStreamReader &xml){
    if (xml.name() == "SpecialCall"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("standard"))
            standard = attributes.value("standard").toInt();
        if(attributes.hasAttribute("tone_time"))
            tone_time = attributes.value("tone_time").toInt();
        if(attributes.hasAttribute("encode_id"))
            encode_id = attributes.value("encode_id").toString();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();

    }
}

Anytone::Tone5Settings::Tone5Settings(){
    unknown_freq_hz.clear();
    information_code_list.clear();
    for(int i = 0; i < 16; i++){
        InformationCode *info_code = new InformationCode();
        info_code->id = i;
        information_code_list.push_back(info_code);
    }

    for(int i = 0; i < 100; i++){
        SpecialCall *sp_call = new SpecialCall();
        sp_call->id = i;
        special_call_list.push_back(sp_call);
    }
}
void Anytone::Tone5Settings::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Tone5Settings");

    xml.writeAttribute("decode_standard", QString::number(decode_standard));
    xml.writeAttribute("decoding_response", QString::number(decoding_response));
    xml.writeAttribute("decode_tone_time", QString::number(decode_tone_time));
    xml.writeAttribute("decode_time", QString::number(decode_time));
    xml.writeAttribute("dec_units", QString::number(dec_units));
    xml.writeAttribute("dis_anyid", QString::number(dis_anyid));
    xml.writeAttribute("pretime", QString::number(pretime));
    xml.writeAttribute("auto_reset_time", QString::number(auto_reset_time));
    xml.writeAttribute("time_after_decode", QString::number(time_after_decode));
    xml.writeAttribute("pause_time", QString::number(pause_time));
    xml.writeAttribute("first_tone_length", QString::number(first_tone_length));
    xml.writeAttribute("stop_code", QString::number(stop_code));
    xml.writeAttribute("stop_time_length", QString::number(stop_time_length));
    xml.writeAttribute("first_tone_after_stop", QString::number(first_tone_after_stop));
    xml.writeAttribute("encode_side_tone", QString::number(encode_side_tone));
    xml.writeAttribute("ptt_bot_standard", QString::number(ptt_bot_standard));
    xml.writeAttribute("ptt_bot_decode_time", QString::number(ptt_bot_decode_time));
    xml.writeAttribute("ptt_eot_standard", QString::number(ptt_eot_standard));
    xml.writeAttribute("ptt_eot_decode_time", QString::number(ptt_eot_decode_time));
    xml.writeAttribute("uint8_24c1031", QString::number(uint8_24c1031));
    xml.writeAttribute("self_id", self_id);
    xml.writeAttribute("ptt_bot_encode_id", ptt_bot_encode_id);
    xml.writeAttribute("ptt_eot_encode_id", ptt_eot_encode_id);

    QString unknown_freq_hz_str;
    for(uint16_t i : unknown_freq_hz){
        unknown_freq_hz_str += "|" + QString::number(i);
    }
    unknown_freq_hz_str.removeFirst();

    xml.writeAttribute("unknown_freq_hz", unknown_freq_hz_str);

    xml.writeStartElement("InfoCodeList");
    for(InformationCode *code : information_code_list){
        code->save(xml);
    }
    xml.writeEndElement();

    xml.writeStartElement("SpecialCallList");
    for(SpecialCall *call : special_call_list){
        call->save(xml);
    }
    xml.writeEndElement();

    
    xml.writeEndElement();
}
void Anytone::Tone5Settings::load(QXmlStreamReader &xml){
    if (xml.name() == "Tone5Settings"){
        QXmlStreamAttributes attributes = xml.attributes();

        if(attributes.hasAttribute("decode_standard"))
            decode_standard = attributes.value("decode_standard").toInt();
        if(attributes.hasAttribute("decoding_response"))
            decoding_response = attributes.value("decoding_response").toInt();
        if(attributes.hasAttribute("decode_tone_time"))
            decode_tone_time = attributes.value("decode_tone_time").toInt();
        if(attributes.hasAttribute("decode_time"))
            decode_time = attributes.value("decode_time").toInt();
        if(attributes.hasAttribute("dec_units"))
            dec_units = attributes.value("dec_units").toInt();
        if(attributes.hasAttribute("dis_anyid"))
            dis_anyid = attributes.value("dis_anyid").toInt();
        if(attributes.hasAttribute("pretime"))
            pretime = attributes.value("pretime").toInt();
        if(attributes.hasAttribute("auto_reset_time"))
            auto_reset_time = attributes.value("auto_reset_time").toInt();
        if(attributes.hasAttribute("time_after_decode"))
            time_after_decode = attributes.value("time_after_decode").toInt();
        if(attributes.hasAttribute("pause_time"))
            pause_time = attributes.value("pause_time").toInt();
        if(attributes.hasAttribute("first_tone_length"))
            first_tone_length = attributes.value("first_tone_length").toInt();
        if(attributes.hasAttribute("stop_code"))
            stop_code = attributes.value("stop_code").toInt();
        if(attributes.hasAttribute("stop_time_length"))
            stop_time_length = attributes.value("stop_time_length").toInt();
        if(attributes.hasAttribute("first_tone_after_stop"))
            first_tone_after_stop = attributes.value("first_tone_after_stop").toInt();
        if(attributes.hasAttribute("encode_side_tone"))
            encode_side_tone = attributes.value("encode_side_tone").toInt();
        if(attributes.hasAttribute("ptt_bot_standard"))
            ptt_bot_standard = attributes.value("ptt_bot_standard").toInt();
        if(attributes.hasAttribute("ptt_bot_decode_time"))
            ptt_bot_decode_time = attributes.value("ptt_bot_decode_time").toInt();
        if(attributes.hasAttribute("ptt_eot_standard"))
            ptt_eot_standard = attributes.value("ptt_eot_standard").toInt();
        if(attributes.hasAttribute("ptt_eot_decode_time"))
            ptt_eot_decode_time = attributes.value("ptt_eot_decode_time").toInt();
        if(attributes.hasAttribute("uint8_24c1031"))
            uint8_24c1031 = attributes.value("uint8_24c1031").toInt();

        if(attributes.hasAttribute("unknown_freq_hz")){
            QString unknown_freq_hz_str = attributes.value("unknown_freq_hz").toString();
            for(QString hz : unknown_freq_hz_str.split("|")){
                unknown_freq_hz.append(static_cast<uint16_t>(hz.toInt()));
            }
        }

        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        while (!xml.atEnd() && !xml.hasError()) {
            if(token == QXmlStreamReader::StartElement && (
                xml.name() == "InfoCodeList" || xml.name() == "SpecialCallList"
            )){

            }else if(token == QXmlStreamReader::StartElement && xml.name() == "InfoCode"){
                attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < information_code_list.size()) {
                    InformationCode * item = information_code_list.at(idx);
                    item->load(xml);
                }
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "SpecialCall"){
                attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < special_call_list.size()) {
                    SpecialCall * item = special_call_list.at(idx);
                    item->load(xml);
                }
            }else if(token == QXmlStreamReader::StartElement){
                break;
            }
            token = xml.readNext();
        }

    }
}
