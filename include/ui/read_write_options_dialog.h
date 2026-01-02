#ifndef READ_WRITE_OPTIONS_DIALOG_H
#define READ_WRITE_OPTIONS_DIALOG_H

#include <QDialog>

class Ui_ReadWriteOptionsDialog;
class MainWindow;

class ReadWriteOptionsDialog: public QDialog
{
    Q_OBJECT

public:
    explicit ReadWriteOptionsDialog(MainWindow *parent = nullptr);
    ~ReadWriteOptionsDialog();
    void setOptionsAndClose();

    bool is_write = false;

private:
    std::unique_ptr<Ui_ReadWriteOptionsDialog> ui;
    MainWindow *parent;
};

#endif