
#include "tone5_settings_dialog.h"
#include "ui_tone5_settings_dialog.h"
#include "main_window.h"
#include "constants.h"
#include "utils.h"


Tone5SettingsDialog::Tone5SettingsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_Tone5SettingsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Tone5SettingsDialog::save);
    connect(ui->decodeStandardCmbx, &QComboBox::currentIndexChanged, this, &Tone5SettingsDialog::decodeStandardChanged);

    setupUI();
    loadData();
    
}
Tone5SettingsDialog::~Tone5SettingsDialog(){}
void Tone5SettingsDialog::setupUI(){

    auto* table_delegate = new Tone5TableModelDelegate(ui->tableView);
    ui->tableView->setItemDelegateForColumn(2, table_delegate);
    ui->tableView->setItemDelegateForColumn(3, table_delegate);
    ui->tableView->setItemDelegateForColumn(4, table_delegate);
    ui->tableView->setItemDelegateForColumn(5, table_delegate);

    table_model = new Tone5TableModel(this);
    ui->tableView->setModel(table_model);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);
    ui->tableView->setColumnWidth(0, 30);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 300);
    ui->tableView->setColumnWidth(3, 125);
    ui->tableView->setColumnWidth(4, 125);


    ui->decodingResponseCmbx->addItems(Constants::DECODING_RESPONSE);
    ui->icDecodingResponseCmbx->addItems(Constants::DECODING_RESPONSE);
    ui->decodeStandardCmbx->addItems(Constants::DECODING_STANDARD);
    ui->botStandardCmbx->addItems(Constants::DECODING_STANDARD);
    ui->eotStandardCmbx->addItems(Constants::DECODING_STANDARD);

    for(int i = 30; i < 101; i++){
        ui->timeDecodeToneCmbx->addItem(QString::number(i));
        ui->botToneTimeCmbx->addItem(QString::number(i));
        ui->eotToneTimeCmbx->addItem(QString::number(i));
    }

    for(int i = 0; i < 201; i++){
        ui->decodeTimeCmbx->addItem(QString::number(i*10));
    }

    for(int i = 0; i < 256; i++){
        if(i > 0){
            ui->pretimeCmbx->addItem(QString::number(i*10));
            ui->timeLapseCmbx->addItem(QString::number(i*10));
            ui->firstToneLengthCmbx->addItem(QString::number(i*10));
        }
        ui->stopTimeCmbx->addItem(QString::number(i*10));
        if(i < 251) ui->firstToneAfterStopCmbx->addItem(QString::number(i*10));
    }

    for(int i = 0; i < 251; i++){
        ui->autoResetTimeCmbx->addItem(QString::number(i));
    }

    ui->pttIdPauseTimeCmbx->addItem("Off");
    for(int i = 5; i < 76; i++){
        ui->pttIdPauseTimeCmbx->addItem(QString::number(i));
    }

    ui->stopCodeCmbx->addItems(QStringList{"Off", "B", "C", "D", "F"});

    ui->functionOptionCmbx->addItems(Constants::FUNCTION_OPTION);

    for(int i = 0; i < 16; i++){
        ui->informationIdCmbx->addItem(QString::number(i+1));
    }

}
void Tone5SettingsDialog::loadData(){
    tone5 = Anytone::Memory::tone5_settings;

    ui->selfIdTxt->setText(tone5->self_id);
    ui->decodeStandardCmbx->setCurrentIndex(tone5->decode_standard);
    ui->decodingResponseCmbx->setCurrentIndex(tone5->decoding_response);
    ui->timeDecodeToneCmbx->setCurrentIndex(tone5->decode_tone_time);
    ui->decodeTimeCmbx->setCurrentIndex(tone5->decode_time);
    ui->decUnit1Chbx->setChecked(Bit::test(tone5->dec_units, 0));
    ui->decUnit2Chbx->setChecked(Bit::test(tone5->dec_units, 1));
    ui->decUnit3Chbx->setChecked(Bit::test(tone5->dec_units, 2));
    ui->decUnit4Chbx->setChecked(Bit::test(tone5->dec_units, 3));
    ui->decUnit5Chbx->setChecked(Bit::test(tone5->dec_units, 4));
    ui->decUnit6Chbx->setChecked(Bit::test(tone5->dec_units, 5));
    ui->decUnit7Chbx->setChecked(Bit::test(tone5->dec_units, 6));
    ui->dispAnytIdChbx->setChecked(tone5->dis_anyid);

    ui->pretimeCmbx->setCurrentIndex(tone5->pretime);
    ui->autoResetTimeCmbx->setCurrentIndex(tone5->auto_reset_time);
    ui->timeLapseCmbx->setCurrentIndex(tone5->time_after_decode);
    ui->pttIdPauseTimeCmbx->setCurrentIndex(tone5->pause_time);
    ui->firstToneLengthCmbx->setCurrentIndex(tone5->first_tone_length);
    if(tone5->stop_code == 0){
        ui->stopCodeCmbx->setCurrentIndex(0);
    }else{
        ui->stopCodeCmbx->setCurrentIndex(tone5->stop_code-4);
    }
    ui->stopTimeCmbx->setCurrentIndex(tone5->stop_time_length);
    ui->firstToneAfterStopCmbx->setCurrentIndex(tone5->first_tone_after_stop);
    ui->sideToneChbx->setChecked(tone5->encode_side_tone);
    ui->botStandardCmbx->setCurrentIndex(tone5->ptt_bot_standard);
    ui->botToneTimeCmbx->setCurrentIndex(tone5->ptt_bot_decode_time);
    ui->botEncodeIdTxt->setText(tone5->ptt_bot_encode_id);
    ui->eotStandardCmbx->setCurrentIndex(tone5->ptt_eot_standard);
    ui->eotToneTimeCmbx->setCurrentIndex(tone5->ptt_eot_decode_time);
    ui->eotEncodeIdTxt->setText(tone5->ptt_eot_encode_id);


}
void Tone5SettingsDialog::decodeStandardChanged(){
    QString text = Constants::DECODING_STANDARD_DESC.at(ui->decodeStandardCmbx->currentIndex());
    text.replace(QString("\n"), QString("<br/>"));
    ui->decodeStandardDescTxt->setHtml("<div style=\"text-align:center;\"" + text + "</div>");
}
void Tone5SettingsDialog::save(){
    
}
