#ifndef ROAMING_CHANNEL_EDIT_DIALOG_H
#define ROAMING_CHANNEL_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "roaming_channel.h"

class Ui_RoamingChannelEditDialog;
class MainWindow;

class RoamingChannelEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit RoamingChannelEditDialog(MainWindow *parent, int index);
    ~RoamingChannelEditDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_RoamingChannelEditDialog> ui;
    int index = 0;
    MainWindow *main_window;
    Anytone::RoamingChannel *channel;

private slots:
    void fastSelect();
    void formatRxFrequency();
    void formatTxFrequency();
    void nextBtnClicked();
    void prevBtnClicked();
    void save();
};

#endif