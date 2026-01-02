#ifndef ANYTONE_2TONE_SETTINGS_H
#define ANYTONE_2TONE_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include "int.h"

namespace Anytone {
    class Tone2EncodeItem {
        public:
        Tone2EncodeItem(){}
        ~Tone2EncodeItem(){}

        void decode(QByteArray data){
            if(data == QByteArray(0x10, 0xff)) return;
            tone_frequency_1 = Int::fromBytes(data.mid(0, 2));
            tone_frequency_2 = Int::fromBytes(data.mid(2, 2));
            name = QString(data.mid(0x8, 0x7));
            name.remove(QChar('\0'));
        }

        QByteArray encode(){
            if(tone_frequency_1 == 0) return QByteArray(0x10, 0xff);
            QByteArray data(0x10, 0xff);
            data.replace(0x0, 2, 
                Int::toBytes(tone_frequency_1, 2)
            );
            data.replace(0x2, 2, 
                Int::toBytes(tone_frequency_2, 2)
            );
            data.replace(0x8, 7, 
                QByteArray::fromHex(name.rightJustified(7, '0').toUtf8())
            );
            return data;
        }

        uint16_t id = 0;
        uint16_t tone_frequency_1 = 0;
        uint16_t tone_frequency_2 = 0;
        QString name;

    };
    class Tone2DecodeItem {
        public:
        Tone2DecodeItem(){}
        ~Tone2DecodeItem(){}

        void decode(QByteArray data){
            tone_frequency_1 = Int::fromBytes(data.mid(0, 2));
            tone_frequency_2 = Int::fromBytes(data.mid(2, 2));
            decoding_response = static_cast<uint8_t>(data.at(0x4));
            name = QString(data.mid(0x5, 0x7));
            name.remove(QChar('\0'));
        }

        QByteArray encode(){
            if(tone_frequency_1 == 0) return QByteArray(0x20, 0xff);
            QByteArray data(0x10, 0);
            data.replace(0x0, 2, 
                Int::toBytes(tone_frequency_1, 2)
            );
            data.replace(0x2, 2, 
                Int::toBytes(tone_frequency_2, 2)
            );
            data[0x4] = decoding_response;
            data.replace(0x5, 7, 
                QByteArray::fromHex(name.rightJustified(7, '0').toUtf8())
            );
            return data;
        }

        uint16_t id = 0;
        uint16_t tone_frequency_1 = 0;
        uint16_t tone_frequency_2 = 0;
        uint8_t decoding_response = 0;
        QString name;

    };
    class Tone2Settings {
    public:
        Tone2Settings(){
            // encode_list.clear;
            // decode_list.clear;

            for(int i = 0; i < 24; i++){
                Tone2EncodeItem *item = new Tone2EncodeItem();
                item->id = i;
                encode_list.push_back(item);
            }

            for(int i = 0; i < 16; i++){
                Tone2DecodeItem *item = new Tone2DecodeItem();
                item->id = i;
                decode_list.push_back(item);
            }
        }
        ~Tone2Settings(){}

        void decode(QByteArray data_24c1290, QByteArray data_24c1100, QByteArray data_24c2400){
            encode_tone_1_duration = static_cast<uint8_t>(data_24c1290.at(0x9));
            encode_tone_2_duration = static_cast<uint8_t>(data_24c1290.at(0xa));
            encode_long_tone_duration = static_cast<uint8_t>(data_24c1290.at(0xb));
            encode_gap_time = static_cast<uint8_t>(data_24c1290.at(0xc));
            encode_auto_reset_time = static_cast<uint8_t>(data_24c1290.at(0xd));
            encode_side_tone = static_cast<bool>(data_24c1290.at(0xe));

            for(int i =0; i < 24; i++){
                encode_list.at(i)->decode(data_24c1100.mid(i*0x10, 0x10));
            }

            for(int i = 0; i < 16; i++){
                decode_list.at(i)->decode(data_24c2400.mid(i*0x10, 0x10));
            }
        }

        void encode(QByteArray &data_24c1290, QByteArray &data_24c1100, QByteArray &data_24c2400){
            data_24c1290[0x9] = encode_tone_1_duration;
            data_24c1290[0xa] = encode_tone_2_duration;
            data_24c1290[0xb] = encode_long_tone_duration;
            data_24c1290[0xc] = encode_gap_time;
            data_24c1290[0xe] = encode_auto_reset_time;
            data_24c1290[0xf] = encode_side_tone;

            for(int i =0; i < 24; i++){
                data_24c1100.append(encode_list.at(i)->encode());
            }

            for(int i =0; i < 16; i++){
                data_24c2400.append(decode_list.at(i)->encode());
            }
        }
        
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