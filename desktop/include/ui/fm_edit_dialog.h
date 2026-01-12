#ifndef FM_EDIT_DIALOG_H
#define FM_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "fm.h"

class Ui_FmEditDialog;
class MainWindow;

class FmEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit FmEditDialog(MainWindow *parent, int index);
    ~FmEditDialog();
    void loadData();

    std::unique_ptr<Ui_FmEditDialog> ui;
    Anytone::FM *fm;
    MainWindow *main_window;
    int index = 0;

private slots:
    void save();
    void nextBtnClicked();
    void prevBtnClicked();
    void updateFrequencyText();

};

#endif