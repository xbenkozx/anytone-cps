#ifndef HOTKEY_SETTIINGS_DIALOG_H
#define HOTKEY_SETTIINGS_DIALOG_H

#include <QDialog>
#include <QString>

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

private slots:
    void save();
};

#endif