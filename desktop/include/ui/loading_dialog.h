#ifndef LOADING_DIALOG_H
#define LOADING_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_LoadingDialog;

class LoadingDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog();

    std::unique_ptr<Ui_LoadingDialog> ui;
    int subbar_max = 0;
    int mainbar_max = 0;
    QString subbar_text = "";
    QString mainbar_text = "";

protected:
    void showEvent(QShowEvent *event) override;
    
public slots:
    void finished(const int &result);
    void updateMainbar(const int &val, const int &max, const QString &text);
    void updateSubbar(const int &val, const int &max, const QString &text);
};

#endif