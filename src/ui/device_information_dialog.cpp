
#include "device_information_dialog.h"
#include "ui_device_information_dialog.h"
#include "main_window.h"


DeviceInformationDialog::DeviceInformationDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_DeviceInformationDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->main_window = parent;

    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII:
            ui->modelTxt->setText("D878UVII");
            break;
        case Anytone::RadioModel::D890UV:
            ui->modelTxt->setText("D890");
            break;
    }
    
    ui->bandTxt->setHtml("<div style=\"text-align:center;\">" + Anytone::Memory::radio_band.replace("\n", "<br/>") + "</div>");
    ui->versionTxt->setText(Anytone::Memory::radio_version);
}
DeviceInformationDialog::~DeviceInformationDialog(){
    
}
