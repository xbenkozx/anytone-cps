#include "memory/at_memory.h"
#include "memory/channel.h"
#include "memory/zone.h"
#include "memory/talkgroup.h"
#include "memory/scanlist.h"
#include "memory/radioid.h"
#include "memory/roaming_zone.h"
#include "memory/roaming_channel.h"
#include "memory/auto_repeater_offset_frequency.h"
#include "memory/fm.h"
#include "memory/digital_contact.h"
#include "memory/gps_roaming.h"
#include "prefabricated_sms.h"
#include "receive_group_call_list.h"
#include "aes_encryption_code.h"
#include "arc4_encryption_code.h"
#include "encryption_code.h"
#include "dtmf_settings.h"
#include "tone2_settings.h"
#include "tone5_settings.h"
#include "talk_alias_settings.h"
#include "analog_address.h"

using namespace Anytone;

OptionalSettings* Memory::optional_settings = nullptr;
Hotkey* Memory::hotkey = nullptr;
AlarmSettings* Memory::alarm_settings = nullptr;
AprsSettings* Memory::aprs_settings = nullptr;
DTMFSettings* Memory::dtmf_settings = nullptr;
Tone2Settings* Memory::tone2_settings = nullptr;
Tone5Settings* Memory::tone5_settings = nullptr;
MasterId* Memory::master_radio_id = nullptr;
TalkAliasSettings* Memory::talk_alias_settings = nullptr;

uint8_t Memory::radio_mode = 0;
RadioModel Memory::radio_model = RadioModel::None;
QString Memory::radio_band = "UHF{400 - 480 MHz}\nVHF{136 - 174 MHz}";
QString Memory::radio_version = "V1.01";

QVector<Channel*> Memory::channels = {};
QVector<Zone*> Memory::zones = {};
QVector<Talkgroup*> Memory::talkgroups = {};
QVector<ScanList*> Memory::scanlists = {};
QVector<RadioId*> Memory::radioids = {};
QVector<RoamingChannel*> Memory::roaming_channels = {};
QVector<RoamingZone*> Memory::roaming_zones = {};
QVector<AutoRepeaterOffsetFrequency*> Memory::ar_offset_frequencies = {};
QVector<FM*> Memory::fm_channels = {};
QVector<DigitalContact*> Memory::digital_contacts = {};
QVector<GpsRoaming*> Memory::gps_roaming_list = {};
QVector<PrefabricatedSms*> Memory::prefabricated_sms_list = {};
QVector<ReceiveGroup*> Memory::receive_group_call_lists = {};
QVector<AesEncryptionCode*> Memory::aes_encryption_keys = {};
QVector<Arc4EncryptionCode*> Memory::arc4_encryption_keys = {};
QVector<EncryptionCode*> Memory::encryption_keys = {};
QVector<AnalogAddress*> Memory::analog_addresses = {};

