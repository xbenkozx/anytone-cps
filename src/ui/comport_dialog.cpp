#include "comport_dialog.h"
#include "ui_comport_dialog.h"
#include "user_settings.h"
#include <QSerialPortInfo>
#include <QFileDialog>

ComportDialog::ComportDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_ComportDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &ComportDialog::save);
    connect(ui->fileBtn, &QPushButton::clicked, this, &ComportDialog::openFile);
    connect(ui->comPortCmbx, &QComboBox::currentIndexChanged, this, &ComportDialog::comportChanged);

    const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();

    QVector<QString> com_list = {"VIRTUAL"};

    ui->comPortCmbx->addItem(QString("VIRTUAL"), QString("VIRTUAL"));
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        QString vendor_id = QString::number(portInfo.vendorIdentifier(), 16);
        QString product_id = QString::number(portInfo.productIdentifier(), 16);
        if(vendor_id == QString("28e9") && product_id == QString("18a")){
            ui->comPortCmbx->addItem(portInfo.portName(), portInfo.portName());
            com_list.push_back(portInfo.portName());
        }
    }

    int comport_idx = com_list.indexOf(UserSettings::comport);
    ui->comPortCmbx->setCurrentIndex(comport_idx);

    ui->label_2->setText(UserSettings::virtual_file_name);
}
ComportDialog::~ComportDialog(){}
void ComportDialog::save(){
    UserSettings::comport = ui->comPortCmbx->itemData(ui->comPortCmbx->currentIndex()).toString();
    UserSettings::virtual_file_name = virtual_file_name;
    UserSettings::save();
}
void ComportDialog::openFile(){
    QString fname = QFileDialog::getOpenFileName(
        this,
        tr("Open Virtual Memory"),
        QDir::currentPath(),
        tr("Bin Files (*.bin)")
    );

    if (fname.isEmpty()) {
        return;
    }

    virtual_file_name = fname;
    ui->label_2->setText(virtual_file_name);
}
void ComportDialog::comportChanged(){
    ui->fileBtn->setVisible((ui->comPortCmbx->currentText() == "VIRTUAL"));
    ui->label_2->setVisible((ui->comPortCmbx->currentText() == "VIRTUAL"));
}