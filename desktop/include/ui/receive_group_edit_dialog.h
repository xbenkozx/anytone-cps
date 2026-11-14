#ifndef RECEIVE_GROUP_EDIT_DIALOG_H
#define RECEIVE_GROUP_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "memory/receive_group_call_list.h"
#include "talkgroup.h"

class Ui_ReceiveGroupEditDialog;
class MainWindow;

class ReceiveGroupEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit ReceiveGroupEditDialog(MainWindow *parent, int index);
    ~ReceiveGroupEditDialog();
    void setupUI();
    void loadData();
    void save();

    std::unique_ptr<Ui_ReceiveGroupEditDialog> ui;
    int index = 0;
    MainWindow *main_window;
    Anytone::ReceiveGroup *group;
    QVector<Anytone::Talkgroup*> available_channels;
    QVector<Anytone::Talkgroup*> member_channels;

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