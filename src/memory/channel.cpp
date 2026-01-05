#include "memory/channel.h"
#include "memory/memory.h"

void Anytone::Channel::clear(){
    rx_frequency = 0;
    offset = 0;
    offset_direction = 0;
    correct_frequency = 0;
    band_width = 0;
    tx_power = 0;
    channel_type = 0;
    talkaround = false;
    call_confirmation = false;
    ptt_prohibit = false;
    ctcss_dcs_decode = 0;
    ctcss_dcs_encode = 0;
    ctcss_decode_tone = 0;
    ctcss_encode_tone = 0;
    dcs_decode_tone = 0;
    dcs_encode_tone = 0;
    contact_idx = 0;
    radio_id_idx = 0;
    squelch_mode = 0;
    ptt_id = 0;
    optional_signal = 0;
    busy_lock = 0;
    scan_list_idx = 0;
    tone2_id_idx = 0;
    tone5_id_idx = 0;
    dtmf_id_idx = 0;
    rx_color_code_idx = 0;
    tx_color_code_idx = 0;
    work_alone = false;
    slot_suit = false;
    dmr_mode_dcdm = 0;
    time_slot = 0;
    receive_group_call_list_idx = 0;
    sms_confirmation = false;
    aes_encryption_idx = 0;
    auto_scan = false;
    data_ack_disable = false;
    exclude_channel_roaming = false;
    dmr_mode = 0;
    ranging = false;
    extend_encryption = 0;
    send_talker_alias = false;
    sms_forbid = false;
    aes_random_key = false;
    aes_multiple_key = false;
    arc4_encryption_key_idx = 0;
    analog_aprs_report_frequency_idx = 0;
    reverse = 0;
    aprs_rx = false;
    analog_aprs_ptt_mode = 0;
    digital_aprs_ptt_mode = 0;
    aprs_report_type = 0;
    analog_aprs_mute = false;
    digital_aprs_report_channel = 0;
    tone2_decode = 0;
    r5tone_bot = 0;
    r5tone_eot = 0;
    digital_encryption = 0;
    name = "";

    contact = nullptr;
    radioid = nullptr;
    scanlist = nullptr;
}
void Anytone::Channel::setFrequencyStr(QString rx_frequency, QString tx_frequency){
    int rx_freq = int(rx_frequency.toDouble() * 100000);
    int tx_freq = int(tx_frequency.toDouble() * 100000);
    setFrequency(rx_freq, tx_freq);
}
void Anytone::Channel::setFrequency(int rx_frequency, int tx_frequency){
    this->rx_frequency = rx_frequency;
    int offset = tx_frequency - rx_frequency;
    if(offset < 0){
            this->offset_direction = 2;
            this->offset = offset * -1;
    }else if(offset > 0){
        this->offset_direction = 1;
        this->offset = offset;
    }else{
        this->offset_direction = 0;
        this->offset = 0;
    }
}
int Anytone::Channel::getTxFrequency(){
    int tx_frequency = rx_frequency;

    if(offset_direction == 1){
        tx_frequency = rx_frequency + offset;
    }else if(offset_direction == 2){
        tx_frequency = rx_frequency - offset;
    }

    return tx_frequency;
};
double Anytone::Channel::getTxFrequencyDouble(){
    return double(getTxFrequency()) / 100000;
};
QString Anytone::Channel::getTxFrequencyString(){
    return QString::number(getTxFrequencyDouble(), 'f', 5);
};
double Anytone::Channel::getRxFrequencyDouble(){
    return double(rx_frequency) / 100000;
};
QString Anytone::Channel::getRxFrequencyString(){
    return QString::number(getRxFrequencyDouble(), 'f', 5);
};

