
#include "digital_contact_whitelist_edit_dialog.h"
#include "ui_talkgroup_whitelist_edit_dialog.h"
#include "memory/anytone_memory.h"
#include "constants.h"

DigitalContactWhitelistEditDialog::DigitalContactWhitelistEditDialog(QWidget *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_TalkgroupWhitelistEditDialog>()),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DigitalContactWhitelistEditDialog::save);
    connect(ui->callTypeCmbx, &QComboBox::currentIndexChanged, this, &DigitalContactWhitelistEditDialog::callTypeChanged);
    connect(ui->tgIdTxt, &QLineEdit::editingFinished, this, &DigitalContactWhitelistEditDialog::dmrIdEditingFinished);

    setupUI();
    loadData();
    
}
DigitalContactWhitelistEditDialog::~DigitalContactWhitelistEditDialog(){}
void DigitalContactWhitelistEditDialog::setupUI(){
    ui->callTypeCmbx->addItems(Constants::CALL_TYPE);
    ui->tgIdTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[0-9]*"),
            ui->tgIdTxt
        )
    );
}
void DigitalContactWhitelistEditDialog::loadData(){
    setWindowTitle("Digital Contact Whitelist Edit---" + QString::number(index+1));
    tg = Anytone::Memory::digital_contact_whitelist.at(index);
    ui->callTypeCmbx->setCurrentIndex(tg->call_type);
    ui->tgIdTxt->setText(QString::number(tg->dmr_id));
}

void DigitalContactWhitelistEditDialog::save(){
    tg->dmr_id = ui->tgIdTxt->text().toInt();
    if(tg->dmr_id == 16777215) ui->callTypeCmbx->setCurrentIndex(2);
    tg->call_type = ui->callTypeCmbx->currentIndex();
}
void DigitalContactWhitelistEditDialog::callTypeChanged(){
    if(ui->callTypeCmbx->currentIndex() == 2){
        ui->tgIdTxt->setEnabled(false);
        ui->tgIdTxt->setText("16777215");
    }else{
        ui->tgIdTxt->setEnabled(true);
        ui->tgIdTxt->clear();
    }
}
void DigitalContactWhitelistEditDialog::dmrIdEditingFinished(){
    if(ui->tgIdTxt->text().toInt() > 16777215){
        ui->tgIdTxt->setText("16777215");
    }
}