
#include "am_air_edit_dialog.h"
#include "ui_am_air_edit_dialog.h"
#include "anytone_memory.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>


AmAirEditDialog::AmAirEditDialog(QWidget *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_AmAirEditDialog>()),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->nextBtn, &QPushButton::clicked, this, &AmAirEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &AmAirEditDialog::prevBtnClicked);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AmAirEditDialog::save);

    ui->frequencyTxt->setValidator(
        new QRegularExpressionValidator(
            QRegularExpression(R"(\d+(\.\d+)?)"),
            ui->frequencyTxt
        )
    );

    loadData();
    
}
AmAirEditDialog::~AmAirEditDialog(){}

void AmAirEditDialog::loadData(){
    setWindowTitle("AM Air Edit---" + QString::number(index+1));
    channel = Anytone::Memory::am_air_list.at(index);

    if(channel->frequency == 0) channel->name = "AM CH " + QString::number(index+1).rightJustified(3, '0');

    ui->frequencyTxt->setText(channel->getFrequencyString());
    ui->nameTxt->setText(channel->name);
}

void AmAirEditDialog::save(){
    channel->name = ui->nameTxt->text();
    channel->setFrequencyString(ui->frequencyTxt->text());
}

void AmAirEditDialog::updateFrequency(){
    QString formatted_freq = formatFrequency(ui->frequencyTxt->text());
    ui->frequencyTxt->setText(formatted_freq);
}
QString AmAirEditDialog::formatFrequency(QString frequency){
    double freq = frequency.toDouble();
    if(freq == 0) return "0";
    if(freq > 145) freq = 145;
    if(freq < 108) freq = 108;
    freq = Format::roundFrequency(freq);
    return QString::number(freq, 'f', 5);
}
void AmAirEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::am_air_list.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::am_air_list.size() - 1);
}
void AmAirEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

