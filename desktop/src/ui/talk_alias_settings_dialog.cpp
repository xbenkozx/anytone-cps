
#include "talk_alias_settings_dialog.h"
#include "ui_talk_alias_settings_dialog.h"
#include "memory/at_memory.h"
#include "talk_alias_settings.h"
#include "constants.h"


TalkAliasSettingsDialog::TalkAliasSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_TalkAliasSettingsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TalkAliasSettingsDialog::save);

    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            ui->displayPriorityCmbx->addItems(Constants::TALKALIAS_DISPLAY_PRIORITY_878);
            break;
        case Anytone::RadioModel::D890UV_FW103:
            ui->displayPriorityCmbx->addItems(Constants::TALKALIAS_DISPLAY_PRIORITY_890);
            break;
    }

    ui->dataFormatCmbx->addItems(Constants::TALKALIAS_DATA_FORMAT);
    
}
TalkAliasSettingsDialog::~TalkAliasSettingsDialog(){}
void TalkAliasSettingsDialog::loadData(){
    ui->displayPriorityCmbx->setCurrentIndex(Anytone::Memory::talk_alias_settings->display_priority);
    ui->dataFormatCmbx->setCurrentIndex(Anytone::Memory::talk_alias_settings->data_format);
}
void TalkAliasSettingsDialog::save(){
    Anytone::Memory::talk_alias_settings->display_priority = ui->displayPriorityCmbx->currentIndex();
    Anytone::Memory::talk_alias_settings->data_format = ui->dataFormatCmbx->currentIndex();
}
