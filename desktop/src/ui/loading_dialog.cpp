#include "loading_dialog.h"
#include "ui_loading_dialog.h"
#include <QCloseEvent>

LoadingDialog::LoadingDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_LoadingDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    
}
LoadingDialog::~LoadingDialog(){
    
}
void LoadingDialog::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);
    m_isBusy = true;
    
    ui->label->setText("Connecting");
    ui->progressBar->setMaximum(0);
    ui->progressBar->setValue(0);
    
    ui->label_2->setText("");
    ui->progressBar_2->setMaximum(1);
    ui->progressBar_2->setValue(0);

    mainbar_max = 0;
    subbar_max = 0;
    mainbar_text = "";
    subbar_text = "";
}
void LoadingDialog::closeEvent(QCloseEvent *event)
{
    if (m_isBusy) {
        event->ignore();
    } else {
        event->accept();
    }
}
void LoadingDialog::finished(const int &result){
    m_isBusy = false;
}
void LoadingDialog::updateMainbar(const int &val, const int &max, const QString &text){
    if(mainbar_max != max){
        ui->progressBar->setMaximum(max);
        mainbar_max = max;
    }
    if(text != mainbar_text){
        ui->label->setText(text);
        mainbar_text = text;
    }
    ui->progressBar->setValue(val);
}
void LoadingDialog::updateSubbar(const int &val, const int &max, const QString &text){
    if(subbar_max != max){
        ui->progressBar_2->setMaximum(max);
        subbar_max = max;
    }
    if(text != subbar_text){
        ui->label_2->setText(text);
        subbar_text = text;
    }
    ui->progressBar_2->setValue(val);
}
