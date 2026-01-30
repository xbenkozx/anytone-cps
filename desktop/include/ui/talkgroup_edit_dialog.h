#ifndef TALKGROUP_EDIT_DIALOG_H
#define TALKGROUP_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "talkgroup.h"

class Ui_TalkgroupEditDialog;
class MainWindow;

class TalkgroupEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit TalkgroupEditDialog(MainWindow *parent, int index);
    ~TalkgroupEditDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_TalkgroupEditDialog> ui;
    MainWindow *main_window;
    int index = 0;
    Anytone::Talkgroup *tg;

private slots:
    void callTypeChanged();
    void dmrIdEditingFinished();
    void nextBtnClicked();
    void prevBtnClicked();
    void save();
};

#endif