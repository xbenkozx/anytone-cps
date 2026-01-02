
#include "aes_encryption_code_dialog.h"
#include "ui_aes_encryption_code_dialog.h"
#include "main_window.h"

AesEncryptionCodeDialog::AesEncryptionCodeDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_AesEncryptionCodeEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    this->index = index;

    connect(this->ui->prevBtn, &QPushButton::clicked, this, &AesEncryptionCodeDialog::prevBtnClicked);
    connect(this->ui->nextBtn, &QPushButton::clicked, this, &AesEncryptionCodeDialog::nextBtnClicked);
    ui->idCmbx->addItem("Off");
    for(int i = 0; i < 255; i++){ ui->idCmbx->addItem(QString::number(i+1)); }

    loadData();    
}
AesEncryptionCodeDialog::~AesEncryptionCodeDialog(){}

void AesEncryptionCodeDialog::loadData(){
    setWindowTitle("AES Encryption Code Edit---" + QString::number(index+1));
    key = Anytone::Memory::aes_encryption_keys.at(index);
    if(!key) return;
    ui->idCmbx->setCurrentIndex(key->id);
    ui->keyTxt->setText(key->key);
}

void AesEncryptionCodeDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

void AesEncryptionCodeDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::aes_encryption_keys.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::aes_encryption_keys.size() - 1);
}

void AesEncryptionCodeDialog::save(){
    key->key = ui->keyTxt->text();
    key->key_length = key->key.size();
    key->id = ui->idCmbx->currentIndex();
    main_window->listAesEncryptionKeys(false);
}
