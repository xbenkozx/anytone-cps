#ifndef ANYTONE_DTMF_SETTINGS_H
#define ANYTONE_DTMF_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class DTMFSettings {
    public:
        DTMFSettings(){}
        ~DTMFSettings(){}

        QStringList hex_char = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
        QStringList dtmf_char = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "*", "#"};

        void decode(QByteArray data_24c1000, QByteArray data_2500500);
        void encode(QByteArray &data_24c1000, QByteArray &data_2500500);
        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t tx_time = 0;
        QString self_id = "";
        uint8_t interval_char = 0xa;
        uint8_t group_code = 0xff;
        uint8_t decoding_response = 0;
        uint8_t first_digit_time = 0;
        uint8_t pretime = 0;
        uint8_t auto_reset_time = 0;
        uint8_t decode_time_lapse = 0;
        uint8_t ptt_id_pause_time = 0;
        uint8_t d_code_pause = 0;
        bool side_tone = false;
        bool ptt_id = false;
        QString ptt_id_bot;
        QString ptt_id_eot;
        QString remote_kill;
        QString remote_stun;
        QString m1;
        QString m2;
        QString m3;
        QString m4;
        QString m5;
        QString m6;
        QString m7;
        QString m8;
        QString m9;
        QString m10;
        QString m11;
        QString m12;
        QString m13;
        QString m14;
        QString m15;
        QString m16;

    };
}

#endif