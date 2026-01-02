#ifndef COMPORT_DIALOG_H
#define COMPORT_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_ComportDialog;

class ComportDialog: public QDialog 
{

    Q_OBJECT

public:
    explicit ComportDialog(QWidget *parent = nullptr);
    ~ComportDialog();
    void openFile();
    
    std::unique_ptr<Ui_ComportDialog> ui;
    QString comport = QString("");
    QString virtual_file_name = QString("");

private slots:
    void save();
    void comportChanged();
};

#endif