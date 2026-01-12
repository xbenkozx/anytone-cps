#ifndef ANYTONE_RECEIVE_GROUP_H
#define ANYTONE_RECEIVE_GROUP_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "talkgroup.h"

namespace Anytone {
    class ReceiveGroup {
    public:
        ReceiveGroup(){}
        ~ReceiveGroup(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        QString name = "";
        std::vector<Talkgroup*> talkgroups = {};

        QVector<uint16_t> tg_idxs = {};
    };
}

#endif