#ifndef ANALOG_ADDRESS_EDIT_DIALOG_H
#define ANALOG_ADDRESS_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <memory>
#include "memory/anytone_memory.h"
#include "analog_address.h"

class Ui_AnalogAddressEditDialog;
class MainWindow;

class AnalogAddressEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AnalogAddressEditDialog(MainWindow *parent, int index);
    ~AnalogAddressEditDialog();
    void loadData();

    std::unique_ptr<Ui_AnalogAddressEditDialog> ui;
    Anytone::AnalogAddress *address;
    MainWindow *main_window;
    int index;

private slots:
    void save();
    void prevBtnClicked();
    void nextBtnClicked();
};

#endif