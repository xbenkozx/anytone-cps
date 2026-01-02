#ifndef AES_ENCRYPTION_CODE_DIALOG_H
#define AES_ENCRYPTION_CODE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <memory>
#include "memory/memory.h"
#include "aes_encryption_code.h"

class Ui_AesEncryptionCodeEditDialog;
class MainWindow;

class AesEncryptionCodeDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AesEncryptionCodeDialog(MainWindow *parent, int index);
    ~AesEncryptionCodeDialog();
    void loadData();

    std::unique_ptr<Ui_AesEncryptionCodeEditDialog> ui;
    Anytone::AesEncryptionCode *key;
    int index = 0;
    MainWindow *main_window;

private slots:
    void save();
    void prevBtnClicked();
    void nextBtnClicked();
};

#endif