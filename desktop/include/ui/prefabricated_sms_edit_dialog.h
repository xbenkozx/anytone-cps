#ifndef PREFABRICATED_SMS_EDIT_DIALOG_H
#define PREFABRICATED_SMS_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "prefabricated_sms.h"

class Ui_PrefabricatedSmsEditDialog;
class MainWindow;

class PrefabricatedSmsEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit PrefabricatedSmsEditDialog(MainWindow *parent, int index);
    ~PrefabricatedSmsEditDialog();
    void loadData();

    std::unique_ptr<Ui_PrefabricatedSmsEditDialog> ui;
    int index = 0;
    MainWindow *main_window;
    Anytone::PrefabricatedSms *sms;

private slots:
    void nextBtnClicked();
    void prevBtnClicked();
    void save();
};

#endif