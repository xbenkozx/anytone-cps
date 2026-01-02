
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include "dtmf_settings_dialog.h"
#include "ui_dtmf_settings_dialog.h"
#include "dtmf_special_call_dialog.h"
#include "memory/memory.h"
#include "main_window.h"
#include "constants.h"


DtmfSettingsDialog::DtmfSettingsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_DtmfSettingsDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DtmfSettingsDialog::save);
    connect(ui->specialCallBtn, &QPushButton::clicked, this, &DtmfSettingsDialog::showSpecialCallDialog);

    ui->pttIdBotTxt->installEventFilter(this);
    ui->pttIdEotTxt->installEventFilter(this);
    ui->m1Txt->installEventFilter(this);
    ui->m2Txt->installEventFilter(this);
    ui->m3Txt->installEventFilter(this);
    ui->m4Txt->installEventFilter(this);
    ui->m5Txt->installEventFilter(this);
    ui->m6Txt->installEventFilter(this);
    ui->m7Txt->installEventFilter(this);
    ui->m8Txt->installEventFilter(this);
    ui->m9Txt->installEventFilter(this);
    ui->m10Txt->installEventFilter(this);
    ui->m11Txt->installEventFilter(this);
    ui->m12Txt->installEventFilter(this);
    ui->m13Txt->installEventFilter(this);
    ui->m14Txt->installEventFilter(this);
    ui->m15Txt->installEventFilter(this);
    ui->m16Txt->installEventFilter(this);

    // connect(ui->selfIdTxt, &QLineEdit::editingFinished, this, [this](const QString &text){ ui->selfIdTxt->setText(text.leftJustified(3, '0')); });

    connect(ui->pttIdBotTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->pttIdBotTxt->setText(text.toUpper()); });
    connect(ui->pttIdEotTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->pttIdEotTxt->setText(text.toUpper()); });
    connect(ui->remotelyKillTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->remotelyKillTxt->setText(text.toUpper()); });
    connect(ui->remotelyStunTxt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->remotelyStunTxt->setText(text.toUpper()); });
    connect(ui->m1Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m1Txt->setText(text.toUpper()); });
    connect(ui->m2Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m2Txt->setText(text.toUpper()); });
    connect(ui->m3Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m3Txt->setText(text.toUpper()); });
    connect(ui->m4Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m4Txt->setText(text.toUpper()); });
    connect(ui->m5Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m5Txt->setText(text.toUpper()); });
    connect(ui->m6Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m6Txt->setText(text.toUpper()); });
    connect(ui->m7Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m7Txt->setText(text.toUpper()); });
    connect(ui->m8Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m8Txt->setText(text.toUpper()); });
    connect(ui->m9Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m9Txt->setText(text.toUpper()); });
    connect(ui->m10Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m10Txt->setText(text.toUpper()); });
    connect(ui->m11Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m11Txt->setText(text.toUpper()); });
    connect(ui->m12Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m12Txt->setText(text.toUpper()); });
    connect(ui->m13Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m13Txt->setText(text.toUpper()); });
    connect(ui->m14Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m14Txt->setText(text.toUpper()); });
    connect(ui->m15Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m15Txt->setText(text.toUpper()); });
    connect(ui->m16Txt, &QLineEdit::textEdited, this, [this](const QString &text){ ui->m16Txt->setText(text.toUpper()); });

    ui->selfIdTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]+$"),  ui->selfIdTxt));
    ui->pttIdBotTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->pttIdBotTxt));
    ui->pttIdEotTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->pttIdEotTxt));
    ui->remotelyKillTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9AabcdBCD*#]+$"),  ui->remotelyKillTxt));
    ui->remotelyStunTxt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->remotelyStunTxt));
    ui->m1Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m1Txt));
    ui->m2Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m2Txt));
    ui->m3Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m3Txt));
    ui->m4Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m4Txt));
    ui->m5Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m5Txt));
    ui->m6Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m6Txt));
    ui->m7Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m7Txt));
    ui->m8Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m8Txt));
    ui->m9Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m9Txt));
    ui->m10Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m10Txt));
    ui->m11Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m11Txt));
    ui->m12Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m12Txt));
    ui->m13Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m13Txt));
    ui->m14Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m14Txt));
    ui->m15Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m15Txt));
    ui->m16Txt->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9abcdABCD*#]+$"),  ui->m16Txt));

    setupUI();
    loadData();
    
}
DtmfSettingsDialog::~DtmfSettingsDialog(){}
void DtmfSettingsDialog::setupUI(){
    ui->txTimeCmbx->addItems(Constants::DTMF_TX_TIME);
    ui->intervalCharCmbx->addItems(Constants::TONE_INTERVAL_CHARACTER);
    ui->groupCodeCmbx->addItems(QStringList{"Off"} + Constants::TONE_INTERVAL_CHARACTER);
    ui->decodingResponseCmbx->addItems(Constants::DECODING_RESPONSE);

    for(int i=0; i < 251; i++){
        ui->firstDigitTimeCmbx->addItem(QString::number(i*10));
        ui->autoResetTimeCmbx->addItem(QString::number(i));
        if(i>0) ui->pretimeCmbx->addItem(QString::number(i*10));
        if(i>0) ui->timeLapseCmbx->addItem(QString::number(i*10));
    }
    
    ui->pttIdPauseCmbx->addItems(QStringList{"Off", "5", "6", "7", "8", "9", "10"});
    ui->dCodePauseCmbx->addItem("Off");
    for(int i=0; i<16; i++){
        ui->dCodePauseCmbx->addItem(QString::number(i+1) + "Second");
    }
}
void DtmfSettingsDialog::loadData(){
    dtmf = Anytone::Memory::dtmf_settings;
    ui->txTimeCmbx->setCurrentIndex(dtmf->tx_time);
    ui->selfIdTxt->setText(dtmf->self_id);
    ui->intervalCharCmbx->setCurrentIndex(dtmf->interval_char - 0xa);
    if(dtmf->group_code == 0xff){
        ui->groupCodeCmbx->setCurrentIndex(0);
    }else{
        ui->groupCodeCmbx->setCurrentIndex(dtmf->group_code-0x9);
    }
    ui->decodingResponseCmbx->setCurrentIndex(dtmf->decoding_response);
    ui->firstDigitTimeCmbx->setCurrentIndex(dtmf->first_digit_time);
    ui->pretimeCmbx->setCurrentIndex(dtmf->pretime-1);
    ui->autoResetTimeCmbx->setCurrentIndex(dtmf->auto_reset_time);
    ui->timeLapseCmbx->setCurrentIndex(dtmf->decode_time_lapse-1);
    if(dtmf->ptt_id_pause_time == 0){
        ui->pttIdPauseCmbx->setCurrentIndex(0);
    }else{
        ui->pttIdPauseCmbx->setCurrentIndex(dtmf->ptt_id_pause_time - 4);
    }
    ui->dCodePauseCmbx->setCurrentIndex(dtmf->d_code_pause);
    ui->sideToneChbx->setChecked(dtmf->side_tone);
    ui->pttIdChbx->setChecked(dtmf->ptt_id);

    ui->pttIdBotTxt->setText(dtmf->ptt_id_bot);
    ui->pttIdEotTxt->setText(dtmf->ptt_id_eot);
    ui->remotelyKillTxt->setText(dtmf->remote_kill);
    ui->remotelyStunTxt->setText(dtmf->remote_stun);

    ui->m1Txt->setText(dtmf->m1);
    ui->m2Txt->setText(dtmf->m2);
    ui->m3Txt->setText(dtmf->m3);
    ui->m4Txt->setText(dtmf->m4);
    ui->m5Txt->setText(dtmf->m5);
    ui->m6Txt->setText(dtmf->m6);
    ui->m7Txt->setText(dtmf->m7);
    ui->m8Txt->setText(dtmf->m8);
    ui->m9Txt->setText(dtmf->m9);
    ui->m10Txt->setText(dtmf->m10);
    ui->m11Txt->setText(dtmf->m11);
    ui->m12Txt->setText(dtmf->m12);
    ui->m13Txt->setText(dtmf->m13);
    ui->m14Txt->setText(dtmf->m14);
    ui->m15Txt->setText(dtmf->m15);
    ui->m16Txt->setText(dtmf->m16);
}
void DtmfSettingsDialog::save(){
    dtmf->tx_time = ui->txTimeCmbx->currentIndex();
    dtmf->self_id = ui->selfIdTxt->text();
    dtmf->interval_char = ui->intervalCharCmbx->currentIndex() + 0xa;
    if(ui->groupCodeCmbx->currentIndex() == 0){
        dtmf->group_code = 0xff;
    }else{
        dtmf->group_code = ui->groupCodeCmbx->currentIndex() + 0xa;
    }


    dtmf->decoding_response = ui->decodingResponseCmbx->currentIndex();
    dtmf->first_digit_time = ui->firstDigitTimeCmbx->currentIndex();
    dtmf->pretime = ui->pretimeCmbx->currentIndex();
    dtmf->auto_reset_time = ui->autoResetTimeCmbx->currentIndex();
    dtmf->decode_time_lapse = ui->timeLapseCmbx->currentIndex();
    if(ui->pttIdPauseCmbx->currentIndex() == 0){
        dtmf->ptt_id_pause_time = 0;
    }else{
        dtmf->ptt_id_pause_time = ui->pttIdPauseCmbx->currentIndex() + 4;
    }
    dtmf->d_code_pause = ui->dCodePauseCmbx->currentIndex();
    dtmf->side_tone = ui->sideToneChbx->isChecked();
    dtmf->ptt_id = ui->pttIdChbx->isChecked();

    dtmf->m1 = ui->m1Txt->text();
    dtmf->m2 = ui->m2Txt->text();
    dtmf->m3 = ui->m3Txt->text();
    dtmf->m4 = ui->m4Txt->text();
    dtmf->m5 = ui->m5Txt->text();
    dtmf->m6 = ui->m6Txt->text();
    dtmf->m7 = ui->m7Txt->text();
    dtmf->m8 = ui->m8Txt->text();
    dtmf->m9 = ui->m9Txt->text();
    dtmf->m10 = ui->m10Txt->text();
    dtmf->m11 = ui->m11Txt->text();
    dtmf->m12 = ui->m12Txt->text();
    dtmf->m13 = ui->m13Txt->text();
    dtmf->m14 = ui->m14Txt->text();
    dtmf->m15 = ui->m15Txt->text();
    dtmf->m16 = ui->m16Txt->text();
}
bool DtmfSettingsDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::FocusIn) {
        last_selected_linedit = static_cast<QLineEdit*>(obj);
    }
    return QWidget::eventFilter(obj, event);
}
void DtmfSettingsDialog::showSpecialCallDialog(){
    if(last_selected_linedit == nullptr) return;
    DtmfSpecialCallDialog dialog(this);
    dialog.exec();
}