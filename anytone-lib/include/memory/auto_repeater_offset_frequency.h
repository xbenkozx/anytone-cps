#ifndef ANYTONE_AUTO_REPEATER_OFFSET_FREQUENCY_H
#define ANYTONE_AUTO_REPEATER_OFFSET_FREQUENCY_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class AutoRepeaterOffsetFrequency{

    public:
        AutoRepeaterOffsetFrequency(){}
        ~AutoRepeaterOffsetFrequency(){}

        double getFrequencyDouble();
        QString getFrequencyString();
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        int frequency = 0;

    };
}

#endif