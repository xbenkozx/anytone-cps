
#include "channel_edit_dialog.h"
#include "ui_channel_settings.h"
#include "main_window.h"
#include "constants.h"
#include "utils.h"
#include "contact_selection_dialog.h"
#include "arc4_encryption_code.h"
#include "aes_encryption_code.h"
#include "encryption_code.h"
#include <QStringList>


ChannelEditDialog::ChannelEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_ChannelSettings>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->index = index;
    main_window = parent;

    radio_id_list = {};
    scanlist_list = {};
    receive_group_call_list = {};

    setWindowFlags(
        Qt::WindowType::Window |
        Qt::WindowType::WindowCloseButtonHint
    );

    // csd = new ContactSelectionDialog(this);

    setupUI();
    
    connect(ui->saveBtn, &QPushButton::clicked, this, &ChannelEditDialog::saveClose);
    connect(ui->closeBtn, &QPushButton::clicked, this, &ChannelEditDialog::close);
    connect(this->ui->prevBtn, &QPushButton::clicked, this, &ChannelEditDialog::prevBtnClicked);
    connect(this->ui->nextBtn, &QPushButton::clicked, this, &ChannelEditDialog::nextBtnClicked);
    connect(this->ui->ctcssDcsDecodeCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::updateCtcssDcsCodes);
    connect(this->ui->ctcssDcsEncodeCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::updateCtcssDcsCodes);
    connect(this->ui->ctcssDcsDecodeToneCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::storeCtcssDcsTones);
    connect(this->ui->ctcssDcsEncodeToneCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::storeCtcssDcsTones);
    connect(this->ui->optionalSignalCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::updateToneCarrierType);
    connect(this->ui->digitalContactBtn, &QPushButton::clicked, this, &ChannelEditDialog::showContactSelectionDialog);
    connect(this->ui->receiveFrequencyTxt, &QLineEdit::editingFinished, this, &ChannelEditDialog::updateRxFrequency);
    connect(this->ui->transmitFrequencyTxt, &QLineEdit::editingFinished, this, &ChannelEditDialog::updateTxFrequency);
    connect(this->ui->extendEncryptionCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::setModeFormVisibility);
    connect(this->ui->channelTypeCmbx, &QComboBox::currentIndexChanged, this, &ChannelEditDialog::setModeFormVisibility);
    connect(this->ui->analogAprsMuteChbx, &QCheckBox::checkStateChanged, this, &ChannelEditDialog::analogAprsMuteToggle);

    if(index == 0) ui->prevBtn->setDisabled(true);
    if(index == Anytone::Memory::channels.size() - 1) ui->nextBtn->setDisabled(true);

    resize(790, 400);

    loadData();
}
ChannelEditDialog::~ChannelEditDialog(){}


