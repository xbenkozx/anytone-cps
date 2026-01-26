
#include "radio_id_edit_dialog.h"
#include "ui_radio_id_edit_dialog.h"
#include "main_window.h"
#include "memory/anytone_memory.h"

RadioIdEditDialog::RadioIdEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_RadioIdEditDialog>()), 
    main_window(parent),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &RadioIdEditDialog::save);
    connect(ui->prevBtn, &QPushButton::clicked, this, &RadioIdEditDialog::prevBtnClicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &RadioIdEditDialog::nextBtnClicked);

    ui->radioIdTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[0-9]*"),
            ui->radioIdTxt
        )
    );
    
    loadData();
    
}
RadioIdEditDialog::~RadioIdEditDialog(){}
void RadioIdEditDialog::loadData(){
    setWindowTitle("Radio ID Edit---" + QString::number(index+1));
    rid = Anytone::Memory::radioids.at(index);

    ui->radioIdNameTxt->setText(rid->name);
    ui->radioIdTxt->setText(QString::number(rid->dmr_id));

}
void RadioIdEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::channels.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::channels.size() - 1);
}
void RadioIdEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void RadioIdEditDialog::save(){
    rid->name = ui->radioIdNameTxt->text();
    rid->dmr_id = ui->radioIdTxt->text().toInt();
}
