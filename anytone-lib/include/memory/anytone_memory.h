#ifndef ANYTONE_MEMORY_H
#define ANYTONE_MEMORY_H

#include <vector>
#include <memory>
#include <QVector>
#include <QXmlStreamWriter>

#include "device_types.h"
#include "master_id.h"
#include "memory/optional_settings.h"
#include "memory/alarm_settings.h"
#include "memory/aprs_settings.h"
#include "hotkey.h"

namespace Anytone {

    struct MemoryMap {
        int LocalInfo;
        int BootImage;
        int BK1Image;
        int BK2Image;
        int AESSet;
        int AESData;
        int AESDataOffset;
        int AESDataLength;
        int AmAirSet;
        int AmAirData;
        int AmAirDataStride;
        int AmAirDataLength;
        int AmAirVfo;
        int AmZoneSet;
        int AmZoneScan;
        int AmZoneAChannel;
        int AmZoneData;
        int AmZoneDataStride;
        int AmZoneDataLength;
        int AnalogBookSet;
        int AnalogBookId;
        int AnalogBookData;
        int AnalogBookDataStride;
        int AnalogBookDataLength;
        int Arc4Set;
        int Arc4Data;
        int Arc4DataOffset;
        int Arc4DataLength;
        int AutoRepeaterData;
        int ChannelSet;
        int ChannelData;
        int ChannelDataOffset;
        int ChannelDataBlockSize;
        int ChannelDataBlockOffset;
        int ChannelDataSecondaryOffset;
        int EncryptionCodeId;
        int EncryptionCodeKey;
        int GpsRoamingData;
        int GpsRoamingDataLength;
        int MasterIdData;
        int MasterIdDataLength;
        int PrefabSmsSet;
        int PrefabSmsData;
        int PrefabSmsDataLength;
        int PrefabSmsDataOffset;
        int PrefabSmsDataBlockSize;
        int PrefabSmsDataBlockOffset;
        int RadioIdSet;
        int RadioIdData;
        int RadioIdDataOffset;
        int RadioIdDataLength;
        int ReceiveGroupSet;
        int ReceiveGroupData;
        int ReceiveGroupDataOffset;
        int ReceiveGroupDataLength;
        int RoamingChannelSet;
        int RoamingChannelData;
        int RoamingChannelDataOffset;
        int RoamingChannelDataLength;
        int RoamingZoneSet;
        int RoamingZoneData;
        int RoamingZoneDataOffset;
        int RoamingZoneDataLength;
        int ScanListSet;
        int ScanListData;
        int ScanListDataOffset;
        int ScanListDataLength;
        int TalkgroupSet;
        int TalkgroupData;
        int TalkgroupDataOffset;
        int TalkgroupDataLength;
        int TalkgroupOrder;
        int ZoneSet;
        int ZonesName;
        int ZoneChannels;
        int ZoneAChannel;
        int ZoneBChannel;
        int ZoneHide;
        int ZoneDataLength;
        int ZoneDataOffset;
    };

    constexpr MemoryMap D878II_MAP {
        .LocalInfo = 0x2fa0000,
        .BootImage = 0x2ac0000,
        .BK1Image = 0x2b00000,
        .BK2Image = 0x2b80000,
        .AESSet = 0x24c8000,
        .AESData = 0x24c4000,
        .AESDataOffset = 0x40,
        .AESDataLength = 0x30,
        .AmAirSet = 0,          // Not Applicable
        .AmAirData = 0,         //      ''
        .AmAirDataStride = 0,   //      ''
        .AmAirDataLength = 0,   //      ''
        .AmAirVfo = 0,          //      ''
        .AmZoneSet = 0,         //      ''
        .AmZoneScan = 0,        //      ''
        .AmZoneAChannel = 0,    //      ''
        .AmZoneData = 0,        //      ''
        .AmZoneDataStride = 0,  //      ''
        .AmZoneDataLength = 0,  //      ''
        .AnalogBookSet = 0x2900100,
        .AnalogBookId = 0x2900000,
        .AnalogBookData = 0x2940000,
        .AnalogBookDataStride = 0x18,
        .AnalogBookDataLength = 0x18,
        .Arc4Set = 0x25c1c00,
        .Arc4Data = 0x25c0c00,
        .Arc4DataOffset = 0x10,
        .Arc4DataLength = 0x10,
        .AutoRepeaterData = 0x24c2000,
        .ChannelSet = 0x24c1500,
        .ChannelData = 0x800000,
        .ChannelDataOffset = 0x40,
        .ChannelDataBlockSize = 128,
        .ChannelDataBlockOffset = 0x40000,
        .ChannelDataSecondaryOffset = 0x2000,
        .EncryptionCodeId = 0x24c1700,
        .EncryptionCodeKey = 0x24c1810,
        .GpsRoamingData = 0x2504000,
        .GpsRoamingDataLength = 0x400,
        .MasterIdData = 0x2582000,
        .MasterIdDataLength = 0x20,
        .PrefabSmsSet = 0x1640000,
        .PrefabSmsData = 0x2140000,
        .PrefabSmsDataLength = 0xd0,
        .PrefabSmsDataOffset = 0x100,
        .PrefabSmsDataBlockSize = 0x800,
        .PrefabSmsDataBlockOffset = 0x40000,
        .RadioIdSet = 0x24c1320,
        .RadioIdData = 0x2580000,
        .RadioIdDataOffset = 0x20,
        .RadioIdDataLength = 0x20,
        .ReceiveGroupSet = 0x25c0b10,
        .ReceiveGroupData = 0x2980000,
        .ReceiveGroupDataOffset = 0x200,
        .ReceiveGroupDataLength = 0x120,
        .RoamingChannelSet = 0x1042000,
        .RoamingChannelData = 0x1040000,
        .RoamingChannelDataOffset = 0x20,
        .RoamingChannelDataLength = 0x20,
        .RoamingZoneSet = 0x1042080,
        .RoamingZoneData = 0x1043000,
        .RoamingZoneDataOffset = 0x50,
        .RoamingZoneDataLength = 0x50,
        .ScanListSet = 0x24c1340,
        .ScanListData = 0x1080000,
        .ScanListDataOffset = 0x200,
        .ScanListDataLength = 0x90,
        .TalkgroupSet = 0x2640000,
        .TalkgroupData = 0x2680000,
        .TalkgroupDataOffset = 0x64,
        .TalkgroupDataLength = 0x40,
        .TalkgroupOrder = 0x4800000,
        .ZoneSet = 0x24c1300,
        .ZonesName = 0x2540000,
        .ZoneChannels = 0x1000000,
        .ZoneAChannel = 0x2500100,
        .ZoneBChannel = 0x2500300,
        .ZoneHide = 0x24c1360,
        .ZoneDataLength = 0x10,
        .ZoneDataOffset = 0x20
    };

