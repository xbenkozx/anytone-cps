#ifndef ANYTONE_EXPERT_OPTIONS_H
#define ANYTONE_EXPERT_OPTIONS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include "utils.h"

namespace Anytone {
    class ExpertOptions {
    public:
        ExpertOptions(){}
        ~ExpertOptions(){}

        void decode(QByteArray data);
        QByteArray encode();

        QByteArray data;
        bool band_select = false;
        bool full_test_mode = false;
        bool chinese = false;
        QString area_code = "";
        QString manufacture_code = "";
        QString radio_type = "";
        QString band_settings_password = "";
        uint8_t frequency_mode = 0;
        QString program_password = "";
        QString serial_number = "";
        QString production_date = "";
        QString maintenance_date = "";
        QString maintenance_description = "";
        QString dealer_code = "";
        QString stock_date = "";
        QString sell_date = "";
        QString seller = "";
    };
}

#endif