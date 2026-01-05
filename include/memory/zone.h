#ifndef ANYTONE_ZONE_H
#define ANYTONE_ZONE_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QDataStream>
#include "memory/channel.h"

namespace Anytone {

    class Zone{
    public:
        Zone(){}
        ~Zone(){}

        void save(QDataStream &ds);
        void load(QDataStream &ds);

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