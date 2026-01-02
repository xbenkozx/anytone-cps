#include "aprs_settings.h"
void Anytone::AprsSettings::decode(QByteArray data_1000, QByteArray data_1800){
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

void Anytone::AprsSettings::encode(QByteArray &data_2501000, QByteArray &data_2501800){
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

std::tuple<uint8_t, uint8_t, uint8_t> Anytone::AprsSettings::decMinToDegree(double deg_min){
    uint8_t deg = uint8_t(abs(deg_min));
    double m = (abs(deg_min) - deg) * 60;
    
    uint8_t minutes = static_cast<uint8_t>(std::floor(m));
    uint8_t minutes_dec = static_cast<uint8_t>(
        std::round((m - minutes) * 100.0)
    );
    return std::tuple<uint8_t, uint8_t, uint8_t>(deg, minutes, minutes_dec);
}