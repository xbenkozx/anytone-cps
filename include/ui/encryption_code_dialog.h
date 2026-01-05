#ifndef ENCRYPTION_CODE_DIALOG_H
#define ENCRYPTION_CODE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <memory>
#include "memory/memory.h"
#include "encryption_code.h"

class Ui_EncryptionCodeEditDialog;
class MainWindow;

class EncryptionCodeDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit EncryptionCodeDialog(MainWindow *parent, int index);
    ~EncryptionCodeDialog();
    void loadData();

    std::unique_ptr<Ui_EncryptionCodeEditDialog> ui;
    Anytone::EncryptionCode *key;
    int index = 0;
    MainWindow *main_window;

private slots:
    void save();
    void prevBtnClicked();
    void nextBtnClicked();
};

#endif