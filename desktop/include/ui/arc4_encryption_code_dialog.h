#ifndef ARC4_ENCRYPTION_CODE_DIALOG_H
#define ARC4_ENCRYPTION_CODE_DIALOG_H

#include <QDialog>
#include <QString>
#include <QObject>
#include <memory>
#include "memory/at_memory.h"
#include "arc4_encryption_code.h"

class Ui_Arc4EncryptionCodeEditDialog;
class MainWindow;

class Arc4EncryptionCodeDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit Arc4EncryptionCodeDialog(MainWindow *parent, int index);
    ~Arc4EncryptionCodeDialog();
    void loadData();

    std::unique_ptr<Ui_Arc4EncryptionCodeEditDialog> ui;
    Anytone::Arc4EncryptionCode *key;
    int index = 0;
    MainWindow *main_window;

private slots:
    void save();
    void prevBtnClicked();
    void nextBtnClicked();
};

#endif