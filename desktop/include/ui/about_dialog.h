#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_AboutDialog;

class AboutDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

    std::unique_ptr<Ui_AboutDialog> ui;
};

#endif