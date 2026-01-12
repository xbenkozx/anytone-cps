
#include "analog_address_edit_dialog.h"
#include "ui_analog_address_edit_dialog.h"
#include "main_window.h"

AnalogAddressEditDialog::AnalogAddressEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_AnalogAddressEditDialog>()),
    main_window(parent),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    ui->numberTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]+$"),  ui->numberTxt));
    connect(ui->prevBtn, &QPushButton::clicked, this, &AnalogAddressEditDialog::prevBtnClicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &AnalogAddressEditDialog::nextBtnClicked);
    
}
AnalogAddressEditDialog::~AnalogAddressEditDialog(){}

void AnalogAddressEditDialog::loadData(){
    setWindowTitle("Analog Address Edit---" + QString::number(index+1));
    address = Anytone::Memory::analog_addresses.at(index);
    if(!address) return;
    
}

void AnalogAddressEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

void AnalogAddressEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::analog_addresses.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::analog_addresses.size() - 1);
}

void AnalogAddressEditDialog::save(){
    address->number = ui->numberTxt->text().toInt();
    address->name = ui->nameTxt->text();
}
