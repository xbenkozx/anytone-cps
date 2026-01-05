#include <QThreadPool>
#include "expert_options_dialog.h"
#include "ui_expert_options_dialog.h"
#include "main_window.h"
#include "user_settings.h"
#include "constants.h"


ExpertOptionsDialog::ExpertOptionsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_ExpertOptionsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    ui->writeBtn->setDisabled(true);

    eo.decode(QByteArray(0x100, 0));

    connect(ui->closeBtn, &QPushButton::clicked, this, &ExpertOptionsDialog::close);
    connect(ui->readBtn, &QPushButton::clicked, this, &ExpertOptionsDialog::readOptions);
    connect(ui->writeBtn, &QPushButton::clicked, this, &ExpertOptionsDialog::writeOptions);

    ui->frequencyCmbx->addItems(Constants::AT_OPTIONS);
}
ExpertOptionsDialog::~ExpertOptionsDialog(){}
void ExpertOptionsDialog::readOptions(){
    if(UserSettings::comport == QString("VIRTUAL")){
        VirtualDevice device;
        if(device.connect(UserSettings::virtual_file_name)){
            eo.decode(device.readLocalInformation());
        }
    }else{
        SerialDevice device;
        if(device.connect(UserSettings::comport)){
            eo.decode(device.readLocalInformation());
            device.endProgMode();
        }
        device.port->close();
    }

    ui->bandSelectChbx->setChecked(eo.band_select);
    ui->fullTestModeChbx->setChecked(eo.full_test_mode);
    ui->chineseChbx->setChecked(eo.chinese);
    ui->radioTypeTxt->setText(eo.radio_type);
    ui->bandSettingPasswordTxt->setText(eo.band_settings_password);
    ui->frequencyCmbx->setCurrentIndex(eo.frequency_mode);
    ui->programPasswordTxt->setText(eo.program_password);
    ui->areaCodeTxt->setText(eo.area_code);
    ui->serialNumberTxt->setText(eo.serial_number);
    ui->productionDateTxt->setText(eo.production_date);
    ui->manufactureCodeTxt->setText(eo.manufacture_code);
    ui->maintenanceDateTxt->setText(eo.maintenance_date);
    ui->maintenanceDescriptionTxt->setPlainText(eo.maintenance_description);
    ui->dealerCodeTxt->setText(eo.dealer_code);
    ui->stockDateTxt->setText(eo.stock_date);
    ui->sellDateTxt->setText(eo.sell_date);
    ui->sellerTxt->setText(eo.seller);
    ui->writeBtn->setDisabled(false);
}

void ExpertOptionsDialog::writeOptions(){

    eo.band_select = ui->bandSelectChbx->isChecked();
    eo.full_test_mode = ui->fullTestModeChbx->isChecked();
    eo.chinese = ui->chineseChbx->isChecked();
    eo.radio_type = ui->radioTypeTxt->text();
    eo.band_settings_password = ui->bandSettingPasswordTxt->text();
    eo.frequency_mode = ui->frequencyCmbx->currentIndex();
    eo.program_password = ui->programPasswordTxt->text();
    eo.area_code = ui->areaCodeTxt->text();
    eo.serial_number = ui->serialNumberTxt->text();
    eo.production_date = ui->productionDateTxt->text();
    eo.manufacture_code = ui->manufactureCodeTxt->text();
    eo.maintenance_date = ui->maintenanceDateTxt->text();
    eo.maintenance_description = ui->maintenanceDescriptionTxt->toPlainText();
    eo.dealer_code = ui->dealerCodeTxt->text();
    eo.stock_date = ui->stockDateTxt->text();
    eo.sell_date = ui->sellDateTxt->text();
    eo.seller = ui->sellerTxt->text();
    ui->writeBtn->setDisabled(false);

    QByteArray data = eo.encode();
    
    if(UserSettings::comport == QString("VIRTUAL")){
        VirtualDevice device;
        if(device.connect(UserSettings::virtual_file_name)){
            
        }
    }else{
        SerialDevice device;
        if(device.connect(UserSettings::comport)){
            device.writeLocalInformation(data);
            device.endProgMode();
        }
        device.port->close();
    }
    
}
