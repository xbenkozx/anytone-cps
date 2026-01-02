#ifndef DEVICE_H
#define DEVICE_H

#include <algorithm>
#include <bitset>
#include <map>
#include <limits>
#include <thread>
#include <QSerialPort>
#include <QObject>
#include <QString>
#include <QFile>
#include <QRunnable>
#include <QDeadlineTimer>
#include <QThread>
#include "utils.h"
#include <algorithm>
#include "memory/memory.h"
#include "memory/channel.h"
#include "memory/zone.h"
#include "memory/talkgroup.h"
#include "memory/scanlist.h"
#include "memory/radioid.h"
#include "memory/roaming_zone.h"
#include "memory/roaming_channel.h"
#include "memory/auto_repeater_offset_frequency.h"
#include "memory/fm.h"
#include "memory/digital_contact.h"
#include "memory/optional_settings.h"
#include "memory/alarm_settings.h"
#include "memory/aprs_settings.h"
#include "memory/master_id.h"
#include "memory/gps_roaming.h"
#include "memory/prefabricated_sms.h"
#include "memory/receive_group_call_list.h"
#include "memory/aes_encryption_code.h"
#include "memory/dtmf_settings.h"
#include "memory/tone2_settings.h"
#include "memory/tone5_settings.h"
#include "memory/talk_alias_settings.h"

enum class DeviceRWType : uint8_t {
    NONE = 0,
    RADIO_DATA = 1,
    DIGITAL_CONTACTS = 2,
    BOOT_IMAGE = 4,
    BK1_IMAGE = 8,
    BK2_IMAGE = 16
};

inline DeviceRWType operator&(DeviceRWType a, DeviceRWType b)
{
    return static_cast<DeviceRWType>(
        static_cast<uint8_t>(a) & static_cast<uint8_t>(b)
    );
}

inline DeviceRWType operator|(DeviceRWType a, DeviceRWType b)
{
    return static_cast<DeviceRWType>(
        static_cast<uint8_t>(a) | static_cast<uint8_t>(b)
    );
}

inline DeviceRWType& operator|=(DeviceRWType& a, DeviceRWType b)
{
    a = a | b;
    return a;
}

// Q_DECLARE_FLAGS(DeviceRWTypes, DeviceRWType)
// Q_DECLARE_OPERATORS_FOR_FLAGS(DeviceRWTypes)

enum DeviceStatus{
    STATUS_SUCCESS,
    STATUS_COM_ERROR,
    STATUS_DEVICE_MISMATCH
};

class Device : public QObject 
{
    Q_OBJECT 
public:
    Device() = default;
    virtual ~Device() = default;
    virtual bool connect(QString portname, int baud = 921600){ return false; }
    virtual void endProgMode(){}
    virtual QByteArray readMemoryAddress(int address, int length){ return QByteArray(); }
    virtual void writeMemoryAddress(int address, QByteArray data){};
    virtual std::vector<QString> readDeviceInfo(){ 
        std::vector<QString> info = {"", ""}; 
        return info;
    }
    QByteArray readLocalInformation();
    void writeLocalInformation(QByteArray data);
    QByteArray readMemory(int address, int length){
        QByteArray data;
        for(int addr = address; addr < address + length; addr += 0x10){
            data.append(readMemoryAddress(addr, 0x10));
        }
        return data;
    }
    void writeMemory(int address, QByteArray data){
        int idx = 0;

        for(int addr = address; addr < address + data.size(); addr += 0x10){
            writeMemoryAddress(addr, data.mid(idx * 0x10, 0x10));
            idx++;
        }
    }
    
    void readBootImage();
    void readBk1Image();
    void readBk2Image();

    void writeBootImage();
    void writeBk1Image();
    void writeBk2Image();

    void readRadioData();
    void readDigitalContacts();
    void readOtherData();
    QByteArray getDigitalContactDataBuffer(int offset);
    void readChannelData();
    void readTalkgroupData();
    void readZoneData();
    void readRadioIdData();
    void readScanListData();
    void readFmData();
    void readRoamingChannelData();
    void readRoamingZoneData();
    void readSettings();
    void readGpsRoamingData();
    void readMasterId();
    void readAutoRepeaterFrequencyData();
    void readPrefabricatedSms();
    void readReceiveGroups();
    void readAesEncryptionKeys();
    void readAprsSettings();
    void readToneSettings();

