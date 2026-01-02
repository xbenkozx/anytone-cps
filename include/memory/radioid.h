#ifndef ANYTONE_RADIOID_H
#define ANYTONE_RADIOID_H

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace Anytone {
    class RadioId {
    public:
        RadioId(){}
        ~RadioId(){}

        void decode(QByteArray data){
            dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
            name = QString(data.mid(5, 26));
            name.remove(QChar('\0'));
        }

        QByteArray encode(){
            QByteArray data(0x20, 0);
            data.replace(0x0, 4, 
                QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
            );
            data.replace(5, 26, 
                name.toUtf8().leftJustified(26, '\0')
            );

            return data;
        }

        int id = 0;
        uint32_t dmr_id = 0;
        QString name = "";
    };
}

#endif