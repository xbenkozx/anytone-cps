#include "fm.h"

double Anytone::FM::getFrequencyDouble(){
    return double(frequency) / 10000;
};
QString Anytone::FM::getFrequencyString(){
    return QString::number(getFrequencyDouble(), 'f', 2);
};
void Anytone::FM::setFrequencyString(QString freq_str){
    frequency = int(freq_str.toDouble() * 10000);
}

void Anytone::FM::save(QDataStream &ds){
    ds << id;
    ds << frequency;
    ds << scan_add;

    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }
}
void Anytone::FM::load(QDataStream &ds){
    ds >> frequency;
    ds >> scan_add;

    // qDebug() << frequency << scan_add;

    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }
}