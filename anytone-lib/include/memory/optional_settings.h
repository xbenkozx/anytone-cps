#ifndef ANYTONE_OPTIONAL_SETTINGS_H
#define ANYTONE_OPTIONAL_SETTINGS_H

#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "utils.h"
#include "int.h"

namespace Anytone {
    class OptionalSettings {
    public:
        OptionalSettings(){
            poweron_display_1 = QByteArray(14, 0);
            poweron_display_2 = QByteArray(14, 0);
        }
        ~OptionalSettings(){}

        void decode_D878UVII(QByteArray data_2500000, QByteArray data_2500600, QByteArray data_2501280, QByteArray data_2501400);
        void decode_D890UV(QByteArray data_3500000, QByteArray data_3500900, QByteArray data_3501280);
        void encode(QByteArray &data_2500000, QByteArray &data_2500600, QByteArray &data_2501280, QByteArray &data_2501400);

        void save(QXmlStreamWriter &xml);
        void load(QXmlStreamReader &xml);

        // Power-on
        uint8_t poweron_interface = 0;
        QByteArray poweron_display_1;
        QByteArray poweron_display_2;
        uint8_t poweron_password = 0;
        QString poweron_password_char = "";
        uint8_t default_startup_channel = 0;
        uint8_t startup_zone_a = 0;
        uint8_t startup_channel_a = 0;
        uint8_t startup_zone_b = 0;
        uint8_t startup_channel_b = 0;
        uint8_t startup_gps_test = 0;
        uint8_t startup_reset = 0;

        // Power Save
        uint8_t auto_shutdown = 0;
        uint8_t power_save = 0;
        uint8_t auto_shutdown_type = 0;

        // Display
        uint8_t brightness = 0;
        uint8_t auto_backlight_duration = 0;
        uint8_t backlight_tx_delay = 0;
        uint8_t menu_exit_time = 0;
        uint8_t time_display = 0;
        uint8_t last_caller = 0;
        uint8_t call_display_mode = 0;
        uint8_t callsign_display_color = 0;
        uint8_t call_end_prompt_box = 0;
        uint8_t display_channel_number = 0;
        uint8_t display_current_contact = 0;
        uint8_t standby_char_color = 0;
        uint8_t standby_bk_picture = 0;
        uint8_t show_last_call_on_launch = 0;
        uint8_t separate_display = 0;
        uint8_t ch_switching_keeps_caller = 0;
        uint8_t backlight_rx_delay = 0;
        uint8_t channel_name_color_a = 0;
        uint8_t channel_name_color_b = 0;
        uint8_t zone_name_color_a = 0;
        uint8_t zone_name_color_b = 0;
        uint8_t display_channel_type = 0;
        uint8_t display_time_slot = 0;
        uint8_t display_color_code = 0;
        uint8_t date_display_format = 0;
        uint8_t volume_bar = 0;

        // Work Mode
        uint8_t display_mode = 0;
        uint8_t vf_mr_a = 0;
        uint8_t vf_mr_b = 0;
        uint8_t mem_zone_a = 0;
        uint8_t mem_zone_b = 0;
        uint8_t main_channel_set = 0;
        uint8_t sub_channel_mode = 0;
        uint8_t working_mode = 0;

        // Vox/BT
        uint8_t vox_level = 0;
        uint8_t vox_delay = 0;
        uint8_t vox_detection = 0;
        uint8_t bt_on_off_D878UVII = 0;
        uint8_t bt_on_off_D890UV = 0;
        uint8_t bt_int_mic = 0;
        uint8_t bt_int_spk = 0;
        uint8_t bt_mic_gain = 0;
        uint8_t bt_spk_gain = 0;
        uint8_t bt_hold_time = 0;
        uint8_t bt_rx_delay = 0;
        uint8_t bt_ptt_hold = 0;
        uint8_t bt_ptt_sleep_time = 0;
        uint8_t bt_nr_before = 0;
        uint8_t bt_nr_after = 0;

        // STE
        uint8_t ste_type_of_ctcss = 0;
        uint8_t ste_when_no_signal = 0;
        uint8_t ste_time = 0;

        // AM/FM
        uint8_t am_fm_function = 0;
        uint8_t fm_vfo_mem = 0;
        uint8_t fm_work_channel = 0;
        uint8_t fm_monitor = 0;
        uint8_t am_vfo_mem = 0;
        uint8_t am_work_zone = 0;
        uint8_t am_offset = 0;
        uint8_t am_sql_level = 0;

