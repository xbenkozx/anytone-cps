
#include "dtmf_special_call_dialog.h"
#include "ui_dtmf_special_call_dialog.h"
#include "dtmf_settings_dialog.h"
#include "ui_dtmf_settings_dialog.h"


DtmfSpecialCallDialog::DtmfSpecialCallDialog(DtmfSettingsDialog *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_DtmfSpecialCallDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    dtmf_dialog = parent;
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DtmfSpecialCallDialog::save);
    ui->callTypeCmbx->addItem("ANI");
    ui->otherIdTxt->setText("000");
    
}
DtmfSpecialCallDialog::~DtmfSpecialCallDialog(){}
void DtmfSpecialCallDialog::save(){
    QString special_call = ui->otherIdTxt->text() + "*" + dtmf_dialog->ui->selfIdTxt->text();
    dtmf_dialog->last_selected_linedit->setText(special_call);
}
