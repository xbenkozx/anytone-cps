#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

#include <QString>
#include <QSettings>
#include "device_types.h"

namespace Anytone{
    enum RadioModel;
}

class UserSettings{
    public:
    static QString comport;
    static QString virtual_file_name;
    static DeviceRWType read_write_options;
    static QString theme;
    static int aprs_alt_type;
    static QString last_save_file;
    static Anytone::RadioModel radio_model;
    static void load();
    static void save();
};

#endif