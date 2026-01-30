#include "csv.h"

#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QFileInfo>
#include <QRegularExpression>
#include "constants.h"
#include "memory/anytone_memory.h"
#include "memory/aes_encryption_code.h"
#include "memory/channel.h"
#include "memory/digital_contact.h"
#include "memory/radioid.h"
#include "memory/aprs_settings.h"
#include "memory/optional_settings.h"
#include "memory/talkgroup.h"
#include "memory/auto_repeater_offset_frequency.h"
#include "memory/dtmf_settings.h"
#include "memory/analog_address.h"
#include "memory/fm.h"
#include "memory/gps_roaming.h"
#include "memory/prefabricated_sms.h"

QMap<CsvList::ListType, QString> CsvList::loadFile(QString filepath){
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERR: Cannot open file";
        return QMap<ListType, QString>();
    }

    QFileInfo fileInfo(file.fileName());

    QTextStream tstream(&file);

    QMap<ListType, QString> list;
    while (!tstream.atEnd())
    {
        QString line = tstream.readLine();
        if(line.startsWith("#")) continue;
        QStringList str_s = line.split(",");
        if(str_s.size() < 2) continue;
        ListType id = static_cast<ListType>(str_s.at(0).toInt());
        QString fpath = fileInfo.absolutePath() + "/" + str_s.at(1);
        fpath.remove("\"");
        list.insert(id, fpath);
    }

    file.close();

    return list;
}
bool CsvList::load(QMap<ListType, QString> mlist){
    if(mlist.size() > 0) list = mlist;

    int i = 0;
    for (auto [key, value] : list.asKeyValueRange()) {
        emit update1(i, list.size(), "Importing");
        emit update2(0, 0, "");
        // qDebug() << value << key;
        if(!loadCsvFile(value, key)) return false;
        i++;
    }

    Anytone::Memory::linkReferences();

    return true;
}
bool CsvList::save(QString filepath){
    return true;
}
void CsvList::run(){
    load();
    emit finished(0);
}

bool CsvList::loadCsvFile(QString filepath, CsvList::ListType list_type){
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERR: Cannot open file";
        return false;
    }

    data_list.clear();
    headers.clear();

    emit update2(0, 0, "Loading CSV File");

    static const QRegularExpression csvComma(
        R"(,(?=(?:[^"]*"[^"]*")*[^"]*$))"
    );

    QString data = file.readAll();

    int item_count = data.split('\n').size();

    QTextStream tstream(&data, QIODevice::ReadOnly);

    // --- Read and process headers ---
    QString header_str = tstream.readLine();
    if (header_str.endsWith(','))
        header_str.chop(1);

    QStringList headers = header_str.split(csvComma);

    // Strip quotes from headers once
    for (QString &h : headers) {
        if (h.size() >= 2 && h.front() == '"' && h.back() == '"')
            h = h.mid(1, h.size() - 2);
    }

    // --- Parse rows ---
    int index = 0;
    while (!tstream.atEnd()) {
        if(index % int(item_count/100) == 0) update2(index, item_count, "Loading CSV File");
        QStringList fields = tstream.readLine().split(csvComma);
        if (fields.size() < headers.size())
            continue;

        QHash<QString, QString> row;
        row.reserve(headers.size());

        for (int i = 0; i < headers.size(); ++i) {
            QString v = fields.at(i);
            if (v.size() >= 2 && v.front() == '"' && v.back() == '"')
                v = v.mid(1, v.size() - 2);

            row.insert(headers.at(i), std::move(v));
        }

        data_list.append(std::move(row));
        index++;
    }

    file.close();

    parseData(list_type);   

    return true;
}
bool CsvList::saveCsvFile(QString filepath, CsvList::ListType list_type){
    return true;
}

