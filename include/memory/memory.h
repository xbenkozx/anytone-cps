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

namespace Anytone {

    enum RadioModel {
        None,
        D878UVII,
        D890UV
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

    class Memory {

    public:
        static void init();
        static void saveData(QDataStream &ds);
        static void loadData(QDataStream &ds);

        static void setDefaults(){
            Memory::setDefaultMasterID();
        }

        static void setDefaultMasterID(){
            Anytone::Memory::master_radio_id->dmr_id = 12345678;
            Anytone::Memory::master_radio_id->name = "My Radio";
            Anytone::Memory::master_radio_id->used = false;
        }

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

        static RadioModel radio_model;
        static QString radio_band;
        static QString radio_version;
        static uint8_t radio_mode;

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

        
    };
}

#endif