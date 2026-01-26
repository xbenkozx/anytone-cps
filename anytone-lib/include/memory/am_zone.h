#ifndef AM_ZONE_H
#define AM_ZONE_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {

    class AmAir;

    class AmZone{
    public:
        AmZone(){}
        ~AmZone(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);
        void decode(QByteArray data);
        void decode_D890UV(QByteArray data);
        QByteArray encodeData();
        QByteArray encode_D890UV();

        uint16_t index = 0;
        QString name = "";

        AmAir* aChannel = nullptr;
        int aChannelIdx = 0;

        QVector<AmAir*> member_channels = {};
        QVector<AmAir*> scan_channels = {};

        QVector<int> member_channel_idxs = {};
        QVector<int> scan_channel_idxs = {};

    };
}

#endif