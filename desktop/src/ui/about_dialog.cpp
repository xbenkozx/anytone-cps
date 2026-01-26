
#include "about_dialog.h"
#include "ui_about_dialog.h"
#include "constants.h"


AboutDialog::AboutDialog(QWidget *parent):
    QDialog(parent),
    ui(std::make_unique<Ui_AboutDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    ui->iconLabel->setStyleSheet("background-image: url(:/icons/d878_icon.png);background-repeat: no-repeat;");

    ui->aboutLabel->setMarkdown(
        "# Anytone CPS\n"
        "Version: **" + Constants::CPS_VERISON + "** Build **" + Constants::CPS_BUILD_NUMBER + "**\n\r"
        "Supported Models:\n"
        "- D878UVII (FW4.00)\n"
        "- D890UV (FW1.03)"
    );
    
    
}
AboutDialog::~AboutDialog(){
    
}
