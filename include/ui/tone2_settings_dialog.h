#ifndef TONE2_SETTINGS_DIALOG_H
#define TONE2_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include "tone2_settings.h"
#include "tone2_decode_table_model.h"
#include "tone2_encode_table_model.h"

class Ui_Tone2SettingsDialog;
class MainWindow;

class Tone2SettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit Tone2SettingsDialog(MainWindow *parent);
    ~Tone2SettingsDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_Tone2SettingsDialog> ui;
    MainWindow *main_window;
    Anytone::Tone2Settings *tone2;
    Tone2EncodeTableModel *encode_table_model;
    Tone2DecodeTableModel *decode_table_model;

private slots:
    void save();
};

#endif