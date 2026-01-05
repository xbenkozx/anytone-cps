#include "radioid.h"

void Anytone::RadioId::decode(QByteArray data){
    dmr_id = QString(data.mid(0x0, 0x4).toHex()).toInt();
    name = QString(data.mid(5, 26));
    name.remove(QChar('\0'));
}

QByteArray Anytone::RadioId::encode(){
    QByteArray data(0x20, 0);
    data.replace(0x0, 4, 
        QByteArray::fromHex(QString::number(dmr_id).rightJustified(8, '0').toUtf8())
    );
    data.replace(5, 26, 
        name.toUtf8().leftJustified(26, '\0')
    );

    return data;
}

void Anytone::RadioId::save(QDataStream &ds){
    ds << id;
    ds << dmr_id;
    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void Anytone::RadioId::load(QDataStream &ds){
    name.clear();
    
    ds >> dmr_id;
    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}