#include "memory/scanlist.h"
#include "memory/anytone_memory.h"
using namespace Anytone;
void ScanList::decode(QByteArray data){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            decode_D878UVII(data);
            break;
        case Anytone::RadioModel::D890UV_FW103:
            decode_D890UV(data);
            break;
        case Anytone::RadioModel::D168UV:
            decode_D168UV(data);
            break;
        default:
        break;
    }
}
void ScanList::decode_D878UVII(QByteArray data){
    priority_channel_select = static_cast<uint8_t>(data.at(0x1));
    priority_channel_1 = Int::fromBytes(data.mid(0x2, 2));
    priority_channel_2 = Int::fromBytes(data.mid(0x4, 2));
    lookback_time_a = Int::fromBytes(data.mid(0x6, 2)) - 5;
    lookback_time_b = Int::fromBytes(data.mid(0x8, 2)) - 5;
    dropout_delay_time = Int::fromBytes(data.mid(0xa, 2)) - 1;
    dwell_time = Int::fromBytes(data.mid(0xc, 2)) - 1;
    revert_channel = static_cast<uint8_t>(data.at(0xe));
    name = QString(data.mid(0xf, 0x10));
    name.remove(QChar('\0'));
    
    for(int i = 0; i < 100; i+=2){
        int ch_idx = Int::fromBytes(data.mid(0x20 + i, 2));
        if(ch_idx != 0xffff) channel_member_idxs.push_back(ch_idx);
    }
}
void ScanList::decode_D890UV(QByteArray data){
    priority_channel_select = static_cast<uint8_t>(data.at(0x1));
    priority_channel_1 = Int::fromBytes(data.mid(0x2, 2));
    priority_channel_2 = Int::fromBytes(data.mid(0x4, 2));

    lookback_time_a = Int::fromBytes(data.mid(0x6, 2)) - 5;
    lookback_time_b = Int::fromBytes(data.mid(0x8, 2)) - 5;
    dropout_delay_time = Int::fromBytes(data.mid(0xa, 2)) - 1;
    dwell_time = Int::fromBytes(data.mid(0xc, 2)) - 1;
    revert_channel = static_cast<uint8_t>(data.at(0x94));
    name = QString(data.mid(0xe, 0x20));
    name.remove(QChar('\0'));
    
    for(int i = 0; i < 100; i+=2){
        int ch_idx = Int::fromBytes(data.mid(0x30 + i, 2));
        if(ch_idx != 0xffff) channel_member_idxs.push_back(ch_idx);
    }
}
void ScanList::decode_D168UV(QByteArray data){

}

QByteArray ScanList::encode(){
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            return encode_D878UVII();
        case Anytone::RadioModel::D890UV_FW103:
            return encode_D890UV();
        case Anytone::RadioModel::D168UV:
            // return encode_D168UV();
        default:
            return QByteArray(0x80, 0);
        break;
    }
}
QByteArray ScanList::encode_D878UVII(){
    QByteArray data(0x20, 0);
    QByteArray channel_data(0x64, 0xff);

    data[0x1] = priority_channel_select;
    data.replace(0x2, 2, 
        Int::toBytes(priority_channel_1, 2)
    );
    data.replace(0x4, 2, 
        Int::toBytes(priority_channel_2, 2)
    );
    data.replace(0x6, 2, 
        Int::toBytes(lookback_time_a + 5, 2)
    );
    data.replace(0x8, 2, 
        Int::toBytes(lookback_time_b + 5, 2)
    );
    data.replace(0xa, 2, 
        Int::toBytes(dropout_delay_time + 1, 2)
    );
    data.replace(0xc, 2, 
        Int::toBytes(dwell_time + 1, 2)
    );
    data[0xe] = revert_channel;
    
    data.replace(0xf, 0x10, 
        name.toUtf8().leftJustified(16, '\0')
    );

    for(int i=0; i < channels.size(); i++){
        Channel *ch = channels.at(i);
        channel_data.replace(i*2, 2, 
            Int::toBytes(ch->id, 2)
        );
    }
    
    data.append(channel_data);

    return data.leftJustified(0x90, 0);
}
QByteArray ScanList::encode_D890UV(){
    QByteArray data(0x30, 0);
    QByteArray channel_data(0x64, 0xff);

    data[0x1] = priority_channel_select;
    
    data.replace(0x2, 2, 
        Int::toBytes(priority_channel_1, 2)
    );
    data.replace(0x4, 2, 
        Int::toBytes(priority_channel_2, 2)
    );
    data.replace(0x6, 2, 
        Int::toBytes(lookback_time_a + 5, 2)
    );
    data.replace(0x8, 2, 
        Int::toBytes(lookback_time_b + 5, 2)
    );
    data.replace(0xa, 2, 
        Int::toBytes(dropout_delay_time + 1, 2)
    );
    data.replace(0xc, 2, 
        Int::toBytes(dwell_time + 1, 2)
    );

    data.replace(0xe, 0x20, 
        Format::wideCharString(name).leftJustified(0x20, '\0')
    );

    for(int i=0; i < channels.size(); i++){
        Channel *ch = channels.at(i);
        channel_data.replace(i*2, 2, 
            Int::toBytes(ch->id, 2)
        );
    }
    data.append(channel_data);
    data = data.leftJustified(0xd0, 0);

    data[0x94] = revert_channel;

    return data;
}

