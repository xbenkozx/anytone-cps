
#include "talkgroup_whitelist_edit_dialog.h"
#include "ui_talkgroup_whitelist_edit_dialog.h"
#include "main_window.h"
#include "memory/anytone_memory.h"
#include "constants.h"

TalkgroupWhitelistEditDialog::TalkgroupWhitelistEditDialog(QWidget *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_TalkgroupWhitelistEditDialog>()),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TalkgroupWhitelistEditDialog::save);;
    connect(ui->callTypeCmbx, &QComboBox::currentIndexChanged, this, &TalkgroupWhitelistEditDialog::callTypeChanged);
    connect(ui->tgIdTxt, &QLineEdit::editingFinished, this, &TalkgroupWhitelistEditDialog::dmrIdEditingFinished);

    setupUI();
    loadData();
    
}
TalkgroupWhitelistEditDialog::~TalkgroupWhitelistEditDialog(){}
void TalkgroupWhitelistEditDialog::setupUI(){
    ui->callTypeCmbx->addItems(Constants::CALL_TYPE);
    ui->tgIdTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[0-9]*"),
            ui->tgIdTxt
        )
    );
}
void TalkgroupWhitelistEditDialog::loadData(){
    setWindowTitle("Talkgroup Whitelist Edit---" + QString::number(index+1));
    tg = Anytone::Memory::talkgroup_whitelist.at(index);
    ui->callTypeCmbx->setCurrentIndex(tg->call_type);
    ui->tgIdTxt->setText(QString::number(tg->dmr_id));
}

void TalkgroupWhitelistEditDialog::save(){
    tg->dmr_id = ui->tgIdTxt->text().toInt();
    if(tg->dmr_id == 16777215) ui->callTypeCmbx->setCurrentIndex(2);
    tg->call_type = ui->callTypeCmbx->currentIndex();
}
void TalkgroupWhitelistEditDialog::callTypeChanged(){
    if(ui->callTypeCmbx->currentIndex() == 2){
        ui->tgIdTxt->setEnabled(false);
        ui->tgIdTxt->setText("16777215");
    }else{
        ui->tgIdTxt->setEnabled(true);
        ui->tgIdTxt->clear();
    }
}
void TalkgroupWhitelistEditDialog::dmrIdEditingFinished(){
    if(ui->tgIdTxt->text().toInt() > 16777215){
        ui->tgIdTxt->setText("16777215");
    }
}