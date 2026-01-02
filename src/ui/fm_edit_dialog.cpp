
#include "fm_edit_dialog.h"
#include "ui_fm_edit_dialog.h"
#include "main_window.h"


FmEditDialog::FmEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_FmEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    
    this->index = index;
    main_window = parent;

    ui->scanAddCmbx->addItems(QStringList{"Del", "Add"});
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &FmEditDialog::save);
    connect(this->ui->previousBtn, &QPushButton::clicked, this, &FmEditDialog::prevBtnClicked);
    connect(this->ui->nextBtn, &QPushButton::clicked, this, &FmEditDialog::nextBtnClicked);
    connect(this->ui->frequencyTxt, &QLineEdit::editingFinished, this, &FmEditDialog::updateFrequencyText);

    if(index == 0) ui->previousBtn->setDisabled(true);
    
    loadData();
    
}
FmEditDialog::~FmEditDialog(){}

void FmEditDialog::loadData(){
    setWindowTitle("FM Edit---" + QString::number(index+1));
    fm = Anytone::Memory::fm_channels.at(index);

    if(fm->frequency == 0) {
        ui->frequencyTxt->setText("88.00");
    }else{
        ui->frequencyTxt->setText(fm->getFrequencyString());
    }

    ui->scanAddCmbx->setCurrentIndex(fm->scan_add);
}

void FmEditDialog::save(){
    fm->setFrequencyString(ui->frequencyTxt->text());
    fm->scan_add = ui->scanAddCmbx->currentIndex();
    main_window->listFmChannels(false);
}
void FmEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::fm_channels.size() - 2){
        index++;
        loadData();
    }

    ui->previousBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::fm_channels.size() - 1);
}
void FmEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->previousBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void FmEditDialog::updateFrequencyText(){
    double freq = ui->frequencyTxt->text().toDouble();
    if(freq != 0){
        if(freq < 76) freq = 76;
        if(freq > 108) freq = 108;
        ui->frequencyTxt->setText(QString::number(freq, 'f', 2));
    }
}