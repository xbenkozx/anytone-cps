#include "master_id.h"

void Anytone::MasterId::decode(QByteArray data){
    dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
    used = static_cast<uint8_t>(data.at(0x4)) == 1;
    name = QString(data.mid(5, 0x15));
    name.remove(QChar('\0'));
}
QByteArray Anytone::MasterId::encode(){
    QByteArray data(0x20, 0);
    data.replace(0, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    data[4] = used;
    data.replace(5, 0x1b, 
        name.toUtf8().leftJustified(0x1b, '\0')
    );
    return data;
}

void Anytone::MasterId::save(QDataStream &ds){
    ds << dmr_id;
    ds << used;

    
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void Anytone::MasterId::load(QDataStream &ds){
    ds >> dmr_id;
    ds >> used;

    name.clear();

    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}