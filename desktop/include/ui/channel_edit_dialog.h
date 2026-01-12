#ifndef CHANNEL_EDIT_DIALOG_H
#define CHANNEL_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include <QObject>
#include "channel.h"
#include "radioid.h"
#include "scanlist.h"
#include "receive_group_call_list.h"

class Ui_ChannelSettings;
class MainWindow;

class ChannelEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ChannelEditDialog(MainWindow *parent, int index);
    ~ChannelEditDialog();


    Anytone::Channel *channel;
    std::unique_ptr<Ui_ChannelSettings> ui;

private:
    void loadData();
    void setupUI();
    void save();
    void updateRxFrequency();
    void updateTxFrequency();
    QString formatFrequency(QString frequency);
    int index = 0;
    int selected_ctcss_encode_tone_idx = 0;
    int selected_dcs_encode_tone_idx = 0;
    int selected_ctcss_decode_tone_idx = 0;
    int selected_dcs_decode_tone_idx = 0;
    QVector<Anytone::RadioId*> radio_id_list;
    QVector<Anytone::ScanList*> scanlist_list;
    QVector<Anytone::ReceiveGroup*> receive_group_call_list;
    MainWindow *main_window;
    // ContactSelectionDialog *csd;

private slots:
    void setModeFormVisibility();
    void analogAprsMuteToggle();
    void showContactSelectionDialog();
    void storeCtcssDcsTones();
    void updateCtcssDcsCodes();
    void updateToneCarrierType();
    void nextBtnClicked();
    void prevBtnClicked();
    void saveClose();
    
};

#endif