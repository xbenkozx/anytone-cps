
#include "alert_settings_dialog.h"
#include "ui_alert_settings_dialog.h"
#include "main_window.h"
#include "constants.h"


AlertSettingsDialog::AlertSettingsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_AlertSettingsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    analog_channel_list = {};
    digital_channel_list = {};

    connect(ui->analogEmergencyAlarmCmbx, &QComboBox::currentIndexChanged, 
        this, &AlertSettingsDialog::analogAlarmUpdated);
    connect(ui->analogEniSendSelectCmbx, &QComboBox::currentIndexChanged,
        this, &AlertSettingsDialog::analogEniSendChanged);
    connect(ui->analogEniSelectCmbx, &QComboBox::currentIndexChanged,
        this, &AlertSettingsDialog::analogEniSelectChanged);
    connect(ui->digitalEniSendSelectCmbx, &QComboBox::currentIndexChanged,
        this, &AlertSettingsDialog::digitalEniSendChanged);
    connect(ui->saveBtn, &QPushButton::clicked, this, &AlertSettingsDialog::save);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &AlertSettingsDialog::close);

    ui->qdcGroupId->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->qdcGroupId));
    ui->qdcPrivateId->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->qdcPrivateId));

    setupUI();
    loadData();
}
AlertSettingsDialog::~AlertSettingsDialog(){}
void AlertSettingsDialog::setupUI(){
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
        ui->workAloneD878UVII->setVisible(false);
    }else{
        ui->qdcSettings->setVisible(false);
        ui->workAloneD890UV->setVisible(false);
    }

    // Analog
    ui->analogEmergencyAlarmCmbx->addItems(Constants::ANALOG_EMERGENCY_ALARM);
    ui->analogEniSelectCmbx->addItems(Constants::ANALOG_EMERGENCY_ENI_SELECT);
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103)
        ui->analogEniSelectCmbx->addItem("QDC1200");

    ui->analogAlarmTimeCmbx->addItems(Constants::ALARM_DURATION);
    ui->analogTxDurationCmbx->addItems(Constants::ALARM_DURATION);
    ui->analogRxDurationCmbx->addItems(Constants::ALARM_DURATION);
    ui->analogEniSendSelectCmbx->addItems(Constants::ENI_SEND_SELECT);
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency != 0 && ch->channel_type == 0){
            analog_channel_list.push_back(ch);
            ui->analogEmergencyChannelCmbx->addItem(ch->name, ch->id);
        }
    }
    ui->analogEmergencyCycleCmbx->addItem("Continuous");
    ui->analogEmergencyCycleCmbx->addItems(Constants::ALARM_DURATION);

    // Digital
    ui->digitalEmergencyAlarmCmbx->addItems(Constants::DIGITAL_EMERGENCY_ALARM);
    ui->digitalAlarmTimeCmbx->addItems(Constants::ALARM_DURATION);
    ui->digitalTxDurationCmbx->addItems(Constants::ALARM_DURATION);
    ui->digitalRxDurationCmbx->addItems(Constants::ALARM_DURATION);
    ui->digitalEniSendSelectCmbx->addItems(Constants::ENI_SEND_SELECT);
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency != 0 && ch->channel_type == 1){
            digital_channel_list.push_back(ch);
            ui->digitalEmergencyChannelCmbx->addItem(ch->name, ch->id);
        }
    }

    ui->digitalEmergencyCycleCmbx->addItem("Continuous");
    ui->digitalEmergencyCycleCmbx->addItems(Constants::ALARM_DURATION);
    ui->digitalCallTypeCmbx->addItems(Constants::CALL_TYPE);

    // Work Alone
    ui->workAloneVoiceSwitchCmbx->addItems(Constants::WORK_ALONE_VOICE_SWITCH);
    ui->workAloneAreaSwitchCmbx->addItems(Constants::WORK_ALONE_AREA_SWITCH);
    ui->workAloneMicSwitchCmbx->addItems(Constants::WORK_ALONE_MIC_SWITCH);

    for(int i = 0; i < 256; i++){
        ui->workAloneResponseTimeCmbx->addItem(QString::number(i+1) + "m");
    }

    for(int i = 0; i < 256; i++){
        ui->workAloneWarningTimeCmbx->addItem(QString::number(i+1) + "s");
    }

    ui->workAloneResponseCmbx->addItems(QStringList{"Key", "Voice Transmit"});

    // Man Down
    ui->manDownDelayCmbx->addItems(Constants::MAN_DOWN_DELAY);

    // QDC1200
    ui->qdcKindCmbx->addItems(Constants::CALL_TYPE);

}
void AlertSettingsDialog::loadData(){
    ui->analogEmergencyAlarmCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_emergency_alarm);
    ui->analogEniSelectCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_eni_type);
    ui->analogAlarmTimeCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_alarm_time - 1);
    ui->analogTxDurationCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_tx_duration - 1);
    ui->analogRxDurationCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_rx_duration - 1);
    ui->analogEniSendSelectCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_eni_send);
    ui->analogEmergencyCycleCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->analog_emergency_cycle);
    ui->digitalEmergencyAlarmCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_emergency_alarm);
    ui->digitalAlarmTimeCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_alarm_time - 1);
    ui->digitalTxDurationCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_tx_duration - 1);
    ui->digitalRxDurationCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_rx_duration - 1);
    ui->digitalEniSendSelectCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_eni_send);
    
    ui->digitalEmergencyCycleCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_emergency_cycle);
    ui->digitalCallTypeCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->digital_call_type);
    ui->workAloneVoiceSwitchCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->work_mode_voice_switch);
    ui->workAloneAreaSwitchCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->work_mode_area_switch);
    ui->workAloneMicSwitchCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->work_mode_mic_switch);
    ui->manDownChbx->setChecked(Anytone::Memory::alarm_settings->man_down);
    ui->receiveAlarmChbx->setChecked(Anytone::Memory::alarm_settings->receive_alarm);
    ui->digitalTgDmrIdTxt->setText(QString::number(Anytone::Memory::alarm_settings->digital_tg_dmr_id));

    int a_idx = analog_channel_list.indexOf(Anytone::Memory::channels[Anytone::Memory::alarm_settings->analog_emergency_channel]);
    int d_idx = analog_channel_list.indexOf(Anytone::Memory::channels[Anytone::Memory::alarm_settings->digital_emergency_channel]);

    if(a_idx != -1) ui->analogEmergencyChannelCmbx->setCurrentIndex(a_idx);
    if(d_idx != -1) ui->digitalEmergencyChannelCmbx->setCurrentIndex(d_idx);


    ui->qdcKindCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->qdc_call_type);
    ui->qdcGroupId->setText(Anytone::Memory::alarm_settings->qdc_group_id);
    ui->qdcPrivateId->setText(Anytone::Memory::alarm_settings->qdc_private_id);

    ui->workAloneResponseTimeCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->work_alone_response_time);
    ui->workAloneWarningTimeCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->work_alone_warning_time);
    ui->workAloneResponseCmbx->setCurrentIndex(Anytone::Memory::alarm_settings->work_alone_response);
}

