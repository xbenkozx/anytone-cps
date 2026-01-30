#include "memory/aprs_settings.h"

void Anytone::AprsSettings::decode_D878UVII(QByteArray data_1000, QByteArray data_1800){
    tx_freq_1 = data_1000.mid(0x1, 0x4).toHex().toInt();
    tx_delay = static_cast<uint8_t>(data_1000.at(0x5));
    send_subtone = static_cast<uint8_t>(data_1000.at(0x6));
    ctcss = static_cast<uint8_t>(data_1000.at(0x7));
    dcs = Int::fromBytes(data_1000.mid(0x8,4));
    manual_tx_interval = static_cast<uint8_t>(data_1000.at(0xa));
    auto_tx_interval = static_cast<uint8_t>(data_1000.at(0xb));
    tx_tone = static_cast<uint8_t>(data_1000.at(0xc));
    fixed_location_beacon = static_cast<uint8_t>(data_1000.at(0xd));

    fix_1_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xe)),
        static_cast<double>(data_1000.at(0xf)) + (static_cast<double>(data_1000.at(0x10)) / 100)
    );

    fix_1_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0x12)),
        static_cast<double>(data_1000.at(0x13)) + (static_cast<double>(data_1000.at(0x14)) / 100)
    );

    fix_1_ns = static_cast<uint8_t>(data_1000.at(0x11));
    fix_1_ew = static_cast<uint8_t>(data_1000.at(0x15));

    fix_2_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xcd)),
        static_cast<double>(data_1000.at(0xd4)) + (static_cast<double>(data_1000.at(0xdb)) / 100)
    );
    fix_3_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xce)),
        static_cast<double>(data_1000.at(0xd5)) + (static_cast<double>(data_1000.at(0xdc)) / 100)
    );
    fix_4_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xcf)),
        static_cast<double>(data_1000.at(0xd6)) + (static_cast<double>(data_1000.at(0xdd)) / 100)
    );
    fix_5_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd0)),
        static_cast<double>(data_1000.at(0xd7)) + (static_cast<double>(data_1000.at(0xde)) / 100)
    );
    fix_6_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd1)),
        static_cast<double>(data_1000.at(0xd8)) + (static_cast<double>(data_1000.at(0xdf)) / 100)
    );
    fix_7_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd2)),
        static_cast<double>(data_1000.at(0xd9)) + (static_cast<double>(data_1000.at(0xe0)) / 100)
    );
    fix_8_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd3)),
        static_cast<double>(data_1000.at(0xda)) + (static_cast<double>(data_1000.at(0xe1)) / 100)
    );

    fix_2_ns = static_cast<uint8_t>(data_1000.at(0xe2));
    fix_3_ns = static_cast<uint8_t>(data_1000.at(0xe3));
    fix_4_ns = static_cast<uint8_t>(data_1000.at(0xe4));
    fix_5_ns = static_cast<uint8_t>(data_1000.at(0xe5));
    fix_6_ns = static_cast<uint8_t>(data_1000.at(0xe6));
    fix_7_ns = static_cast<uint8_t>(data_1000.at(0xe7));
    fix_8_ns = static_cast<uint8_t>(data_1000.at(0xe8));

    fix_2_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xe9)),
        static_cast<double>(data_1000.at(0xf0)) + (static_cast<double>(data_1000.at(0xf7)) / 100)
    );
    fix_3_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xea)),
        static_cast<double>(data_1000.at(0xf1)) + (static_cast<double>(data_1000.at(0xf8)) / 100)
    );
    fix_4_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xeb)),
        static_cast<double>(data_1000.at(0xf2)) + (static_cast<double>(data_1000.at(0xf9)) / 100)
    );
    fix_5_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xec)),
        static_cast<double>(data_1000.at(0xf3)) + (static_cast<double>(data_1000.at(0xfa)) / 100)
    );
    fix_6_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xed)),
        static_cast<double>(data_1000.at(0xf4)) + (static_cast<double>(data_1000.at(0xfb)) / 100)
    );
    fix_7_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xee)),
        static_cast<double>(data_1000.at(0xf5)) + (static_cast<double>(data_1000.at(0xfc)) / 100)
    );
    fix_8_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xef)),
        static_cast<double>(data_1000.at(0xf6)) + (static_cast<double>(data_1000.at(0xfd)) / 100)
    );

    fix_2_ew = static_cast<uint8_t>(data_1000.at(0xfe));
    fix_3_ew = static_cast<uint8_t>(data_1000.at(0xff));
    fix_4_ew = static_cast<uint8_t>(data_1000.at(0x100));
    fix_5_ew = static_cast<uint8_t>(data_1000.at(0x101));
    fix_6_ew = static_cast<uint8_t>(data_1000.at(0x102));
    fix_7_ew = static_cast<uint8_t>(data_1000.at(0x103));
    fix_8_ew = static_cast<uint8_t>(data_1000.at(0x104));

    to_call = QString(data_1000.mid(0x16, 6));
    to_call_ssid = static_cast<uint8_t>(data_1000.at(0x1c));
    your_call = QString(data_1000.mid(0x1d, 6));
    your_call_ssid = static_cast<uint8_t>(data_1000.at(0x23));
    digipeater_path = QString(data_1000.mid(0x24, 0x15)) + QString(data_1000.mid(0x83, 0x23));


    aprs_symbol = QString(data_1000.mid(0x39, 1));
    map_icon = QString(data_1000.mid(0x3a, 1));
    tx_power = static_cast<uint8_t>(data_1000.at(0x3b));
    prewave_time = static_cast<uint8_t>(data_1000.at(0x3c));
    
    roaming_support = static_cast<uint8_t>(data_1000.at(0x78));
    altitude = Int::fromBytes(data_1000.mid(0xa6, 2));
    analog_tx_mode = static_cast<uint8_t>(data_1000.at(0xaa));
    pass_all = static_cast<uint8_t>(data_1000.at(0xab));
    tx_freq_2 = data_1000.mid(0xac, 0x4).toHex().toInt();
    tx_freq_3 = data_1000.mid(0xb0, 0x4).toHex().toInt();
    tx_freq_4 = data_1000.mid(0xb4, 0x4).toHex().toInt();
    tx_freq_5 = data_1000.mid(0xb8, 0x4).toHex().toInt();
    tx_freq_6 = data_1000.mid(0xbc, 0x4).toHex().toInt();
    tx_freq_7 = data_1000.mid(0xc0, 0x4).toHex().toInt();
    tx_freq_8 = data_1000.mid(0xc4, 0x4).toHex().toInt();

    repeater_activation_delay = static_cast<uint8_t>(data_1000.at(0x81));
    dis_time = static_cast<uint8_t>(data_1000.at(0x82));
    sending_text = QString(data_1000.mid(0x200, 0x3c));

    uint8_t filters_1 = static_cast<uint8_t>(data_1000.at(0xa8));
    uint8_t filters_2 = static_cast<uint8_t>(data_1000.at(0xa9));

    filter_position = Bit::test(filters_1, 0);
    filter_mic_e = Bit::test(filters_1, 1);
    filter_object = Bit::test(filters_1, 2);
    filter_item = Bit::test(filters_1, 3);
    filter_message = Bit::test(filters_1, 4);
    filter_wx_report = Bit::test(filters_1, 5);
    filter_nmea_report = Bit::test(filters_1, 6);
    filter_status_report = Bit::test(filters_1, 7);
    filter_other = Bit::test(filters_2, 0);

    for(AprsReceiveFilter *f : receive_filters){
        f->decode(data_1800.mid(f->id * 8, 8));
    }

    digital_report_channel_1 = Int::fromBytes(data_1000.mid(0x40, 2));
    digital_report_channel_2 = Int::fromBytes(data_1000.mid(0x42, 2));
    digital_report_channel_3 = Int::fromBytes(data_1000.mid(0x44, 2));
    digital_report_channel_4 = Int::fromBytes(data_1000.mid(0x46, 2));
    digital_report_channel_5 = Int::fromBytes(data_1000.mid(0x48, 2));
    digital_report_channel_6 = Int::fromBytes(data_1000.mid(0x4a, 2));
    digital_report_channel_7 = Int::fromBytes(data_1000.mid(0x4c, 2));
    digital_report_channel_8 = Int::fromBytes(data_1000.mid(0x4e, 2));

    digital_report_tg_1 = data_1000.mid(0x50, 4).toHex().toInt();
    digital_report_tg_2 = data_1000.mid(0x54, 4).toHex().toInt();
    digital_report_tg_3 = data_1000.mid(0x58, 4).toHex().toInt();
    digital_report_tg_4 = data_1000.mid(0x5c, 4).toHex().toInt();
    digital_report_tg_5 = data_1000.mid(0x60, 4).toHex().toInt();
    digital_report_tg_6 = data_1000.mid(0x64, 4).toHex().toInt();
    digital_report_tg_7 = data_1000.mid(0x68, 4).toHex().toInt();
    digital_report_tg_8 = data_1000.mid(0x6c, 4).toHex().toInt();

    digital_report_call_type_1 = data_1000.at(0x70);
    digital_report_call_type_2 = data_1000.at(0x71);
    digital_report_call_type_3 = data_1000.at(0x72);
    digital_report_call_type_4 = data_1000.at(0x73);
    digital_report_call_type_5 = data_1000.at(0x74);
    digital_report_call_type_6 = data_1000.at(0x75);
    digital_report_call_type_7 = data_1000.at(0x76);
    digital_report_call_type_8 = data_1000.at(0x77);

    digital_report_slot_1 = data_1000.at(0x79);
    digital_report_slot_2 = data_1000.at(0x7a);
    digital_report_slot_3 = data_1000.at(0x7b);
    digital_report_slot_4 = data_1000.at(0x7c);
    digital_report_slot_5 = data_1000.at(0x7d);
    digital_report_slot_6 = data_1000.at(0x7e);
    digital_report_slot_7 = data_1000.at(0x7f);
    digital_report_slot_8 = data_1000.at(0x80);

    // name.remove(QChar('\0'));
    to_call.remove(QChar('\0'));
    your_call.remove(QChar('\0'));
    digipeater_path.remove(QChar('\0'));
    sending_text.remove(QChar('\0'));
}
void Anytone::AprsSettings::encode_D878UVII(QByteArray &data_2501000, QByteArray &data_2501800){
    data_2501000.replace(0x1, 4, 
        QByteArray::fromHex(QString::number(tx_freq_1).rightJustified(8, '0').toUtf8())
    );
    data_2501000[0x5] = tx_delay;
    data_2501000[0x6] = send_subtone;
    data_2501000[0x7] = ctcss;
    data_2501000.replace(0x8, 4, 
        Int::toBytes(dcs, 4)
    );
    data_2501000[0xa] = manual_tx_interval;
    data_2501000[0xb] = auto_tx_interval;
    data_2501000[0xc] = tx_tone;
    data_2501000[0xd] = fixed_location_beacon;

    std::tuple<uint8_t, uint8_t, uint8_t> fix1_lat_d = decMinToDegree(fix_1_lat);
    data_2501000[0xe] = std::get<0>(fix1_lat_d);
    data_2501000[0xf] = std::get<1>(fix1_lat_d);
    data_2501000[0x10] = std::get<2>(fix1_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix1_lng_d = decMinToDegree(fix_1_lng);
    data_2501000[0x12] = std::get<0>(fix1_lng_d);
    data_2501000[0x13] = std::get<1>(fix1_lng_d);
    data_2501000[0x14] = std::get<2>(fix1_lng_d);

    data_2501000[0x11] = fix_1_ns;
    data_2501000[0x15] = fix_1_ew;

    std::tuple<uint8_t, uint8_t, uint8_t> fix2_lat_d = decMinToDegree(fix_2_lat);
    data_2501000[0xcd] = std::get<0>(fix2_lat_d);
    data_2501000[0xd4] = std::get<1>(fix2_lat_d);
    data_2501000[0xdb] = std::get<2>(fix2_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix3_lat_d = decMinToDegree(fix_3_lat);
    data_2501000[0xce] = std::get<0>(fix3_lat_d);
    data_2501000[0xd5] = std::get<1>(fix3_lat_d);
    data_2501000[0xdc] = std::get<2>(fix3_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix4_lat_d = decMinToDegree(fix_4_lat);
    data_2501000[0xcf] = std::get<0>(fix4_lat_d);
    data_2501000[0xd6] = std::get<1>(fix4_lat_d);
    data_2501000[0xdd] = std::get<2>(fix4_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix5_lat_d = decMinToDegree(fix_5_lat);
    data_2501000[0xd0] = std::get<0>(fix5_lat_d);
    data_2501000[0xd7] = std::get<1>(fix5_lat_d);
    data_2501000[0xde] = std::get<2>(fix5_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix6_lat_d = decMinToDegree(fix_6_lat);
    data_2501000[0xd1] = std::get<0>(fix6_lat_d);
    data_2501000[0xd8] = std::get<1>(fix6_lat_d);
    data_2501000[0xdf] = std::get<2>(fix6_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix7_lat_d = decMinToDegree(fix_7_lat);
    data_2501000[0xd2] = std::get<0>(fix7_lat_d);
    data_2501000[0xd9] = std::get<1>(fix7_lat_d);
    data_2501000[0xe0] = std::get<2>(fix7_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix8_lat_d = decMinToDegree(fix_8_lat);
    data_2501000[0xd3] = std::get<0>(fix8_lat_d);
    data_2501000[0xda] = std::get<1>(fix8_lat_d);
    data_2501000[0xe1] = std::get<2>(fix8_lat_d);

    data_2501000[0xe2] = fix_2_ns;
    data_2501000[0xe3] = fix_3_ns;
    data_2501000[0xe4] = fix_4_ns;
    data_2501000[0xe5] = fix_5_ns;
    data_2501000[0xe6] = fix_6_ns;
    data_2501000[0xe7] = fix_7_ns;
    data_2501000[0xe8] = fix_8_ns;

    std::tuple<uint8_t, uint8_t, uint8_t> fix2_lng_d = decMinToDegree(fix_2_lng);
    data_2501000[0xe9] = std::get<0>(fix2_lng_d);
    data_2501000[0xf0] = std::get<1>(fix2_lng_d);
    data_2501000[0xf7] = std::get<2>(fix2_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix3_lng_d = decMinToDegree(fix_3_lng);
    data_2501000[0xea] = std::get<0>(fix3_lng_d);
    data_2501000[0xf1] = std::get<1>(fix3_lng_d);
    data_2501000[0xf8] = std::get<2>(fix3_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix4_lng_d = decMinToDegree(fix_4_lng);
    data_2501000[0xeb] = std::get<0>(fix4_lng_d);
    data_2501000[0xf2] = std::get<1>(fix4_lng_d);
    data_2501000[0xf9] = std::get<2>(fix4_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix5_lng_d = decMinToDegree(fix_5_lng);
    data_2501000[0xec] = std::get<0>(fix5_lng_d);
    data_2501000[0xf3] = std::get<1>(fix5_lng_d);
    data_2501000[0xfa] = std::get<2>(fix5_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix6_lng_d = decMinToDegree(fix_6_lng);
    data_2501000[0xed] = std::get<0>(fix6_lng_d);
    data_2501000[0xf4] = std::get<1>(fix6_lng_d);
    data_2501000[0xfb] = std::get<2>(fix6_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix7_lng_d = decMinToDegree(fix_7_lng);
    data_2501000[0xee] = std::get<0>(fix7_lng_d);
    data_2501000[0xf5] = std::get<1>(fix7_lng_d);
    data_2501000[0xfc] = std::get<2>(fix7_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix8_lng_d = decMinToDegree(fix_8_lng);
    data_2501000[0xef] = std::get<0>(fix8_lng_d);
    data_2501000[0xf6] = std::get<1>(fix8_lng_d);
    data_2501000[0xfd] = std::get<2>(fix8_lng_d);

    data_2501000[0xfe] = fix_2_ew;
    data_2501000[0xff] = fix_3_ew;
    data_2501000[0x100] = fix_4_ew;
    data_2501000[0x101] = fix_5_ew;
    data_2501000[0x102] = fix_6_ew;
    data_2501000[0x103] = fix_7_ew;
    data_2501000[0x104] = fix_8_ew;

    data_2501000.replace(0x16, 6, 
        to_call.toUtf8().leftJustified(6, '\0')
    );
    data_2501000[0x1c] = to_call_ssid;
    data_2501000.replace(0x1d, 6, 
        your_call.toUtf8().leftJustified(6, '\0')
    );
    data_2501000[0x23] = your_call_ssid;

    QByteArray digitpeater_path_data = digipeater_path.toUtf8().leftJustified(0x38, '\0');
    data_2501000.replace(0x24, 0x15, 
        digitpeater_path_data.mid(0, 0x15)
    );
    data_2501000.replace(0x83, 0x23, 
        digitpeater_path_data.mid(0x15, 0x23)
    );

    data_2501000[0x39] = aprs_symbol.at(0).toLatin1();
    data_2501000[0x3a] = map_icon.at(0).toLatin1();
    data_2501000[0x3b] = tx_power;
    data_2501000[0x3c] = prewave_time;
    data_2501000[0x78] = roaming_support;
    data_2501000.replace(0xa6, 2, 
        Int::toBytes(altitude, 2)
    );
    data_2501000[0xaa] = analog_tx_mode;
    data_2501000[0xab] = pass_all;
    data_2501000.replace(0xac, 4, 
        QByteArray::fromHex(QString::number(tx_freq_2).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0xb0, 4, 
        QByteArray::fromHex(QString::number(tx_freq_3).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0xb4, 4, 
        QByteArray::fromHex(QString::number(tx_freq_4).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0xb8, 4, 
        QByteArray::fromHex(QString::number(tx_freq_5).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0xbc, 4, 
        QByteArray::fromHex(QString::number(tx_freq_6).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0xc0, 4, 
        QByteArray::fromHex(QString::number(tx_freq_7).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0xc4, 4, 
        QByteArray::fromHex(QString::number(tx_freq_8).rightJustified(8, '0').toUtf8())
    );

    data_2501000[0x81] = repeater_activation_delay;
    data_2501000[0x82] = dis_time;
    data_2501000.replace(0x200, 0x3c,
        sending_text.toUtf8().leftJustified(0x3c, '\0')
    );

    uint8_t filters_1 = 0;
    uint8_t filters_2 = 0;            

    if(filter_position) Bit::set(&filters_1, 0);
    if(filter_mic_e) Bit::set(&filters_1, 1);
    if(filter_object) Bit::set(&filters_1, 2);
    if(filter_item) Bit::set(&filters_1, 3);
    if(filter_message) Bit::set(&filters_1, 4);
    if(filter_wx_report) Bit::set(&filters_1, 5);
    if(filter_nmea_report) Bit::set(&filters_1, 6);
    if(filter_status_report) Bit::set(&filters_1, 7);
    if(filter_other) Bit::set(&filters_2, 0);

    data_2501000[0xa8] = filters_1;
    data_2501000[0xa9] = filters_2;

    data_2501000.replace(0x40, 2, Int::toBytes(digital_report_channel_1, 2));
    data_2501000.replace(0x42, 2, Int::toBytes(digital_report_channel_2, 2));
    data_2501000.replace(0x44, 2, Int::toBytes(digital_report_channel_3, 2));
    data_2501000.replace(0x46, 2, Int::toBytes(digital_report_channel_4, 2));
    data_2501000.replace(0x48, 2, Int::toBytes(digital_report_channel_5, 2));
    data_2501000.replace(0x4a, 2, Int::toBytes(digital_report_channel_6, 2));
    data_2501000.replace(0x4c, 2, Int::toBytes(digital_report_channel_7, 2));
    data_2501000.replace(0x4e, 2, Int::toBytes(digital_report_channel_8, 2));

    data_2501000.replace(0x50, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_1).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x54, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_2).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x58, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_3).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x5c, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_4).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x60, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_5).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x64, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_6).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x68, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_7).rightJustified(8, '0').toUtf8())
    );
    data_2501000.replace(0x6c, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_8).rightJustified(8, '0').toUtf8())
    );

    data_2501000[0x70] = digital_report_call_type_1;
    data_2501000[0x71] = digital_report_call_type_2;
    data_2501000[0x72] = digital_report_call_type_3;
    data_2501000[0x73] = digital_report_call_type_4;
    data_2501000[0x74] = digital_report_call_type_5;
    data_2501000[0x75] = digital_report_call_type_6;
    data_2501000[0x76] = digital_report_call_type_7;
    data_2501000[0x77] = digital_report_call_type_8;

    data_2501000[0x79] = digital_report_slot_1;
    data_2501000[0x7a] = digital_report_slot_2;
    data_2501000[0x7b] = digital_report_slot_3;
    data_2501000[0x7c] = digital_report_slot_4;
    data_2501000[0x7d] = digital_report_slot_5;
    data_2501000[0x7e] = digital_report_slot_6;
    data_2501000[0x7f] = digital_report_slot_7;
    data_2501000[0x80] = digital_report_slot_8;


    data_2501000[0x3f] = 0xff; // unknown

    for(AprsReceiveFilter *f : receive_filters){
        data_2501800.replace(f->id * 8, 8, f->encode());
    }
}


void Anytone::AprsSettings::decode_D890UV(QByteArray data_1000, QByteArray data_1300){
    tx_freq_1 = data_1000.mid(0x1, 0x4).toHex().toInt();
    tx_delay = static_cast<uint8_t>(data_1000.at(0x5));
    send_subtone = static_cast<uint8_t>(data_1000.at(0x6));
    ctcss = static_cast<uint8_t>(data_1000.at(0x7));
    dcs = Int::fromBytes(data_1000.mid(0x8,4));
    manual_tx_interval = static_cast<uint8_t>(data_1000.at(0xa));
    auto_tx_interval = static_cast<uint8_t>(data_1000.at(0xb));
    tx_tone = static_cast<uint8_t>(data_1000.at(0xc));
    fixed_location_beacon = static_cast<uint8_t>(data_1000.at(0xd));

    fix_1_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xe)),
        static_cast<double>(data_1000.at(0xf)) + (static_cast<double>(data_1000.at(0x10)) / 100)
    );

    fix_1_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0x12)),
        static_cast<double>(data_1000.at(0x13)) + (static_cast<double>(data_1000.at(0x14)) / 100)
    );

    fix_1_ns = static_cast<uint8_t>(data_1000.at(0x11));
    fix_1_ew = static_cast<uint8_t>(data_1000.at(0x15));

    fix_2_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xcd)),
        static_cast<double>(data_1000.at(0xd4)) + (static_cast<double>(data_1000.at(0xdb)) / 100)
    );
    fix_3_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xce)),
        static_cast<double>(data_1000.at(0xd5)) + (static_cast<double>(data_1000.at(0xdc)) / 100)
    );
    fix_4_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xcf)),
        static_cast<double>(data_1000.at(0xd6)) + (static_cast<double>(data_1000.at(0xdd)) / 100)
    );
    fix_5_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd0)),
        static_cast<double>(data_1000.at(0xd7)) + (static_cast<double>(data_1000.at(0xde)) / 100)
    );
    fix_6_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd1)),
        static_cast<double>(data_1000.at(0xd8)) + (static_cast<double>(data_1000.at(0xdf)) / 100)
    );
    fix_7_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd2)),
        static_cast<double>(data_1000.at(0xd9)) + (static_cast<double>(data_1000.at(0xe0)) / 100)
    );
    fix_8_lat = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xd3)),
        static_cast<double>(data_1000.at(0xda)) + (static_cast<double>(data_1000.at(0xe1)) / 100)
    );

    fix_2_ns = static_cast<uint8_t>(data_1000.at(0xe2));
    fix_3_ns = static_cast<uint8_t>(data_1000.at(0xe3));
    fix_4_ns = static_cast<uint8_t>(data_1000.at(0xe4));
    fix_5_ns = static_cast<uint8_t>(data_1000.at(0xe5));
    fix_6_ns = static_cast<uint8_t>(data_1000.at(0xe6));
    fix_7_ns = static_cast<uint8_t>(data_1000.at(0xe7));
    fix_8_ns = static_cast<uint8_t>(data_1000.at(0xe8));

    fix_2_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xe9)),
        static_cast<double>(data_1000.at(0xf0)) + (static_cast<double>(data_1000.at(0xf7)) / 100)
    );
    fix_3_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xea)),
        static_cast<double>(data_1000.at(0xf1)) + (static_cast<double>(data_1000.at(0xf8)) / 100)
    );
    fix_4_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xeb)),
        static_cast<double>(data_1000.at(0xf2)) + (static_cast<double>(data_1000.at(0xf9)) / 100)
    );
    fix_5_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xec)),
        static_cast<double>(data_1000.at(0xf3)) + (static_cast<double>(data_1000.at(0xfa)) / 100)
    );
    fix_6_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xed)),
        static_cast<double>(data_1000.at(0xf4)) + (static_cast<double>(data_1000.at(0xfb)) / 100)
    );
    fix_7_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xee)),
        static_cast<double>(data_1000.at(0xf5)) + (static_cast<double>(data_1000.at(0xfc)) / 100)
    );
    fix_8_lng = AprsSettings::degMinToDecimal(
        static_cast<uint8_t>(data_1000.at(0xef)),
        static_cast<double>(data_1000.at(0xf6)) + (static_cast<double>(data_1000.at(0xfd)) / 100)
    );

    fix_2_ew = static_cast<uint8_t>(data_1000.at(0xfe));
    fix_3_ew = static_cast<uint8_t>(data_1000.at(0xff));
    fix_4_ew = static_cast<uint8_t>(data_1000.at(0x100));
    fix_5_ew = static_cast<uint8_t>(data_1000.at(0x101));
    fix_6_ew = static_cast<uint8_t>(data_1000.at(0x102));
    fix_7_ew = static_cast<uint8_t>(data_1000.at(0x103));
    fix_8_ew = static_cast<uint8_t>(data_1000.at(0x104));

    to_call = QString(data_1000.mid(0x16, 6));
    to_call_ssid = static_cast<uint8_t>(data_1000.at(0x1c));
    your_call = QString(data_1000.mid(0x1d, 6));
    your_call_ssid = static_cast<uint8_t>(data_1000.at(0x23));
    digipeater_path = QString(data_1000.mid(0x24, 0x15)) + QString(data_1000.mid(0x83, 0x23));


    aprs_symbol = QString(data_1000.mid(0x39, 1));
    map_icon = QString(data_1000.mid(0x3a, 1));
    tx_power = static_cast<uint8_t>(data_1000.at(0x3b));
    prewave_time = static_cast<uint8_t>(data_1000.at(0x3c));
    
    roaming_support = static_cast<uint8_t>(data_1000.at(0x78));
    altitude = Int::fromBytes(data_1000.mid(0xa6, 2));
    analog_tx_mode = static_cast<uint8_t>(data_1000.at(0xaa));
    pass_all = static_cast<uint8_t>(data_1000.at(0xab));
    tx_freq_2 = data_1000.mid(0xac, 0x4).toHex().toInt();
    tx_freq_3 = data_1000.mid(0xb0, 0x4).toHex().toInt();
    tx_freq_4 = data_1000.mid(0xb4, 0x4).toHex().toInt();
    tx_freq_5 = data_1000.mid(0xb8, 0x4).toHex().toInt();
    tx_freq_6 = data_1000.mid(0xbc, 0x4).toHex().toInt();
    tx_freq_7 = data_1000.mid(0xc0, 0x4).toHex().toInt();
    tx_freq_8 = data_1000.mid(0xc4, 0x4).toHex().toInt();

    repeater_activation_delay = static_cast<uint8_t>(data_1000.at(0x81));
    dis_time = static_cast<uint8_t>(data_1000.at(0x82));
    sending_text = QString(data_1000.mid(0x200, 0x60));

    uint8_t filters_1 = static_cast<uint8_t>(data_1000.at(0xa8));
    uint8_t filters_2 = static_cast<uint8_t>(data_1000.at(0xa9));

    filter_position = Bit::test(filters_1, 0);
    filter_mic_e = Bit::test(filters_1, 1);
    filter_object = Bit::test(filters_1, 2);
    filter_item = Bit::test(filters_1, 3);
    filter_message = Bit::test(filters_1, 4);
    filter_wx_report = Bit::test(filters_1, 5);
    filter_nmea_report = Bit::test(filters_1, 6);
    filter_status_report = Bit::test(filters_1, 7);
    filter_other = Bit::test(filters_2, 0);

    for(AprsReceiveFilter *f : receive_filters){
        f->decode(data_1300.mid(f->id * 8, 8));
    }

    digital_report_channel_1 = Int::fromBytes(data_1000.mid(0x40, 2));
    digital_report_channel_2 = Int::fromBytes(data_1000.mid(0x42, 2));
    digital_report_channel_3 = Int::fromBytes(data_1000.mid(0x44, 2));
    digital_report_channel_4 = Int::fromBytes(data_1000.mid(0x46, 2));
    digital_report_channel_5 = Int::fromBytes(data_1000.mid(0x48, 2));
    digital_report_channel_6 = Int::fromBytes(data_1000.mid(0x4a, 2));
    digital_report_channel_7 = Int::fromBytes(data_1000.mid(0x4c, 2));
    digital_report_channel_8 = Int::fromBytes(data_1000.mid(0x4e, 2));

    digital_report_tg_1 = data_1000.mid(0x50, 4).toHex().toInt();
    digital_report_tg_2 = data_1000.mid(0x54, 4).toHex().toInt();
    digital_report_tg_3 = data_1000.mid(0x58, 4).toHex().toInt();
    digital_report_tg_4 = data_1000.mid(0x5c, 4).toHex().toInt();
    digital_report_tg_5 = data_1000.mid(0x60, 4).toHex().toInt();
    digital_report_tg_6 = data_1000.mid(0x64, 4).toHex().toInt();
    digital_report_tg_7 = data_1000.mid(0x68, 4).toHex().toInt();
    digital_report_tg_8 = data_1000.mid(0x6c, 4).toHex().toInt();

    digital_report_call_type_1 = data_1000.at(0x70);
    digital_report_call_type_2 = data_1000.at(0x71);
    digital_report_call_type_3 = data_1000.at(0x72);
    digital_report_call_type_4 = data_1000.at(0x73);
    digital_report_call_type_5 = data_1000.at(0x74);
    digital_report_call_type_6 = data_1000.at(0x75);
    digital_report_call_type_7 = data_1000.at(0x76);
    digital_report_call_type_8 = data_1000.at(0x77);

    digital_report_slot_1 = data_1000.at(0x79);
    digital_report_slot_2 = data_1000.at(0x7a);
    digital_report_slot_3 = data_1000.at(0x7b);
    digital_report_slot_4 = data_1000.at(0x7c);
    digital_report_slot_5 = data_1000.at(0x7d);
    digital_report_slot_6 = data_1000.at(0x7e);
    digital_report_slot_7 = data_1000.at(0x7f);
    digital_report_slot_8 = data_1000.at(0x80);

    // name.remove(QChar('\0'));
    to_call.remove(QChar('\0'));
    your_call.remove(QChar('\0'));
    digipeater_path.remove(QChar('\0'));
    sending_text.remove(QChar('\0'));
}
void Anytone::AprsSettings::encode_D890UV(QByteArray &data_3501000, QByteArray &data_3501300){
    data_3501000.replace(0x1, 4, 
        QByteArray::fromHex(QString::number(tx_freq_1).rightJustified(8, '0').toUtf8())
    );
    data_3501000[0x5] = tx_delay;
    data_3501000[0x6] = send_subtone;
    data_3501000[0x7] = ctcss;
    data_3501000.replace(0x8, 4, 
        Int::toBytes(dcs, 4)
    );
    data_3501000[0xa] = manual_tx_interval;
    data_3501000[0xb] = auto_tx_interval;
    data_3501000[0xc] = tx_tone;
    data_3501000[0xd] = fixed_location_beacon;

    std::tuple<uint8_t, uint8_t, uint8_t> fix1_lat_d = decMinToDegree(fix_1_lat);
    data_3501000[0xe] = std::get<0>(fix1_lat_d);
    data_3501000[0xf] = std::get<1>(fix1_lat_d);
    data_3501000[0x10] = std::get<2>(fix1_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix1_lng_d = decMinToDegree(fix_1_lng);
    data_3501000[0x12] = std::get<0>(fix1_lng_d);
    data_3501000[0x13] = std::get<1>(fix1_lng_d);
    data_3501000[0x14] = std::get<2>(fix1_lng_d);

    data_3501000[0x11] = fix_1_ns;
    data_3501000[0x15] = fix_1_ew;

    std::tuple<uint8_t, uint8_t, uint8_t> fix2_lat_d = decMinToDegree(fix_2_lat);
    data_3501000[0xcd] = std::get<0>(fix2_lat_d);
    data_3501000[0xd4] = std::get<1>(fix2_lat_d);
    data_3501000[0xdb] = std::get<2>(fix2_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix3_lat_d = decMinToDegree(fix_3_lat);
    data_3501000[0xce] = std::get<0>(fix3_lat_d);
    data_3501000[0xd5] = std::get<1>(fix3_lat_d);
    data_3501000[0xdc] = std::get<2>(fix3_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix4_lat_d = decMinToDegree(fix_4_lat);
    data_3501000[0xcf] = std::get<0>(fix4_lat_d);
    data_3501000[0xd6] = std::get<1>(fix4_lat_d);
    data_3501000[0xdd] = std::get<2>(fix4_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix5_lat_d = decMinToDegree(fix_5_lat);
    data_3501000[0xd0] = std::get<0>(fix5_lat_d);
    data_3501000[0xd7] = std::get<1>(fix5_lat_d);
    data_3501000[0xde] = std::get<2>(fix5_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix6_lat_d = decMinToDegree(fix_6_lat);
    data_3501000[0xd1] = std::get<0>(fix6_lat_d);
    data_3501000[0xd8] = std::get<1>(fix6_lat_d);
    data_3501000[0xdf] = std::get<2>(fix6_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix7_lat_d = decMinToDegree(fix_7_lat);
    data_3501000[0xd2] = std::get<0>(fix7_lat_d);
    data_3501000[0xd9] = std::get<1>(fix7_lat_d);
    data_3501000[0xe0] = std::get<2>(fix7_lat_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix8_lat_d = decMinToDegree(fix_8_lat);
    data_3501000[0xd3] = std::get<0>(fix8_lat_d);
    data_3501000[0xda] = std::get<1>(fix8_lat_d);
    data_3501000[0xe1] = std::get<2>(fix8_lat_d);

    data_3501000[0xe2] = fix_2_ns;
    data_3501000[0xe3] = fix_3_ns;
    data_3501000[0xe4] = fix_4_ns;
    data_3501000[0xe5] = fix_5_ns;
    data_3501000[0xe6] = fix_6_ns;
    data_3501000[0xe7] = fix_7_ns;
    data_3501000[0xe8] = fix_8_ns;

    std::tuple<uint8_t, uint8_t, uint8_t> fix2_lng_d = decMinToDegree(fix_2_lng);
    data_3501000[0xe9] = std::get<0>(fix2_lng_d);
    data_3501000[0xf0] = std::get<1>(fix2_lng_d);
    data_3501000[0xf7] = std::get<2>(fix2_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix3_lng_d = decMinToDegree(fix_3_lng);
    data_3501000[0xea] = std::get<0>(fix3_lng_d);
    data_3501000[0xf1] = std::get<1>(fix3_lng_d);
    data_3501000[0xf8] = std::get<2>(fix3_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix4_lng_d = decMinToDegree(fix_4_lng);
    data_3501000[0xeb] = std::get<0>(fix4_lng_d);
    data_3501000[0xf2] = std::get<1>(fix4_lng_d);
    data_3501000[0xf9] = std::get<2>(fix4_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix5_lng_d = decMinToDegree(fix_5_lng);
    data_3501000[0xec] = std::get<0>(fix5_lng_d);
    data_3501000[0xf3] = std::get<1>(fix5_lng_d);
    data_3501000[0xfa] = std::get<2>(fix5_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix6_lng_d = decMinToDegree(fix_6_lng);
    data_3501000[0xed] = std::get<0>(fix6_lng_d);
    data_3501000[0xf4] = std::get<1>(fix6_lng_d);
    data_3501000[0xfb] = std::get<2>(fix6_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix7_lng_d = decMinToDegree(fix_7_lng);
    data_3501000[0xee] = std::get<0>(fix7_lng_d);
    data_3501000[0xf5] = std::get<1>(fix7_lng_d);
    data_3501000[0xfc] = std::get<2>(fix7_lng_d);

    std::tuple<uint8_t, uint8_t, uint8_t> fix8_lng_d = decMinToDegree(fix_8_lng);
    data_3501000[0xef] = std::get<0>(fix8_lng_d);
    data_3501000[0xf6] = std::get<1>(fix8_lng_d);
    data_3501000[0xfd] = std::get<2>(fix8_lng_d);

    data_3501000[0xfe] = fix_2_ew;
    data_3501000[0xff] = fix_3_ew;
    data_3501000[0x100] = fix_4_ew;
    data_3501000[0x101] = fix_5_ew;
    data_3501000[0x102] = fix_6_ew;
    data_3501000[0x103] = fix_7_ew;
    data_3501000[0x104] = fix_8_ew;

    data_3501000.replace(0x16, 6, 
        to_call.toUtf8().leftJustified(6, '\0')
    );
    data_3501000[0x1c] = to_call_ssid;
    data_3501000.replace(0x1d, 6, 
        your_call.toUtf8().leftJustified(6, '\0')
    );
    data_3501000[0x23] = your_call_ssid;

    QByteArray digitpeater_path_data = digipeater_path.toUtf8().leftJustified(0x38, '\0');
    data_3501000.replace(0x24, 0x15, 
        digitpeater_path_data.mid(0, 0x15)
    );
    data_3501000.replace(0x83, 0x23, 
        digitpeater_path_data.mid(0x15, 0x23)
    );

    data_3501000[0x39] = aprs_symbol.at(0).toLatin1();
    data_3501000[0x3a] = map_icon.at(0).toLatin1();
    data_3501000[0x3b] = tx_power;
    data_3501000[0x3c] = prewave_time;
    data_3501000[0x78] = roaming_support;
    data_3501000.replace(0xa6, 2, 
        Int::toBytes(altitude, 2)
    );
    data_3501000[0xaa] = analog_tx_mode;
    data_3501000[0xab] = pass_all;
    data_3501000.replace(0xac, 4, 
        QByteArray::fromHex(QString::number(tx_freq_2).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0xb0, 4, 
        QByteArray::fromHex(QString::number(tx_freq_3).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0xb4, 4, 
        QByteArray::fromHex(QString::number(tx_freq_4).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0xb8, 4, 
        QByteArray::fromHex(QString::number(tx_freq_5).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0xbc, 4, 
        QByteArray::fromHex(QString::number(tx_freq_6).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0xc0, 4, 
        QByteArray::fromHex(QString::number(tx_freq_7).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0xc4, 4, 
        QByteArray::fromHex(QString::number(tx_freq_8).rightJustified(8, '0').toUtf8())
    );

    data_3501000[0x81] = repeater_activation_delay;
    data_3501000[0x82] = dis_time;
    data_3501000.replace(0x200, 0x60,
        Format::wideCharString(sending_text).leftJustified(0x60, '\0')
    );

    uint8_t filters_1 = 0;
    uint8_t filters_2 = 0;            

    if(filter_position) Bit::set(&filters_1, 0);
    if(filter_mic_e) Bit::set(&filters_1, 1);
    if(filter_object) Bit::set(&filters_1, 2);
    if(filter_item) Bit::set(&filters_1, 3);
    if(filter_message) Bit::set(&filters_1, 4);
    if(filter_wx_report) Bit::set(&filters_1, 5);
    if(filter_nmea_report) Bit::set(&filters_1, 6);
    if(filter_status_report) Bit::set(&filters_1, 7);
    if(filter_other) Bit::set(&filters_2, 0);

    data_3501000[0xa8] = filters_1;
    data_3501000[0xa9] = filters_2;

    data_3501000.replace(0x40, 2, Int::toBytes(digital_report_channel_1, 2));
    data_3501000.replace(0x42, 2, Int::toBytes(digital_report_channel_2, 2));
    data_3501000.replace(0x44, 2, Int::toBytes(digital_report_channel_3, 2));
    data_3501000.replace(0x46, 2, Int::toBytes(digital_report_channel_4, 2));
    data_3501000.replace(0x48, 2, Int::toBytes(digital_report_channel_5, 2));
    data_3501000.replace(0x4a, 2, Int::toBytes(digital_report_channel_6, 2));
    data_3501000.replace(0x4c, 2, Int::toBytes(digital_report_channel_7, 2));
    data_3501000.replace(0x4e, 2, Int::toBytes(digital_report_channel_8, 2));

    data_3501000.replace(0x50, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_1).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x54, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_2).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x58, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_3).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x5c, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_4).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x60, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_5).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x64, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_6).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x68, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_7).rightJustified(8, '0').toUtf8())
    );
    data_3501000.replace(0x6c, 4, 
        QByteArray::fromHex(QString::number(digital_report_tg_8).rightJustified(8, '0').toUtf8())
    );

    data_3501000[0x70] = digital_report_call_type_1;
    data_3501000[0x71] = digital_report_call_type_2;
    data_3501000[0x72] = digital_report_call_type_3;
    data_3501000[0x73] = digital_report_call_type_4;
    data_3501000[0x74] = digital_report_call_type_5;
    data_3501000[0x75] = digital_report_call_type_6;
    data_3501000[0x76] = digital_report_call_type_7;
    data_3501000[0x77] = digital_report_call_type_8;

    data_3501000[0x79] = digital_report_slot_1;
    data_3501000[0x7a] = digital_report_slot_2;
    data_3501000[0x7b] = digital_report_slot_3;
    data_3501000[0x7c] = digital_report_slot_4;
    data_3501000[0x7d] = digital_report_slot_5;
    data_3501000[0x7e] = digital_report_slot_6;
    data_3501000[0x7f] = digital_report_slot_7;
    data_3501000[0x80] = digital_report_slot_8;


    data_3501000[0x3f] = 0xff; // unknown

    for(AprsReceiveFilter *f : receive_filters){
        data_3501300.replace(f->id * 8, 8, f->encode());
    }
}


void Anytone::AprsSettings::save(QXmlStreamWriter &xml){
    
    xml.writeStartElement("APRSSettings");
    xml.writeAttribute("tx_freq_1", QString::number(tx_freq_1));
    xml.writeAttribute("tx_delay", QString::number(tx_delay));
    xml.writeAttribute("send_subtone", QString::number(send_subtone));
    xml.writeAttribute("ctcss", QString::number(ctcss));
    xml.writeAttribute("dcs", QString::number(dcs));
    xml.writeAttribute("manual_tx_interval", QString::number(manual_tx_interval));
    xml.writeAttribute("auto_tx_interval", QString::number(auto_tx_interval));
    xml.writeAttribute("tx_tone", QString::number(tx_tone));
    xml.writeAttribute("fix_1_lat", QString::number(fix_1_lat));
    xml.writeAttribute("fix_1_ns", QString::number(fix_1_ns));
    xml.writeAttribute("fix_1_lng", QString::number(fix_1_lng));
    xml.writeAttribute("fix_1_ew", QString::number(fix_1_ew));
    xml.writeAttribute("to_call ", to_call);
    xml.writeAttribute("to_call_ssid", QString::number(to_call_ssid));
    xml.writeAttribute("your_call", your_call);
    xml.writeAttribute("your_call_ssid", QString::number(your_call_ssid));
    xml.writeAttribute("digipeater_path", digipeater_path);
    xml.writeAttribute("aprs_symbol", aprs_symbol);
    xml.writeAttribute("map_icon", map_icon);
    xml.writeAttribute("tx_power", QString::number(tx_power));
    xml.writeAttribute("prewave_time", QString::number(prewave_time));
    xml.writeAttribute("roaming_support", QString::number(roaming_support));
    xml.writeAttribute("repeater_activation_delay", QString::number(repeater_activation_delay));
    xml.writeAttribute("dis_time", QString::number(dis_time));
    xml.writeAttribute("altitude", QString::number(altitude));
    xml.writeAttribute("pass_all", QString::number(pass_all));
    xml.writeAttribute("sending_text ", sending_text);
    xml.writeAttribute("fixed_location_beacon", QString::number(fixed_location_beacon));
    xml.writeAttribute("analog_tx_mode", QString::number(analog_tx_mode));
    xml.writeAttribute("filter_position", QString::number(filter_position));
    xml.writeAttribute("filter_mic_e", QString::number(filter_mic_e));
    xml.writeAttribute("filter_object", QString::number(filter_object));
    xml.writeAttribute("filter_item", QString::number(filter_item));
    xml.writeAttribute("filter_message", QString::number(filter_message));
    xml.writeAttribute("filter_wx_report", QString::number(filter_wx_report));
    xml.writeAttribute("filter_nmea_report", QString::number(filter_nmea_report));
    xml.writeAttribute("filter_status_report", QString::number(filter_status_report));
    xml.writeAttribute("filter_other", QString::number(filter_other));
    xml.writeAttribute("digital_report_channel_1", QString::number(digital_report_channel_1));
    xml.writeAttribute("digital_report_channel_2", QString::number(digital_report_channel_2));
    xml.writeAttribute("digital_report_channel_3", QString::number(digital_report_channel_3));
    xml.writeAttribute("digital_report_channel_4", QString::number(digital_report_channel_4));
    xml.writeAttribute("digital_report_channel_5", QString::number(digital_report_channel_5));
    xml.writeAttribute("digital_report_channel_6", QString::number(digital_report_channel_6));
    xml.writeAttribute("digital_report_channel_7", QString::number(digital_report_channel_7));
    xml.writeAttribute("digital_report_channel_8", QString::number(digital_report_channel_8));
    xml.writeAttribute("digital_report_tg_1", QString::number(digital_report_tg_1));
    xml.writeAttribute("digital_report_tg_2", QString::number(digital_report_tg_2));
    xml.writeAttribute("digital_report_tg_3", QString::number(digital_report_tg_3));
    xml.writeAttribute("digital_report_tg_4", QString::number(digital_report_tg_4));
    xml.writeAttribute("digital_report_tg_5", QString::number(digital_report_tg_5));
    xml.writeAttribute("digital_report_tg_6", QString::number(digital_report_tg_6));
    xml.writeAttribute("digital_report_tg_7", QString::number(digital_report_tg_7));
    xml.writeAttribute("digital_report_tg_8", QString::number(digital_report_tg_8));
    xml.writeAttribute("digital_report_call_type_1", QString::number(digital_report_call_type_1));
    xml.writeAttribute("digital_report_call_type_2", QString::number(digital_report_call_type_2));
    xml.writeAttribute("digital_report_call_type_3", QString::number(digital_report_call_type_3));
    xml.writeAttribute("digital_report_call_type_4", QString::number(digital_report_call_type_4));
    xml.writeAttribute("digital_report_call_type_5", QString::number(digital_report_call_type_5));
    xml.writeAttribute("digital_report_call_type_6", QString::number(digital_report_call_type_6));
    xml.writeAttribute("digital_report_call_type_7", QString::number(digital_report_call_type_7));
    xml.writeAttribute("digital_report_call_type_8", QString::number(digital_report_call_type_8));
    xml.writeAttribute("digital_report_slot_1", QString::number(digital_report_slot_1));
    xml.writeAttribute("digital_report_slot_2", QString::number(digital_report_slot_2));
    xml.writeAttribute("digital_report_slot_3", QString::number(digital_report_slot_3));
    xml.writeAttribute("digital_report_slot_4", QString::number(digital_report_slot_4));
    xml.writeAttribute("digital_report_slot_5", QString::number(digital_report_slot_5));
    xml.writeAttribute("digital_report_slot_6", QString::number(digital_report_slot_6));
    xml.writeAttribute("digital_report_slot_7", QString::number(digital_report_slot_7));
    xml.writeAttribute("digital_report_slot_8", QString::number(digital_report_slot_8));
    xml.writeAttribute("fix_2_lat", QString::number(fix_2_lat));
    xml.writeAttribute("fix_2_lng", QString::number(fix_2_lng));
    xml.writeAttribute("fix_3_lat", QString::number(fix_3_lat));
    xml.writeAttribute("fix_3_lng", QString::number(fix_3_lng));
    xml.writeAttribute("fix_4_lat", QString::number(fix_4_lat));
    xml.writeAttribute("fix_4_lng", QString::number(fix_4_lng));
    xml.writeAttribute("fix_5_lat", QString::number(fix_5_lat));
    xml.writeAttribute("fix_5_lng", QString::number(fix_5_lng));
    xml.writeAttribute("fix_6_lat", QString::number(fix_6_lat));
    xml.writeAttribute("fix_6_lng", QString::number(fix_6_lng));
    xml.writeAttribute("fix_7_lat", QString::number(fix_7_lat));
    xml.writeAttribute("fix_7_lng", QString::number(fix_7_lng));
    xml.writeAttribute("fix_8_lat", QString::number(fix_8_lat));
    xml.writeAttribute("fix_8_lng", QString::number(fix_8_lng));
    xml.writeAttribute("fix_2_ns", QString::number(fix_2_ns));
    xml.writeAttribute("fix_2_ew", QString::number(fix_2_ew));
    xml.writeAttribute("fix_3_ns", QString::number(fix_3_ns));
    xml.writeAttribute("fix_3_ew", QString::number(fix_3_ew));
    xml.writeAttribute("fix_4_ns", QString::number(fix_4_ns));
    xml.writeAttribute("fix_4_ew", QString::number(fix_4_ew));
    xml.writeAttribute("fix_5_ns", QString::number(fix_5_ns));
    xml.writeAttribute("fix_5_ew", QString::number(fix_5_ew));
    xml.writeAttribute("fix_6_ns", QString::number(fix_6_ns));
    xml.writeAttribute("fix_6_ew", QString::number(fix_6_ew));
    xml.writeAttribute("fix_7_ns", QString::number(fix_7_ns));
    xml.writeAttribute("fix_7_ew", QString::number(fix_7_ew));
    xml.writeAttribute("fix_8_ns", QString::number(fix_8_ns));
    xml.writeAttribute("fix_8_ew", QString::number(fix_8_ew));
    xml.writeAttribute("tx_freq_2", QString::number(tx_freq_2));
    xml.writeAttribute("tx_freq_3", QString::number(tx_freq_3));
    xml.writeAttribute("tx_freq_4", QString::number(tx_freq_4));
    xml.writeAttribute("tx_freq_5", QString::number(tx_freq_5));
    xml.writeAttribute("tx_freq_6", QString::number(tx_freq_6));
    xml.writeAttribute("tx_freq_7", QString::number(tx_freq_7));
    xml.writeAttribute("tx_freq_8", QString::number(tx_freq_8));

    xml.writeStartElement("APRSFilterList");
    for(AprsReceiveFilter *filter : receive_filters){
        filter->save(xml);
    }
    xml.writeEndElement();
    
    xml.writeEndElement();
}
void Anytone::AprsSettings::load(QXmlStreamReader &xml){
    if (xml.name() == "APRSSettings"){
        QXmlStreamAttributes attributes = xml.attributes();

        if(attributes.hasAttribute("tx_freq_1"))
            tx_freq_1 = attributes.value("tx_freq_1").toInt();
        if(attributes.hasAttribute("tx_delay"))
            tx_delay = attributes.value("tx_delay").toInt();
        if(attributes.hasAttribute("send_subtone"))
            send_subtone = attributes.value("send_subtone").toInt();
        if(attributes.hasAttribute("ctcss"))
            ctcss = attributes.value("ctcss").toInt();
        if(attributes.hasAttribute("dcs"))
            dcs = attributes.value("dcs").toInt();
        if(attributes.hasAttribute("manual_tx_interval"))
            manual_tx_interval = attributes.value("manual_tx_interval").toInt();
        if(attributes.hasAttribute("auto_tx_interval"))
            auto_tx_interval = attributes.value("auto_tx_interval").toInt();
        if(attributes.hasAttribute("tx_tone"))
            tx_tone = attributes.value("tx_tone").toInt();
        if(attributes.hasAttribute("fix_1_lat"))
            fix_1_lat = attributes.value("fix_1_lat").toInt();
        if(attributes.hasAttribute("fix_1_ns"))
            fix_1_ns = attributes.value("fix_1_ns").toInt();
        if(attributes.hasAttribute("fix_1_lng"))
            fix_1_lng = attributes.value("fix_1_lng").toInt();
        if(attributes.hasAttribute("fix_1_ew"))
            fix_1_ew = attributes.value("fix_1_ew").toInt();
        if(attributes.hasAttribute("to_call "))
            to_call = attributes.value("to_call ").toString();
        if(attributes.hasAttribute("to_call_ssid"))
            to_call_ssid = attributes.value("to_call_ssid").toInt();
        if(attributes.hasAttribute("your_call"))
            your_call = attributes.value("your_call").toString();
        if(attributes.hasAttribute("your_call_ssid"))
            your_call_ssid = attributes.value("your_call_ssid").toInt();
        if(attributes.hasAttribute("digipeater_path"))
            digipeater_path = attributes.value("digipeater_path").toString();
        if(attributes.hasAttribute("aprs_symbol"))
            aprs_symbol = attributes.value("aprs_symbol").toString();
        if(attributes.hasAttribute("map_icon"))
            map_icon = attributes.value("map_icon").toString();
        if(attributes.hasAttribute("tx_power"))
            tx_power = attributes.value("tx_power").toInt();
        if(attributes.hasAttribute("prewave_time"))
            prewave_time = attributes.value("prewave_time").toInt();
        if(attributes.hasAttribute("roaming_support"))
            roaming_support = attributes.value("roaming_support").toInt();
        if(attributes.hasAttribute("repeater_activation_delay"))
            repeater_activation_delay = attributes.value("repeater_activation_delay").toInt();
        if(attributes.hasAttribute("dis_time"))
            dis_time = attributes.value("dis_time").toInt();
        if(attributes.hasAttribute("altitude"))
            altitude = attributes.value("altitude").toInt();
        if(attributes.hasAttribute("pass_all"))
            pass_all = attributes.value("pass_all").toInt();
        if(attributes.hasAttribute("sending_text "))
            sending_text = attributes.value("sending_text ").toString();
        if(attributes.hasAttribute("fixed_location_beacon"))
            fixed_location_beacon = attributes.value("fixed_location_beacon").toInt();
        if(attributes.hasAttribute("analog_tx_mode"))
            analog_tx_mode = attributes.value("analog_tx_mode").toInt();
        if(attributes.hasAttribute("filter_position"))
            filter_position = attributes.value("filter_position").toInt();
        if(attributes.hasAttribute("filter_mic_e"))
            filter_mic_e = attributes.value("filter_mic_e").toInt();
        if(attributes.hasAttribute("filter_object"))
            filter_object = attributes.value("filter_object").toInt();
        if(attributes.hasAttribute("filter_item"))
            filter_item = attributes.value("filter_item").toInt();
        if(attributes.hasAttribute("filter_message"))
            filter_message = attributes.value("filter_message").toInt();
        if(attributes.hasAttribute("filter_wx_report"))
            filter_wx_report = attributes.value("filter_wx_report").toInt();
        if(attributes.hasAttribute("filter_nmea_report"))
            filter_nmea_report = attributes.value("filter_nmea_report").toInt();
        if(attributes.hasAttribute("filter_status_report"))
            filter_status_report = attributes.value("filter_status_report").toInt();
        if(attributes.hasAttribute("filter_other"))
            filter_other = attributes.value("filter_other").toInt();
        if(attributes.hasAttribute("digital_report_channel_1"))
            digital_report_channel_1 = attributes.value("digital_report_channel_1").toInt();
        if(attributes.hasAttribute("digital_report_channel_2"))
            digital_report_channel_2 = attributes.value("digital_report_channel_2").toInt();
        if(attributes.hasAttribute("digital_report_channel_3"))
            digital_report_channel_3 = attributes.value("digital_report_channel_3").toInt();
        if(attributes.hasAttribute("digital_report_channel_4"))
            digital_report_channel_4 = attributes.value("digital_report_channel_4").toInt();
        if(attributes.hasAttribute("digital_report_channel_5"))
            digital_report_channel_5 = attributes.value("digital_report_channel_5").toInt();
        if(attributes.hasAttribute("digital_report_channel_6"))
            digital_report_channel_6 = attributes.value("digital_report_channel_6").toInt();
        if(attributes.hasAttribute("digital_report_channel_7"))
            digital_report_channel_7 = attributes.value("digital_report_channel_7").toInt();
        if(attributes.hasAttribute("digital_report_channel_8"))
            digital_report_channel_8 = attributes.value("digital_report_channel_8").toInt();
        if(attributes.hasAttribute("digital_report_tg_1"))
            digital_report_tg_1 = attributes.value("digital_report_tg_1").toInt();
        if(attributes.hasAttribute("digital_report_tg_2"))
            digital_report_tg_2 = attributes.value("digital_report_tg_2").toInt();
        if(attributes.hasAttribute("digital_report_tg_3"))
            digital_report_tg_3 = attributes.value("digital_report_tg_3").toInt();
        if(attributes.hasAttribute("digital_report_tg_4"))
            digital_report_tg_4 = attributes.value("digital_report_tg_4").toInt();
        if(attributes.hasAttribute("digital_report_tg_5"))
            digital_report_tg_5 = attributes.value("digital_report_tg_5").toInt();
        if(attributes.hasAttribute("digital_report_tg_6"))
            digital_report_tg_6 = attributes.value("digital_report_tg_6").toInt();
        if(attributes.hasAttribute("digital_report_tg_7"))
            digital_report_tg_7 = attributes.value("digital_report_tg_7").toInt();
        if(attributes.hasAttribute("digital_report_tg_8"))
            digital_report_tg_8 = attributes.value("digital_report_tg_8").toInt();
        if(attributes.hasAttribute("digital_report_call_type_1"))
            digital_report_call_type_1 = attributes.value("digital_report_call_type_1").toInt();
        if(attributes.hasAttribute("digital_report_call_type_2"))
            digital_report_call_type_2 = attributes.value("digital_report_call_type_2").toInt();
        if(attributes.hasAttribute("digital_report_call_type_3"))
            digital_report_call_type_3 = attributes.value("digital_report_call_type_3").toInt();
        if(attributes.hasAttribute("digital_report_call_type_4"))
            digital_report_call_type_4 = attributes.value("digital_report_call_type_4").toInt();
        if(attributes.hasAttribute("digital_report_call_type_5"))
            digital_report_call_type_5 = attributes.value("digital_report_call_type_5").toInt();
        if(attributes.hasAttribute("digital_report_call_type_6"))
            digital_report_call_type_6 = attributes.value("digital_report_call_type_6").toInt();
        if(attributes.hasAttribute("digital_report_call_type_7"))
            digital_report_call_type_7 = attributes.value("digital_report_call_type_7").toInt();
        if(attributes.hasAttribute("digital_report_call_type_8"))
            digital_report_call_type_8 = attributes.value("digital_report_call_type_8").toInt();
        if(attributes.hasAttribute("digital_report_slot_1"))
            digital_report_slot_1 = attributes.value("digital_report_slot_1").toInt();
        if(attributes.hasAttribute("digital_report_slot_2"))
            digital_report_slot_2 = attributes.value("digital_report_slot_2").toInt();
        if(attributes.hasAttribute("digital_report_slot_3"))
            digital_report_slot_3 = attributes.value("digital_report_slot_3").toInt();
        if(attributes.hasAttribute("digital_report_slot_4"))
            digital_report_slot_4 = attributes.value("digital_report_slot_4").toInt();
        if(attributes.hasAttribute("digital_report_slot_5"))
            digital_report_slot_5 = attributes.value("digital_report_slot_5").toInt();
        if(attributes.hasAttribute("digital_report_slot_6"))
            digital_report_slot_6 = attributes.value("digital_report_slot_6").toInt();
        if(attributes.hasAttribute("digital_report_slot_7"))
            digital_report_slot_7 = attributes.value("digital_report_slot_7").toInt();
        if(attributes.hasAttribute("digital_report_slot_8"))
            digital_report_slot_8 = attributes.value("digital_report_slot_8").toInt();
        if(attributes.hasAttribute("fix_2_lat"))
            fix_2_lat = attributes.value("fix_2_lat").toInt();
        if(attributes.hasAttribute("fix_2_lng"))
            fix_2_lng = attributes.value("fix_2_lng").toInt();
        if(attributes.hasAttribute("fix_3_lat"))
            fix_3_lat = attributes.value("fix_3_lat").toInt();
        if(attributes.hasAttribute("fix_3_lng"))
            fix_3_lng = attributes.value("fix_3_lng").toInt();
        if(attributes.hasAttribute("fix_4_lat"))
            fix_4_lat = attributes.value("fix_4_lat").toInt();
        if(attributes.hasAttribute("fix_4_lng"))
            fix_4_lng = attributes.value("fix_4_lng").toInt();
        if(attributes.hasAttribute("fix_5_lat"))
            fix_5_lat = attributes.value("fix_5_lat").toInt();
        if(attributes.hasAttribute("fix_5_lng"))
            fix_5_lng = attributes.value("fix_5_lng").toInt();
        if(attributes.hasAttribute("fix_6_lat"))
            fix_6_lat = attributes.value("fix_6_lat").toInt();
        if(attributes.hasAttribute("fix_6_lng"))
            fix_6_lng = attributes.value("fix_6_lng").toInt();
        if(attributes.hasAttribute("fix_7_lat"))
            fix_7_lat = attributes.value("fix_7_lat").toInt();
        if(attributes.hasAttribute("fix_7_lng"))
            fix_7_lng = attributes.value("fix_7_lng").toInt();
        if(attributes.hasAttribute("fix_8_lat"))
            fix_8_lat = attributes.value("fix_8_lat").toInt();
        if(attributes.hasAttribute("fix_8_lng"))
            fix_8_lng = attributes.value("fix_8_lng").toInt();
        if(attributes.hasAttribute("fix_2_ns"))
            fix_2_ns = attributes.value("fix_2_ns").toInt();
        if(attributes.hasAttribute("fix_2_ew;"))
            fix_2_ew = attributes.value("fix_2_ew").toInt();
        if(attributes.hasAttribute("fix_3_ns;"))
            fix_3_ns = attributes.value("fix_3_ns").toInt();
        if(attributes.hasAttribute("fix_3_ew;"))
            fix_3_ew = attributes.value("fix_3_ew").toInt();
        if(attributes.hasAttribute("fix_4_ns;"))
            fix_4_ns = attributes.value("fix_4_ns").toInt();
        if(attributes.hasAttribute("fix_4_ew;"))
            fix_4_ew = attributes.value("fix_4_ew").toInt();
        if(attributes.hasAttribute("fix_5_ns;"))
            fix_5_ns = attributes.value("fix_5_ns").toInt();
        if(attributes.hasAttribute("fix_5_ew;"))
            fix_5_ew = attributes.value("fix_5_ew").toInt();
        if(attributes.hasAttribute("fix_6_ns;"))
            fix_6_ns = attributes.value("fix_6_ns").toInt();
        if(attributes.hasAttribute("fix_6_ew;"))
            fix_6_ew = attributes.value("fix_6_ew").toInt();
        if(attributes.hasAttribute("fix_7_ns;"))
            fix_7_ns = attributes.value("fix_7_ns").toInt();
        if(attributes.hasAttribute("fix_7_ew;"))
            fix_7_ew = attributes.value("fix_7_ew").toInt();
        if(attributes.hasAttribute("fix_8_ns;"))
            fix_8_ns = attributes.value("fix_8_ns").toInt();
        if(attributes.hasAttribute("fix_8_ew;"))
            fix_8_ew = attributes.value("fix_8_ew").toInt();
        if(attributes.hasAttribute("tx_freq_2"))
            tx_freq_2 = attributes.value("tx_freq_2").toInt();
        if(attributes.hasAttribute("tx_freq_3"))
            tx_freq_3 = attributes.value("tx_freq_3").toInt();
        if(attributes.hasAttribute("tx_freq_4"))
            tx_freq_4 = attributes.value("tx_freq_4").toInt();
        if(attributes.hasAttribute("tx_freq_5"))
            tx_freq_5 = attributes.value("tx_freq_5").toInt();
        if(attributes.hasAttribute("tx_freq_6"))
            tx_freq_6 = attributes.value("tx_freq_6").toInt();
        if(attributes.hasAttribute("tx_freq_7"))
            tx_freq_7 = attributes.value("tx_freq_7").toInt();
        if(attributes.hasAttribute("tx_freq_8"))
            tx_freq_8 = attributes.value("tx_freq_8").toInt();


        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        while (!xml.atEnd() && !xml.hasError()) {
            if(token == QXmlStreamReader::StartElement && xml.name() == "APRSFilterList"){

            }else if(token == QXmlStreamReader::StartElement && xml.name() == "APRSFilter"){
                int idx = attributes.value("id").toInt();
                AprsReceiveFilter *filter = receive_filters.at(idx);
                filter->load(xml);
            }else if(token == QXmlStreamReader::StartElement){
                return;
            }
            token = xml.readNext();
        }
    }
}

std::tuple<uint8_t, uint8_t, uint8_t> Anytone::AprsSettings::decMinToDegree(double deg_min){
    uint8_t deg = uint8_t(abs(deg_min));
    double m = (abs(deg_min) - deg) * 60;
    
    uint8_t minutes = static_cast<uint8_t>(std::floor(m));
    uint8_t minutes_dec = static_cast<uint8_t>(
        std::round((m - minutes) * 100.0)
    );
    return std::tuple<uint8_t, uint8_t, uint8_t>(deg, minutes, minutes_dec);
}