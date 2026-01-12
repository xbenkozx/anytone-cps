#ifndef ANYTONE_GPS_ROAMING_H
#define ANYTONE_GPS_ROAMING_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "zone.h"

namespace Anytone {
    class GpsRoaming {
    public:
        GpsRoaming(){}
        ~GpsRoaming(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        uint8_t enabled = 0;
        uint8_t zone_idx = 0xff;
        uint8_t lat_degree = 0;
        uint8_t lat_minute = 0;
        uint8_t lat_minute_decimal = 0;
        uint8_t north_south = 0;
        uint8_t long_degree = 0;
        uint8_t long_minute = 0;
        uint8_t long_minute_decimal = 0;
        uint8_t east_west = 0;
        uint32_t radius = 0;

        Zone *zone;
    };
}

#endif