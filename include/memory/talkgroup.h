#ifndef ANYTONE_TALKGROUP_H
#define ANYTONE_TALKGROUP_H

#include <QByteArray>
#include <QString>
#include <QDataStream>

namespace Anytone {
    class Talkgroup {

    public:
        Talkgroup();
        ~Talkgroup(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint16_t id = 0;
        uint32_t dmr_id = 0;
        uint8_t call_alert = 0;
        QString name = "";
        uint8_t call_type = 0;

    };
}

#endif