
#include "auto_repeater_edit_dialog.h"
#include "ui_auto_repeater_edit_dialog.h"
#include "main_window.h"


AutoRepeaterEditDialog::AutoRepeaterEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_AutoRepeaterOffsetFrequencyEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    main_window = parent;
    this->index = index;
    
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AutoRepeaterEditDialog::save);
    connect(ui->frequencyTxt, &QLineEdit::editingFinished, this, &AutoRepeaterEditDialog::formatFrequency);
    connect(this->ui->prevBtn, &QPushButton::clicked, this, &AutoRepeaterEditDialog::prevBtnClicked);
    connect(this->ui->nextBtn, &QPushButton::clicked, this, &AutoRepeaterEditDialog::nextBtnClicked);

    loadData();
    
}
AutoRepeaterEditDialog::~AutoRepeaterEditDialog(){}

void AutoRepeaterEditDialog::loadData(){
    setWindowTitle("Auto Repeater Offset Frequency---" + QString::number(index+1));
    arf = Anytone::Memory::ar_offset_frequencies.at(index);
    ui->frequencyTxt->setText(arf->getFrequencyString());
}
void AutoRepeaterEditDialog::formatFrequency(){
    double freq = ui->frequencyTxt->text().toDouble();
    ui->frequencyTxt->setText(QString::number(freq, 'f', 3));
}

void AutoRepeaterEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::ar_offset_frequencies.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::ar_offset_frequencies.size() - 1);
}
void AutoRepeaterEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void AutoRepeaterEditDialog::save(){
    arf->frequency = int(ui->frequencyTxt->text().toDouble() * 100000);
}
