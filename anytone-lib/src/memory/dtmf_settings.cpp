#include <QChar>
#include "memory/dtmf_settings.h"

void Anytone::DTMFSettings::decode(QByteArray data_24c1000, QByteArray data_2500500){
    self_id = hex_char.at(static_cast<uint8_t>(data_24c1000.at(0x86))) +
            hex_char.at(static_cast<uint8_t>(data_24c1000.at(0x87))) +
            hex_char.at(static_cast<uint8_t>(data_24c1000.at(0x88)));

    interval_char = static_cast<uint8_t>(data_24c1000.at(0x80));
    group_code = static_cast<uint8_t>(data_24c1000.at(0x81));
    decoding_response = static_cast<uint8_t>(data_24c1000.at(0x82));
    first_digit_time = static_cast<uint8_t>(data_24c1000.at(0x84));
    pretime = static_cast<uint8_t>(data_24c1000.at(0x83));
    auto_reset_time = static_cast<uint8_t>(data_24c1000.at(0x85));
    decode_time_lapse = static_cast<uint8_t>(data_24c1000.at(0x8a));
    ptt_id_pause_time = static_cast<uint8_t>(data_24c1000.at(0x8b));
    d_code_pause = static_cast<uint8_t>(data_24c1000.at(0x8d));
    side_tone = static_cast<uint8_t>(data_24c1000.at(0x89));
    ptt_id = static_cast<uint8_t>(data_24c1000.at(0x8c));

    if(data_24c1000.mid(0x90, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_24c1000.mid(0x90, 0x10)){
            if(c < 16) ptt_id_bot.append(dtmf_char.at(c));
        }
    }

    if(data_24c1000.mid(0xa0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_24c1000.mid(0xa0, 0x10)){
            if(c < 16) ptt_id_eot.append(dtmf_char.at(c));
        }
    }

    if(data_24c1000.mid(0xb0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_24c1000.mid(0xb0, 0x10)){
            if(c < 16) remote_kill.append(dtmf_char.at(c));
        }
    }

    if(data_24c1000.mid(0xc0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_24c1000.mid(0xc0, 0x10)){
            if(c < 16) remote_stun.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x0, 0x10)){
            if(c < 16) m1.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x10, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x10, 0x10)){
            if(c < 16) m2.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x20, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x20, 0x10)){
            if(c < 16) m3.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x30, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x30, 0x10)){
            if(c < 16) m4.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x40, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x40, 0x10)){
            if(c < 16) m5.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x50, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x50, 0x10)){
            if(c < 16) m6.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x60, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x60, 0x10)){
            if(c < 16) m7.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x70, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x70, 0x10)){
            if(c < 16) m8.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x80, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x80, 0x10)){
            if(c < 16) m9.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0x90, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0x90, 0x10)){
            if(c < 16) m10.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0xa0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0xa0, 0x10)){
            if(c < 16) m11.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0xb0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0xb0, 0x10)){
            if(c < 16) m12.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0xc0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0xc0, 0x10)){
            if(c < 16) m13.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0xd0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0xd0, 0x10)){
            if(c < 16) m14.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0xe0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0xe0, 0x10)){
            if(c < 16) m15.append(dtmf_char.at(c));
        }
    }

    if(data_2500500.mid(0xf0, 0x10) != QByteArray(0x10, 0xff)) {
        for(uint8_t c : data_2500500.mid(0xf0, 0x10)){
            if(c < 16) m16.append(dtmf_char.at(c));
        }
    }
}
void Anytone::DTMFSettings::encode(QByteArray &data_24c1000, QByteArray &data_2500500){
    data_24c1000[0x86] = hex_char.indexOf(self_id.at(0));
    data_24c1000[0x87] = hex_char.indexOf(self_id.at(1));
    data_24c1000[0x88] = hex_char.indexOf(self_id.at(2));
    data_24c1000[0x80] = interval_char;
    data_24c1000[0x81] = group_code;
    data_24c1000[0x82] = decoding_response;
    data_24c1000[0x84] = first_digit_time;
    data_24c1000[0x83] = pretime;
    data_24c1000[0x85] = auto_reset_time;
    data_24c1000[0x8a] = decode_time_lapse;
    data_24c1000[0x8b] = ptt_id_pause_time;
    data_24c1000[0x8d] = d_code_pause;
    data_24c1000[0x89] = side_tone;
    data_24c1000[0x8c] = ptt_id;

    data_24c1000.replace(0x90, 0x10, QByteArray(0x10, 0xff));
    data_24c1000.replace(0xa0, 0x10, QByteArray(0x10, 0xff));
    data_24c1000.replace(0xb0, 0x10, QByteArray(0x10, 0xff));
    data_24c1000.replace(0xc0, 0x10, QByteArray(0x10, 0xff));
    int i = 0;
    for(QChar c : ptt_id_bot){ data_24c1000[0x90+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : ptt_id_eot){ data_24c1000[0xa0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : remote_kill){ data_24c1000[0xb0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : remote_stun){ data_24c1000[0xc0+i] = dtmf_char.indexOf(c); i++; }


    i = 0;
    for(QChar c : m1){ data_2500500[0x0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m2){ data_2500500[0x10+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m3){ data_2500500[0x20+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m4){ data_2500500[0x30+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m5){ data_2500500[0x40+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m6){ data_2500500[0x50+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m7){ data_2500500[0x60+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m8){ data_2500500[0x70+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m9){ data_2500500[0x80+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m10){ data_2500500[0x90+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m11){ data_2500500[0xa0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m12){ data_2500500[0xb0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m13){ data_2500500[0xc0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m14){ data_2500500[0xd0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m15){ data_2500500[0xe0+i] = dtmf_char.indexOf(c); i++; }
    i = 0;
    for(QChar c : m16){ data_2500500[0xf0+i] = dtmf_char.indexOf(c); i++; }
    
}

void Anytone::DTMFSettings::save(QXmlStreamWriter &xml){
    xml.writeStartElement("DTMFSettings");
    xml.writeAttribute("tx_time", QString::number(tx_time));
    xml.writeAttribute("interval_char", QString::number(interval_char));
    xml.writeAttribute("group_code", QString::number(group_code));
    xml.writeAttribute("decoding_response", QString::number(decoding_response));
    xml.writeAttribute("first_digit_time", QString::number(first_digit_time));
    xml.writeAttribute("pretime", QString::number(pretime));
    xml.writeAttribute("auto_reset_time", QString::number(auto_reset_time));
    xml.writeAttribute("decode_time_lapse", QString::number(decode_time_lapse));
    xml.writeAttribute("ptt_id_pause_time", QString::number(ptt_id_pause_time));
    xml.writeAttribute("d_code_pause", QString::number(d_code_pause));
    xml.writeAttribute("side_tone", QString::number(side_tone));
    xml.writeAttribute("ptt_id", QString::number(ptt_id));
    xml.writeAttribute("self_id", self_id);
    xml.writeAttribute("ptt_id_bot", ptt_id_bot);
    xml.writeAttribute("ptt_id_eot", ptt_id_eot);
    xml.writeAttribute("remote_kill", remote_kill);
    xml.writeAttribute("remote_stun", remote_stun);
    xml.writeAttribute("m1", m1);
    xml.writeAttribute("m2", m2);
    xml.writeAttribute("m3", m3);
    xml.writeAttribute("m4", m4);
    xml.writeAttribute("m5", m5);
    xml.writeAttribute("m6", m6);
    xml.writeAttribute("m7", m7);
    xml.writeAttribute("m8", m8);
    xml.writeAttribute("m9", m9);
    xml.writeAttribute("m10", m10);
    xml.writeAttribute("m11", m11);
    xml.writeAttribute("m12", m12);
    xml.writeAttribute("m13", m13);
    xml.writeAttribute("m14", m14);
    xml.writeAttribute("m15", m15);
    xml.writeAttribute("m16", m16);
    xml.writeEndElement();
}
void Anytone::DTMFSettings::load(QXmlStreamReader &xml){
    if (xml.name() == "DTMFSettings"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("tx_time"))
            tx_time = attributes.value("tx_time").toInt();
        if(attributes.hasAttribute("interval_char"))
            interval_char = attributes.value("interval_char").toInt();
        if(attributes.hasAttribute("group_code"))
            group_code = attributes.value("group_code").toInt();
        if(attributes.hasAttribute("decoding_response"))
            decoding_response = attributes.value("decoding_response").toInt();
        if(attributes.hasAttribute("first_digit_time"))
            first_digit_time = attributes.value("first_digit_time").toInt();
        if(attributes.hasAttribute("pretime"))
            pretime = attributes.value("pretime").toInt();
        if(attributes.hasAttribute("auto_reset_time"))
            auto_reset_time = attributes.value("auto_reset_time").toInt();
        if(attributes.hasAttribute("decode_time_lapse"))
            decode_time_lapse = attributes.value("decode_time_lapse").toInt();
        if(attributes.hasAttribute("ptt_id_pause_time"))
            ptt_id_pause_time = attributes.value("ptt_id_pause_time").toInt();
        if(attributes.hasAttribute("d_code_pause"))
            d_code_pause = attributes.value("d_code_pause").toInt();
        if(attributes.hasAttribute("side_tone"))
            side_tone = attributes.value("side_tone").toInt();
        if(attributes.hasAttribute("ptt_id"))
            ptt_id = attributes.value("ptt_id").toInt();
        if(attributes.hasAttribute("self_id"))
            self_id = attributes.value("self_id").toString();
        if(attributes.hasAttribute("ptt_id_bot"))
            ptt_id_bot = attributes.value("ptt_id_bot").toString();
        if(attributes.hasAttribute("ptt_id_eot"))
            ptt_id_eot = attributes.value("ptt_id_eot").toString();
        if(attributes.hasAttribute("remote_kill"))
            remote_kill = attributes.value("remote_kill").toString();
        if(attributes.hasAttribute("remote_stun"))
            remote_stun = attributes.value("remote_stun").toString();
        if(attributes.hasAttribute("m1"))
            m1 = attributes.value("m1").toString();
        if(attributes.hasAttribute("m2"))
            m2 = attributes.value("m2").toString();
        if(attributes.hasAttribute("m3"))
            m3 = attributes.value("m3").toString();
        if(attributes.hasAttribute("m4"))
            m4 = attributes.value("m4").toString();
        if(attributes.hasAttribute("m5"))
            m5 = attributes.value("m5").toString();
        if(attributes.hasAttribute("m6"))
            m6 = attributes.value("m6").toString();
        if(attributes.hasAttribute("m7"))
            m7 = attributes.value("m7").toString();
        if(attributes.hasAttribute("m8"))
            m8 = attributes.value("m8").toString();
        if(attributes.hasAttribute("m9"))
            m9 = attributes.value("m9").toString();
        if(attributes.hasAttribute("m10"))
            m10 = attributes.value("m10").toString();
        if(attributes.hasAttribute("m11"))
            m11 = attributes.value("m11").toString();
        if(attributes.hasAttribute("m12"))
            m12 = attributes.value("m12").toString();
        if(attributes.hasAttribute("m13"))
            m13 = attributes.value("m13").toString();
        if(attributes.hasAttribute("m14"))
            m14 = attributes.value("m14").toString();
        if(attributes.hasAttribute("m15"))
            m15 = attributes.value("m15").toString();
        if(attributes.hasAttribute("m16"))
            m16 = attributes.value("m16").toString();
    }
}