#ifndef ANYTONE_RADIOID_H
#define ANYTONE_RADIOID_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class RadioId {
    public:
        RadioId(){}
        ~RadioId(){}

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encode();
        QByteArray encode_D878UVII();
        QByteArray encode_D890UV();
        QByteArray encode_D168UV();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        uint32_t dmr_id = 0;
        QString name = "";
    };
}

#endif