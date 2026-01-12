#include "optional_settings_dialog.h"
#include <QAudioFormat>
#include <QAudioSink>
#include <QBuffer>
#include <QPainter>
#include <QPainterPath>
#include "ui_optional_settings_edit_dialog.h"
#include "main_window.h"
#include "zone.h"
#include "roaming_zone.h"
#include "constants.h"

ScreenRender::ScreenRender(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(320, 256);
}

void ScreenRender::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QColor text_color = QColor(255, 255, 255);
    QColor channela_color = QColor(255, 255, 255);
    QColor channelb_color = QColor(255, 255, 255);
    QColor zonea_color = QColor(255, 255, 255);
    QColor zoneb_color = QColor(255, 255, 255);

    switch(channel_name_color_a){
        case 0: // Orange
            channela_color = QColor(255, 140, 0);
            break;
        case 1: // Red
            channela_color = Qt::red;
            break;
        case 2: // Yellow
            channela_color = Qt::yellow;
            break;
        case 3: // Green
            channela_color = Qt::green;
            break;
        case 4: // Turquoise
            channela_color = Qt::cyan;
            break;
        case 5: // Blue
            channela_color = Qt::blue;
            break;
        case 6: // White
            channela_color = Qt::white;
            break;
    }

    switch(channel_name_color_b){
        case 0: // Orange
            channelb_color = QColor(255, 140, 0);
            break;
        case 1: // Red
            channelb_color = Qt::red;
            break;
        case 2: // Yellow
            channelb_color = Qt::yellow;
            break;
        case 3: // Green
            channelb_color = Qt::green;
            break;
        case 4: // Turquoise
            channelb_color = Qt::cyan;
            break;
        case 5: // Blue
            channelb_color = Qt::blue;
            break;
        case 6: // White
            channelb_color = Qt::white;
            break;
    }

    switch(zone_name_color_a){
        case 0: // Orange
            zonea_color = QColor(255, 140, 0);
            break;
        case 1: // Red
            zonea_color = Qt::red;
            break;
        case 2: // Yellow
            zonea_color = Qt::yellow;
            break;
        case 3: // Green
            zonea_color = Qt::green;
            break;
        case 4: // Turquoise
            zonea_color = Qt::cyan;
            break;
        case 5: // Blue
            zonea_color = Qt::blue;
            break;
        case 6: // White
            zonea_color = Qt::white;
            break;
    }

    switch(zone_name_color_b){
        case 0: // Orange
            zoneb_color = QColor(255, 140, 0);
            break;
        case 1: // Red
            zoneb_color = Qt::red;
            break;
        case 2: // Yellow
            zoneb_color = Qt::yellow;
            break;
        case 3: // Green
            zoneb_color = Qt::green;
            break;
        case 4: // Turquoise
            zoneb_color = Qt::cyan;
            break;
        case 5: // Blue
            zoneb_color = Qt::blue;
            break;
        case 6: // White
            zoneb_color = Qt::white;
            break;
    }

    switch(sb_text_color){
        case 0: // White
            text_color = Qt::white;
            break;
        case 1: // Black
            text_color = Qt::black;
            break;
        case 2: // Orange
            text_color = QColor(255, 140, 0);
            break;
        case 3: // Red
            text_color = Qt::red;
            break;
        case 4: // Yellow
            text_color = Qt::yellow;
            break;
        case 5: // Green
            text_color = Qt::green;
            break;
        case 6: // Turquoise
            text_color = Qt::cyan;
            break;
        case 7: // Blue
            text_color = Qt::blue;
            break;
        
    }

    painter.setPen(QPen(Qt::black, 0, Qt::SolidLine));
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawRect(0, 0, 320, 256);
    painter.setPen(QPen(Qt::white, 2, Qt::SolidLine));

    // Antenna
    painter.drawLine(4, 2, 20, 2);
    painter.drawLine(12, 2, 12, 22);
    painter.drawLine(4, 2, 12, 10);
    painter.drawLine(20, 2, 12, 10);
    painter.drawLine(18, 12, 28, 22);
    painter.drawLine(18, 22, 28, 12);

    // Antenna
    painter.drawLine(270, 2, 286, 2);
    painter.drawLine(278, 2, 278, 22);
    painter.drawLine(270, 2, 278, 10);
    painter.drawLine(286, 2, 278, 10);
    painter.drawLine(284, 12, 294, 22);
    painter.drawLine(284, 22, 294, 12);

    // Battery
    painter.setPen(QPen(text_color, 4, Qt::SolidLine));
    painter.drawLine(265, 16, 265, 10);
    painter.setPen(QPen(Qt::black, 0, Qt::NoPen));
    painter.setBrush(QBrush(text_color, Qt::SolidPattern));
    painter.drawRect(230, 2, 34, 22);
    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter.drawRect(234, 4, 26, 18);
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawRect(236, 6, 6, 14);
    painter.drawRect(244, 6, 6, 14);
    painter.drawRect(252, 6, 6, 14);

    if(show_time){
        painter.setBrush(QBrush(Qt::darkGray, Qt::SolidPattern));
        painter.drawRect(0, 30, 320, 22);
    }

    // Bands
    QFont bold_font = painter.font();
    bold_font.setBold(true);
    painter.setFont(bold_font);
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    if(show_channel_type) painter.drawRect(8, 58, 34, 14);
    if(show_ts) painter.drawRect(168, 58, 18, 14);
    painter.drawRect(210, 58, 14, 14);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawRect(12, 76, 14, 14);
    painter.setPen(QPen(text_color, 1, Qt::SolidLine));
    painter.drawText(48, 70, "CH-001");
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    if(show_channel_type) painter.drawText(10, 70, "DMR");
    if(show_ts) painter.drawText(170, 70, "T1");
    painter.drawText(212, 70, "R");
    bold_font.setStretch(150);
    painter.setFont(bold_font);
    painter.drawText(13, 88, "L");
    bold_font.setStretch(100);
    painter.setFont(bold_font);

    painter.setPen(QPen(Qt::black, 0, Qt::NoPen));
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    if(show_channel_type) painter.drawRect(8, 148, 34, 14);
    if(show_ts) painter.drawRect(168, 148, 18, 14);
    painter.drawRect(210, 148, 14, 14);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawRect(12, 166, 14, 14);
    painter.setPen(QPen(text_color, 1, Qt::SolidLine));
    painter.drawText(48, 160, "CH-002");
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
    if(show_channel_type) painter.drawText(10, 160, "DMR");
    if(show_ts) painter.drawText(170, 160, "T1");
    painter.drawText(212, 160, "R");

    bold_font.setStretch(150);
    painter.setFont(bold_font);
    painter.drawText(13, 178, "L");
    bold_font.setStretch(100);
    painter.setFont(bold_font);

    if(show_cc){
        painter.setPen(QPen(text_color, 1, Qt::SolidLine));
        painter.drawText(12, 196, "C10");
    }

    
    bold_font.setPixelSize(25);
    painter.setFont(bold_font);
    painter.setPen(QPen(channela_color, 1, Qt::SolidLine));
    painter.drawText(90, 110, "Channel 1");
    painter.setPen(QPen(zonea_color, 1, Qt::SolidLine));
    painter.drawText(112, 136, "Zone 1");
    bold_font.setPixelSize(20);
    painter.setFont(bold_font);
    painter.setPen(QPen(channelb_color, 1, Qt::SolidLine));
    painter.drawText(100, 190, "Channel 2");
    painter.setPen(QPen(zoneb_color, 1, Qt::SolidLine));
    painter.drawText(120, 212, "Zone 1");
    
    painter.setPen(QPen(text_color, 1, Qt::SolidLine));
    if(date_type == 0 && show_time){
        painter.drawText(4, 48, "YYYY-MM-DD HH:mm");
    }else if(show_time){
        painter.drawText(4, 48, "DD-MM-YYYY HH:mm");
    }

    painter.scale(1.0, .75);
    painter.drawText(2, 332, "Menu");
    painter.drawText(115, 332, "Zone");
    painter.drawText(280, 332, "List");

    QPainterPath path;
    path.moveTo (170, 325);
    path.lineTo (190, 325);
    path.lineTo (180, 315);
    path.lineTo (170, 325);
    painter.setPen (Qt :: NoPen);
    painter.fillPath (path, QBrush (text_color));
    
    path.moveTo (170, 330);
    path.lineTo (190, 330);
    path.lineTo (180, 340);
    path.lineTo (170, 330);
    painter.fillPath (path, QBrush (text_color));
    painter.restore();


    
}

PowerOnCharLineEdit::PowerOnCharLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
}
void PowerOnCharLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        emit backspacePressed(text());
        // Keep default behavior
        QLineEdit::keyPressEvent(event);
    } else {
        QLineEdit::keyPressEvent(event);
    }
}

