#include "memory/channel.h"
#include "memory/anytone_memory.h"
#include <QXmlStreamAttributes>

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
    custom_ctcss = 251100;
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
    tx_interrupt = 0;
    dmr_crc_ignore = 0;
    scrambler_set = 0;
    custom_scrambler = 0;
    name = "";

    temp_radio_id_name = "";
    temp_scan_list_name = "";
    temp_receive_group_name = "";

    contact = nullptr;
    radioid = nullptr;
    scanlist = nullptr;
}
void Anytone::Channel::setFrequencyStr(QString rx_frequency, QString tx_frequency){
    int rx_freq = qRound(rx_frequency.toDouble() * 100000);
    int tx_freq = qRound(tx_frequency.toDouble() * 100000);
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
        tx_interrupt = ch->tx_interrupt;
        dmr_crc_ignore = ch->dmr_crc_ignore;
        scrambler_set = ch->scrambler_set;
        custom_scrambler = ch->custom_scrambler;
}
void Anytone::Channel::decode(QByteArray data){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            decode_D878UVII(data);
            break;
        case Anytone::RadioModel::D890UV_FW103:
            decode_D890UV(data);
            break;
        case Anytone::RadioModel::D168UV:
            decode_D168UV(data);
            break;
        default:
        break;
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
    custom_ctcss = Int::fromBytes(data.mid(0x10, 2));
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
void Anytone::Channel::decode_D890UV(QByteArray data){
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
    custom_ctcss = Int::fromBytes(data.mid(0x10, 2));
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
    
    dmr_crc_ignore = Bit::test(static_cast<unsigned char>(data.at(0x34)), 7);
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
    scrambler_set = static_cast<uint8_t>(data.at(0x3e));
    custom_scrambler = static_cast<uint8_t>(data.at(0x3f));

    r5tone_bot = static_cast<uint8_t>(data.at(0x40));
    r5tone_eot = static_cast<uint8_t>(data.at(0x41));
    tx_color_code_idx = static_cast<uint8_t>(data.at(0x43));

    name = QString(data.mid(0x44, 0x20));
    name.remove(QChar('\0'));

    // QByteArray bytes(reinterpret_cast<const char*>(name.utf16()), name.size() * 2);
    // qDebug() << bytes;
}
void Anytone::Channel::decode_D168UV(QByteArray data){

    if(rx_frequency == 0){
        return;
    }
}

QByteArray Anytone::Channel::encodeData(){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            return encode_D878UVII();
        case Anytone::RadioModel::D890UV_FW103:
            return encode_D890UV();
        case Anytone::RadioModel::D168UV:
            return encode_D168UV();
        default:
            return QByteArray(0x80, 0);
        break;
    }
}