    void writeRadioData();
    void writeDigitalContacts();
    void writeOtherData();
    void writeChannelData();
    void writeZoneData();
    void writeTalkgroupData();
    void writeRadioIdData();
    void writeScanListData();
    void writeFMChannelData();
    void writeGpsRoamingData();
    void writeAutoRepeaterFrequencyData();
    void writeRoamingChannelData();
    void writeRoamingZoneData();
    void writeSettingsData();
    void writeMasterRadioIdData();
    void writePrefabSms();
    void writeAesKeys();
    void writeAprsSettings();
    void writeToneSettings();
    
    bool is_alive = true;
    DeviceRWType read_write_options = DeviceRWType::NONE;
    bool is_write = false;
    QByteArray image_data;
    std::map<int, QByteArray> write_data = {};

signals:
    void finished(const int &result);
    void imageDataReady();
    void update1(const int &val, const int &max, const QString &text);
    void update2(const int &val, const int &max, const QString &text);
};

class VirtualDevice: public Device 
{
    Q_OBJECT
public:
    VirtualDevice(){
        // bin_data = new QByteArray(0x48001D0, static_cast<char>(0xff));
    }
    ~VirtualDevice(){}
    bool connect(QString filepath, int _n = 0) override {
        QFile file(filepath);
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "ERR: Cannot open file";
            return false;
        }

        QTextStream in(&file);
        QString fileContent;
        
        bin_data = new QByteArray((QByteArray)file.readAll());

        file.close();

        return true;
    }
    bool save(QString filepath) {
        QFile file(filepath);
        if (!file.open(QIODevice::WriteOnly)) {
            qDebug() << "ERR: Cannot open file";
            return false;
        }

        qint64 written = file.write(*bin_data); 

        if (written != bin_data->size()) {
            qDebug() << "ERR: Incomplete write";
            file.close();
            return false;
        }

        file.close();
        return true;
    }
    std::vector<QString> readDeviceInfo() override {
        std::vector<QString> data = {QString("ID878UV2"), QString("V101")};
        return data;
    }

    QByteArray readMemoryAddress(int address, int length) override;
    void writeMemoryAddress(int address, QByteArray data) override;
    QByteArray * bin_data;
};

