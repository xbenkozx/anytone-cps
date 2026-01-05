#ifndef ANYTONE_ROAMING_ZONE_H
#define ANYTONE_ROAMING_ZONE_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QDataStream>
#include "roaming_channel.h"

namespace Anytone {
    class RoamingZone {
    public:
        RoamingZone(){}
        ~RoamingZone(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        QString name = "";
        QVector<RoamingChannel*> channels;
        QVector<int> channel_idxs;
    };
}

#endif