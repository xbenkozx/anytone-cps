
#include "retry_connection_dialog.h"
#include "ui_retry_connection_dialog.h"
#include "main_window.h"


RetryConnectionDialog::RetryConnectionDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_RetryConnectionDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    main_window = parent;

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &RetryConnectionDialog::retry);
    
}
RetryConnectionDialog::~RetryConnectionDialog(){}
void RetryConnectionDialog::retry(){
    if(is_write){
        main_window->readFromRadio();
    }else{
        main_window->writeToRadio();
    }
}