QByteArray Anytone::Channel::encode_D878UVII(){
    QByteArray data(0x80, 0);
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

    bytes[0xa] = ctcss_encode_tone;
    bytes[0xb] = ctcss_decode_tone;

    data.replace(0xc, 2, 
        Int::toBytes(dcs_encode_tone, 2)
    );
    data.replace(0xe, 2, 
        Int::toBytes(dcs_decode_tone, 2)
    );

    data.replace(0x10, 2, 
        Int::toBytes(custom_ctcss, 2)
    );

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
    
    bytes[0x40] = r5tone_bot;
    bytes[0x41] = r5tone_eot;
    bytes[0x43] = tx_color_code_idx;

    return data;

    return data;
}
QByteArray Anytone::Channel::encode_D890UV(){
    QByteArray data(0x80, 0);
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

    bytes[0xa] = ctcss_encode_tone;
    bytes[0xb] = ctcss_decode_tone;

    data.replace(0xc, 2, Int::toBytes(dcs_encode_tone, 2));
    data.replace(0xe, 2, Int::toBytes(dcs_decode_tone, 2));
    data.replace(0x10, 2, Int::toBytes(custom_ctcss, 2));
    data[0x12] = tone2_decode;
    data.replace(0x13, 2, Int::toBytes(contact_idx, 2, Endian::Big));
    radio_id_idx = data[0x18];
    data[0x19] += (squelch_mode << 4);
    data[0x19] += ptt_id;
    data[0x1a] += (optional_signal << 4);
    data[0x1a] += busy_lock;
    data[0x1b] = scan_list_idx;
    data[0x1c] = receive_group_call_list_idx;
    data[0x1d] = tone2_id_idx;
    data[0x1e] = tone5_id_idx;
    data[0x1f] = dtmf_id_idx;
    data[0x20] = rx_color_code_idx;

    if(work_alone) Bit::set(&bytes[0x21], 7);
    if(aprs_rx) Bit::set(&bytes[0x21], 5);
    if(slot_suit) Bit::set(&bytes[0x21], 4);
    if(time_slot) Bit::set(&bytes[0x21], 1);
    if(sms_confirmation) Bit::set(&bytes[0x21], 0);
    data[0x21] += (dmr_mode_dcdm << 2);

    data[0x22] = aes_encryption_idx;
    if(dmr_crc_ignore) Bit::set(&bytes[0x34], 7);
    if(auto_scan) Bit::set(&bytes[0x34], 4);
    if(data_ack_disable) Bit::set(&bytes[0x34], 3);
    if(exclude_channel_roaming) Bit::set(&bytes[0x34], 2);
    if(dmr_mode) Bit::set(&bytes[0x34], 1);
    if(ranging) Bit::set(&bytes[0x34], 0);

    data[0x35] = aprs_report_type;
    data[0x36] = analog_aprs_ptt_mode;
    data[0x37] = digital_aprs_ptt_mode;
    data[0x38] = digital_aprs_report_channel;
    data[0x39] = correct_frequency;
    data[0x3a] = digital_encryption;

    if(extend_encryption) Bit::set(&bytes[0x3b], 5);
    if(send_talker_alias) Bit::set(&bytes[0x3b], 4);
    if(analog_aprs_mute) Bit::set(&bytes[0x3b], 3);
    if(sms_forbid) Bit::set(&bytes[0x3b], 2);
    if(aes_random_key) Bit::set(&bytes[0x3b], 1);
    if(aes_multiple_key) Bit::set(&bytes[0x3b], 0);

    data[0x3c] = analog_aprs_report_frequency_idx;
    data[0x3d] = arc4_encryption_key_idx;
    data[0x3e] = scrambler_set;
    data[0x3f] = custom_scrambler;

    data[0x40] = r5tone_bot;
    data[0x41] = r5tone_eot;
    data[0x43] = tx_color_code_idx;

    data.replace(0x44, 0x20, Format::wideCharString(name).leftJustified(0x20, 0x0));

    
    return data;
}
QByteArray Anytone::Channel::encode_D168UV(){
    QByteArray data(0x80, 0);
    auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());

    return data;
}

