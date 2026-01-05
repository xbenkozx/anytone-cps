#ifndef ANYTONE_RECEIVE_GROUP_H
#define ANYTONE_RECEIVE_GROUP_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>
#include "talkgroup.h"

namespace Anytone {
    class ReceiveGroup {
    public:
        ReceiveGroup(){}
        ~ReceiveGroup(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        QString name = "";
        std::vector<Talkgroup*> talkgroups = {};

        QVector<uint16_t> tg_idxs = {};
    };
}

#endif