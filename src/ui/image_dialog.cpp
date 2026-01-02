
#include <QFileDialog>
#include "image_dialog.h"
#include "ui_image_dialog.h"
#include "user_settings.h"


ImageDialog::ImageDialog(QWidget *parent, DeviceRWType option) :
    QDialog(parent),
    ui(std::make_unique<Ui_ImageDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    threadpool = QThreadPool::globalInstance();
    this->option = option;

    if(option == DeviceRWType::BOOT_IMAGE){
        setWindowTitle("Boot Image");
    }else if(option == DeviceRWType::BK1_IMAGE){
        setWindowTitle("BK1 Image");
    }else if(option == DeviceRWType::BK2_IMAGE){
        setWindowTitle("BK2 Image");
    }
    
    connect(ui->openImageBtn, &QPushButton::clicked, this, &ImageDialog::openImage);
    connect(ui->readBtn, &QPushButton::clicked, this, &ImageDialog::readImage);
    connect(ui->writeBtn, &QPushButton::clicked, this, &ImageDialog::writeImage);
    connect(ui->openBinBtn, &QPushButton::clicked, this, &ImageDialog::openBin);
    connect(ui->saveBinBtn, &QPushButton::clicked, this, &ImageDialog::saveBin);

    ui->progressBar->setMaximum(0xa000);
    ui->progressBar->setVisible(false);
    
}
ImageDialog::~ImageDialog(){}
void ImageDialog::openImage(){
    QString fname = QFileDialog::getOpenFileName(
        this,
        tr("Open Image"),
        QDir::currentPath(),
        tr("Image Files (*.jpg *.jpeg *.bmp)")
    );

    if (fname.isEmpty()) {
        return;
    }

    QImage image;

    // Try to load the image from the specified file path
    if (image.load(fname)) {
        image_data = convertImageToRGB565BigEndian(image);
        showImageData();
    } else {
        qDebug() << "Failed to load image:" << fname;
    }
}
void ImageDialog::readWriteImage(bool is_write){
    if(UserSettings::comport.size() == 0){
        qDebug() << "Error: Comport not set";
        return;
    }

    if(UserSettings::comport != QString("VIRTUAL")){
        bool com_connected = false;
        const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &portInfo : serialPortInfos) {
            if(UserSettings::comport == portInfo.portName()) com_connected = true;
        }
        if(!com_connected){
            qDebug() << "COM Error: COM Port not available";
            return;
        }
    }

    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);

    adw = new SerialWorker();
    if(UserSettings::comport == QString("VIRTUAL")){
        adw->setVirtualFile(UserSettings::virtual_file_name);
    }else{
        adw->setComport(UserSettings::comport);
    }
    adw->setReadWriteOptions(option);
    adw->is_write = is_write;
    if(is_write) adw->setImageData(image_data);
    QObject::connect(adw, &SerialWorker::update1, this, &ImageDialog::updateMainBar);
    QObject::connect(adw, &SerialWorker::imageDataReady, this, &ImageDialog::imageDataReady);
    QObject::connect(adw, &SerialWorker::finished, this, &ImageDialog::readFromRadioFinished, Qt::QueuedConnection);
    threadpool->start(adw);
}
void ImageDialog::readImage(){
    readWriteImage(false);
}
void ImageDialog::writeImage(){
    readWriteImage(true);
}
void ImageDialog::saveBin(){
    QString fname = QFileDialog::getSaveFileName(
        this,
        tr("Save Bin"),
        QDir::currentPath(),
        tr("Bin Files (*.bin)")
    );

    if (fname.isEmpty()) {
        return;
    }

    QFile file(fname);
    if (!file.open(QIODevice::WriteOnly)) {
        qDebug() << "ERR: Cannot open file";
        return;
    }

    qint64 written = file.write(image_data); 

    if (written != image_data.size()) {
        qDebug() << "ERR: Incomplete write";
        file.close();
        return;
    }

    file.close();
}
void ImageDialog::openBin(){
    QString fname = QFileDialog::getOpenFileName(
        this,
        tr("Open Bin"),
        QDir::currentPath(),
        tr("Bin Files (*.bin)")
    );

    if (fname.isEmpty()) {
        return;
    }

    QFile file(fname);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERR: Cannot open file";
        return;
    }

    QTextStream in(&file);
    QString fileContent;
    
    image_data = file.readAll();

    file.close();
    showImageData();
}
void ImageDialog::updateMainBar(const int &val, const int &max, const QString &text){
    ui->progressBar->setValue(val);
}
void ImageDialog::imageDataReady(QByteArray image_data){
    this->image_data = QByteArray(image_data);
    showImageData();
}
void ImageDialog::readFromRadioFinished(const int &result){
    ui->progressBar->setVisible(false);
}
void ImageDialog::showImageData()
{
    constexpr int h = 160;
    constexpr int w = 128;

    const QByteArray &src = image_data;
    if (src.size() < w * h * 2)
        return;
    QByteArray tmp;
    tmp.resize(w * h * 2);

    const uchar *in = reinterpret_cast<const uchar*>(src.constData());
    quint16 *out16  = reinterpret_cast<quint16*>(tmp.data());

    for (int i = 0; i < w * h; ++i) {
        out16[i] = qFromBigEndian<quint16>(in + i * 2);
    }
    QImage img(reinterpret_cast<const uchar*>(tmp.constData()),
               w, h,
               w * 2,
               QImage::Format_RGB16);

    QImage imgCopy = img.copy();
    QImage transposed = imgCopy.transformed(QTransform().rotate(90).scale(1, -1));
    // QImage transposed = imgCopy.transformed(QTransform(0, 1, 1, 0, 0, 0));

    ui->imageLabel->setPixmap(QPixmap::fromImage(transposed));
}
QByteArray ImageDialog::convertImageToRGB565BigEndian(const QImage &input)
{
    // Work in a known format
    QImage img = input.convertToFormat(QImage::Format_RGB888);

    const int w = img.width();
    const int h = img.height();

    QByteArray out;
    out.resize(w * h * 2);

    uchar *dst = reinterpret_cast<uchar*>(out.data());

    for (int y = 0; y < h; ++y) {
        const uchar *row = img.constScanLine(y); // RGB888: R,G,B repeating
        for (int x = 0; x < w; ++x) {
            const int idx = x * 3;
            const uchar r = row[idx + 0];
            const uchar g = row[idx + 1];
            const uchar b = row[idx + 2];

            const quint16 r5 = (r >> 3) & 0x1F;
            const quint16 g6 = (g >> 2) & 0x3F;
            const quint16 b5 = (b >> 3) & 0x1F;

            const quint16 rgb565 = (r5 << 11) | (g6 << 5) | b5;

            // big-endian write (like struct.pack('>H', ...))
            qToBigEndian<quint16>(rgb565, dst);
            dst += 2;
        }
    }

    return out;
}

