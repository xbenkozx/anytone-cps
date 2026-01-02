#ifndef ANYTONE_PREFABRICATED_SMS_H
#define ANYTONE_PREFABRICATED_SMS_H

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace Anytone {
    class PrefabricatedSms {
    public:
        PrefabricatedSms(){}
        ~PrefabricatedSms(){}

        void decode(QByteArray data){
            text = QString(data);
            text.remove(QChar('\0'));
        }

        QByteArray encode(){
            return text.toUtf8().leftJustified(0xd0, '\0');
        }

        int id = 0;
        QString text = "";
    };
}

#endif