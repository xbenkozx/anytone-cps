#ifndef ANYTONE_FM_H
#define ANYTONE_FM_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class FM {
    public:
        FM(){}
        ~FM(){}

        double getFrequencyDouble();
        QString getFrequencyString();
        void setFrequencyString(QString freq_str);
        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        uint32_t frequency = 0;
        bool scan_add = true;
        QString name;
    };
}

#endif