void AlertSettingsDialog::analogEniSelectChanged(){
    ui->qdcSettings->setEnabled(ui->analogEniSelectCmbx->currentIndex() == 3);
}
void AlertSettingsDialog::analogAlarmUpdated(){
    int ci = ui->analogEmergencyAlarmCmbx->currentIndex();
    ui->analogEniSelectCmbx->setDisabled(ci==0);
    ui->analogEmergencyIdCmbx->setDisabled(ci==0);
    ui->analogAlarmTimeCmbx->setDisabled(ci!=0);
    ui->analogTxDurationCmbx->setDisabled(ci==0);
    ui->analogRxDurationCmbx->setDisabled(ci==0);
}
void AlertSettingsDialog::analogEniSendChanged(){
    ui->analogEmergencyChannelCmbx->setDisabled(ui->analogEniSendSelectCmbx->currentIndex() != 0);
}
void AlertSettingsDialog::digitalEniSendChanged(){
    ui->digitalEmergencyChannelCmbx->setDisabled(ui->digitalEniSendSelectCmbx->currentIndex()!=0);
}
void AlertSettingsDialog::save(){
    Anytone::Memory::alarm_settings->analog_emergency_alarm = ui->analogEmergencyAlarmCmbx->currentIndex();
    Anytone::Memory::alarm_settings->analog_eni_type = ui->analogEniSelectCmbx->currentIndex();
    Anytone::Memory::alarm_settings->analog_alarm_time = ui->analogAlarmTimeCmbx->currentIndex() + 1;
    Anytone::Memory::alarm_settings->analog_tx_duration = ui->analogTxDurationCmbx->currentIndex() + 1;
    Anytone::Memory::alarm_settings->analog_rx_duration = ui->analogRxDurationCmbx->currentIndex() + 1;
    Anytone::Memory::alarm_settings->analog_eni_send = ui->analogEniSendSelectCmbx->currentIndex();
    Anytone::Memory::alarm_settings->analog_emergency_channel = analog_channel_list.at(ui->analogEmergencyChannelCmbx->currentIndex())->id;
    Anytone::Memory::alarm_settings->analog_emergency_cycle = ui->analogEmergencyCycleCmbx->currentIndex();
    Anytone::Memory::alarm_settings->digital_emergency_alarm = ui->digitalEmergencyAlarmCmbx->currentIndex();
    Anytone::Memory::alarm_settings->digital_alarm_time = ui->digitalAlarmTimeCmbx->currentIndex() - 1;
    Anytone::Memory::alarm_settings->digital_tx_duration = ui->digitalTxDurationCmbx->currentIndex() - 1;
    Anytone::Memory::alarm_settings->digital_rx_duration = ui->digitalRxDurationCmbx->currentIndex() - 1;
    Anytone::Memory::alarm_settings->digital_eni_send = ui->digitalEniSendSelectCmbx->currentIndex();
    Anytone::Memory::alarm_settings->digital_emergency_channel = digital_channel_list.at(ui->digitalEmergencyChannelCmbx->currentIndex())->id;
    Anytone::Memory::alarm_settings->digital_emergency_cycle = ui->digitalEmergencyCycleCmbx->currentIndex();
    Anytone::Memory::alarm_settings->digital_call_type = ui->digitalCallTypeCmbx->currentIndex();
    Anytone::Memory::alarm_settings->work_mode_voice_switch = ui->workAloneVoiceSwitchCmbx->currentIndex();
    Anytone::Memory::alarm_settings->work_mode_area_switch = ui->workAloneAreaSwitchCmbx->currentIndex();
    Anytone::Memory::alarm_settings->work_mode_mic_switch = ui->workAloneMicSwitchCmbx->currentIndex();
    Anytone::Memory::alarm_settings->man_down_delay = ui->manDownDelayCmbx->currentIndex();
    Anytone::Memory::alarm_settings->man_down_delay = ui->manDownChbx->isChecked();
    Anytone::Memory::alarm_settings->receive_alarm = ui->receiveAlarmChbx->isChecked();
    Anytone::Memory::alarm_settings->digital_tg_dmr_id = ui->digitalTgDmrIdTxt->text().toInt();
    close();
}
