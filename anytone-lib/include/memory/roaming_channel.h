#ifndef ANYTONE_ROAMING_CHANNEL_H
#define ANYTONE_ROAMING_CHANNEL_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "int.h"

namespace Anytone {
    class RoamingChannel {
    public:
        RoamingChannel(){}
        ~RoamingChannel(){}

        double getRxFrequencyDouble();
        QString getRxFrequencyString();
        double getTxFrequencyDouble();
        QString getTxFrequencyString();

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        uint32_t rx_frequency = 0;
        uint32_t tx_frequency = 0;
        QString name = "";
        uint8_t color_code = 0;
        uint8_t slot = 0;
    };
}

#endif