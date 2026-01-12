#include "memory/alarm_settings.h"

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

void Anytone::AlarmSettings::save(QXmlStreamWriter &xml){
    xml.writeStartElement("AlarmSettings");
    xml.writeAttribute("analog_emergency_alarm", QString::number(analog_emergency_alarm));
    xml.writeAttribute("analog_eni_type", QString::number(analog_eni_type));
    xml.writeAttribute("analog_emergency_id", QString::number(analog_emergency_id));
    xml.writeAttribute("analog_alarm_time", QString::number(analog_alarm_time));
    xml.writeAttribute("analog_tx_duration", QString::number(analog_tx_duration));
    xml.writeAttribute("analog_rx_duration", QString::number(analog_rx_duration));
    xml.writeAttribute("analog_eni_send", QString::number(analog_eni_send));
    xml.writeAttribute("analog_emergency_channel", QString::number(analog_emergency_channel));
    xml.writeAttribute("analog_emergency_cycle", QString::number(analog_emergency_cycle));
    xml.writeAttribute("work_mode_voice_switch", QString::number(work_mode_voice_switch));
    xml.writeAttribute("work_mode_area_switch", QString::number(work_mode_area_switch));
    xml.writeAttribute("work_mode_mic_switch", QString::number(work_mode_mic_switch));
    xml.writeAttribute("digital_emergency_alarm", QString::number(digital_emergency_alarm));
    xml.writeAttribute("digital_alarm_time", QString::number(digital_alarm_time));
    xml.writeAttribute("digital_tx_duration", QString::number(digital_tx_duration));
    xml.writeAttribute("digital_rx_duration", QString::number(digital_rx_duration));
    xml.writeAttribute("digital_eni_send", QString::number(digital_eni_send));
    xml.writeAttribute("digital_emergency_channel", QString::number(digital_emergency_channel));
    xml.writeAttribute("digital_emergency_cycle", QString::number(digital_emergency_cycle));
    xml.writeAttribute("digital_tg_dmr_id", QString::number(digital_tg_dmr_id));
    xml.writeAttribute("digital_call_type", QString::number(digital_call_type));
    xml.writeAttribute("receive_alarm", QString::number(receive_alarm));
    xml.writeAttribute("man_down", QString::number(man_down));
    xml.writeAttribute("man_down_delay", QString::number(man_down_delay));
    xml.writeEndElement();
}
void Anytone::AlarmSettings::load(QXmlStreamReader &xml){
    if (xml.name() == "AlarmSettings"){
        QXmlStreamAttributes attributes = xml.attributes();
        
        if(attributes.hasAttribute("analog_emergency_alarm"))
            analog_emergency_alarm = attributes.value("analog_emergency_alarm").toInt();
        if(attributes.hasAttribute("analog_eni_type"))
            analog_eni_type = attributes.value("analog_eni_type").toInt();
        if(attributes.hasAttribute("analog_emergency_id"))
            analog_emergency_id = attributes.value("analog_emergency_id").toInt();
        if(attributes.hasAttribute("analog_alarm_time"))
            analog_alarm_time = attributes.value("analog_alarm_time").toInt();
        if(attributes.hasAttribute("analog_tx_duration"))
            analog_tx_duration = attributes.value("analog_tx_duration").toInt();
        if(attributes.hasAttribute("analog_rx_duration"))
            analog_rx_duration = attributes.value("analog_rx_duration").toInt();
        if(attributes.hasAttribute("analog_eni_send"))
            analog_eni_send = attributes.value("analog_eni_send").toInt();
        if(attributes.hasAttribute("analog_emergency_channel"))
            analog_emergency_channel = attributes.value("analog_emergency_channel").toInt();
        if(attributes.hasAttribute("analog_emergency_cycle"))
            analog_emergency_cycle = attributes.value("analog_emergency_cycle").toInt();
        if(attributes.hasAttribute("work_mode_voice_switch"))
            work_mode_voice_switch = attributes.value("work_mode_voice_switch").toInt();
        if(attributes.hasAttribute("work_mode_area_switch"))
            work_mode_area_switch = attributes.value("work_mode_area_switch").toInt();
        if(attributes.hasAttribute("work_mode_mic_switch"))
            work_mode_mic_switch = attributes.value("work_mode_mic_switch").toInt();
        if(attributes.hasAttribute("digital_emergency_alarm"))
            digital_emergency_alarm = attributes.value("digital_emergency_alarm").toInt();
        if(attributes.hasAttribute("digital_alarm_time"))
            digital_alarm_time = attributes.value("digital_alarm_time").toInt();
        if(attributes.hasAttribute("digital_tx_duration"))
            digital_tx_duration = attributes.value("digital_tx_duration").toInt();
        if(attributes.hasAttribute("digital_rx_duration"))
            digital_rx_duration = attributes.value("digital_rx_duration").toInt();
        if(attributes.hasAttribute("digital_eni_send"))
            digital_eni_send = attributes.value("digital_eni_send").toInt();
        if(attributes.hasAttribute("digital_emergency_channel"))
            digital_emergency_channel = attributes.value("digital_emergency_channel").toInt();
        if(attributes.hasAttribute("digital_emergency_cycle"))
            digital_emergency_cycle = attributes.value("digital_emergency_cycle").toInt();
        if(attributes.hasAttribute("digital_tg_dmr_id"))
            digital_tg_dmr_id = attributes.value("digital_tg_dmr_id").toInt();
        if(attributes.hasAttribute("digital_call_type"))
            digital_call_type = attributes.value("digital_call_type").toInt();
        if(attributes.hasAttribute("receive_alarm"))
            receive_alarm = attributes.value("receive_alarm").toInt();
        if(attributes.hasAttribute("man_down"))
            man_down = attributes.value("man_down").toInt();
        if(attributes.hasAttribute("man_down_delay"))
            man_down_delay = attributes.value("man_down_delay").toInt();

    }
}