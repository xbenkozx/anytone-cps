#ifndef LOCAL_INFORMATION_DIALOG_H
#define LOCAL_INFORMATION_DIALOG_H

#include <QDialog>
#include <QString>
#include "device.h"
#include "expert_options.h"

class Ui_LocalInformationDialog;
class MainWindow;

class LocalInformationDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit LocalInformationDialog(MainWindow *parent);
    ~LocalInformationDialog();
    void readRadio();

    std::unique_ptr<Ui_LocalInformationDialog> ui;
    MainWindow *main_window;
    Anytone::ExpertOptions eo;
};

#endif