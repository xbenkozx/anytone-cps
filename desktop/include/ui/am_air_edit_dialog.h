#ifndef AM_AIR_EDIT_DIALOG_H
#define AM_AIR_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include <am_air.h>

class Ui_AmAirEditDialog;

class AmAirEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AmAirEditDialog(QWidget *parent, int index);
    ~AmAirEditDialog();
    void loadData();
    void save();
    QString formatFrequency(QString frequency);

    std::unique_ptr<Ui_AmAirEditDialog> ui;
    Anytone::AmAir *channel;
    int index = 0;

private slots:
    void updateFrequency();
    void nextBtnClicked();
    void prevBtnClicked();
};

#endif