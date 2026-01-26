#ifndef ANYTONE_ANALOG_ADDRESS_H
#define ANYTONE_ANALOG_ADDRESS_H

#include <QByteArray>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class AnalogAddress{
    public:
        AnalogAddress(){}
        ~AnalogAddress(){}

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        QByteArray encode();
        QByteArray encode_D878UVII();
        QByteArray encode_D890UV();
        
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        int id;
        uint32_t number = 0;
        QString name;
    };
}
#endif