#ifndef AM_ZONE_EDIT_DIALOG_H
#define AM_ZONE_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "am_zone.h"
#include "am_air.h"

class Ui_AmZoneEditDialog;

class AmZoneEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AmZoneEditDialog(QWidget *parent, int index);
    ~AmZoneEditDialog();
    void loadData();
    void save();
    void updateAChannelList();

    std::unique_ptr<Ui_AmZoneEditDialog> ui;
    int index = 0;
    Anytone::AmZone* zone;
    QVector<Anytone::AmAir*> available_channels;
    QVector<Anytone::AmAir*> member_channels;
    QVector<Anytone::AmAir*> available_scan_channels;
    QVector<Anytone::AmAir*> scan_channels;

    int available_channel_selected_idx = 0;
    int member_channel_selected_idx = 0;
    int available_scan_channel_selected_idx = 0;
    int member_scan_channel_selected_idx = 0;

private slots:
    void orderMemberId();
    void orderMemberName();
    void updateChannelTables();
    void pushChannel();
    void popChannel();
    void pushScanChannel();
    void popScanChannel();
    void orderUp();
    void orderDown();
    void nextBtnClicked();
    void prevBtnClicked();
};

#endif