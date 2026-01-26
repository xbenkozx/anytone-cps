
#include "satellite_dialog.h"
#include "ui_satellite_dialog.h"
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFileInfo>
#include "memory/anytone_memory.h"
#include "memory/satellite.h"
#include "satellite_table_model.h"
#include "user_settings.h"

SatelliteDialog::SatelliteDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_SatelliteDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    ui->progressBar->setVisible(false);

    threadpool = QThreadPool::globalInstance();

    connect(ui->refreshBtn, &QPushButton::clicked, this, &SatelliteDialog::downloadKeplerData);
    connect(ui->writeBtn, &QPushButton::clicked, this, &SatelliteDialog::writeData);

    table_model = new SatelliteTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 70);
    ui->tableView->setColumnWidth(2, 200);
    ui->tableView->setColumnWidth(3, 70);
    ui->tableView->setColumnWidth(4, 70);
    ui->tableView->setColumnWidth(5, 70);
    ui->tableView->setColumnWidth(6, 70);
    ui->tableView->setColumnWidth(7, 70);
    ui->tableView->setColumnWidth(8, 70);
    ui->tableView->setColumnWidth(9, 70);
    ui->tableView->setColumnWidth(1, 70);
    ui->tableView->setColumnWidth(11, 70);
    ui->tableView->setColumnWidth(12, 70);
    ui->tableView->setColumnWidth(13, 70);
    ui->tableView->setColumnWidth(14, 70);

    QString file_path = UserSettings::getUserDirectory() + "kepler.txt";
    if (QFile::exists(file_path)) {
        QFileInfo fileInfo(file_path);
        if (fileInfo.exists()) {
            ui->label->setText("Last Updated: " + fileInfo.lastModified().toString("MM/dd/yy HH:mm"));
        }
        QFile file(file_path);
        if(file.open(QIODevice::ReadOnly)){
            if(file.size() > 0){
                QByteArray data = file.readAll();
                QString content = QString::fromUtf8(data);

                decodeSatelliteData(content);

                file.close();
                return;
            }else{
                qDebug() << "kepler.txt is empty.";
            }
        }else{
            qDebug() << "Error opening kepler.txt for reading:" << file.errorString();
        }
    }
    
}
SatelliteDialog::~SatelliteDialog(){
    
}


void SatelliteDialog::downloadKeplerData(){

    
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://celestrak.org/NORAD/elements/gp.php?GROUP=amateur")));

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QString content = QString::fromUtf8(data);                
            QFile kepFile(UserSettings::getUserDirectory() + "kepler.txt");
            if(kepFile.open(QIODevice::WriteOnly)){
                kepFile.write(content.toUtf8());
                kepFile.close();
            }
            decodeSatelliteData(content);
            QFileInfo fileInfo(UserSettings::getUserDirectory() + "kepler.txt");
            if (fileInfo.exists()) {
                ui->label->setText("Last Updated: " + fileInfo.lastModified().toString("MM/dd/yy HH:mm"));
            }
        }else{
            qDebug() << "Error downloading Kepler data:" << reply->errorString();
        }
        reply->deleteLater();
    });
    
}

void SatelliteDialog::decodeSatelliteData(QString data){
    Anytone::Memory::satellite_data_list.clear();
    QStringList lines = data.split("\n", Qt::SkipEmptyParts);
    for(int line = 0; line < lines.size(); line += 3){
        if(line + 2 >= lines.size()) break;
        QString name = lines.at(line).trimmed();
        QString line1 = lines.at(line + 1).trimmed();
        QString line2 = lines.at(line + 2).trimmed();

        Anytone::Satellite *sat = new Anytone::Satellite();
        sat->decodeKeplerData(name + "\n" + line1 + "\n" + line2);
        sat->write_enable = sat->rx_frequency > 0 ? 1 : 0;
        Anytone::Memory::satellite_data_list.append(sat);                
    }

    table_model->reload();
}

void SatelliteDialog::writeData(){
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
    adw->setReadWriteOptions(DeviceRWType::SATELLITE_DATA);
    adw->is_write = true;
    QObject::connect(adw, &SerialWorker::update1, this, &SatelliteDialog::updateMainBar);
    QObject::connect(adw, &SerialWorker::finished, this, &SatelliteDialog::writeToRadioFinished, Qt::QueuedConnection);
    threadpool->start(adw);
}

void SatelliteDialog::updateMainBar(const int &val, const int &max, const QString &text){
    ui->progressBar->setValue(val);
    ui->progressBar->setMaximum(max);
}

void SatelliteDialog::writeToRadioFinished(const int &result){
    ui->progressBar->setVisible(false);
}
