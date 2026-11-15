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
    static QString last_dir;
    // Directory a file dialog should start in: the last one used, else the folder of the last
    // codeplug, else the Documents folder.
    static QString dialogDir();
    // Same for the codeplug (.atd) dialogs: the folder of the last codeplug opened or saved.
    static QString codeplugDir();
    // Remember the folder of a file the user just picked in a file dialog.
    static void rememberFile(const QString &filepath);
    static Anytone::RadioModel radio_model;
    static void load();
    static void save();
    static QString getUserDirectory();
    static void saveDefaults();
    static void loadDefaults();
};

#endif