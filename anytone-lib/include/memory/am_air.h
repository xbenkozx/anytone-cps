#ifndef AM_AIR_H
#define AM_AIR_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class AmAir {
    public:
        AmAir(){}
        ~AmAir(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);
        QString getFrequencyString();
        void setFrequencyStr(QString frequency);
        void decode(QByteArray data);
        void decode_D890UV(QByteArray data);
        QByteArray encode();
        QByteArray encode_D890UV();

        uint16_t index = 0;
        uint32_t frequency = 0;
        QString name = "";

    };
}

#endif