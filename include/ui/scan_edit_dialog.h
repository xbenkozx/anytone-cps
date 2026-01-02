#ifndef SCAN_EDIT_DIALOG_H
#define SCAN_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include <QVector>
#include "scanlist.h"
#include "channel.h"

class Ui_ScanEditDialog;
class MainWindow;

class ScanEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ScanEditDialog(MainWindow *parent, int index);
    ~ScanEditDialog();
    void setupUI();
    void loadData();
    void save();
    void orderAvailable(int sort_type);
    void updateChannelTables();
    void updatePriorityChannelList();

    std::unique_ptr<Ui_ScanEditDialog> ui;
    MainWindow *main_window;
    int index = 0;
    Anytone::ScanList *scan_list;

    QVector<Anytone::Channel*> available_channels;
    QVector<Anytone::Channel*> member_channels;

    int available_channel_selected_idx = 0;
    int member_channel_selected_idx = 0;

private slots:
    void nextBtnClicked();
    void prevBtnClicked();
    void saveClose();
    void pushChannel();
    void popChannel();
    void orderMemberId();
    void orderMemberName();
    void orderUp();
    void orderDown();
    void orderAvailableId();
    void orderAvailableName();
    void priorityChannelSelectChanged();
};

#endif