void Anytone::Channel::copy(Channel *ch){
        rx_frequency = ch->rx_frequency;
        offset = ch->offset;
        offset_direction = ch->offset_direction;
        correct_frequency = ch->correct_frequency;
        band_width = ch->band_width;
        tx_power = ch->tx_power;
        channel_type = ch->channel_type;
        talkaround = ch->talkaround;
        call_confirmation = ch->call_confirmation;
        ptt_prohibit = ch->ptt_prohibit;
        ctcss_dcs_decode = ch->ctcss_dcs_decode;
        ctcss_dcs_encode = ch->ctcss_dcs_encode;
        ctcss_decode_tone = ch->ctcss_decode_tone;
        ctcss_encode_tone = ch->ctcss_encode_tone;
        dcs_decode_tone = ch->dcs_decode_tone;
        dcs_encode_tone = ch->dcs_encode_tone;
        contact_idx = ch->contact_idx;
        radio_id_idx = ch->radio_id_idx;
        squelch_mode = ch->squelch_mode;
        ptt_id = ch->ptt_id;
        optional_signal = ch->optional_signal;
        busy_lock = ch->busy_lock;
        scan_list_idx = ch->scan_list_idx;
        tone2_id_idx = ch->tone2_id_idx;
        tone5_id_idx = ch->tone5_id_idx;
        dtmf_id_idx = ch->dtmf_id_idx;
        rx_color_code_idx = ch->rx_color_code_idx;
        tx_color_code_idx = ch->tx_color_code_idx;
        work_alone = ch->work_alone;
        slot_suit = ch->slot_suit;
        dmr_mode_dcdm = ch->dmr_mode_dcdm;
        time_slot = ch->time_slot;
        receive_group_call_list_idx = ch->receive_group_call_list_idx;
        sms_confirmation = ch->sms_confirmation;
        aes_encryption_idx = ch->aes_encryption_idx;
        auto_scan = ch->auto_scan;
        data_ack_disable = ch->data_ack_disable;
        exclude_channel_roaming = ch->exclude_channel_roaming;
        dmr_mode = ch->dmr_mode;
        ranging = ch->ranging;
        extend_encryption = ch->extend_encryption;
        send_talker_alias = ch->send_talker_alias;
        sms_forbid = ch->sms_forbid;
        aes_random_key = ch->aes_random_key;
        aes_multiple_key = ch->aes_multiple_key;
        arc4_encryption_key_idx = ch->arc4_encryption_key_idx;
        analog_aprs_report_frequency_idx = ch->analog_aprs_report_frequency_idx;
        reverse = ch->reverse;
        aprs_rx = ch->aprs_rx;
        analog_aprs_ptt_mode = ch->analog_aprs_ptt_mode;
        digital_aprs_ptt_mode = ch->digital_aprs_ptt_mode;
        aprs_report_type = ch->aprs_report_type;
        analog_aprs_mute = ch->analog_aprs_mute;
        digital_aprs_report_channel = ch->digital_aprs_report_channel;
        tone2_decode = ch->tone2_decode;
        r5tone_bot = ch->r5tone_bot;
        r5tone_eot = ch->r5tone_eot;
        digital_encryption = ch->digital_encryption;
        name = ch->name;
        contact = ch->contact;
        radioid = ch->radioid;
        scanlist = ch->scanlist;
        receive_group_list = ch->receive_group_list;
}
void Anytone::Channel::decode(QByteArray data){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII:
            decode_D878UVII(data);
            break;
        case Anytone::RadioModel::D890UV:
            decode_D890UV(data);
            break;
        case Anytone::RadioModel::D168UV:
            decode_D168UV(data);
            break;
        default:
        break;
    }
}
void Anytone::Channel::decode_D890UV(QByteArray data){
    qDebug() << data;
    rx_frequency = data.mid(0x0, 0x4).toHex().toInt();
    if(rx_frequency == 0){
        return;
    }

    offset = data.mid(0x4, 0x4).toHex().toInt();
    offset_direction = (static_cast<uint8_t>(data.at(0x8)) >> 6) & 0x3;
    band_width = (static_cast<uint8_t>(data.at(0x8)) >> 4) & 0x3;
    tx_power = (static_cast<uint8_t>(data.at(0x8)) >> 2) & 0x3;
    channel_type = (static_cast<uint8_t>(data.at(0x8))) & 0x3;

    name = QString(data.mid(0x44, 0x20));
    name.remove(QChar('\0'));
}
void Anytone::Channel::decode_D168UV(QByteArray data){

    if(rx_frequency == 0){
        return;
    }
}
void Anytone::Channel::decode_D878UVII(QByteArray data){
    rx_frequency = data.mid(0x0, 0x4).toHex().toInt();

    if(rx_frequency == 0){
        return;
    }

    offset = data.mid(0x4, 0x4).toHex().toInt();
    offset_direction = (static_cast<uint8_t>(data.at(0x8)) >> 6) & 0x3;
    band_width = (static_cast<uint8_t>(data.at(0x8)) >> 4) & 0x3;
    tx_power = (static_cast<uint8_t>(data.at(0x8)) >> 2) & 0x3;
    channel_type = (static_cast<uint8_t>(data.at(0x8))) & 0x3;

    talkaround = Bit::test(static_cast<unsigned char>(data.at(0x9)), 7);
    call_confirmation = Bit::test(static_cast<unsigned char>(data.at(0x9)), 6);
    ptt_prohibit = Bit::test(static_cast<unsigned char>(data.at(0x9)), 5);
    reverse = Bit::test(static_cast<unsigned char>(data.at(0x9)), 4);
    ctcss_dcs_encode = (static_cast<uint8_t>(data.at(0x9)) >> 2) & 0x3;
    ctcss_dcs_decode = (static_cast<uint8_t>(data.at(0x9))) & 0x3;
    ctcss_encode_tone = static_cast<uint8_t>(data.at(0xa));
    ctcss_decode_tone = static_cast<uint8_t>(data.at(0xb));
    dcs_encode_tone = Int::fromBytes(data.mid(0xc, 2));
    dcs_decode_tone = Int::fromBytes(data.mid(0xe, 2));
    tone2_decode = static_cast<uint8_t>(data.at(0x12));
    contact_idx = Int::fromBytes(data.mid(0x13, 2), Endian::Big);
    radio_id_idx = static_cast<uint8_t>(data.at(0x18));
    squelch_mode = (static_cast<uint8_t>(data.at(0x19)) >> 4) & 0x3;
    ptt_id = (static_cast<uint8_t>(data.at(0x19))) & 0x3;
    optional_signal = (static_cast<uint8_t>(data.at(0x1a)) >> 4) & 0x3;
    busy_lock = (static_cast<uint8_t>(data.at(0x1a))) & 0x3;
    scan_list_idx = static_cast<uint8_t>(data.at(0x1b));
    receive_group_call_list_idx = static_cast<uint8_t>(data.at(0x1c));
    tone2_id_idx = static_cast<uint8_t>(data.at(0x1d));
    tone5_id_idx = static_cast<uint8_t>(data.at(0x1e));
    dtmf_id_idx = static_cast<uint8_t>(data.at(0x1f));
    rx_color_code_idx = static_cast<uint8_t>(data.at(0x20));
    work_alone = Bit::test(static_cast<unsigned char>(data.at(0x21)), 7);
    aprs_rx = Bit::test(static_cast<unsigned char>(data.at(0x21)), 5);
    slot_suit = Bit::test(static_cast<unsigned char>(data.at(0x21)), 4);
    dmr_mode_dcdm = (static_cast<uint8_t>(data.at(0x21)) >> 2) & 0x3;
    time_slot = Bit::test(static_cast<unsigned char>(data.at(0x21)), 1);
    sms_confirmation = Bit::test(static_cast<unsigned char>(data.at(0x21)), 0);
    aes_encryption_idx = static_cast<uint8_t>(data.at(0x22));
    name = QString(data.mid(0x23, 0x10));
    
    auto_scan = Bit::test(static_cast<unsigned char>(data.at(0x34)), 4);
    data_ack_disable = Bit::test(static_cast<unsigned char>(data.at(0x34)), 3);
    exclude_channel_roaming = Bit::test(static_cast<unsigned char>(data.at(0x34)), 2);
    dmr_mode = Bit::test(static_cast<unsigned char>(data.at(0x34)), 1);
    ranging = Bit::test(static_cast<unsigned char>(data.at(0x34)), 0);
    aprs_report_type = static_cast<uint8_t>(data.at(0x35)); 
    analog_aprs_ptt_mode = static_cast<uint8_t>(data.at(0x36));
    digital_aprs_ptt_mode = static_cast<uint8_t>(data.at(0x37));
    digital_aprs_report_channel = static_cast<uint8_t>(data.at(0x38));
    correct_frequency = static_cast<uint8_t>(data.at(0x39));
    digital_encryption = static_cast<uint8_t>(data.at(0x3a));
    extend_encryption = Bit::test(static_cast<unsigned char>(data.at(0x3b)), 5);
    send_talker_alias = Bit::test(static_cast<unsigned char>(data.at(0x3b)), 4);
    analog_aprs_mute = Bit::test(static_cast<unsigned char>(data.at(0x3b)), 3);
    sms_forbid = Bit::test(static_cast<unsigned char>(data.at(0x3b)), 2);
    aes_random_key = Bit::test(static_cast<unsigned char>(data.at(0x3b)), 1);
    aes_multiple_key = Bit::test(static_cast<unsigned char>(data.at(0x3b)), 0);
    analog_aprs_report_frequency_idx = static_cast<uint8_t>(data.at(0x3c));
    arc4_encryption_key_idx = static_cast<uint8_t>(data.at(0x3d));

    r5tone_bot = static_cast<uint8_t>(data.at(0x40));
    r5tone_eot = static_cast<uint8_t>(data.at(0x41));
    tx_color_code_idx = static_cast<uint8_t>(data.at(0x43));

    //D890 Only


    name.remove(QChar('\0'));
};

