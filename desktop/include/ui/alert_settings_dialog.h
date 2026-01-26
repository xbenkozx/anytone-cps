#ifndef ALERT_SETTINGS_DIALOG_H
#define ALERT_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "memory/anytone_memory.h"
#include "channel.h"
#include "aes_encryption_code.h"

class Ui_AlertSettingsDialog;
class MainWindow;

class AlertSettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AlertSettingsDialog(MainWindow *parent);
    ~AlertSettingsDialog();
    void setupUI();
    void loadData();

private:
    std::unique_ptr<Ui_AlertSettingsDialog> ui;
    MainWindow *main_window;
    QVector<Anytone::Channel*> analog_channel_list;
    QVector<Anytone::Channel*> digital_channel_list;

private slots:
    void analogAlarmUpdated();
    void analogEniSendChanged();
    void digitalEniSendChanged();
    void save();
};

#endif