void Anytone::Channel::save(QXmlStreamWriter &xml){
    xml.writeStartElement("Channel");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("rx_frequency", QString::number(rx_frequency));
    xml.writeAttribute("offset", QString::number(offset));
    xml.writeAttribute("offset_direction",  QString::number(offset_direction));
    xml.writeAttribute("correct_frequency",  QString::number(correct_frequency));
    xml.writeAttribute("name", name);
    xml.writeAttribute("band_width",  QString::number(band_width));
    xml.writeAttribute("tx_power",  QString::number(tx_power));
    xml.writeAttribute("channel_type",  QString::number(channel_type));
    xml.writeAttribute("talkaround", talkaround?"1":"0");
    xml.writeAttribute("call_confirmation", call_confirmation?"1":"0");
    xml.writeAttribute("ptt_prohibit", ptt_prohibit?"1":"0");
    xml.writeAttribute("custom_ctcss", QString::number(custom_ctcss));
    xml.writeAttribute("ctcss_dcs_decode",  QString::number(ctcss_dcs_decode));
    xml.writeAttribute("ctcss_dcs_encode",  QString::number(ctcss_dcs_encode));
    xml.writeAttribute("ctcss_decode_tone",  QString::number(ctcss_decode_tone));
    xml.writeAttribute("ctcss_encode_tone",  QString::number(ctcss_encode_tone));
    xml.writeAttribute("dcs_decode_tone",  QString::number(dcs_decode_tone));
    xml.writeAttribute("dcs_encode_tone",  QString::number(dcs_encode_tone));
    xml.writeAttribute("contact_idx",  QString::number(contact_idx));
    xml.writeAttribute("radio_id_idx",  QString::number(radio_id_idx));
    xml.writeAttribute("squelch_mode",  QString::number(squelch_mode));
    xml.writeAttribute("ptt_id",  QString::number(ptt_id));
    xml.writeAttribute("optional_signal",  QString::number(optional_signal));
    xml.writeAttribute("busy_lock",  QString::number(busy_lock));
    xml.writeAttribute("scan_list_idx",  QString::number(scan_list_idx));
    xml.writeAttribute("tone2_id_idx",  QString::number(tone2_id_idx));
    xml.writeAttribute("tone5_id_idx",  QString::number(tone5_id_idx));
    xml.writeAttribute("dtmf_id_idx",  QString::number(dtmf_id_idx));
    xml.writeAttribute("rx_color_code_idx",  QString::number(rx_color_code_idx));
    xml.writeAttribute("tx_color_code_idx",  QString::number(tx_color_code_idx));
    xml.writeAttribute("work_alone",  work_alone?"1":"0");
    xml.writeAttribute("slot_suit",  slot_suit?"1":"0");
    xml.writeAttribute("dmr_mode_dcdm",  QString::number(dmr_mode_dcdm));
    xml.writeAttribute("time_slot",  QString::number(time_slot));
    xml.writeAttribute("receive_group_call_list_idx",  QString::number(receive_group_call_list_idx));
    xml.writeAttribute("sms_confirmation", sms_confirmation?"1":"0");
    xml.writeAttribute("aes_encryption_idx",  QString::number(aes_encryption_idx));
    xml.writeAttribute("auto_scan", auto_scan?"1":"0");
    xml.writeAttribute("data_ack_disable", data_ack_disable?"1":"0");
    xml.writeAttribute("exclude_channel_roaming", exclude_channel_roaming?"1":"0");
    xml.writeAttribute("dmr_mode",  QString::number(dmr_mode));
    xml.writeAttribute("ranging", ranging?"1":"0");
    xml.writeAttribute("extend_encryption",  QString::number(extend_encryption));
    xml.writeAttribute("send_talker_alias", send_talker_alias?"1":"0");
    xml.writeAttribute("sms_forbid", QString::number(sms_forbid));
    xml.writeAttribute("aes_random_key", QString::number(aes_random_key));
    xml.writeAttribute("aes_multiple_key", QString::number(aes_multiple_key));
    xml.writeAttribute("arc4_encryption_key_idx",  QString::number(arc4_encryption_key_idx));
    xml.writeAttribute("analog_aprs_report_frequency_idx",  QString::number(analog_aprs_report_frequency_idx));
    xml.writeAttribute("reverse",  QString::number(reverse));
    xml.writeAttribute("aprs_rx", aprs_rx?"1":"0");
    xml.writeAttribute("analog_aprs_ptt_mode",  QString::number(analog_aprs_ptt_mode));
    xml.writeAttribute("digital_aprs_ptt_mode",  QString::number(digital_aprs_ptt_mode));
    xml.writeAttribute("aprs_report_type",  QString::number(aprs_report_type));
    xml.writeAttribute("analog_aprs_mute", analog_aprs_mute?"1":"0");
    xml.writeAttribute("digital_aprs_report_channel",  QString::number(digital_aprs_report_channel));
    xml.writeAttribute("tone2_decode",  QString::number(tone2_decode));
    xml.writeAttribute("r5tone_bot",  QString::number(r5tone_bot));
    xml.writeAttribute("r5tone_eot",  QString::number(r5tone_eot));
    xml.writeAttribute("digital_encryption",  QString::number(digital_encryption));
    xml.writeAttribute("custom_scrambler",  QString::number(custom_scrambler));

    
    xml.writeEndElement();
}
void Anytone::Channel::load(QXmlStreamReader &xml){
    if (xml.name() == "Channel"){
        QXmlStreamAttributes attributes = xml.attributes();
        
        if(attributes.hasAttribute("rx_frequency"))
            rx_frequency = attributes.value("rx_frequency").toInt();
        if(attributes.hasAttribute("offset"))
            offset = attributes.value("offset").toInt();
        if(attributes.hasAttribute("offset_direction"))
            offset_direction = attributes.value("offset_direction").toInt();
        if(attributes.hasAttribute("correct_frequency"))
            correct_frequency = attributes.value("correct_frequency").toInt();
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
        if(attributes.hasAttribute("band_width"))
            band_width = attributes.value("band_width").toInt();
        if(attributes.hasAttribute("tx_power"))
            tx_power = attributes.value("tx_power").toInt();
        if(attributes.hasAttribute("channel_type"))
            channel_type = attributes.value("channel_type").toInt();
        if(attributes.hasAttribute("talkaround"))
            talkaround = attributes.value("talkaround").toInt();
        if(attributes.hasAttribute("call_confirmation"))
            call_confirmation = attributes.value("call_confirmation").toInt();
        if(attributes.hasAttribute("ptt_prohibit"))
            ptt_prohibit = attributes.value("ptt_prohibit").toInt();
        if(attributes.hasAttribute("custom_ctcss"))
            custom_ctcss = attributes.value("custom_ctcss").toInt();
        if(attributes.hasAttribute("ctcss_dcs_decode"))
            ctcss_dcs_decode = attributes.value("ctcss_dcs_decode").toInt();
        if(attributes.hasAttribute("ctcss_dcs_encode"))
            ctcss_dcs_encode = attributes.value("ctcss_dcs_encode").toInt();
        if(attributes.hasAttribute("ctcss_decode_tone"))
            ctcss_decode_tone = attributes.value("ctcss_decode_tone").toInt();
        if(attributes.hasAttribute("ctcss_encode_tone"))
            ctcss_encode_tone = attributes.value("ctcss_encode_tone").toInt();
        if(attributes.hasAttribute("dcs_decode_tone"))
            dcs_decode_tone = attributes.value("dcs_decode_tone").toInt();
        if(attributes.hasAttribute("dcs_encode_tone"))
            dcs_encode_tone = attributes.value("dcs_encode_tone").toInt();
        if(attributes.hasAttribute("contact_idx"))
            contact_idx = attributes.value("contact_idx").toInt();
        if(attributes.hasAttribute("radio_id_idx"))
            radio_id_idx = attributes.value("radio_id_idx").toInt();
        if(attributes.hasAttribute("squelch_mode"))
            squelch_mode = attributes.value("squelch_mode").toInt();
        if(attributes.hasAttribute("ptt_id"))
            ptt_id = attributes.value("ptt_id").toInt();
        if(attributes.hasAttribute("optional_signal"))
            optional_signal = attributes.value("optional_signal").toInt();
        if(attributes.hasAttribute("busy_lock"))
            busy_lock = attributes.value("busy_lock").toInt();
        if(attributes.hasAttribute("scan_list_idx"))
            scan_list_idx = attributes.value("scan_list_idx").toInt();
        if(attributes.hasAttribute("tone2_id_idx"))
            tone2_id_idx = attributes.value("tone2_id_idx").toInt();
        if(attributes.hasAttribute("tone5_id_idx"))
            tone5_id_idx = attributes.value("tone5_id_idx").toInt();
        if(attributes.hasAttribute("dtmf_id_idx"))
            dtmf_id_idx = attributes.value("dtmf_id_idx").toInt();
        if(attributes.hasAttribute("rx_color_code_idx"))
            rx_color_code_idx = attributes.value("rx_color_code_idx").toInt();
        if(attributes.hasAttribute("tx_color_code_idx"))
            tx_color_code_idx = attributes.value("tx_color_code_idx").toInt();
        if(attributes.hasAttribute("work_alone"))
            work_alone = attributes.value("work_alone").toInt();
        if(attributes.hasAttribute("slot_suit"))
            slot_suit = attributes.value("slot_suit").toInt();
        if(attributes.hasAttribute("dmr_mode_dcdm"))
            dmr_mode_dcdm = attributes.value("dmr_mode_dcdm").toInt();
        if(attributes.hasAttribute("time_slot"))
            time_slot = attributes.value("time_slot").toInt();
        if(attributes.hasAttribute("receive_group_call_list_idx"))
            receive_group_call_list_idx = attributes.value("receive_group_call_list_idx").toInt();
        if(attributes.hasAttribute("sms_confirmation"))
            sms_confirmation = attributes.value("sms_confirmation").toInt();
        if(attributes.hasAttribute("aes_encryption_idx"))
            aes_encryption_idx = attributes.value("aes_encryption_idx").toInt();
        if(attributes.hasAttribute("auto_scan"))
            auto_scan = attributes.value("auto_scan").toInt();
        if(attributes.hasAttribute("data_ack_disable"))
            data_ack_disable = attributes.value("data_ack_disable").toInt();
        if(attributes.hasAttribute("exclude_channel_roaming"))
            exclude_channel_roaming = attributes.value("exclude_channel_roaming").toInt();
        if(attributes.hasAttribute("dmr_mode"))
            dmr_mode = attributes.value("dmr_mode").toInt();
        if(attributes.hasAttribute("ranging"))
            ranging = attributes.value("ranging").toInt();
        if(attributes.hasAttribute("extend_encryption"))
            extend_encryption = attributes.value("extend_encryption").toInt();
        if(attributes.hasAttribute("send_talker_alias"))
            send_talker_alias = attributes.value("send_talker_alias").toInt();
        if(attributes.hasAttribute("sms_forbid"))
            sms_forbid = attributes.value("sms_forbid").toInt();
        if(attributes.hasAttribute("aes_random_key"))
            aes_random_key = attributes.value("aes_random_key").toInt();
        if(attributes.hasAttribute("aes_multiple_key"))
            aes_multiple_key = attributes.value("aes_multiple_key").toInt();
        if(attributes.hasAttribute("arc4_encryption_key_idx"))
            arc4_encryption_key_idx = attributes.value("arc4_encryption_key_idx").toInt();
        if(attributes.hasAttribute("analog_aprs_report_frequency_idx"))
            analog_aprs_report_frequency_idx = attributes.value("analog_aprs_report_frequency_idx").toInt();
        if(attributes.hasAttribute("reverse"))
            reverse = attributes.value("reverse").toInt();
        if(attributes.hasAttribute("aprs_rx"))
            aprs_rx = attributes.value("aprs_rx").toInt();
        if(attributes.hasAttribute("analog_aprs_ptt_mode"))
            analog_aprs_ptt_mode = attributes.value("analog_aprs_ptt_mode").toInt();
        if(attributes.hasAttribute("digital_aprs_ptt_mode"))
            digital_aprs_ptt_mode = attributes.value("digital_aprs_ptt_mode").toInt();
        if(attributes.hasAttribute("aprs_report_type"))
            aprs_report_type = attributes.value("aprs_report_type").toInt();
        if(attributes.hasAttribute("analog_aprs_mute"))
            analog_aprs_mute = attributes.value("analog_aprs_mute").toInt();
        if(attributes.hasAttribute("digital_aprs_report_channel"))
            digital_aprs_report_channel = attributes.value("digital_aprs_report_channel").toInt();
        if(attributes.hasAttribute("tone2_decode"))
            tone2_decode = attributes.value("tone2_decode").toInt();
        if(attributes.hasAttribute("r5tone_bot"))
            r5tone_bot = attributes.value("r5tone_bot").toInt();
        if(attributes.hasAttribute("r5tone_eot"))
            r5tone_eot = attributes.value("r5tone_eot").toInt();
        if(attributes.hasAttribute("digital_encryption"))
            digital_encryption = attributes.value("digital_encryption").toInt();
        if(attributes.hasAttribute("custom_scrambler"))
            custom_scrambler = attributes.value("custom_scrambler").toInt();
    }
}
