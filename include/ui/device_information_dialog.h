#ifndef DEVICE_INFORMATION_DIALOG_H
#define DEVICE_INFORMATION_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_DeviceInformationDialog;
class MainWindow;

class DeviceInformationDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit DeviceInformationDialog(MainWindow *parent);
    ~DeviceInformationDialog();

    std::unique_ptr<Ui_DeviceInformationDialog> ui;
    MainWindow *main_window;
};

#endif