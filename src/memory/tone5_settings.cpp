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