#include <QString>
#include "user_settings.h"
QString UserSettings::comport = QString("VIRTUAL");
QString UserSettings::virtual_file_name = QString("bin-dump-contacts.bin"); // Hard-set. remove when ready
QString UserSettings::theme = "";
DeviceRWType UserSettings::read_write_options = DeviceRWType::RADIO_DATA;
int UserSettings::aprs_alt_type = 0;

void UserSettings::load(){
    #ifdef _WIN32
    QSettings settings("C:/Users/" + QString(getenv("USERNAME")) + "/anytone-cps.ini", QSettings::IniFormat);
    #else
    QSettings settings("/home/" + QString(getenv("USER")) + "/anytone-cps.settings", QSettings::IniFormat);
    #endif
    UserSettings::comport = settings.value("serial/comport", "VIRTUAL").toString();
    UserSettings::virtual_file_name = settings.value("serial/virt_filename", "").toString();
    UserSettings::theme = settings.value("user/theme", "").toString();
    UserSettings::read_write_options = static_cast<DeviceRWType>(settings.value("user/rwoption", 1).toInt());
}
void UserSettings::save(){
    #ifdef _WIN32
    QSettings settings("C:/Users/" + QString(getenv("USERNAME")) + "/anytone-cps.ini", QSettings::IniFormat);
    #else
    QSettings settings("/home/" + QString(getenv("USER")) + "/anytone-cps.settings", QSettings::IniFormat);
    #endif
    settings.setValue("serial/comport", UserSettings::comport);
    settings.setValue("serial/virt_filename", UserSettings::virtual_file_name);
    settings.setValue("user/theme", UserSettings::theme);
    settings.setValue("user/rwoption", static_cast<uint8_t>(UserSettings::read_write_options));
}