#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <array>
#include <QString>
#include <QStringList>

class Constants {
public:
    static const QString CPS_VERISON;
    static const QString CPS_BUILD_NUMBER;
    static const QString RADIO_MODEL;
    static const QString FW_CPS_VERSION;
    static const QString FW_CPS_VERSION_MODIFIER;
    static const QString RADIO_VERSION;
    static const QStringList OFF_ON;
    static const QStringList VF_MR;
    static const QStringList AT_OPTIONS;
    static const QStringList CHANNEL_TYPE;
    static const QStringList TX_POWER;
    static const QStringList BAND_WIDTH;
    static const QStringList CTCSS_CODE;
    static const QStringList DCS_CODE;
    static const QStringList ANALOG_APRS_PTT_MODE;
    static const QStringList APRS_REPORT_TYPE;
    static const QStringList OPTIONAL_SIGNAL;
    static const QStringList CALL_ALERT;
    static const QStringList CALL_TYPE;
    static const QStringList SCAN_LIST_PRIORITY_CHANNEL_SELECT;
    static const QStringList SCAN_LIST_PRIORITY_CHANNEL;
    static const QStringList SCAN_LIST_REVERT_CHANNEL;
    static const QStringList SCAN_LIST_LOOK_BACK_TIME;
    static const QStringList SCAN_LIST_DROPOUT_DELAY_DWELL_TIME;

    static const QStringList POWERON_INTERFACE;
    static const QStringList AUTOSHUTDOWN;
    static const QStringList POWER_SAVE;
    static const QStringList AUTOSHUTDOWN_TYPE;
    static const QStringList BRIGHTNESS;
    static const QStringList AUTO_BACKLIGHT_DURATION;
    static const QStringList BACKLIGHT_DELAY_TX;
    static const QStringList MENU_EXIT_TIME;
    static const QStringList LAST_CALLER;
    static const QStringList CALL_DISPLAY_MODE;
    static const QStringList COLOR1;
    static const QStringList COLOR2;
    static const QStringList DISPLAY_CHANNEL_NUMBER;
    static const QStringList DISPLAY_STANDBY_PICTURE;
    static const QStringList BACKLIGHT_DELAY_RX;
    static const QStringList DATE_DISPLAY_FORMAT;

    static const QStringList DISPLAY_MODE;
    static const QStringList MAIN_CHANNEL_SET;
    static const QStringList WORKING_MODE;

    static const QStringList VOX_LEVEL;
    static const QStringList VOX_DELAY;
    static const QStringList VOX_DETECTION;
    static const QStringList BT_GAIN;
    static const QStringList BT_HOLD_TIME;
    static const QStringList BT_RX_DELAY;
    static const QStringList BT_PTT_SLEEP;

    static const QStringList STE_CTCSS_TYPE;
    static const QStringList STE_NO_SIGNAL;
    static const QStringList STE_TIME;

    static const QStringList KEY_LOCK;
    static const QStringList KEY_FUNCTION;
    static const QStringList LONG_KEY_TIME;

    static const QStringList TOT;
    static const QStringList LANGUAGE;
    static const QStringList FREQUENCY_STEP;
    static const QStringList SQL_LEVEL;
    static const QStringList TBST;
    static const QStringList ANALOG_CALL_HOLD_TIME;
    static const QStringList MUTE_TIMING;
    static const QStringList ENCRYPTION_TYPE;

    static const QStringList TG_HOLD_TIME;
    static const QStringList VOICE_HEADER_REPETITIONS;
    static const QStringList TX_PREAMBLE_DURATION;
    static const QStringList DIGITAL_MONITOR;
    static const QStringList DIGITAL_MONITOR_CC;
    static const QStringList SMS_FORMAT;

    static const QStringList ALERT;
    static const QStringList TALK_PERMIT;
    static const QStringList DIGITAL_IDLE_TONE;
    static const QStringList KEY_TONE_SOUND_ADJUSTABLE;

    static const QStringList TIME_ZONE;
    static const QStringList RANGING_INTERVAL;
    static const QStringList DISTANCE_UNIT;
    static const QStringList GPS_MODE;

    static const QStringList AUTO_REPEATER_ENABLED;
    static const QStringList AUTO_REPEATER_INTERVALS;
    static const QStringList REPEATER_OUT_OF_RANGE_NOTIFY;
    static const QStringList AUTO_ROAMING_START_CONDITION;
    static const QStringList ROAMING_EFFECT_WAIT_TIME;

    static const QStringList VFO_SCAN_TYPE;

    static const QStringList MAX_VOLUME;
    static const QStringList MIC_GAIN;

    static const QStringList ROAMING_CHANNEL_COLOR_CODE;
    static const QStringList ROAMING_CHANNEL_SLOT;

    static const QStringList FM_SCAN;

    static const QStringList ANALOG_EMERGENCY_ALARM;
    static const QStringList ANALOG_EMERGENCY_ENI_SELECT;
    static const QStringList ALARM_DURATION;
    static const QStringList ENI_SEND_SELECT;
    static const QStringList WORK_ALONE_VOICE_SWITCH;
    static const QStringList WORK_ALONE_AREA_SWITCH;
    static const QStringList WORK_ALONE_MIC_SWITCH;
    static const QStringList DIGITAL_EMERGENCY_ALARM;
    static const QStringList MAN_DOWN_DELAY;
    static const QStringList APRS_ALT_DATA;
    static const QStringList DTMF_TX_TIME;
    static const QStringList TONE_INTERVAL_CHARACTER;
    static const QStringList DECODING_RESPONSE;
    static const QStringList DECODING_STANDARD;
    static const QStringList FUNCTION_OPTION;
    static const QStringList DECODING_STANDARD_DESC;
    static const QStringList RADIO_MODE_BAND;

    static const QStringList TALKALIAS_DISPLAY_PRIORITY_878;
    static const QStringList TALKALIAS_DISPLAY_PRIORITY_890;
    static const QStringList TALKALIAS_DATA_FORMAT;

    
    
};

#endif