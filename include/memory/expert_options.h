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

        void decode(QByteArray data){
            full_test_mode = Bit::test(data.at(0x2), 0);
            frequency_mode = static_cast<uint8_t>(data.at(0x3));
            chinese = static_cast<uint8_t>(data.at(0x4)) == 0 && static_cast<uint8_t>(data.at(0x5)) == 0;
            band_select = Bit::test(data.at(0x6), 0);
            band_settings_password = QString(data.mid(0xb, 4));
            radio_type = QString(data.mid(0x10, 7));
            program_password = QString(data.mid(0x28, 4));
            area_code = QString(data.mid(0x2c, 4));
            serial_number = QString(data.mid(0x30, 0x10));
            production_date = QString(data.mid(0x40, 0x10));
            manufacture_code = QString(data.mid(0x50, 8));
            maintenance_date = QString(data.mid(0x60, 0x10));
            dealer_code = QString(data.mid(0x70, 0x10));
            stock_date = QString(data.mid(0x80, 0x10));
            sell_date = QString(data.mid(0x90, 0x10));
            seller = QString(data.mid(0xa0, 0x10));
            maintenance_description = QString(data.mid(0xb0, 0x50));

            this->data = data;

            band_settings_password.remove(QChar('\0'));
            radio_type.remove(QChar('\0'));
            program_password.remove(QChar('\0'));
            area_code.remove(QChar('\0'));
            serial_number.remove(QChar('\0'));
            production_date.remove(QChar('\0'));
            manufacture_code.remove(QChar('\0'));
            maintenance_date.remove(QChar('\0'));
            dealer_code.remove(QChar('\0'));
            stock_date.remove(QChar('\0'));
            sell_date.remove(QChar('\0'));
            seller.remove(QChar('\0'));
            maintenance_description.remove(QChar('\0'));
        }

        QByteArray encode(){
            QByteArray o_data = data;
            auto* bytes = reinterpret_cast<std::uint8_t*>(o_data.data());
            if(full_test_mode) { Bit::set(&bytes[0x2], 0); } else{ Bit::clear(&bytes[0x2], 0); }
            if(band_select) { Bit::set(&bytes[0x6], 0); } else { Bit::clear(&bytes[0x6], 0); }

            o_data[0x3] = frequency_mode;
            o_data[0x4] = !chinese;
            o_data[0x5] = !chinese;
            o_data.replace(0xb, 4, band_settings_password.leftJustified(4, '\0').toUtf8());
            o_data.replace(0x10, 7, radio_type.leftJustified(7, '\0').toUtf8());
            o_data.replace(0x28, 4, program_password.leftJustified(4, '\0').toUtf8());
            o_data.replace(0x2c, 4, area_code.leftJustified(4, '\0').toUtf8());
            o_data.replace(0x30, 0x10, serial_number.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0x40, 0x10, production_date.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0x50, 8, manufacture_code.leftJustified(8, '\0').toUtf8());
            o_data.replace(0x60, 0x10, maintenance_date.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0x70, 0x10, dealer_code.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0x80, 0x10, stock_date.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0x90, 0x10, sell_date.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0xa0, 0x10, seller.leftJustified(0x10, '\0').toUtf8());
            o_data.replace(0xb0, 0x50, maintenance_description.leftJustified(0x50, '\0').toUtf8());
            
            return o_data;
        }

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