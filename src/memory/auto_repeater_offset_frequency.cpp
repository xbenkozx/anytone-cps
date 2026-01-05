#include "auto_repeater_offset_frequency.h"

double Anytone::AutoRepeaterOffsetFrequency::getFrequencyDouble(){
    return double(frequency) / 100000;
};

QString Anytone::AutoRepeaterOffsetFrequency::getFrequencyString(){
    return QString::number(getFrequencyDouble(), 'f', 3);
};
void Anytone::AutoRepeaterOffsetFrequency::save(QDataStream &ds){
    ds << id;
    ds << frequency;
}
void Anytone::AutoRepeaterOffsetFrequency::load(QDataStream &ds){
    ds >> frequency;
}