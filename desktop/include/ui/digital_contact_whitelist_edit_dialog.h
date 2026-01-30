#ifndef DIGITAL_CONTACT_WHITELIST_EDIT_DIALOG_H
#define DIGITAL_CONTACT_WHITELIST_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "talkgroup_whitelist.h"

class Ui_TalkgroupWhitelistEditDialog;
class MainWindow;

class DigitalContactWhitelistEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit DigitalContactWhitelistEditDialog(QWidget *parent, int index);
    ~DigitalContactWhitelistEditDialog();
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