QByteArray Anytone::Channel::encodeData1(){
    QByteArray data(0x40, 0);
    auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(rx_frequency).rightJustified(8, '0').toUtf8())
    );
    data.replace(0x4, 4, 
        QByteArray::fromHex(QString::number(offset).rightJustified(8, '0').toUtf8())
    );
    data[0x8] = ((offset_direction << 6) + (band_width << 4) + (tx_power << 2) + channel_type) & 0xff;
    if(talkaround) Bit::set(&bytes[9], 7);
    if(call_confirmation) Bit::set(&bytes[9], 6);
    if(ptt_prohibit) Bit::set(&bytes[9], 5);
    if(reverse) Bit::set(&bytes[9], 4);

    bytes[9] += (ctcss_dcs_encode & 0x3) << 2;
    bytes[9] += (ctcss_dcs_decode & 0x3);

    bytes[10] = ctcss_encode_tone;
    bytes[11] = ctcss_decode_tone;

    data.replace(12, 2, 
        Int::toBytes(dcs_encode_tone, 2)
    );
    data.replace(14, 2, 
        Int::toBytes(dcs_decode_tone, 2)
    );

    bytes[16] = 0xcf;
    bytes[17] = 0x09;
    bytes[18] = tone2_decode;
    data.replace(19, 2, 
        Int::toBytes(contact_idx, 2, Endian::Big)
    );

    data[24] = radio_id_idx;
    if(squelch_mode) Bit::set(&bytes[25], 4);
    if(ptt_id) Bit::set(&bytes[25], 0);
    if(optional_signal) Bit::set(&bytes[26], 4);
    if(busy_lock) Bit::set(&bytes[26], 0);
    data[27] = scan_list_idx;
    data[28] = receive_group_call_list_idx;
    data[29] = tone2_id_idx;
    data[30] = tone5_id_idx;
    data[31] = dtmf_id_idx;
    data[32] = rx_color_code_idx;

    if(work_alone) Bit::set(&bytes[33], 7);
    if(aprs_rx) Bit::set(&bytes[33], 5);
    if(slot_suit) Bit::set(&bytes[33], 4);
    data[33] += (dmr_mode_dcdm << 2);
    if(time_slot) Bit::set(&bytes[33], 1);
    if(sms_confirmation) Bit::set(&bytes[33], 0);

    data[34] = aes_encryption_idx;
    data.replace(35, 16, 
        name.toUtf8().leftJustified(16, '\0')
    );
    if(auto_scan) Bit::set(&bytes[52], 4);
    if(data_ack_disable) Bit::set(&bytes[52], 3);
    if(exclude_channel_roaming) Bit::set(&bytes[52], 2);
    if(dmr_mode) Bit::set(&bytes[52], 1);
    if(ranging) Bit::set(&bytes[52], 0);
    data[53] = aprs_report_type;
    data[54] = analog_aprs_ptt_mode;
    data[55] = digital_aprs_ptt_mode;
    data[56] = digital_aprs_report_channel;
    data[57] = correct_frequency;
    data[58] = digital_encryption;
    if(extend_encryption) Bit::set(&bytes[59], 5);
    if(send_talker_alias) Bit::set(&bytes[59], 4);
    if(analog_aprs_mute) Bit::set(&bytes[59], 3);
    if(sms_forbid) Bit::set(&bytes[59], 2);
    if(aes_random_key) Bit::set(&bytes[59], 1);
    if(aes_multiple_key) Bit::set(&bytes[59], 0);
    data[60] = analog_aprs_report_frequency_idx;
    data[61] = arc4_encryption_key_idx;

    return data;
}
QByteArray Anytone::Channel::encodeData2(){
    QByteArray data(0x40, 0);
    auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());
    bytes[0] = r5tone_bot;
    bytes[1] = r5tone_eot;
    bytes[3] = tx_color_code_idx;

    return data;
}