void CsvList::parseData(CsvList::ListType list_type){
    switch(list_type){
        case CsvList::ListType::Channel:
            parseChannelData();
            break;
        case CsvList::ListType::DigitalContactList:
            parseDigitalContactData();
            break;
        case CsvList::ListType::RadioIdList:
            parseRadioIdData();
            break;
        case CsvList::ListType::TalkGroups:
            parseTalkgroupData();
            break;
        case CsvList::ListType::Zone:
            parseZoneData();
            break;
        case CsvList::ListType::ScanList:
            parseTalkgroupData();
            break;
        case CsvList::ListType::AnalogAddressBook:
            parseTalkgroupData();
            break;
        case CsvList::ListType::FM:
            parseTalkgroupData();
            break;
        case CsvList::ListType::ReceiveGroupCallList:
            parseTalkgroupData();
            break;
        case CsvList::ListType::Tone5Encode:
            parseTalkgroupData();
            break;
        case CsvList::ListType::Tone2Encode:
            parseTalkgroupData();
            break;
        case CsvList::DTMFEncode:
            parseDTMFEncode();
            break;
        case CsvList::HotKey_QuickCall:
            parseHotKey_QuickCall();
            break;
        case CsvList::HotKey_State:
            parseHotKey_State();
            break;
        case CsvList::HotKey_HotKey:
            parseHotKey_HotKey();
            break;
        case CsvList::AutoRepeaterOffsetFrequencies:
            parseAutoRepeaterOffsetFrequencies();
            break;
        case CsvList::RoamingChannel:
            parseRoamingChannel();
            break;
        case CsvList::RoamingZone:
            parseRoamingZone();
            break;
        case CsvList::APRS:
            parseAPRS();
            break;
        case CsvList::GPSRoaming:
            parseGPSRoaming();
            break;
        case CsvList::OptionalSettings:
            parseOptionalSettings();
            break;
        case CsvList::AlertTone:
            parseAlertTone();
            break;
        case CsvList::AESEncryptionCode:
            parseAESEncryptionCode();
            break;
        default:
            break;
    }
}
void CsvList::parseAESEncryptionCode(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::AesEncryptionCode *key = Anytone::Memory::aes_encryption_keys.at(idx);

    }
}
void CsvList::parseAlertTone(){
    Anytone::OptionalSettings *os = Anytone::Memory::optional_settings;
    QHash<QString, QString> data = data_list.at(0);
    os->call_permit_first_tone_freq = data["Freq11"].toInt();
    os->call_permit_first_tone_period = int(data["Time11"].toInt() / 10);
    os->call_permit_second_tone_freq = data["Freq12"].toInt();
    os->call_permit_second_tone_period = int(data["Time12"].toInt() / 10);
    os->call_permit_third_tone_freq = data["Freq13"].toInt();
    os->call_permit_third_tone_period = int(data["Time13"].toInt() / 10);
    os->call_permit_fourth_tone_freq = data["Freq14"].toInt();
    os->call_permit_fourth_tone_period = int(data["Time14"].toInt() / 10);
    os->call_permit_fifth_tone_freq = data["Freq15"].toInt();
    os->call_permit_fifth_tone_period = int(data["Time15"].toInt() / 10);

    os->idle_channel_first_tone_freq = data["Freq21"].toInt();
    os->idle_channel_first_tone_period = int(data["Time21"].toInt() / 10);
    os->idle_channel_second_tone_freq = data["Freq22"].toInt();
    os->idle_channel_second_tone_period = int(data["Time22"].toInt() / 10);
    os->idle_channel_third_tone_freq = data["Freq23"].toInt();
    os->idle_channel_third_tone_period = int(data["Time23"].toInt() / 10);
    os->idle_channel_fourth_tone_freq = data["Freq24"].toInt();
    os->idle_channel_fourth_tone_period = int(data["Time24"].toInt() / 10);
    os->idle_channel_fifth_tone_freq = data["Freq25"].toInt();
    os->idle_channel_fifth_tone_period = int(data["Time25"].toInt() / 10);

    os->call_reset_first_tone_freq = data["Freq31"].toInt();
    os->call_reset_first_tone_period = int(data["Time31"].toInt() / 10);
    os->call_reset_second_tone_freq = data["Freq32"].toInt();
    os->call_reset_second_tone_period = int(data["Time32"].toInt() / 10);
    os->call_reset_third_tone_freq = data["Freq33"].toInt();
    os->call_reset_third_tone_period = int(data["Time33"].toInt() / 10);
    os->call_reset_fourth_tone_freq = data["Freq34"].toInt();
    os->call_reset_fourth_tone_period = int(data["Time34"].toInt() / 10);
    os->call_reset_fifth_tone_freq = data["Freq35"].toInt();
    os->call_reset_fifth_tone_period = int(data["Time35"].toInt() / 10);

    os->call_end_first_tone_freq = data["Freq41"].toInt();
    os->call_end_first_tone_period = int(data["Time41"].toInt() / 10);
    os->call_end_second_tone_freq = data["Freq42"].toInt();
    os->call_end_second_tone_period = int(data["Time42"].toInt() / 10);
    os->call_end_third_tone_freq = data["Freq43"].toInt();
    os->call_end_third_tone_period = int(data["Time43"].toInt() / 10);
    os->call_end_fourth_tone_freq = data["Freq44"].toInt();
    os->call_end_fourth_tone_period = int(data["Time44"].toInt() / 10);
    os->call_end_fifth_tone_freq = data["Freq45"].toInt();
    os->call_end_fifth_tone_period = int(data["Time45"].toInt() / 10);

    os->call_all_first_tone_freq = data["Freq51"].toInt();
    os->call_all_first_tone_period = int(data["Time51"].toInt() / 10);
    os->call_all_second_tone_freq = data["Freq52"].toInt();
    os->call_all_second_tone_period = int(data["Time52"].toInt() / 10);
    os->call_all_third_tone_freq = data["Freq53"].toInt();
    os->call_all_third_tone_period = int(data["Time53"].toInt() / 10);
    os->call_all_fourth_tone_freq = data["Freq54"].toInt();
    os->call_all_fourth_tone_period = int(data["Time54"].toInt() / 10);
    os->call_all_fifth_tone_freq = data["Freq55"].toInt();
    os->call_all_fifth_tone_period = int(data["Time55"].toInt() / 10);
}
void CsvList::parseAnalogAddressBookData(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::AnalogAddress *address = Anytone::Memory::analog_addresses.at(idx);
        address->number = data["Number"].toInt();
        address->name = data["Name"];
    }
}
void CsvList::parseAPRS(){
    Anytone::AprsSettings *aprs = Anytone::Memory::aprs_settings;
    QHash<QString, QString> data = data_list.at(0);

    aprs->manual_tx_interval = data["Manual TX Interval[s]"].toInt();
    aprs->auto_tx_interval = data["APRS Auto TX Interval[s]"].toInt();
    aprs->roaming_support = data["Support For Roaming"].toInt();
    aprs->fixed_location_beacon = data["Fixed Location Beacon"].toInt();
    aprs->repeater_activation_delay = data["Repeater Activation Delay[ms]"].toInt();
    aprs->tx_tone = data["APRS TX Tone"].toInt();
    aprs->to_call = data["TOCALL"];
    aprs->to_call_ssid = data["TOCALL SSID"].toInt();
    aprs->your_call = data["Your Call Sign"];
    aprs->your_call_ssid = data["Your SSID"].toInt();
    aprs->aprs_symbol = data["APRS Symbol Table"];
    aprs->map_icon = data["APRS Map Icon"];
    aprs->digipeater_path = data["Digipeater Path"];
    aprs->sending_text = data["Enter Your Sending Text"];
    

    if(data["Transmit Delay[ms]"].toInt() > 0){
        aprs->tx_delay = data["Transmit Delay[ms]"].toInt() / 20;
    }

    aprs->send_subtone = data["Send Sub Tone"].toInt();
    aprs->ctcss = data["CTCSS"].toInt();

    if(data["Prewave Time[ms]"].toInt() > 0){
        aprs->prewave_time = data["Prewave Time[ms]"].toInt() / 10;
    }

    aprs->tx_power = data["Transmit Power"].toInt();

    int idx = 1;
    for(Anytone::AprsReceiveFilter *rf : aprs->receive_filters){
        rf->enabled = data["Receive Filter" + QString::number(idx)].toInt();
        rf->callsign = data["Call Sign" + QString::number(idx)];
        rf->ssid = data["SSID" + QString::number(idx)].toInt();
        idx++;
    }

    aprs->filter_position = data["POSITION"].toInt();
    aprs->filter_mic_e = data["MIC-E"].toInt();
    aprs->filter_object = data["OBJECT"].toInt();
    aprs->filter_item = data["ITEM"].toInt();
    aprs->filter_message = data["MESSAGE"].toInt();
    aprs->filter_wx_report = data["WX REPORT"].toInt();
    aprs->filter_nmea_report = data["NMEA REPORT"].toInt();
    aprs->filter_status_report = data["STATUS REPORT"].toInt();
    aprs->filter_other = data["OTHER"].toInt();

    aprs->tx_freq_1 = qRound(data["Transmission Frequency0"].toDouble() * 100000);
    aprs->tx_freq_2 = qRound(data["Transmission Frequency1"].toDouble() * 100000);
    aprs->tx_freq_3 = qRound(data["Transmission Frequency2"].toDouble() * 100000);
    aprs->tx_freq_4 = qRound(data["Transmission Frequency3"].toDouble() * 100000);
    aprs->tx_freq_5 = qRound(data["Transmission Frequency4"].toDouble() * 100000);
    aprs->tx_freq_6 = qRound(data["Transmission Frequency5"].toDouble() * 100000);
    aprs->tx_freq_7 = qRound(data["Transmission Frequency6"].toDouble() * 100000);
    aprs->tx_freq_8 = qRound(data["Transmission Frequency7"].toDouble() * 100000);

    int fix1_lat_deg = data["LatiDegree"].toInt();
    int fix1_lat_min = data["LatiMinInt"].toInt();
    int fix1_lat_mark = data["LatiMinMark"].toInt();
    int fix1_lng_deg = data["LongtiDegree"].toInt();
    int fix1_lng_min = data["LongtiMinInt"].toInt();
    int fix1_lng_mark = data["LongtiMinMark"].toInt();
    
    aprs->fix_1_ns = data["North or South"].toInt();
    aprs->fix_1_ew = data["East or West Hemisphere"].toInt();



    aprs->fix_1_lat = Anytone::AprsSettings::degMinToDecimal(fix1_lat_deg, fix1_lat_min + qRound(double(fix1_lat_mark / 100)));
    aprs->fix_1_lng = Anytone::AprsSettings::degMinToDecimal(fix1_lng_deg, fix1_lng_min + qRound(double(fix1_lng_mark / 100)));

    aprs->digital_report_channel_1 = data["channel1"].toInt();
    aprs->digital_report_channel_2 = data["channel2"].toInt();
    aprs->digital_report_channel_3 = data["channel3"].toInt();
    aprs->digital_report_channel_4 = data["channel4"].toInt();
    aprs->digital_report_channel_5 = data["channel5"].toInt();
    aprs->digital_report_channel_6 = data["channel6"].toInt();
    aprs->digital_report_channel_7 = data["channel7"].toInt();
    aprs->digital_report_channel_8 = data["channel8"].toInt();

    aprs->digital_report_slot_1 = data["slot1"].toInt();
    aprs->digital_report_slot_2 = data["slot2"].toInt();
    aprs->digital_report_slot_3 = data["slot3"].toInt();
    aprs->digital_report_slot_4 = data["slot4"].toInt();
    aprs->digital_report_slot_5 = data["slot5"].toInt();
    aprs->digital_report_slot_6 = data["slot6"].toInt();
    aprs->digital_report_slot_7 = data["slot7"].toInt();
    aprs->digital_report_slot_8 = data["slot8"].toInt();

    aprs->digital_report_tg_1 = data["Aprs Tg1"].toInt();
    aprs->digital_report_tg_2 = data["Aprs Tg2"].toInt();
    aprs->digital_report_tg_3 = data["Aprs Tg3"].toInt();
    aprs->digital_report_tg_4 = data["Aprs Tg4"].toInt();
    aprs->digital_report_tg_5 = data["Aprs Tg5"].toInt();
    aprs->digital_report_tg_6 = data["Aprs Tg6"].toInt();
    aprs->digital_report_tg_7 = data["Aprs Tg7"].toInt();
    aprs->digital_report_tg_8 = data["Aprs Tg8"].toInt();

    aprs->digital_report_call_type_1 = data["Call Type1"].toInt();
    aprs->digital_report_call_type_2 = data["Call Type2"].toInt();
    aprs->digital_report_call_type_3 = data["Call Type3"].toInt();
    aprs->digital_report_call_type_4 = data["Call Type4"].toInt();
    aprs->digital_report_call_type_5 = data["Call Type5"].toInt();
    aprs->digital_report_call_type_6 = data["Call Type6"].toInt();
    aprs->digital_report_call_type_7 = data["Call Type7"].toInt();
    aprs->digital_report_call_type_8 = data["Call Type8"].toInt();


}
void CsvList::parseARC4EncryptionCode(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::Arc4EncryptionCode *key = Anytone::Memory::arc4_encryption_keys.at(idx);

    }
}
void CsvList::parseAutoRepeaterOffsetFrequencies(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::AutoRepeaterOffsetFrequency *arf = Anytone::Memory::ar_offset_frequencies.at(idx);
        arf->frequency = qRound(data["Offset Frequency"].toDouble() * 100000);
    }
}
void CsvList::parseChannelData(){
    for(QHash<QString, QString> ch_data : data_list){
        int idx = ch_data["No."].toInt() - 1;
        Anytone::Channel *ch = Anytone::Memory::channels.at(idx);
        ch->name = ch_data["Channel Name"];
        ch->setFrequencyStr(ch_data["Receive Frequency"], ch_data["Transmit Frequency"]);
        if(Constants::CHANNEL_TYPE.indexOf(ch_data["Channel Type"]) != -1) 
            ch->channel_type = Constants::CHANNEL_TYPE.indexOf(ch_data["Channel Type"]);

        if(Constants::TX_POWER.indexOf(ch_data["Transmit Power"]) != -1) 
            ch->tx_power = Constants::TX_POWER.indexOf(ch_data["Transmit Power"]);

        if(Constants::BAND_WIDTH.indexOf(ch_data["Band Width"]) != -1) 
            ch->band_width = Constants::BAND_WIDTH.indexOf(ch_data["Band Width"]);

        if(Constants::CTCSS_CODE.indexOf(ch_data["CTCSS/DCS Decode"]) != -1){
            ch->ctcss_dcs_decode = 1;
            ch->ctcss_decode_tone = Constants::CTCSS_CODE.indexOf(ch_data["CTCSS/DCS Decode"]);
        }else if(Constants::DCS_CODE.indexOf(ch_data["CTCSS/DCS Decode"]) != -1){
            ch->ctcss_dcs_decode = 2;
            ch->dcs_decode_tone = Constants::DCS_CODE.indexOf(ch_data["CTCSS/DCS Decode"]);
        }

        if(Constants::CTCSS_CODE.indexOf(ch_data["CTCSS/DCS Encode"]) != -1){
            ch->ctcss_dcs_encode = 1;
            ch->ctcss_encode_tone = Constants::CTCSS_CODE.indexOf(ch_data["CTCSS/DCS Encode"]);
        }else if(Constants::DCS_CODE.indexOf(ch_data["CTCSS/DCS Encode"]) != -1){
            ch->ctcss_dcs_encode = 2;
            ch->dcs_encode_tone = Constants::DCS_CODE.indexOf(ch_data["CTCSS/DCS Encode"]);
        }

        ch->temp_contact_tg = ch_data["Contact TG/DMR ID"].toInt();
        ch->temp_radio_id_name = ch_data["Radio ID"];

        if(Constants::BUSY_LOCK.indexOf(ch_data["Busy Lock/TX Permit"]) != -1) 
            ch->busy_lock = Constants::BUSY_LOCK.indexOf(ch_data["Busy Lock/TX Permit"]);

        if(Constants::SQL_MODE.indexOf(ch_data["Squelch Mode"]) != -1) 
            ch->squelch_mode = Constants::SQL_MODE.indexOf(ch_data["Squelch Mode"]);

        if(Constants::PTT_ID.indexOf(ch_data["PTT ID"]) != -1) 
            ch->ptt_id = Constants::PTT_ID.indexOf(ch_data["PTT ID"]);
            
        ch->rx_color_code_idx = ch_data["RX Color Code"].toInt();
        ch->temp_scan_list_name = ch_data["Scan List"];
        ch->temp_receive_group_name = ch_data["Receive Group List"];

        if(Constants::OFF_ON.indexOf(ch_data["PTT Prohibit"]) != -1) 
            ch->reverse = Constants::OFF_ON.indexOf(ch_data["PTT Prohibit"]);

        if(Constants::OFF_ON.indexOf(ch_data["Reverse"]) != -1) 
            ch->reverse = Constants::OFF_ON.indexOf(ch_data["Reverse"]);

        if(Constants::OFF_ON.indexOf(ch_data["Slot Suit"]) != -1) 
            ch->slot_suit = Constants::OFF_ON.indexOf(ch_data["Slot Suit"]);

        if(Constants::OFF_ON.indexOf(ch_data["Call Confirmation"]) != -1) 
            ch->call_confirmation = Constants::OFF_ON.indexOf(ch_data["Call Confirmation"]);

        if(Constants::OFF_ON.indexOf(ch_data["Talk Around(Simplex)"]) != -1) 
            ch->talkaround = Constants::OFF_ON.indexOf(ch_data["Talk Around(Simplex)"]);

        if(Constants::OFF_ON.indexOf(ch_data["Work Alone"]) != -1) 
            ch->work_alone = Constants::OFF_ON.indexOf(ch_data["Work Alone"]);

        if(Constants::OFF_ON.indexOf(ch_data["Ranging"]) != -1) 
            ch->ranging= Constants::OFF_ON.indexOf(ch_data["Ranging"]);

        if(Constants::OFF_ON.indexOf(ch_data["APRS RX"]) != -1) 
            ch->aprs_rx = Constants::OFF_ON.indexOf(ch_data["APRS RX"]);
    }
}
void CsvList::parseDigitalContactData(){
    qDebug() << data_list.size();
    int i = 0;
    int data_size = data_list.size();
    for(QHash<QString, QString> data : data_list){
        if(i % int(data_size/100) == 0) emit update2(i, data_size, "Importing Digital Contacts");
        int idx = data["No."].toInt() - 1;
        Anytone::DigitalContact *dc = Anytone::Memory::digital_contacts.at(idx);
        dc->radio_id = data["Radio ID"].toInt();
        dc->callsign = data["Callsign"];
        dc->name = data["Name"];
        dc->city = data["City"];
        dc->state = data["State"];
        dc->country = data["Country"];
        dc->remarks = data["Remarks"];
        
        int call_type = Constants::CALL_TYPE.indexOf(data["Call Type"]);
        int call_alert = Constants::CALL_TYPE.indexOf(data["Call Alert"]);
        if(call_type != -1) dc->call_type = call_type;
        if(call_alert != -1) dc->call_alert = call_alert;
        i++;
    }
}
void CsvList::parseDTMFEncode(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::DTMFSettings *dtmf = Anytone::Memory::dtmf_settings;
        
    }
}
void CsvList::parseFM(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::FM *fm = Anytone::Memory::fm_channels.at(idx);
        fm->frequency = qRound(data["Frequency[MHz]"].toDouble() * 100000);
        if(QStringList{"Del", "Add"}.indexOf(data["Scan"]) != -1) fm->scan_add = QStringList{"Del", "Add"}.indexOf(data["Scan"]);
    }
}
void CsvList::parseGPSRoaming(){
    int idx = 0;
    for(QHash<QString, QString> data : data_list){
        Anytone::GpsRoaming *gps = Anytone::Memory::gps_roaming_list.at(idx);
        gps->enabled = data["OnOff"].toInt();
        gps->zone_idx = data["Zone"].toInt();

        gps->lat_degree = data["Latitude Degree"].toInt();
        gps->north_south = data["North or South"].toInt();
        gps->long_degree =  data["Longtitude Degree"].toInt();
        gps->east_west= data["East or West"].toInt();

        gps->lat_minute = data["Latitude Minute"].toDouble();
        gps->lat_minute_decimal = data["Latitude Minute1"].toDouble();
        gps->long_minute = data["Longtitude Minute"].toDouble();
        gps->long_minute_decimal = data["Longtitude Minute1"].toDouble();
        
        gps->radius= data["Radius(Meter)"].toInt();
        
        idx += 1;
    }
}
void CsvList::parseHotKey_HotKey(){
    Anytone::Hotkey *hotkey = Anytone::Memory::hotkey;
    // QHash<QString, QString> data = list.at(0);
}
void CsvList::parseHotKey_QuickCall(){
    Anytone::Hotkey *hotkey = Anytone::Memory::hotkey;
    // QHash<QString, QString> data = list.at(0);
}
void CsvList::parseHotKey_State(){
    Anytone::Hotkey *hotkey = Anytone::Memory::hotkey;
    // QHash<QString, QString> data = list.at(0);
}
void CsvList::parseOptionalSettings(){
    Anytone::OptionalSettings *os = Anytone::Memory::optional_settings;
    QHash<QString, QString> data = data_list.at(0);
}
void CsvList::parsePrefabricatedSms(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::PrefabricatedSms *sms = Anytone::Memory::prefabricated_sms_list.at(idx);
        sms->text = data["Text"];
    }
}
void CsvList::parseRadioIdData(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        if(idx >= Anytone::Memory::radioids.size()) continue;
        Anytone::RadioId *tg = Anytone::Memory::radioids.at(idx);

        tg->dmr_id = data["Radio ID"].toInt();
        tg->name = data["Name"];
    }
}
void CsvList::parseReceiveGroupCallList(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::ReceiveGroup *rcgl = Anytone::Memory::receive_group_call_lists.at(idx);

    }
}
void CsvList::parseRoamingChannel(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::RoamingChannel *ch = Anytone::Memory::roaming_channels.at(idx);

    }
}
void CsvList::parseRoamingZone(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::RoamingZone *zone = Anytone::Memory::roaming_zones.at(idx);

    }
}
void CsvList::parseScanListData(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::ScanList *sl = Anytone::Memory::scanlists.at(idx);

    }
}
void CsvList::parseTalkgroupData(){
    for(QHash<QString, QString> ch_data : data_list){
        int idx = ch_data["No."].toInt() - 1;
        Anytone::Talkgroup *tg = Anytone::Memory::talkgroups.at(idx);

        tg->dmr_id = ch_data["Radio ID"].toInt();
        tg->name = ch_data["Name"];

        if(Constants::CALL_TYPE.indexOf(ch_data["Call Type"]) != -1) 
            tg->call_type = Constants::CALL_TYPE.indexOf(ch_data["Call Type"]);

        if(Constants::CALL_ALERT.indexOf(ch_data["Call Alert"]) != -1) 
            tg->call_alert = Constants::CALL_ALERT.indexOf(ch_data["Call Alert"]);

    }
}
void CsvList::parseTone5Encode(){
    Anytone::Tone5Settings *tone5 = Anytone::Memory::tone5_settings;
    QHash<QString, QString> data = data_list.at(0);
}
void CsvList::parseTone2Encode(){
    Anytone::Tone2Settings *tone2 = Anytone::Memory::tone2_settings;
    QHash<QString, QString> data = data_list.at(0);
}
void CsvList::parseZoneData(){
    for(QHash<QString, QString> data : data_list){
        int idx = data["No."].toInt() - 1;
        Anytone::Zone *zone = Anytone::Memory::zones.at(idx);
        zone->name = data["Zone Name"];
        zone->hide = data["Zone Hide"].toInt();

        QStringList member_names = data["Zone Channel Member"].split("|");
        QStringList member_rx_freq = data["Zone Channel Member RX Frequency"].split("|");
        QStringList member_tx_freq = data["Zone Channel Member TX Frequency"].split("|");

        zone->temp_a_channel_name = {data["A Channel"], data["A Channel RX Frequency"], data["A Channel TX Frequency"]};
        zone->temp_b_channel_name = {data["B Channel"], data["B Channel RX Frequency"], data["B Channel TX Frequency"]};

        for(int i = 0; i < member_names.size(); i++){
            QString name = member_names.at(i);
            QString rx_freq = member_rx_freq.at(i);
            QString tx_freq = member_tx_freq.at(i);

            QVector<QString> member = {name, rx_freq, tx_freq};
            zone->temp_member_channels.append(member);
        }

    }
}
