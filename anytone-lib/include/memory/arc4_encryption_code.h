#ifndef ANYTONE_ARC4_ENCRYPTION_CODE_H
#define ANYTONE_ARC4_ENCRYPTION_CODE_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone{
    class Arc4EncryptionCode{
        public:
        Arc4EncryptionCode(){}
        ~Arc4EncryptionCode(){}

        QByteArray encode();
        void decode(QByteArray data);
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t index = 0;
        uint8_t id = 0;
        QString key = QString("");
    };
}

#endif