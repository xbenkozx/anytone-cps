#ifndef ANYTONE_PREFABRICATED_SMS_H
#define ANYTONE_PREFABRICATED_SMS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone {
    class PrefabricatedSms {
    public:
        PrefabricatedSms(){}
        ~PrefabricatedSms(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t id = 0;
        QString text = "";
    };
}

#endif