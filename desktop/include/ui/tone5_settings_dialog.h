#ifndef TONE5_SETTINGS_DIALOG_H
#define TONE5_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include "tone5_settings.h"
#include "tone5_table_model.h"

class Ui_Tone5SettingsDialog;
class MainWindow;

class Tone5SettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit Tone5SettingsDialog(MainWindow *parent);
    ~Tone5SettingsDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_Tone5SettingsDialog> ui;
    MainWindow *main_window;
    Anytone::Tone5Settings *tone5;
    Tone5TableModel *table_model;
private slots:
    void save();
    void decodeStandardChanged();
};

#endif