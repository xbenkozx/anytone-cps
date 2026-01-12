#ifndef ANYTONE_ENCRYPTION_CODE_H
#define ANYTONE_ENCRYPTION_CODE_H

#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone{
    class EncryptionCode{
        public:
        EncryptionCode(){}
        ~EncryptionCode(){}

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t index = 0;
        QString id = QString("0000");
        QString key = QString("0000");

    };
}

#endif