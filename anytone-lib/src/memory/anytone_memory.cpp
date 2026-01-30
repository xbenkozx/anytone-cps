#include "memory/anytone_memory.h"
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
#include "am_air.h"
#include "am_zone.h"
#include "talkgroup_whitelist.h"

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

Channel* Memory::default_channel = nullptr;
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
QVector<AmAir*> Memory::am_air_list= {};
QVector<AmZone*> Memory::am_zones = {};
QVector<Satellite*> Memory::satellite_data_list = {};
QVector<TalkgroupWhitelist*> Memory::talkgroup_whitelist = {};
QVector<TalkgroupWhitelist*> Memory::digital_contact_whitelist = {};

// **********************
// Save File Save
// **********************
void Memory::saveData(QXmlStreamWriter &xml){
    int save_max = 30;
    int save_count = 0;
    xml.writeStartDocument();
    xml.writeStartElement("Codeplug");
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAesEncryptionCodes(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAprsSettings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAlarmSettings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAmAir(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAmZones(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAnalogAddresses(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveArc4EncryptionCodes(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveAutoRepeaterOffsets(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveChannels(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveDigitalContactWhitelist(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveDtmfSettings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveEncryptionCodes(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveFm(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveGpsRoaming(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveHotKey(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveMasterId(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveOptionalSettings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    savePrefabricatedSms(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveRadioIds(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveReceiveGroupCallList(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveRoamingChannel(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveRoamingZone(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveScanList(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveTalkerAliasSettings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveTalkgroups(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveTalkgroupWhitelist(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveTone2Settings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveTone5Settings(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
    saveZones(xml);
    Memory::instance().update1(save_count++, save_max, "Saving Data");
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
void Memory::saveAmAir(QXmlStreamWriter &xml){
    xml.writeStartElement("AmAirList");
    for(AmAir *item : Memory::am_air_list){
        if(item->frequency > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
}
void Memory::saveAmZones(QXmlStreamWriter &xml){
    xml.writeStartElement("AmZoneList");
    for(AmZone *item : Memory::am_zones){
        if(item->member_channels.size() > 0 || item->scan_channels.size() > 0) {
            item->save(xml);
        }
    }
    xml.writeEndElement();
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
void Memory::saveDigitalContactWhitelist(QXmlStreamWriter &xml){
    xml.writeStartElement("DigitalContactWhitelistList");
    for(TalkgroupWhitelist *item : Memory::digital_contact_whitelist){
        if(item->dmr_id > 0) {
            item->save(xml);
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
void Memory::saveTalkgroupWhitelist(QXmlStreamWriter &xml){
    xml.writeStartElement("TalkgroupWhitelistList");
    for(TalkgroupWhitelist *item : Memory::talkgroup_whitelist){
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
    int count = 0;
    int index = 0;

    for(DigitalContact *item : Memory::digital_contacts){
        if(item->radio_id > 0) count++;
    }
    
    xml.writeStartElement("DigitalContactList");
    xml.writeAttribute("items", QString::number(count));
    for(DigitalContact *item : Memory::digital_contacts){
        if(index % int(count/100) == 0) Memory::instance().update2(index, count, "Saving Digital Contacts");
        if(item->radio_id > 0) {
            item->save(xml);
        }
        index++;
    }
    xml.writeEndElement();
}

// **********************
// Save File Load
// **********************
void Memory::loadData(QXmlStreamReader &xml){
    int load_max = 30;
    int load_count = 0;
    QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
    while (!xml.atEnd() && !xml.hasError()) {
        
        if (token == QXmlStreamReader::StartDocument) {
            token = xml.readNext();
            continue;
        }

        if (token == QXmlStreamReader::StartElement) {
            if(xml.name() == u"AESEncryptionList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadAesEncryptionCodes(xml);
            }else if(xml.name() == u"APRSSettings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                aprs_settings->load(xml);
            }else if(xml.name() == u"AlarmSettings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                alarm_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"AmAirList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadAmAir(xml);
            }else if(xml.name() == u"AmZoneList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadAmZones(xml);
            }else if(xml.name() == u"AnalogAddressList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadAnalogAddresses(xml);
            }else if(xml.name() == u"ARC4EncryptionList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadArc4EncryptionCodes(xml);
            }else if(xml.name() == u"AutoRepeaterList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadAutoRepeaterOffsets(xml);
            }else if(xml.name() == u"ChannelList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadChannels(xml);
            }else if(xml.name() == u"DigitalContactWhitelistList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadDigitalContactWhitelist(xml);
            }else if(xml.name() == u"DTMFSettings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                dtmf_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"EncryptionCodeList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadEncryptionCodes(xml);
            }else if(xml.name() == u"FMList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadFm(xml);
            }else if(xml.name() == u"GPSRoamingList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadGpsRoaming(xml);
            }else if(xml.name() == u"HotKeySettings") {
                hotkey->load(xml);
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                token = xml.readNext();
            }else if(xml.name() == u"OptionalSettings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                optional_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"PrefabricatedSmsList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadPrefabricatedSms(xml);
            }else if(xml.name() == u"RadioIdList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadRadioIds(xml);
            }else if(xml.name() == u"ReceiveGroupList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadReceiveGroupCallList(xml);
            }else if(xml.name() == u"RoamingChannelList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadRoamingChannel(xml);
            }else if(xml.name() == u"RoamingZoneList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadRoamingZone(xml);
            }else if(xml.name() == u"ScanlistList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadScanList(xml);
            }else if(xml.name() == u"TalkAliasSettings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                talk_alias_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"TalkgroupList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadTalkgroups(xml);
            }else if(xml.name() == u"TalkgroupWhitelistList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadTalkgroupWhitelist(xml);
            }else if(xml.name() == u"Tone2Settings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                tone2_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"Tone5Settings") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                tone5_settings->load(xml);
                token = xml.readNext();
            }else if(xml.name() == u"ZoneList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
                loadZones(xml);
            }else if(xml.name() == u"DigitalContactList") {
                Memory::instance().update1(load_count++, load_max, "Loading Data");
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
void Memory::loadAmAir(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"AmAir") {
            int idx = xml.attributes().value("id").toInt();
            AmAir *item = Memory::am_air_list.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"AmAir") {
            return;
        }
    }
}
void Memory::loadAmZones(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"AmZone") {
            int idx = xml.attributes().value("id").toInt();
            AmZone *item = Memory::am_zones.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"AmZone") {
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
void Memory::loadDigitalContactWhitelist(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"TalkgroupWhitelist") {
            int idx = xml.attributes().value("id").toInt();
            TalkgroupWhitelist *item = Memory::digital_contact_whitelist.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"TalkgroupWhitelist") {
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
void Memory::loadTalkgroupWhitelist(QXmlStreamReader &xml){
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"TalkgroupWhitelist") {
            int idx = xml.attributes().value("id").toInt();
            TalkgroupWhitelist *item = Memory::talkgroup_whitelist.at(idx);
            item->load(xml);
        }else if(token == QXmlStreamReader::StartElement && xml.name() != u"TalkgroupWhitelist") {
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
    int count = 0;
    int index = 0;
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamAttributes attributes = xml.attributes();
        if(attributes.hasAttribute("items")) count = attributes.value("items").toInt();
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement && xml.name() == u"DigitalContact") {
            if(index % int(count/100) == 0) Memory::instance().update2(index, count, "Loading Digital Contacts");
            int idx = xml.attributes().value("id").toInt();
            DigitalContact *item = Memory::digital_contacts.at(idx);
            item->load(xml);
            index++;
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
    Memory::linkAmZoneRef();
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
void Memory::linkAmZoneRef(){
    for(AmZone *zone : am_zones){
        for(int idx : zone->member_channel_idxs){
            zone->member_channels.append(am_air_list[idx]);
        }
        for(int idx : zone->scan_channel_idxs){
            zone->scan_channels.append(am_air_list[idx]);
        }

        if(zone->member_channels.size() > 0){
            if(zone->aChannelIdx < zone->member_channels.size()) {
                zone->aChannel = zone->member_channels[zone->aChannelIdx];
            }else{
                zone->aChannel = zone->member_channels[0];
            }
        }
    }
}

// **********************
// Data Initializers
// **********************
void Memory::init(){
    hotkey = new Hotkey();
    optional_settings = new OptionalSettings();
    alarm_settings = new AlarmSettings();
    aprs_settings = new AprsSettings();
    dtmf_settings = new DTMFSettings();
    tone2_settings = new Tone2Settings();
    tone5_settings = new Tone5Settings();
    master_radio_id = new MasterId();
    talk_alias_settings = new TalkAliasSettings();
    initChannels();
    initZones();
    initTalkgroups();
    initScanLists();
    initRadioIds();
    initRoamingZones();
    initRoamingChannels();
    initFMChannels();
    initAutoRepeaterFrequencies();
    initGpsRoaming();
    initPrefabricatedSms();
    initReceiveGroupCallLists();
    initAesEncryptionKeys();
    initArc4EncryptionKeys();
    initEncryptionKeys();
    initAnalogAddresses();
    initAmAir();
    initAmZones();
    initTalkgroupWhitelist();
    initDigitalContactpWhitelist();
    
    linkReferences();
}
void Memory::initChannels(){
    qDeleteAll(Memory::channels);
    Memory::channels.clear();
    for(int i = 0; i < 4002; i++){
        Channel *channel = new Channel();
        channel->id = i;
        Memory::channels.push_back(channel);
    }
}
void Memory::initZones(){
    qDeleteAll(Memory::zones);
    Memory::zones.clear();
    for(int i = 0; i < 250; i++){
        Zone *zone = new Zone();
        zone->id = i;
        Memory::zones.push_back(zone);
    }
}
void Memory::initTalkgroups(){
    qDeleteAll(Memory::talkgroups);
    Memory::talkgroups.clear();
    for(int i = 0; i < 10000; i++){
        Talkgroup *tg = new Talkgroup();
        tg->id = i;
        Memory::talkgroups.push_back(tg);
    }
}
void Memory::initScanLists(){
    qDeleteAll(Memory::scanlists);
    Memory::scanlists.clear();
    for(int i = 0; i < 250; i++){
        ScanList *sc = new ScanList();
        sc->id = i;
        Memory::scanlists.push_back(sc);
    }
}
void Memory::initRadioIds(){
    qDeleteAll(Memory::radioids);
    Memory::radioids.clear();
    for(int i = 0; i < 250; i++){
        RadioId *rid = new RadioId();
        rid->id = i;
        Memory::radioids.push_back(rid);
    }
}
void Memory::initRoamingZones(){
    qDeleteAll(Memory::roaming_zones);
    Memory::roaming_zones.clear();
    for(int i = 0; i < 64; i++){
        RoamingZone *z = new RoamingZone();
        z->id = i;
        Memory::roaming_zones.push_back(z);
    }
}
void Memory::initRoamingChannels(){
    qDeleteAll(Memory::roaming_channels);
    Memory::roaming_channels.clear();
    for(int i = 0; i < 250; i++){
        RoamingChannel *ch = new RoamingChannel();
        ch->id = i;
        Memory::roaming_channels.push_back(ch);
    }
}
void Memory::initFMChannels(){
    qDeleteAll(Memory::fm_channels);
    Memory::fm_channels.clear();
    for(int i = 0; i < 101; i++){
        FM *fm = new FM();
        fm->id = i;
        Memory::fm_channels.push_back(fm);
    }
}
void Memory::initAutoRepeaterFrequencies(){
    qDeleteAll(Memory::ar_offset_frequencies);
    Memory::ar_offset_frequencies.clear();
    for(int i = 0; i < 250; i++){
        AutoRepeaterOffsetFrequency *ar = new AutoRepeaterOffsetFrequency();
        ar->id = i;
        Memory::ar_offset_frequencies.push_back(ar);
    }
}
void Memory::initDigitalContacts(){
    qDeleteAll(Memory::digital_contacts);
    Memory::digital_contacts.clear();
    for(int i = 0; i < 500000; i++){
        DigitalContact *contact = new DigitalContact();
        contact->id = i;
        Memory::digital_contacts.push_back(contact);
    }
}
void Memory::initGpsRoaming(){
    qDeleteAll(Memory::gps_roaming_list);
    Memory::gps_roaming_list.clear();
    for(int i = 0; i < 32; i++){
        GpsRoaming *gps = new GpsRoaming();
        gps->id = i;
        Memory::gps_roaming_list.push_back(gps);
    }
}
void Memory::initPrefabricatedSms(){
    qDeleteAll(Memory::prefabricated_sms_list);
    Memory::prefabricated_sms_list.clear();
    for(int i = 0; i < 100; i++){
        PrefabricatedSms *sms = new PrefabricatedSms();
        sms->id = i;
        Memory::prefabricated_sms_list.push_back(sms);
    }
}
void Memory::initReceiveGroupCallLists(){
    qDeleteAll(Memory::receive_group_call_lists);
    Memory::receive_group_call_lists.clear();
    for(int i = 0; i < 100; i++){
        ReceiveGroup *rgcl = new ReceiveGroup();
        rgcl->id = i;
        Memory::receive_group_call_lists.push_back(rgcl);
    }
}
void Memory::initAesEncryptionKeys(){
    qDeleteAll(Memory::aes_encryption_keys);
    Memory::aes_encryption_keys.clear();
    for(int i = 0; i < 255; i++){
        AesEncryptionCode *key = new AesEncryptionCode();
        key->index = i;
        Memory::aes_encryption_keys.push_back(key);
    }
}
void Memory::initArc4EncryptionKeys(){
    qDeleteAll(Memory::arc4_encryption_keys);
    Memory::arc4_encryption_keys.clear();
    for(int i = 0; i < 255; i++){
        Arc4EncryptionCode *key = new Arc4EncryptionCode();
        key->index = i;
        Memory::arc4_encryption_keys.push_back(key);
    }
}
void Memory::initEncryptionKeys(){
    qDeleteAll(Memory::encryption_keys);
    Memory::encryption_keys.clear();
    for(int i = 0; i < 32; i++){
        EncryptionCode *key = new EncryptionCode();
        key->index = i;
        Memory::encryption_keys.push_back(key);
    }
}
void Memory::initAnalogAddresses(){
    qDeleteAll(Memory::analog_addresses);
    Memory::analog_addresses.clear();
    for(int i = 0; i < 128; i++){
        AnalogAddress *item = new AnalogAddress();
        item->id = i;
        Memory::analog_addresses.push_back(item);
    }
}
void Memory::initAmAir(){
    qDeleteAll(Memory::am_air_list);
    Memory::am_air_list.clear();
    for(int i = 0; i < 257; i++){
        AmAir *item = new AmAir();
        item->index = i;
        Memory::am_air_list.push_back(item);
    }
}
void Memory::initAmZones(){
    qDeleteAll(Memory::am_zones);
    Memory::am_zones.clear();
    for(int i = 0; i < 16; i++){
        AmZone *item = new AmZone();
        item->index = i;
        Memory::am_zones.push_back(item);
    }
}
void Memory::initTalkgroupWhitelist(){
    qDeleteAll(Memory::talkgroup_whitelist);
    Memory::talkgroup_whitelist.clear();
    for(int i = 0; i < 1000; i++){
        TalkgroupWhitelist *item = new TalkgroupWhitelist();
        item->index = i;
        Memory::talkgroup_whitelist.push_back(item);
    }
}
void Memory::initDigitalContactpWhitelist(){
    qDeleteAll(Memory::digital_contact_whitelist);
    Memory::digital_contact_whitelist.clear();
    for(int i = 0; i < 1000; i++){
        TalkgroupWhitelist *item = new TalkgroupWhitelist();
        item->index = i;
        Memory::digital_contact_whitelist.push_back(item);
    }
}

// **********************
// Data Defaults
// **********************
void Memory::setDefaults(){
    setDefaultChannel();
    setDefaultZones();
    setDefaultMasterID();
    setDefaultTalkgroups();
    setDefaultRadioIds();
    
    linkReferences();
}
void Memory::setDefaultChannel(){
    if(!default_channel){
        default_channel = new Channel();
        default_channel->name = "Channel {id}";
        default_channel->rx_frequency = 44000000;
        default_channel->band_width = 1;
    }

    Anytone::Memory::channels.at(0)->copy(default_channel);
    Anytone::Memory::channels.at(0)->name.replace("{id}", QString::number(1));
}
void Memory::setDefaultZones(){
    Anytone::Memory::zones.at(0)->name = "Zone 1";
    Anytone::Memory::zones.at(0)->temp_member_channel_idxs.append(0);
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
