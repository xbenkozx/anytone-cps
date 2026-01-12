#ifndef ANYTONE_TALKGROUP_H
#define ANYTONE_TALKGROUP_H

#include <QByteArray>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class Talkgroup {

    public:
        Talkgroup();
        ~Talkgroup(){}

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint16_t id = 0;
        uint32_t dmr_id = 0;
        uint8_t call_alert = 0;
        QString name = "";
        uint8_t call_type = 0;

    };
}

#endif