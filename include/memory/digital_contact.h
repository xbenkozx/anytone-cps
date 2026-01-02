#ifndef ANYTONE_DIGITAL_CONTACT_H
#define ANYTONE_DIGITAL_CONTACT_H

#include <QByteArray>
#include <QString>
#include <QDebug>

namespace Anytone {
    class DigitalContact {
    public:
        DigitalContact(){}
        ~DigitalContact(){}

        void save(QDataStream &ds);

        void load(QDataStream &ds);

        int id = 0;
        uint32_t radio_id = 0;
        QString callsign = "";
        QString name = "";
        QString city = "";
        QString state = "";
        QString country = "";
        QString remarks = "";
        uint8_t call_type = 0;
        uint8_t call_alert = 0;
    };
}
#endif