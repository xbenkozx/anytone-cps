#ifndef EXPERT_OPTIONS_DIALOG_H
#define EXPERT_OPTIONS_DIALOG_H

#include <QDialog>
#include <QString>
#include "device.h"
#include "expert_options.h"

class Ui_ExpertOptionsDialog;
class MainWindow;

class ExpertOptionsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ExpertOptionsDialog(MainWindow *parent);
    ~ExpertOptionsDialog();
    void readOptions();
    void writeOptions();

    std::unique_ptr<Ui_ExpertOptionsDialog> ui;
    MainWindow *main_window;
    Anytone::ExpertOptions eo;
};

#endif