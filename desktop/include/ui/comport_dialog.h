#ifndef COMPORT_DIALOG_H
#define COMPORT_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_ComportDialog;
class MainWindow;

class ComportDialog: public QDialog 
{
    Q_OBJECT

public:
    explicit ComportDialog(MainWindow *parent);
    ~ComportDialog();
    void openFile();
    
    std::unique_ptr<Ui_ComportDialog> ui;
    QString comport = QString("");
    QString virtual_file_name = QString("");
    MainWindow *main_window;

private slots:
    void save();
    void comportChanged();
    void populatePorts();
};

#endif