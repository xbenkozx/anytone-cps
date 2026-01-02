#ifndef ANYTONE_CHANNEL_H
#define ANYTONE_CHANNEL_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QtEndian>
#include <iostream>
#include "utils.h"
#include "int.h"
#include "memory/talkgroup.h"
#include "memory/radioid.h"
#include "memory/scanlist.h"
#include "receive_group_call_list.h"

namespace Anytone {

    class ScanList;

    class Channel{
    public:
        Channel(){}
        ~Channel(){}

        void save(QDataStream &ds);
        void load(QDataStream &ds);
        void copy(Channel *ch);
        void clear(){
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

        void setFrequencyStr(QString rx_frequency, QString tx_frequency){
            int rx_freq = int(rx_frequency.toDouble() * 100000);
            int tx_freq = int(tx_frequency.toDouble() * 100000);
            setFrequency(rx_freq, tx_freq);
        }

        void setFrequency(int rx_frequency, int tx_frequency){
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
        
        int getTxFrequency(){
            int tx_frequency = rx_frequency;
    
            if(offset_direction == 1){
                tx_frequency = rx_frequency + offset;
            }else if(offset_direction == 2){
                tx_frequency = rx_frequency - offset;
            }

            return tx_frequency;
        };
        double getTxFrequencyDouble(){
            return double(getTxFrequency()) / 100000;
        };
        QString getTxFrequencyString(){
            return QString::number(getTxFrequencyDouble(), 'f', 5);
        };
        double getRxFrequencyDouble(){
            return double(rx_frequency) / 100000;
        };
        QString getRxFrequencyString(){
            return QString::number(getRxFrequencyDouble(), 'f', 5);
        };
        void decode(QByteArray data_0, QByteArray data_1);
        QByteArray encodeData1();
        QByteArray encodeData2();

        uint16_t id = 0;
        uint32_t rx_frequency = 0;
        uint32_t offset = 0;
        uint8_t offset_direction = 0;
        uint8_t correct_frequency = 0;
        uint8_t band_width = 0;
        uint8_t tx_power = 0;
        uint8_t channel_type = 0;
        bool talkaround = false;
        bool call_confirmation = false;
        bool ptt_prohibit = false;
        uint8_t ctcss_dcs_decode = 0;
        uint8_t ctcss_dcs_encode = 0;
        uint8_t ctcss_decode_tone = 0;
        uint8_t ctcss_encode_tone = 0;
        uint16_t dcs_decode_tone = 0;
        uint16_t dcs_encode_tone = 0;
        uint16_t contact_idx = 0;
        uint8_t radio_id_idx = 0;
        uint8_t squelch_mode = 0;
        uint8_t ptt_id = 0;
        uint8_t optional_signal = 0;
        uint8_t busy_lock = 0;
        uint8_t scan_list_idx = 0;
        uint8_t tone2_id_idx = 0;
        uint8_t tone5_id_idx = 0;
        uint8_t dtmf_id_idx = 0;
        uint8_t rx_color_code_idx = 0;
        uint8_t tx_color_code_idx = 0;
        bool work_alone = false;
        bool slot_suit = false;
        uint8_t dmr_mode_dcdm = 0;
        uint8_t time_slot = 0;
        uint8_t receive_group_call_list_idx = 0;
        bool sms_confirmation = false;
        uint8_t aes_encryption_idx = 0;
        bool auto_scan = false;
        bool data_ack_disable = false;
        bool exclude_channel_roaming = false;
        uint8_t dmr_mode = 0;
        bool ranging = false;
        uint8_t extend_encryption = 0;
        bool send_talker_alias = false;
        bool sms_forbid = false;
        bool aes_random_key = false;
        bool aes_multiple_key = false;
        uint8_t arc4_encryption_key_idx = 0;
        uint8_t analog_aprs_report_frequency_idx = 0;
        uint8_t reverse = 0;
        bool aprs_rx = false;
        uint8_t analog_aprs_ptt_mode = 0;
        uint8_t digital_aprs_ptt_mode = 0;
        uint8_t aprs_report_type = 0;
        bool analog_aprs_mute = false;
        uint8_t digital_aprs_report_channel = 0;
        uint8_t tone2_decode = 0;
        uint8_t r5tone_bot = 0;
        uint8_t r5tone_eot = 0;
        uint8_t digital_encryption = 0;
        QString name;

        Talkgroup *contact = nullptr;
        RadioId *radioid;
        ScanList *scanlist;
        ReceiveGroup *receive_group_list;
    };

}

#endif