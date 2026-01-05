#ifndef ANYTONE_RADIOID_H
#define ANYTONE_RADIOID_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class RadioId {
    public:
        RadioId(){}
        ~RadioId(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        uint32_t dmr_id = 0;
        QString name = "";
    };
}

#endif