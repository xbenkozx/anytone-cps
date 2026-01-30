#ifndef IMPORT_EXPORT_DIALOG_H
#define IMPORT_EXPORT_DIALOG_H

#include <QDialog>
#include <QString>
#include <QVector>
#include <QMap>
#include <QThreadPool>
#include "csv.h"
#include "loading_dialog.h"

class Ui_ImportExportDialog;

class ImportExportDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ImportExportDialog(QWidget *parent);
    ~ImportExportDialog();
    void showEvent(QShowEvent *event) override;
    QString openCsv();

    std::unique_ptr<Ui_ImportExportDialog> ui;
    bool is_export = false;

    QVector<QMap<int, QString>> ie_list;
    QThreadPool *threadpool;
    CsvList *csv_worker;
    LoadingDialog *loading_dialog;
    QMap<CsvList::ListType, QString> list;

    #ifdef _WIN32
    QString default_path = "C:/Users/" + QString(getenv("USERNAME")) + "/Downloads";
    #else
    QString default_path = "/home/" + QString(getenv("USER")) +  "/Downloads";
    #endif

private slots:
    void importList();
    void exportList();
    void importFinished(const int &result);

    void importAllBtnClicked();
};

#endif