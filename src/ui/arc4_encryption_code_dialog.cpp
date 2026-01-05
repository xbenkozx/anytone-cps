
#include "arc4_encryption_code_dialog.h"
#include "ui_arc4_encryption_code_dialog.h"
#include "main_window.h"

Arc4EncryptionCodeDialog::Arc4EncryptionCodeDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_Arc4EncryptionCodeEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    this->index = index;

    connect(ui->prevBtn, &QPushButton::clicked, this, &Arc4EncryptionCodeDialog::prevBtnClicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &Arc4EncryptionCodeDialog::nextBtnClicked);
    ui->idCmbx->addItem("Off");
    for(int i = 0; i < 255; i++){ ui->idCmbx->addItem(QString::number(i+1)); }

    connect(ui->keyTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->keyTxt->setText(text.toUpper().rightJustified(10, '0')); });
    ui->keyTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD]+$"),  ui->keyTxt));

    loadData();    
}
Arc4EncryptionCodeDialog::~Arc4EncryptionCodeDialog(){}

void Arc4EncryptionCodeDialog::loadData(){
    setWindowTitle("ARC4 Encryption Code Edit---" + QString::number(index+1));
    key = Anytone::Memory::arc4_encryption_keys.at(index);
    if(!key) return;
    ui->idCmbx->setCurrentIndex(key->id);
    ui->keyTxt->setText(key->key);
}

void Arc4EncryptionCodeDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

void Arc4EncryptionCodeDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::arc4_encryption_keys.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::arc4_encryption_keys.size() - 1);
}

void Arc4EncryptionCodeDialog::save(){
    key->key = ui->keyTxt->text();
    key->id = ui->idCmbx->currentIndex();
    main_window->listArc4EncryptionKeys(false);
}
