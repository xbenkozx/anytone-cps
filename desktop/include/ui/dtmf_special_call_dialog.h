#ifndef DTMF_SPECIAL_CALL_DIALOG_H
#define DTMF_SPECIAL_CALL_DIALOG_H

#include <QDialog>
#include <QString>

class Ui_DtmfSpecialCallDialog;
class DtmfSettingsDialog;

class DtmfSpecialCallDialog : public QDialog 
{
    Q_OBJECT

public:
    explicit DtmfSpecialCallDialog(DtmfSettingsDialog *parent);
    ~DtmfSpecialCallDialog();

    std::unique_ptr<Ui_DtmfSpecialCallDialog> ui;
    DtmfSettingsDialog *dtmf_dialog;
private slots:
    void save();
};

#endif