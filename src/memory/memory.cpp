#include "memory/memory.h"
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
void Memory::saveData(QDataStream &ds){
    uint16_t save_file_version = 1;
    ds << QString("D878UV2").toUtf8() << QString("4.00").toUtf8() << Memory::radio_mode << save_file_version;

    QByteArray radio_data;

    radio_data.append(saveAesEncryptionCodes(ds));
    radio_data.append(saveAprsSettings());
    radio_data.append(saveAlarmSettings());
    radio_data.append(saveAnalogAddresses(ds));
    radio_data.append(saveArc4EncryptionCodes(ds));
    radio_data.append(saveAutoRepeaterOffsets(ds));
    radio_data.append(saveChannels(ds));
    radio_data.append(saveDtmfSettings());
    radio_data.append(saveEncryptionCodes(ds));
    radio_data.append(saveFm(ds));
    radio_data.append(saveGpsRoaming(ds));
    radio_data.append(saveHotKey());
    radio_data.append(saveMasterId());
    radio_data.append(saveOptionalSettings());
    radio_data.append(savePrefabricatedSms(ds));
    radio_data.append(saveRadioIds(ds));
    radio_data.append(saveReceiveGroupCallList(ds));
    radio_data.append(saveRoamingChannel(ds));
    radio_data.append(saveRoamingZone(ds));
    radio_data.append(saveScanList(ds));
    radio_data.append(saveTalkerAliasSettings());
    radio_data.append(saveTalkgroups(ds));
    radio_data.append(saveTone2Settings());
    radio_data.append(saveTone5Settings());
    radio_data.append(saveZones(ds));
    radio_data.append(saveDigitalContacts(ds));

    ds << radio_data;
}
QByteArray Memory::saveAesEncryptionCodes(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(AesEncryptionCode *item : Memory::aes_encryption_keys){
        if(item->id > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveAprsSettings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::aprs_settings->save(data_ds);
    return data;
}
QByteArray Memory::saveAlarmSettings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::alarm_settings->save(data_ds);
    return data;
}
QByteArray Memory::saveAnalogAddresses(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(AnalogAddress *item : Memory::analog_addresses){
        if(item->number > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveArc4EncryptionCodes(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(Arc4EncryptionCode *item : Memory::arc4_encryption_keys){
        if(item->id > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveAutoRepeaterOffsets(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(AutoRepeaterOffsetFrequency *item : Memory::ar_offset_frequencies){
        if(item->frequency > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveChannels(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(Channel *item : Memory::channels){
        if(item->rx_frequency > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveDtmfSettings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::dtmf_settings->save(data_ds);
    return data;
}
QByteArray Memory::saveEncryptionCodes(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(EncryptionCode *item : Memory::encryption_keys){
        count++;
        item->save(data_ds);
    }
    ds << count;
    return data;
}
QByteArray Memory::saveFm(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(FM *item : Memory::fm_channels){
        if(item->frequency > 0){
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveGpsRoaming(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(GpsRoaming *item : Memory::gps_roaming_list){
        count++;
        item->save(data_ds);
    }
    ds << count;
    return data;
}
QByteArray Memory::saveHotKey(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::hotkey->save(data_ds);
    return data;
}
QByteArray Memory::saveMasterId(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::master_radio_id->save(data_ds);
    return data;
}
QByteArray Memory::saveOptionalSettings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::optional_settings->save(data_ds);
    return data;
}
QByteArray Memory::savePrefabricatedSms(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(PrefabricatedSms *item : Memory::prefabricated_sms_list){
        if(item->text.size() > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveRadioIds(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(RadioId *item : Memory::radioids){
        if(item->dmr_id > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveReceiveGroupCallList(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(ReceiveGroup *item : Memory::receive_group_call_lists){
        if(item->talkgroups.size() > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveRoamingChannel(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(RoamingChannel *item : Memory::roaming_channels){
        if(item->rx_frequency > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveRoamingZone(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(RoamingZone *item : Memory::roaming_zones){
        if(item->channels.size() > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveScanList(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(ScanList *item : Memory::scanlists){
        if(item->channels.size() > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveTalkerAliasSettings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::talk_alias_settings->save(data_ds);
    return data;
}
QByteArray Memory::saveTalkgroups(QDataStream &ds){
    uint16_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(Talkgroup *item : Memory::talkgroups){
        if(item->dmr_id > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveTone2Settings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::tone2_settings->save(data_ds);
    return data;
}
QByteArray Memory::saveTone5Settings(){
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    Memory::tone5_settings->save(data_ds);
    return data;
}
QByteArray Memory::saveZones(QDataStream &ds){
    uint8_t count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(Zone *item : Memory::zones){
        if(item->channels.size() > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}
QByteArray Memory::saveDigitalContacts(QDataStream &ds){
    int count = 0;
    QByteArray data;
    QDataStream data_ds(&data, QIODevice::WriteOnly);
    for(DigitalContact *item : Memory::digital_contacts){
        if(item->radio_id > 0) {
            count++;
            item->save(data_ds);
        }
    }
    ds << count;
    return data;
}

// **********************
// Save File Load
// **********************
void Memory::loadData(QDataStream &ds){
    init();
    QByteArray radio_model_utf8;
    QByteArray fw_version_utf8;
    uint8_t radio_mode_i = 0;
    uint16_t save_file_version = 0;
    ds >> radio_model_utf8;
    ds >> fw_version_utf8;
    ds >> radio_mode_i;
    ds >> save_file_version;

    uint16_t aes_code_count = 0;
    uint16_t analog_address_count = 0;
    uint16_t arc4_code_count = 0;
    uint16_t ar_offset_count = 0;
    uint16_t channel_count = 0;
    uint16_t encryption_code_count = 0;
    uint16_t fm_count = 0;
    uint16_t gps_roaming_count = 0;
    uint16_t prefab_sms_count = 0;
    uint16_t radio_id_count = 0;
    uint16_t receive_group_count = 0;
    uint16_t roaming_channel_count = 0;
    uint16_t roaming_zone_count = 0;
    uint16_t scanlist_count = 0;
    uint16_t tg_count = 0;
    uint8_t zone_count = 0;
    int digital_contact_count = 0;

    // Get Data Lengths
    ds >> aes_code_count;
    ds >> analog_address_count;
    ds >> arc4_code_count;
    ds >> ar_offset_count;
    ds >> channel_count;
    ds >> encryption_code_count;
    ds >> fm_count;
    ds >> gps_roaming_count;
    ds >> prefab_sms_count;
    ds >> radio_id_count;
    ds >> receive_group_count;
    ds >> roaming_channel_count;
    ds >> roaming_zone_count;
    ds >> scanlist_count;
    ds >> tg_count;
    ds >> zone_count;
    ds >> digital_contact_count;

    int data_len = 0;
    ds >> data_len;

    // Read Data
    loadAesEncryptionCodes(aes_code_count, ds);
    loadAprsSettings(ds);
    loadAlarmSettings(ds);
    loadAnalogAddresses(analog_address_count, ds);
    loadArc4EncryptionCodes(arc4_code_count, ds);
    loadAutoRepeaterOffsets(ar_offset_count, ds);
    loadChannels(channel_count, ds);
    loadDtmfSettings(ds);
    loadEncryptionCodes(encryption_code_count, ds);
    loadFm(fm_count, ds);
    loadGpsRoaming(gps_roaming_count, ds);
    loadHotkey(ds);
    loadMasterId(ds);
    loadOptionalSettings(ds);
    loadPrefabricatedSms(prefab_sms_count, ds);
    loadRadioIds(radio_id_count, ds);
    loadReceiveGroupCallList(receive_group_count, ds);
    loadRoamingChannel(roaming_channel_count, ds);
    loadRoamingZone(roaming_zone_count, ds);
    loadScanList(scanlist_count, ds);
    loadTalkerAliasSettings(ds);
    loadTalkgroups(tg_count, ds);
    loadTone2Settings(ds);
    loadTone5Settings(ds);
    loadZones(zone_count, ds);
    loadDigitalContacts(digital_contact_count, ds);

    linkReferences();
}
void Memory::loadAesEncryptionCodes(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        AesEncryptionCode *item = Memory::aes_encryption_keys.at(idx);
        item->load(ds);
    }
}
void Memory::loadAprsSettings(QDataStream &ds){
    Memory::aprs_settings->load(ds);
}
void Memory::loadAlarmSettings(QDataStream &ds){
    Memory::alarm_settings->load(ds);
}
void Memory::loadAnalogAddresses(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        AnalogAddress *item = Memory::analog_addresses.at(i);
        item->load(ds);
    }
}
void Memory::loadArc4EncryptionCodes(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        Arc4EncryptionCode *item = Memory::arc4_encryption_keys.at(idx);
        item->load(ds);
    }
}
void Memory::loadAutoRepeaterOffsets(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        AutoRepeaterOffsetFrequency *item = Memory::ar_offset_frequencies.at(idx);
        item->load(ds);
    }
}
void Memory::loadChannels(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint16_t idx = 0;
        ds >> idx;
        Channel *item = Memory::channels.at(idx);
        item->load(ds);
    }
}
void Memory::loadDtmfSettings(QDataStream &ds){
    Memory::dtmf_settings->load(ds);
}
void Memory::loadEncryptionCodes(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        EncryptionCode *item = Memory::encryption_keys.at(idx);
        item->load(ds);
    }
}
void Memory::loadFm(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        FM *item = Memory::fm_channels.at(idx);
        item->load(ds);
    }
}
void Memory::loadGpsRoaming(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        GpsRoaming *item = Memory::gps_roaming_list.at(idx);
        item->load(ds);
    }
}
void Memory::loadHotkey(QDataStream &ds){
    Memory::hotkey->load(ds);
}
void Memory::loadMasterId(QDataStream &ds){
    Memory::master_radio_id->load(ds);
}
void Memory::loadOptionalSettings(QDataStream &ds){
    Memory::optional_settings->load(ds);
}
void Memory::loadPrefabricatedSms(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        PrefabricatedSms *item = Memory::prefabricated_sms_list.at(idx);
        item->load(ds);
    }
}
void Memory::loadRadioIds(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        RadioId *item = Memory::radioids.at(idx);
        item->load(ds);
    }
}
void Memory::loadReceiveGroupCallList(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        ReceiveGroup *item = Memory::receive_group_call_lists.at(idx);
        item->load(ds);
    }
}
void Memory::loadRoamingChannel(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        RoamingChannel *item = Memory::roaming_channels.at(idx);
        item->load(ds);
    }
}
void Memory::loadRoamingZone(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        RoamingZone *item = Memory::roaming_zones.at(idx);
        item->load(ds);
    }
}
void Memory::loadScanList(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        ScanList *item = Memory::scanlists.at(idx);
        item->load(ds);
    }
}
void Memory::loadTalkerAliasSettings(QDataStream &ds){
    Memory::talk_alias_settings->load(ds);
}
void Memory::loadTalkgroups(uint16_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint16_t idx = 0;
        ds >> idx;
        Talkgroup *item = Memory::talkgroups.at(idx);
        item->load(ds);
    }
}
void Memory::loadTone2Settings(QDataStream &ds){
    Memory::tone2_settings->load(ds);
}
void Memory::loadTone5Settings(QDataStream &ds){
    Memory::tone5_settings->load(ds);
}
void Memory::loadZones(uint8_t count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint8_t idx = 0;
        ds >> idx;
        Zone *item = Memory::zones.at(idx);
        item->load(ds);
    }
}
void Memory::loadDigitalContacts(int count, QDataStream &ds){
    for(int i = 0; i < count; i++){
        uint32_t idx = 0;
        ds >> idx;
        DigitalContact *item = Memory::digital_contacts.at(idx);
        item->load(ds);
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
}
void Memory::linkZoneRef(){
    for (Zone* zone : zones) {
        if (!zone) continue;
        if(zone->temp_member_channel_idxs.size() > 0){
            for(uint16_t idx : zone->temp_member_channel_idxs){
                zone->channels.push_back(Memory::channels.at(idx));
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