        // Key Function
        uint8_t key_lock = 0;
        uint8_t pf1_short_key_D878UVII = 0;
        uint8_t pf2_short_key_D878UVII = 0;
        uint8_t pf3_short_key_D878UVII = 0;
        uint8_t p1_short_key_D878UVII = 0;
        uint8_t p2_short_key_D878UVII = 0;
        uint8_t pf1_long_key_D878UVII = 0;
        uint8_t pf2_long_key_D878UVII = 0;
        uint8_t pf3_long_key_D878UVII = 0;
        uint8_t p1_long_key_D878UVII = 0;
        uint8_t p2_long_key_D878UVII = 0;
        uint8_t pf1_short_key_D890UV = 0;
        uint8_t pf2_short_key_D890UV = 0;
        uint8_t pf3_short_key_D890UV = 0;
        uint8_t p1_short_key_D890UV = 0;
        uint8_t p2_short_key_D890UV = 0;
        uint8_t pf1_long_key_D890UV = 0;
        uint8_t pf2_long_key_D890UV = 0;
        uint8_t pf3_long_key_D890UV = 0;
        uint8_t p1_long_key_D890UV = 0;
        uint8_t p2_long_key_D890UV = 0;
        uint8_t long_key_time = 0;
        uint8_t knob_lock = 0;
        uint8_t keyboard_lock = 0;
        uint8_t side_key_lock = 0;
        uint8_t forced_key_lock = 0;

        // Other
        uint8_t address_book_sent_with_code = 0;
        uint8_t tot = 0;
        uint8_t language = 0;
        uint8_t frequency_step = 0;
        uint8_t sql_level_a = 0;
        uint8_t sql_level_b = 0;
        uint8_t tbst = 0;
        uint8_t analog_call_hold_time = 0;
        uint8_t call_channel_maintained = 0;
        uint8_t priority_zone_a = 0;
        uint8_t priority_zone_b = 0;
        uint8_t mute_timing = 0;
        uint8_t encryption_type = 0;
        uint8_t tot_predict = 0;
        uint8_t tx_power_agc = 0;
        uint8_t noaa_moni = 0;
        uint8_t noaa_scan = 0;
        uint8_t noaa = 0;
        uint8_t noaa_channel = 0;

        // Digital Func
        uint8_t group_call_hold_time = 0;
        uint8_t private_call_hold_time = 0;
        uint8_t manual_dial_group_call_hold_time = 0;
        uint8_t manual_dial_private_call_hold_time = 0;
        uint8_t voice_header_repetitions = 0;
        uint8_t tx_preamble_duration = 0;
        uint8_t filter_own_id = 0;
        uint8_t digital_remote_kill = 0;
        uint8_t digital_monitor = 0;
        uint8_t digital_monitor_cc = 0;
        uint8_t digital_monitor_id = 0;
        uint8_t monitor_slot_hold = 0;
        uint8_t remote_monitor = 0;
        uint8_t sms_format = 0;
        uint8_t digital_protocol = 0;
        uint8_t reset_digital_protocol = 0;

        // Alert Tone
        uint8_t sms_alert = 0;
        uint8_t call_alert = 0;
        uint8_t digi_call_reset_tone = 0;
        uint8_t talk_permit = 0;
        uint8_t key_tone = 0;
        uint8_t digi_idle_channel_tone = 0;
        uint8_t startup_sound = 0;
        uint8_t tone_key_sound_adjustable = 0;
        uint8_t analog_idle_channel_tone = 0;
        uint8_t plugin_recording_tone = 0;
        uint32_t call_permit_first_tone_freq = 0;
        uint32_t call_permit_first_tone_period = 0;
        uint32_t call_permit_second_tone_freq = 0;
        uint32_t call_permit_second_tone_period = 0;
        uint32_t call_permit_third_tone_freq = 0;
        uint32_t call_permit_third_tone_period = 0;
        uint32_t call_permit_fourth_tone_freq = 0;
        uint32_t call_permit_fourth_tone_period = 0;
        uint32_t call_permit_fifth_tone_freq = 0;
        uint32_t call_permit_fifth_tone_period = 0;
        uint32_t idle_channel_first_tone_freq = 0;
        uint32_t idle_channel_first_tone_period = 0;
        uint32_t idle_channel_second_tone_freq = 0;
        uint32_t idle_channel_second_tone_period = 0;
        uint32_t idle_channel_third_tone_freq = 0;
        uint32_t idle_channel_third_tone_period = 0;
        uint32_t idle_channel_fourth_tone_freq = 0;
        uint32_t idle_channel_fourth_tone_period = 0;
        uint32_t idle_channel_fifth_tone_freq = 0;
        uint32_t idle_channel_fifth_tone_period = 0;
        uint32_t call_reset_first_tone_freq = 0;
        uint32_t call_reset_first_tone_period = 0;
        uint32_t call_reset_second_tone_freq = 0;
        uint32_t call_reset_second_tone_period = 0;
        uint32_t call_reset_third_tone_freq = 0;
        uint32_t call_reset_third_tone_period = 0;
        uint32_t call_reset_fourth_tone_freq = 0;
        uint32_t call_reset_fourth_tone_period = 0;
        uint32_t call_reset_fifth_tone_freq = 0;
        uint32_t call_reset_fifth_tone_period = 0;

