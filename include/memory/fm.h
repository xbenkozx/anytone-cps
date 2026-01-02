#ifndef ANYTONE_FM_H
#define ANYTONE_FM_H

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace Anytone {
    class FM {
    public:
        FM(){}
        ~FM(){}

        double getFrequencyDouble(){
            return double(frequency) / 10000;
        };

        QString getFrequencyString(){
            return QString::number(getFrequencyDouble(), 'f', 2);
        };

        void setFrequencyString(QString freq_str){
            frequency = int(freq_str.toDouble() * 10000);
        }

        int id = 0;
        uint32_t frequency = 0;
        bool scan_add = true;
        QString name;
    };
}

#endif