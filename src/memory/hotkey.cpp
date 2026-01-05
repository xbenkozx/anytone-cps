#include "hotkey.h"

Anytone::Hotkey::Hotkey(){
    quick_call_list.clear();
    for(int i = 0; i < 4; i++){
        quick_call_list.append(new AnalogQuickCall());
    }

    state_content_list.clear();
    for(int i = 0; i < 32; i++){
        state_content_list.append("");
    }

    key_list.clear();
    for(int i = 0; i < 18; i++){
        HotkeyKey *key = new HotkeyKey();
        key->name = function_key_name.at(i);
        key_list.append(key);
    }
}

void Anytone::Hotkey::decode(QByteArray data){

}
QByteArray Anytone::Hotkey::encode(){
    QByteArray data;

    return data;
}

void Anytone::Hotkey::save(QDataStream &ds){

}
void Anytone::Hotkey::load(QDataStream &ds){

}