void ChannelEditDialog::setupUI(){
    // Common Settings
    ui->channelTypeCmbx->addItems(Constants::CHANNEL_TYPE);
    ui->txPowerCmbx->addItems(Constants::TX_POWER);
    ui->bandWidthCmbx->addItems(Constants::BAND_WIDTH);
    ui->busyLockCmbx->addItems(Constants::BUSY_LOCK);
    ui->scanListCmbx->addItem("Off");
    for(Anytone::ScanList *sl : Anytone::Memory::scanlists){
        if(sl->channels.size() > 0){
            scanlist_list.push_back(sl);
            ui->scanListCmbx->addItem(sl->name, sl->id);
        }
    }
    ui->aprsReportTypeCmbx->addItems(Constants::APRS_REPORT_TYPE);
    ui->analogAprsPttModeCmbx->addItems(Constants::ANALOG_APRS_PTT_MODE);
    ui->digitalAprsPttModeCmbx->addItems(Constants::OFF_ON);
    ui->digitalAprsReportChannelCmbx->addItems(QStringList{"1", "2", "3", "4", "5", "6", "7", "8"});
    ui->excludeChannelRoamingCmbx->addItems(Constants::OFF_ON);
    ui->dmrModeCmbx->addItems(QStringList{"DMO Simplex", "Repeater", "DCDM/Double Slot", "DCDM TS Split"});
    ui->analogAprsReportFreqCmbx->addItems(QStringList{"1", "2", "3", "4", "5", "6", "7", "8"});
    
    // Analog Settings
    ui->ctcssDcsDecodeCmbx->addItems(QStringList{"Off", "CTCSS", "DCS"});
    ui->ctcssDcsEncodeCmbx->addItems(QStringList{"Off", "CTCSS", "DCS"});
    ui->squelchModeCmbx->addItems(Constants::SQL_MODE);
    ui->optionalSignalCmbx->addItems(Constants::OPTIONAL_SIGNAL);
    updateToneCarrierType();
    ui->pttIdCmbx->addItems(Constants::PTT_ID);
    // self->ui->optionalSignalCmbx->setDisabled(True) # TODO Enable if optional signals in codeplug
    // self->ui->tone5BotCmbx->setDisabled(True)
    // self->ui->tone5EotCmbx->setDisabled(True) # TODO Enable if 5Tone EOT in codplug

    // Digital Settings
    radio_id_list.clear();
    for(Anytone::RadioId *rid : Anytone::Memory::radioids){
        if(rid->dmr_id > 0){
            ui->radioIdCmbx->addItem(rid->name);
            radio_id_list.push_back(rid);
        }
    }
    
    ui->rxColorCodeCmbx->addItems(QStringList{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"});
    ui->txColorCodeCmbx->addItems(QStringList{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"});
    ui->slotCmbx->addItems(QStringList{"Slot 1", "Slot 2"});
    ui->rxGroupListCmbx->addItem("None");
    receive_group_call_list.clear();
    for(Anytone::ReceiveGroup *rgl : Anytone::Memory::receive_group_call_lists){
        ui->rxGroupListCmbx->addItem(rgl->name, rgl->id);
        receive_group_call_list.push_back(rgl);
    }

    
    ui->extendEncryptionCmbx->addItems(QStringList{"AES", "ARC4"});

    ui->digitalEncryptionCmbx->addItem("Off");
    for(Anytone::EncryptionCode *key : Anytone::Memory::encryption_keys){
        ui->digitalEncryptionCmbx->addItem(QString::number(key->index));
    }
    ui->arc4CodeCmbx->addItem("Off");
    for(Anytone::Arc4EncryptionCode *key : Anytone::Memory::arc4_encryption_keys){
        if(key->id > 0) ui->arc4CodeCmbx->addItem(QString::number(key->id));
    }
    ui->aesCodeCmbx->addItem("Off");
    for(Anytone::AesEncryptionCode *key : Anytone::Memory::aes_encryption_keys){
        if(key->id > 0) ui->aesCodeCmbx->addItem(QString::number(key->id));
    }
    ui->multiKeyCmbx->addItems(Constants::OFF_ON);
    ui->randomKeyCmbx->addItems(Constants::OFF_ON);
    ui->smsForbidCmbx->addItems(Constants::OFF_ON);


    //Additonal Stuff
    ui->txInterruptCmbx->addItems(QStringList{"Off", "Low Priority", "High Priority"});
    ui->scramblerSetCmbx->addItems(Constants::SCRAMBLER);
    ui->customScramblerCmbx->addItems(Constants::CUSTOM_SCRAMBLER);
    ui->dmrCrcIgnoreCmbx->addItems(Constants::OFF_ON);

    

    // Show/Hide Radio Specfic Items
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            ui->dmrCrcIgnoreLbl->setVisible(false);
            ui->dmrCrcIgnoreCmbx->setVisible(false);
            ui->scramblerSetLbl->setVisible(false);
            ui->scramblerSetCmbx->setVisible(false);
            ui->customScramblerLbl->setVisible(false);
            ui->customScramblerCmbx->setVisible(false);
            ui->compandChbx->setVisible(false);
            ui->qdc1200Lbl->setVisible(false);
            ui->qdc1200Cmbx->setVisible(false);
            ui->txInterruptLbl->setVisible(false);
            ui->txInterruptCmbx->setVisible(false);
            // ui->customCtcssTxt->setVisible(false);
            break;
        case Anytone::RadioModel::D890UV_FW103:
            ui->dmrCrcIgnoreLbl->setVisible(true);
            ui->dmrCrcIgnoreCmbx->setVisible(true);
            ui->scramblerSetLbl->setVisible(true);
            ui->scramblerSetCmbx->setVisible(true);
            ui->customScramblerLbl->setVisible(true);
            ui->customScramblerCmbx->setVisible(true);
            ui->compandChbx->setVisible(true);
            ui->qdc1200Lbl->setVisible(true);
            ui->qdc1200Cmbx->setVisible(true);
            ui->txInterruptLbl->setVisible(true);
            ui->txInterruptCmbx->setVisible(true);
            // ui->customCtcssTxt->setVisible(true);
            break;
        default:
            break;
    }
}
void ChannelEditDialog::loadData(){
    setWindowTitle("Channel Information Edit---" + QString::number(index+1));
    channel = Anytone::Memory::channels.at(index);

    selected_ctcss_encode_tone_idx = channel->ctcss_encode_tone;
    selected_dcs_encode_tone_idx = channel->dcs_encode_tone;
    selected_ctcss_decode_tone_idx = channel->ctcss_decode_tone;
    selected_dcs_decode_tone_idx = channel->dcs_decode_tone;

    // Set the default channel settings if it is a new channel
    if(channel->rx_frequency == 0){
        // createChannelDefaults();
    }

    ui->channelNameTxt->setText(channel->name);

    // Common Settings
    ui->receiveFrequencyTxt->setText(channel->getRxFrequencyString());
    ui->transmitFrequencyTxt->setText(channel->getTxFrequencyString());
    ui->channelTypeCmbx->setCurrentIndex(channel->channel_type);
    ui->txPowerCmbx->setCurrentIndex(channel->tx_power);
    ui->bandWidthCmbx->setCurrentIndex(channel->band_width);
    ui->busyLockCmbx->setCurrentIndex(channel->busy_lock);

    ui->aprsReportTypeCmbx->setCurrentIndex(channel->aprs_report_type);
    ui->analogAprsPttModeCmbx->setCurrentIndex(channel->analog_aprs_ptt_mode);
    ui->digitalAprsPttModeCmbx->setCurrentIndex(channel->digital_aprs_ptt_mode);
    ui->digitalAprsReportChannelCmbx->setCurrentIndex(channel->digital_aprs_report_channel);
    ui->excludeChannelRoamingCmbx->setCurrentIndex(channel->exclude_channel_roaming);
    ui->dmrModeCmbx->setCurrentIndex(channel->dmr_mode);
    ui->analogAprsReportFreqCmbx->setCurrentIndex(channel->analog_aprs_report_frequency_idx);
    ui->dmrCrcIgnoreCmbx->setCurrentIndex(channel->dmr_crc_ignore);
    ui->pttProhibitChbx->setChecked(channel->ptt_prohibit);
    ui->talkAroundChbx->setChecked(channel->talkaround);
    ui->aprsRxChbx->setChecked(channel->aprs_rx);
    ui->workAloneChbx->setChecked(channel->work_alone);
    ui->dataAckDisableChbx->setChecked(channel->data_ack_disable);
    ui->autoScanChbx->setChecked(channel->auto_scan);
    ui->analogAprsMuteChbx->setChecked(channel->analog_aprs_mute);

    // ANALOG
    ui->ctcssDcsDecodeCmbx->setCurrentIndex(channel->ctcss_dcs_decode);
    ui->ctcssDcsEncodeCmbx->setCurrentIndex(channel->ctcss_dcs_encode);
    updateCtcssDcsCodes();
    ui->customCtcssTxt->setText(QString::number((double(channel->custom_ctcss)/10), 'f', 1));
    ui->squelchModeCmbx->setCurrentIndex(channel->squelch_mode);
    ui->optionalSignalCmbx->setCurrentIndex(channel->optional_signal);
    ui->dtmfIdCmbx->setCurrentIndex(channel->dtmf_id_idx);
    ui->tone2IdCmbx->setCurrentIndex(channel->tone2_id_idx);
    ui->tone5IdCmbx->setCurrentIndex(channel->tone5_id_idx);
    ui->pttIdCmbx->setCurrentIndex(channel->ptt_id);
    ui->reverseChbx->setChecked(channel->reverse);
    ui->tone2DecodeCmbx->setCurrentIndex(channel->tone2_decode);
    ui->tone5BotCmbx->setCurrentIndex(channel->r5tone_bot);
    ui->tone5EotCmbx->setCurrentIndex(channel->r5tone_eot);

    
    ui->scramblerSetCmbx->setCurrentIndex(channel->scrambler_set);
    ui->customScramblerCmbx->setCurrentIndex(channel->custom_scrambler);

    // DIGITAL
    ui->rxColorCodeCmbx->setCurrentIndex(channel->rx_color_code_idx);
    ui->txColorCodeCmbx->setCurrentIndex(channel->tx_color_code_idx);
    ui->slotCmbx->setCurrentIndex(channel->time_slot);
    ui->digitalEncryptionCmbx->setCurrentIndex(channel->digital_encryption);
    ui->extendEncryptionCmbx->setCurrentIndex(channel->extend_encryption);
    ui->arc4CodeCmbx->setCurrentIndex(channel->arc4_encryption_key_idx);
    ui->aesCodeCmbx->setCurrentIndex(channel->aes_encryption_idx);
    ui->multiKeyCmbx->setCurrentIndex(channel->aes_multiple_key);
    ui->randomKeyCmbx->setCurrentIndex(channel->aes_random_key);
    ui->smsForbidCmbx->setCurrentIndex(channel->sms_forbid);
    ui->txInterruptCmbx->setCurrentIndex(channel->tx_interrupt);
    ui->sendTalkerAliasChbx->setChecked(channel->send_talker_alias);
    ui->callConfirmationChbx->setChecked(channel->call_confirmation);
    ui->slotSuitChbx->setChecked(channel->slot_suit);
    ui->smsConfirmationChbx->setChecked(channel->sms_confirmation);


    if(channel->contact)
        ui->digitalContactBtn->setText(channel->contact->name);
    
    if(channel->scanlist)
        ui->scanListCmbx->setCurrentIndex(scanlist_list.indexOf(channel->scanlist) + 1);

    if(channel->radioid){
        int rid_idx = radio_id_list.indexOf(channel->radioid);
        if(rid_idx != -1) ui->radioIdCmbx->setCurrentIndex(rid_idx);
    }

    if(channel->receive_group_list)
        ui->rxGroupListCmbx->setCurrentIndex(receive_group_call_list.indexOf(channel->receive_group_list) + 1);

    // updateCtcssDcsCodes();
    setModeFormVisibility();
}

void ChannelEditDialog::showContactSelectionDialog(){
    ContactSelectionDialog csd(this);
    csd.exec();
}
void ChannelEditDialog::setModeFormVisibility(){
    int mode = ui->channelTypeCmbx->currentIndex();
    switch(mode){
        case 0:
            ui->busyLockTxPresentLbl->setText("Busy Lock");
            ui->analogGroupBox->setDisabled(false);
            ui->digitalGroupBox->setDisabled(true);
            ui->dmrModeCmbx->setDisabled(true);
            ui->bandWidthCmbx->setDisabled(false);
            ui->analogAprsMuteChbx->setDisabled(false);
            ui->squelchModeCmbx->setDisabled(false);
            ui->optionalSignalCmbx->setDisabled(false);
            ui->tone2DecodeCmbx->setDisabled(false);
            break;
        case 1:
            ui->busyLockTxPresentLbl->setText("TX Present");
            ui->analogGroupBox->setDisabled(true);
            ui->digitalGroupBox->setDisabled(false);
            ui->dmrModeCmbx->setDisabled(false);
            ui->bandWidthCmbx->setDisabled(true);
            ui->bandWidthCmbx->setCurrentIndex(0);
            ui->analogAprsMuteChbx->setDisabled(true);
            ui->reverseChbx->setDisabled(true);
            ui->squelchModeCmbx->setDisabled(true);
            ui->optionalSignalCmbx->setDisabled(true);
            ui->tone2DecodeCmbx->setDisabled(true);
            break;
        case 2:
            ui->busyLockTxPresentLbl->setText("Busy Lock");
            ui->analogGroupBox->setDisabled(false);
            ui->digitalGroupBox->setDisabled(false);
            ui->dmrModeCmbx->setDisabled(false);
            ui->bandWidthCmbx->setDisabled(true);
            ui->bandWidthCmbx->setCurrentIndex(0);
            ui->analogAprsMuteChbx->setDisabled(false);
            ui->squelchModeCmbx->setDisabled(false);
            ui->optionalSignalCmbx->setDisabled(true);
            ui->tone2DecodeCmbx->setDisabled(true);
            break;
        case 3:
            ui->busyLockTxPresentLbl->setText("TX Present");
            ui->analogGroupBox->setDisabled(false);
            ui->digitalGroupBox->setDisabled(false);
            ui->dmrModeCmbx->setDisabled(false);
            ui->bandWidthCmbx->setDisabled(true);
            ui->bandWidthCmbx->setCurrentIndex(0);
            ui->analogAprsMuteChbx->setDisabled(true);
            ui->reverseChbx->setDisabled(true);
            ui->squelchModeCmbx->setDisabled(false);
            ui->optionalSignalCmbx->setDisabled(true);
            ui->tone2DecodeCmbx->setDisabled(true);
            break;
        default:
            break;
    }


    if(Anytone::Memory::optional_settings->encryption_type == 0){
        ui->digitalEncryptionCmbx->setDisabled(false);
        ui->extendEncryptionCmbx->setDisabled(true);
        ui->aesCodeCmbx->setDisabled(true);
        ui->arc4CodeCmbx->setDisabled(true);
        ui->multiKeyCmbx->setDisabled(true);
        ui->randomKeyCmbx->setDisabled(true);
    }else{
        ui->digitalEncryptionCmbx->setDisabled(true);
        ui->extendEncryptionCmbx->setDisabled(false);
        if(ui->extendEncryptionCmbx->currentIndex() == 0){ //AES
            ui->arc4CodeCmbx->setDisabled(true);
            ui->aesCodeCmbx->setDisabled(false);
            ui->multiKeyCmbx->setDisabled(false);
            ui->randomKeyCmbx->setDisabled(false);
        }else{ // ARC4
            ui->arc4CodeCmbx->setDisabled(false);
            ui->aesCodeCmbx->setDisabled(true);
            ui->multiKeyCmbx->setDisabled(true);
            ui->randomKeyCmbx->setDisabled(true);
        }
    }

    updateToneCarrierType();
}
void ChannelEditDialog::updateRxFrequency(){
    QString formatted_freq = formatFrequency(ui->receiveFrequencyTxt->text());
    if(formatted_freq.size() == 0){
        qDebug() << "Invalid Frequency";
        ui->receiveFrequencyTxt->setText(channel->getRxFrequencyString());
        return;
    }
    ui->receiveFrequencyTxt->setText(formatted_freq);
}
void ChannelEditDialog::updateTxFrequency(){
    QString formatted_freq = formatFrequency(ui->transmitFrequencyTxt->text());
    if(formatted_freq.size() == 0){
        qDebug() << "Invalid Frequency";
        ui->transmitFrequencyTxt->setText(channel->getTxFrequencyString());
        return;
    }
    ui->transmitFrequencyTxt->setText(formatted_freq);
}
void ChannelEditDialog::updateToneCarrierType(){
    if(ui->optionalSignalCmbx->currentIndex() == 0 || ui->channelTypeCmbx->currentIndex() != 0){
        ui->dtmfIdCmbx->setDisabled(true);
        ui->tone2IdCmbx->setDisabled(true);
        ui->tone5IdCmbx->setDisabled(true);
        ui->tone5BotCmbx->setDisabled(true);
        ui->tone5EotCmbx->setDisabled(true);
    }else if(ui->optionalSignalCmbx->currentIndex() == 1){
        ui->dtmfIdCmbx->setDisabled(false);
        ui->tone2IdCmbx->setDisabled(true);
        ui->tone5IdCmbx->setDisabled(true);
        ui->tone5BotCmbx->setDisabled(true);
        ui->tone5EotCmbx->setDisabled(true);
    }else if(ui->optionalSignalCmbx->currentIndex() == 2){
        ui->dtmfIdCmbx->setDisabled(true);
        ui->tone2IdCmbx->setDisabled(false);
        ui->tone5IdCmbx->setDisabled(true);
        ui->tone5BotCmbx->setDisabled(true);
        ui->tone5EotCmbx->setDisabled(true);
    }else if(ui->optionalSignalCmbx->currentIndex() == 3){
        ui->dtmfIdCmbx->setDisabled(true);
        ui->tone2IdCmbx->setDisabled(true);
        ui->tone5IdCmbx->setDisabled(false);
        ui->tone5BotCmbx->setDisabled(false);
        ui->tone5EotCmbx->setDisabled(false);
    }
}
QString ChannelEditDialog::formatFrequency(QString frequency){
    double freq = frequency.toDouble();
    if(freq > 480 || freq < 88) return "";
    freq = Format::roundFrequency(freq);
    return QString::number(freq, 'f', 5);
}
void ChannelEditDialog::analogAprsMuteToggle(){
    if(ui->analogAprsMuteChbx->isChecked()) ui->aprsRxChbx->setChecked(true);
}
void ChannelEditDialog::storeCtcssDcsTones(){
    int decode_current_idx = ui->ctcssDcsDecodeToneCmbx->currentIndex();
    if(decode_current_idx != -1){
        if(ui->ctcssDcsDecodeCmbx->currentIndex() == 1){
            selected_ctcss_decode_tone_idx = ui->ctcssDcsDecodeToneCmbx->currentIndex();
        }else if(ui->ctcssDcsDecodeCmbx->currentIndex() == 2){
            selected_dcs_decode_tone_idx = ui->ctcssDcsDecodeToneCmbx->currentIndex();
        }
    }

    int encode_current_idx = ui->ctcssDcsEncodeToneCmbx->currentIndex();
    if(encode_current_idx != -1){
        if(ui->ctcssDcsEncodeCmbx->currentIndex() == 1){
            selected_ctcss_encode_tone_idx = ui->ctcssDcsEncodeToneCmbx->currentIndex();
        }else if(ui->ctcssDcsEncodeCmbx->currentIndex() == 2){
            selected_dcs_encode_tone_idx = ui->ctcssDcsEncodeToneCmbx->currentIndex();
        }
    }
}
void ChannelEditDialog::updateCtcssDcsCodes(){
    ui->ctcssDcsDecodeToneCmbx->blockSignals(true);
    ui->ctcssDcsEncodeToneCmbx->blockSignals(true);

    if(ui->ctcssDcsDecodeCmbx->currentIndex() == 1){
        ui->ctcssDcsDecodeToneCmbx->clear();
        ui->ctcssDcsDecodeToneCmbx->addItems(Constants::CTCSS_CODE);
        ui->ctcssDcsDecodeToneCmbx->setDisabled(false);
        ui->ctcssDcsDecodeToneCmbx->setCurrentIndex(selected_ctcss_decode_tone_idx);
    }else if(ui->ctcssDcsDecodeCmbx->currentIndex() == 2){
        ui->ctcssDcsDecodeToneCmbx->clear();
        ui->ctcssDcsDecodeToneCmbx->addItems(Constants::DCS_CODE);
        ui->ctcssDcsDecodeToneCmbx->setDisabled(false);
        ui->ctcssDcsDecodeToneCmbx->setCurrentIndex(selected_dcs_decode_tone_idx);
    }else{
        ui->ctcssDcsDecodeToneCmbx->setDisabled(true);
    }

    if(ui->ctcssDcsEncodeCmbx->currentIndex() == 1){
        ui->ctcssDcsEncodeToneCmbx->clear();
        ui->ctcssDcsEncodeToneCmbx->addItems(Constants::CTCSS_CODE);
        ui->ctcssDcsEncodeToneCmbx->setDisabled(false);
        ui->ctcssDcsEncodeToneCmbx->setCurrentIndex(selected_ctcss_encode_tone_idx);
    }else if(ui->ctcssDcsEncodeCmbx->currentIndex() == 2){
        ui->ctcssDcsEncodeToneCmbx->clear();
        ui->ctcssDcsEncodeToneCmbx->addItems(Constants::DCS_CODE);
        ui->ctcssDcsEncodeToneCmbx->setDisabled(false);
        ui->ctcssDcsEncodeToneCmbx->setCurrentIndex(selected_dcs_encode_tone_idx);
    }else{
        ui->ctcssDcsEncodeToneCmbx->setDisabled(true);
    }

    ui->ctcssDcsDecodeToneCmbx->blockSignals(false);
    ui->ctcssDcsEncodeToneCmbx->blockSignals(false);
}

void ChannelEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::channels.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::channels.size() - 1);
}
void ChannelEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void ChannelEditDialog::save(){
    channel->name = ui->channelNameTxt->text();

    // Common Settings
    channel->setFrequencyStr(ui->receiveFrequencyTxt->text(), ui->transmitFrequencyTxt->text());
    channel->channel_type = ui->channelTypeCmbx->currentIndex();
    channel->tx_power = ui->txPowerCmbx->currentIndex();
    channel->band_width = ui->bandWidthCmbx->currentIndex();
    channel->busy_lock = ui->busyLockCmbx->currentIndex();
    channel->aprs_report_type = ui->aprsReportTypeCmbx->currentIndex();
    channel->analog_aprs_ptt_mode = ui->analogAprsPttModeCmbx->currentIndex();
    channel->digital_aprs_ptt_mode = ui->digitalAprsPttModeCmbx->currentIndex();
    channel->digital_aprs_report_channel = ui->digitalAprsReportChannelCmbx->currentIndex();
    channel->exclude_channel_roaming = ui->excludeChannelRoamingCmbx->currentIndex();
    channel->dmr_mode = ui->dmrModeCmbx->currentIndex();
    channel->analog_aprs_report_frequency_idx = ui->analogAprsReportFreqCmbx->currentIndex();
    channel->ptt_prohibit = ui->pttProhibitChbx->isChecked();
    channel->talkaround = ui->talkAroundChbx->isChecked();
    channel->aprs_rx = ui->aprsRxChbx->isChecked();
    channel->work_alone = ui->workAloneChbx->isChecked();
    channel->data_ack_disable = ui->dataAckDisableChbx->isChecked();
    channel->auto_scan = ui->autoScanChbx->isChecked();
    channel->analog_aprs_mute = ui->analogAprsMuteChbx->isChecked();

    // CTCSS/DCS Tone
    channel->ctcss_dcs_decode = ui->ctcssDcsDecodeCmbx->currentIndex();
    channel->ctcss_dcs_encode = ui->ctcssDcsEncodeCmbx->currentIndex();
    if(channel->ctcss_dcs_decode == 1){
        channel->ctcss_decode_tone = ui->ctcssDcsDecodeToneCmbx->currentIndex();
    }else if(channel->ctcss_dcs_decode == 2){
        channel->dcs_decode_tone = ui->ctcssDcsDecodeToneCmbx->currentIndex();
    }
    
    if(channel->ctcss_dcs_encode == 1){
        channel->ctcss_encode_tone = ui->ctcssDcsEncodeToneCmbx->currentIndex();
    }else if(channel->ctcss_dcs_encode == 2){
        channel->dcs_encode_tone = ui->ctcssDcsEncodeToneCmbx->currentIndex();
    }

    if(ui->scanListCmbx->currentIndex() == 0){
        channel->scanlist = nullptr;
    }else{
        channel->scanlist = scanlist_list.at(ui->scanListCmbx->currentIndex() - 1);
    }
    channel->custom_ctcss = qRound(ui->customCtcssTxt->text().toDouble() * 10);

    // Analog
    channel->squelch_mode = ui->squelchModeCmbx->currentIndex();
    channel->optional_signal = ui->optionalSignalCmbx->currentIndex();
    channel->dtmf_id_idx = ui->dtmfIdCmbx->currentIndex();
    channel->tone2_id_idx = ui->tone2IdCmbx->currentIndex();
    channel->tone5_id_idx = ui->tone5IdCmbx->currentIndex();
    channel->ptt_id = ui->pttIdCmbx->currentIndex();
    channel->tone2_decode = ui->tone2DecodeCmbx->currentIndex();
    channel->r5tone_bot = ui->tone5BotCmbx->currentIndex();
    channel->r5tone_eot = ui->tone5EotCmbx->currentIndex();
    channel->reverse = ui->reverseChbx->isChecked();

    // DIGITAL
    channel->rx_color_code_idx = ui->rxColorCodeCmbx->currentIndex();
    channel->tx_color_code_idx = ui->txColorCodeCmbx->currentIndex();
    channel->time_slot = ui->slotCmbx->currentIndex();
    channel->digital_encryption = ui->digitalEncryptionCmbx->currentIndex();
    channel->extend_encryption = ui->extendEncryptionCmbx->currentIndex();
    channel->aes_multiple_key = ui->multiKeyCmbx->currentIndex();
    channel->aes_random_key = ui->randomKeyCmbx->currentIndex();
    channel->sms_forbid = ui->smsForbidCmbx->currentIndex();
    channel->send_talker_alias = ui->sendTalkerAliasChbx->isChecked();
    channel->call_confirmation = ui->callConfirmationChbx->isChecked();
    channel->slot_suit = ui->slotSuitChbx->isChecked();
    channel->sms_confirmation = ui->smsConfirmationChbx->isChecked();

    uint8_t arc4_idx = 0;
    if(ui->arc4CodeCmbx->currentText() != "Off"){
        arc4_idx = ui->arc4CodeCmbx->currentText().toInt();
    }
    channel->arc4_encryption_key_idx = arc4_idx;

    uint8_t aes_idx = 0;
    if(ui->aesCodeCmbx->currentText() != "Off"){
        aes_idx = ui->aesCodeCmbx->currentText().toInt();
    }
    channel->aes_encryption_idx = aes_idx;

    uint8_t enc_idx = 0;
    if(ui->digitalEncryptionCmbx->currentText() != "Off"){
        enc_idx = ui->digitalEncryptionCmbx->currentText().toInt();
    }
    channel->digital_encryption = enc_idx;

    // Radio ID
    if(channel->contact) ui->digitalContactBtn->setText(channel->contact->name);
    Anytone::RadioId *rid = radio_id_list.at(ui->radioIdCmbx->currentIndex());
    channel->radio_id_idx = rid->id;
    channel->radioid = rid;
}
void ChannelEditDialog::saveClose(){
    save();
    close();
}