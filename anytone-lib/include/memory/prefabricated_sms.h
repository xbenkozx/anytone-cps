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
        QByteArray encodeData();
        QByteArray encode_D878UVII();
        QByteArray encode_D890UV();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t id = 0;
        QString text = "";
    };
}

#endif