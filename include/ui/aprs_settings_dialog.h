#ifndef APRS_SETTINGS_DIALOG_H
#define APRS_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include "aprs_receive_filter_table_model.h"
#include "aprs_settings.h"

class Ui_AprsSettingsDialog;

class AprsSettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AprsSettingsDialog(QWidget *parent);
    ~AprsSettingsDialog();
    void setupUI();
    void loadData();
    static double degMinToDecimal(int deg, double minutes);
    static double toFrequencyDouble(int frequency);
    static QString toFrequencyString(int frequency);
    std::unique_ptr<Ui_AprsSettingsDialog> ui;
    Anytone::AprsSettings *aprs;
    AprsReceiveFilterTableModel *filter_model;

};

#endif