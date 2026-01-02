#include "read_write_options_dialog.h"
#include "ui_read_write_options_dialog.h"
#include "main_window.h"
#include "user_settings.h"
#include "device.h"

ReadWriteOptionsDialog::ReadWriteOptionsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_ReadWriteOptionsDialog>())
{
    this->parent = parent;
    ui->setupUi(this);

    QObject::connect(ui->buttonBox, &QDialogButtonBox::accepted,
                    this, &ReadWriteOptionsDialog::setOptionsAndClose);

    ui->digitalContactListChbx->setChecked((UserSettings::read_write_options & DeviceRWType::DIGITAL_CONTACTS) != DeviceRWType::NONE);
    ui->otherDataChbx->setChecked((UserSettings::read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE);
}

ReadWriteOptionsDialog::~ReadWriteOptionsDialog(){}

void ReadWriteOptionsDialog::setOptionsAndClose(){
    DeviceRWType options = DeviceRWType::NONE;
    if(ui->digitalContactListChbx->isChecked()) options |= DeviceRWType::DIGITAL_CONTACTS;
    if(ui->otherDataChbx->isChecked()) options |= DeviceRWType::RADIO_DATA;

    UserSettings::read_write_options = options;
    UserSettings::save();
    if(!is_write){
        this->parent->readFromRadio();
    }else{
        this->parent->writeToRadio();
    }
}