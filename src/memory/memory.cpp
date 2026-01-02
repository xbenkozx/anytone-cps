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
#include "dtmf_settings.h"
#include "tone2_settings.h"
#include "tone5_settings.h"
#include "talk_alias_settings.h"


using namespace Anytone;

OptionalSettings* Memory::optional_settings = nullptr;
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

void Memory::saveData(QDataStream &ds){
    ds << QString("D878UV2").toUtf8() << QString("4.00").toUtf8() << Memory::radio_mode;

    // Channel
    uint16_t channel_count = 0;
    QByteArray channel_data;
    QDataStream channel_ds(&channel_data, QIODevice::WriteOnly);
    for(Channel *ch : Memory::channels){
        if(ch->rx_frequency > 0) {
            channel_count++;
            ch->save(channel_ds);
        }
    }

    // Zone
    uint8_t zone_count = 0;
    QByteArray zone_data;
    QDataStream zone_ds(&zone_data, QIODevice::WriteOnly);
    for(Zone *zone : Memory::zones){
        if(zone->channels.size() > 0) {
            zone_count++;
            zone->save(zone_ds);
        }
    }

    // Digital Contacts
    int digital_contact_count = 0;
    QByteArray digital_contact_data;
    QDataStream digital_contact_ds(&digital_contact_data, QIODevice::WriteOnly);
    for(DigitalContact *c : Memory::digital_contacts){
        if(c->radio_id > 0) {
            digital_contact_count++;
            c->save(digital_contact_ds);
        }
    }

    ds << channel_count;
    ds << zone_count;
    ds << digital_contact_count;

    ds << channel_data;
    ds << zone_data;
    ds << digital_contact_data;
}
void Memory::loadData(QDataStream &ds){
    init();
    QByteArray radio_model_utf8;
    QByteArray fw_version_utf8;
    uint8_t radio_mode_i = 0;
    ds >> radio_model_utf8;
    ds >> fw_version_utf8;
    ds >> radio_mode_i;

    uint16_t channel_count = 0;
    uint8_t zone_count = 0;
    int digital_contact_count = 0;
    ds >> channel_count;
    ds >> zone_count;
    ds >> digital_contact_count;

    // Channel
    int _channel_data_len = 0;
    ds >> _channel_data_len;
    for(int i = 0; i < channel_count; i++){
        uint16_t ch_idx = 0;
        ds >> ch_idx;
        Channel *ch = Memory::channels.at(ch_idx);
        ch->load(ds);
    }

    // Channel
    int _zone_data_len = 0;
    ds >> _zone_data_len;
    for(int i = 0; i < zone_count; i++){
        uint8_t idx = 0;
        ds >> idx;
        Zone *zone = Memory::zones.at(idx);
        zone->load(ds);
    }

    // Digital Contacts
    int _digital_contact_len = 0;
    ds >> _digital_contact_len;
    for(int i = 0; i < digital_contact_count; i++){
        int idx = 0;
        ds >> idx;
        DigitalContact *c = Memory::digital_contacts.at(idx);
        c->load(ds);
    }

    linkReferences();
}

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


void Memory::init(){
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

    setDefaults();
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
        key->id = i;
        Memory::aes_encryption_keys.push_back(key);
    }
}
