#ifndef TALKGROUP_WHITELIST_EDIT_DIALOG_H
#define TALKGROUP_WHITELIST_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "talkgroup_whitelist.h"

class Ui_TalkgroupWhitelistEditDialog;
class MainWindow;

class TalkgroupWhitelistEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit TalkgroupWhitelistEditDialog(QWidget *parent, int index);
    ~TalkgroupWhitelistEditDialog();
    void setupUI();
    void loadData();

    std::unique_ptr<Ui_TalkgroupWhitelistEditDialog> ui;
    int index = 0;
    Anytone::TalkgroupWhitelist *tg;

private slots:
    void callTypeChanged();
    void dmrIdEditingFinished();
    void save();
};

#endif