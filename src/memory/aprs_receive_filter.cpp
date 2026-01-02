#include "aprs_receive_filter.h"

void Anytone::AprsReceiveFilter::decode(QByteArray data){
    enabled = static_cast<uint8_t>(data.at(0x0));
    callsign = QString(data.mid(0x1, 6));
    ssid = static_cast<uint8_t>(data.at(0x7));

    callsign.remove(QChar('\0'));
}

QByteArray Anytone::AprsReceiveFilter::encode(){
    QByteArray data(0x8, 0);
    data[0] = enabled;
    data[7] = ssid;
    data.replace(1, 6, callsign.leftJustified(6, '\0').toUtf8());
    return data;
}