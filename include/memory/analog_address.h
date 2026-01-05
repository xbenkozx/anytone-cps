#ifndef ANYTONE_ANALOG_ADDRESS_H
#define ANYTONE_ANALOG_ADDRESS_H

#include <QByteArray>
#include <QString>
#include <QDataStream>

namespace Anytone {
    class AnalogAddress{
    public:
        AnalogAddress(){}
        ~AnalogAddress(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint32_t number = 0;
        QString name;
    };
}
#endif