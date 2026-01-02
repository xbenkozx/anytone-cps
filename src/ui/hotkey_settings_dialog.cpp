
#include "hotkey_settings_dialog.h"
#include "ui_hotkey_settings_dialog.h"
#include "main_window.h"
#include "memory/memory.h"


HotKeySettingsDialog::HotKeySettingsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_HotKeySettingsDialog>()), 
    main_window(parent)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    setupUI();
    loadData();
    
}
HotKeySettingsDialog::~HotKeySettingsDialog(){}
void HotKeySettingsDialog::setupUI(){

}
void HotKeySettingsDialog::loadData(){

}
void HotKeySettingsDialog::save(){
    
}