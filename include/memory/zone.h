#ifndef ANYTONE_ZONE_H
#define ANYTONE_ZONE_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include "memory/channel.h"

namespace Anytone {

    class Zone{
    public:
        Zone(){}
        ~Zone(){}

        void save(QDataStream &ds){
            ds << id;
            uint8_t name_len = name.size();
            ds << name_len;
            for(char c : name.toStdString()){
                ds << c;
            }
            ds << hide;
            ds << a_channel_idx;
            ds << b_channel_idx;

            uint8_t channel_count = channels.size();
            ds << channel_count;
            for(Channel *ch : channels){
                ds << ch->id;
            }

        }

        void load(QDataStream &ds){
            uint8_t name_size;
            ds >> name_size;
            for(int i = 0; i < name_size; i++){
                char c;
                ds >> c;
                name.append(c);
            }

            ds >> hide;
            ds >> a_channel_idx;
            ds >> b_channel_idx;

            uint8_t channel_count;
            ds >> channel_count;
            for(int i = 0; i < channel_count; i++){
                uint16_t ch_idx;
                ds >> ch_idx;
                temp_member_channel_idxs.append(ch_idx);
            }
        }

        uint8_t id = 0;
        QString name = "";
        bool hide = false;
        uint16_t a_channel_idx = 0;
        uint16_t b_channel_idx = 0;
        QVector<Channel*> channels = {};
        Channel *a_channel;
        Channel *b_channel;
        QVector<uint16_t> temp_member_channel_idxs = {};
        QVector<QVector<QString>> temp_member_channels = {};

    };
}

#endif