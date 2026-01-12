#ifndef ANYTONE_SCANLIST_H
#define ANYTONE_SCANLIST_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "int.h"
#include "channel.h"

namespace Anytone {
    class Channel;
    
    class ScanList{

public:
        ScanList(){}
        ~ScanList(){}

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        QString name = "";
        QVector<Channel*> channels = {};
        uint8_t scan_mode = 0;
        uint8_t priority_channel_select = 0;
        uint16_t priority_channel_1 = 0xffff;
        uint16_t priority_channel_2 = 0xffff;
        uint8_t revert_channel = 0;
        uint8_t lookback_time_a = 0;
        uint8_t lookback_time_b = 0;
        uint8_t dropout_delay_time = 0;
        uint8_t dwell_time = 0;

        QVector<int> channel_member_idxs;
    };

}

#endif