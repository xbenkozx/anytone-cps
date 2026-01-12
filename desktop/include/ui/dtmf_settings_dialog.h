#ifndef DTMF_SETTINGS_DIALOG_H
#define DTMF_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include "dtmf_settings.h"

class Ui_DtmfSettingsDialog;
class MainWindow;

class DtmfSettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit DtmfSettingsDialog(MainWindow *parent);
    ~DtmfSettingsDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_DtmfSettingsDialog> ui;
    MainWindow *main_window;
    Anytone::DTMFSettings *dtmf;
    QLineEdit *last_selected_linedit = nullptr;

private slots:
    void save();
    void showSpecialCallDialog();
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif