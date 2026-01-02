#ifndef RADIO_ID_EDIT_DIALOG_H
#define RADIO_ID_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "radioid.h"

class Ui_RadioIdEditDialog;
class MainWindow;

class RadioIdEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit RadioIdEditDialog(MainWindow *parent, int index);
    ~RadioIdEditDialog();
    void loadData();

    std::unique_ptr<Ui_RadioIdEditDialog> ui;
    MainWindow *main_window;
    int index = 0;
    Anytone::RadioId *rid;

private slots:
    void nextBtnClicked();
    void prevBtnClicked();
    void save();
};

#endif