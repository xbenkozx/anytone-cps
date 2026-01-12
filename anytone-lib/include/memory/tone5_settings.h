#ifndef ANYTONE_5TONE_SETTINGS_H
#define ANYTONE_5TONE_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class InformationCode {
    public:
        InformationCode(){}
        ~InformationCode(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        uint8_t function_option = 0;
        uint8_t decoding_response = 0;
        QString information_id;
        QString function_name;
    };

    class SpecialCall {
    public:
        SpecialCall(){}
        ~SpecialCall(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id;
        QString encode_id;
        uint8_t standard = 0;
        uint8_t tone_time = 40;
        QString name;
    };
    
    class Tone5Settings {
    public:
        Tone5Settings();
        ~Tone5Settings(){}

        void decode(QByteArray data_24c1000);
        void encode(QByteArray &data_24c1000);

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        QStringList hex_char = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};


        QString self_id;
        uint8_t decode_standard = 0;
        uint8_t decoding_response = 0;
        uint8_t decode_tone_time = 0;
        uint8_t decode_time = 0;
        uint8_t dec_units = 0;
        bool dis_anyid = false;

        uint8_t pretime = 0;
        uint8_t auto_reset_time = 0;
        uint8_t time_after_decode = 0;
        uint8_t pause_time = 0;
        uint8_t first_tone_length = 0;
        uint8_t stop_code = 0;
        uint8_t stop_time_length = 0;
        uint8_t first_tone_after_stop = 0;
        bool encode_side_tone = false;

        uint8_t ptt_bot_standard = 0;
        QString ptt_bot_encode_id;
        uint8_t ptt_bot_decode_time = 0;
        uint8_t ptt_eot_standard = 0;
        QString ptt_eot_encode_id;
        uint8_t ptt_eot_decode_time = 0;

        QVector<InformationCode*> information_code_list;
        QVector<SpecialCall*> special_call_list;

        uint8_t uint8_24c1031;
        QVector<uint16_t> unknown_freq_hz;

    };
}

#endif