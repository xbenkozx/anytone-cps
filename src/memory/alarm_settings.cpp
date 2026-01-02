#include "alarm_settings.h"

void Anytone::AlarmSettings::decode(QByteArray data_0000, QByteArray data_1400, QByteArray data_1440){
    analog_emergency_alarm = static_cast<uint8_t>(data_1400.at(0x0));
    analog_eni_type = static_cast<uint8_t>(data_1400.at(0x1));
    analog_emergency_id = static_cast<uint8_t>(data_1400.at(0x2));
    analog_alarm_time = static_cast<uint8_t>(data_1400.at(0x3));
    analog_tx_duration = static_cast<uint8_t>(data_1400.at(0x4));
    analog_rx_duration = static_cast<uint8_t>(data_1400.at(0x5));
    analog_eni_send = static_cast<uint8_t>(data_1400.at(0x8));
    analog_emergency_channel = static_cast<uint8_t>(data_1400.at(0x6));
    analog_emergency_cycle = static_cast<uint8_t>(data_1400.at(0x9));
    work_mode_voice_switch =  static_cast<uint8_t>(data_1400.at(0x12));
    work_mode_area_switch =  static_cast<uint8_t>(data_1400.at(0x13));
    work_mode_mic_switch =  static_cast<uint8_t>(data_1400.at(0x14));
    digital_emergency_alarm = static_cast<uint8_t>(data_1400.at(0xa));
    digital_alarm_time = static_cast<uint8_t>(data_1400.at(0xb));
    digital_tx_duration = static_cast<uint8_t>(data_1400.at(0xc));
    digital_rx_duration = static_cast<uint8_t>(data_1400.at(0xd));
    digital_eni_send =  static_cast<uint8_t>(data_1400.at(0x10));
    digital_emergency_channel = static_cast<uint8_t>(data_1400.at(0xe));
    digital_emergency_cycle =  static_cast<uint8_t>(data_1400.at(0x11));
    digital_call_type = static_cast<uint8_t>(data_1440.at(0x0));
    receive_alarm =  static_cast<uint8_t>(data_1400.at(0x15));
    man_down =  static_cast<uint8_t>(data_0000.at(0x24));
    man_down_delay =  static_cast<uint8_t>(data_0000.at(0x4f));

    digital_tg_dmr_id = QString(data_1440.mid(0x23, 0x4).toHex()).toInt();
}

void Anytone::AlarmSettings::encode(QByteArray &data_2500000, QByteArray &data_24c1400, QByteArray &data_24c1440){
    data_24c1400[0x00] = analog_emergency_alarm;
    data_24c1400[0x01] = analog_eni_type;
    data_24c1400[0x02] = analog_emergency_id;
    data_24c1400[0x03] = analog_alarm_time;
    data_24c1400[0x04] = analog_tx_duration;
    data_24c1400[0x05] = analog_rx_duration;
    data_24c1400[0x08] = analog_eni_send;
    data_24c1400[0x06] = analog_emergency_channel;
    data_24c1400[0x09] = analog_emergency_cycle;
    data_24c1400[0x12] = work_mode_voice_switch;
    data_24c1400[0x13] = work_mode_area_switch;
    data_24c1400[0x14] = work_mode_mic_switch;
    data_24c1400[0x0a] = digital_emergency_alarm;
    data_24c1400[0x0b] = digital_alarm_time;
    data_24c1400[0x0c] = digital_tx_duration;
    data_24c1400[0x0d] = digital_rx_duration;
    data_24c1400[0x10] = digital_eni_send;
    data_24c1400[0x0e] = digital_emergency_channel;
    data_24c1400[0x11] = digital_emergency_cycle;
    data_24c1440.replace(0x23, 4, 
        QByteArray::fromHex(QString::number(digital_tg_dmr_id).rightJustified(8, '0').toUtf8())
    );
    data_24c1440[0x0] = digital_call_type;
    data_24c1400[0x15] = receive_alarm;
    data_2500000[0x24] = man_down;
    data_2500000[0x4f] = man_down_delay;
}