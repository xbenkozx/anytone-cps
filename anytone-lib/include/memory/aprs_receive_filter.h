#ifndef APRS_RECEIVE_FILTER_H
#define APRS_RECEIVE_FILTER_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class AprsReceiveFilter {
    public:
        AprsReceiveFilter(){}
        ~AprsReceiveFilter(){}

        void decode(QByteArray data);
        QByteArray encode();
        
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        uint8_t enabled = 0;
        QString callsign = "";
        uint8_t ssid = 0;

    };
}

#endif