#include "gps_roaming.h"

void Anytone::GpsRoaming::decode(QByteArray data){
    enabled = static_cast<uint8_t>(data.at(0));
    zone_idx = static_cast<uint8_t>(data.at(1));
    lat_degree = static_cast<uint8_t>(data.at(2));
    lat_minute = static_cast<uint8_t>(data.at(3));
    lat_minute_decimal = static_cast<uint8_t>(data.at(4));
    north_south = static_cast<uint8_t>(data.at(5));
    long_degree = static_cast<uint8_t>(data.at(6));
    long_minute = static_cast<uint8_t>(data.at(7));
    long_minute_decimal = static_cast<uint8_t>(data.at(8));
    east_west = static_cast<int>(data.at(9));
    radius = Int::fromBytes(data.mid(12, 2));
}
QByteArray Anytone::GpsRoaming::encode(){
    QByteArray data(0x10, 0);
    data[0] = enabled;
    data[1] = zone_idx;
    data[2] = lat_degree;
    data[3] = lat_minute;
    data[4] = lat_minute_decimal;
    data[5] = north_south;
    data[6] = long_degree;
    data[7] = long_minute;
    data[8] = long_minute_decimal;
    data[9] = east_west;

    data.replace(0xc, 4, 
        Int::toBytes(radius, 4)
    );
    return data;
}