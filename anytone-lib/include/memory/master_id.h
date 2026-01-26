#ifndef ANYTONE_MASTER_ID_H
#define ANYTONE_MASTER_ID_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

namespace Anytone {
    class MasterId {
    public:
        MasterId(){}
        ~MasterId(){}

        void decode(QByteArray data);
        void decode_D878UVII(QByteArray data);
        void decode_D890UV(QByteArray data);
        void decode_D168UV(QByteArray data);
        QByteArray encodeData();
        QByteArray encode_D878UVII();
        QByteArray encode_D890UV();

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        uint32_t dmr_id = 0;
        bool used = false;
        QString name = "";
    };
}

#endif