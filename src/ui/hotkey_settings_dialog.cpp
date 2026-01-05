
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
    key_table_model = new HotkeyKeyTableModel(this);
    ui->hotKeyTableView->setModel(key_table_model);
    ui->hotKeyTableView->verticalHeader()->setVisible(false);
    ui->hotKeyTableView->setSortingEnabled(false);
    ui->hotKeyTableView->setColumnWidth(6, 300);

    quick_call_table_model = new HotKeyQuickCallTableModel(this);
    ui->analogQuickCallTableView->setModel(quick_call_table_model);
    ui->analogQuickCallTableView->verticalHeader()->setVisible(false);
    ui->analogQuickCallTableView->setSortingEnabled(false);
    ui->analogQuickCallTableView->setColumnWidth(0, 70);

    state_info_table_model = new HotkeyStateInfoTableModel(this);
    ui->stateInformationTableView->setModel(state_info_table_model);
    ui->stateInformationTableView->verticalHeader()->setVisible(false);
    ui->stateInformationTableView->setSortingEnabled(false);
    ui->stateInformationTableView->setColumnWidth(0, 70);
    ui->stateInformationTableView->setColumnWidth(1, 300);
}
void HotKeySettingsDialog::loadData(){

}
void HotKeySettingsDialog::save(){
    
}