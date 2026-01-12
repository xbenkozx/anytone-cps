#ifndef ANYTONE_AES_ENCRYPTION_CODE_H
#define ANYTONE_AES_ENCRYPTION_CODE_H

#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone{
    class AesEncryptionCode{
        public:
        AesEncryptionCode(){}
        ~AesEncryptionCode(){}

        QByteArray encode();
        void decode(QByteArray data);
        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint8_t index = 0;
        uint8_t id = 0;
        QString key = QString("");
        uint8_t key_length = 0;
    };
}

#endif