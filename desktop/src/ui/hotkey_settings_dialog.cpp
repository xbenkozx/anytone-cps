
#include "hotkey_settings_dialog.h"
#include "ui_hotkey_settings_dialog.h"
#include "main_window.h"
#include "memory/anytone_memory.h"


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
    ui->hotKeyTableView->setColumnWidth(2, 70);
    ui->hotKeyTableView->setColumnWidth(4, 150);
    ui->hotKeyTableView->setColumnWidth(6, 250);
    auto* hk_table_delegate = new HotKeyHotKeyDelegate(ui->hotKeyTableView);
    ui->hotKeyTableView->setItemDelegateForColumn(1, hk_table_delegate);
    ui->hotKeyTableView->setItemDelegateForColumn(2, hk_table_delegate);
    ui->hotKeyTableView->setItemDelegateForColumn(3, hk_table_delegate);
    ui->hotKeyTableView->setItemDelegateForColumn(4, hk_table_delegate);
    ui->hotKeyTableView->setItemDelegateForColumn(5, hk_table_delegate);
    ui->hotKeyTableView->setItemDelegateForColumn(6, hk_table_delegate);

    quick_call_table_model = new HotKeyQuickCallTableModel(this);
    ui->analogQuickCallTableView->setModel(quick_call_table_model);
    ui->analogQuickCallTableView->verticalHeader()->setVisible(false);
    ui->analogQuickCallTableView->setSortingEnabled(false);
    ui->analogQuickCallTableView->setColumnWidth(0, 70);
    auto* hk_quick_call_delegate = new HotKeyQuickCallDelegate(ui->analogQuickCallTableView);
    ui->analogQuickCallTableView->setItemDelegateForColumn(1, hk_quick_call_delegate);
    ui->analogQuickCallTableView->setItemDelegateForColumn(2, hk_quick_call_delegate);

    state_info_table_model = new HotkeyStateInfoTableModel(this);
    ui->stateInformationTableView->setModel(state_info_table_model);
    ui->stateInformationTableView->verticalHeader()->setVisible(false);
    ui->stateInformationTableView->setSortingEnabled(false);
    ui->stateInformationTableView->setColumnWidth(0, 70);
    ui->stateInformationTableView->setColumnWidth(1, 300);
    auto* hk_state_info_delegate = new HotKeyStateInfoDelegate(ui->stateInformationTableView);
    ui->stateInformationTableView->setItemDelegateForColumn(1, hk_state_info_delegate);
}
void HotKeySettingsDialog::loadData(){

}
void HotKeySettingsDialog::save(){
    
}