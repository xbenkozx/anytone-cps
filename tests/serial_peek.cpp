// Read-only radio check: reads the device id and 16 bytes at given addresses.
// Usage: serial-peek <port> <hex-address> [<hex-address> ...]
// Sends only PROGRAM, the read command and END. Nothing is written to the radio.
#include <QCoreApplication>
#include <QDebug>
#include "device.h"

int main(int argc, char **argv){
    QCoreApplication app(argc, argv);
    if(argc < 3){ qCritical() << "usage: serial-peek <port> <hex-addr>..."; return 2; }
    SerialDevice d;
    if(!d.connect(argv[1])){ qCritical() << "cannot connect"; return 1; }
    const auto info = d.readDeviceInfo();
    qInfo().noquote() << "device:" << info[0] << info[1];
    for(int i = 2; i < argc; i++){
        const int addr = QString(argv[i]).toInt(nullptr, 16);
        const QByteArray data = d.readMemoryAddress(addr, 0x10);
        qInfo().noquote() << QString("0x%1:").arg(addr, 0, 16) << data.toHex(' ');
    }
    d.endProgMode();
    return 0;
}
