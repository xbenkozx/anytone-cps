#include <QChar>
#include "dtmf_settings.h"

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

void Anytone::DTMFSettings::save(QDataStream &ds){
    ds << tx_time;
    ds << interval_char;
    ds << group_code;
    ds << decoding_response;
    ds << first_digit_time;
    ds << pretime;
    ds << auto_reset_time;
    ds << decode_time_lapse;
    ds << ptt_id_pause_time;
    ds << d_code_pause;
    ds << side_tone;
    ds << ptt_id;

    uint8_t self_id_len = self_id.size();
    ds << self_id_len;
    for(char c : self_id.toStdString()){ ds << c; }

    uint8_t ptt_id_bot_len = ptt_id_bot.size();
    ds << ptt_id_bot_len;
    for(char c : ptt_id_bot.toStdString()){ ds << c; }

    uint8_t ptt_id_eot_len = ptt_id_eot.size();
    ds << ptt_id_eot_len;
    for(char c : ptt_id_eot.toStdString()){ ds << c; }

    uint8_t remote_kill_len = remote_kill.size();
    ds << remote_kill_len;
    for(char c : remote_kill.toStdString()){ ds << c; }

    uint8_t remote_stun_len = remote_stun.size();
    ds << remote_stun_len;
    for(char c : remote_stun.toStdString()){ ds << c; }

    uint8_t m1_len = m1.size();
    ds << m1_len;
    for(char c : m1.toStdString()){ ds << c; }

    uint8_t m2_len = m2.size();
    ds << m2_len;
    for(char c : m2.toStdString()){ ds << c; }

    uint8_t m3_len = m3.size();
    ds << m3_len;
    for(char c : m3.toStdString()){ ds << c; }

    uint8_t m4_len = m4.size();
    ds << m4_len;
    for(char c : m4.toStdString()){ ds << c; }

    uint8_t m5_len = m5.size();
    ds << m5_len;
    for(char c : m5.toStdString()){ ds << c; }

    uint8_t m6_len = m6.size();
    ds << m6_len;
    for(char c : m6.toStdString()){ ds << c; }

    uint8_t m7_len = m7.size();
    ds << m7_len;
    for(char c : m7.toStdString()){ ds << c; }

    uint8_t m8_len = m8.size();
    ds << m8_len;
    for(char c : m8.toStdString()){ ds << c; }

    uint8_t m9_len = m8.size();
    ds << m9_len;
    for(char c : m9.toStdString()){ ds << c; }

    uint8_t m10_len = m8.size();
    ds << m10_len;
    for(char c : m10.toStdString()){ ds << c; }

    uint8_t m11_len = m8.size();
    ds << m11_len;
    for(char c : m11.toStdString()){ ds << c; }

    uint8_t m12_len = m8.size();
    ds << m12_len;
    for(char c : m12.toStdString()){ ds << c; }

    uint8_t m13_len = m8.size();
    ds << m13_len;
    for(char c : m13.toStdString()){ ds << c; }

    uint8_t m14_len = m8.size();
    ds << m14_len;
    for(char c : m14.toStdString()){ ds << c; }

    uint8_t m15_len = m8.size();
    ds << m15_len;
    for(char c : m15.toStdString()){ ds << c; }

    uint8_t m16_len = m8.size();
    ds << m16_len;
    for(char c : m8.toStdString()){ ds << c; }
}
void Anytone::DTMFSettings::load(QDataStream &ds){
    ds >> tx_time;
    ds >> interval_char;
    ds >> group_code;
    ds >> decoding_response;
    ds >> first_digit_time;
    ds >> pretime;
    ds >> auto_reset_time;
    ds >> decode_time_lapse;
    ds >> ptt_id_pause_time;
    ds >> d_code_pause;
    ds >> side_tone;
    ds >> ptt_id;

    uint8_t str_size;
    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        self_id.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        ptt_id_bot.append(c);
    }
    
    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        ptt_id_eot.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        remote_kill.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        remote_stun.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m1.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m2.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m3.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m4.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m5.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m6.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m7.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m8.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m9.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m10.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m11.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m12.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m13.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m14.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m15.append(c);
    }

    ds >> str_size;
    for(int i = 0; i < str_size; i++){
        char c;
        ds >> c;
        m16.append(c);
    }
}