        // Alert Tone 1
        uint32_t call_end_first_tone_freq = 0;
        uint32_t call_end_first_tone_period = 0;
        uint32_t call_end_second_tone_freq = 0;
        uint32_t call_end_second_tone_period = 0;
        uint32_t call_end_third_tone_freq = 0;
        uint32_t call_end_third_tone_period = 0;
        uint32_t call_end_fourth_tone_freq = 0;
        uint32_t call_end_fourth_tone_period = 0;
        uint32_t call_end_fifth_tone_freq = 0;
        uint32_t call_end_fifth_tone_period = 0;
        uint32_t call_all_first_tone_freq = 0;
        uint32_t call_all_first_tone_period = 0;
        uint32_t call_all_second_tone_freq = 0;
        uint32_t call_all_second_tone_period = 0;
        uint32_t call_all_third_tone_freq = 0;
        uint32_t call_all_third_tone_period = 0;
        uint32_t call_all_fourth_tone_freq = 0;
        uint32_t call_all_fourth_tone_period = 0;
        uint32_t call_all_fifth_tone_freq = 0;
        uint32_t call_all_fifth_tone_period = 0;

        // GPS/Ranging
        uint8_t gps_power = 0;
        uint8_t gps_positioning = 0;
        uint8_t time_zone = 0;
        uint8_t ranging_interval = 0;
        uint8_t distance_unit = 0;
        uint8_t gps_template_information = 0;
        QString gps_information_char = "";
        uint8_t gps_mode = 0;
        uint8_t gps_roaming = 0;

        // VFO Scan
        uint8_t vfo_scan_type = 0;
        uint32_t vfo_scan_start_freq_uhf = 0;
        uint32_t vfo_scan_end_freq_uhf = 0;
        uint32_t vfo_scan_start_freq_vhf = 0;
        uint32_t vfo_scan_end_freq_vhf = 0;

        // Auto Repeater
        uint8_t auto_repeater_a = 0;
        uint8_t auto_repeater_b = 0;
        uint8_t auto_repeater_1_uhf = 0xff;
        uint8_t auto_repeater_1_vhf = 0xff;
        uint8_t auto_repeater_2_uhf = 0xff;
        uint8_t auto_repeater_2_vhf = 0xff;
        uint8_t repeater_check = 0;
        uint8_t repeater_check_interval = 0;
        uint8_t repeater_check_reconnections = 0;
        uint8_t repeater_out_of_range_notify = 0;
        uint8_t out_of_range_notify = 0;
        uint8_t auto_roaming = 0;
        uint8_t auto_roaming_start_condition = 0;
        uint8_t auto_roaming_fixed_time = 0;
        uint8_t roaming_effect_wait_time = 0;
        uint8_t roaming_zone = 0;
        uint32_t auto_repeater_1_min_freq_vhf = 0;
        uint32_t auto_repeater_1_max_freq_vhf = 0;
        uint32_t auto_repeater_1_min_freq_uhf = 0;
        uint32_t auto_repeater_1_max_freq_uhf = 0;
        uint32_t auto_repeater_2_min_freq_vhf = 0;
        uint32_t auto_repeater_2_max_freq_vhf = 0;
        uint32_t auto_repeater_2_min_freq_uhf = 0;
        uint32_t auto_repeater_2_max_freq_uhf = 0;
        uint8_t repeater_mode = 0;
        uint8_t rep_cc_limit = 0;
        uint8_t rep_slot_a = 0;
        uint8_t rep_slot_b = 0;

        // Record
        uint8_t record_function = 0;
        uint8_t record_delay = 0;

        // Volume/Audio
        uint8_t max_volume = 0;
        uint8_t max_headphone_volume = 0;
        uint8_t digi_mic_gain = 0;
        uint8_t enhanced_sound_quality = 0;
        uint8_t analog_mic_gain = 0;
        uint8_t power_on_volume_type = 0;
        uint8_t power_on_volume = 0;
        uint8_t rx_agc = 0;
        uint8_t nx_mic_gain = 0;

        // Satellite
        uint8_t sat_location = 0;
        uint8_t sat_tx_power = 0;
        uint8_t sat_ana_sql = 0;
        uint8_t sat_aos_limit = 0;
        
    };
}

#endif