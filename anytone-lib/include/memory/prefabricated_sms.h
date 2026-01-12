#ifndef ANYTONE_PREFABRICATED_SMS_H
#define ANYTONE_PREFABRICATED_SMS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class PrefabricatedSms {
    public:
        PrefabricatedSms(){}
        ~PrefabricatedSms(){}

        void decode(QByteArray data);
        QByteArray encode();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        QString text = "";
    };
}

#endif