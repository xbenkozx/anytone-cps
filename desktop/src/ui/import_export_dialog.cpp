
#include "import_export_dialog.h"
#include "ui_import_export_dialog.h"
#include <QFileDialog>
#include <QMessageBox>

ImportExportDialog::ImportExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_ImportExportDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    threadpool = QThreadPool::globalInstance();

    connect(ui->cancelBtn, &QPushButton::clicked, this, &ImportExportDialog::close);
    connect(ui->importBtn, &QPushButton::clicked, this, &ImportExportDialog::importList);
    connect(ui->exportBtn, &QPushButton::clicked, this, &ImportExportDialog::exportList);

    connect(ui->importAllBtn, &QPushButton::clicked, this, &ImportExportDialog::importAllBtnClicked);

    loading_dialog = new LoadingDialog(this);
    
}
ImportExportDialog::~ImportExportDialog(){}

void ImportExportDialog::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    if(is_export){
        setWindowTitle("Export");
        ui->importBtn->setVisible(false);
        ui->importAllBtn->setVisible(false);
    }else{
        setWindowTitle("Import");
        ui->exportBtn->setVisible(false);
        ui->exportAllBtn->setVisible(false);
    }
}

void ImportExportDialog::importAllBtnClicked(){
    #ifdef _WIN32
    QString default_path = "C:/Users/" + QString(getenv("USERNAME")) + "/Documents";
    #else
    QString default_path = "/home/" + QString(getenv("USER")) +  "/Documents";
    #endif

    QString fname = QFileDialog::getOpenFileName(
        this,
        tr("Import List"),
        default_path,
        tr("LST File (*.LST)")
    );

    QMap<CsvList::ListType, QString> list = CsvList::loadFile(fname);
    csv_worker = new CsvList(list);

    loading_dialog->show();

    QObject::connect(csv_worker, &CsvList::update1, loading_dialog, &LoadingDialog::updateMainbar, Qt::QueuedConnection);
    QObject::connect(csv_worker, &CsvList::update2, loading_dialog, &LoadingDialog::updateSubbar, Qt::QueuedConnection);
    QObject::connect(csv_worker, &CsvList::finished, this, &ImportExportDialog::importFinished, Qt::QueuedConnection);
    threadpool->start(csv_worker);

    // if(){
    //     QMessageBox::information(this,
    //         tr("Import"),
    //         tr("Import OK"));
    //     close();
    // }else{
    //     QMessageBox::warning(this,
    //         tr("Import"),
    //         tr("Import Failed"));
    // }
}

void ImportExportDialog::importFinished(const int &result){
    loading_dialog->close();
    close();
    QMessageBox::information(this,
            tr("Import"),
            tr("Import OK"));
}

void ImportExportDialog::importList(){

}
void ImportExportDialog::exportList(){

}