class SerialDevice: public Device 
{
    Q_OBJECT
public:
    SerialDevice(){}
    ~SerialDevice(){}
    bool connect(QString portname, int baud = 921600) override {
        port = new QSerialPort();
        port->setPortName(portname);
        port->setBaudRate(baud);

        if(port->open(QSerialPort::ReadWrite)){
            is_alive = true;
            if(startProgMode()){
                return true;
            }else{
                emit finished(DeviceStatus::STATUS_COM_ERROR);
            }
        }else{
            qDebug() << "COM Error: Could not access com port";
        }

        return false;
    }
    bool startProgMode(){
        port->write(QByteArray("PROGRAM"));

        QByteArray resp = readPort();
        if(resp != QByteArray("QX\x06") && resp != QByteArray("\x00")){
            qDebug() << "ERR: Unexpected response from device (" << resp << ")";
            return false;
        }

        return true;
    }
    void endProgMode() override {
        port->write(QByteArray("END"));
        QByteArray resp = readPort();
    }
    QByteArray readPort(int timeout_ms=1000){
        QDeadlineTimer timer(timeout_ms);
        QByteArray data;

        while(!timer.hasExpired()){
            if(port->waitForReadyRead(50)){
                data.append(port->readAll());
                if(data.endsWith('\x06')){
                    break;
                }
            }
        }

        if(data.size() == 0) is_alive = false;

        return data;
    }
    QByteArray readMemoryAddress(int address, int length) override {
        if(length % 16 != 0) qDebug() << "ERR: Memory Alignment" << QByteArray::number(address).toHex();
        if(!is_alive) return QByteArray();

        QByteArray data;
        while(length > 0){
            int byte_length = std::min(length, 16);

            QByteArray readcmd;
            readcmd.append('R');
            readcmd.append(static_cast<char>(address >> 24));
            readcmd.append(static_cast<char>(address >> 16));
            readcmd.append(static_cast<char>(address >> 8));
            readcmd.append(static_cast<char>(address));
            readcmd.append(static_cast<char>(byte_length));

            port->write(readcmd);

            QByteArray resp = readPort();
            if(resp.size() < 24){
                is_alive = false;
                return QByteArray();
            }

            uint8_t checksum = 0;
            for (int i = 1; i < resp.size() - 2; ++i) {
                checksum += static_cast<uint8_t>(resp.at(i));
            }
            checksum &= 0xFF;

            if(static_cast<uint8_t>(resp.at(22)) != checksum){
                qDebug() << "WARN: Checksum failed.";
            }else if(resp.at(0) != 'W'){
                qDebug() << "WARN: First byte of response not \"W\"";
            }else if(static_cast<uint8_t>(resp.at(23)) != '\x06'){
                qDebug() << "WARN: Last byte of response not 0x06.";
            }

            length -= byte_length;
            address += byte_length;

            data.append(resp.mid(6, 16));
        }

        return data;
    }
    void writeMemoryAddress(int address, QByteArray data){
        if(data.size() != 16) qDebug() << "ERR: Memory Alignment" << QByteArray::number(address).toHex();
        if(!is_alive) return;
        if(address == 0x2fa0010) return;


        QByteArray writecmd;
        writecmd.append('W');
        writecmd.append(static_cast<char>(address >> 24));
        writecmd.append(static_cast<char>(address >> 16));
        writecmd.append(static_cast<char>(address >> 8));
        writecmd.append(static_cast<char>(address));
        writecmd.append(static_cast<char>(16));
        writecmd.append(data);
        uint8_t checksum = 0;
        for (int i = 1; i < writecmd.size(); ++i) {
            checksum += static_cast<uint8_t>(writecmd.at(i));
        }
        checksum &= 0xFF;

        writecmd.append(checksum);
        writecmd.append("\6");

        port->write(writecmd);
        QByteArray resp = readPort();

        if(resp.size() == 0 || (resp.size() > 0 && resp.at(0) != 0x6)){
            qDebug() << "WARN: Last byte of response not 0x06.";
        }

        // if(static_cast<uint8_t>(resp.at(22)) != checksum){
        //     qDebug() << "WARN: Checksum failed.";
        // }else if(resp.at(0) != 'W'){
        //     qDebug() << "WARN: First byte of response not \"W\"";
        // }else if(static_cast<uint8_t>(resp.at(23)) != '\x06'){
        //     qDebug() << "WARN: Last byte of response not 0x06.";
        // }
    }
    std::vector<QString> readDeviceInfo() override {
        port->write(QByteArray("\x02"));
        QByteArray resp = readPort();
        QString radio_model = QString(resp.mid(0x0, 0x8));
        QString radio_version = QString(resp.mid(0x9, 5));
        radio_model.remove(QChar('\0'));
        radio_version.remove(QChar('\0'));
        std::vector<QString> data = {radio_model, radio_version};
        return data;
    }
    QSerialPort *port;
};

class SerialWorker : public QObject, public QRunnable {
    Q_OBJECT

public:
    
    SerialWorker(){}
    ~SerialWorker(){}
    void setComport(QString comport){
        this->comport = comport;
    }
    void setVirtualFile(QString filepath){
        bin_filepath = filepath;
    }
    void setReadWriteOptions(DeviceRWType rw_options){
        this->rw_options = rw_options;
    }
    void setImageData(QByteArray image_data){
        this->image_data = image_data;
    }

    void run();
    
    QString comport;
    QString bin_filepath;
    QByteArray image_data;
    Device *device;
    bool is_write = false;
    int connection_attempt = 0;
    DeviceRWType rw_options = DeviceRWType::NONE;

private slots:
    void done();

signals:
    void finished(const int &result);
    void imageDataReady(const QByteArray &image_data);
    void update1(const int &val, const int &max, const QString &text);
    void update2(const int &val, const int &max, const QString &text);
};

#endif