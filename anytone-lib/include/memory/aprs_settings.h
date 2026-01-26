#ifndef ANYTONE_APRS_SETTINGS_H
#define ANYTONE_APRS_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "aprs_receive_filter.h"
#include "utils.h"
#include "int.h"

namespace Anytone {
    
    class AprsSettings {
    public:
        AprsSettings(){
            for(int i = 0; i < 32; i++){
                AprsReceiveFilter *f = new AprsReceiveFilter();
                f->id = i;
                receive_filters.push_back(f);
            }
        }
        ~AprsSettings(){}

        void decode_D878UVII(QByteArray data_1000, QByteArray data_1800);
        void encode_D878UVII(QByteArray &data_2501000, QByteArray &data_2501800);
        void decode_D890UV(QByteArray data_1000, QByteArray data_1800);
        void encode_D890UV(QByteArray &data_3501000, QByteArray &data_3501800);
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);
        static double degMinToDecimal(uint8_t deg, double minutes){
            return double(deg) + (minutes / 60);
        }
        static std::tuple<uint8_t, uint8_t, uint8_t> decMinToDegree(double deg_min);

        int tx_freq_1 = 0;
        uint8_t tx_delay = 0;
        uint8_t send_subtone = 0;
        uint8_t ctcss = 0;
        int dcs = 0;
        uint8_t manual_tx_interval = 0;
        uint8_t auto_tx_interval = 0;
        uint8_t tx_tone = 0;
        double fix_1_lat = 0.0;
        uint8_t fix_1_ns = 0;
        double fix_1_lng = 0.0;
        uint8_t fix_1_ew = 0;
        QString to_call = "";
        uint8_t to_call_ssid = 0;
        QString your_call = "";
        uint8_t your_call_ssid = 0;
        QString digipeater_path = "";
        QString aprs_symbol = "";
        QString map_icon = "";
        uint8_t tx_power = 0;
        uint8_t prewave_time = 0;
        uint8_t roaming_support = 0;
        uint8_t repeater_activation_delay = 0;
        uint8_t dis_time = 0;
        uint8_t altitude = 0;
        uint8_t pass_all = 0;
        QString sending_text = "";
        uint8_t fixed_location_beacon = 0;
        uint8_t analog_tx_mode = 0;
        bool filter_position = false;
        bool filter_mic_e = false;
        bool filter_object = false;
        bool filter_item = false;
        bool filter_message = false;
        bool filter_wx_report = false;
        bool filter_nmea_report = false;
        bool filter_status_report = false;
        bool filter_other = false;

        // Report Channel
        int digital_report_channel_1 = 0xa20f;
        int digital_report_channel_2 = 0xa20f;
        int digital_report_channel_3 = 0xa20f;
        int digital_report_channel_4 = 0xa20f;
        int digital_report_channel_5 = 0xa20f;
        int digital_report_channel_6 = 0xa20f;
        int digital_report_channel_7 = 0xa20f;
        int digital_report_channel_8 = 0xa20f;

        int digital_report_tg_1 = 0;
        int digital_report_tg_2 = 0;
        int digital_report_tg_3 = 0;
        int digital_report_tg_4 = 0;
        int digital_report_tg_5 = 0;
        int digital_report_tg_6 = 0;
        int digital_report_tg_7 = 0;
        int digital_report_tg_8 = 0;

        int digital_report_call_type_1 = 0;
        int digital_report_call_type_2 = 0;
        int digital_report_call_type_3 = 0;
        int digital_report_call_type_4 = 0;
        int digital_report_call_type_5 = 0;
        int digital_report_call_type_6 = 0;
        int digital_report_call_type_7 = 0;
        int digital_report_call_type_8 = 0;

        int digital_report_slot_1 = 0;
        int digital_report_slot_2 = 0;
        int digital_report_slot_3 = 0;
        int digital_report_slot_4 = 0;
        int digital_report_slot_5 = 0;
        int digital_report_slot_6 = 0;
        int digital_report_slot_7 = 0;
        int digital_report_slot_8 = 0;
        

        double fix_2_lat = 0.0;
        double fix_2_lng = 0.0;
        double fix_3_lat = 0.0;
        double fix_3_lng = 0.0;
        double fix_4_lat = 0.0;
        double fix_4_lng = 0.0;
        double fix_5_lat = 0.0;
        double fix_5_lng = 0.0;
        double fix_6_lat = 0.0;
        double fix_6_lng = 0.0;
        double fix_7_lat = 0.0;
        double fix_7_lng = 0.0;
        double fix_8_lat = 0.0;
        double fix_8_lng = 0.0;

        int fix_2_ns = 0;
        int fix_2_ew = 0;
        int fix_3_ns = 0;
        int fix_3_ew = 0;
        int fix_4_ns = 0;
        int fix_4_ew = 0;
        int fix_5_ns = 0;
        int fix_5_ew = 0;
        int fix_6_ns = 0;
        int fix_6_ew = 0;
        int fix_7_ns = 0;
        int fix_7_ew = 0;
        int fix_8_ns = 0;
        int fix_8_ew = 0;


        int tx_freq_2 = 0;
        int tx_freq_3 = 0;
        int tx_freq_4 = 0;
        int tx_freq_5 = 0;
        int tx_freq_6 = 0;
        int tx_freq_7 = 0;
        int tx_freq_8 = 0;

        std::vector<AprsReceiveFilter*> receive_filters = {};
    };

    
}

#endif