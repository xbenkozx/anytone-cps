#ifndef AUTO_REPEATER_EDIT_DIALOG_H
#define AUTO_REPEATER_EDIT_DIALOG_H

#include <QDialog>
#include <QString>
#include "memory/memory.h"
#include "auto_repeater_offset_frequency.h"

class Ui_AutoRepeaterOffsetFrequencyEditDialog;
class MainWindow;

class AutoRepeaterEditDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit AutoRepeaterEditDialog(MainWindow *parent, int index);
    ~AutoRepeaterEditDialog();

    std::unique_ptr<Ui_AutoRepeaterOffsetFrequencyEditDialog> ui;
    MainWindow *main_window;
    Anytone::AutoRepeaterOffsetFrequency *arf;
    int index = 0;
    

private:
    void loadData();
    void formatFrequency();

private slots:
    void nextBtnClicked();
    void prevBtnClicked();
    void save();

};

#endif