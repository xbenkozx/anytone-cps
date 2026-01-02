#ifndef ANYTONE_MASTER_ID_H
#define ANYTONE_MASTER_ID_H

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace Anytone {
    class MasterId {
    public:
        MasterId(){}
        ~MasterId(){}

        void decode(QByteArray data){
            dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
            used = static_cast<uint8_t>(data.at(0x4)) == 1;
            name = QString(data.mid(5, 0x15));
            name.remove(QChar('\0'));
        }

        QByteArray encode(){
            QByteArray data(0x20, 0);
            data.replace(0, 4, 
                QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
            );
            data[4] = used;
            data.replace(5, 0x1b, 
                name.toUtf8().leftJustified(0x1b, '\0')
            );
            return data;
        }

        uint32_t dmr_id = 0;
        bool used = false;
        QString name = "";
    };
}

#endif