#ifndef ZONE_EDIT_DIALOG_H
#define ZONE_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "channel.h"
#include "zone.h"

class Ui_ZoneEditDialog;
class MainWindow;

class ZoneEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ZoneEditDialog(MainWindow *parent, int index);
    ~ZoneEditDialog();
    void setupUI();
    void loadData();
    void save();
    void updateChannelSelectLists();

    std::unique_ptr<Ui_ZoneEditDialog> ui;
    int index = 0;
    MainWindow *main_window;

    Anytone::Zone *zone;
    QVector<Anytone::Channel*> available_channels;
    QVector<Anytone::Channel*> member_channels;

    int available_channel_selected_idx = 0;
    int member_channel_selected_idx = 0;

private slots:
    void orderAvailableId();
    void orderAvailableName();
    void orderAvailable(int sort_type);
    void orderMemberId();
    void orderMemberName();
    void orderMemberFreq();
    void updateChannelTables();
    void pushChannel();
    void popChannel();
    void orderUp();
    void orderDown();
    void nextBtnClicked();
    void prevBtnClicked();
    void saveClose();
};

#endif