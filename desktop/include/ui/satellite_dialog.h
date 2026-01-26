#ifndef SATELLITE_DIALOG_H
#define SATELLITE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QThreadPool>
#include <QSerialPortInfo>
#include "device.h"

class Ui_SatelliteDialog;
class SatelliteTableModel;

class SatelliteDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit SatelliteDialog(QWidget *parent = nullptr);
    ~SatelliteDialog();
    void downloadKeplerData();
    void decodeSatelliteData(QString data);
    void writeData();

    std::unique_ptr<Ui_SatelliteDialog> ui;

    SatelliteTableModel *table_model;
    SerialWorker *adw;
    QThreadPool *threadpool;

public slots:
    void updateMainBar(const int &val, const int &max, const QString &text);
    void writeToRadioFinished(const int &result);
};

#endif