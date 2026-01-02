
#include "aprs_settings_dialog.h"
#include "ui_aprs_settings_dialog.h"
#include "user_settings.h"
#include "memory/memory.h"
#include "channel.h"
#include "constants.h"


AprsSettingsDialog::AprsSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_AprsSettingsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    setupUI();
    loadData();
    
}
AprsSettingsDialog::~AprsSettingsDialog(){}

void AprsSettingsDialog::setupUI(){

    filter_model = new AprsReceiveFilterTableModel(this);
    ui->rxFilterTableView->setModel(filter_model);
    ui->rxFilterTableView->verticalHeader()->setVisible(false);
    ui->rxFilterTableView->setSortingEnabled(false);
    ui->rxFilterTableView->setColumnWidth(0, 70);
    ui->rxFilterTableView->setColumnWidth(1, 100);
    ui->rxFilterTableView->setColumnWidth(2, 100);
    ui->rxFilterTableView->setColumnWidth(2, 100);

    auto* delegate1 = new ComboBoxDelegate(QStringList{"Off", "On"}, ui->rxFilterTableView);
    auto* delegate2 = new ComboBoxDelegate(
        QStringList{
            "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7",
            "-8", "-9", "-10", "-11", "-12", "-13", "-14", "-15", "Off"
        }, ui->rxFilterTableView);

    ui->rxFilterTableView->setItemDelegateForColumn(1, delegate1);
    ui->rxFilterTableView->setItemDelegateForColumn(3, delegate2);

    // Common
    ui->manualTxIntervalCmbx->addItems(Constants::OFF_ON);
    ui->autoTxIntervalCmbx->addItem("Off");
    for(int i = 30; i < 7651; i += 30){
        ui->autoTxIntervalCmbx->addItem(QString::number(i));
    }
    ui->roamingSupportCmbx->addItems(Constants::OFF_ON);
    ui->fixedBeaconLocationCmbx->addItem("Off");
    for(int i = 0; i < 8; i++){
        ui->fixedBeaconLocationCmbx->addItem(QString::number(i+1));
    }
    ui->aprsAltDataCmbx->addItems(Constants::APRS_ALT_DATA);
    for(int i = 3; i < 16; i++){
        ui->aprsDisTimeCmbx->addItem(QString::number(i)+"S");
    }
    ui->aprsDisTimeCmbx->addItem("Inifinity");

    ui->fix1NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix2NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix3NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix4NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix5NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix6NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix7NsCmbx->addItems(QStringList{"N", "S"});
    ui->fix8NsCmbx->addItems(QStringList{"N", "S"});

    ui->fix1EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix2EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix3EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix4EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix5EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix6EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix7EwCmbx->addItems(QStringList{"E", "W"});
    ui->fix8EwCmbx->addItems(QStringList{"E", "W"});

    // Analog
    ui->analogAprsTxToneCmbx->addItems(Constants::OFF_ON);
    for(int i = 0; i < 16; i++){ ui->toCallSsidCmbx->addItem("-" + QString::number(i)); }
    for(int i = 0; i < 16; i++){ ui->yourCallSsidCmbx->addItem("-" + QString::number(i)); }
    for(int i = 0; i < 5101; i+=20){ ui->txDelayCmbx->addItem(QString::number(i)); }
    ui->sendSubToneCmbx->addItems(QStringList{"OFF", "CTC", "DCS"});
    ui->ctcssToneCmbx->addItems(Constants::CTCSS_CODE);
    ui->dcsToneCmbx->addItems(Constants::DCS_CODE);
    for(int i = 0; i < 2551; i+=10){ ui->prewaveTimeCmbx->addItem(QString::number(i)); }
    ui->txPowerCmbx->addItems(Constants::TX_POWER);
    ui->analogAprsTxCmbx->addItems(QStringList{"Narrow", "Wide"});

    // Digital
    ui->digitalReportChannel1Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel2Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel3Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel4Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel5Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel6Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel7Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    ui->digitalReportChannel8Cmbx->addItem("Current Channel", QVariant::fromValue(nullptr));
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency ==0 || ch->channel_type != 1) continue;
        ui->digitalReportChannel1Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel2Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel3Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel4Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel5Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel6Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel7Cmbx->addItem(ch->name, QVariant::fromValue(ch));
        ui->digitalReportChannel8Cmbx->addItem(ch->name, QVariant::fromValue(ch));
    }

    ui->digitalReportSlot1Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot2Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot3Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot4Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot5Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot6Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot7Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});
    ui->digitalReportSlot8Cmbx->addItems(QStringList{"Current Slot", "Slot1", "Slot2"});

    ui->digitalReportCallType1Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType2Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType3Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType4Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType5Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType6Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType7Cmbx->addItems(Constants::CALL_TYPE);
    ui->digitalReportCallType8Cmbx->addItems(Constants::CALL_TYPE);

    ui->repeaterActivationDelayCmbx->addItem("Off");
    for(int i = 100; i < 1001; i+=100){ ui->repeaterActivationDelayCmbx->addItem(QString::number(i)); }

    ui->passAllCmbx->addItems(Constants::OFF_ON);
    
}
void AprsSettingsDialog::loadData(){
    // Common
    aprs = Anytone::Memory::aprs_settings;
    ui->manualTxIntervalCmbx->setCurrentIndex(aprs->manual_tx_interval);
    ui->autoTxIntervalCmbx->setCurrentIndex(aprs->auto_tx_interval);
    ui->roamingSupportCmbx->setCurrentIndex(aprs->roaming_support);
    ui->fixedBeaconLocationCmbx->setCurrentIndex(aprs->fixed_location_beacon);
    ui->aprsAltDataTxt->setText(QString::number(aprs->altitude));
    ui->aprsAltDataCmbx->setCurrentIndex(UserSettings::aprs_alt_type);
    ui->aprsDisTimeCmbx->setCurrentIndex(aprs->dis_time);

    ui->fix1LatTxt->setText(QString::number(aprs->fix_1_lat, 'f', 5));
    ui->fix2LatTxt->setText(QString::number(aprs->fix_2_lat, 'f', 5));
    ui->fix3LatTxt->setText(QString::number(aprs->fix_3_lat, 'f', 5));
    ui->fix4LatTxt->setText(QString::number(aprs->fix_4_lat, 'f', 5));
    ui->fix5LatTxt->setText(QString::number(aprs->fix_5_lat, 'f', 5));
    ui->fix6LatTxt->setText(QString::number(aprs->fix_6_lat, 'f', 5));
    ui->fix7LatTxt->setText(QString::number(aprs->fix_7_lat, 'f', 5));
    ui->fix8LatTxt->setText(QString::number(aprs->fix_8_lat, 'f', 5));
    
    ui->fix1NsCmbx->setCurrentIndex(aprs->fix_1_ns);
    ui->fix2NsCmbx->setCurrentIndex(aprs->fix_2_ns);
    ui->fix3NsCmbx->setCurrentIndex(aprs->fix_3_ns);
    ui->fix4NsCmbx->setCurrentIndex(aprs->fix_4_ns);
    ui->fix5NsCmbx->setCurrentIndex(aprs->fix_5_ns);
    ui->fix6NsCmbx->setCurrentIndex(aprs->fix_6_ns);
    ui->fix7NsCmbx->setCurrentIndex(aprs->fix_7_ns);
    ui->fix8NsCmbx->setCurrentIndex(aprs->fix_8_ns);

    ui->fix1LongTxt->setText(QString::number(aprs->fix_1_lng, 'f', 5));
    ui->fix2LongTxt->setText(QString::number(aprs->fix_2_lng, 'f', 5));
    ui->fix3LongTxt->setText(QString::number(aprs->fix_3_lng, 'f', 5));
    ui->fix4LongTxt->setText(QString::number(aprs->fix_4_lng, 'f', 5));
    ui->fix5LongTxt->setText(QString::number(aprs->fix_5_lng, 'f', 5));
    ui->fix6LongTxt->setText(QString::number(aprs->fix_6_lng, 'f', 5));
    ui->fix7LongTxt->setText(QString::number(aprs->fix_7_lng, 'f', 5));
    ui->fix8LongTxt->setText(QString::number(aprs->fix_8_lng, 'f', 5));

    ui->fix1EwCmbx->setCurrentIndex(aprs->fix_1_ew);
    ui->fix2EwCmbx->setCurrentIndex(aprs->fix_2_ew);
    ui->fix3EwCmbx->setCurrentIndex(aprs->fix_3_ew);
    ui->fix4EwCmbx->setCurrentIndex(aprs->fix_4_ew);
    ui->fix5EwCmbx->setCurrentIndex(aprs->fix_5_ew);
    ui->fix6EwCmbx->setCurrentIndex(aprs->fix_6_ew);
    ui->fix7EwCmbx->setCurrentIndex(aprs->fix_7_ew);
    ui->fix8EwCmbx->setCurrentIndex(aprs->fix_8_ew);

    // Analog
    ui->analogAprsTxToneCmbx->setCurrentIndex(aprs->tx_tone);
    ui->toCallTxt->setText(aprs->to_call);
    ui->toCallSsidCmbx->setCurrentIndex(aprs->to_call_ssid);
    ui->yourCallTxt->setText(aprs->your_call);
    ui->yourCallSsidCmbx->setCurrentIndex(aprs->your_call_ssid);
    ui->aprsSymbolTableTxt->setText(aprs->aprs_symbol);
    ui->aprsMapIconTxt->setText(aprs->map_icon);
    ui->digipeaterPathTxt->setText(aprs->digipeater_path);
    ui->sendingTextTxt->setText(aprs->sending_text);
    ui->txDelayCmbx->setCurrentIndex(aprs->tx_delay);
    ui->sendSubToneCmbx->setCurrentIndex(aprs->send_subtone);
    ui->ctcssToneCmbx->setCurrentIndex(aprs->ctcss);
    ui->dcsToneCmbx->setCurrentIndex(aprs->dcs);
    ui->prewaveTimeCmbx->setCurrentIndex(aprs->prewave_time);
    ui->txPowerCmbx->setCurrentIndex(aprs->tx_power);
    ui->analogAprsTxCmbx->setCurrentIndex(aprs->analog_tx_mode);

    //TODO: filters
    ui->filterPositionChbx->setChecked(aprs->filter_position);
    ui->filterMicEChbx->setChecked(aprs->filter_mic_e);
    ui->filterObjectChbx->setChecked(aprs->filter_object);
    ui->filterItemChbx->setChecked(aprs->filter_item);
    ui->filterMessageChbx->setChecked(aprs->filter_message);
    ui->filterWxReportChbx->setChecked(aprs->filter_wx_report);
    ui->filterNmeaReportChbx->setChecked(aprs->filter_nmea_report);
    ui->filterStatusReportChbx->setChecked(aprs->filter_status_report);
    ui->filterOtherChbx->setChecked(aprs->filter_other);

    ui->analogTxFreq1Txt->setText(toFrequencyString(aprs->tx_freq_1));
    ui->analogTxFreq2Txt->setText(toFrequencyString(aprs->tx_freq_2));
    ui->analogTxFreq3Txt->setText(toFrequencyString(aprs->tx_freq_3));
    ui->analogTxFreq4Txt->setText(toFrequencyString(aprs->tx_freq_4));
    ui->analogTxFreq5Txt->setText(toFrequencyString(aprs->tx_freq_5));
    ui->analogTxFreq6Txt->setText(toFrequencyString(aprs->tx_freq_6));
    ui->analogTxFreq7Txt->setText(toFrequencyString(aprs->tx_freq_7));
    ui->analogTxFreq8Txt->setText(toFrequencyString(aprs->tx_freq_8));

    // Digital
    ui->digitalReportChannel1Cmbx->setCurrentIndex(aprs->digital_report_channel_1 == 0x0fa2 ? 0 : aprs->digital_report_channel_1);
    ui->digitalReportChannel2Cmbx->setCurrentIndex(aprs->digital_report_channel_2 == 0x0fa2 ? 0 : aprs->digital_report_channel_2);
    ui->digitalReportChannel3Cmbx->setCurrentIndex(aprs->digital_report_channel_3 == 0x0fa2 ? 0 : aprs->digital_report_channel_3);
    ui->digitalReportChannel4Cmbx->setCurrentIndex(aprs->digital_report_channel_4 == 0x0fa2 ? 0 : aprs->digital_report_channel_4);
    ui->digitalReportChannel5Cmbx->setCurrentIndex(aprs->digital_report_channel_5 == 0x0fa2 ? 0 : aprs->digital_report_channel_5);
    ui->digitalReportChannel6Cmbx->setCurrentIndex(aprs->digital_report_channel_6 == 0x0fa2 ? 0 : aprs->digital_report_channel_6);
    ui->digitalReportChannel7Cmbx->setCurrentIndex(aprs->digital_report_channel_7 == 0x0fa2 ? 0 : aprs->digital_report_channel_7);
    ui->digitalReportChannel8Cmbx->setCurrentIndex(aprs->digital_report_channel_8 == 0x0fa2 ? 0 : aprs->digital_report_channel_8);

    ui->digitalReportSlot1Cmbx->setCurrentIndex(aprs->digital_report_slot_1);
    ui->digitalReportSlot2Cmbx->setCurrentIndex(aprs->digital_report_slot_2);
    ui->digitalReportSlot3Cmbx->setCurrentIndex(aprs->digital_report_slot_3);
    ui->digitalReportSlot4Cmbx->setCurrentIndex(aprs->digital_report_slot_4);
    ui->digitalReportSlot5Cmbx->setCurrentIndex(aprs->digital_report_slot_5);
    ui->digitalReportSlot6Cmbx->setCurrentIndex(aprs->digital_report_slot_6);
    ui->digitalReportSlot7Cmbx->setCurrentIndex(aprs->digital_report_slot_7);
    ui->digitalReportSlot8Cmbx->setCurrentIndex(aprs->digital_report_slot_8);

    if(aprs->digital_report_tg_1 > 0) ui->digitalReportTg1Txt->setText(QString::number(aprs->digital_report_tg_1));
    if(aprs->digital_report_tg_2 > 0) ui->digitalReportTg2Txt->setText(QString::number(aprs->digital_report_tg_2));
    if(aprs->digital_report_tg_3 > 0) ui->digitalReportTg3Txt->setText(QString::number(aprs->digital_report_tg_3));
    if(aprs->digital_report_tg_4 > 0) ui->digitalReportTg4Txt->setText(QString::number(aprs->digital_report_tg_4));
    if(aprs->digital_report_tg_5 > 0) ui->digitalReportTg5Txt->setText(QString::number(aprs->digital_report_tg_5));
    if(aprs->digital_report_tg_6 > 0) ui->digitalReportTg6Txt->setText(QString::number(aprs->digital_report_tg_6));
    if(aprs->digital_report_tg_7 > 0) ui->digitalReportTg7Txt->setText(QString::number(aprs->digital_report_tg_7));
    if(aprs->digital_report_tg_8 > 0) ui->digitalReportTg8Txt->setText(QString::number(aprs->digital_report_tg_8));

    ui->digitalReportCallType1Cmbx->setCurrentIndex(aprs->digital_report_call_type_1);
    ui->digitalReportCallType2Cmbx->setCurrentIndex(aprs->digital_report_call_type_2);
    ui->digitalReportCallType3Cmbx->setCurrentIndex(aprs->digital_report_call_type_3);
    ui->digitalReportCallType4Cmbx->setCurrentIndex(aprs->digital_report_call_type_4);
    ui->digitalReportCallType5Cmbx->setCurrentIndex(aprs->digital_report_call_type_5);
    ui->digitalReportCallType6Cmbx->setCurrentIndex(aprs->digital_report_call_type_6);
    ui->digitalReportCallType7Cmbx->setCurrentIndex(aprs->digital_report_call_type_7);
    ui->digitalReportCallType8Cmbx->setCurrentIndex(aprs->digital_report_call_type_8);

    ui->passAllCmbx->setCurrentIndex(aprs->pass_all);
}

double AprsSettingsDialog::toFrequencyDouble(int frequency){
    return double(frequency) / 100000;
};
QString AprsSettingsDialog::toFrequencyString(int frequency){
    return QString::number(toFrequencyDouble(frequency), 'f', 5);
};
double AprsSettingsDialog::degMinToDecimal(int deg, double minutes){
    return double(deg) + (minutes / 60);
}