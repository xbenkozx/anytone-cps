#ifndef TALK_ALIAS_SETTINGS_DIALOG_H
#define TALK_ALIAS_SETTINGS_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_TalkAliasSettingsDialog;

class TalkAliasSettingsDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit TalkAliasSettingsDialog(QWidget *parent);
    ~TalkAliasSettingsDialog();

    void loadData();

    std::unique_ptr<Ui_TalkAliasSettingsDialog> ui;

private slots:
    void save();
};

#endif