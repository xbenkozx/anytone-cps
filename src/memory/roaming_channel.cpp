#include "roaming_channel.h"

double Anytone::RoamingChannel::getRxFrequencyDouble(){
    return double(rx_frequency) / 100000;
};
QString Anytone::RoamingChannel::getRxFrequencyString(){
    return QString::number(getTxFrequencyDouble(), 'f', 5);
};
double Anytone::RoamingChannel::getTxFrequencyDouble(){
    return double(tx_frequency) / 100000;
};
QString Anytone::RoamingChannel::getTxFrequencyString(){
    return QString::number(getTxFrequencyDouble(), 'f', 5);
};

void Anytone::RoamingChannel::decode(QByteArray data){
    rx_frequency = QString(data.mid(0x0, 4).toHex()).toInt();
    tx_frequency = QString(data.mid(0x4, 4).toHex()).toInt();
    color_code = static_cast<uint8_t>(data.at(0x8));
    slot = static_cast<uint8_t>(data.at(0x9));
    name = QString(data.mid(0xa, 0x10));
    name.remove(QChar('\0'));
}
QByteArray Anytone::RoamingChannel::encode(){
    QByteArray data(0x20, 0);
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(rx_frequency).rightJustified(8, '0').toUtf8())
    );
    data.replace(0x4, 4, 
        QByteArray::fromHex(QString::number(tx_frequency).rightJustified(8, '0').toUtf8())
    );
    data.replace(0x8, 1, 
        Int::toBytes(slot, 1)
    );
    data.replace(0x9, 1, 
        Int::toBytes(slot, 1)
    );
    data.replace(0xa, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );
    
    return data;
}

void Anytone::RoamingChannel::save(QDataStream &ds){
    ds << id;
    ds << rx_frequency;
    ds << tx_frequency;
    ds << color_code;
    ds << slot;

    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
    
}
void Anytone::RoamingChannel::load(QDataStream &ds){
    ds >> rx_frequency;
    ds >> tx_frequency;
    ds >> color_code;
    ds >> slot;

    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}