#ifndef ANYTONE_ENCRYPTION_CODE_H
#define ANYTONE_ENCRYPTION_CODE_H

#include <QString>
#include <QDebug>
#include <QDataStream>

namespace Anytone{
    class EncryptionCode{
        public:
        EncryptionCode(){}
        ~EncryptionCode(){}

        void save(QDataStream &ds);
        void load(QDataStream &ds);

        uint8_t index = 0;
        QString id = QString("0000");
        QString key = QString("0000");

    };
}

#endif