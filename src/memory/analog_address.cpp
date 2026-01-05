#include "analog_address.h"
#include <QDebug>

void Anytone::AnalogAddress::decode(QByteArray data){
    uint8_t number_len = data[0x7];
    number = data.mid(0x0, 0x5).toHex().mid(0, number_len).toInt();
    name = QString(data.mid(0x8, 0xf));
    name.remove(QChar('\0'));
}
QByteArray Anytone::AnalogAddress::encode(){
    QByteArray data(0x18, 0);
    QString num = QString::number(number);
    data.replace(0x0, 5, 
        QByteArray::fromHex(num.rightJustified(10, '0').toUtf8())
    );
    data[0x7] = num.size();
    data.replace(0x8, 0xf, 
        name.toUtf8().leftJustified(0xf, '\0')
    );

    return data;
}

void Anytone::AnalogAddress::save(QDataStream &ds){
    ds << number;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void Anytone::AnalogAddress::load(QDataStream &ds){
    ds >> number;
    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}