
#include "basic_dialog.h"
#include "ui_basic_dialog.h"


BasicDialog::BasicDialog(QWidget *parent, QString text, QString title) :
    QDialog(parent),
    ui(std::make_unique<Ui_BasicDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    setWindowTitle(title);
    ui->label->setText(text);
    
}
BasicDialog::~BasicDialog(){
    
}