// **********************
// Save File Save
// **********************
void Memory::saveData(QXmlStreamWriter &xml){
    xml.writeStartDocument();
    xml.writeStartElement("Codeplug");
    saveAesEncryptionCodes(xml);
    saveAprsSettings(xml);
    saveAlarmSettings(xml);
    saveAnalogAddresses(xml);
    saveArc4EncryptionCodes(xml);
    saveAutoRepeaterOffsets(xml);
    saveChannels(xml);
    saveDtmfSettings(xml);
    saveEncryptionCodes(xml);
    saveFm(xml);
    saveGpsRoaming(xml);
    saveHotKey(xml);
    saveMasterId(xml);
    saveOptionalSettings(xml);
    savePrefabricatedSms(xml);
    saveRadioIds(xml);
    saveReceiveGroupCallList(xml);
    saveRoamingChannel(xml);
    saveRoamingZone(xml);
    saveScanList(xml);
    saveTalkerAliasSettings(xml);
    saveTalkgroups(xml);
    saveTone2Settings(xml);
    saveTone5Settings(xml);
    saveZones(xml);
    saveDigitalContacts(xml);
    xml.writeEndElement();
    xml.writeEndDocument();
}
void Memory::saveAesEncryptionCodes(QXmlStreamWriter &xml){
    xml.writeStartElement("AESEncryptionList");
    for(AesEncryptionCode *item : Memory::aes_encryption_keys){
        if(item->id > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveAprsSettings(QXmlStreamWriter &xml){
    aprs_settings->save(xml);
}
void Memory::saveAlarmSettings(QXmlStreamWriter &xml){
    alarm_settings->save(xml);
}
void Memory::saveAnalogAddresses(QXmlStreamWriter &xml){
    xml.writeStartElement("AnalogAddressList");
    for(AnalogAddress *item : Memory::analog_addresses){
        if(item->number > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveArc4EncryptionCodes(QXmlStreamWriter &xml){
    xml.writeStartElement("ARC4EncryptionList");
    for(Arc4EncryptionCode *item : Memory::arc4_encryption_keys){
        if(item->id > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveAutoRepeaterOffsets(QXmlStreamWriter &xml){
    xml.writeStartElement("AutoRepeaterList");
    for(AutoRepeaterOffsetFrequency *item : Memory::ar_offset_frequencies){
        if(item->frequency > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveChannels(QXmlStreamWriter &xml){
    xml.writeStartElement("ChannelList");
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency > 0){
            ch->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveDtmfSettings(QXmlStreamWriter &xml){
    dtmf_settings->save(xml);
}
void Memory::saveEncryptionCodes(QXmlStreamWriter &xml){
    xml.writeStartElement("EncryptionCodeList");
    for(EncryptionCode *item : Memory::encryption_keys){
        item->save(xml);
    }
    xml.writeEndElement();
}
void Memory::saveFm(QXmlStreamWriter &xml){
    xml.writeStartElement("FMList");
    for(FM *item : Memory::fm_channels){
        if(item->frequency > 0){
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveGpsRoaming(QXmlStreamWriter &xml){
    xml.writeStartElement("GPSRoamingList");
    for(GpsRoaming *item : Memory::gps_roaming_list){
        item->save(xml);
    }
    xml.writeEndElement();
}
void Memory::saveHotKey(QXmlStreamWriter &xml){
    hotkey->save(xml);
}
void Memory::saveMasterId(QXmlStreamWriter &xml){
    master_radio_id->save(xml);
}
void Memory::saveOptionalSettings(QXmlStreamWriter &xml){
    optional_settings->save(xml);
}
void Memory::savePrefabricatedSms(QXmlStreamWriter &xml){
    xml.writeStartElement("PrefabricatedSmsList");
    for(PrefabricatedSms *item : Memory::prefabricated_sms_list){
        if(item->text.size() > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveRadioIds(QXmlStreamWriter &xml){
    xml.writeStartElement("RadioIdList");
    for(RadioId *item : Memory::radioids){
        if(item->dmr_id > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveReceiveGroupCallList(QXmlStreamWriter &xml){
    xml.writeStartElement("ReceiveGroupList");
    for(ReceiveGroup *item : Memory::receive_group_call_lists){
        if(item->talkgroups.size() > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveRoamingChannel(QXmlStreamWriter &xml){
    xml.writeStartElement("RoamingChannelList");
    for(RoamingChannel *item : Memory::roaming_channels){
        if(item->rx_frequency > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveRoamingZone(QXmlStreamWriter &xml){
    xml.writeStartElement("RoamingZoneList");
    for(RoamingZone *item : Memory::roaming_zones){
        if(item->channels.size() > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveScanList(QXmlStreamWriter &xml){
    xml.writeStartElement("ScanlistList");
    for(ScanList *item : Memory::scanlists){
        if(item->channels.size() > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveTalkerAliasSettings(QXmlStreamWriter &xml){
    talk_alias_settings->save(xml);
}
void Memory::saveTalkgroups(QXmlStreamWriter &xml){
    xml.writeStartElement("TalkgroupList");
    for(Talkgroup *item : Memory::talkgroups){
        if(item->dmr_id > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveTone2Settings(QXmlStreamWriter &xml){
    tone2_settings->save(xml);
}
void Memory::saveTone5Settings(QXmlStreamWriter &xml){
    tone5_settings->save(xml);
}
void Memory::saveZones(QXmlStreamWriter &xml){
    xml.writeStartElement("ZoneList");
    for(Zone *item : Memory::zones){
        if(item->channels.size() > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveDigitalContacts(QXmlStreamWriter &xml){
    xml.writeStartElement("DigitalContactList");
    for(DigitalContact *item : Memory::digital_contacts){
        if(item->radio_id > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}


// **********************
// Save File Load
// **********************
void Memory::loadData(QXmlStreamReader &xml){
    QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
    while (!xml.atEnd() && !xml.hasError()) {
        
        if (token == QXmlStreamReader::StartDocument) {
            token = xml.readNext();
            continue;
        }

        if (token == QXmlStreamReader::StartElement) {
            if(xml.name() == u"AESEncryptionList") {
                loadAesEncryptionCodes(xml);
            }else if(xml.name() == u"APRSSettings") {
                aprs_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"AlarmSettings") {
                alarm_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"AnalogAddressList") {
                loadAnalogAddresses(xml);
            }else if(xml.name() == u"ARC4EncryptionList") {
                loadArc4EncryptionCodes(xml);
            }else if(xml.name() == u"AutoRepeaterList") {
                loadAutoRepeaterOffsets(xml);
            }else if(xml.name() == u"ChannelList") {
                loadChannels(xml);
            }else if(xml.name() == u"DTMFSettings") {
                dtmf_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"EncryptionCodeList") {
                loadEncryptionCodes(xml);
            }else if(xml.name() == u"FMList") {
                loadFm(xml);
            }else if(xml.name() == u"GPSRoamingList") {
                loadGpsRoaming(xml);
            }else if(xml.name() == u"HotKeySettings") {
                hotkey->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"OptionalSettings") {
                optional_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"PrefabricatedSmsList") {
                loadPrefabricatedSms(xml);
            }else if(xml.name() == u"RadioIdList") {
                loadRadioIds(xml);
            }else if(xml.name() == u"ReceiveGroupList") {
                loadReceiveGroupCallList(xml);
            }else if(xml.name() == u"RoamingChannelList") {
                loadRoamingChannel(xml);
            }else if(xml.name() == u"RoamingZoneList") {
                loadRoamingZone(xml);
            }else if(xml.name() == u"ScanlistList") {
                loadScanList(xml);
            }else if(xml.name() == u"TalkAliasSettings") {
                talk_alias_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"TalkgroupList") {
                loadTalkgroups(xml);
            }else if(xml.name() == u"Tone2Settings") {
                tone2_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"Tone5Settings") {
                tone5_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"ZoneList") {
                loadZones(xml);
            }else if(xml.name() == u"DigitalContactList") {
                loadDigitalContacts(xml);
            }else{
                token = xml.readNext();
            }

        }else{
            token = xml.readNext();
        }
    }

    if (xml.hasError()) {
        qDebug() << "XML error:" << xml.errorString();
    }else{
        linkReferences();
    }
}
void Memory::loadAesEncryptionCodes(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"AESCode") {
            int idx = xml.attributes().value("index").toInt();
            AesEncryptionCode *item = Memory::aes_encryption_keys.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"AESCode") {
            return;
        }
    }
}
void Memory::loadAnalogAddresses(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"AnalogAddress") {
            int idx = xml.attributes().value("id").toInt();
            AnalogAddress *item = Memory::analog_addresses.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"AnalogAddress") {
            return;
        }
    }
}
void Memory::loadArc4EncryptionCodes(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"ARC4Code") {
            int idx = xml.attributes().value("index").toInt();
            Arc4EncryptionCode *item = Memory::arc4_encryption_keys.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"ARC4Code") {
            return;
        }
    }
}
void Memory::loadAutoRepeaterOffsets(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"AutoRepeater") {
            int idx = xml.attributes().value("id").toInt();
            AutoRepeaterOffsetFrequency *item = Memory::ar_offset_frequencies.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"AutoRepeater") {
            return;
        }
    }
}
void Memory::loadChannels(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"Channel") {
            int idx = xml.attributes().value("id").toInt();
            Channel *item = Memory::channels.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"Channel") {
            return;
        }
    }
}
void Memory::loadEncryptionCodes(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"EncryptionCode") {
            int idx = xml.attributes().value("index").toInt();
            EncryptionCode *item = Memory::encryption_keys.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"EncryptionCode") {
            return;
        }
    }
}
void Memory::loadFm(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"FM") {
            int idx = xml.attributes().value("id").toInt();
            FM *item = Memory::fm_channels.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"FM") {
            return;
        }
    }
}
void Memory::loadGpsRoaming(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"GPSRoaming") {
            int idx = xml.attributes().value("id").toInt();
            GpsRoaming *item = Memory::gps_roaming_list.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"GPSRoaming") {
            return;
        }
    }

}
void Memory::loadPrefabricatedSms(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"Sms") {
            int idx = xml.attributes().value("id").toInt();
            PrefabricatedSms *item = Memory::prefabricated_sms_list.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"Sms") {
            return;
        }
    }

}
void Memory::loadRadioIds(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"RadioId") {
            int idx = xml.attributes().value("id").toInt();
            RadioId *item = Memory::radioids.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"RadioId") {
            return;
        }
    }
}
void Memory::loadReceiveGroupCallList(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"ReceiveGroup") {
            int idx = xml.attributes().value("id").toInt();
            ReceiveGroup *item = Memory::receive_group_call_lists.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"ReceiveGroup") {
            return;
        }
    }
}
void Memory::loadRoamingChannel(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"RoamingChannel") {
            int idx = xml.attributes().value("id").toInt();
            RoamingChannel *item = Memory::roaming_channels.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"RoamingChannel") {
            return;
        }
    }
}
void Memory::loadRoamingZone(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"RoamingZone") {
            int idx = xml.attributes().value("id").toInt();
            RoamingZone *item = Memory::roaming_zones.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"RoamingZone") {
            return;
        }
    }
}
void Memory::loadScanList(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"ScanList") {
            int idx = xml.attributes().value("id").toInt();
            ScanList *item = Memory::scanlists.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"ScanList") {
            return;
        }
    }
}
void Memory::loadTalkgroups(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"Talkgroup") {
            int idx = xml.attributes().value("id").toInt();
            Talkgroup *item = Memory::talkgroups.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"Talkgroup") {
            return;
        }
    }
}
void Memory::loadZones(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"Zone") {
            int idx = xml.attributes().value("id").toInt();
            Zone *item = Memory::zones.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"Zone") {
            return;
        }
    }
}
void Memory::loadDigitalContacts(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"DigitalContact") {
            int idx = xml.attributes().value("id").toInt();
            DigitalContact *item = Memory::digital_contacts.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"DigitalContact") {
            return;
        }
    }
}


// **********************
// Data Linkers
// **********************
void Memory::linkReferences(){
    Memory::linkZoneRef();
    Memory::linkChannelRef();
    Memory::linkScanListRef();
    Memory::linkRoamingZoneRef();
    Memory::linkHotKeyRef();
    linkReceiveGroupRef();
}
void Memory::linkZoneRef(){
    QVector<QVector<QString>> channels_list = {};
    for(Channel *ch : channels){
        QVector<QString> chl;
        chl.append(ch->name);
        chl.append(ch->getRxFrequencyString());
        chl.append(ch->getTxFrequencyString());
        
        channels_list.append(chl);
    }
    for (Zone* zone : zones) {
        if (!zone) continue;

        if(zone->temp_member_channel_idxs.size() > 0){
            for(uint16_t idx : zone->temp_member_channel_idxs){
                zone->channels.push_back(Memory::channels.at(idx));
            }
        }

        if(zone->temp_member_channels.size() > 0){
            for(QVector<QString> member : zone->temp_member_channels){
                int ch_idx = channels_list.indexOf(member);
                zone->channels.push_back(Memory::channels.at(ch_idx));
            }
        }

        if(zone->temp_a_channel_name.size() > 0){
            int a_ch_id = channels_list.indexOf(zone->temp_a_channel_name);
            if(a_ch_id != -1 && zone->channels.indexOf(Memory::channels.at(a_ch_id)) != 1){
                zone->a_channel_idx = zone->channels.indexOf(Memory::channels.at(a_ch_id));
            }
        }
        if(zone->temp_b_channel_name.size() > 0){
            int b_ch_id = channels_list.indexOf(zone->temp_b_channel_name);
            if(b_ch_id != -1 && zone->channels.indexOf(Memory::channels.at(b_ch_id)) != -1){
                zone->b_channel_idx = zone->channels.indexOf(Memory::channels.at(b_ch_id));
            }
        }
        

        if(zone->a_channel_idx < zone->channels.size())
            zone->a_channel = zone->channels.at(zone->a_channel_idx);

        if(zone->b_channel_idx < zone->channels.size())
            zone->b_channel = zone->channels.at(zone->b_channel_idx);
    }
}
void Memory::linkChannelRef(){
    for(Channel *ch : Memory::channels){
        if(ch->contact_idx < Memory::talkgroups.size())
            ch->contact = Memory::talkgroups.at(ch->contact_idx);

        if(ch->radio_id_idx < Memory::radioids.size())
            ch->radioid = Memory::radioids.at(ch->radio_id_idx);

        if(ch->scan_list_idx < Memory::scanlists.size())
            ch->scanlist = Memory::scanlists.at(ch->scan_list_idx);

        if(ch->temp_contact_tg != 0){
            for(Talkgroup *tg : talkgroups){
                if(tg->dmr_id == ch->temp_contact_tg){
                    ch->contact = tg;
                    ch->contact_idx = tg->id;
                    break;
                }
            }
        }

        if(!ch->temp_radio_id_name.isEmpty()){
            for(RadioId *rid : radioids){
                if(rid->name == ch->temp_radio_id_name){
                    ch->radio_id_idx = rid->id;
                    ch->radioid = rid;
                    break;
                }
            }
        }
        
    }
}
void Memory::linkScanListRef(){
    for(ScanList *sc : Memory::scanlists){
        for(int idx : sc->channel_member_idxs){
            sc->channels.push_back(Memory::channels.at(idx));
        }
    }
}
void Memory::linkRoamingZoneRef(){
    for(RoamingZone *z : Memory::roaming_zones){
        for(int idx : z->channel_idxs){
            z->channels.push_back(Memory::roaming_channels.at(idx));
        }
    }
}
void Memory::linkHotKeyRef(){
    for(HotkeyKey *key : hotkey->key_list){
        if(key->call_type == 2 && key->call_obj != 0xffffffff){
            key->talkgroup = talkgroups.at(key->call_obj);
        }
    }
}
void Memory::linkReceiveGroupRef(){
    for(ReceiveGroup *z : Memory::receive_group_call_lists){
        for(int idx : z->tg_idxs){
            z->talkgroups.push_back(Memory::talkgroups.at(idx));
        }
    }
}
// **********************
// Data Initializers
// **********************
void Memory::init(){
    Memory::hotkey = new Hotkey();
    Memory::optional_settings = new OptionalSettings();
    Memory::alarm_settings = new AlarmSettings();
    Memory::aprs_settings = new AprsSettings();
    Memory::dtmf_settings = new DTMFSettings();
    Memory::tone2_settings = new Tone2Settings();
    Memory::tone5_settings = new Tone5Settings();
    Memory::master_radio_id = new MasterId();
    Memory::talk_alias_settings = new TalkAliasSettings();
    Memory::initChannels();
    Memory::initZones();
    Memory::initTalkgroups();
    Memory::initScanLists();
    Memory::initRadioIds();
    Memory::initRoamingZones();
    Memory::initRoamingChannels();
    Memory::initFMChannels();
    Memory::initAutoRepeaterFrequencies();
    Memory::initDigitalContacts();
    Memory::initGpsRoaming();
    Memory::initPrefabricatedSms();
    Memory::initReceiveGroupCallLists();
    Memory::initAesEncryptionKeys();
    Memory::initArc4EncryptionKeys();
    Memory::initEncryptionKeys();
    Memory::initAnalogAddresses();

    setDefaults();
    linkReferences();
}
void Memory::initChannels(){
    Memory::channels.clear();
    for(int i = 0; i < 4002; i++){
        Channel *channel = new Channel();
        channel->id = i;
        Memory::channels.push_back(channel);
    }
}
void Memory::initZones(){
    Memory::zones.clear();
    for(int i = 0; i < 250; i++){
        Zone *zone = new Zone();
        zone->id = i;
        Memory::zones.push_back(zone);
    }
}
void Memory::initTalkgroups(){
    Memory::talkgroups.clear();
    for(int i = 0; i < 10000; i++){
        Talkgroup *tg = new Talkgroup();
        tg->id = i;
        Memory::talkgroups.push_back(tg);
    }
}
void Memory::initScanLists(){
    Memory::scanlists.clear();
    for(int i = 0; i < 250; i++){
        ScanList *sc = new ScanList();
        sc->id = i;
        Memory::scanlists.push_back(sc);
    }
}
void Memory::initRadioIds(){
    Memory::radioids.clear();
    for(int i = 0; i < 250; i++){
        RadioId *rid = new RadioId();
        rid->id = i;
        Memory::radioids.push_back(rid);
    }
}
void Memory::initRoamingZones(){
    Memory::roaming_zones.clear();
    for(int i = 0; i < 64; i++){
        RoamingZone *z = new RoamingZone();
        z->id = i;
        Memory::roaming_zones.push_back(z);
    }
}
void Memory::initRoamingChannels(){
    Memory::roaming_channels.clear();
    for(int i = 0; i < 250; i++){
        RoamingChannel *ch = new RoamingChannel();
        ch->id = i;
        Memory::roaming_channels.push_back(ch);
    }
}
void Memory::initFMChannels(){
    Memory::fm_channels.clear();
    for(int i = 0; i < 101; i++){
        FM *fm = new FM();
        fm->id = i;
        Memory::fm_channels.push_back(fm);
    }
}
void Memory::initAutoRepeaterFrequencies(){
    Memory::ar_offset_frequencies.clear();
    for(int i = 0; i < 250; i++){
        AutoRepeaterOffsetFrequency *ar = new AutoRepeaterOffsetFrequency();
        ar->id = i;
        Memory::ar_offset_frequencies.push_back(ar);
    }
}
void Memory::initDigitalContacts(){
    Memory::digital_contacts.clear();
    for(int i = 0; i < 500000; i++){
        DigitalContact *contact = new DigitalContact();
        contact->id = i;
        Memory::digital_contacts.push_back(contact);
    }
}
void Memory::initGpsRoaming(){
    Memory::gps_roaming_list.clear();
    for(int i = 0; i < 32; i++){
        GpsRoaming *gps = new GpsRoaming();
        gps->id = i;
        Memory::gps_roaming_list.push_back(gps);
    }
}
void Memory::initPrefabricatedSms(){
    Memory::prefabricated_sms_list.clear();
    for(int i = 0; i < 100; i++){
        PrefabricatedSms *sms = new PrefabricatedSms();
        sms->id = i;
        Memory::prefabricated_sms_list.push_back(sms);
    }
}
void Memory::initReceiveGroupCallLists(){
    Memory::receive_group_call_lists.clear();
    for(int i = 0; i < 100; i++){
        ReceiveGroup *rgcl = new ReceiveGroup();
        rgcl->id = i;
        Memory::receive_group_call_lists.push_back(rgcl);
    }
}
void Memory::initAesEncryptionKeys(){
    Memory::aes_encryption_keys.clear();
    for(int i = 0; i < 255; i++){
        AesEncryptionCode *key = new AesEncryptionCode();
        key->index = i;
        Memory::aes_encryption_keys.push_back(key);
    }
}
void Memory::initArc4EncryptionKeys(){
    Memory::arc4_encryption_keys.clear();
    for(int i = 0; i < 255; i++){
        Arc4EncryptionCode *key = new Arc4EncryptionCode();
        key->index = i;
        Memory::arc4_encryption_keys.push_back(key);
    }
}
void Memory::initEncryptionKeys(){
    Memory::encryption_keys.clear();
    for(int i = 0; i < 32; i++){
        EncryptionCode *key = new EncryptionCode();
        key->index = i;
        Memory::encryption_keys.push_back(key);
    }
}
void Memory::initAnalogAddresses(){
    Memory::analog_addresses.clear();
    for(int i = 0; i < 128; i++){
        AnalogAddress *item = new AnalogAddress();
        item->id = i;
        Memory::analog_addresses.push_back(item);
    }
}

// **********************
// Data Defaults
// **********************
void Memory::setDefaults(){
    setDefaultMasterID();
    setDefaultTalkgroups();
    setDefaultRadioIds();
}
void Memory::setDefaultMasterID(){
    master_radio_id->dmr_id = 12345678;
    master_radio_id->name = "My Radio";
    master_radio_id->used = false;
}
void Memory::setDefaultTalkgroups(){
    talkgroups.at(0)->dmr_id = 12345678;
    talkgroups.at(0)->name = "Contact 1";
}
void Memory::setDefaultRadioIds(){
    radioids.at(0)->dmr_id = 12345678;
    radioids.at(0)->name = "My Radio";
}
