#ifndef RETRY_CONNECTION_DIALOG_H
#define RETRY_CONNECTION_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_RetryConnectionDialog;
class MainWindow;

class RetryConnectionDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit RetryConnectionDialog(MainWindow *parent);
    ~RetryConnectionDialog();

    std::unique_ptr<Ui_RetryConnectionDialog> ui;
    bool is_write = false;
    MainWindow *main_window;
private slots:
    void retry();
};

#endif