void Anytone::Channel::save(QDataStream &ds){
    ds << id;
    ds << rx_frequency;
    ds << offset;
    ds << offset_direction;
    ds << correct_frequency;

    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }

    ds << band_width;
    ds << tx_power;
    ds << channel_type;
    ds << talkaround;
    ds << call_confirmation;
    ds << ptt_prohibit;
    ds << ctcss_dcs_decode;
    ds << ctcss_dcs_encode;
    ds << ctcss_decode_tone;
    ds << ctcss_encode_tone;
    ds << dcs_decode_tone;
    ds << dcs_encode_tone;
    ds << contact_idx;
    ds << radio_id_idx;
    ds << squelch_mode;
    ds << ptt_id;
    ds << optional_signal;
    ds << busy_lock;
    ds << scan_list_idx;
    ds << tone2_id_idx;
    ds << tone5_id_idx;
    ds << dtmf_id_idx;
    ds << rx_color_code_idx;
    ds << tx_color_code_idx;
    ds << work_alone;
    ds << slot_suit;
    ds << dmr_mode_dcdm;
    ds << time_slot;
    ds << receive_group_call_list_idx;
    ds << sms_confirmation;
    ds << aes_encryption_idx;
    ds << auto_scan;
    ds << data_ack_disable;
    ds << exclude_channel_roaming;
    ds << dmr_mode;
    ds << ranging;
    ds << extend_encryption;
    ds << send_talker_alias;
    ds << sms_forbid;
    ds << aes_random_key;
    ds << aes_multiple_key;
    ds << arc4_encryption_key_idx;
    ds << analog_aprs_report_frequency_idx;
    ds << reverse;
    ds << aprs_rx;
    ds << analog_aprs_ptt_mode;
    ds << digital_aprs_ptt_mode;
    ds << aprs_report_type;
    ds << analog_aprs_mute;
    ds << digital_aprs_report_channel;
    ds << tone2_decode;
    ds << r5tone_bot;
    ds << r5tone_eot;
    ds << digital_encryption;
}
void Anytone::Channel::load(QDataStream &ds){
    ds >> rx_frequency;
    ds >> offset;
    ds >> offset_direction;
    ds >> correct_frequency;

    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }

    ds >> band_width;
    ds >> tx_power;
    ds >> channel_type;
    ds >> talkaround;
    ds >> call_confirmation;
    ds >> ptt_prohibit;
    ds >> ctcss_dcs_decode;
    ds >> ctcss_dcs_encode;
    ds >> ctcss_decode_tone;
    ds >> ctcss_encode_tone;
    ds >> dcs_decode_tone;
    ds >> dcs_encode_tone;
    ds >> contact_idx;
    ds >> radio_id_idx;
    ds >> squelch_mode;
    ds >> ptt_id;
    ds >> optional_signal;
    ds >> busy_lock;
    ds >> scan_list_idx;
    ds >> tone2_id_idx;
    ds >> tone5_id_idx;
    ds >> dtmf_id_idx;
    ds >> rx_color_code_idx;
    ds >> tx_color_code_idx;
    ds >> work_alone;
    ds >> slot_suit;
    ds >> dmr_mode_dcdm;
    ds >> time_slot;
    ds >> receive_group_call_list_idx;
    ds >> sms_confirmation;
    ds >> aes_encryption_idx;
    ds >> auto_scan;
    ds >> data_ack_disable;
    ds >> exclude_channel_roaming;
    ds >> dmr_mode;
    ds >> ranging;
    ds >> extend_encryption;
    ds >> send_talker_alias;
    ds >> sms_forbid;
    ds >> aes_random_key;
    ds >> aes_multiple_key;
    ds >> arc4_encryption_key_idx;
    ds >> analog_aprs_report_frequency_idx;
    ds >> reverse;
    ds >> aprs_rx;
    ds >> analog_aprs_ptt_mode;
    ds >> digital_aprs_ptt_mode;
    ds >> aprs_report_type;
    ds >> analog_aprs_mute;
    ds >> digital_aprs_report_channel;
    ds >> tone2_decode;
    ds >> r5tone_bot;
    ds >> r5tone_eot;
    ds >> digital_encryption;

    
    // QByteArray utf8_name;
    // ds >> utf8_name;

    // name = QString::fromUtf8(utf8_name);
}