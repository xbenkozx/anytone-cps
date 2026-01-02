#include <QThreadPool>
#include "local_information_dialog.h"
#include "ui_local_information_dialog.h"
#include "main_window.h"
#include "user_settings.h"


LocalInformationDialog::LocalInformationDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_LocalInformationDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    readRadio();
}
LocalInformationDialog::~LocalInformationDialog(){}
void LocalInformationDialog::readRadio(){
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

    ui->radioTypeTxt->setText(eo.radio_type);
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
}
