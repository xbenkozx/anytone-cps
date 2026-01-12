
#include "roaming_channel_edit_dialog.h"
#include "ui_roaming_channel_edit_dialog.h"
#include "main_window.h"
#include "memory/at_memory.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>


RoamingChannelEditDialog::RoamingChannelEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_RoamingChannelEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->index = index;
    this->main_window = parent;

    connect(this->ui->previousBtn, &QPushButton::clicked, this, &RoamingChannelEditDialog::prevBtnClicked);
    connect(this->ui->nextBtn, &QPushButton::clicked, this, &RoamingChannelEditDialog::nextBtnClicked);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &RoamingChannelEditDialog::save);
    connect(ui->rxFrequencyTxt, &QLineEdit::editingFinished, this, &RoamingChannelEditDialog::formatRxFrequency);
    connect(ui->txFrequencyTxt, &QLineEdit::editingFinished, this, &RoamingChannelEditDialog::formatTxFrequency);
    connect(ui->fastSelectCmbx, &QComboBox::currentIndexChanged, this, &RoamingChannelEditDialog::fastSelect);

    ui->rxFrequencyTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression(R"(\d+(\.\d+)?)"),
            ui->rxFrequencyTxt
        )
    );

    ui->txFrequencyTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression(R"(\d+(\.\d+)?)"),
            ui->txFrequencyTxt
        )
    );

    if(index == 0) ui->previousBtn->setDisabled(true);
    if(index == Anytone::Memory::roaming_channels.size() - 1) ui->nextBtn->setDisabled(true);

    setupUI();
    loadData();
    
}
RoamingChannelEditDialog::~RoamingChannelEditDialog(){}

void RoamingChannelEditDialog::setupUI(){
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency > 0) ui->fastSelectCmbx->addItem(ch->name, QVariant::fromValue(ch));
    }

    for (int i = 0; i < 16; ++i) {
        ui->colorCodeCmbx->addItem(QString::number(i));
    }
    ui->colorCodeCmbx->addItem("No Use");
    ui->slotCmbx->addItems(QStringList{"Slot1", "Slot2", "No Use"});
}
void RoamingChannelEditDialog::loadData(){
    setWindowTitle("Roaming Channel Edit---" + QString::number(index+1));
    channel = Anytone::Memory::roaming_channels.at(index);

    ui->rxFrequencyTxt->setText(channel->getRxFrequencyString());
    ui->txFrequencyTxt->setText(channel->getTxFrequencyString());
    if(channel->name.size() == 0){
        ui->nameTxt->setText("Roam Channel " + QString::number(index+1));
    }else{
        ui->nameTxt->setText(channel->name);
        ui->colorCodeCmbx->setCurrentIndex(channel->color_code);
        ui->slotCmbx->setCurrentIndex(channel->slot);
    }
}
void RoamingChannelEditDialog::fastSelect(){
    auto *ch = ui->fastSelectCmbx->currentData().value<Anytone::Channel*>();
    if(!ch) return;
    ui->rxFrequencyTxt->setText(ch->getRxFrequencyString());
    ui->txFrequencyTxt->setText(ch->getTxFrequencyString());
    ui->slotCmbx->setCurrentIndex(ch->time_slot);
    ui->colorCodeCmbx->setCurrentIndex(ch->rx_color_code_idx);
}
void RoamingChannelEditDialog::formatRxFrequency(){
    double freq = ui->rxFrequencyTxt->text().toDouble();
    if(freq > 480 || freq < 88) return;
    freq = Format::roundFrequency(freq);
    ui->rxFrequencyTxt->setText(QString::number(freq, 'f', 5));
}
void RoamingChannelEditDialog::formatTxFrequency(){
    double freq = ui->txFrequencyTxt->text().toDouble();
    if(freq > 480 || freq < 88) return;
    freq = Format::roundFrequency(freq);
    ui->txFrequencyTxt->setText(QString::number(freq, 'f', 5));
}

void RoamingChannelEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::channels.size() - 2){
        index++;
        loadData();
    }

    ui->previousBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::channels.size() - 1);
}
void RoamingChannelEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->previousBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void RoamingChannelEditDialog::save(){
    channel->rx_frequency = int(ui->rxFrequencyTxt->text().toDouble() * 100000);
    channel->tx_frequency = int(ui->txFrequencyTxt->text().toDouble() * 100000);
    channel->name = ui->nameTxt->text();
    channel->color_code = ui->colorCodeCmbx->currentIndex();
    channel->slot = ui->slotCmbx->currentIndex();
}
