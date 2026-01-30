
#include "talkgroup_edit_dialog.h"
#include "ui_talkgroup_edit_dialog.h"
#include "main_window.h"
#include "memory/anytone_memory.h"
#include "constants.h"

TalkgroupEditDialog::TalkgroupEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_TalkgroupEditDialog>()), 
    main_window(parent),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &TalkgroupEditDialog::save);
    connect(ui->prevBtn, &QPushButton::clicked, this, &TalkgroupEditDialog::prevBtnClicked);
    connect(ui->nextBtn, &QPushButton::clicked, this, &TalkgroupEditDialog::nextBtnClicked);
    connect(ui->callTypeCmbx, &QComboBox::currentIndexChanged, this, &TalkgroupEditDialog::callTypeChanged);
    connect(ui->tgIdTxt, &QLineEdit::editingFinished, this, &TalkgroupEditDialog::dmrIdEditingFinished);

    setupUI();
    loadData();
    
}
TalkgroupEditDialog::~TalkgroupEditDialog(){}
void TalkgroupEditDialog::setupUI(){
    ui->callTypeCmbx->addItems(Constants::CALL_TYPE);
    ui->callAlertCmbx->addItems(Constants::CALL_ALERT);
    ui->tgIdTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression("[0-9]*"),
            ui->tgIdTxt
        )
    );
}
void TalkgroupEditDialog::loadData(){
    setWindowTitle("Contact/Talkgroup Edit---" + QString::number(index+1));
    tg = Anytone::Memory::talkgroups.at(index);
    ui->nameTxt->setText(tg->name);
    ui->callTypeCmbx->setCurrentIndex(tg->call_type);
    ui->tgIdTxt->setText(QString::number(tg->dmr_id));
    ui->callAlertCmbx->setCurrentIndex(tg->call_alert);
}
void TalkgroupEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::channels.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::channels.size() - 1);
}
void TalkgroupEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void TalkgroupEditDialog::save(){
    tg->dmr_id = ui->tgIdTxt->text().toInt();
    if(tg->dmr_id == 16777215) ui->callTypeCmbx->setCurrentIndex(2);
    tg->name = ui->nameTxt->text();
    tg->call_type = ui->callTypeCmbx->currentIndex();
    tg->call_alert = ui->callAlertCmbx->currentIndex();
}
void TalkgroupEditDialog::callTypeChanged(){
    if(ui->callTypeCmbx->currentIndex() == 2){
        ui->tgIdTxt->setEnabled(false);
        ui->callAlertCmbx->setEnabled(false);
        ui->tgIdTxt->setText("16777215");
    }else{
        ui->tgIdTxt->setEnabled(true);
        ui->callAlertCmbx->setEnabled(true);
        ui->tgIdTxt->clear();
    }
}
void TalkgroupEditDialog::dmrIdEditingFinished(){
    if(ui->tgIdTxt->text().toInt() > 16777215){
        ui->tgIdTxt->setText("16777215");
    }
}