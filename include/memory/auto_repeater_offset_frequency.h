#ifndef ANYTONE_AUTO_REPEATER_OFFSET_FREQUENCY_H
#define ANYTONE_AUTO_REPEATER_OFFSET_FREQUENCY_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class AutoRepeaterOffsetFrequency{

    public:
        AutoRepeaterOffsetFrequency(){}
        ~AutoRepeaterOffsetFrequency(){}

        double getFrequencyDouble();
        QString getFrequencyString();
        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        int frequency = 0;

    };
}

#endif