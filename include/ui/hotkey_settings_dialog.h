#ifndef HOTKEY_SETTIINGS_DIALOG_H
#define HOTKEY_SETTIINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include "hotkey_key_table_model.h"
#include "hotkey_quick_call_table_model.h"
#include "hotkey_state_info_table_model.h"

class Ui_HotKeySettingsDialog;
class MainWindow;

class HotKeySettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit HotKeySettingsDialog(MainWindow *parent);
    ~HotKeySettingsDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_HotKeySettingsDialog> ui;
    MainWindow *main_window;
    HotkeyKeyTableModel *key_table_model;
    HotKeyQuickCallTableModel *quick_call_table_model;
    HotkeyStateInfoTableModel *state_info_table_model;

private slots:
    void save();
};

#endif