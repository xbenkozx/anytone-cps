#ifndef IMAGE_DIALOG_H
#define IMAGE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QTransform>
#include <QtEndian>
#include <QByteArray>
#include <QThreadPool>
#include <QSerialPortInfo>
#include "device.h"

class Ui_ImageDialog;

class ImageDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent, DeviceRWType option);
    ~ImageDialog();
    void openImage();
    void readWriteImage(bool is_write);
    void readImage();
    void writeImage();
    void saveBin();
    void openBin();
    void showImageData();
    QByteArray convertImageToRGB565BigEndian(const QImage &input);
    QByteArray image_data;
    std::unique_ptr<Ui_ImageDialog> ui;
    SerialWorker *adw;
    QThreadPool *threadpool;
    DeviceRWType option;

private slots:
    void updateMainBar(const int &val, const int &max, const QString &text);
    void readFromRadioFinished(const int &result);
    void imageDataReady(QByteArray image_data);
};

#endif