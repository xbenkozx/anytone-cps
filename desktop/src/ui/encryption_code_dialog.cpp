
#include "encryption_code_dialog.h"
#include "ui_encryption_code_dialog.h"
#include "main_window.h"

EncryptionCodeDialog::EncryptionCodeDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_EncryptionCodeEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    this->index = index;

    connect(ui->prevBtn, &QPushButton::clicked, this, &EncryptionCodeDialog::prevBtnClicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &EncryptionCodeDialog::nextBtnClicked);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &EncryptionCodeDialog::saveClose);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &EncryptionCodeDialog::close);

    connect(ui->idTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->idTxt->setText(text.toUpper().rightJustified(4, '0')); });
    ui->keyTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD]+$"),  ui->idTxt));

    connect(ui->keyTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->keyTxt->setText(text.toUpper().rightJustified(4, '0')); });
    ui->keyTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD]+$"),  ui->keyTxt));


    loadData();
}
EncryptionCodeDialog::~EncryptionCodeDialog(){}

void EncryptionCodeDialog::loadData(){
    setWindowTitle("Encryption Code Edit---" + QString::number(index+1));
    key = Anytone::Memory::encryption_keys.at(index);
    if(!key) return;
    ui->idTxt->setText(key->id);
    ui->keyTxt->setText(key->key);
}

void EncryptionCodeDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

void EncryptionCodeDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::encryption_keys.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::encryption_keys.size() - 1);
}

void EncryptionCodeDialog::saveClose(){
    save();
    close();
}
void EncryptionCodeDialog::save(){
    key->id = ui->idTxt->text();
    key->key = ui->keyTxt->text();
}
