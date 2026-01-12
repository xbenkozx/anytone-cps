#ifndef ANYTONE_CHANNEL_H
#define ANYTONE_CHANNEL_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QtEndian>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
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

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);
        void copy(Channel *ch);
        void clear();
        void setFrequencyStr(QString rx_frequency, QString tx_frequency);
        void setFrequency(int rx_frequency, int tx_frequency);
        int getTxFrequency();
        double getTxFrequencyDouble();
        QString getTxFrequencyString();
        double getRxFrequencyDouble();
        QString getRxFrequencyString();
        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encodeData();
        QByteArray encode_D878UVII();
        QByteArray encode_D890UV();
        QByteArray encode_D168UV();

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
        uint32_t custom_ctcss = 0;
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
        uint8_t tx_interrupt = 0;
        uint8_t scrambler_set = 0;
        uint8_t custom_scrambler = 0;
        uint8_t dmr_crc_ignore = false;
        QString name;

        int temp_contact_tg = 0;
        QString temp_radio_id_name;
        QString temp_scan_list_name;
        QString temp_receive_group_name;

        Talkgroup *contact = nullptr;
        RadioId *radioid;
        ScanList *scanlist;
        ReceiveGroup *receive_group_list;


        
    };

}

#endif