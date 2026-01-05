#ifndef ANYTONE_ROAMING_CHANNEL_H
#define ANYTONE_ROAMING_CHANNEL_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>
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
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        uint32_t rx_frequency = 0;
        uint32_t tx_frequency = 0;
        QString name = "";
        uint8_t color_code = 0;
        uint8_t slot = 0;
    };
}

#endif