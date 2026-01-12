#ifndef INT_UTILS_H
#define INT_UTILS_H

#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QDebug>

enum Endian{
    Little,
    Big
};

class Int {
public:
    static uint32_t fromBytes(QByteArray data, Endian endian = Endian::Little){
        QByteArray d = QByteArray(data);
        if(d.size() < 4){
            if(endian == Endian::Big){
                d.prepend(QByteArray(4 - d.size(), '\0'));
            }else{
                d.append(QByteArray(4 - d.size(), '\0'));
            }
        }
        
        QDataStream stream(&d, QIODevice::ReadOnly);
        stream.setByteOrder(endian == Endian::Big ? QDataStream::BigEndian : QDataStream::LittleEndian);

        uint32_t i = 0;
        stream >> i;
        return uint32_t(i);
    }

    static QByteArray toBytes(int value, int size, Endian endian = Endian::Little){
        QByteArray d;
        QDataStream stream(&d, QIODevice::WriteOnly);
        stream.setByteOrder(endian == Endian::Big ? QDataStream::BigEndian : QDataStream::LittleEndian);
        switch(size){
            case 1:
                stream << static_cast<uint8_t>(value);
                break;
            case 2:
                stream << static_cast<uint16_t>(value);
                break;
            case 4:
                stream << static_cast<uint32_t>(value);
                break;
            default:
                qDebug() << "Invalid size";
                break;
        };
        
        return d;
    }
};

#endif