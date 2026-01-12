#ifndef ROAMING_ZONE_EDIT_DIALOG_H
#define ROAMING_ZONE_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "roaming_zone.h"

class Ui_RoamingZoneEditDialog;
class MainWindow;

class RoamingZoneEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit RoamingZoneEditDialog(MainWindow *parent, int index);
    ~RoamingZoneEditDialog();
    void setupUI();
    void loadData();
    void save();

    std::unique_ptr<Ui_RoamingZoneEditDialog> ui;
    int index = 0;
    MainWindow *main_window;
    Anytone::RoamingZone *zone;
    QVector<Anytone::RoamingChannel*> available_channels;
    QVector<Anytone::RoamingChannel*> member_channels;

    int available_channel_selected_idx = 0;
    int member_channel_selected_idx = 0;

private slots:
    void orderAvailableId();
    void orderAvailableName();
    void orderAvailable(int sort_type);
    void orderMemberId();
    void orderMemberName();
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