void Anytone::ScanList::save(QXmlStreamWriter &xml){
    xml.writeStartElement("ScanList");
    xml.writeAttribute("id", QString::number(id));
    xml.writeAttribute("scan_mode", QString::number(scan_mode));
    xml.writeAttribute("priority_channel_select", QString::number(priority_channel_select));
    xml.writeAttribute("priority_channel_1", QString::number(priority_channel_1));
    xml.writeAttribute("priority_channel_2", QString::number(priority_channel_2));
    xml.writeAttribute("revert_channel", QString::number(revert_channel));
    xml.writeAttribute("lookback_time_a", QString::number(lookback_time_a));
    xml.writeAttribute("lookback_time_b", QString::number(lookback_time_b));
    xml.writeAttribute("dropout_delay_time", QString::number(dropout_delay_time));
    xml.writeAttribute("dwell_time", QString::number(dwell_time));
    xml.writeAttribute("name", name);
    QString ch_idx_str;
    for(Channel *ch : channels){
        ch_idx_str += "|" + QString::number(ch->id);
    }
    ch_idx_str.removeFirst();
    xml.writeAttribute("channel_list", ch_idx_str);
    xml.writeEndElement();
}
void Anytone::ScanList::load(QXmlStreamReader &xml){
    if (xml.name() == "ScanList"){
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("scan_mode"))
            scan_mode = attributes.value("scan_mode").toInt();
        if(attributes.hasAttribute("priority_channel_select"))
            priority_channel_select = attributes.value("priority_channel_select").toInt();
        if(attributes.hasAttribute("priority_channel_1"))
            priority_channel_1 = attributes.value("priority_channel_1").toInt();
        if(attributes.hasAttribute("priority_channel_2"))
            priority_channel_2 = attributes.value("priority_channel_2").toInt();
        if(attributes.hasAttribute("revert_channel"))
            revert_channel = attributes.value("revert_channel").toInt();
        if(attributes.hasAttribute("lookback_time_a"))
            lookback_time_a = attributes.value("lookback_time_a").toInt();
        if(attributes.hasAttribute("lookback_time_b"))
            lookback_time_b = attributes.value("lookback_time_b").toInt();
        if(attributes.hasAttribute("dropout_delay_time"))
            dropout_delay_time = attributes.value("dropout_delay_time").toInt();
        if(attributes.hasAttribute("dwell_time"))
            dwell_time = attributes.value("dwell_time").toInt();
        
        if(attributes.hasAttribute("name"))
            name = attributes.value("name").toString();
        if(attributes.hasAttribute("channel_list")){
            QString ch_idx_str = attributes.value("channel_list").toString();
            for(QString idx : ch_idx_str.split("|")){
                channel_member_idxs.append(static_cast<uint16_t>(idx.toInt()));
            }
        }
    }
}