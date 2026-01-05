#ifndef ANYTONE_MEMORY_H
#define ANYTONE_MEMORY_H

#include <vector>
#include <memory>
#include <QVector>
#include <QDataStream>

#include "master_id.h"
#include "memory/optional_settings.h"
#include "memory/alarm_settings.h"
#include "memory/aprs_settings.h"
#include "hotkey.h"

namespace Anytone {

    enum RadioModel {
        None,
        D878UVII,
        D890UV,
        D168UV
    };

    struct MemoryMap {
        int LocalInfo;
        int BootImage;
        int BK1Image;
        int BK2Image;
        int ChannelSet;
        int ChannelData;
        int ChannelDataOffset;
        int ChannelDataBlockSize;
        int ChannelDataBlockOffset;
        int ChannelDataSecondaryOffset;
        // int ZonesName;
        // int ZoneChannels;
        // int ZoneAChannel;
        // int ZoneBChannel;
        // int ZoneHide;
        // int RadioIdSet;
        // int RadioIdData;
        // int ScanListSet;
        // int ScanListData;
        // int FmData;
        // int RoamingZoneSet;
        // int RoamingZoneData;
        // int RoamingChannelSet;
        // int RoamingChannelData;
    };

    constexpr MemoryMap D878_MAP {
        .LocalInfo = 0x2fa0000,
        .BootImage = 0x2ac0000,
        .BK1Image = 0x2b00000,
        .BK2Image = 0x2b80000,
        .ChannelSet = 0x24c1500,
        .ChannelData = 0x800000,
        .ChannelDataOffset = 0x40,
        .ChannelDataBlockSize = 128,
        .ChannelDataBlockOffset = 0x40000,
        .ChannelDataSecondaryOffset = 0x2000
        // .ChannelSet = 0x24c1500,
        // .ChannelsData = ,
        // .ZonesName = ,
        // .ZoneChannels = ,
        // .ZoneAChannel = ,
        // .ZoneBChannel = ,
        // .ZoneHide = ,
        // .RadioIdSet = ,
        // .RadioIdData = ,
        // .ScanListSet = ,
        // .ScanListData = ,
        // .FmData = ,
        // .RoamingZoneSet = ,
        // .RoamingZoneData = ,
        // .RoamingChannelSet = ,
        // .RoamingChannelData = 

    };

    constexpr MemoryMap D890_MAP {
        .LocalInfo = 0x4f80000,
        .BootImage = 0x3f80000,
        .BK1Image = 0x4000000,
        .BK2Image = 0x4080000,
        .ChannelSet = 0x0,
        .ChannelData = 0x1000000,
        .ChannelDataOffset = 0x80,
        .ChannelDataBlockSize = 128,
        .ChannelDataBlockOffset = 0x40000,
        .ChannelDataSecondaryOffset = 0x40 
        // .ChannelSet = ,
        // .ChannelsData = ,
        // .ZonesName = 0x3600000,
        // .ZoneChannels = ,
        // .ZoneAChannel = ,
        // .ZoneBChannel = ,
        // .ZoneHide = ,
        // .RadioIdSet = ,
        // .RadioIdData = ,
        // .ScanListSet = ,
        // .ScanListData = ,
        // .FmData = ,
        // .RoamingZoneSet = ,
        // .RoamingZoneData = ,
        // .RoamingChannelSet = ,
        // .RoamingChannelData = 
    };

    class Channel;
    class Zone;
    class Talkgroup;
    class ScanList;
    class RadioId;
    class RoamingChannel;
    class RoamingZone;
    class AutoRepeaterOffsetFrequency;
    class FM;
    class DigitalContact;
    class AutoRepeaterOffsetFrequency;
    class GpsRoaming;
    class PrefabricatedSms;
    class ReceiveGroup;
    class AesEncryptionCode;
    class DTMFSettings;
    class Tone2Settings;
    class Tone5Settings;
    class TalkAliasSettings;
    class Arc4EncryptionCode;
    class EncryptionCode;
    class AnalogAddress;

    class Memory {

    public:
        static void init();
        static void saveData(QDataStream &ds);
        static QByteArray saveAesEncryptionCodes(QDataStream &ds);
        static QByteArray saveAprsSettings();
        static QByteArray saveAlarmSettings();
        static QByteArray saveAnalogAddresses(QDataStream &ds);
        static QByteArray saveArc4EncryptionCodes(QDataStream &ds);
        static QByteArray saveAutoRepeaterOffsets(QDataStream &ds);
        static QByteArray saveChannels(QDataStream &ds);
        static QByteArray saveDtmfSettings();
        static QByteArray saveEncryptionCodes(QDataStream &ds);
        static QByteArray saveFm(QDataStream &ds);
        static QByteArray saveGpsRoaming(QDataStream &ds);
        static QByteArray saveHotKey();
        static QByteArray saveMasterId();
        static QByteArray saveOptionalSettings();
        static QByteArray savePrefabricatedSms(QDataStream &ds);
        static QByteArray saveRadioIds(QDataStream &ds);
        static QByteArray saveReceiveGroupCallList(QDataStream &ds);
        static QByteArray saveRoamingChannel(QDataStream &ds);
        static QByteArray saveRoamingZone(QDataStream &ds);
        static QByteArray saveScanList(QDataStream &ds);
        static QByteArray saveTalkerAliasSettings();
        static QByteArray saveTalkgroups(QDataStream &ds);
        static QByteArray saveTone2Settings();
        static QByteArray saveTone5Settings();
        static QByteArray saveZones(QDataStream &ds);
        static QByteArray saveDigitalContacts(QDataStream &ds);
        static void loadData(QDataStream &ds);
        
