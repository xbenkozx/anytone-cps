#ifndef ANYTONE_ROAMING_ZONE_H
#define ANYTONE_ROAMING_ZONE_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "roaming_channel.h"

namespace Anytone {
    class RoamingZone {
    public:
        RoamingZone(){}
        ~RoamingZone(){}

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        QString name = "";
        QVector<RoamingChannel*> channels;
        QVector<int> channel_idxs;
    };
}

#endif