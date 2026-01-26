#include <QString>
#include <QDir>
#include "user_settings.h"
#include "memory/anytone_memory.h"
QString UserSettings::comport = QString("VIRTUAL");
QString UserSettings::virtual_file_name = QString("bin-dump-contacts.bin"); // Hard-set. remove when ready
QString UserSettings::theme = "";
DeviceRWType UserSettings::read_write_options = DeviceRWType::RADIO_DATA;
int UserSettings::aprs_alt_type = 0;
QString UserSettings::last_save_file = "";
Anytone::RadioModel UserSettings::radio_model = Anytone::RadioModel::None;

QString UserSettings::getUserDirectory(){
    #ifdef _WIN32
    QString dir = "C:/Users/" + QString(getenv("USERNAME")) + "/anytone-cps/";
    #else
    QString dir = "/home/" + QString(getenv("USER")) + "/anytone-cps/";
    #endif

    QDir dirObj;

    if (!dirObj.mkpath(dir)) {
        qDebug() << "Failed to create directory:" << dir;
    }

    return dir;
}

void UserSettings::load(){
    QSettings settings(getUserDirectory() + "/settings.ini", QSettings::IniFormat);
    UserSettings::comport = settings.value("serial/comport", "VIRTUAL").toString();
    UserSettings::virtual_file_name = settings.value("serial/virt_filename", "").toString();
    UserSettings::theme = settings.value("user/theme", "").toString();
    UserSettings::read_write_options = static_cast<DeviceRWType>(settings.value("user/rwoption", 1).toInt());
    UserSettings::last_save_file = settings.value("user/save_file", "").toString();
    UserSettings::radio_model = static_cast<Anytone::RadioModel>(settings.value("user/radio_model", 0).toInt());
}
void UserSettings::save(){
    QSettings settings(getUserDirectory() + "/settings.ini", QSettings::IniFormat);
    settings.setValue("serial/comport", UserSettings::comport);
    settings.setValue("serial/virt_filename", UserSettings::virtual_file_name);
    settings.setValue("user/theme", UserSettings::theme);
    settings.setValue("user/rwoption", static_cast<uint8_t>(UserSettings::read_write_options));
    settings.setValue("user/save_file", UserSettings::last_save_file);
    settings.setValue("user/radio_model", static_cast<uint8_t>(UserSettings::radio_model));
}