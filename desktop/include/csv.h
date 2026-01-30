#ifndef CSV_H
#define CSV_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QStringList>
#include <QRunnable>
#include <QObject>

class CsvList : public QObject, public QRunnable {

    Q_OBJECT

public:
    enum ListType {
        Channel,
        RadioIdList,
        Zone,
        ScanList,
        AnalogAddressBook,
        TalkGroups,
        PrefabricatedSms,
        FM,
        ReceiveGroupCallList,
        Tone5Encode,
        Tone2Encode,
        DTMFEncode,
        HotKey_QuickCall,
        HotKey_State,
        HotKey_HotKey,
        DigitalContactList,
        AutoRepeaterOffsetFrequencies,
        RoamingChannel,
        RoamingZone,
        APRS,
        GPSRoaming,
        OptionalSettings,
        AlertTone,
        AESEncryptionCode,
        ARC4EncryptionCode
    };
    
    CsvList(){}
    CsvList(QMap<ListType, QString> list) : list(list) {}
    ~CsvList(){}

    void run();
    QMap<CsvList::ListType, QString> list;

    bool load(QMap<ListType, QString> list = {});
    bool save(QString filepath);
    static QMap<ListType, QString> loadFile(QString filepath);

    bool loadCsvFile(QString filepath, CsvList::ListType list_type);
    bool saveCsvFile(QString filepath, CsvList::ListType list_type);
    void parseData(CsvList::ListType list_type);
    void parseAESEncryptionCode();
    void parseAlertTone();
    void parseAnalogAddressBookData();
    void parseAPRS();
    void parseARC4EncryptionCode();
    void parseAutoRepeaterOffsetFrequencies();
    void parseChannelData();
    void parseDigitalContactData();
    void parseDTMFEncode();
    void parseFM();
    void parseGPSRoaming();
    void parseHotKey_HotKey();
    void parseHotKey_QuickCall();
    void parseHotKey_State();
    void parseOptionalSettings();
    void parsePrefabricatedSms();
    void parseRadioIdData();
    void parseReceiveGroupCallList();
    void parseRoamingChannel();
    void parseRoamingZone();
    void parseScanListData();
    void parseTalkgroupData();
    void parseTone5Encode();
    void parseTone2Encode();
    void parseZoneData();    

    QStringList headers;
    QVector<QHash<QString, QString>> data_list;

signals:
    void finished(const int &result);
    void update1(const int &val, const int &max, const QString &text);
    void update2(const int &val, const int &max, const QString &text);
};


#endif