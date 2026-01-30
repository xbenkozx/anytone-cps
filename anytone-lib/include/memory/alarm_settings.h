#ifndef ANYTONE_ALARM_SETTINGS_H
#define ANYTONE_ALARM_SETTINGS_H

#include <algorithm>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class AlarmSettings {
    public:
        AlarmSettings(){}
        ~AlarmSettings(){}

        void decode_D878UVII(QByteArray data_0000, QByteArray data_1400, QByteArray data_1440);
        void decode_D890UV(QByteArray data_3483000, QByteArray data_3482e00, QByteArray data_3500000);
        void encode_D878UVII(QByteArray &data_2500000, QByteArray &data_24c1400, QByteArray &data_24c1440);
        void encode_D890UV(QByteArray &data_3483000, QByteArray &data_3482e00, QByteArray &data_3500000);
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t analog_emergency_alarm = 0;
        uint8_t analog_eni_type = 0;
        uint8_t analog_emergency_id = 0;
        uint8_t analog_alarm_time = 0;
        uint8_t analog_tx_duration = 0;
        uint8_t analog_rx_duration = 0;
        uint8_t analog_eni_send = 0;
        uint8_t analog_emergency_channel = 0;
        uint8_t analog_emergency_cycle = 0;
        uint8_t work_mode_voice_switch = 0;
        uint8_t work_mode_area_switch = 0;
        uint8_t work_mode_mic_switch = 0;
        uint8_t digital_emergency_alarm = 0;
        uint8_t digital_alarm_time = 0;
        uint8_t digital_tx_duration = 0;
        uint8_t digital_rx_duration = 0;
        uint8_t digital_eni_send = 0;
        uint8_t digital_emergency_channel = 0;
        uint8_t digital_emergency_cycle = 0;
        uint8_t work_alone_response_time = 0;
        uint8_t work_alone_warning_time = 0;
        uint8_t work_alone_response = 0;
        int digital_tg_dmr_id = 0;
        uint8_t digital_call_type = 0;
        bool receive_alarm = false;
        bool man_down = false;
        uint8_t man_down_delay = 0;
        int qdc_call_type = 0;
        QString qdc_group_id;
        QString qdc_private_id;
    };
}

#endif