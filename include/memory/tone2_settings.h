#ifndef ANYTONE_2TONE_SETTINGS_H
#define ANYTONE_2TONE_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>
#include "int.h"

namespace Anytone {
    class Tone2EncodeItem {
        public:
        Tone2EncodeItem(){}
        ~Tone2EncodeItem(){}

        void decode(QByteArray data);
        QByteArray encode();
        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint16_t id = 0;
        uint16_t tone_frequency_1 = 0;
        uint16_t tone_frequency_2 = 0;
        QString name;

    };
    class Tone2DecodeItem {
        public:
        Tone2DecodeItem(){}
        ~Tone2DecodeItem(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint16_t id = 0;
        uint16_t tone_frequency_1 = 0;
        uint16_t tone_frequency_2 = 0;
        uint8_t decoding_response = 0;
        QString name;

    };
    class Tone2Settings {
    public:
        Tone2Settings();
        ~Tone2Settings(){}

        void decode(QByteArray data_24c1290);
        void encode(QByteArray &data_24c1290);
        
        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t encode_tone_1_duration = 0;
        uint8_t encode_tone_2_duration = 0;
        uint8_t encode_long_tone_duration = 0;
        uint8_t encode_gap_time = 0;
        uint8_t encode_auto_reset_time = 0;
        bool encode_side_tone = false;
        QVector<Tone2EncodeItem*> encode_list;
        QVector<Tone2DecodeItem*> decode_list;

    };
}

#endif