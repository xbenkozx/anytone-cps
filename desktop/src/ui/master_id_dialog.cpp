
#include "master_id_dialog.h"
#include "ui_master_id_dialog.h"
#include "main_window.h"
#include "memory/at_memory.h"


MasterIdDialog::MasterIdDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_MasterIdDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->main_window = parent;

    loadData();
    
}
MasterIdDialog::~MasterIdDialog(){
    
}

void MasterIdDialog::loadData(){
    ui->masterIdTxt->setText(QString::number(Anytone::Memory::master_radio_id->dmr_id));
    ui->masterIdNameTxt->setText(Anytone::Memory::master_radio_id->name);
    ui->usedChbx->setChecked(Anytone::Memory::master_radio_id->used);
}

void MasterIdDialog::save(){
    Anytone::Memory::master_radio_id->dmr_id = ui->masterIdTxt->text().toInt();
    Anytone::Memory::master_radio_id->name = ui->masterIdNameTxt->text();
    Anytone::Memory::master_radio_id->used = ui->usedChbx->isChecked();
}