OptionalSettingsDialog::OptionalSettingsDialog(MainWindow *parent) :
    QDialog(parent),
    ui(std::make_unique<Ui_OptionalSettingsEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->main_window = parent;
    screen_render = new ScreenRender(this);
    ui->horizontalLayout_6->addWidget(screen_render);

    setupUI();

    connect(ui->callEndPlayBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::playCallEndTone);
    connect(ui->callAllPlayBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::playCallAllTone);
    connect(ui->callPermitPlayBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::playCallPermitTone);
    connect(ui->idleChannelPlayBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::playIdleChannelTone);
    connect(ui->callResetPlayBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::playCallResetTone);
    connect(ui->okBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::saveClose);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &OptionalSettingsDialog::close);
    connect(ui->startupZoneACmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::updateStartupChannels);
    connect(ui->startupZoneBCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::updateStartupChannels);
    connect(ui->defaultStartupChannelCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::updateStartupChannels);
    connect(ui->displayModeCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::updateWorkMode);
    connect(ui->pf1ShortCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::keyFunctionChanged);
    connect(ui->pf2ShortCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::keyFunctionChanged);
    connect(ui->pf3ShortCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::keyFunctionChanged);
    connect(ui->p1ShortCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::keyFunctionChanged);
    connect(ui->p2ShortCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::keyFunctionChanged);

    connect(ui->standbyCharColorCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->channelNameColorACmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->channelNameColorBCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->zoneNameColorACmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->zoneNameColorBCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);

    connect(ui->displayColorCodeCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->displayTimeSlotCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->dateDisplayFormatCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->displayChannelTypeCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);
    connect(ui->timeDisplayCmbx, &QComboBox::currentIndexChanged, this, &OptionalSettingsDialog::refreshScreenView);

    
    loadData();
    updateStartupChannels();
    updateWorkMode();
    refreshScreenView();
    
}
void OptionalSettingsDialog::refreshScreenView(){
    screen_render->channel_name_color_a = ui->channelNameColorACmbx->currentIndex();
    screen_render->channel_name_color_b = ui->channelNameColorBCmbx->currentIndex();
    screen_render->zone_name_color_a = ui->zoneNameColorACmbx->currentIndex();
    screen_render->zone_name_color_b = ui->zoneNameColorBCmbx->currentIndex();
    screen_render->sb_text_color = ui->standbyCharColorCmbx->currentIndex();

    screen_render->show_cc = ui->displayColorCodeCmbx->currentIndex();
    screen_render->show_ts = ui->displayTimeSlotCmbx->currentIndex();
    screen_render->date_type = ui->dateDisplayFormatCmbx->currentIndex();
    screen_render->show_channel_type = ui->displayChannelTypeCmbx->currentIndex();
    screen_render->show_time = ui->timeDisplayCmbx->currentIndex();
    screen_render->repaint();
}
OptionalSettingsDialog::~OptionalSettingsDialog(){
    
}
void OptionalSettingsDialog::setupUI(){
    ui->keyFunctionImage->setStyleSheet("background-image: url(:/icons/d878_key_diagram.jpg);background-repeat: no-repeat;");

    zone_names.clear();
    for(Anytone::Zone *zone : Anytone::Memory::zones){
        zone_names.push_back(zone->name);
    }

    for(int i=0; i < 14; i++){
        PowerOnCharLineEdit *pocEdit = new PowerOnCharLineEdit(ui->widget_3);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pocEdit->sizePolicy().hasHeightForWidth());
        pocEdit->setSizePolicy(sizePolicy);
        pocEdit->setMaximumSize(QSize(20, 16777215));
        pocEdit->setBaseSize(QSize(0, 0));
        pocEdit->setMaxLength(1);
        pocEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ui->horizontalLayout_3->addWidget(pocEdit);
        display_char_line1_txt_list.push_back(pocEdit);
        connect(pocEdit, &PowerOnCharLineEdit::textEdited,
            this, [this, pocEdit](const QString &) {
                powerOnCharUpdate(pocEdit);
            });
        connect(pocEdit, &PowerOnCharLineEdit::backspacePressed,
            this, [this, pocEdit](const QString &) {
                powerOnCharKeyPress(pocEdit);
            });
    }

    for(int i=0; i < 14; i++){
        PowerOnCharLineEdit *pocEdit = new PowerOnCharLineEdit(ui->widget_4);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pocEdit->sizePolicy().hasHeightForWidth());
        pocEdit->setSizePolicy(sizePolicy);
        pocEdit->setMaximumSize(QSize(20, 16777215));
        pocEdit->setBaseSize(QSize(0, 0));
        pocEdit->setMaxLength(1);
        pocEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ui->horizontalLayout_4->addWidget(pocEdit);
        display_char_line2_txt_list.push_back(pocEdit);
        connect(pocEdit, &PowerOnCharLineEdit::textEdited,
            this, [this, pocEdit](const QString &) {
                powerOnCharUpdate(pocEdit);
            });
        connect(pocEdit, &PowerOnCharLineEdit::backspacePressed,
            this, [this, pocEdit](const QString &) {
                powerOnCharKeyPress(pocEdit);
            });
    }

    // Power On
    ui->poweronInterfaceCmbx->addItems(Constants::POWERON_INTERFACE);
    ui->poweronPasswordCmbx->addItems(Constants::OFF_ON);
    ui->defaultStartupChannelCmbx->addItems(Constants::OFF_ON);
    for(Anytone::Zone *zone : Anytone::Memory::zones){
        if(zone->channels.size() > 0){
            ui->startupZoneACmbx->addItem(zone->name);
            ui->startupZoneBCmbx->addItem(zone->name);
        }
    }
    ui->startupGpsTestCmbx->addItems(Constants::OFF_ON);
    ui->startupResetCmbx->addItems(Constants::OFF_ON);

    // Power Save
    ui->autoShutdownCmbx->addItems(Constants::AUTOSHUTDOWN);
    ui->powerSaveCmbx->addItems(Constants::POWER_SAVE);
    ui->autoShutdownTypeCmbx->addItems(Constants::AUTOSHUTDOWN_TYPE);

    // Display
    ui->brightnessCmbx->addItems(Constants::BRIGHTNESS);
    ui->autoBacklightDurationCmbx->addItems(Constants::AUTO_BACKLIGHT_DURATION);
    ui->backlightDelayTxCmbx->addItems(Constants::BACKLIGHT_DELAY_TX);
    ui->menuExitTimeCmbx->addItems(Constants::MENU_EXIT_TIME);
    ui->timeDisplayCmbx->addItems(Constants::OFF_ON);
    ui->lastCallerCmbx->addItems(Constants::LAST_CALLER);
    ui->callDisplayModeCmbx->addItems(Constants::CALL_DISPLAY_MODE);
    ui->callsignDisplayColorCmbx->addItems(Constants::COLOR1);
    ui->callEndPromptCmbx->addItems(Constants::OFF_ON);
    ui->displayChannelNumberCmbx->addItems(Constants::DISPLAY_CHANNEL_NUMBER);
    ui->displayCurrentContactCmbx->addItems(Constants::OFF_ON);
    ui->standbyCharColorCmbx->addItems(Constants::COLOR2);
    ui->standbyBkPictureCmbx->addItems(Constants::DISPLAY_STANDBY_PICTURE);
    ui->showLastCallOnLaunchCmbx->addItems(Constants::OFF_ON);
    ui->separateDisplayCmbx->addItems(Constants::OFF_ON);
    ui->keepsLastCallerCmbx->addItems(Constants::OFF_ON);
    ui->backlightDelayRxCmbx->addItems(Constants::BACKLIGHT_DELAY_RX);
    ui->channelNameColorACmbx->addItems(Constants::COLOR1);
    ui->channelNameColorBCmbx->addItems(Constants::COLOR1);
    ui->zoneNameColorACmbx->addItems(Constants::COLOR1);
    ui->zoneNameColorBCmbx->addItems(Constants::COLOR1);
    ui->displayChannelTypeCmbx->addItems(Constants::OFF_ON);
    ui->displayTimeSlotCmbx->addItems(Constants::OFF_ON);
    ui->displayColorCodeCmbx->addItems(Constants::OFF_ON);
    ui->dateDisplayFormatCmbx->addItems(Constants::DATE_DISPLAY_FORMAT);
    ui->volumeBarCmbx->addItems(Constants::OFF_ON);
    
    // Work Mode
    ui->displayModeCmbx->addItems(Constants::DISPLAY_MODE);
    ui->vfMrACmbx->addItems(Constants::VF_MR);
    ui->vfMrBCmbx->addItems(Constants::VF_MR);
    ui->memZoneACmbx->addItems(zone_names);
    ui->memZoneBCmbx->addItems(zone_names);
    ui->mainChannelSetCmbx->addItems(Constants::MAIN_CHANNEL_SET);
    ui->subChannelModeCmbx->addItems(Constants::OFF_ON);
    ui->workingModeCmbx->addItems(Constants::WORKING_MODE);

    // VOX/BT
    ui->voxLevelCmbx->addItems(Constants::VOX_LEVEL);
    ui->voxDelayCmbx->addItems(Constants::VOX_DELAY);
    ui->voxDetectionCmbx->addItems(Constants::VOX_DETECTION);
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        ui->btOnOffCmbx->addItems(Constants::OFF_ON);
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        ui->btOnOffCmbx->addItems(QStringList{"Off", "On", "KISS TNC"});
    }
    ui->btIntMicCmbx->addItems(Constants::OFF_ON);
    ui->btIntSpkCmbx->addItems(Constants::OFF_ON);
    ui->btMicGainCmbx->addItems(Constants::BT_GAIN);
    ui->btSpkGainCmbx->addItems(Constants::BT_GAIN);
    ui->btHoldTimeCmbx->addItems(Constants::BT_HOLD_TIME);
    ui->btRxDelayCmbx->addItems(Constants::BT_RX_DELAY);
    ui->btPttHoldCmbx->addItems(Constants::OFF_ON);
    ui->pttSleepTimeCmbx->addItems(Constants::BT_PTT_SLEEP);

    // STE
    ui->steCtcssTypeCmbx->addItems(Constants::STE_CTCSS_TYPE);
    ui->steNoSignalCmbx->addItems(Constants::STE_NO_SIGNAL);
    ui->steTimeCmbx->addItems(Constants::STE_TIME);

    // FM
    ui->fmVfMrCmbx->addItems(Constants::VF_MR);
    for(Anytone::FM *fm : Anytone::Memory::fm_channels){
        if(fm->frequency > 0) ui->fmWorkChannelCmbx->addItem(QString::number(fm->id + 1), QVariant::fromValue(fm));
    }
    ui->fmMonitorCmbx->addItems(Constants::OFF_ON);

    // Key Function
    ui->keyLockCmbx->addItems(Constants::KEY_LOCK);
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        ui->pf1ShortCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->pf2ShortCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->pf3ShortCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->p1ShortCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->p2ShortCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->pf1LongCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->pf2LongCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->pf3LongCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->p1LongCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
        ui->p2LongCmbx->addItems(Constants::KEY_FUNCTION_D878UVII);
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
        ui->pf1ShortCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->pf2ShortCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->pf3ShortCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->p1ShortCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->p2ShortCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->pf1LongCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->pf2LongCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->pf3LongCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->p1LongCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
        ui->p2LongCmbx->addItems(Constants::KEY_FUNCTION_D890UV);
    }

    ui->longKeyTimeCmbx->addItems(Constants::LONG_KEY_TIME);
    ui->knobLockCmbx->addItems(Constants::OFF_ON);
    ui->keyboardLockCmbx->addItems(Constants::OFF_ON);
    ui->sideKeyLockCmbx->addItems(Constants::OFF_ON);
    ui->forcedKeyLockCmbx->addItems(Constants::OFF_ON);

    // Other
    ui->addressSentWithOwnCodeCmbx->addItems(Constants::OFF_ON);
    ui->totCmbx->addItems(Constants::TOT);
    ui->languageCmbx->addItems(Constants::LANGUAGE);
    ui->frequencyStepCmbx->addItems(Constants::FREQUENCY_STEP);
    ui->sqlLevelACmbx->addItems(Constants::SQL_LEVEL);
    ui->sqlLevelBCmbx->addItems(Constants::SQL_LEVEL);
    ui->tbstCmbx->addItems(Constants::TBST);
    ui->analogCallHoldTimeCmbx->addItems(Constants::ANALOG_CALL_HOLD_TIME);
    ui->callChannelMaintainedCmbx->addItems(Constants::OFF_ON);
    ui->priorityZoneACmbx->addItems(zone_names);
    ui->priorityZoneBCmbx->addItems(zone_names);
    ui->muteTimingCmbx->addItems(Constants::MUTE_TIMING);
    ui->encryptionTypeCmbx->addItems(Constants::ENCRYPTION_TYPE);
    ui->totPredictCmbx->addItems(Constants::OFF_ON);
    ui->txPowerAgcCmbx->addItems(Constants::OFF_ON);

    // Digital Function
    ui->groupCallHoldTimeCmbx->addItems(Constants::TG_HOLD_TIME);
    ui->privateCallHoldTimeCmbx->addItems(Constants::TG_HOLD_TIME);
    ui->manualDialGroupCallHoldTimeCmbx->addItems(Constants::TG_HOLD_TIME);
    ui->manualDialPrivateCallHoldTimeCmbx->addItems(Constants::TG_HOLD_TIME);
    ui->voiceHeaderRepetitionsCmbx->addItems(Constants::VOICE_HEADER_REPETITIONS);
    ui->txPreambleDurationCmbx->addItems(Constants::TX_PREAMBLE_DURATION);
    ui->filterOwnCallInMissedCallsCmbx->addItems(Constants::OFF_ON);
    ui->digitalRemoteKillCmbx->addItems(Constants::OFF_ON);
    ui->digitalMonitorCmbx->addItems(Constants::DIGITAL_MONITOR);
    ui->digitalMonitorCcCmbx->addItems(Constants::DIGITAL_MONITOR_CC);
    ui->digitalMonitorIdCmbx->addItems(Constants::DIGITAL_MONITOR_CC);
    ui->monitorHoldSlotCmbx->addItems(Constants::OFF_ON);
    ui->remoteMonitorCmbx->addItems(Constants::OFF_ON);
    ui->smsFormatCmbx->addItems(Constants::SMS_FORMAT);

    // Alert Tone
    ui->smsAlertCmbx->addItems(Constants::ALERT);
    ui->callAlertCmbx->addItems(Constants::ALERT);
    ui->digiCallResetToneCmbx->addItems(Constants::OFF_ON);
    ui->talkPermitCmbx->addItems(Constants::TALK_PERMIT);
    ui->keyToneCmbx->addItems(Constants::OFF_ON);
    ui->digiIdleChannelToneCmbx->addItems(Constants::DIGITAL_IDLE_TONE);
    ui->startupSoundCmbx->addItems(Constants::OFF_ON);
    ui->toneKeySoundAdjustableCmbx->addItems(Constants::KEY_TONE_SOUND_ADJUSTABLE);
    ui->analogIdleChannelToneCmbx->addItems(Constants::OFF_ON);
    ui->pluginRecordingToneCmbx->addItems(Constants::OFF_ON);

    // GPS
    ui->gpsCmbx->addItems(Constants::OFF_ON);
    ui->gpsPositioningCmbx->addItems(Constants::OFF_ON);
    ui->timeZoneCmbx->addItems(Constants::TIME_ZONE);
    ui->rangingIntervalCmbx->addItems(Constants::RANGING_INTERVAL);
    ui->distanceUnitCmbx->addItems(Constants::DISTANCE_UNIT);
    ui->gpsInformationUpdateCmbx->addItems(Constants::OFF_ON);
    ui->gpsModeCmbx->addItems(Constants::GPS_MODE);
    ui->gpsRoamingCmbx->addItems(Constants::OFF_ON);

    // VFO Scan
    ui->vfoScanTypeCmbx->addItems(Constants::VFO_SCAN_TYPE);

    // Auto Repeater
    ui->autoRepeaterACmbx->addItems(Constants::AUTO_REPEATER_ENABLED);
    ui->autoRepeaterBCmbx->addItems(Constants::AUTO_REPEATER_ENABLED);
    ui->autoRepeater1UhfCmbx->addItem("Off");
    ui->autoRepeater1VhfCmbx->addItem("Off");
    ui->autoRepeater2UhfCmbx->addItem("Off");
    ui->autoRepeater2VhfCmbx->addItem("Off");
    ui->repeaterCheckCmbx->addItems(Constants::OFF_ON);
    ui->repeaterCheckIntervalsCmbx->addItems(Constants::AUTO_REPEATER_INTERVALS);
    ui->repeaterCheckReconnectionsCmbx->addItems(QStringList{"3", "4", "5"});
    ui->repeaterOutOfRangeNotifyCmbx->addItems(Constants::REPEATER_OUT_OF_RANGE_NOTIFY);
    for(int i=0; i<10; i++){ ui->outOfRangeNotifyCmbx->addItem(QString::number(i+1)); }
    ui->autoRoamingCmbx->addItems(Constants::OFF_ON);
    ui->autoRoamingStartConditionCmbx->addItems(Constants::AUTO_ROAMING_START_CONDITION);
    for(int i=0; i<8; i++){ ui->autoRoamingFixedTimeCmbx->addItem(QString::number(i+1)); }
    ui->roamingEffectWaitTimeCmbx->addItems(Constants::ROAMING_EFFECT_WAIT_TIME);
    
    for(Anytone::RoamingZone *rz : Anytone::Memory::roaming_zones){
        ui->roamingZoneCmbx->addItem(rz->name, QVariant::fromValue(rz));
    }

    // Record
    ui->recordFunctionCmbx->addItems(Constants::OFF_ON);

    // Volume/Audio
    ui->maxVolumeCmbx->addItems(Constants::MAX_VOLUME);
    ui->maxHeadphoneVolumeCmbx->addItems(Constants::MAX_VOLUME);
    ui->digiMicGainCmbx->addItems(Constants::MIC_GAIN);
    ui->enhancedSoundQualityCmbx->addItems(Constants::OFF_ON);
    ui->analogMicGainCmbx->addItems(Constants::MIC_GAIN);

    // 890UV
    ui->amFmFunctionCmbx->addItems(Constants::OFF_ON);
    ui->amVfoMemCmbx->addItems(Constants::VF_MR);
    // for(Anytone::AM *am : Anytone::Memory::am_channels){
    //     if(am->frequency > 0) ui->amWorkZoneCmbx->addItem(am->name, QVariant::fromValue(am));
    // }
    ui->amOffsetCmbx->addItems(QStringList{"Positive", "Negative"});
    ui->amSqlLevelCmbx->addItems(QStringList{"Off", "1", "2", "3", "4", "5"});
    ui->btNrBeforeCmbx->addItems(QStringList{"Off", "1", "2", "3", "4", "5"});
    ui->btNrAfterCmbx->addItems(QStringList{"Off", "1", "2", "3", "4", "5"});
    ui->repeaterModeCmbx->addItems(Constants::OFF_ON);
    ui->repCcLimitCmbx->addItems(QStringList{"Off", "Match Channel A Color Code", "Match Channel B Color Code"});
    ui->repSlotACmbx->addItems(QStringList{"Off", "Channel A Fixed Time Slot 1", "Channel A Fixed Time Slot 2"});
    ui->repSlotBCmbx->addItems(QStringList{"Off", "Channel B Fixed Time Slot 1", "Channel B Fixed Time Slot 2"});
    for(double i = 0; i < 51; i+=2){
        ui->recordDelayCmbx->addItem(QString::number(i/10, 'f', 1) + "s");
    }
    ui->satLocationCmbx->addItems(QStringList{"Off", "Fixed-1", "Fixed-2", "Fixed-3", "Fixed-4", "Fixed-5", "Fixed-6", "Fixed-7", "Fixed-8"});
    ui->satTxPowerCmbx->addItems(Constants::TX_POWER);
    ui->satAnaSqlCmbx->addItems(QStringList{"0", "1", "2", "3", "4", "5"});
    for(double i = 0; i < 31; i++){
        ui->satAosLimitCmbx->addItem(QString::number(i));
    }
    ui->noaaMoniCmbx->addItems(Constants::OFF_ON);
    ui->noaaScanCmbx->addItems(Constants::OFF_ON);
    ui->noaaCmbx->addItems(Constants::OFF_ON);
    for(double i = 0; i < 10; i++){
        ui->noaaChannelCmbx->addItem(QString::number(i+1));
    }

    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        ui->amFmFunctionCmbx->setEnabled(false);
        ui->amGroupBox->setEnabled(false);
        ui->btNrBeforeCmbx->setEnabled(false);
        ui->btNrAfterCmbx->setEnabled(false);
        ui->repeaterModeCmbx->setEnabled(false);
        ui->repCcLimitCmbx->setEnabled(false);
        ui->repSlotACmbx->setEnabled(false);
        ui->repSlotBCmbx->setEnabled(false);
        ui->recordDelayCmbx->setEnabled(false);
        ui->satLocationCmbx->setEnabled(false);
        ui->satTxPowerCmbx->setEnabled(false);
        ui->satAnaSqlCmbx->setEnabled(false);
        ui->satAosLimitCmbx->setEnabled(false);
        ui->noaaMoniCmbx->setEnabled(false);
        ui->noaaScanCmbx->setEnabled(false);
        ui->noaaCmbx->setEnabled(false);
        ui->noaaChannelCmbx->setEnabled(false);
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){

    }
}
void OptionalSettingsDialog::loadData(){
    // Power-On
    ui->poweronInterfaceCmbx->setCurrentIndex(Anytone::Memory::optional_settings->poweron_interface);

    for(int i = 0; i < Anytone::Memory::optional_settings->poweron_display_1.size(); i++){
        char c = Anytone::Memory::optional_settings->poweron_display_1.at(i);
        if(c!=0) display_char_line1_txt_list.at(i)->setText(QString(c));
    }
    for(int i = 0; i < Anytone::Memory::optional_settings->poweron_display_2.size(); i++){
        char c = Anytone::Memory::optional_settings->poweron_display_2.at(i);
        if(c!=0) display_char_line2_txt_list.at(i)->setText(QString(c));
    }

    ui->poweronPasswordCmbx->setCurrentIndex(Anytone::Memory::optional_settings->poweron_password);
    ui->poweronPasswordTxt->setText(Anytone::Memory::optional_settings->poweron_password_char);
    ui->defaultStartupChannelCmbx->setCurrentIndex(Anytone::Memory::optional_settings->default_startup_channel);
    ui->startupZoneACmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_zone_a);
    ui->startupZoneBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_zone_b);
    ui->startupChannelACmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_channel_a);
    ui->startupChannelBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_channel_b);
    ui->startupGpsTestCmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_gps_test);
    ui->startupResetCmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_reset);

    // Power Save
    ui->autoShutdownCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_shutdown);
    ui->powerSaveCmbx->setCurrentIndex(Anytone::Memory::optional_settings->power_save);
    ui->autoShutdownTypeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_shutdown_type);

    // Display
    ui->brightnessCmbx->setCurrentIndex(Anytone::Memory::optional_settings->brightness);
    ui->autoBacklightDurationCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_backlight_duration);
    ui->backlightDelayTxCmbx->setCurrentIndex(Anytone::Memory::optional_settings->backlight_tx_delay);
    ui->menuExitTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->menu_exit_time);
    ui->timeDisplayCmbx->setCurrentIndex(Anytone::Memory::optional_settings->time_display);
    ui->lastCallerCmbx->setCurrentIndex(Anytone::Memory::optional_settings->last_caller);
    ui->callDisplayModeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->call_display_mode);
    ui->callsignDisplayColorCmbx->setCurrentIndex(Anytone::Memory::optional_settings->callsign_display_color);
    ui->callEndPromptCmbx->setCurrentIndex(Anytone::Memory::optional_settings->call_end_prompt_box);
    ui->displayChannelNumberCmbx->setCurrentIndex(Anytone::Memory::optional_settings->display_channel_number);
    ui->displayCurrentContactCmbx->setCurrentIndex(Anytone::Memory::optional_settings->display_current_contact);
    ui->standbyCharColorCmbx->setCurrentIndex(Anytone::Memory::optional_settings->standby_char_color);
    ui->standbyBkPictureCmbx->setCurrentIndex(Anytone::Memory::optional_settings->standby_bk_picture);
    ui->showLastCallOnLaunchCmbx->setCurrentIndex(Anytone::Memory::optional_settings->show_last_call_on_launch);
    ui->separateDisplayCmbx->setCurrentIndex(Anytone::Memory::optional_settings->separate_display);
    ui->keepsLastCallerCmbx->setCurrentIndex(Anytone::Memory::optional_settings->ch_switching_keeps_caller);
    ui->backlightDelayRxCmbx->setCurrentIndex(Anytone::Memory::optional_settings->backlight_rx_delay);
    ui->channelNameColorACmbx->setCurrentIndex(Anytone::Memory::optional_settings->channel_name_color_a);
    ui->channelNameColorBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->channel_name_color_b);
    ui->zoneNameColorACmbx->setCurrentIndex(Anytone::Memory::optional_settings->zone_name_color_a);
    ui->zoneNameColorBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->zone_name_color_b);
    ui->displayChannelTypeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->display_channel_type);
    ui->displayTimeSlotCmbx->setCurrentIndex(Anytone::Memory::optional_settings->display_time_slot);
    ui->displayColorCodeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->display_color_code);
    ui->dateDisplayFormatCmbx->setCurrentIndex(Anytone::Memory::optional_settings->date_display_format);
    ui->volumeBarCmbx->setCurrentIndex(Anytone::Memory::optional_settings->volume_bar);

    // Work Mode
    ui->displayModeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->display_mode);
    ui->vfMrACmbx->setCurrentIndex(Anytone::Memory::optional_settings->vf_mr_a);
    ui->vfMrBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->vf_mr_b);
    ui->memZoneACmbx->setCurrentIndex(Anytone::Memory::optional_settings->mem_zone_a);
    ui->memZoneBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->mem_zone_b);
    ui->mainChannelSetCmbx->setCurrentIndex(Anytone::Memory::optional_settings->main_channel_set);
    ui->subChannelModeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sub_channel_mode);
    ui->workingModeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->working_mode);

    // Vox/BT
    ui->voxLevelCmbx->setCurrentIndex(Anytone::Memory::optional_settings->vox_level);
    ui->voxDelayCmbx->setCurrentIndex(Anytone::Memory::optional_settings->vox_delay);
    ui->voxDetectionCmbx->setCurrentIndex(Anytone::Memory::optional_settings->vox_detection);
    ui->btIntMicCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_int_mic);
    ui->btIntSpkCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_int_spk);
    ui->btMicGainCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_mic_gain);
    ui->btSpkGainCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_spk_gain);
    ui->btHoldTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_hold_time);
    ui->btRxDelayCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_rx_delay);
    ui->btPttHoldCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_ptt_hold);
    ui->pttSleepTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_ptt_sleep_time);

    // STE
    ui->steCtcssTypeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->ste_type_of_ctcss);
    ui->steNoSignalCmbx->setCurrentIndex(Anytone::Memory::optional_settings->ste_when_no_signal);
    ui->steTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->ste_time - 1);

    // FM
    ui->fmVfMrCmbx->setCurrentIndex(Anytone::Memory::optional_settings->fm_vfo_mem);
    ui->fmWorkChannelCmbx->setCurrentIndex(Anytone::Memory::optional_settings->fm_work_channel);
    ui->fmMonitorCmbx->setCurrentIndex(Anytone::Memory::optional_settings->fm_monitor);

    // Key Function
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        ui->btOnOffCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_on_off_D878UVII);
        ui->keyLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->key_lock);
        ui->pf1ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf1_short_key_D878UVII);
        ui->pf2ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf2_short_key_D878UVII);
        ui->pf3ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf3_short_key_D878UVII);
        ui->p1ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p1_short_key_D878UVII);
        ui->p2ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p2_short_key_D878UVII);
        ui->pf1LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf1_long_key_D878UVII);
        ui->pf2LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf2_long_key_D878UVII);
        ui->pf3LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf3_long_key_D878UVII);
        ui->p1LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p1_long_key_D878UVII);
        ui->p2LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p2_long_key_D878UVII);
        ui->longKeyTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->long_key_time);
        ui->knobLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->knob_lock);
        ui->keyboardLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->keyboard_lock);
        ui->sideKeyLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->side_key_lock);
        ui->forcedKeyLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->forced_key_lock);
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
        ui->btOnOffCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_on_off_D890UV);
        ui->keyLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->key_lock);
        ui->pf1ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf1_short_key_D890UV);
        ui->pf2ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf2_short_key_D890UV);
        ui->pf3ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf3_short_key_D890UV);
        ui->p1ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p1_short_key_D890UV);
        ui->p2ShortCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p2_short_key_D890UV);
        ui->pf1LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf1_long_key_D890UV);
        ui->pf2LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf2_long_key_D890UV);
        ui->pf3LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->pf3_long_key_D890UV);
        ui->p1LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p1_long_key_D890UV);
        ui->p2LongCmbx->setCurrentIndex(Anytone::Memory::optional_settings->p2_long_key_D890UV);
        ui->longKeyTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->long_key_time);
        ui->knobLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->knob_lock);
        ui->keyboardLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->keyboard_lock);
        ui->sideKeyLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->side_key_lock);
        ui->forcedKeyLockCmbx->setCurrentIndex(Anytone::Memory::optional_settings->forced_key_lock);
    }

    // Other
    ui->addressSentWithOwnCodeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->address_book_sent_with_code);
    ui->totCmbx->setCurrentIndex(Anytone::Memory::optional_settings->tot);
    ui->languageCmbx->setCurrentIndex(Anytone::Memory::optional_settings->language);
    ui->frequencyStepCmbx->setCurrentIndex(Anytone::Memory::optional_settings->frequency_step);
    ui->sqlLevelACmbx->setCurrentIndex(Anytone::Memory::optional_settings->sql_level_a);
    ui->sqlLevelBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sql_level_b);
    ui->tbstCmbx->setCurrentIndex(Anytone::Memory::optional_settings->tbst);
    ui->analogCallHoldTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->analog_call_hold_time);
    ui->callChannelMaintainedCmbx->setCurrentIndex(Anytone::Memory::optional_settings->call_channel_maintained);
    ui->priorityZoneACmbx->setCurrentIndex(Anytone::Memory::optional_settings->priority_zone_a);
    ui->priorityZoneBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->priority_zone_b);
    ui->muteTimingCmbx->setCurrentIndex(Anytone::Memory::optional_settings->mute_timing);
    ui->encryptionTypeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->encryption_type);
    ui->totPredictCmbx->setCurrentIndex(Anytone::Memory::optional_settings->tot_predict);
    ui->txPowerAgcCmbx->setCurrentIndex(Anytone::Memory::optional_settings->tx_power_agc);

    // Digital Func
    ui->groupCallHoldTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->group_call_hold_time - 1);
    ui->privateCallHoldTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->private_call_hold_time - 1);
    ui->manualDialGroupCallHoldTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->manual_dial_group_call_hold_time - 1);
    ui->manualDialPrivateCallHoldTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->manual_dial_private_call_hold_time - 1);
    ui->voiceHeaderRepetitionsCmbx->setCurrentIndex(Anytone::Memory::optional_settings->voice_header_repetitions - 2);
    ui->txPreambleDurationCmbx->setCurrentIndex(Anytone::Memory::optional_settings->tx_preamble_duration);
    ui->filterOwnCallInMissedCallsCmbx->setCurrentIndex(Anytone::Memory::optional_settings->filter_own_id);
    ui->digitalRemoteKillCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digital_remote_kill);
    ui->digitalMonitorCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digital_monitor);
    ui->digitalMonitorCcCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digital_monitor_cc);
    ui->digitalMonitorIdCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digital_monitor_id);
    ui->monitorHoldSlotCmbx->setCurrentIndex(Anytone::Memory::optional_settings->monitor_slot_hold);
    ui->remoteMonitorCmbx->setCurrentIndex(Anytone::Memory::optional_settings->remote_monitor);
    ui->smsFormatCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sms_format);

    // Alert Tone
    ui->smsAlertCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sms_alert);
    ui->callAlertCmbx->setCurrentIndex(Anytone::Memory::optional_settings->call_alert);
    ui->digiCallResetToneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digi_call_reset_tone);
    ui->talkPermitCmbx->setCurrentIndex(Anytone::Memory::optional_settings->talk_permit);
    ui->keyToneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->key_tone);
    ui->digiIdleChannelToneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digi_idle_channel_tone);
    ui->startupSoundCmbx->setCurrentIndex(Anytone::Memory::optional_settings->startup_sound);
    ui->toneKeySoundAdjustableCmbx->setCurrentIndex(Anytone::Memory::optional_settings->tone_key_sound_adjustable);
    ui->analogIdleChannelToneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->analog_idle_channel_tone);
    ui->pluginRecordingToneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->plugin_recording_tone);

    ui->callPermitFirstToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_first_tone_freq));
    ui->callPermitFirstTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_first_tone_period * 10));
    ui->callPermitSecondToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_second_tone_freq));
    ui->callPermitSecondTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_second_tone_period * 10));
    ui->callPermitThirdToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_third_tone_freq));
    ui->callPermitThirdTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_third_tone_period * 10));
    ui->callPermitFourthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_fourth_tone_freq));
    ui->callPermitFourthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_fourth_tone_period * 10));
    ui->callPermitFifthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_fifth_tone_freq));
    ui->callPermitFifthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_permit_fifth_tone_period * 10));

    ui->idleChannelFirstToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_first_tone_freq));
    ui->idleChannelFirstTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_first_tone_period * 10));
    ui->idleChannelSecondToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_second_tone_freq));
    ui->idleChannelSecondTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_second_tone_period * 10));
    ui->idleChannelThirdToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_third_tone_freq));
    ui->idleChannelThirdTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_third_tone_period * 10));
    ui->idleChannelFourthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_fourth_tone_freq));
    ui->idleChannelFourthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_fourth_tone_period * 10));
    ui->idleChannelFifthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_fifth_tone_freq));
    ui->idleChannelFifthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->idle_channel_fifth_tone_period * 10));

    ui->callResetFirstToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_first_tone_freq));
    ui->callResetFirstTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_first_tone_period * 10));
    ui->callResetSecondToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_second_tone_freq));
    ui->callResetSecondTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_second_tone_period * 10));
    ui->callResetThirdToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_third_tone_freq));
    ui->callResetThirdTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_third_tone_period * 10));
    ui->callResetFourthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_fourth_tone_freq));
    ui->callResetFourthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_fourth_tone_period * 10));
    ui->callResetFifthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_fifth_tone_freq));
    ui->callResetFifthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_reset_fifth_tone_period * 10));

    // Alert Tone 1
    ui->callEndFirstToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_first_tone_freq));
    ui->callEndFirstTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_first_tone_period * 10));
    ui->callEndSecondToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_second_tone_freq));
    ui->callEndSecondTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_second_tone_period * 10));
    ui->callEndThirdToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_third_tone_freq));
    ui->callEndThirdTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_third_tone_period * 10));
    ui->callEndFourthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_fourth_tone_freq));
    ui->callEndFourthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_fourth_tone_period * 10));
    ui->callEndFifthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_fifth_tone_freq));
    ui->callEndFifthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_end_fifth_tone_period * 10));

    ui->callAllFirstToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_first_tone_freq));
    ui->callAllFirstTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_first_tone_period * 10));
    ui->callAllSecondToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_second_tone_freq));
    ui->callAllSecondTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_second_tone_period * 10));
    ui->callAllThirdToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_third_tone_freq));
    ui->callAllThirdTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_third_tone_period * 10));
    ui->callAllFourthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_fourth_tone_freq));
    ui->callAllFourthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_fourth_tone_period * 10));
    ui->callAllFifthToneFreqTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_fifth_tone_freq));
    ui->callAllFifthTonePeriodTxt->setText(QString::number(Anytone::Memory::optional_settings->call_all_fifth_tone_period * 10));

    // GPS/Ranging
    ui->gpsCmbx->setCurrentIndex(Anytone::Memory::optional_settings->gps_power);
    ui->gpsPositioningCmbx->setCurrentIndex(Anytone::Memory::optional_settings->gps_positioning);
    ui->timeZoneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->time_zone);
    ui->rangingIntervalCmbx->setCurrentIndex(Anytone::Memory::optional_settings->ranging_interval - 5);
    ui->distanceUnitCmbx->setCurrentIndex(Anytone::Memory::optional_settings->distance_unit);
    ui->gpsInformationUpdateCmbx->setCurrentIndex(Anytone::Memory::optional_settings->gps_template_information);
    ui->gpsModeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->gps_mode);
    ui->gpsInformationUpdateTxt->setText(Anytone::Memory::optional_settings->gps_information_char);
    ui->gpsRoamingCmbx->setCurrentIndex(Anytone::Memory::optional_settings->gps_roaming);

    // VFO Scan
    ui->vfoScanTypeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->vfo_scan_type);
    ui->vfoScanStartUhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->vfo_scan_start_freq_uhf)/100000)));
    ui->vfoScanEndUhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->vfo_scan_end_freq_uhf)/100000)));
    ui->vfoScanStartVhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->vfo_scan_start_freq_vhf)/100000)));
    ui->vfoScanEndVhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->vfo_scan_end_freq_vhf)/100000)));

    // Auto Repeater
    ui->autoRepeaterACmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_repeater_a);
    ui->autoRepeaterBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_repeater_b);
    ui->autoRepeater1UhfCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_repeater_1_uhf != 0xff ? Anytone::Memory::optional_settings->auto_repeater_1_uhf + 1 : 0);
    ui->autoRepeater1VhfCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_repeater_1_vhf != 0xff ? Anytone::Memory::optional_settings->auto_repeater_1_vhf + 1 : 0);
    ui->autoRepeater2UhfCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_repeater_2_uhf != 0xff ? Anytone::Memory::optional_settings->auto_repeater_2_uhf + 1 : 0);
    ui->autoRepeater2VhfCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_repeater_2_vhf != 0xff ? Anytone::Memory::optional_settings->auto_repeater_2_vhf + 1 : 0);

    
    ui->repeaterCheckCmbx->setCurrentIndex(Anytone::Memory::optional_settings->repeater_check);
    ui->repeaterCheckIntervalsCmbx->setCurrentIndex(Anytone::Memory::optional_settings->repeater_check_interval);
    ui->repeaterCheckReconnectionsCmbx->setCurrentIndex(Anytone::Memory::optional_settings->repeater_check_reconnections);
    ui->repeaterOutOfRangeNotifyCmbx->setCurrentIndex(Anytone::Memory::optional_settings->repeater_out_of_range_notify);
    ui->outOfRangeNotifyCmbx->setCurrentIndex(Anytone::Memory::optional_settings->out_of_range_notify);
    ui->autoRoamingCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_roaming);
    ui->autoRoamingStartConditionCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_roaming_start_condition);
    ui->autoRoamingFixedTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->auto_roaming_fixed_time);
    ui->roamingEffectWaitTimeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->roaming_effect_wait_time);
                                                        
    ui->minFreqAutoRepeater1VhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_1_min_freq_vhf)/100000)));
    ui->maxFreqAutoRepeater1VhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_1_max_freq_vhf)/100000)));
    ui->minFreqAutoRepeater1UhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_1_min_freq_uhf)/100000)));
    ui->maxFreqAutoRepeater1UhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_1_max_freq_uhf)/100000)));

    ui->minFreqAutoRepeater2VhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_2_min_freq_vhf)/100000)));
    ui->maxFreqAutoRepeater2VhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_2_max_freq_vhf)/100000)));
    ui->minFreqAutoRepeater2UhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_2_min_freq_uhf)/100000)));
    ui->maxFreqAutoRepeater2UhfTxt->setText(formatFrequency(QString::number(double(Anytone::Memory::optional_settings->auto_repeater_2_max_freq_uhf)/100000)));

    // Record
    ui->recordFunctionCmbx->setCurrentIndex(Anytone::Memory::optional_settings->record_function);

    // Volume/Audio
    ui->maxVolumeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->max_volume);
    ui->maxHeadphoneVolumeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->max_headphone_volume);
    ui->digiMicGainCmbx->setCurrentIndex(Anytone::Memory::optional_settings->digi_mic_gain);
    ui->enhancedSoundQualityCmbx->setCurrentIndex(Anytone::Memory::optional_settings->enhanced_sound_quality);
    ui->analogMicGainCmbx->setCurrentIndex(Anytone::Memory::optional_settings->analog_mic_gain);


    // 890UV
    ui->amFmFunctionCmbx->setCurrentIndex(Anytone::Memory::optional_settings->am_fm_function);
    ui->amVfoMemCmbx->setCurrentIndex(Anytone::Memory::optional_settings->am_vfo_mem);
    ui->amWorkZoneCmbx->setCurrentIndex(Anytone::Memory::optional_settings->am_work_zone);
    ui->amOffsetCmbx->setCurrentIndex(Anytone::Memory::optional_settings->am_offset);
    ui->amSqlLevelCmbx->setCurrentIndex(Anytone::Memory::optional_settings->am_sql_level);
    ui->btNrBeforeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_nr_before);
    ui->btNrAfterCmbx->setCurrentIndex(Anytone::Memory::optional_settings->bt_nr_after);
    ui->repeaterModeCmbx->setCurrentIndex(Anytone::Memory::optional_settings->repeater_mode);
    ui->repCcLimitCmbx->setCurrentIndex(Anytone::Memory::optional_settings->rep_cc_limit);
    ui->repSlotACmbx->setCurrentIndex(Anytone::Memory::optional_settings->rep_slot_a);
    ui->repSlotBCmbx->setCurrentIndex(Anytone::Memory::optional_settings->rep_slot_b);
    ui->recordDelayCmbx->setCurrentIndex(Anytone::Memory::optional_settings->record_delay);
    ui->satLocationCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sat_location);
    ui->satTxPowerCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sat_tx_power);
    ui->satAnaSqlCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sat_ana_sql);
    ui->satAosLimitCmbx->setCurrentIndex(Anytone::Memory::optional_settings->sat_aos_limit);
    ui->noaaMoniCmbx->setCurrentIndex(Anytone::Memory::optional_settings->noaa_moni);
    ui->noaaScanCmbx->setCurrentIndex(Anytone::Memory::optional_settings->noaa_scan);
    ui->noaaCmbx->setCurrentIndex(Anytone::Memory::optional_settings->noaa);
    ui->noaaChannelCmbx->setCurrentIndex(Anytone::Memory::optional_settings->noaa_channel);
}
void OptionalSettingsDialog::updateWorkMode(){
    int work_mode = ui->displayModeCmbx->currentIndex();
    ui->vfMrACmbx->setDisabled(work_mode == 0);
    ui->vfMrBCmbx->setDisabled(work_mode == 0);
}
void OptionalSettingsDialog::updateStartupChannels(){
    if(ui->defaultStartupChannelCmbx->currentIndex() == 0){
        ui->startupZoneACmbx->setDisabled(true);
        ui->startupZoneBCmbx->setDisabled(true);
        ui->startupChannelACmbx->setDisabled(true);
        ui->startupChannelBCmbx->setDisabled(true);
    }else{
        ui->startupZoneACmbx->setDisabled(false);
        ui->startupZoneBCmbx->setDisabled(false);
        ui->startupChannelACmbx->setDisabled(false);
        ui->startupChannelBCmbx->setDisabled(false);
    }

    int startup_ch_a = ui->startupChannelACmbx->currentIndex();
    int startup_ch_b = ui->startupChannelBCmbx->currentIndex();

    if(startup_ch_a < 0) startup_ch_a = 0;
    if(startup_ch_b < 0) startup_ch_b = 0;

    ui->startupChannelACmbx->clear();
    ui->startupChannelBCmbx->clear();
    ui->startupChannelACmbx->addItem("VFO");
    ui->startupChannelBCmbx->addItem("VFO");
    if(ui->startupZoneACmbx->currentIndex() >= 0 && ui->startupZoneACmbx->currentIndex() < Anytone::Memory::zones.size()){
        for(Anytone::Channel *ch : Anytone::Memory::zones.at(ui->startupZoneACmbx->currentIndex())->channels){
            ui->startupChannelACmbx->addItem(ch->name);
            ui->startupChannelBCmbx->addItem(ch->name);
        }
    }
    ui->startupChannelACmbx->setCurrentIndex(startup_ch_a);
    ui->startupChannelBCmbx->setCurrentIndex(startup_ch_b);
}
void OptionalSettingsDialog::keyFunctionChanged(){
    if(ui->pf1ShortCmbx->currentText() == "Monitor"){
        ui->pf1LongCmbx->setCurrentIndex(0);
        ui->pf1LongCmbx->setDisabled(true);
    }else{
        ui->pf1LongCmbx->setDisabled(false);
    }

    if(ui->pf2ShortCmbx->currentText() == "Monitor"){
        ui->pf2LongCmbx->setCurrentIndex(0);
        ui->pf2LongCmbx->setDisabled(true);
    }else{
        ui->pf2LongCmbx->setDisabled(false);
    }

    if(ui->pf3ShortCmbx->currentText() == "Monitor"){
        ui->pf3LongCmbx->setCurrentIndex(0);
        ui->pf3LongCmbx->setDisabled(true);
    }else{
        ui->pf3LongCmbx->setDisabled(false);
    }

    if(ui->p1ShortCmbx->currentText() == "Monitor"){
        ui->p1LongCmbx->setCurrentIndex(0);
        ui->p1LongCmbx->setDisabled(true);
    }else{
        ui->p1LongCmbx->setDisabled(false);
    }

    if(ui->p2ShortCmbx->currentText() == "Monitor"){
        ui->p2LongCmbx->setCurrentIndex(0);
        ui->p2LongCmbx->setDisabled(true);
    }else{
        ui->p2LongCmbx->setDisabled(false);
    }
}
void OptionalSettingsDialog::saveClose(){
    save();
    close();
}
void OptionalSettingsDialog::powerOnCharUpdate(PowerOnCharLineEdit *lineEdit){
    int char_idx = -1;
    QString text = lineEdit->text();
    if(!text.isEmpty()){
        lineEdit->blockSignals(true);
        lineEdit->setText(text.toUpper());
        lineEdit->blockSignals(false);
        char_idx = (display_char_line1_txt_list + display_char_line2_txt_list).indexOf(lineEdit);
        if(char_idx < 27){
            (display_char_line1_txt_list + display_char_line2_txt_list).at(char_idx+1)->setFocus();
        }
    }
}
void OptionalSettingsDialog::powerOnCharKeyPress(PowerOnCharLineEdit *lineEdit){
    QString text = lineEdit->text();
    if(text.isEmpty()){
        int char_idx = (display_char_line1_txt_list + display_char_line2_txt_list).indexOf(lineEdit);
        if(char_idx > 0){
            (display_char_line1_txt_list + display_char_line2_txt_list).at(char_idx-1)->setFocus();
        }
    }
}
void OptionalSettingsDialog::playCallEndTone(){
    QVector<QPair<double,double>> tones = {
        {ui->callEndFirstToneFreqTxt->text().toInt(), double(ui->callEndFirstTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callEndSecondToneFreqTxt->text().toInt(), double(ui->callEndSecondTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callEndThirdToneFreqTxt->text().toInt(), double(ui->callEndThirdTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callEndFourthToneFreqTxt->text().toInt(), double(ui->callEndFourthTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callEndFifthToneFreqTxt->text().toInt(), double(ui->callEndFifthTonePeriodTxt->text().toDouble() / 1000)}
    };

    playTones(tones);
}
void OptionalSettingsDialog::playCallAllTone(){
    QVector<QPair<double,double>> tones = {
        {ui->callAllFirstToneFreqTxt->text().toInt(), double(ui->callAllFirstTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callAllSecondToneFreqTxt->text().toInt(), double(ui->callAllSecondTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callAllThirdToneFreqTxt->text().toInt(), double(ui->callAllThirdTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callAllFourthToneFreqTxt->text().toInt(), double(ui->callAllFourthTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callAllFifthToneFreqTxt->text().toInt(), double(ui->callAllFifthTonePeriodTxt->text().toDouble() / 1000)}
    };

    playTones(tones);
}
void OptionalSettingsDialog::playCallPermitTone(){
    QVector<QPair<double,double>> tones = {
        {ui->callPermitFirstToneFreqTxt->text().toInt(), double(ui->callPermitFirstTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callPermitSecondToneFreqTxt->text().toInt(), double(ui->callPermitSecondTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callPermitThirdToneFreqTxt->text().toInt(), double(ui->callPermitThirdTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callPermitFourthToneFreqTxt->text().toInt(), double(ui->callPermitFourthTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callPermitFifthToneFreqTxt->text().toInt(), double(ui->callPermitFifthTonePeriodTxt->text().toDouble() / 1000)}
    };

    playTones(tones);
}
void OptionalSettingsDialog::playIdleChannelTone(){
    QVector<QPair<double,double>> tones = {
        {ui->idleChannelFirstToneFreqTxt->text().toInt(), double(ui->idleChannelFirstTonePeriodTxt->text().toDouble() / 1000)},
        {ui->idleChannelSecondToneFreqTxt->text().toInt(), double(ui->idleChannelSecondTonePeriodTxt->text().toDouble() / 1000)},
        {ui->idleChannelThirdToneFreqTxt->text().toInt(), double(ui->idleChannelThirdTonePeriodTxt->text().toDouble() / 1000)},
        {ui->idleChannelFourthToneFreqTxt->text().toInt(), double(ui->idleChannelFourthTonePeriodTxt->text().toDouble() / 1000)},
        {ui->idleChannelFifthToneFreqTxt->text().toInt(), double(ui->idleChannelFifthTonePeriodTxt->text().toDouble() / 1000)}
    };

    playTones(tones);
}
void OptionalSettingsDialog::playCallResetTone(){
    QVector<QPair<double,double>> tones = {
        {ui->callResetFirstToneFreqTxt->text().toInt(), double(ui->callResetFirstTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callResetSecondToneFreqTxt->text().toInt(), double(ui->callResetSecondTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callResetThirdToneFreqTxt->text().toInt(), double(ui->callResetThirdTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callResetFourthToneFreqTxt->text().toInt(), double(ui->callResetFourthTonePeriodTxt->text().toDouble() / 1000)},
        {ui->callResetFifthToneFreqTxt->text().toInt(), double(ui->callResetFifthTonePeriodTxt->text().toDouble() / 1000)}
    };

    playTones(tones);
}
QByteArray OptionalSettingsDialog::makeU8Sine(int sampleRate, double freqHz, double durationSec)
{
    const int nSamples = int(sampleRate * durationSec);
    QByteArray out;
    out.resize(nSamples);

    for (int t = 0; t < nSamples; ++t) {
        double s = std::sin(2.0 * M_PI * freqHz * (double(t) / sampleRate));
        int v = int(s * 127.0 + 128.0);
        v = std::clamp(v, 0, 255);
        out[t] = char(uint8_t(v));
    }
    return out;
}
void OptionalSettingsDialog::playTones(const QVector<QPair<double,double>>& toneList, int sampleRate)
{
    QAudioFormat fmt;
    fmt.setSampleRate(sampleRate);
    fmt.setChannelCount(1);
    fmt.setSampleFormat(QAudioFormat::UInt8); // unsigned 8-bit

    auto *sink = new QAudioSink(fmt); // parent it appropriately in your class if needed

    QByteArray pcm;
    for (auto &tone : toneList)
        pcm += makeU8Sine(sampleRate, tone.first, tone.second);

    auto *buf = new QBuffer(sink);
    buf->setData(pcm);
    buf->open(QIODevice::ReadOnly);

    sink->start(buf);

    // If you need to block until done (not recommended on UI thread):
    // connect(sink, &QAudioSink::stateChanged, ... stop/delete when IdleState)
}

void OptionalSettingsDialog::save(){
    // Power-On
    Anytone::Memory::optional_settings->poweron_interface = ui->poweronInterfaceCmbx->currentIndex();
    
    for(int i = 0; i < display_char_line1_txt_list.size(); i++){
        PowerOnCharLineEdit *poc = display_char_line1_txt_list.at(i);
        Anytone::Memory::optional_settings->poweron_display_1[i] = (poc->text().isEmpty()?'\0':poc->text().at(0).toLatin1());
    }
    for(int i = 0; i < display_char_line2_txt_list.size(); i++){
        PowerOnCharLineEdit *poc = display_char_line2_txt_list.at(i);
        Anytone::Memory::optional_settings->poweron_display_2[i] = (poc->text().isEmpty()?'\0':poc->text().at(0).toLatin1());
    }

    Anytone::Memory::optional_settings->poweron_password = ui->poweronPasswordCmbx->currentIndex();
    Anytone::Memory::optional_settings->poweron_password_char = ui->poweronPasswordTxt->text();
    Anytone::Memory::optional_settings->default_startup_channel = ui->defaultStartupChannelCmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_zone_a = ui->startupZoneACmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_zone_b = ui->startupZoneBCmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_channel_a = ui->startupChannelACmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_channel_b = ui->startupChannelBCmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_gps_test = ui->startupGpsTestCmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_reset = ui->startupResetCmbx->currentIndex();

    // Power Save
    Anytone::Memory::optional_settings->auto_shutdown = ui->autoShutdownCmbx->currentIndex();
    Anytone::Memory::optional_settings->power_save = ui->powerSaveCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_shutdown_type = ui->autoShutdownTypeCmbx->currentIndex();

    // Display
    Anytone::Memory::optional_settings->brightness = ui->brightnessCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_backlight_duration = ui->autoBacklightDurationCmbx->currentIndex();
    Anytone::Memory::optional_settings->backlight_tx_delay = ui->backlightDelayTxCmbx->currentIndex();
    Anytone::Memory::optional_settings->menu_exit_time = ui->menuExitTimeCmbx->currentIndex();
    Anytone::Memory::optional_settings->time_display = ui->timeDisplayCmbx->currentIndex();
    Anytone::Memory::optional_settings->last_caller = ui->lastCallerCmbx->currentIndex();
    Anytone::Memory::optional_settings->call_display_mode = ui->callDisplayModeCmbx->currentIndex();
    Anytone::Memory::optional_settings->callsign_display_color = ui->callsignDisplayColorCmbx->currentIndex();
    Anytone::Memory::optional_settings->call_end_prompt_box = ui->callEndPromptCmbx->currentIndex();
    Anytone::Memory::optional_settings->display_channel_number = ui->displayChannelNumberCmbx->currentIndex();
    Anytone::Memory::optional_settings->display_current_contact = ui->displayCurrentContactCmbx->currentIndex();
    Anytone::Memory::optional_settings->standby_char_color = ui->standbyCharColorCmbx->currentIndex();
    Anytone::Memory::optional_settings->standby_bk_picture = ui->standbyBkPictureCmbx->currentIndex();
    Anytone::Memory::optional_settings->show_last_call_on_launch = ui->showLastCallOnLaunchCmbx->currentIndex();
    Anytone::Memory::optional_settings->separate_display = ui->separateDisplayCmbx->currentIndex();
    Anytone::Memory::optional_settings->ch_switching_keeps_caller = ui->keepsLastCallerCmbx->currentIndex();
    Anytone::Memory::optional_settings->backlight_rx_delay = ui->backlightDelayRxCmbx->currentIndex();
    Anytone::Memory::optional_settings->channel_name_color_a = ui->channelNameColorACmbx->currentIndex();
    Anytone::Memory::optional_settings->channel_name_color_b = ui->channelNameColorBCmbx->currentIndex();
    Anytone::Memory::optional_settings->zone_name_color_a = ui->zoneNameColorACmbx->currentIndex();
    Anytone::Memory::optional_settings->zone_name_color_b = ui->zoneNameColorBCmbx->currentIndex();
    Anytone::Memory::optional_settings->display_channel_type = ui->displayChannelTypeCmbx->currentIndex();
    Anytone::Memory::optional_settings->display_time_slot = ui->displayTimeSlotCmbx->currentIndex();
    Anytone::Memory::optional_settings->display_color_code = ui->displayColorCodeCmbx->currentIndex();
    Anytone::Memory::optional_settings->date_display_format = ui->dateDisplayFormatCmbx->currentIndex();
    Anytone::Memory::optional_settings->volume_bar = ui->volumeBarCmbx->currentIndex();

    // Work Mode
    Anytone::Memory::optional_settings->display_mode = ui->displayModeCmbx->currentIndex();
    Anytone::Memory::optional_settings->vf_mr_a = ui->vfMrACmbx->currentIndex();
    Anytone::Memory::optional_settings->vf_mr_b = ui->vfMrBCmbx->currentIndex();
    Anytone::Memory::optional_settings->mem_zone_a = ui->memZoneACmbx->currentIndex();
    Anytone::Memory::optional_settings->mem_zone_b = ui->memZoneBCmbx->currentIndex();
    Anytone::Memory::optional_settings->main_channel_set = ui->mainChannelSetCmbx->currentIndex();
    Anytone::Memory::optional_settings->sub_channel_mode = ui->subChannelModeCmbx->currentIndex();
    Anytone::Memory::optional_settings->working_mode = ui->workingModeCmbx->currentIndex();

    // Vox/BT
    Anytone::Memory::optional_settings->vox_level = ui->voxLevelCmbx->currentIndex();
    Anytone::Memory::optional_settings->vox_delay = ui->voxDelayCmbx->currentIndex();
    Anytone::Memory::optional_settings->vox_detection = ui->voxDetectionCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_int_mic = ui->btIntMicCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_int_spk = ui->btIntSpkCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_mic_gain = ui->btMicGainCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_spk_gain = ui->btSpkGainCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_hold_time = ui->btHoldTimeCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_rx_delay = ui->btRxDelayCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_ptt_hold = ui->btPttHoldCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_ptt_sleep_time = ui->pttSleepTimeCmbx->currentIndex();

    // STE
    Anytone::Memory::optional_settings->ste_type_of_ctcss = ui->steCtcssTypeCmbx->currentIndex();
    Anytone::Memory::optional_settings->ste_when_no_signal = ui->steNoSignalCmbx->currentIndex();
    Anytone::Memory::optional_settings->ste_time = ui->steTimeCmbx->currentIndex() + 1;

    // FM
    Anytone::Memory::optional_settings->fm_vfo_mem = ui->fmVfMrCmbx->currentIndex();
    Anytone::Memory::optional_settings->fm_work_channel = ui->fmWorkChannelCmbx->currentIndex();
    Anytone::Memory::optional_settings->fm_monitor = ui->fmMonitorCmbx->currentIndex();

    // Key Function
    Anytone::Memory::optional_settings->key_lock = ui->keyLockCmbx->currentIndex();
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        Anytone::Memory::optional_settings->pf1_short_key_D878UVII = ui->pf1ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf2_short_key_D878UVII = ui->pf2ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf3_short_key_D878UVII = ui->pf3ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->p1_short_key_D878UVII = ui->p1ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->p2_short_key_D878UVII = ui->p2ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf1_long_key_D878UVII = ui->pf1LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf2_long_key_D878UVII = ui->pf2LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf3_long_key_D878UVII = ui->pf3LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->p1_long_key_D878UVII = ui->p1LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->p2_long_key_D878UVII = ui->p2LongCmbx->currentIndex();
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        Anytone::Memory::optional_settings->pf1_short_key_D890UV = ui->pf1ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf2_short_key_D890UV = ui->pf2ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf3_short_key_D890UV = ui->pf3ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->p1_short_key_D890UV = ui->p1ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->p2_short_key_D890UV = ui->p2ShortCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf1_long_key_D890UV = ui->pf1LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf2_long_key_D890UV = ui->pf2LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->pf3_long_key_D890UV = ui->pf3LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->p1_long_key_D890UV = ui->p1LongCmbx->currentIndex();
        Anytone::Memory::optional_settings->p2_long_key_D890UV = ui->p2LongCmbx->currentIndex();
    }
    Anytone::Memory::optional_settings->long_key_time = ui->longKeyTimeCmbx->currentIndex();
    Anytone::Memory::optional_settings->knob_lock = ui->knobLockCmbx->currentIndex();
    Anytone::Memory::optional_settings->keyboard_lock = ui->keyboardLockCmbx->currentIndex();
    Anytone::Memory::optional_settings->side_key_lock = ui->sideKeyLockCmbx->currentIndex();
    Anytone::Memory::optional_settings->forced_key_lock = ui->forcedKeyLockCmbx->currentIndex();

    // Other
    Anytone::Memory::optional_settings->address_book_sent_with_code = ui->addressSentWithOwnCodeCmbx->currentIndex();
    Anytone::Memory::optional_settings->tot = ui->totCmbx->currentIndex();
    Anytone::Memory::optional_settings->language = ui->languageCmbx->currentIndex();
    Anytone::Memory::optional_settings->frequency_step = ui->frequencyStepCmbx->currentIndex();
    Anytone::Memory::optional_settings->sql_level_a = ui->sqlLevelACmbx->currentIndex();
    Anytone::Memory::optional_settings->sql_level_b = ui->sqlLevelBCmbx->currentIndex();
    Anytone::Memory::optional_settings->tbst = ui->tbstCmbx->currentIndex();
    Anytone::Memory::optional_settings->analog_call_hold_time = ui->analogCallHoldTimeCmbx->currentIndex();
    Anytone::Memory::optional_settings->call_channel_maintained = ui->callChannelMaintainedCmbx->currentIndex();
    Anytone::Memory::optional_settings->priority_zone_a = ui->priorityZoneACmbx->currentIndex();
    Anytone::Memory::optional_settings->priority_zone_b = ui->priorityZoneBCmbx->currentIndex();
    Anytone::Memory::optional_settings->mute_timing = ui->muteTimingCmbx->currentIndex();
    Anytone::Memory::optional_settings->encryption_type = ui->encryptionTypeCmbx->currentIndex();
    Anytone::Memory::optional_settings->tot_predict = ui->totPredictCmbx->currentIndex();
    Anytone::Memory::optional_settings->tx_power_agc = ui->txPowerAgcCmbx->currentIndex();

        // Digital Func
    Anytone::Memory::optional_settings->group_call_hold_time = ui->groupCallHoldTimeCmbx->currentIndex() + 1;
    Anytone::Memory::optional_settings->private_call_hold_time = ui->privateCallHoldTimeCmbx->currentIndex() + 1;
    Anytone::Memory::optional_settings->manual_dial_group_call_hold_time = ui->manualDialGroupCallHoldTimeCmbx->currentIndex() + 1;
    Anytone::Memory::optional_settings->manual_dial_private_call_hold_time = ui->manualDialPrivateCallHoldTimeCmbx->currentIndex() + 1;
    Anytone::Memory::optional_settings->voice_header_repetitions = ui->voiceHeaderRepetitionsCmbx->currentIndex() + 2;
    Anytone::Memory::optional_settings->tx_preamble_duration = ui->txPreambleDurationCmbx->currentIndex();
    Anytone::Memory::optional_settings->filter_own_id = ui->filterOwnCallInMissedCallsCmbx->currentIndex();
    Anytone::Memory::optional_settings->digital_remote_kill = ui->digitalRemoteKillCmbx->currentIndex();
    Anytone::Memory::optional_settings->digital_monitor = ui->digitalMonitorCmbx->currentIndex();
    Anytone::Memory::optional_settings->digital_monitor_cc = ui->digitalMonitorCcCmbx->currentIndex();
    Anytone::Memory::optional_settings->digital_monitor_id = ui->digitalMonitorIdCmbx->currentIndex();
    Anytone::Memory::optional_settings->monitor_slot_hold = ui->monitorHoldSlotCmbx->currentIndex();
    Anytone::Memory::optional_settings->remote_monitor = ui->remoteMonitorCmbx->currentIndex();
    Anytone::Memory::optional_settings->sms_format = ui->smsFormatCmbx->currentIndex();

    // Alert Tone
    Anytone::Memory::optional_settings->sms_alert = ui->smsAlertCmbx->currentIndex();
    Anytone::Memory::optional_settings->call_alert = ui->callAlertCmbx->currentIndex();
    Anytone::Memory::optional_settings->digi_call_reset_tone = ui->digiCallResetToneCmbx->currentIndex();
    Anytone::Memory::optional_settings->talk_permit = ui->talkPermitCmbx->currentIndex();
    Anytone::Memory::optional_settings->key_tone = ui->keyToneCmbx->currentIndex();
    Anytone::Memory::optional_settings->digi_idle_channel_tone = ui->digiIdleChannelToneCmbx->currentIndex();
    Anytone::Memory::optional_settings->startup_sound = ui->startupSoundCmbx->currentIndex();
    Anytone::Memory::optional_settings->tone_key_sound_adjustable = ui->toneKeySoundAdjustableCmbx->currentIndex();
    Anytone::Memory::optional_settings->analog_idle_channel_tone = ui->analogIdleChannelToneCmbx->currentIndex();
    Anytone::Memory::optional_settings->plugin_recording_tone = ui->pluginRecordingToneCmbx->currentIndex();

    Anytone::Memory::optional_settings->call_permit_first_tone_freq = ui->callPermitFirstToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_permit_second_tone_freq = ui->callPermitSecondToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_permit_third_tone_freq = ui->callPermitThirdToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_permit_fourth_tone_freq = ui->callPermitFourthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_permit_fifth_tone_freq = ui->callPermitFifthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_permit_first_tone_period = int(ui->callPermitFirstTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_permit_second_tone_period = int(ui->callPermitSecondTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_permit_third_tone_period = int(ui->callPermitThirdTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_permit_fourth_tone_period = int(ui->callPermitFourthTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_permit_fifth_tone_period = int(ui->callPermitFifthTonePeriodTxt->text().toDouble() / 10);

    Anytone::Memory::optional_settings->idle_channel_first_tone_freq = ui->idleChannelFirstToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->idle_channel_second_tone_freq = ui->idleChannelSecondToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->idle_channel_third_tone_freq = ui->idleChannelThirdToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->idle_channel_fourth_tone_freq = ui->idleChannelFourthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->idle_channel_fifth_tone_freq = ui->idleChannelFifthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->idle_channel_first_tone_period = int(ui->idleChannelFirstTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->idle_channel_second_tone_period = int(ui->idleChannelSecondTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->idle_channel_third_tone_period = int(ui->idleChannelThirdTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->idle_channel_fourth_tone_period = int(ui->idleChannelFourthTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->idle_channel_fifth_tone_period = int(ui->idleChannelFifthTonePeriodTxt->text().toDouble() / 10);

    Anytone::Memory::optional_settings->call_reset_first_tone_freq = ui->callResetFirstToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_reset_second_tone_freq = ui->callResetSecondToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_reset_third_tone_freq = ui->callResetThirdToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_reset_fourth_tone_freq = ui->callResetFourthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_reset_fifth_tone_freq = ui->callResetFifthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_reset_first_tone_period = int(ui->callResetFirstTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_reset_second_tone_period = int(ui->callResetSecondTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_reset_third_tone_period = int(ui->callResetThirdTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_reset_fourth_tone_period = int(ui->callResetFourthTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_reset_fifth_tone_period = int(ui->callResetFifthTonePeriodTxt->text().toDouble() / 10);
    
    // Alert Tone 1
    Anytone::Memory::optional_settings->call_end_first_tone_freq = ui->callEndFirstToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_end_second_tone_freq = ui->callEndSecondToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_end_third_tone_freq = ui->callEndThirdToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_end_fourth_tone_freq = ui->callEndFourthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_end_fifth_tone_freq = ui->callEndFifthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_end_first_tone_period = int(ui->callEndFirstTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_end_second_tone_period = int(ui->callEndSecondTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_end_third_tone_period = int(ui->callEndThirdTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_end_fourth_tone_period = int(ui->callEndFourthTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_end_fifth_tone_period = int(ui->callEndFifthTonePeriodTxt->text().toDouble() / 10);

    Anytone::Memory::optional_settings->call_all_first_tone_freq = ui->callAllFirstToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_all_second_tone_freq = ui->callAllSecondToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_all_third_tone_freq = ui->callAllThirdToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_all_fourth_tone_freq = ui->callAllFourthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_all_fifth_tone_freq = ui->callAllFifthToneFreqTxt->text().toInt();
    Anytone::Memory::optional_settings->call_all_first_tone_period = int(ui->callAllFirstTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_all_second_tone_period = int(ui->callAllSecondTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_all_third_tone_period = int(ui->callAllThirdTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_all_fourth_tone_period = int(ui->callAllFourthTonePeriodTxt->text().toDouble() / 10);
    Anytone::Memory::optional_settings->call_all_fifth_tone_period = int(ui->callAllFifthTonePeriodTxt->text().toDouble() / 10);

    // GPS/Ranging
    Anytone::Memory::optional_settings->gps_power = ui->gpsCmbx->currentIndex();
    Anytone::Memory::optional_settings->gps_positioning = ui->gpsPositioningCmbx->currentIndex();
    Anytone::Memory::optional_settings->time_zone = ui->timeZoneCmbx->currentIndex();
    Anytone::Memory::optional_settings->ranging_interval = ui->rangingIntervalCmbx->currentIndex() + 5;
    Anytone::Memory::optional_settings->distance_unit = ui->distanceUnitCmbx->currentIndex();
    Anytone::Memory::optional_settings->gps_template_information = ui->gpsInformationUpdateCmbx->currentIndex();
    Anytone::Memory::optional_settings->gps_mode = ui->gpsModeCmbx->currentIndex();
    Anytone::Memory::optional_settings->gps_information_char = ui->gpsInformationUpdateTxt->text();

    // VFO Scan
    Anytone::Memory::optional_settings->vfo_scan_type = ui->vfoScanTypeCmbx->currentIndex();
    Anytone::Memory::optional_settings->vfo_scan_start_freq_uhf = int(ui->vfoScanStartUhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->vfo_scan_end_freq_uhf = int(ui->vfoScanEndUhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->vfo_scan_start_freq_vhf = int(ui->vfoScanStartVhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->vfo_scan_end_freq_vhf = int(ui->vfoScanEndVhfTxt->text().toDouble() * 100000);

    // Auto Repeater
    Anytone::Memory::optional_settings->auto_repeater_a = ui->autoRepeaterACmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_repeater_b = ui->autoRepeaterBCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_repeater_1_uhf = ui->autoRepeater1UhfCmbx->currentIndex() > 0 ? ui->autoRepeater1UhfCmbx->currentIndex() + 1 : 0xff;
    Anytone::Memory::optional_settings->auto_repeater_1_vhf = ui->autoRepeater1VhfCmbx->currentIndex() > 0 ? ui->autoRepeater1VhfCmbx->currentIndex() + 1 : 0xff;
    Anytone::Memory::optional_settings->auto_repeater_2_uhf = ui->autoRepeater2UhfCmbx->currentIndex() > 0 ? ui->autoRepeater2UhfCmbx->currentIndex() + 1 : 0xff;
    Anytone::Memory::optional_settings->auto_repeater_2_vhf = ui->autoRepeater2VhfCmbx->currentIndex() > 0 ? ui->autoRepeater2VhfCmbx->currentIndex() + 1 : 0xff;
    Anytone::Memory::optional_settings->repeater_check = ui->repeaterCheckCmbx->currentIndex();
    Anytone::Memory::optional_settings->repeater_check_interval = ui->repeaterCheckIntervalsCmbx->currentIndex();
    Anytone::Memory::optional_settings->repeater_check_reconnections = ui->repeaterCheckReconnectionsCmbx->currentIndex();
    Anytone::Memory::optional_settings->repeater_out_of_range_notify = ui->repeaterOutOfRangeNotifyCmbx->currentIndex();
    Anytone::Memory::optional_settings->out_of_range_notify = ui->outOfRangeNotifyCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_roaming = ui->autoRoamingCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_roaming_start_condition = ui->autoRoamingStartConditionCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_roaming_fixed_time = ui->autoRoamingFixedTimeCmbx->currentIndex();
    Anytone::Memory::optional_settings->roaming_effect_wait_time = ui->roamingEffectWaitTimeCmbx->currentIndex();
    Anytone::Memory::optional_settings->auto_repeater_1_min_freq_vhf = int(ui->minFreqAutoRepeater1VhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_1_max_freq_vhf = int(ui->maxFreqAutoRepeater1VhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_1_min_freq_uhf = int(ui->minFreqAutoRepeater1UhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_1_max_freq_uhf = int(ui->maxFreqAutoRepeater1UhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_2_min_freq_vhf = int(ui->minFreqAutoRepeater2VhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_2_max_freq_vhf = int(ui->maxFreqAutoRepeater2VhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_2_min_freq_uhf = int(ui->minFreqAutoRepeater2UhfTxt->text().toDouble() * 100000);
    Anytone::Memory::optional_settings->auto_repeater_2_max_freq_uhf = int(ui->maxFreqAutoRepeater2UhfTxt->text().toDouble() * 100000);

    // Record
    Anytone::Memory::optional_settings->record_function = ui->recordFunctionCmbx->currentIndex();

    // Volume/Audio
    Anytone::Memory::optional_settings->max_volume = ui->maxVolumeCmbx->currentIndex();
    Anytone::Memory::optional_settings->max_headphone_volume = ui->maxHeadphoneVolumeCmbx->currentIndex();
    Anytone::Memory::optional_settings->digi_mic_gain = ui->digiMicGainCmbx->currentIndex();
    Anytone::Memory::optional_settings->enhanced_sound_quality = ui->enhancedSoundQualityCmbx->currentIndex();
    Anytone::Memory::optional_settings->analog_mic_gain = ui->analogMicGainCmbx->currentIndex();

    // 890UV
    Anytone::Memory::optional_settings->am_fm_function = ui->amFmFunctionCmbx->currentIndex();
    Anytone::Memory::optional_settings->am_vfo_mem = ui->amVfoMemCmbx->currentIndex();
    Anytone::Memory::optional_settings->am_work_zone = ui->amWorkZoneCmbx->currentIndex();
    Anytone::Memory::optional_settings->am_offset = ui->amOffsetCmbx->currentIndex();
    Anytone::Memory::optional_settings->am_sql_level = ui->amSqlLevelCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_nr_before = ui->btNrBeforeCmbx->currentIndex();
    Anytone::Memory::optional_settings->bt_nr_after = ui->btNrAfterCmbx->currentIndex();
    Anytone::Memory::optional_settings->repeater_mode = ui->repeaterModeCmbx->currentIndex();
    Anytone::Memory::optional_settings->rep_cc_limit = ui->repCcLimitCmbx->currentIndex();
    Anytone::Memory::optional_settings->rep_slot_a = ui->repSlotACmbx->currentIndex();
    Anytone::Memory::optional_settings->rep_slot_b = ui->repSlotBCmbx->currentIndex();
    Anytone::Memory::optional_settings->record_delay = ui->recordDelayCmbx->currentIndex();
    Anytone::Memory::optional_settings->sat_location = ui->satLocationCmbx->currentIndex();
    Anytone::Memory::optional_settings->sat_tx_power = ui->satTxPowerCmbx->currentIndex();
    Anytone::Memory::optional_settings->sat_ana_sql = ui->satAnaSqlCmbx->currentIndex();
    Anytone::Memory::optional_settings->sat_aos_limit = ui->satAosLimitCmbx->currentIndex();
    Anytone::Memory::optional_settings->noaa_moni = ui->noaaMoniCmbx->currentIndex();
    Anytone::Memory::optional_settings->noaa_scan = ui->noaaScanCmbx->currentIndex();
    Anytone::Memory::optional_settings->noaa = ui->noaaCmbx->currentIndex();
    Anytone::Memory::optional_settings->noaa_channel = ui->noaaChannelCmbx->currentIndex();


    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        Anytone::Memory::optional_settings->bt_on_off_D878UVII = ui->btOnOffCmbx->currentIndex();
    }else if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
        Anytone::Memory::optional_settings->bt_on_off_D890UV = ui->btOnOffCmbx->currentIndex();
    }
}
QString OptionalSettingsDialog::formatFrequency(QString frequency){
    double freq = frequency.toDouble();
    if(freq > 480) freq = 480;
    if(freq < 130) freq = 140;
    return QString::number(Format::roundFrequency(freq), 'f', 5);
}