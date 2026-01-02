#ifndef ANYTONE_ROAMING_CHANNEL_H
#define ANYTONE_ROAMING_CHANNEL_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include "int.h"

namespace Anytone {
    class RoamingChannel {
    public:
        RoamingChannel(){}
        ~RoamingChannel(){}

        double getRxFrequencyDouble(){
            return double(rx_frequency) / 100000;
        };
        QString getRxFrequencyString(){
            return QString::number(getTxFrequencyDouble(), 'f', 5);
        };
        double getTxFrequencyDouble(){
            return double(tx_frequency) / 100000;
        };
        QString getTxFrequencyString(){
            return QString::number(getTxFrequencyDouble(), 'f', 5);
        };

        void decode(QByteArray data){
            rx_frequency = QString(data.mid(0x0, 4).toHex()).toInt();
            tx_frequency = QString(data.mid(0x4, 4).toHex()).toInt();
            color_code = static_cast<uint8_t>(data.at(0x8));
            slot = static_cast<uint8_t>(data.at(0x9));
            name = QString(data.mid(0xa, 0x10));
            name.remove(QChar('\0'));
        }
        QByteArray encode(){
            QByteArray data(0x20, 0);
            data.replace(0x0, 4, 
                QByteArray::fromHex(QString::number(rx_frequency).rightJustified(8, '0').toUtf8())
            );
            data.replace(0x4, 4, 
                QByteArray::fromHex(QString::number(tx_frequency).rightJustified(8, '0').toUtf8())
            );
            data.replace(0x8, 1, 
                Int::toBytes(slot, 1)
            );
            data.replace(0x9, 1, 
                Int::toBytes(slot, 1)
            );
            data.replace(0xa, 0x10, 
                name.toUtf8().leftJustified(16, '\0')
            );
            
            return data;
        }

        int id = 0;
        uint32_t rx_frequency = 0;
        uint32_t tx_frequency = 0;
        QString name = "";
        uint8_t color_code = 0;
        uint8_t slot = 0;
    };
}

#endif