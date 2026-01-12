
#include "tone2_settings_dialog.h"
#include "ui_tone2_settings_dialog.h"
#include "main_window.h"


Tone2SettingsDialog::Tone2SettingsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_Tone2SettingsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &Tone2SettingsDialog::save);

    auto* encode_table_delegate = new Tone2EncodeTableModelDelegate(ui->encodeTableView);
    ui->encodeTableView->setItemDelegateForColumn(1, encode_table_delegate);
    ui->encodeTableView->setItemDelegateForColumn(2, encode_table_delegate);
    ui->encodeTableView->setItemDelegateForColumn(3, encode_table_delegate);

    auto* decode_table_delegate = new Tone2DecodeTableModelDelegate(ui->encodeTableView);
    ui->decodeTableView->setItemDelegateForColumn(1, decode_table_delegate);
    ui->decodeTableView->setItemDelegateForColumn(2, decode_table_delegate);
    ui->decodeTableView->setItemDelegateForColumn(3, decode_table_delegate);

    encode_table_model = new Tone2EncodeTableModel(this);
    ui->encodeTableView->setModel(encode_table_model);
    ui->encodeTableView->verticalHeader()->setVisible(false);
    ui->encodeTableView->setSortingEnabled(false);
    ui->encodeTableView->setColumnWidth(0, 70);
    ui->encodeTableView->setColumnWidth(1, 100);
    ui->encodeTableView->setColumnWidth(2, 100);
    ui->encodeTableView->setColumnWidth(3, 100);

    decode_table_model = new Tone2DecodeTableModel(this);
    ui->decodeTableView->setModel(decode_table_model);
    ui->decodeTableView->verticalHeader()->setVisible(false);
    ui->decodeTableView->setSortingEnabled(false);
    ui->decodeTableView->setColumnWidth(0, 70);
    ui->decodeTableView->setColumnWidth(1, 100);
    ui->decodeTableView->setColumnWidth(2, 100);
    ui->decodeTableView->setColumnWidth(3, 200);
    ui->decodeTableView->setColumnWidth(3, 200);

    setupUI();
    loadData();
    
}
Tone2SettingsDialog::~Tone2SettingsDialog(){}
void Tone2SettingsDialog::setupUI(){
    for(int i = 5; i < 101; i++){
        ui->tone1DurationCmbx->addItem(QString::number(i/10, 'f', 1));
        ui->tone2DurationCmbx->addItem(QString::number(i/10, 'f', 1));
        ui->longToneDurationCmbx->addItem(QString::number(i/10, 'f', 1));
    }
    for(int i = 0; i < 21; i++){
        ui->gapTimeCmbx->addItem(QString::number(i*100));
    }
    for(int i = 0; i < 251; i++){
        ui->autoResetTimeCmbx->addItem(QString::number(i));
    }

}
void Tone2SettingsDialog::loadData(){
    tone2 = Anytone::Memory::tone2_settings;
    ui->tone1DurationCmbx->setCurrentIndex(tone2->encode_tone_1_duration);
    ui->tone2DurationCmbx->setCurrentIndex(tone2->encode_tone_2_duration);
    ui->longToneDurationCmbx->setCurrentIndex(tone2->encode_long_tone_duration);
    ui->gapTimeCmbx->setCurrentIndex(tone2->encode_gap_time);
    ui->autoResetTimeCmbx->setCurrentIndex(tone2->encode_auto_reset_time);
    ui->sideToneChbx->setChecked(tone2->encode_side_tone);

    // TODO: Load table model

}
void Tone2SettingsDialog::save(){
    tone2->encode_tone_1_duration = ui->tone1DurationCmbx->currentIndex();
    tone2->encode_tone_2_duration = ui->tone2DurationCmbx->currentIndex();
    tone2->encode_long_tone_duration = ui->longToneDurationCmbx->currentIndex();
    tone2->encode_gap_time = ui->gapTimeCmbx->currentIndex();
    tone2->encode_auto_reset_time = ui->autoResetTimeCmbx->currentIndex();
    tone2->encode_side_tone = ui->sideToneChbx->isChecked();
}
