
#include "prefabricated_sms_edit_dialog.h"
#include "ui_prefabricated_sms_edit_dialog.h"
#include "main_window.h"


PrefabricatedSmsEditDialog::PrefabricatedSmsEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_PrefabricatedSmsEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->index = index;
    main_window = parent;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &PrefabricatedSmsEditDialog::save);
    connect(ui->nextBtn, &QPushButton::clicked, this, &PrefabricatedSmsEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &PrefabricatedSmsEditDialog::prevBtnClicked);

    loadData();
    
}
PrefabricatedSmsEditDialog::~PrefabricatedSmsEditDialog(){}
void PrefabricatedSmsEditDialog::loadData(){
    setWindowTitle("Prefabricated SMS Edit---" + QString::number(index+1));
    sms = Anytone::Memory::prefabricated_sms_list.at(index);
    ui->plainTextEdit->setPlainText(sms->text);
}
void PrefabricatedSmsEditDialog::save(){
    sms->text = ui->plainTextEdit->toPlainText();
}
void PrefabricatedSmsEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::prefabricated_sms_list.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::prefabricated_sms_list.size() - 1);
}
void PrefabricatedSmsEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

