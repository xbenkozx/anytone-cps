#ifndef ANYTONE_ROAMING_ZONE_H
#define ANYTONE_ROAMING_ZONE_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QVector>
#include "roaming_channel.h"

namespace Anytone {
    class RoamingZone {
    public:
        RoamingZone(){}
        ~RoamingZone(){}

        void decode(QByteArray data){
            name = QString(data.mid(0x40, 0x10));
            name.remove(QChar('\0'));
            for(uint8_t ch_idx : data.mid(0, 0x40)){
                if(ch_idx == 0xff) continue;
                channel_idxs.push_back(ch_idx);
            }
        }
        QByteArray encode(){
            QByteArray data(0x50, 0xff);
            auto* bytes = reinterpret_cast<std::uint8_t*>(data.data());
            data.replace(0x40, 0x10, 
                name.toUtf8().leftJustified(16, '\0')
            );
            for(int i=0; i < channels.size(); i++){
                RoamingChannel *rc = channels.at(i);
                if(rc->rx_frequency == 0) continue;
                bytes[i] = rc->id;
            }
            return data;
        }

        int id = 0;
        QString name = "";
        QVector<RoamingChannel*> channels;
        QVector<int> channel_idxs;
    };
}

#endif