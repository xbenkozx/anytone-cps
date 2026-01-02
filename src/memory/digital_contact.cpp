#include "digital_contact.h"

void Anytone::DigitalContact::save(QDataStream &ds){
    ds << id;
    ds << radio_id;

    uint8_t callsign_len = callsign.size();
    ds << callsign_len;
    for(char c : callsign.toStdString()){
        ds << c;
    }

    uint8_t name_len = name.size();
    ds << name_len;
    for(char c : name.toStdString()){
        ds << c;
    }

    uint8_t city_len = city.size();
    ds << city_len;
    for(char c : city.toStdString()){
        ds << c;
    }

    uint8_t state_len = state.size();
    ds << state_len;
    for(char c : state.toStdString()){
        ds << c;
    }

    uint8_t country_len = country.size();
    ds << country_len;
    for(char c : country.toStdString()){
        ds << c;
    }

    uint8_t remarks_len = remarks.size();
    ds << remarks_len;
    for(char c : remarks.toStdString()){
        ds << c;
    }
    
    ds << call_type;
    ds << call_alert;
}

void Anytone::DigitalContact::load(QDataStream &ds){

    ds >> radio_id;

    uint8_t callsign_size;
    ds >> callsign_size;
    for(int i = 0; i < callsign_size; i++){
        char c;
        ds >> c;
        callsign.append(c);
    }

    uint8_t name_size;
    ds >> name_size;
    for(int i = 0; i < name_size; i++){
        char c;
        ds >> c;
        name.append(c);
    }

    uint8_t city_size;
    ds >> city_size;
    for(int i = 0; i < city_size; i++){
        char c;
        ds >> c;
        city.append(c);
    }

    uint8_t state_size;
    ds >> state_size;
    for(int i = 0; i < state_size; i++){
        char c;
        ds >> c;
        state.append(c);
    }

    uint8_t country_size;
    ds >> country_size;
    for(int i = 0; i < country_size; i++){
        char c;
        ds >> c;
        country.append(c);
    }

    uint8_t remarks_size;
    ds >> remarks_size;
    for(int i = 0; i < remarks_size; i++){
        char c;
        ds >> c;
        remarks.append(c);
    }

    ds >> call_type;
    ds >> call_alert;
}