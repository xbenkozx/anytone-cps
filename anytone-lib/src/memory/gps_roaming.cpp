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

void Anytone::GpsRoaming::save(QXmlStreamWriter &xml){
    xml.writeStartElement("GPSRoaming");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("enabled", QString::number(enabled));
    xml.writeAttribute("zone_idx", QString::number(zone_idx));
    xml.writeAttribute("lat_degree", QString::number(lat_degree));
    xml.writeAttribute("lat_minute", QString::number(lat_minute));
    xml.writeAttribute("lat_minute_decimal", QString::number(lat_minute_decimal));
    xml.writeAttribute("north_south", QString::number(north_south));
    xml.writeAttribute("long_degree", QString::number(long_degree));
    xml.writeAttribute("long_minute", QString::number(long_minute));
    xml.writeAttribute("long_minute_decimal", QString::number(long_minute_decimal));
    xml.writeAttribute("east_west", QString::number(east_west));
    xml.writeAttribute("radius", QString::number(radius));
    xml.writeEndElement();
}
void Anytone::GpsRoaming::load(QXmlStreamReader &xml){
    if (xml.name() == "GPSRoaming"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("enabled"))
            enabled = attributes.value("enabled").toInt();
        if(attributes.hasAttribute("zone_idx"))
            zone_idx = attributes.value("zone_idx").toInt();
        if(attributes.hasAttribute("lat_degree"))
            lat_degree = attributes.value("lat_degree").toInt();
        if(attributes.hasAttribute("lat_minute"))
            lat_minute = attributes.value("lat_minute").toInt();
        if(attributes.hasAttribute("lat_minute_decimal"))
            lat_minute_decimal = attributes.value("lat_minute_decimal").toInt();
        if(attributes.hasAttribute("north_south"))
            north_south = attributes.value("north_south").toInt();
        if(attributes.hasAttribute("long_degree"))
            long_degree = attributes.value("long_degree").toInt();
        if(attributes.hasAttribute("long_minute"))
            long_minute = attributes.value("long_minute").toInt();
        if(attributes.hasAttribute("long_minute_decimal"))
            long_minute_decimal = attributes.value("long_minute_decimal").toInt();
        if(attributes.hasAttribute("east_west"))
            east_west = attributes.value("east_west").toInt();
        if(attributes.hasAttribute("radius"))
            radius = attributes.value("radius").toInt();

    }
}