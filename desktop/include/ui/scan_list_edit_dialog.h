#ifndef SCAN_LIST_EDIT_DIALOG_H
#define SCAN_LIST_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "channel.h"
#include "scanlist.h"

class Ui_ScanEditDialog;
class MainWindow;

class ScanListEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ScanListEditDialog(MainWindow *parent, int index);
    ~ScanListEditDialog();
    void setupUI();
    void loadData();
    void save();
    void priorityChannelSelectChanged();
    void updatePriorityChannelList();

    std::unique_ptr<Ui_ScanEditDialog> ui;
    int index = 0;
    MainWindow *main_window;

    Anytone::ScanList *scanlist;
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