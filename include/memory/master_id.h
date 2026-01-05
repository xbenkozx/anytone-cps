#ifndef ANYTONE_MASTER_ID_H
#define ANYTONE_MASTER_ID_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class MasterId {
    public:
        MasterId(){}
        ~MasterId(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint32_t dmr_id = 0;
        bool used = false;
        QString name = "";
    };
}

#endif