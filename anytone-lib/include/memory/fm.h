#ifndef ANYTONE_FM_H
#define ANYTONE_FM_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class FM {
    public:
        FM(){}
        ~FM(){}

        double getFrequencyDouble();
        QString getFrequencyString();
        void setFrequencyString(QString freq_str);
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        uint32_t frequency = 0;
        bool scan_add = true;
        QString name;
    };
}

#endif