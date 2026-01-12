#ifndef BASIC_DIALOG_H
#define BASIC_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_BasicDialog;

class BasicDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit BasicDialog(QWidget *parent = nullptr, QString text = "", QString title = "");
    ~BasicDialog();

    std::unique_ptr<Ui_BasicDialog> ui;
};

#endif