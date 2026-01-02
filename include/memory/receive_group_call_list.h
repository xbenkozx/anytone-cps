#ifndef ANYTONE_RECEIVE_GROUP_H
#define ANYTONE_RECEIVE_GROUP_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include "talkgroup.h"

namespace Anytone {
    class ReceiveGroup {
    public:
        ReceiveGroup(){}
        ~ReceiveGroup(){}

        void decode(QByteArray data){

        }

        int id = 0;
        QString name = "";
        std::vector<Talkgroup*> talkgroups = {};

        std::vector<uint16_t> tg_idxs = {};
    };
}

#endif