#ifndef ANYTONE_AUTO_REPEATER_OFFSET_FREQUENCY_H
#define ANYTONE_AUTO_REPEATER_OFFSET_FREQUENCY_H

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace Anytone {
    class AutoRepeaterOffsetFrequency{

    public:
        AutoRepeaterOffsetFrequency(){}
        ~AutoRepeaterOffsetFrequency(){}

        double getFrequencyDouble(){
            return double(frequency) / 100000;
        };

        QString getFrequencyString(){
            return QString::number(getFrequencyDouble(), 'f', 3);
        };

        int id = 0;
        int frequency = 0;

    };
}

#endif