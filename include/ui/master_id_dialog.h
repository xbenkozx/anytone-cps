#ifndef MASTER_ID_DIALOG_H
#define MASTER_ID_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_MasterIdDialog;
class MainWindow;

class MasterIdDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit MasterIdDialog(MainWindow *parent);
    ~MasterIdDialog();
    void loadData();

    std::unique_ptr<Ui_MasterIdDialog> ui;
    MainWindow *main_window;

private slots:
    void save();
};

#endif