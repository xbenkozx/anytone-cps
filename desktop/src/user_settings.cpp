#include <QString>
#include <QDir>
#include "user_settings.h"
#include "memory/anytone_memory.h"
#include "memory/channel.h"

QString UserSettings::comport = QString("");
QString UserSettings::virtual_file_name = QString("");
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

void UserSettings::loadDefaults(){
    QFile file(getUserDirectory() + "/defaults.xml");
    if(file.open(QIODevice::ReadOnly)){
        QXmlStreamReader xml(&file);
        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        while (!xml.atEnd() && !xml.hasError()) {
            
            if (token == QXmlStreamReader::StartDocument) {
                token = xml.readNext();
                continue;
            }

            if (token == QXmlStreamReader::StartElement) {
                if(xml.name() == u"Channel") {
                    if(!Anytone::Memory::default_channel) Anytone::Memory::default_channel = new Anytone::Channel();
                    Anytone::Memory::default_channel->load(xml);
                    token = xml.readNext();
                }
            }else{
                token = xml.readNext();
            }
        }
        file.close();

        if (xml.hasError()) {
            qDebug() << "XML error:" << xml.errorString();
        }
    }else{
        Anytone::Memory::setDefaultChannel();
        qDebug() << "Could not save defaults";
    }
}

void UserSettings::saveDefaults(){
    QFile file(getUserDirectory() + "/defaults.xml");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QXmlStreamWriter xml(&file);
        xml.setAutoFormatting(true);
        Anytone::Memory::default_channel->save(xml);
        file.close();
    }else{
        qDebug() << "Could not load defaults";
    }
}