        static void loadAesEncryptionCodes(uint16_t count, QDataStream &ds);
        static void loadAprsSettings(QDataStream &ds);
        static void loadAlarmSettings(QDataStream &ds);
        static void loadAnalogAddresses(uint16_t count, QDataStream &ds);
        static void loadArc4EncryptionCodes(uint16_t count, QDataStream &ds);
        static void loadAutoRepeaterOffsets(uint16_t count, QDataStream &ds);
        static void loadChannels(uint16_t count, QDataStream &ds);
        static void loadDtmfSettings(QDataStream &ds);
        static void loadEncryptionCodes(uint16_t count, QDataStream &ds);
        static void loadFm(uint16_t count, QDataStream &ds);
        static void loadGpsRoaming(uint16_t count, QDataStream &ds);
        static void loadHotkey(QDataStream &ds);
        static void loadMasterId(QDataStream &ds);
        static void loadOptionalSettings(QDataStream &ds);
        static void loadPrefabricatedSms(uint16_t count, QDataStream &ds);
        static void loadRadioIds(uint16_t count, QDataStream &ds);
        static void loadReceiveGroupCallList(uint16_t count, QDataStream &ds);
        static void loadRoamingChannel(uint16_t count, QDataStream &ds);
        static void loadRoamingZone(uint16_t count, QDataStream &ds);
        static void loadScanList(uint16_t count, QDataStream &ds);
        static void loadTalkerAliasSettings(QDataStream &ds);
        static void loadTalkgroups(uint16_t count, QDataStream &ds);
        static void loadTone2Settings(QDataStream &ds);
        static void loadTone5Settings(QDataStream &ds);
        static void loadZones(uint8_t count, QDataStream &ds);
        static void loadDigitalContacts(int count, QDataStream &ds);

        static void setDefaults();
        static void setDefaultMasterID();
        static void setDefaultTalkgroups();
        static void setDefaultRadioIds();

        static void linkReferences();
        static void linkZoneRef();
        static void linkChannelRef();
        static void linkScanListRef();
        static void linkRoamingZoneRef();

        static void initChannels();
        static void initZones();
        static void initTalkgroups();
        static void initScanLists();
        static void initRadioIds();
        static void initRoamingZones();
        static void initRoamingChannels();
        static void initFMChannels();
        static void initAutoRepeaterFrequencies();
        static void initDigitalContacts();
        static void initGpsRoaming();
        static void initPrefabricatedSms();
        static void initReceiveGroupCallLists();
        static void initAesEncryptionKeys();
        static void initArc4EncryptionKeys();
        static void initEncryptionKeys();
        static void initAnalogAddresses();

        static const MemoryMap* Map(){
            switch (Anytone::Memory::radio_model) {
                case RadioModel::D878UVII: return &D878_MAP;
                case RadioModel::D890UV:   return &D890_MAP;
                default: return nullptr;
            }
        }

        static RadioModel radio_model;
        static QString radio_band;
        static QString radio_version;
        static uint8_t radio_mode;

        static Hotkey *hotkey;
        static OptionalSettings *optional_settings;
        static AlarmSettings *alarm_settings;
        static AprsSettings *aprs_settings;
        static DTMFSettings *dtmf_settings;
        static Tone2Settings *tone2_settings;
        static Tone5Settings *tone5_settings;
        static MasterId *master_radio_id;
        static TalkAliasSettings *talk_alias_settings;
        static QVector<Channel*> channels;
        static QVector<Zone*> zones;
        static QVector<Talkgroup*> talkgroups;
        static QVector<ScanList*> scanlists;
        static QVector<RadioId*> radioids;
        static QVector<RoamingChannel*> roaming_channels;
        static QVector<RoamingZone*> roaming_zones;
        static QVector<AutoRepeaterOffsetFrequency*> ar_offset_frequencies;
        static QVector<FM*> fm_channels;
        static QVector<DigitalContact*> digital_contacts;
        static QVector<GpsRoaming*> gps_roaming_list;
        static QVector<PrefabricatedSms*> prefabricated_sms_list;
        static QVector<ReceiveGroup*> receive_group_call_lists;
        static QVector<AesEncryptionCode*> aes_encryption_keys;
        static QVector<Arc4EncryptionCode*> arc4_encryption_keys;
        static QVector<EncryptionCode*> encryption_keys;
        static QVector<AnalogAddress*> analog_addresses;
        
    };
}

#endif