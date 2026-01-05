#ifndef APRS_RECEIVE_FILTER_H
#define APRS_RECEIVE_FILTER_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class AprsReceiveFilter {
    public:
        AprsReceiveFilter(){}
        ~AprsReceiveFilter(){}

        void decode(QByteArray data);
        QByteArray encode();
        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        uint8_t enabled = 0;
        QString callsign = "";
        uint8_t ssid = 0;

    };
}

#endif