    constexpr MemoryMap D890_MAP {
        .LocalInfo = 0x4f80000,
        .BootImage = 0x3f80000,
        .BK1Image = 0x4000000,
        .BK2Image = 0x4080000,
        .AESSet = 0x3585600,
        .AESData = 0x3580000,
        .AESDataOffset = 0x40,
        .AESDataLength = 0x30,
        .AmAirSet = 0x3884200,
        .AmAirData = 0x3880000,
        .AmAirDataStride = 0x40,
        .AmAirDataLength = 0x40,
        .AmAirVfo = 0x3884000,
        .AmZoneSet = 0x3884400,
        .AmZoneScan = 0x3884800,
        .AmZoneAChannel = 0x3884600,
        .AmZoneData = 0x3888000,
        .AmZoneDataStride = 0x80,
        .AmZoneDataLength = 0x80,
        .AnalogBookSet = 0x3800100,
        .AnalogBookId = 0x3800000,
        .AnalogBookData = 0x3801000,
        .AnalogBookDataStride = 0x40,
        .AnalogBookDataLength = 0x40,
        .Arc4Set = 0x3585620,
        .Arc4Data = 0x3584000,
        .Arc4DataOffset = 0x10,
        .Arc4DataLength = 0x10,
        .AutoRepeaterData = 0x3483200,
        .ChannelSet = 0x3482a00,
        .ChannelData = 0x1000000,
        .ChannelDataOffset = 0x80,
        .ChannelDataBlockSize = 128,
        .ChannelDataBlockOffset = 0x80000,
        .ChannelDataSecondaryOffset = 0x40,
        .EncryptionCodeId = 0x3585000,
        .EncryptionCodeKey = 0x3585100,
        .GpsRoamingData = 0x3502000,
        .GpsRoamingDataLength = 0x400,
        .MasterIdData = 0x3684000,
        .MasterIdDataLength = 0x40,
        .PrefabSmsSet = 0x2980000,
        .PrefabSmsData = 0x3180000,
        .PrefabSmsDataLength = 0x1a0,
        .PrefabSmsDataOffset = 0x200,
        .PrefabSmsDataBlockSize = 0x1000,
        .PrefabSmsDataBlockOffset = 0x80000,
        .RadioIdSet = 0x3482c40,
        .RadioIdData = 0x3680000,
        .RadioIdDataOffset = 0x40,
        .RadioIdDataLength = 0x40,
        .ReceiveGroupSet = 0x3701510,
        .ReceiveGroupData = 0x3780000,
        .ReceiveGroupDataOffset = 0x200,
        .ReceiveGroupDataLength = 0x120,
        .RoamingChannelSet = 0x2084000,
        .RoamingChannelData = 0x2080000,
        .RoamingChannelDataOffset = 0x40,
        .RoamingChannelDataLength = 0x40,
        .RoamingZoneSet = 0x2084080,
        .RoamingZoneData = 0x2085000,
        .RoamingZoneDataOffset = 0x80,
        .RoamingZoneDataLength = 0x80,
        .ScanListSet = 0x3482c60,
        .ScanListData = 0x2100000,
        .ScanListDataOffset = 0x200,
        .ScanListDataLength = 0xd0,
        .TalkgroupSet = 0x3980000,
        .TalkgroupData = 0x3a00000,
        .TalkgroupDataOffset = 0xc8,
        .TalkgroupDataLength = 0x80,
        .TalkgroupOrder = 0x3f00000,
        .ZoneSet = 0x3482c00,
        .ZonesName = 0x3600000,
        .ZoneChannels = 0x2000000,
        .ZoneAChannel = 0x3500400,
        .ZoneBChannel = 0x3500600,
        .ZoneHide = 0x3482c20,
        .ZoneDataLength = 0x20,
        .ZoneDataOffset = 0x40
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
    class AmAir;
    class AmZone;
    class Satellite;

    class Memory {

    public:
        static void init();
        static void saveData(QXmlStreamWriter &xml);
        static void saveAesEncryptionCodes(QXmlStreamWriter &xml);
        static void saveAlarmSettings(QXmlStreamWriter &xml);
        static void saveAmAir(QXmlStreamWriter &xml);
        static void saveAmZones(QXmlStreamWriter &xml);
        static void saveAnalogAddresses(QXmlStreamWriter &xml);
        static void saveAprsSettings(QXmlStreamWriter &xml);
        static void saveArc4EncryptionCodes(QXmlStreamWriter &xml);
        static void saveAutoRepeaterOffsets(QXmlStreamWriter &xml);
        static void saveChannels(QXmlStreamWriter &xml);
        static void saveDtmfSettings(QXmlStreamWriter &xml);
        static void saveEncryptionCodes(QXmlStreamWriter &xml);
        static void saveFm(QXmlStreamWriter &xml);
        static void saveGpsRoaming(QXmlStreamWriter &xml);
        static void saveHotKey(QXmlStreamWriter &xml);
        static void saveMasterId(QXmlStreamWriter &xml);
        static void saveOptionalSettings(QXmlStreamWriter &xml);
        static void savePrefabricatedSms(QXmlStreamWriter &xml);
        static void saveRadioIds(QXmlStreamWriter &xml);
        static void saveReceiveGroupCallList(QXmlStreamWriter &xml);
        static void saveRoamingChannel(QXmlStreamWriter &xml);
        static void saveRoamingZone(QXmlStreamWriter &xml);
        static void saveScanList(QXmlStreamWriter &xml);
        static void saveTalkerAliasSettings(QXmlStreamWriter &xml);
        static void saveTalkgroups(QXmlStreamWriter &xml);
        static void saveTone2Settings(QXmlStreamWriter &xml);
        static void saveTone5Settings(QXmlStreamWriter &xml);
        static void saveZones(QXmlStreamWriter &xml);
        static void saveDigitalContacts(QXmlStreamWriter &xml);

        static void loadData(QXmlStreamReader &xml);
        static void loadAesEncryptionCodes(QXmlStreamReader &xml);
        static void loadAmAir(QXmlStreamReader &xml);
        static void loadAmZones(QXmlStreamReader &xml);
        static void loadAnalogAddresses(QXmlStreamReader &xml);
        static void loadArc4EncryptionCodes(QXmlStreamReader &xml);
        static void loadAutoRepeaterOffsets(QXmlStreamReader &xml);
        static void loadChannels(QXmlStreamReader &xml);
        static void loadEncryptionCodes(QXmlStreamReader &ds);
        static void loadFm(QXmlStreamReader &ds);
        static void loadGpsRoaming(QXmlStreamReader &ds);
        static void loadPrefabricatedSms(QXmlStreamReader &ds);
        static void loadRadioIds(QXmlStreamReader &ds);
        static void loadReceiveGroupCallList(QXmlStreamReader &ds);
        static void loadRoamingChannel(QXmlStreamReader &ds);
        static void loadRoamingZone(QXmlStreamReader &ds);
        static void loadScanList(QXmlStreamReader &ds);
        static void loadTalkgroups(QXmlStreamReader &ds);
        static void loadZones(QXmlStreamReader &ds);
        static void loadDigitalContacts(QXmlStreamReader &ds);

        static void setDefaults();
        static void setDefaultMasterID();
        static void setDefaultTalkgroups();
        static void setDefaultRadioIds();

        static void linkReferences();
        static void linkZoneRef();
        static void linkChannelRef();
        static void linkScanListRef();
        static void linkRoamingZoneRef();
        static void linkHotKeyRef();
        static void linkReceiveGroupRef();
        static void linkAmZoneRef();

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
        static void initAmAir();
        static void initAmZones();

        static const MemoryMap* Map(){
            switch (Anytone::Memory::radio_model) {
                case RadioModel::D878UVII_FW400: return &D878II_MAP;
                case RadioModel::D890UV_FW103:   return &D890_MAP;
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
        static QVector<AmAir*> am_air_list;
        static QVector<AmZone*> am_zones;
        static QVector<Satellite*> satellite_data_list;
        
    };
}

#endif