#include "hotkey.h"
#include "talkgroup.h"

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

void Anytone::Hotkey::save(QXmlStreamWriter &xml){
    xml.writeStartElement("HotKeySettings");

    xml.writeStartElement("HotkeyKeyList");
    for(int i = 0; i < key_list.size(); i++){
        xml.writeStartElement("HotkeyKey");
        HotkeyKey *key = key_list.at(i);
        xml.writeAttribute("id", QString::number(i));
        xml.writeAttribute("mode", QString::number(key->mode));
        xml.writeAttribute("menu", QString::number(key->menu));
        xml.writeAttribute("call_type", QString::number(key->call_type));
        xml.writeAttribute("digi_call_type", QString::number(key->digi_call_type));
        xml.writeAttribute("call_obj", QString::number(key->call_obj));
        xml.writeAttribute("content", QString::number(key->content));
        xml.writeEndElement();
    }
    xml.writeEndElement();

    xml.writeStartElement("QuickCallList");
    for(int i = 0; i < quick_call_list.size(); i++){
        xml.writeStartElement("QuickCall");
        xml.writeAttribute("id", QString::number(i));
        xml.writeAttribute("operation_type", QString::number(quick_call_list.at(i)->operation_type));
        xml.writeAttribute("call_id", QString::number(quick_call_list.at(i)->call_id));
        xml.writeEndElement();
    }
    xml.writeEndElement();

    xml.writeStartElement("StateContentList");
    int index = 0;
    for(QString s : state_content_list){
        xml.writeStartElement("StateContent");
        xml.writeAttribute("id", QString::number(index));
        xml.writeAttribute("text", s);
        xml.writeEndElement();
        index++;
    }
    xml.writeEndElement();
    xml.writeEndElement();
}
void Anytone::Hotkey::load(QXmlStreamReader &xml){
    if (xml.name() == "HotKeySettings"){
        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        while (!xml.atEnd() && !xml.hasError()) {
            if(token == QXmlStreamReader::StartElement && (
                xml.name() == "HotkeyKeyList" || xml.name() == "QuickCallList" || xml.name() == "StateContentList"
            )){

            }else if(token == QXmlStreamReader::StartElement && xml.name() == "HotkeyKey"){
                QXmlStreamAttributes attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < key_list.size()) {
                    HotkeyKey *key = key_list.at(idx);
                    if(attributes.hasAttribute("mode"))
                        key->mode = attributes.value("mode").toInt();
                    if(attributes.hasAttribute("menu"))
                        key->menu = attributes.value("menu").toInt();
                    if(attributes.hasAttribute("call_type"))
                        key->call_type = attributes.value("call_type").toInt();
                    if(attributes.hasAttribute("digi_call_type"))
                        key->digi_call_type = attributes.value("digi_call_type").toInt();
                    if(attributes.hasAttribute("call_obj"))
                        key->call_obj = attributes.value("call_obj").toInt();
                    if(attributes.hasAttribute("content"))
                        key->content = attributes.value("content").toInt();
                }
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "QuickCall"){
                QXmlStreamAttributes attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < quick_call_list.size()){
                    AnalogQuickCall *qc = quick_call_list.at(idx);
                    if(attributes.hasAttribute("operation_type"))
                        qc->operation_type =  attributes.value("operation_type").toInt();
                    if(attributes.hasAttribute("call_id"))
                        qc->call_id =  attributes.value("call_id").toInt();
                }
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "StateContent"){
                QXmlStreamAttributes attributes = xml.attributes();
                int idx = attributes.value("id").toInt();
                if(idx < state_content_list.size()) {
                    if(attributes.hasAttribute("text"))
                        state_content_list[idx] =  attributes.value("text").toString();
                }
                    
            }else if(token == QXmlStreamReader::StartElement){
                break;
            }
            token = xml.readNext();
        }
    }
}