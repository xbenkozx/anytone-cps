#include "optional_settings.h"

void Anytone::OptionalSettings::decode_D878UVII(QByteArray data_0000, QByteArray data_0600, QByteArray data_1280, QByteArray data_1400){
    poweron_interface = static_cast<uint8_t>(data_0000.at(0x6));
    poweron_display_1 = data_0600.mid(0x0, 0xe);
    poweron_display_2 = data_0600.mid(0x10, 0xe);
    poweron_password = static_cast<uint8_t>(data_0000.at(0x7));
    poweron_password_char = QString(data_0600.mid(0x20, 0x8));
    default_startup_channel = static_cast<uint8_t>(data_0000.at(0xd7));
    startup_zone_a = static_cast<uint8_t>(data_0000.at(0xd8));
    startup_channel_a = static_cast<uint8_t>(data_0000.at(0xda));
    startup_zone_b = static_cast<uint8_t>(data_0000.at(0xd9));
    startup_channel_b = static_cast<uint8_t>(data_0000.at(0xdb));
    startup_gps_test = static_cast<uint8_t>(data_0000.at(0xeb));
    startup_reset = static_cast<uint8_t>(data_0000.at(0xec));

    auto_shutdown = static_cast<uint8_t>(data_0000.at(0x3));
    power_save = static_cast<uint8_t>(data_0000.at(0xb));
    auto_shutdown_type = static_cast<uint8_t>(data_0000.at(0x3f));

    brightness = static_cast<uint8_t>(data_0000.at(0x26));
    auto_backlight_duration = static_cast<uint8_t>(data_0000.at(0x27));
    backlight_tx_delay = static_cast<uint8_t>(data_0000.at(0xe1));
    menu_exit_time = static_cast<uint8_t>(data_0000.at(0x37));
    time_display = static_cast<uint8_t>(data_0000.at(0x51));
    last_caller = static_cast<uint8_t>(data_0000.at(0x4d));
    call_display_mode = static_cast<uint8_t>(data_0000.at(0xaf));
    callsign_display_color = static_cast<uint8_t>(data_0000.at(0xbc));
    call_end_prompt_box = static_cast<uint8_t>(data_0000.at(0x3a));
    display_channel_number = static_cast<uint8_t>(data_0000.at(0xb8));
    display_current_contact = static_cast<uint8_t>(data_0000.at(0xb9));
    standby_char_color = static_cast<uint8_t>(data_0000.at(0xc0));
    standby_bk_picture = static_cast<uint8_t>(data_0000.at(0xc1));
    show_last_call_on_launch = static_cast<uint8_t>(data_0000.at(0xc2));
    separate_display = static_cast<uint8_t>(data_0000.at(0xe2));
    ch_switching_keeps_caller = static_cast<uint8_t>(data_0000.at(0xe3));
    backlight_rx_delay = static_cast<uint8_t>(data_0000.at(0xe6));
    channel_name_color_a = static_cast<uint8_t>(data_0000.at(0xe4));
    channel_name_color_b = static_cast<uint8_t>(data_1400.at(0x39));
    zone_name_color_a = static_cast<uint8_t>(data_1400.at(0x3d));
    zone_name_color_b = static_cast<uint8_t>(data_1400.at(0x3e));
    display_channel_type = Bit::test(data_1400.at(0x40), 0);
    display_time_slot = Bit::test(data_1400.at(0x40), 1);
    display_color_code = Bit::test(data_1400.at(0x40), 2);
    date_display_format = static_cast<uint8_t>(data_1400.at(0x42));
    volume_bar = static_cast<uint8_t>(data_0000.at(0x47));

    display_mode = static_cast<uint8_t>(data_0000.at(0x01));
    vf_mr_a = static_cast<uint8_t>(data_0000.at(0x15));
    vf_mr_b = static_cast<uint8_t>(data_0000.at(0x16));
    mem_zone_a = static_cast<uint8_t>(data_0000.at(0x1f));
    mem_zone_b = static_cast<uint8_t>(data_0000.at(0x20));
    main_channel_set = static_cast<uint8_t>(data_0000.at(0x2c));
    sub_channel_mode = static_cast<uint8_t>(data_0000.at(0x2d));
    working_mode = static_cast<uint8_t>(data_0000.at(0x34));
    vox_level = static_cast<uint8_t>(data_0000.at(0x0c));
    vox_delay = static_cast<uint8_t>(data_0000.at(0x0d));
    vox_detection = static_cast<uint8_t>(data_0000.at(0x33));
    bt_on_off_D878UVII = static_cast<uint8_t>(data_0000.at(0xb1));
    bt_int_mic = static_cast<uint8_t>(data_0000.at(0xb2));
    bt_int_spk = static_cast<uint8_t>(data_0000.at(0xb3));
    bt_mic_gain = static_cast<uint8_t>(data_0000.at(0xb6));
    bt_spk_gain = static_cast<uint8_t>(data_0000.at(0xb7));
    bt_hold_time = static_cast<uint8_t>(data_0000.at(0xed));
    bt_rx_delay = static_cast<uint8_t>(data_0000.at(0xee));
    bt_ptt_hold = static_cast<uint8_t>(data_1400.at(0x21));
    bt_ptt_sleep_time = static_cast<uint8_t>(data_1400.at(0x34));

    ste_type_of_ctcss = static_cast<uint8_t>(data_0000.at(0x17));
    ste_when_no_signal = static_cast<uint8_t>(data_0000.at(0x18));
    ste_time = static_cast<uint8_t>(data_1400.at(0x36));

    fm_vfo_mem = static_cast<uint8_t>(data_0000.at(0x1e));
    fm_work_channel = static_cast<uint8_t>(data_0000.at(0x1d));
    fm_monitor = static_cast<uint8_t>(data_0000.at(0x2b));

    key_lock = static_cast<uint8_t>(data_0000.at(0x02));
    pf1_short_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x10));
    pf2_short_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x11));
    pf3_short_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x12));
    p1_short_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x13));
    p2_short_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x14));
    pf1_long_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x41));
    pf2_long_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x42));
    pf3_long_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x43));
    p1_long_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x44));
    p2_long_key_D878UVII = static_cast<uint8_t>(data_0000.at(0x45));
    long_key_time = static_cast<uint8_t>(data_0000.at(0x46));
    knob_lock = Bit::test(data_0000.at(0xbe), 0);
    keyboard_lock = Bit::test(data_0000.at(0xbe), 1);
    side_key_lock = Bit::test(data_0000.at(0xbe), 3);
    forced_key_lock = Bit::test(data_0000.at(0xbe), 4);

    address_book_sent_with_code = static_cast<uint8_t>(data_0000.at(0xd5));
    tot = static_cast<uint8_t>(data_0000.at(0x04));
    language = static_cast<uint8_t>(data_0000.at(0x05));
    frequency_step = static_cast<uint8_t>(data_0000.at(0x08));
    sql_level_a = static_cast<uint8_t>(data_0000.at(0x09));
    sql_level_b = static_cast<uint8_t>(data_0000.at(0x0a));
    tbst = static_cast<uint8_t>(data_0000.at(0x2e));
    analog_call_hold_time = static_cast<uint8_t>(data_0000.at(0x50));
    call_channel_maintained = static_cast<uint8_t>(data_0000.at(0x6e));
    priority_zone_a = static_cast<uint8_t>(data_0000.at(0x6f));
    priority_zone_b = static_cast<uint8_t>(data_0000.at(0x70));
    mute_timing = static_cast<uint8_t>(data_0000.at(0xe9));
    encryption_type = static_cast<uint8_t>(data_1400.at(0x3a));
    tot_predict = static_cast<uint8_t>(data_1400.at(0x3b));
    tx_power_agc = static_cast<uint8_t>(data_1400.at(0x3c));

    priority_zone_a = (priority_zone_a < 255?priority_zone_a+1:0);
    priority_zone_b = (priority_zone_b < 255?priority_zone_b+1:0);

    group_call_hold_time = static_cast<uint8_t>(data_0000.at(0x19));
    private_call_hold_time = static_cast<uint8_t>(data_0000.at(0x1a));
    manual_dial_group_call_hold_time = static_cast<uint8_t>(data_1400.at(0x37));
    manual_dial_private_call_hold_time = static_cast<uint8_t>(data_1400.at(0x38));
    voice_header_repetitions = static_cast<uint8_t>(data_1400.at(0x6e));
    tx_preamble_duration = static_cast<uint8_t>(data_0000.at(0x1c));
    filter_own_id = static_cast<uint8_t>(data_0000.at(0x38));
    digital_remote_kill = static_cast<uint8_t>(data_0000.at(0x3c));
    digital_monitor = static_cast<uint8_t>(data_0000.at(0x49));
    digital_monitor_cc = static_cast<uint8_t>(data_0000.at(0x4a));
    digital_monitor_id = static_cast<uint8_t>(data_0000.at(0x4b));
    monitor_slot_hold = static_cast<uint8_t>(data_0000.at(0x4c));
    remote_monitor = static_cast<uint8_t>(data_0000.at(0x3e));
    sms_format = static_cast<uint8_t>(data_0000.at(0xc3));

    sms_alert = static_cast<uint8_t>(data_0000.at(0x29));
    call_alert = static_cast<uint8_t>(data_0000.at(0x2f));
    digi_call_reset_tone = static_cast<uint8_t>(data_0000.at(0x32));
    talk_permit = static_cast<uint8_t>(data_0000.at(0x31));
    key_tone = static_cast<uint8_t>(data_0000.at(0x00));
    digi_idle_channel_tone = static_cast<uint8_t>(data_0000.at(0x36));
    startup_sound = static_cast<uint8_t>(data_0000.at(0x39));
    tone_key_sound_adjustable = static_cast<uint8_t>(data_0000.at(0xbb));
    analog_idle_channel_tone = static_cast<uint8_t>(data_1400.at(0x41));
    plugin_recording_tone = static_cast<uint8_t>(data_0000.at(0xb4));
    call_permit_first_tone_freq = Int::fromBytes(data_0000.mid(0x72,2));
    call_permit_first_tone_period = Int::fromBytes(data_0000.mid(0x7c,2));
    call_permit_second_tone_freq = Int::fromBytes(data_0000.mid(0x74,2));
    call_permit_second_tone_period = Int::fromBytes(data_0000.mid(0x7e,2));
    call_permit_third_tone_freq = Int::fromBytes(data_0000.mid(0x76,2));
    call_permit_third_tone_period = Int::fromBytes(data_0000.mid(0x80,2));
    call_permit_fourth_tone_freq = Int::fromBytes(data_0000.mid(0x78,2));
    call_permit_fourth_tone_period = Int::fromBytes(data_0000.mid(0x82,2));
    call_permit_fifth_tone_freq = Int::fromBytes(data_0000.mid(0x7a,2));
    call_permit_fifth_tone_period = Int::fromBytes(data_0000.mid(0x84,2));
    idle_channel_first_tone_freq = Int::fromBytes(data_0000.mid(0x86,2));
    idle_channel_first_tone_period = Int::fromBytes(data_0000.mid(0x90,2));
    idle_channel_second_tone_freq = Int::fromBytes(data_0000.mid(0x88,2));
    idle_channel_second_tone_period = Int::fromBytes(data_0000.mid(0x92,2));
    idle_channel_third_tone_freq = Int::fromBytes(data_0000.mid(0x8a,2));
    idle_channel_third_tone_period = Int::fromBytes(data_0000.mid(0x94,2));
    idle_channel_fourth_tone_freq = Int::fromBytes(data_0000.mid(0x8c,2));
    idle_channel_fourth_tone_period = Int::fromBytes(data_0000.mid(0x96,2));
    idle_channel_fifth_tone_freq = Int::fromBytes(data_0000.mid(0x8e,2));
    idle_channel_fifth_tone_period = Int::fromBytes(data_0000.mid(0x98,2));
    call_reset_first_tone_freq = Int::fromBytes(data_0000.mid(0x9a,2));
    call_reset_first_tone_period = Int::fromBytes(data_0000.mid(0xa4,2));
    call_reset_second_tone_freq = Int::fromBytes(data_0000.mid(0x9c,2));
    call_reset_second_tone_period = Int::fromBytes(data_0000.mid(0xa6,2));
    call_reset_third_tone_freq = Int::fromBytes(data_0000.mid(0x9e,2));
    call_reset_third_tone_period = Int::fromBytes(data_0000.mid(0xa8,2));
    call_reset_fourth_tone_freq = Int::fromBytes(data_0000.mid(0xa0,2));
    call_reset_fourth_tone_period = Int::fromBytes(data_0000.mid(0xaa,2));
    call_reset_fifth_tone_freq = Int::fromBytes(data_0000.mid(0xa2,2));
    call_reset_fifth_tone_period = Int::fromBytes(data_0000.mid(0xac,2));

    call_end_first_tone_freq = Int::fromBytes(data_1400.mid(0x46,2));
    call_end_first_tone_period = Int::fromBytes(data_1400.mid(0x50,2));
    call_end_second_tone_freq = Int::fromBytes(data_1400.mid(0x48,2));
    call_end_second_tone_period = Int::fromBytes(data_1400.mid(0x52,2));
    call_end_third_tone_freq = Int::fromBytes(data_1400.mid(0x4a,2));
    call_end_third_tone_period = Int::fromBytes(data_1400.mid(0x54,2));
    call_end_fourth_tone_freq = Int::fromBytes(data_1400.mid(0x4c,2));
    call_end_fourth_tone_period = Int::fromBytes(data_1400.mid(0x56,2));
    call_end_fifth_tone_freq = Int::fromBytes(data_1400.mid(0x4e,2));
    call_end_fifth_tone_period = Int::fromBytes(data_1400.mid(0x58,2));
    call_all_first_tone_freq = Int::fromBytes(data_1400.mid(0x5a,2));
    call_all_first_tone_period = Int::fromBytes(data_1400.mid(0x64,2));
    call_all_second_tone_freq = Int::fromBytes(data_1400.mid(0x5c,2));
    call_all_second_tone_period = Int::fromBytes(data_1400.mid(0x66,2));
    call_all_third_tone_freq = Int::fromBytes(data_1400.mid(0x5e,2));
    call_all_third_tone_period = Int::fromBytes(data_1400.mid(0x68,2));
    call_all_fourth_tone_freq = Int::fromBytes(data_1400.mid(0x60,2));
    call_all_fourth_tone_period = Int::fromBytes(data_1400.mid(0x6a,2));
    call_all_fifth_tone_freq = Int::fromBytes(data_1400.mid(0x62,2));
    call_all_fifth_tone_period = Int::fromBytes(data_1400.mid(0x6c,2));

    gps_power = static_cast<uint8_t>(data_0000.at(0x28));
    gps_positioning = static_cast<uint8_t>(data_0000.at(0x3f));
    time_zone = static_cast<uint8_t>(data_0000.at(0x30));
    ranging_interval = static_cast<uint8_t>(data_0000.at(0xb5));
    distance_unit = static_cast<uint8_t>(data_0000.at(0xbd));
    gps_template_information = static_cast<uint8_t>(data_0000.at(0x53));
    gps_information_char = QString(data_1280.mid(0x0, 0x20));
    gps_mode = static_cast<uint8_t>(data_1400.at(0x35));
    gps_roaming = static_cast<uint8_t>(data_1400.at(0x44));

    vfo_scan_type = static_cast<uint8_t>(data_0000.at(0x0e));
    vfo_scan_start_freq_uhf = Int::fromBytes(data_0000.mid(0x58,4));
    vfo_scan_end_freq_uhf = Int::fromBytes(data_0000.mid(0x5c,4));
    vfo_scan_start_freq_vhf = Int::fromBytes(data_0000.mid(0x60,4));
    vfo_scan_end_freq_vhf = Int::fromBytes(data_0000.mid(0x64,4));

    auto_repeater_a = static_cast<uint8_t>(data_0000.at(0x48));
    auto_repeater_b = static_cast<uint8_t>(data_0000.at(0xd4));
    auto_repeater_1_uhf = static_cast<uint8_t>(data_0000.at(0x68));
    auto_repeater_1_vhf = static_cast<uint8_t>(data_0000.at(0x69));
    auto_repeater_2_uhf = static_cast<uint8_t>(data_1400.at(0x22));
    auto_repeater_2_vhf = static_cast<uint8_t>(data_1400.at(0x23));
    repeater_check = static_cast<uint8_t>(data_0000.at(0xdd));
    repeater_check_interval = static_cast<uint8_t>(data_0000.at(0xde));
    repeater_check_reconnections = static_cast<uint8_t>(data_0000.at(0xdf));
    repeater_out_of_range_notify = static_cast<uint8_t>(data_0000.at(0xe5));
    out_of_range_notify = static_cast<uint8_t>(data_0000.at(0xea));
    auto_roaming = static_cast<uint8_t>(data_0000.at(0xe7));
    auto_roaming_start_condition = static_cast<uint8_t>(data_0000.at(0xe0));
    auto_roaming_fixed_time = static_cast<uint8_t>(data_0000.at(0xba));
    roaming_effect_wait_time = static_cast<uint8_t>(data_0000.at(0xbf));
    roaming_zone = static_cast<uint8_t>(data_0000.at(0xd5));
    auto_repeater_1_min_freq_vhf = Int::fromBytes(data_0000.mid(0xc4,4));
    auto_repeater_1_max_freq_vhf = Int::fromBytes(data_0000.mid(0xc8,4));
    auto_repeater_1_min_freq_uhf = Int::fromBytes(data_0000.mid(0xcc,4));
    auto_repeater_1_max_freq_uhf = Int::fromBytes(data_0000.mid(0xd0,4));
    auto_repeater_2_min_freq_vhf = Int::fromBytes(data_1400.mid(0x24,4));
    auto_repeater_2_max_freq_vhf = Int::fromBytes(data_1400.mid(0x28,4));
    auto_repeater_2_min_freq_uhf = Int::fromBytes(data_1400.mid(0x2c,4));
    auto_repeater_2_max_freq_uhf = Int::fromBytes(data_1400.mid(0x30,4));

    record_function = static_cast<uint8_t>(data_0000.at(0x22));
    max_volume = static_cast<uint8_t>(data_0000.at(0x3b));
    max_headphone_volume = static_cast<uint8_t>(data_0000.at(0x52));
    digi_mic_gain = static_cast<uint8_t>(data_0000.at(0x0f));
    enhanced_sound_quality = static_cast<uint8_t>(data_0000.at(0x57));
    analog_mic_gain = static_cast<uint8_t>(data_1400.at(0x43));

    poweron_password_char.remove(QChar('\0'));
    gps_information_char.remove(QChar('\0'));
}
void Anytone::OptionalSettings::decode_D890UV(
    QByteArray data_3500000, 
    QByteArray data_3500900, 
    QByteArray data_3501280
){
    // Power On
    poweron_interface = static_cast<uint8_t>(data_3500000.at(0x6));
    poweron_display_1 = data_3500900.mid(0x0, 0xe);
    poweron_display_2 = data_3500900.mid(0x10, 0xe);
    poweron_password = static_cast<uint8_t>(data_3500000.at(0x7));
    poweron_password_char = QString(data_3500900.mid(0x20, 0x8));
    default_startup_channel = static_cast<uint8_t>(data_3500000.at(0xd7));
    startup_zone_a = static_cast<uint8_t>(data_3500000.at(0xd8));
    startup_channel_a = static_cast<uint8_t>(data_3500000.at(0xda));
    startup_zone_b = static_cast<uint8_t>(data_3500000.at(0xd9));
    startup_channel_b = static_cast<uint8_t>(data_3500000.at(0xdb));
    startup_gps_test = static_cast<uint8_t>(data_3500000.at(0xeb));
    startup_reset = static_cast<uint8_t>(data_3500000.at(0xec));

    // Alert Tone
    sms_alert = static_cast<uint8_t>(data_3500000.at(0x29));
    call_alert = static_cast<uint8_t>(data_3500000.at(0x2f));
    digi_call_reset_tone = static_cast<uint8_t>(data_3500000.at(0x32));
    talk_permit = static_cast<uint8_t>(data_3500000.at(0x31));
    key_tone = static_cast<uint8_t>(data_3500000.at(0x00));
    digi_idle_channel_tone = static_cast<uint8_t>(data_3500000.at(0x36));
    startup_sound = static_cast<uint8_t>(data_3500000.at(0x39));
    tone_key_sound_adjustable = static_cast<uint8_t>(data_3500000.at(0xbb));
    analog_idle_channel_tone = static_cast<uint8_t>(data_3500000.at(0x111));
    plugin_recording_tone = static_cast<uint8_t>(data_3500000.at(0xb4));
    call_permit_first_tone_freq = Int::fromBytes(data_3500000.mid(0x72,2));
    call_permit_first_tone_period = Int::fromBytes(data_3500000.mid(0x7c,2));
    call_permit_second_tone_freq = Int::fromBytes(data_3500000.mid(0x74,2));
    call_permit_second_tone_period = Int::fromBytes(data_3500000.mid(0x7e,2));
    call_permit_third_tone_freq = Int::fromBytes(data_3500000.mid(0x76,2));
    call_permit_third_tone_period = Int::fromBytes(data_3500000.mid(0x80,2));
    call_permit_fourth_tone_freq = Int::fromBytes(data_3500000.mid(0x78,2));
    call_permit_fourth_tone_period = Int::fromBytes(data_3500000.mid(0x82,2));
    call_permit_fifth_tone_freq = Int::fromBytes(data_3500000.mid(0x7a,2));
    call_permit_fifth_tone_period = Int::fromBytes(data_3500000.mid(0x84,2));
    idle_channel_first_tone_freq = Int::fromBytes(data_3500000.mid(0x86,2));
    idle_channel_first_tone_period = Int::fromBytes(data_3500000.mid(0x90,2));
    idle_channel_second_tone_freq = Int::fromBytes(data_3500000.mid(0x88,2));
    idle_channel_second_tone_period = Int::fromBytes(data_3500000.mid(0x92,2));
    idle_channel_third_tone_freq = Int::fromBytes(data_3500000.mid(0x8a,2));
    idle_channel_third_tone_period = Int::fromBytes(data_3500000.mid(0x94,2));
    idle_channel_fourth_tone_freq = Int::fromBytes(data_3500000.mid(0x8c,2));
    idle_channel_fourth_tone_period = Int::fromBytes(data_3500000.mid(0x96,2));
    idle_channel_fifth_tone_freq = Int::fromBytes(data_3500000.mid(0x8e,2));
    idle_channel_fifth_tone_period = Int::fromBytes(data_3500000.mid(0x98,2));
    call_reset_first_tone_freq = Int::fromBytes(data_3500000.mid(0x9a,2));
    call_reset_first_tone_period = Int::fromBytes(data_3500000.mid(0xa4,2));
    call_reset_second_tone_freq = Int::fromBytes(data_3500000.mid(0x9c,2));
    call_reset_second_tone_period = Int::fromBytes(data_3500000.mid(0xa6,2));
    call_reset_third_tone_freq = Int::fromBytes(data_3500000.mid(0x9e,2));
    call_reset_third_tone_period = Int::fromBytes(data_3500000.mid(0xa8,2));
    call_reset_fourth_tone_freq = Int::fromBytes(data_3500000.mid(0xa0,2));
    call_reset_fourth_tone_period = Int::fromBytes(data_3500000.mid(0xaa,2));
    call_reset_fifth_tone_freq = Int::fromBytes(data_3500000.mid(0xa2,2));
    call_reset_fifth_tone_period = Int::fromBytes(data_3500000.mid(0xac,2));

    call_end_first_tone_freq = Int::fromBytes(data_3500000.mid(0x116,2));
    call_end_first_tone_period = Int::fromBytes(data_3500000.mid(0x120,2));
    call_end_second_tone_freq = Int::fromBytes(data_3500000.mid(0x118,2));
    call_end_second_tone_period = Int::fromBytes(data_3500000.mid(0x122,2));
    call_end_third_tone_freq = Int::fromBytes(data_3500000.mid(0x11a,2));
    call_end_third_tone_period = Int::fromBytes(data_3500000.mid(0x124,2));
    call_end_fourth_tone_freq = Int::fromBytes(data_3500000.mid(0x11c,2));
    call_end_fourth_tone_period = Int::fromBytes(data_3500000.mid(0x126,2));
    call_end_fifth_tone_freq = Int::fromBytes(data_3500000.mid(0x11e,2));
    call_end_fifth_tone_period = Int::fromBytes(data_3500000.mid(0x128,2));

    call_all_first_tone_freq = Int::fromBytes(data_3500000.mid(0x12a,2));
    call_all_first_tone_period = Int::fromBytes(data_3500000.mid(0x134,2));
    call_all_second_tone_freq = Int::fromBytes(data_3500000.mid(0x12c,2));
    call_all_second_tone_period = Int::fromBytes(data_3500000.mid(0x136,2));
    call_all_third_tone_freq = Int::fromBytes(data_3500000.mid(0x12e,2));
    call_all_third_tone_period = Int::fromBytes(data_3500000.mid(0x138,2));
    call_all_fourth_tone_freq = Int::fromBytes(data_3500000.mid(0x130,2));
    call_all_fourth_tone_period = Int::fromBytes(data_3500000.mid(0x13a,2));
    call_all_fifth_tone_freq = Int::fromBytes(data_3500000.mid(0x132,2));
    call_all_fifth_tone_period = Int::fromBytes(data_3500000.mid(0x13c,2));

    // Display
    brightness = static_cast<uint8_t>(data_3500000.at(0x26));
    auto_backlight_duration = static_cast<uint8_t>(data_3500000.at(0x27));
    backlight_tx_delay = static_cast<uint8_t>(data_3500000.at(0xe1));
    menu_exit_time = static_cast<uint8_t>(data_3500000.at(0x37));
    time_display = static_cast<uint8_t>(data_3500000.at(0x51));
    last_caller = static_cast<uint8_t>(data_3500000.at(0x4d));
    call_display_mode = static_cast<uint8_t>(data_3500000.at(0xaf));
    callsign_display_color = static_cast<uint8_t>(data_3500000.at(0xbc));
    call_end_prompt_box = static_cast<uint8_t>(data_3500000.at(0x3a));
    display_channel_number = static_cast<uint8_t>(data_3500000.at(0xb8));
    display_current_contact = static_cast<uint8_t>(data_3500000.at(0xb9));
    standby_char_color = static_cast<uint8_t>(data_3500000.at(0xc0));
    standby_bk_picture = static_cast<uint8_t>(data_3500000.at(0xc1));
    show_last_call_on_launch = static_cast<uint8_t>(data_3500000.at(0xc2));
    separate_display = static_cast<uint8_t>(data_3500000.at(0xe1));
    ch_switching_keeps_caller = static_cast<uint8_t>(data_3500000.at(0xe2));
    backlight_rx_delay = static_cast<uint8_t>(data_3500000.at(0xe5));
    channel_name_color_a = static_cast<uint8_t>(data_3500000.at(0xe3));
    channel_name_color_b = static_cast<uint8_t>(data_3500000.at(0x109));
    zone_name_color_a = static_cast<uint8_t>(data_3500000.at(0x10d));
    zone_name_color_b = static_cast<uint8_t>(data_3500000.at(0x10e));
    display_channel_type = Bit::test(data_3500000.at(0x110), 0);
    display_time_slot = Bit::test(data_3500000.at(0x110), 1);
    display_color_code = Bit::test(data_3500000.at(0x110), 2);
    date_display_format = static_cast<uint8_t>(data_3500000.at(0x112));
    volume_bar = static_cast<uint8_t>(data_3500000.at(0x47));

    // GPS/Ranging
    gps_power = static_cast<uint8_t>(data_3500000.at(0x28));
    gps_positioning = static_cast<uint8_t>(data_3500000.at(0x3f));
    time_zone = static_cast<uint8_t>(data_3500000.at(0x30));
    ranging_interval = static_cast<uint8_t>(data_3500000.at(0xb5));
    distance_unit = static_cast<uint8_t>(data_3500000.at(0xbd));
    gps_template_information = static_cast<uint8_t>(data_3500000.at(0x53));
    gps_information_char = QString(data_3501280.mid(0x0, 0x30));
    gps_mode = static_cast<uint8_t>(data_3500000.at(0x105));
    gps_roaming = static_cast<uint8_t>(data_3500000.at(0x114));

    // VFO Scan
    vfo_scan_type = static_cast<uint8_t>(data_3500000.at(0x0e));
    vfo_scan_start_freq_uhf = Int::fromBytes(data_3500000.mid(0x58,4));
    vfo_scan_end_freq_uhf = Int::fromBytes(data_3500000.mid(0x5c,4));
    vfo_scan_start_freq_vhf = Int::fromBytes(data_3500000.mid(0x60,4));
    vfo_scan_end_freq_vhf = Int::fromBytes(data_3500000.mid(0x64,4));

    // Auto Repeater
    auto_repeater_a = static_cast<uint8_t>(data_3500000.at(0x48));
    auto_repeater_b = static_cast<uint8_t>(data_3500000.at(0xd4));
    auto_repeater_1_uhf = static_cast<uint8_t>(data_3500000.at(0x68));
    auto_repeater_1_vhf = static_cast<uint8_t>(data_3500000.at(0x69));
    auto_repeater_2_uhf = static_cast<uint8_t>(data_3500000.at(0xf1));
    auto_repeater_2_vhf = static_cast<uint8_t>(data_3500000.at(0xf2));
    repeater_check = static_cast<uint8_t>(data_3500000.at(0xdd));
    repeater_check_interval = static_cast<uint8_t>(data_3500000.at(0xde));
    repeater_check_reconnections = static_cast<uint8_t>(data_3500000.at(0xdf));
    repeater_out_of_range_notify = static_cast<uint8_t>(data_3500000.at(0xe5));
    out_of_range_notify = static_cast<uint8_t>(data_3500000.at(0xea));
    auto_roaming = static_cast<uint8_t>(data_3500000.at(0xe7));
    auto_roaming_start_condition = static_cast<uint8_t>(data_3500000.at(0xe0));
    auto_roaming_fixed_time = static_cast<uint8_t>(data_3500000.at(0xba));
    roaming_effect_wait_time = static_cast<uint8_t>(data_3500000.at(0xbf));
    roaming_zone = static_cast<uint8_t>(data_3500000.at(0xd5));
    auto_repeater_1_min_freq_vhf = Int::fromBytes(data_3500000.mid(0xc4,4));
    auto_repeater_1_max_freq_vhf = Int::fromBytes(data_3500000.mid(0xc8,4));
    auto_repeater_1_min_freq_uhf = Int::fromBytes(data_3500000.mid(0xcc,4));
    auto_repeater_1_max_freq_uhf = Int::fromBytes(data_3500000.mid(0xd0,4));
    auto_repeater_2_min_freq_vhf = Int::fromBytes(data_3500000.mid(0xf4,4));
    auto_repeater_2_max_freq_vhf = Int::fromBytes(data_3500000.mid(0xf8,4));
    auto_repeater_2_min_freq_uhf = Int::fromBytes(data_3500000.mid(0xfc,4));
    auto_repeater_2_max_freq_uhf = Int::fromBytes(data_3500000.mid(0x100,4));
    repeater_mode = static_cast<uint8_t>(data_3500000.at(0x143));
    rep_cc_limit = static_cast<uint8_t>(data_3500000.at(0x144));
    rep_slot_a = static_cast<uint8_t>(data_3500000.at(0x145));
    rep_slot_b = static_cast<uint8_t>(data_3500000.at(0x146));

    // Record
    record_function = static_cast<uint8_t>(data_3500000.at(0x22));
    record_delay = static_cast<uint8_t>(data_3500000.at(0xae));    

    // Volume/Audio
    max_volume = static_cast<uint8_t>(data_3500000.at(0x3b));
    power_on_volume_type = static_cast<uint8_t>(data_3500000.at(0x155));
    power_on_volume = static_cast<uint8_t>(data_3500000.at(0x156));
    max_headphone_volume = static_cast<uint8_t>(data_3500000.at(0x52));
    digi_mic_gain = static_cast<uint8_t>(data_3500000.at(0x0f));
    enhanced_sound_quality = static_cast<uint8_t>(data_3500000.at(0x57));
    analog_mic_gain = static_cast<uint8_t>(data_3500000.at(0x113));
    rx_agc = static_cast<uint8_t>(data_3500000.at(0x147));
    nx_mic_gain = static_cast<uint8_t>(data_3500000.at(0x153));

    // Work Mode
    display_mode = static_cast<uint8_t>(data_3500000.at(0x01));
    vf_mr_a = static_cast<uint8_t>(data_3500000.at(0x15));
    vf_mr_b = static_cast<uint8_t>(data_3500000.at(0x16));
    mem_zone_a = static_cast<uint8_t>(data_3500000.at(0x1f));
    mem_zone_b = static_cast<uint8_t>(data_3500000.at(0x20));
    main_channel_set = static_cast<uint8_t>(data_3500000.at(0x2c));
    sub_channel_mode = static_cast<uint8_t>(data_3500000.at(0x2d));
    working_mode = static_cast<uint8_t>(data_3500000.at(0x34));

    // VOX/BT
    vox_level = static_cast<uint8_t>(data_3500000.at(0x0c));
    vox_delay = static_cast<uint8_t>(data_3500000.at(0x0d));
    vox_detection = static_cast<uint8_t>(data_3500000.at(0x33));
    bt_on_off_D890UV = static_cast<uint8_t>(data_3500000.at(0xb1));
    bt_int_mic = static_cast<uint8_t>(data_3500000.at(0xb2));
    bt_int_spk = static_cast<uint8_t>(data_3500000.at(0xb3));
    bt_mic_gain = static_cast<uint8_t>(data_3500000.at(0xb6));
    bt_spk_gain = static_cast<uint8_t>(data_3500000.at(0xb7));
    bt_hold_time = static_cast<uint8_t>(data_3500000.at(0xeb));
    bt_rx_delay = static_cast<uint8_t>(data_3500000.at(0xec));
    bt_ptt_hold = static_cast<uint8_t>(data_3500000.at(0xf0));
    bt_ptt_sleep_time = static_cast<uint8_t>(data_3500000.at(0x104));
    bt_nr_before = static_cast<uint8_t>(data_3500000.at(0x14b));
    bt_nr_after = static_cast<uint8_t>(data_3500000.at(0x14c));

    // STE
    ste_type_of_ctcss = static_cast<uint8_t>(data_3500000.at(0x17));
    ste_when_no_signal = static_cast<uint8_t>(data_3500000.at(0x18));
    ste_time = static_cast<uint8_t>(data_3500000.at(0x106));

    // AM/FM
    am_fm_function = static_cast<uint8_t>(data_3500000.at(0x1e));
    fm_vfo_mem = static_cast<uint8_t>(data_3500000.at(0x1e));
    fm_work_channel = static_cast<uint8_t>(data_3500000.at(0x1d));
    fm_monitor = static_cast<uint8_t>(data_3500000.at(0x2b));
    am_vfo_mem = static_cast<uint8_t>(data_3500000.at(0x13f));
    am_work_zone = static_cast<uint8_t>(data_3500000.at(0x140));
    am_offset = static_cast<uint8_t>(data_3500000.at(0x141));
    am_sql_level = static_cast<uint8_t>(data_3500000.at(0x142));

    // Power Save
    auto_shutdown = static_cast<uint8_t>(data_3500000.at(0x3));
    power_save = static_cast<uint8_t>(data_3500000.at(0xb));
    auto_shutdown_type = static_cast<uint8_t>(data_3500000.at(0x3f));

    // Key Function
    key_lock = static_cast<uint8_t>(data_3500000.at(0x02));
    pf1_short_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x10));
    pf2_short_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x11));
    pf3_short_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x12));
    p1_short_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x13));
    p2_short_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x14));
    pf1_long_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x41));
    pf2_long_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x42));
    pf3_long_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x43));
    p1_long_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x44));
    p2_long_key_D890UV = static_cast<uint8_t>(data_3500000.at(0x45));
    long_key_time = static_cast<uint8_t>(data_3500000.at(0x46));
    knob_lock = Bit::test(data_3500000.at(0xbe), 0);
    keyboard_lock = Bit::test(data_3500000.at(0xbe), 1);
    side_key_lock = Bit::test(data_3500000.at(0xbe), 3);
    forced_key_lock = Bit::test(data_3500000.at(0xbe), 4);

    // Other
    address_book_sent_with_code = static_cast<uint8_t>(data_3500000.at(0xd5));
    tot = static_cast<uint8_t>(data_3500000.at(0x04));
    language = static_cast<uint8_t>(data_3500000.at(0x05));
    frequency_step = static_cast<uint8_t>(data_3500000.at(0x08));
    sql_level_a = static_cast<uint8_t>(data_3500000.at(0x09));
    sql_level_b = static_cast<uint8_t>(data_3500000.at(0x0a));
    tbst = static_cast<uint8_t>(data_3500000.at(0x2e));
    analog_call_hold_time = static_cast<uint8_t>(data_3500000.at(0x50));
    call_channel_maintained = static_cast<uint8_t>(data_3500000.at(0x6e));
    priority_zone_a = static_cast<uint8_t>(data_3500000.at(0x6f));
    priority_zone_b = static_cast<uint8_t>(data_3500000.at(0x70));
    mute_timing = static_cast<uint8_t>(data_3500000.at(0xe8));
    encryption_type = static_cast<uint8_t>(data_3500000.at(0x10a));
    tot_predict = static_cast<uint8_t>(data_3500000.at(0x10b));
    tx_power_agc = static_cast<uint8_t>(data_3500000.at(0x10c));
    noaa_moni = static_cast<uint8_t>(data_3500000.at(0x157));
    noaa_scan = static_cast<uint8_t>(data_3500000.at(0x158));
    noaa = static_cast<uint8_t>(data_3500000.at(0xef));
    noaa_channel = static_cast<uint8_t>(data_3500000.at(0x13e));

    // Digital Func
    group_call_hold_time = static_cast<uint8_t>(data_3500000.at(0x19));
    private_call_hold_time = static_cast<uint8_t>(data_3500000.at(0x1a));
    manual_dial_group_call_hold_time = static_cast<uint8_t>(data_3500000.at(0x107));
    manual_dial_private_call_hold_time = static_cast<uint8_t>(data_3500000.at(0x108));
    voice_header_repetitions = static_cast<uint8_t>(data_3500000.at(0x1b));
    tx_preamble_duration = static_cast<uint8_t>(data_3500000.at(0x1c));
    filter_own_id = static_cast<uint8_t>(data_3500000.at(0x38));
    digital_remote_kill = static_cast<uint8_t>(data_3500000.at(0x3c));
    digital_monitor = static_cast<uint8_t>(data_3500000.at(0x49));
    digital_monitor_cc = static_cast<uint8_t>(data_3500000.at(0x4a));
    digital_monitor_id = static_cast<uint8_t>(data_3500000.at(0x4b));
    monitor_slot_hold = static_cast<uint8_t>(data_3500000.at(0x4c));
    remote_monitor = static_cast<uint8_t>(data_3500000.at(0x3e));
    sms_format = static_cast<uint8_t>(data_3500000.at(0xc3));
    // digital_protocol = static_cast<uint8_t>(data_3500000.at(0xc3));
    reset_digital_protocol = static_cast<uint8_t>(data_3500000.at(0x154));

    // Satellite
    sat_location = static_cast<uint8_t>(data_3500000.at(0x14e));
    sat_tx_power = static_cast<uint8_t>(data_3500000.at(0x14f));
    sat_ana_sql = static_cast<uint8_t>(data_3500000.at(0x150));
    sat_aos_limit = static_cast<uint8_t>(data_3500000.at(0x151));

    poweron_password_char.remove(QChar('\0'));
    gps_information_char.remove(QChar('\0'));

}

void Anytone::OptionalSettings::encode_D878UVII(QByteArray &data_2500000, QByteArray &data_2500600, QByteArray &data_2501280, QByteArray &data_2501400){
    auto* data_2500000_bytes = reinterpret_cast<std::uint8_t*>(data_2500000.data());
    auto* data_2501400_bytes = reinterpret_cast<std::uint8_t*>(data_2501400.data());
    
    // Power-on
    data_2500000[0x6] = poweron_interface;
    data_2500600.replace(0, 0xe, 
        poweron_display_1.leftJustified(0xe, '\0')
    );
    data_2500600.replace(0x10, 0xe, 
        poweron_display_2.leftJustified(0xe, '\0')
    );
    data_2500000[0x7] = poweron_password;
    data_2500600.replace(0x10, 8, 
        poweron_password_char.toUtf8().leftJustified(8, '\0')
    );
    data_2500000[0xd7] = default_startup_channel;
    data_2500000[0xd8] = startup_zone_a;
    data_2500000[0xda] = startup_channel_a;
    data_2500000[0xd9] = startup_zone_b;
    data_2500000[0xdb] = startup_channel_b;
    data_2500000[0xeb] = startup_gps_test;
    data_2500000[0xec] = startup_reset;

    // Power Save
    data_2500000[0x3] = auto_shutdown;
    data_2500000[0xb] = power_save;
    data_2501400[0x3f] = auto_shutdown_type;

    // Display
    data_2500000[0x26] = brightness;
    data_2500000[0x27] = auto_backlight_duration;
    data_2500000[0xe1] = backlight_tx_delay;
    data_2500000[0x37] = menu_exit_time;
    data_2500000[0x51] = time_display;
    data_2500000[0x4d] = last_caller;
    data_2500000[0xaf] = call_display_mode;
    data_2500000[0xbc] = callsign_display_color;
    data_2500000[0x3a] = call_end_prompt_box;
    data_2500000[0xb8] = display_channel_number;
    data_2500000[0xb9] = display_current_contact;
    data_2500000[0xc0] = standby_char_color;
    data_2500000[0xc1] = standby_bk_picture;
    data_2500000[0xc2] = show_last_call_on_launch;
    data_2500000[0xe2] = separate_display;
    data_2500000[0xe3] = ch_switching_keeps_caller;
    data_2500000[0xe6] = backlight_rx_delay;
    data_2500000[0xe4] = channel_name_color_a;
    data_2501400[0x39] = channel_name_color_b;
    data_2501400[0x3d] = zone_name_color_a;
    data_2501400[0x3e] = zone_name_color_b;
    if(display_channel_type) Bit::set(&data_2501400_bytes[0x40], 0);
    if(display_time_slot) Bit::set(&data_2501400_bytes[0x40], 1);
    if(display_color_code) Bit::set(&data_2501400_bytes[0x40], 2);
    data_2501400[0x42] = date_display_format;
    data_2501400[0x47] = volume_bar;

    // Work Mode
    data_2500000[0x01] = display_mode;
    data_2500000[0x15] = vf_mr_a;
    data_2500000[0x16] = vf_mr_b;
    data_2500000[0x1f] = mem_zone_a;
    data_2500000[0x20] = mem_zone_b;
    data_2500000[0x2c] = main_channel_set;
    data_2500000[0x2d] = sub_channel_mode;
    data_2500000[0x34] = working_mode;

    // Vox/BT
    data_2500000[0x0c] = vox_level;
    data_2500000[0x0d] = vox_delay;
    data_2500000[0x33] = vox_detection;
    data_2500000[0xb1] = bt_on_off_D878UVII;
    data_2500000[0xb2] = bt_int_mic;
    data_2500000[0xb3] = bt_int_spk;
    data_2500000[0xb6] = bt_mic_gain;
    data_2500000[0xb7] = bt_spk_gain;
    data_2500000[0xed] = bt_hold_time;
    data_2500000[0xee] = bt_rx_delay;
    data_2501400[0x21] = bt_ptt_hold;
    data_2501400[0x34] = bt_ptt_sleep_time;

    // STE
    data_2500000[0x17] = ste_type_of_ctcss;
    data_2500000[0x18] = ste_when_no_signal;
    data_2501400[0x36] = ste_time;

    // FM
    data_2500000[0x1e] = fm_vfo_mem;
    data_2500000[0x1d] = fm_work_channel;
    data_2500000[0x2b] = fm_monitor;
    
    // Key Function
    data_2500000[0x02] = key_lock;
    data_2500000[0x10] = pf1_short_key_D878UVII;
    data_2500000[0x11] = pf2_short_key_D878UVII;
    data_2500000[0x12] = pf3_short_key_D878UVII;
    data_2500000[0x13] = p1_short_key_D878UVII;
    data_2500000[0x14] = p2_short_key_D878UVII;
    data_2500000[0x41] = pf1_long_key_D878UVII;
    data_2500000[0x42] = pf2_long_key_D878UVII;
    data_2500000[0x43] = pf3_long_key_D878UVII;
    data_2500000[0x44] = p1_long_key_D878UVII;
    data_2500000[0x45] = p2_long_key_D878UVII;
    data_2500000[0x46] = long_key_time;
    if(knob_lock) Bit::set(&data_2500000_bytes[0xbe], 0);
    if(keyboard_lock) Bit::set(&data_2500000_bytes[0xbe], 1);
    if(side_key_lock) Bit::set(&data_2500000_bytes[0xbe], 3);
    if(forced_key_lock) Bit::set(&data_2500000_bytes[0xbe], 4);
    

    // Other
    if(priority_zone_a == 0){
        priority_zone_a = 0xff;
    }else{
        priority_zone_a -= 1;
    }

    if(priority_zone_b == 0){
        priority_zone_b = 0xff;
    }else{
        priority_zone_b -= 1;
    }

    data_2500000[0xd5] = address_book_sent_with_code;
    data_2500000[0x04] = tot;
    data_2500000[0x05] = language;
    data_2500000[0x08] = frequency_step;
    data_2500000[0x09] = sql_level_a;
    data_2500000[0x0a] = sql_level_b;
    data_2500000[0x2e] = tbst;
    data_2500000[0x50] = analog_call_hold_time;
    data_2500000[0x6e] = call_channel_maintained;
    data_2500000[0x6f] = priority_zone_a;
    data_2500000[0x70] = priority_zone_b;
    data_2500000[0xe9] = mute_timing;
    data_2501400[0x3a] = encryption_type;
    data_2501400[0x3b] = tot_predict;
    data_2501400[0x3c] = tx_power_agc;

    // Digital Func
    data_2500000[0x19] = group_call_hold_time;
    data_2500000[0x1a] = private_call_hold_time;
    data_2501400[0x37] = manual_dial_group_call_hold_time;
    data_2501400[0x38] = manual_dial_private_call_hold_time;
    data_2501400[0x6e] = voice_header_repetitions;
    data_2500000[0x1c] = tx_preamble_duration;
    data_2500000[0x38] = filter_own_id;
    data_2500000[0x3c] = digital_remote_kill;
    data_2500000[0x49] = digital_monitor;
    data_2500000[0x4a] = digital_monitor_cc;
    data_2500000[0x4b] = digital_monitor_id;
    data_2500000[0x4c] = monitor_slot_hold;
    data_2500000[0x3e] = remote_monitor;
    data_2500000[0xc3] = sms_format;

    // Alert Tone
    data_2500000[0x29] = sms_alert;
    data_2500000[0x2f] = call_alert;
    data_2500000[0x32] = digi_call_reset_tone;
    data_2500000[0x31] = talk_permit;
    data_2500000[0x00] = key_tone;
    data_2500000[0x36] = digi_idle_channel_tone;
    data_2500000[0x39] = startup_sound;
    data_2500000[0xbb] = tone_key_sound_adjustable;
    data_2501400[0x41] = analog_idle_channel_tone;
    data_2500000[0xb4] = plugin_recording_tone;

    data_2500000.replace(0x72, 2, Int::toBytes(call_permit_first_tone_freq, 2));
    data_2500000.replace(0x7c, 2, Int::toBytes(call_permit_first_tone_period, 2));
    data_2500000.replace(0x74, 2, Int::toBytes(call_permit_second_tone_freq, 2));
    data_2500000.replace(0x7e, 2, Int::toBytes(call_permit_second_tone_period, 2));
    data_2500000.replace(0x76, 2, Int::toBytes(call_permit_third_tone_freq, 2));
    data_2500000.replace(0x80, 2, Int::toBytes(call_permit_third_tone_period, 2));
    data_2500000.replace(0x78, 2, Int::toBytes(call_permit_fourth_tone_freq, 2));
    data_2500000.replace(0x82, 2, Int::toBytes(call_permit_fourth_tone_period, 2));
    data_2500000.replace(0x7a, 2, Int::toBytes(call_permit_fifth_tone_freq, 2));
    data_2500000.replace(0x84, 2, Int::toBytes(call_permit_fifth_tone_period, 2));
    data_2500000.replace(0x86, 2, Int::toBytes(idle_channel_first_tone_freq, 2));
    data_2500000.replace(0x90, 2, Int::toBytes(idle_channel_first_tone_period, 2));
    data_2500000.replace(0x88, 2, Int::toBytes(idle_channel_second_tone_freq, 2));
    data_2500000.replace(0x92, 2, Int::toBytes(idle_channel_second_tone_period, 2));
    data_2500000.replace(0x8a, 2, Int::toBytes(idle_channel_third_tone_freq, 2));
    data_2500000.replace(0x94, 2, Int::toBytes(idle_channel_third_tone_period, 2));
    data_2500000.replace(0x8c, 2, Int::toBytes(idle_channel_fourth_tone_freq, 2));
    data_2500000.replace(0x96, 2, Int::toBytes(idle_channel_fourth_tone_period, 2));
    data_2500000.replace(0x8e, 2, Int::toBytes(idle_channel_fifth_tone_freq, 2));
    data_2500000.replace(0x98, 2, Int::toBytes(idle_channel_fifth_tone_period, 2));
    data_2500000.replace(0x9a, 2, Int::toBytes(call_reset_first_tone_freq, 2));
    data_2500000.replace(0xa4, 2, Int::toBytes(call_reset_first_tone_period, 2));
    data_2500000.replace(0x9c, 2, Int::toBytes(call_reset_second_tone_freq, 2));
    data_2500000.replace(0xa6, 2, Int::toBytes(call_reset_second_tone_period, 2));
    data_2500000.replace(0x9e, 2, Int::toBytes(call_reset_third_tone_freq, 2));
    data_2500000.replace(0xa8, 2, Int::toBytes(call_reset_third_tone_period, 2));
    data_2500000.replace(0xa0, 2, Int::toBytes(call_reset_fourth_tone_freq, 2));
    data_2500000.replace(0xaa, 2, Int::toBytes(call_reset_fourth_tone_period, 2));
    data_2500000.replace(0xa2, 2, Int::toBytes(call_reset_fifth_tone_freq, 2));
    data_2500000.replace(0xac, 2, Int::toBytes(call_reset_fifth_tone_period, 2));

    // Alert Tone 1
    data_2501400.replace(0x46, 2, Int::toBytes(call_end_first_tone_freq, 2));
    data_2501400.replace(0x50, 2, Int::toBytes(call_end_first_tone_period, 2));
    data_2501400.replace(0x48, 2, Int::toBytes(call_end_second_tone_freq, 2));
    data_2501400.replace(0x52, 2, Int::toBytes(call_end_second_tone_period, 2));
    data_2501400.replace(0x4a, 2, Int::toBytes(call_end_third_tone_freq, 2));
    data_2501400.replace(0x54, 2, Int::toBytes(call_end_third_tone_period, 2));
    data_2501400.replace(0x4c, 2, Int::toBytes(call_end_fourth_tone_freq, 2));
    data_2501400.replace(0x56, 2, Int::toBytes(call_end_fourth_tone_period, 2));
    data_2501400.replace(0x4e, 2, Int::toBytes(call_end_fifth_tone_freq, 2));
    data_2501400.replace(0x58, 2, Int::toBytes(call_end_fifth_tone_period, 2));
    data_2501400.replace(0x5a, 2, Int::toBytes(call_all_first_tone_freq, 2));
    data_2501400.replace(0x64, 2, Int::toBytes(call_all_first_tone_period, 2));
    data_2501400.replace(0x5c, 2, Int::toBytes(call_all_second_tone_freq, 2));
    data_2501400.replace(0x66, 2, Int::toBytes(call_all_second_tone_period, 2));
    data_2501400.replace(0x5e, 2, Int::toBytes(call_all_third_tone_freq, 2));
    data_2501400.replace(0x68, 2, Int::toBytes(call_all_third_tone_period, 2));
    data_2501400.replace(0x60, 2, Int::toBytes(call_all_fourth_tone_freq, 2));
    data_2501400.replace(0x6a, 2, Int::toBytes(call_all_fourth_tone_period, 2));
    data_2501400.replace(0x62, 2, Int::toBytes(call_all_fifth_tone_freq, 2));
    data_2501400.replace(0x6c, 2, Int::toBytes(call_all_fifth_tone_period, 2));

    // GPS/Ranging
    data_2500000[0x28] = gps_power;
    data_2500000[0x3f] = gps_positioning;
    data_2500000[0x30] = time_zone;
    data_2500000[0xb5] = ranging_interval;
    data_2500000[0xbd] = distance_unit;
    data_2500000[0x53] = gps_template_information;
    data_2501280.replace(0, 0x20, 
        gps_information_char.toUtf8().leftJustified(0x20, '\0')
    );
    data_2501400[0x35] = gps_mode;
    data_2501400[0x44] = gps_roaming;

    // VFO Scan
    data_2500000[0x0e] = vfo_scan_type;
    data_2500000.replace(0x58, 4, Int::toBytes(vfo_scan_start_freq_uhf, 4));
    data_2500000.replace(0x5c, 4, Int::toBytes(vfo_scan_end_freq_uhf, 4));
    data_2500000.replace(0x60, 4, Int::toBytes(vfo_scan_start_freq_vhf, 4));
    data_2500000.replace(0x64, 4, Int::toBytes(vfo_scan_end_freq_vhf, 4));

    // Auto Repeater
    data_2500000[0x48] = auto_repeater_a;
    data_2500000[0xd4] = auto_repeater_b;
    data_2500000[0x68] = auto_repeater_1_uhf;
    data_2500000[0x69] = auto_repeater_1_vhf;
    data_2501400[0x22] = auto_repeater_2_uhf;
    data_2501400[0x23] = auto_repeater_2_vhf;
    data_2500000[0xdd] = repeater_check;
    data_2500000[0xde] = repeater_check_interval;
    data_2500000[0xdf] = repeater_check_reconnections;
    data_2500000[0xe5] = repeater_out_of_range_notify;
    data_2500000[0xea] = out_of_range_notify;
    data_2500000[0xe7] = auto_roaming;
    data_2500000[0xe0] = auto_roaming_start_condition;
    data_2500000[0xba] = auto_roaming_fixed_time;
    data_2500000[0xbf] = roaming_effect_wait_time;
    data_2500000[0xd5] = roaming_zone;
    data_2500000.replace(0xc4, 4, Int::toBytes(auto_repeater_1_min_freq_vhf, 4));
    data_2500000.replace(0xc8, 4, Int::toBytes(auto_repeater_1_max_freq_vhf, 4));
    data_2500000.replace(0xcc, 4, Int::toBytes(auto_repeater_1_min_freq_uhf, 4));
    data_2500000.replace(0xd0, 4, Int::toBytes(auto_repeater_1_max_freq_uhf, 4));
    data_2501400.replace(0x24, 4, Int::toBytes(auto_repeater_2_min_freq_vhf, 4));
    data_2501400.replace(0x28, 4, Int::toBytes(auto_repeater_2_max_freq_vhf, 4));
    data_2501400.replace(0x2c, 4, Int::toBytes(auto_repeater_2_min_freq_uhf, 4));
    data_2501400.replace(0x30, 4, Int::toBytes(auto_repeater_2_max_freq_uhf, 4));

    // Record
    data_2500000[0x22] = record_function;

    // Volume/Audio
    data_2500000[0x3b] = max_volume;
    data_2500000[0x52] = max_headphone_volume;
    data_2500000[0x0f] = digi_mic_gain;
    data_2500000[0x57] = enhanced_sound_quality;
    data_2501400[0x43] = analog_mic_gain;
}
void Anytone::OptionalSettings::encode_D890UV(QByteArray &data_3500000, QByteArray &data_3500900, QByteArray &data_3501280){
    auto* data_3500000_bytes = reinterpret_cast<std::uint8_t*>(data_3500000.data());

    // Power On
    data_3500000[0x6] = poweron_interface;
    data_3500900.replace(0x0, 0xe, poweron_display_1);
    data_3500900.replace(0x10, 0xe, poweron_display_2);
    data_3500000[0x7] = poweron_password;
    data_3500900.replace(0x20, 0x8, poweron_password_char.toUtf8().leftJustified(0x8, 0));
    data_3500000[0xd7] = default_startup_channel;
    data_3500000[0xd8] = startup_zone_a;
    data_3500000[0xda] = startup_channel_a;
    data_3500000[0xd9] = startup_zone_b;
    data_3500000[0xdb] = startup_channel_b;
    data_3500000[0xeb] = startup_gps_test;
    data_3500000[0xec] = startup_reset;

    // Alert Tone
    data_3500000[0x29] = sms_alert;
    data_3500000[0x2f] = call_alert;
    data_3500000[0x32] = digi_call_reset_tone;
    data_3500000[0x31] = talk_permit;
    data_3500000[0x00] = key_tone;
    data_3500000[0x36] = digi_idle_channel_tone;
    data_3500000[0x39] = startup_sound;
    data_3500000[0xbb] = tone_key_sound_adjustable;
    data_3500000[0x111] = analog_idle_channel_tone;
    data_3500000[0xb4] = plugin_recording_tone;

    data_3500000.replace(0x72, 2, Int::toBytes(call_permit_first_tone_freq, 2));
    data_3500000.replace(0x7c, 2, Int::toBytes(call_permit_first_tone_period, 2));
    data_3500000.replace(0x74, 2, Int::toBytes(call_permit_second_tone_freq, 2));
    data_3500000.replace(0x7e, 2, Int::toBytes(call_permit_second_tone_period, 2));
    data_3500000.replace(0x76, 2, Int::toBytes(call_permit_third_tone_freq, 2));
    data_3500000.replace(0x80, 2, Int::toBytes(call_permit_third_tone_period, 2));
    data_3500000.replace(0x78, 2, Int::toBytes(call_permit_fourth_tone_freq, 2));
    data_3500000.replace(0x82, 2, Int::toBytes(call_permit_fourth_tone_period, 2));
    data_3500000.replace(0x7a, 2, Int::toBytes(call_permit_fifth_tone_freq, 2));
    data_3500000.replace(0x84, 2, Int::toBytes(call_permit_fifth_tone_period, 2));
    data_3500000.replace(0x86, 2, Int::toBytes(idle_channel_first_tone_freq, 2));
    data_3500000.replace(0x90, 2, Int::toBytes(idle_channel_first_tone_period, 2));
    data_3500000.replace(0x88, 2, Int::toBytes(idle_channel_second_tone_freq, 2));
    data_3500000.replace(0x92, 2, Int::toBytes(idle_channel_second_tone_period, 2));
    data_3500000.replace(0x8a, 2, Int::toBytes(idle_channel_third_tone_freq, 2));
    data_3500000.replace(0x94, 2, Int::toBytes(idle_channel_third_tone_period, 2));
    data_3500000.replace(0x8c, 2, Int::toBytes(idle_channel_fourth_tone_freq, 2));
    data_3500000.replace(0x96, 2, Int::toBytes(idle_channel_fourth_tone_period, 2));
    data_3500000.replace(0x8e, 2, Int::toBytes(idle_channel_fifth_tone_freq, 2));
    data_3500000.replace(0x98, 2, Int::toBytes(idle_channel_fifth_tone_period, 2));
    data_3500000.replace(0x9a, 2, Int::toBytes(call_reset_first_tone_freq, 2));
    data_3500000.replace(0xa4, 2, Int::toBytes(call_reset_first_tone_period, 2));
    data_3500000.replace(0x9c, 2, Int::toBytes(call_reset_second_tone_freq, 2));
    data_3500000.replace(0xa6, 2, Int::toBytes(call_reset_second_tone_period, 2));
    data_3500000.replace(0x9e, 2, Int::toBytes(call_reset_third_tone_freq, 2));
    data_3500000.replace(0xa8, 2, Int::toBytes(call_reset_third_tone_period, 2));
    data_3500000.replace(0xa0, 2, Int::toBytes(call_reset_fourth_tone_freq, 2));
    data_3500000.replace(0xaa, 2, Int::toBytes(call_reset_fourth_tone_period, 2));
    data_3500000.replace(0xa2, 2, Int::toBytes(call_reset_fifth_tone_freq, 2));
    data_3500000.replace(0xac, 2, Int::toBytes(call_reset_fifth_tone_period, 2));

    data_3500000.replace(0x116, 2, Int::toBytes(call_end_first_tone_freq, 2));
    data_3500000.replace(0x120, 2, Int::toBytes(call_end_first_tone_period, 2));
    data_3500000.replace(0x118, 2, Int::toBytes(call_end_second_tone_freq, 2));
    data_3500000.replace(0x122, 2, Int::toBytes(call_end_second_tone_period, 2));
    data_3500000.replace(0x11a, 2, Int::toBytes(call_end_third_tone_freq, 2));
    data_3500000.replace(0x124, 2, Int::toBytes(call_end_third_tone_period, 2));
    data_3500000.replace(0x11c, 2, Int::toBytes(call_end_fourth_tone_freq, 2));
    data_3500000.replace(0x126, 2, Int::toBytes(call_end_fourth_tone_period, 2));
    data_3500000.replace(0x11e, 2, Int::toBytes(call_end_fifth_tone_freq, 2));
    data_3500000.replace(0x128, 2, Int::toBytes(call_end_fifth_tone_period, 2));
    data_3500000.replace(0x12a, 2, Int::toBytes(call_all_first_tone_freq, 2));
    data_3500000.replace(0x134, 2, Int::toBytes(call_all_first_tone_period, 2));
    data_3500000.replace(0x12c, 2, Int::toBytes(call_all_second_tone_freq, 2));
    data_3500000.replace(0x136, 2, Int::toBytes(call_all_second_tone_period, 2));
    data_3500000.replace(0x12e, 2, Int::toBytes(call_all_third_tone_freq, 2));
    data_3500000.replace(0x138, 2, Int::toBytes(call_all_third_tone_period, 2));
    data_3500000.replace(0x130, 2, Int::toBytes(call_all_fourth_tone_freq, 2));
    data_3500000.replace(0x13a, 2, Int::toBytes(call_all_fourth_tone_period, 2));
    data_3500000.replace(0x132, 2, Int::toBytes(call_all_fifth_tone_freq, 2));
    data_3500000.replace(0x13c, 2, Int::toBytes(call_all_fifth_tone_period, 2));

    // Display
    data_3500000[0x26] = brightness;
    data_3500000[0x27] = auto_backlight_duration;
    data_3500000[0xe1] = backlight_tx_delay;
    data_3500000[0x37] = menu_exit_time;
    data_3500000[0x51] = time_display;
    data_3500000[0x4d] = last_caller;
    data_3500000[0xaf] = call_display_mode;
    data_3500000[0xbc] = callsign_display_color;
    data_3500000[0x3a] = call_end_prompt_box;
    data_3500000[0xb8] = display_channel_number;
    data_3500000[0xb9] = display_current_contact;
    data_3500000[0xc0] = standby_char_color;
    data_3500000[0xc1] = standby_bk_picture;
    data_3500000[0xc2] = show_last_call_on_launch;
    data_3500000[0xe1] = separate_display;
    data_3500000[0xe2] = ch_switching_keeps_caller;
    data_3500000[0xe5] = backlight_rx_delay;
    data_3500000[0xe3] = channel_name_color_a;
    data_3500000[0x109] = channel_name_color_b;
    data_3500000[0x10d] = zone_name_color_a;
    data_3500000[0x10e] = zone_name_color_b;
    if(display_channel_type) Bit::set(&data_3500000_bytes[0x110], 0);
    if(display_time_slot) Bit::set(&data_3500000_bytes[0x110], 1);
    if(display_color_code) Bit::set(&data_3500000_bytes[0x110], 2);
    data_3500000[0x112] = date_display_format;
    data_3500000[0x47] = volume_bar;

    // GPS/Ranging
    data_3500000[0x28] = gps_power;
    data_3500000[0x3f] = gps_positioning;
    data_3500000[0x30] = time_zone;
    data_3500000[0xb5] = ranging_interval;
    data_3500000[0xbd] = distance_unit;
    data_3500000[0x53] = gps_template_information;
    data_3501280.replace(0x0, 0x30, Format::wideCharString(gps_information_char).leftJustified(0x30, 0));
    data_3500000[0x105] = gps_mode;
    data_3500000[0x114] = gps_roaming;

    // VFO Scan
    data_3500000[0x0e] = vfo_scan_type;
    data_3500000.replace(0x58 , 4, Int::toBytes(vfo_scan_start_freq_uhf, 4));
    data_3500000.replace(0x5c , 4, Int::toBytes(vfo_scan_end_freq_uhf, 4));
    data_3500000.replace(0x60 , 4, Int::toBytes(vfo_scan_start_freq_vhf, 4));
    data_3500000.replace(0x64 , 4, Int::toBytes(vfo_scan_end_freq_vhf, 4));

    // Auto Repeater
    data_3500000[0x48] = auto_repeater_a;
    data_3500000[0xd4] = auto_repeater_b;
    data_3500000[0x68] = auto_repeater_1_uhf;
    data_3500000[0x69] = auto_repeater_1_vhf;
    data_3500000[0xf1] = auto_repeater_2_uhf;
    data_3500000[0xf2] = auto_repeater_2_vhf;
    data_3500000[0xdd] = repeater_check;
    data_3500000[0xde] = repeater_check_interval;
    data_3500000[0xdf] = repeater_check_reconnections;
    data_3500000[0xe5] = repeater_out_of_range_notify;
    data_3500000[0xea] = out_of_range_notify;
    data_3500000[0xe7] = auto_roaming;
    data_3500000[0xe0] = auto_roaming_start_condition;
    data_3500000[0xba] = auto_roaming_fixed_time;
    data_3500000[0xbf] = roaming_effect_wait_time;
    data_3500000[0xd5] = roaming_zone;
    data_3500000.replace(0xc4, 4, Int::toBytes(auto_repeater_1_min_freq_vhf, 4)); 
    data_3500000.replace(0xc8, 4, Int::toBytes(auto_repeater_1_max_freq_vhf, 4)); 
    data_3500000.replace(0xcc, 4, Int::toBytes(auto_repeater_1_min_freq_uhf, 4)); 
    data_3500000.replace(0xd0, 4, Int::toBytes(auto_repeater_1_max_freq_uhf, 4)); 
    data_3500000.replace(0xf4, 4, Int::toBytes(auto_repeater_2_min_freq_vhf, 4)); 
    data_3500000.replace(0xf8, 4, Int::toBytes(auto_repeater_2_max_freq_vhf, 4)); 
    data_3500000.replace(0xfc, 4, Int::toBytes(auto_repeater_2_min_freq_uhf, 4)); 
    data_3500000.replace(0x100, 4, Int::toBytes(auto_repeater_2_max_freq_uhf, 4)); 
    data_3500000[0x143] = repeater_mode;
    data_3500000[0x144] = rep_cc_limit;
    data_3500000[0x145] = rep_slot_a;
    data_3500000[0x146] = rep_slot_b;

    // Record
    data_3500000[0x22] = record_function;
    data_3500000[0xae] = record_delay;

    // Volume/Audio
    data_3500000[0x3b] = max_volume;
    data_3500000[0x52] = max_headphone_volume;
    data_3500000[0x0f] = digi_mic_gain;
    data_3500000[0x57] = enhanced_sound_quality;
    data_3500000[0x155] = power_on_volume_type;
    data_3500000[0x156] = power_on_volume;
    data_3500000[0x113] = analog_mic_gain;
    data_3500000[0x147] = rx_agc;
    data_3500000[0x153] = nx_mic_gain;

    // Work Mode
    data_3500000[0x01] = display_mode;
    data_3500000[0x15] = vf_mr_a;
    data_3500000[0x16] = vf_mr_b;
    data_3500000[0x1f] = mem_zone_a;
    data_3500000[0x20] = mem_zone_b;
    data_3500000[0x2c] = main_channel_set;
    data_3500000[0x2d] = sub_channel_mode;
    data_3500000[0x34] = working_mode;

    // VOX/BT
    data_3500000[0x0c] = vox_level;
    data_3500000[0x0d] = vox_delay;
    data_3500000[0x33] = vox_detection;
    data_3500000[0xb1] = bt_on_off_D890UV;
    data_3500000[0xb2] = bt_int_mic;
    data_3500000[0xb3] = bt_int_spk;
    data_3500000[0xb6] = bt_mic_gain;
    data_3500000[0xb7] = bt_spk_gain;
    data_3500000[0xeb] = bt_hold_time;
    data_3500000[0xec] = bt_rx_delay;
    data_3500000[0xf0] = bt_ptt_hold;
    data_3500000[0x104] = bt_ptt_sleep_time;
    data_3500000[0x14b] = bt_nr_before;
    data_3500000[0x14c] = bt_nr_after;

    // STE
    data_3500000[0x17] = ste_type_of_ctcss;
    data_3500000[0x18] = ste_when_no_signal;
    data_3500000[0x106] = ste_time;

    // AM/FM
    data_3500000[0x1e] = am_fm_function;
    data_3500000[0x1e] = fm_vfo_mem;
    data_3500000[0x1d] = fm_work_channel;
    data_3500000[0x2b] = fm_monitor;
    data_3500000[0x13f] = am_vfo_mem;
    data_3500000[0x140] = am_work_zone;
    data_3500000[0x141] = am_offset;
    data_3500000[0x142] = am_sql_level;

    // Power Save
    data_3500000[0x3] = auto_shutdown;
    data_3500000[0xb] = power_save;
    data_3500000[0x3f] = auto_shutdown_type;

    // Key Function
    data_3500000[0x02] = key_lock;
    data_3500000[0x10] = pf1_short_key_D890UV;
    data_3500000[0x11] = pf2_short_key_D890UV;
    data_3500000[0x12] = pf3_short_key_D890UV;
    data_3500000[0x13] = p1_short_key_D890UV;
    data_3500000[0x14] = p2_short_key_D890UV;
    data_3500000[0x41] = pf1_long_key_D890UV;
    data_3500000[0x42] = pf2_long_key_D890UV;
    data_3500000[0x43] = pf3_long_key_D890UV;
    data_3500000[0x44] = p1_long_key_D890UV;
    data_3500000[0x45] = p2_long_key_D890UV;
    data_3500000[0x46] = long_key_time;
    if(knob_lock) Bit::set(&data_3500000_bytes[0xbe], 0);
    if(keyboard_lock) Bit::set(&data_3500000_bytes[0xbe], 1);
    if(side_key_lock) Bit::set(&data_3500000_bytes[0xbe], 3);
    if(forced_key_lock) Bit::set(&data_3500000_bytes[0xbe], 4);

    // Other
    data_3500000[0xd5] = address_book_sent_with_code;
    data_3500000[0x04] = tot;
    data_3500000[0x05] = language;
    data_3500000[0x08] = frequency_step;
    data_3500000[0x09] = sql_level_a;
    data_3500000[0x0a] = sql_level_b;
    data_3500000[0x2e] = tbst;
    data_3500000[0x50] = analog_call_hold_time;
    data_3500000[0x6e] = call_channel_maintained;
    data_3500000[0x6f] = priority_zone_a;
    data_3500000[0x70] = priority_zone_b;
    data_3500000[0xe8] = mute_timing;
    data_3500000[0xef] = noaa;
    data_3500000[0x10a] = encryption_type;
    data_3500000[0x10b] = tot_predict;
    data_3500000[0x10c] = tx_power_agc;
    data_3500000[0x157] = noaa_moni;
    data_3500000[0x158] = noaa_scan;
    data_3500000[0x13e] = noaa_channel;

    // Digital Func
    data_3500000[0x19] = group_call_hold_time;
    data_3500000[0x1a] = private_call_hold_time;
    data_3500000[0x107] = manual_dial_group_call_hold_time;
    data_3500000[0x108] = manual_dial_private_call_hold_time;
    data_3500000[0x1b] = voice_header_repetitions;
    data_3500000[0x1c] = tx_preamble_duration;
    data_3500000[0x38] = filter_own_id;
    data_3500000[0x3c] = digital_remote_kill;
    data_3500000[0x49] = digital_monitor;
    data_3500000[0x4a] = digital_monitor_cc;
    data_3500000[0x4b] = digital_monitor_id;
    data_3500000[0x4c] = monitor_slot_hold;
    data_3500000[0x3e] = remote_monitor;
    data_3500000[0xc3] = sms_format;
    // data_3500000[0xc3] = digital_protocol;
    data_3500000[0x154] = reset_digital_protocol;

    // Satellite
    data_3500000[0x14e] = sat_location;
    data_3500000[0x14f] = sat_tx_power;
    data_3500000[0x150] = sat_ana_sql;
    data_3500000[0x151] = sat_aos_limit;
}
void Anytone::OptionalSettings::save(QXmlStreamWriter &xml){
    xml.writeStartElement("OptionalSettings");

    xml.writeStartElement("PowerOn");
    xml.writeAttribute("poweron_interface", QString::number(poweron_interface));
    xml.writeAttribute("poweron_password", QString::number(poweron_password));
    xml.writeAttribute("default_startup_channel", QString::number(default_startup_channel));
    xml.writeAttribute("startup_zone_a", QString::number(startup_zone_a));
    xml.writeAttribute("startup_channel_a", QString::number(startup_channel_a));
    xml.writeAttribute("startup_zone_b", QString::number(startup_zone_b));
    xml.writeAttribute("startup_channel_b", QString::number(startup_channel_b));
    xml.writeAttribute("startup_gps_test", QString::number(startup_gps_test));
    xml.writeAttribute("startup_reset", QString::number(startup_reset));
    xml.writeAttribute("poweron_display_1", poweron_display_1.toHex());
    xml.writeAttribute("poweron_display_2", poweron_display_2.toHex());
    xml.writeAttribute("poweron_password_char", poweron_password_char);
    xml.writeEndElement();

    // Power Save
    xml.writeStartElement("PowerSave");
    xml.writeAttribute("auto_shutdown", QString::number(auto_shutdown));
    xml.writeAttribute("power_save", QString::number(power_save));
    xml.writeAttribute("auto_shutdown_type", QString::number(auto_shutdown_type));
    xml.writeEndElement();

    // Display
    xml.writeStartElement("Display");
    xml.writeAttribute("brightness", QString::number(brightness));
    xml.writeAttribute("auto_backlight_duration", QString::number(auto_backlight_duration));
    xml.writeAttribute("backlight_tx_delay", QString::number(backlight_tx_delay));
    xml.writeAttribute("menu_exit_time", QString::number(menu_exit_time));
    xml.writeAttribute("time_display", QString::number(time_display));
    xml.writeAttribute("last_caller", QString::number(last_caller));
    xml.writeAttribute("call_display_mode", QString::number(call_display_mode));
    xml.writeAttribute("callsign_display_color", QString::number(callsign_display_color));
    xml.writeAttribute("call_end_prompt_box", QString::number(call_end_prompt_box));
    xml.writeAttribute("display_channel_number", QString::number(display_channel_number));
    xml.writeAttribute("display_current_contact", QString::number(display_current_contact));
    xml.writeAttribute("standby_char_color", QString::number(standby_char_color));
    xml.writeAttribute("standby_bk_picture", QString::number(standby_bk_picture));
    xml.writeAttribute("show_last_call_on_launch", QString::number(show_last_call_on_launch));
    xml.writeAttribute("separate_display", QString::number(separate_display));
    xml.writeAttribute("ch_switching_keeps_caller", QString::number(ch_switching_keeps_caller));
    xml.writeAttribute("backlight_rx_delay", QString::number(backlight_rx_delay));
    xml.writeAttribute("channel_name_color_a", QString::number(channel_name_color_a));
    xml.writeAttribute("channel_name_color_b", QString::number(channel_name_color_b));
    xml.writeAttribute("zone_name_color_a", QString::number(zone_name_color_a));
    xml.writeAttribute("zone_name_color_b", QString::number(zone_name_color_b));
    xml.writeAttribute("display_channel_type", QString::number(display_channel_type));
    xml.writeAttribute("display_time_slot", QString::number(display_time_slot));
    xml.writeAttribute("display_color_code", QString::number(display_color_code));
    xml.writeAttribute("date_display_format", QString::number(date_display_format));
    xml.writeAttribute("volume_bar", QString::number(volume_bar));
    xml.writeEndElement();

    // Work Mode
    xml.writeStartElement("WorkMode");
    xml.writeAttribute("display_mode", QString::number(display_mode));
    xml.writeAttribute("vf_mr_a", QString::number(vf_mr_a));
    xml.writeAttribute("vf_mr_b", QString::number(vf_mr_b));
    xml.writeAttribute("mem_zone_a", QString::number(mem_zone_a));
    xml.writeAttribute("mem_zone_b", QString::number(mem_zone_b));
    xml.writeAttribute("main_channel_set", QString::number(main_channel_set));
    xml.writeAttribute("sub_channel_mode", QString::number(sub_channel_mode));
    xml.writeAttribute("working_mode", QString::number(working_mode));
    xml.writeEndElement();

    // Vox/BT
    xml.writeStartElement("VoxBT");
    xml.writeAttribute("vox_level", QString::number(vox_level));
    xml.writeAttribute("vox_delay", QString::number(vox_delay));
    xml.writeAttribute("vox_detection", QString::number(vox_detection));
    xml.writeAttribute("bt_on_off_D878UVII", QString::number(bt_on_off_D878UVII));
    xml.writeAttribute("bt_on_off_D890UV", QString::number(bt_on_off_D890UV));
    xml.writeAttribute("bt_int_mic", QString::number(bt_int_mic));
    xml.writeAttribute("bt_int_spk", QString::number(bt_int_spk));
    xml.writeAttribute("bt_mic_gain", QString::number(bt_mic_gain));
    xml.writeAttribute("bt_spk_gain", QString::number(bt_spk_gain));
    xml.writeAttribute("bt_hold_time", QString::number(bt_hold_time));
    xml.writeAttribute("bt_rx_delay", QString::number(bt_rx_delay));
    xml.writeAttribute("bt_ptt_hold", QString::number(bt_ptt_hold));
    xml.writeAttribute("bt_ptt_sleep_time", QString::number(bt_ptt_sleep_time));
    xml.writeAttribute("bt_nr_before", QString::number(bt_nr_before));
    xml.writeAttribute("bt_nr_after", QString::number(bt_nr_after));
    xml.writeEndElement();

    // STE
    xml.writeStartElement("STE");
    xml.writeAttribute("ste_type_of_ctcss", QString::number(ste_type_of_ctcss));
    xml.writeAttribute("ste_when_no_signal", QString::number(ste_when_no_signal));
    xml.writeAttribute("ste_time", QString::number(ste_time));
    xml.writeEndElement();

    // FM
    xml.writeStartElement("FM");
    xml.writeAttribute("am_fm_function", QString::number(am_fm_function));
    xml.writeAttribute("fm_vfo_mem", QString::number(fm_vfo_mem));
    xml.writeAttribute("fm_work_channel", QString::number(fm_work_channel));
    xml.writeAttribute("fm_monitor", QString::number(fm_monitor));
    xml.writeAttribute("am_vfo_mem", QString::number(am_vfo_mem));
    xml.writeAttribute("am_work_zone", QString::number(am_work_zone));
    xml.writeAttribute("am_offset", QString::number(am_offset));
    xml.writeAttribute("am_sql_level", QString::number(am_sql_level));
    xml.writeEndElement();

    // Key Function
    xml.writeStartElement("KeyFunction");
    xml.writeAttribute("key_lock", QString::number(key_lock));
    xml.writeAttribute("pf1_short_key_D878UVII", QString::number(pf1_short_key_D878UVII));
    xml.writeAttribute("pf2_short_key_D878UVII", QString::number(pf2_short_key_D878UVII));
    xml.writeAttribute("pf3_short_key_D878UVII", QString::number(pf3_short_key_D878UVII));
    xml.writeAttribute("p1_short_key_D878UVII", QString::number(p1_short_key_D878UVII));
    xml.writeAttribute("p2_short_key_D878UVII", QString::number(p2_short_key_D878UVII));
    xml.writeAttribute("pf1_long_key_D878UVII", QString::number(pf1_long_key_D878UVII));
    xml.writeAttribute("pf2_long_key_D878UVII", QString::number(pf2_long_key_D878UVII));
    xml.writeAttribute("pf3_long_key_D878UVII", QString::number(pf3_long_key_D878UVII));
    xml.writeAttribute("p1_long_key_D878UVII", QString::number(p1_long_key_D878UVII));
    xml.writeAttribute("p2_long_key_D878UVII", QString::number(p2_long_key_D878UVII));
    xml.writeAttribute("pf1_short_key_D890UV", QString::number(pf1_short_key_D890UV));
    xml.writeAttribute("pf2_short_key_D890UV", QString::number(pf2_short_key_D890UV));
    xml.writeAttribute("pf3_short_key_D890UV", QString::number(pf3_short_key_D890UV));
    xml.writeAttribute("p1_short_key_D890UV", QString::number(p1_short_key_D890UV));
    xml.writeAttribute("p2_short_key_D890UV", QString::number(p2_short_key_D890UV));
    xml.writeAttribute("pf1_long_key_D890UV", QString::number(pf1_long_key_D890UV));
    xml.writeAttribute("pf2_long_key_D890UV", QString::number(pf2_long_key_D890UV));
    xml.writeAttribute("pf3_long_key_D890UV", QString::number(pf3_long_key_D890UV));
    xml.writeAttribute("p1_long_key_D890UV", QString::number(p1_long_key_D890UV));
    xml.writeAttribute("p2_long_key_D890UV", QString::number(p2_long_key_D890UV));
    xml.writeAttribute("long_key_time", QString::number(long_key_time));
    xml.writeAttribute("knob_lock", QString::number(knob_lock));
    xml.writeAttribute("keyboard_lock", QString::number(keyboard_lock));
    xml.writeAttribute("side_key_lock", QString::number(side_key_lock));
    xml.writeAttribute("forced_key_lock", QString::number(forced_key_lock));
    xml.writeEndElement();

    // Other
    xml.writeStartElement("Other");
    xml.writeAttribute("address_book_sent_with_code", QString::number(address_book_sent_with_code));
    xml.writeAttribute("tot", QString::number(tot));
    xml.writeAttribute("language", QString::number(language));
    xml.writeAttribute("frequency_step", QString::number(frequency_step));
    xml.writeAttribute("sql_level_a", QString::number(sql_level_a));
    xml.writeAttribute("sql_level_b", QString::number(sql_level_b));
    xml.writeAttribute("tbst", QString::number(tbst));
    xml.writeAttribute("analog_call_hold_time", QString::number(analog_call_hold_time));
    xml.writeAttribute("call_channel_maintained", QString::number(call_channel_maintained));
    xml.writeAttribute("priority_zone_a", QString::number(priority_zone_a));
    xml.writeAttribute("priority_zone_b", QString::number(priority_zone_b));
    xml.writeAttribute("mute_timing", QString::number(mute_timing));
    xml.writeAttribute("encryption_type", QString::number(encryption_type));
    xml.writeAttribute("tot_predict", QString::number(tot_predict));
    xml.writeAttribute("tx_power_agc", QString::number(tx_power_agc));
    xml.writeAttribute("noaa_moni", QString::number(noaa_moni));
    xml.writeAttribute("noaa_scan", QString::number(noaa_scan));
    xml.writeAttribute("noaa", QString::number(noaa));
    xml.writeAttribute("noaa_channel", QString::number(noaa_channel));
    xml.writeEndElement();

    // Digital Func
    xml.writeStartElement("DigitalFunc");
    xml.writeAttribute("group_call_hold_time", QString::number(group_call_hold_time));
    xml.writeAttribute("private_call_hold_time", QString::number(private_call_hold_time));
    xml.writeAttribute("manual_dial_group_call_hold_time", QString::number(manual_dial_group_call_hold_time));
    xml.writeAttribute("manual_dial_private_call_hold_time", QString::number(manual_dial_private_call_hold_time));
    xml.writeAttribute("voice_header_repetitions", QString::number(voice_header_repetitions));
    xml.writeAttribute("tx_preamble_duration", QString::number(tx_preamble_duration));
    xml.writeAttribute("filter_own_id", QString::number(filter_own_id));
    xml.writeAttribute("digital_remote_kill", QString::number(digital_remote_kill));
    xml.writeAttribute("digital_monitor", QString::number(digital_monitor));
    xml.writeAttribute("digital_monitor_cc", QString::number(digital_monitor_cc));
    xml.writeAttribute("digital_monitor_id", QString::number(digital_monitor_id));
    xml.writeAttribute("monitor_slot_hold", QString::number(monitor_slot_hold));
    xml.writeAttribute("remote_monitor", QString::number(remote_monitor));
    xml.writeAttribute("sms_format", QString::number(sms_format));
    xml.writeAttribute("digital_protocol", QString::number(digital_protocol));
    xml.writeAttribute("reset_digital_protocol", QString::number(reset_digital_protocol));
    xml.writeEndElement();

    // Alert Tone
    xml.writeStartElement("AlertTone");
    xml.writeAttribute("sms_alert", QString::number(sms_alert));
    xml.writeAttribute("call_alert", QString::number(call_alert));
    xml.writeAttribute("digi_call_reset_tone", QString::number(digi_call_reset_tone));
    xml.writeAttribute("talk_permit", QString::number(talk_permit));
    xml.writeAttribute("key_tone", QString::number(key_tone));
    xml.writeAttribute("digi_idle_channel_tone", QString::number(digi_idle_channel_tone));
    xml.writeAttribute("startup_sound", QString::number(startup_sound));
    xml.writeAttribute("tone_key_sound_adjustable", QString::number(tone_key_sound_adjustable));
    xml.writeAttribute("analog_idle_channel_tone", QString::number(analog_idle_channel_tone));
    xml.writeAttribute("plugin_recording_tone", QString::number(plugin_recording_tone));
    xml.writeAttribute("call_permit_first_tone_freq", QString::number(call_permit_first_tone_freq));
    xml.writeAttribute("call_permit_first_tone_period", QString::number(call_permit_first_tone_period));
    xml.writeAttribute("call_permit_second_tone_freq", QString::number(call_permit_second_tone_freq));
    xml.writeAttribute("call_permit_second_tone_period", QString::number(call_permit_second_tone_period));
    xml.writeAttribute("call_permit_third_tone_freq", QString::number(call_permit_third_tone_freq));
    xml.writeAttribute("call_permit_third_tone_period", QString::number(call_permit_third_tone_period));
    xml.writeAttribute("call_permit_fourth_tone_freq", QString::number(call_permit_fourth_tone_freq));
    xml.writeAttribute("call_permit_fourth_tone_period", QString::number(call_permit_fourth_tone_period));
    xml.writeAttribute("call_permit_fifth_tone_freq", QString::number(call_permit_fifth_tone_freq));
    xml.writeAttribute("call_permit_fifth_tone_period", QString::number(call_permit_fifth_tone_period));
    xml.writeAttribute("idle_channel_first_tone_freq", QString::number(idle_channel_first_tone_freq));
    xml.writeAttribute("idle_channel_first_tone_period", QString::number(idle_channel_first_tone_period));
    xml.writeAttribute("idle_channel_second_tone_freq", QString::number(idle_channel_second_tone_freq));
    xml.writeAttribute("idle_channel_second_tone_period", QString::number(idle_channel_second_tone_period));
    xml.writeAttribute("idle_channel_third_tone_freq", QString::number(idle_channel_third_tone_freq));
    xml.writeAttribute("idle_channel_third_tone_period", QString::number(idle_channel_third_tone_period));
    xml.writeAttribute("idle_channel_fourth_tone_freq", QString::number(idle_channel_fourth_tone_freq));
    xml.writeAttribute("idle_channel_fourth_tone_period", QString::number(idle_channel_fourth_tone_period));
    xml.writeAttribute("idle_channel_fifth_tone_freq", QString::number(idle_channel_fifth_tone_freq));
    xml.writeAttribute("idle_channel_fifth_tone_period", QString::number(idle_channel_fifth_tone_period));
    xml.writeAttribute("call_reset_first_tone_freq", QString::number(call_reset_first_tone_freq));
    xml.writeAttribute("call_reset_first_tone_period", QString::number(call_reset_first_tone_period));
    xml.writeAttribute("call_reset_second_tone_freq", QString::number(call_reset_second_tone_freq));
    xml.writeAttribute("call_reset_second_tone_period", QString::number(call_reset_second_tone_period));
    xml.writeAttribute("call_reset_third_tone_freq", QString::number(call_reset_third_tone_freq));
    xml.writeAttribute("call_reset_third_tone_period", QString::number(call_reset_third_tone_period));
    xml.writeAttribute("call_reset_fourth_tone_freq", QString::number(call_reset_fourth_tone_freq));
    xml.writeAttribute("call_reset_fourth_tone_period", QString::number(call_reset_fourth_tone_period));
    xml.writeAttribute("call_reset_fifth_tone_freq", QString::number(call_reset_fifth_tone_freq));
    xml.writeAttribute("call_reset_fifth_tone_period", QString::number(call_reset_fifth_tone_period));
    xml.writeEndElement();

    // Alert Tone 1
    xml.writeStartElement("AlertTone1");
    xml.writeAttribute("call_end_first_tone_freq", QString::number(call_end_first_tone_freq));
    xml.writeAttribute("call_end_first_tone_period", QString::number(call_end_first_tone_period));
    xml.writeAttribute("call_end_second_tone_freq", QString::number(call_end_second_tone_freq));
    xml.writeAttribute("call_end_second_tone_period", QString::number(call_end_second_tone_period));
    xml.writeAttribute("call_end_third_tone_freq", QString::number(call_end_third_tone_freq));
    xml.writeAttribute("call_end_third_tone_period", QString::number(call_end_third_tone_period));
    xml.writeAttribute("call_end_fourth_tone_freq", QString::number(call_end_fourth_tone_freq));
    xml.writeAttribute("call_end_fourth_tone_period", QString::number(call_end_fourth_tone_period));
    xml.writeAttribute("call_end_fifth_tone_freq", QString::number(call_end_fifth_tone_freq));
    xml.writeAttribute("call_end_fifth_tone_period", QString::number(call_end_fifth_tone_period));
    xml.writeAttribute("call_all_first_tone_freq", QString::number(call_all_first_tone_freq));
    xml.writeAttribute("call_all_first_tone_period", QString::number(call_all_first_tone_period));
    xml.writeAttribute("call_all_second_tone_freq", QString::number(call_all_second_tone_freq));
    xml.writeAttribute("call_all_second_tone_period", QString::number(call_all_second_tone_period));
    xml.writeAttribute("call_all_third_tone_freq", QString::number(call_all_third_tone_freq));
    xml.writeAttribute("call_all_third_tone_period", QString::number(call_all_third_tone_period));
    xml.writeAttribute("call_all_fourth_tone_freq", QString::number(call_all_fourth_tone_freq));
    xml.writeAttribute("call_all_fourth_tone_period", QString::number(call_all_fourth_tone_period));
    xml.writeAttribute("call_all_fifth_tone_freq", QString::number(call_all_fifth_tone_freq));
    xml.writeAttribute("call_all_fifth_tone_period", QString::number(call_all_fifth_tone_period));
    xml.writeEndElement();

    // GPS/Ranging
    xml.writeStartElement("GPSRanging");
    xml.writeAttribute("gps_power", QString::number(gps_power));
    xml.writeAttribute("gps_positioning", QString::number(gps_positioning));
    xml.writeAttribute("time_zone", QString::number(time_zone));
    xml.writeAttribute("ranging_interval", QString::number(ranging_interval));
    xml.writeAttribute("distance_unit", QString::number(distance_unit));
    xml.writeAttribute("gps_template_information", QString::number(gps_template_information));
    xml.writeAttribute("gps_mode", QString::number(gps_mode));
    xml.writeAttribute("gps_roaming", QString::number(gps_roaming));
    xml.writeAttribute("gps_information_char", gps_information_char);
    xml.writeEndElement();

    // VFO Scan
    xml.writeStartElement("VFOScan");
    xml.writeAttribute("vfo_scan_type", QString::number(vfo_scan_type));
    xml.writeAttribute("vfo_scan_start_freq_uhf", QString::number(vfo_scan_start_freq_uhf));
    xml.writeAttribute("vfo_scan_end_freq_uhf", QString::number(vfo_scan_end_freq_uhf));
    xml.writeAttribute("vfo_scan_start_freq_vhf", QString::number(vfo_scan_start_freq_vhf));
    xml.writeAttribute("vfo_scan_end_freq_vhf", QString::number(vfo_scan_end_freq_vhf));
    xml.writeEndElement();

    // Auto Repeater
    xml.writeStartElement("AutoRepeater");
    xml.writeAttribute("auto_repeater_a", QString::number(auto_repeater_a));
    xml.writeAttribute("auto_repeater_b", QString::number(auto_repeater_b));
    xml.writeAttribute("auto_repeater_1_uhf", QString::number(auto_repeater_1_uhf));
    xml.writeAttribute("auto_repeater_1_vhf", QString::number(auto_repeater_1_vhf));
    xml.writeAttribute("auto_repeater_2_uhf", QString::number(auto_repeater_2_uhf));
    xml.writeAttribute("auto_repeater_2_vhf", QString::number(auto_repeater_2_vhf));
    xml.writeAttribute("repeater_check", QString::number(repeater_check));
    xml.writeAttribute("repeater_check_interval", QString::number(repeater_check_interval));
    xml.writeAttribute("repeater_check_reconnections", QString::number(repeater_check_reconnections));
    xml.writeAttribute("repeater_out_of_range_notify", QString::number(repeater_out_of_range_notify));
    xml.writeAttribute("out_of_range_notify", QString::number(out_of_range_notify));
    xml.writeAttribute("auto_roaming", QString::number(auto_roaming));
    xml.writeAttribute("auto_roaming_start_condition", QString::number(auto_roaming_start_condition));
    xml.writeAttribute("auto_roaming_fixed_time", QString::number(auto_roaming_fixed_time));
    xml.writeAttribute("roaming_effect_wait_time", QString::number(roaming_effect_wait_time));
    xml.writeAttribute("roaming_zone", QString::number(roaming_zone));
    xml.writeAttribute("auto_repeater_1_min_freq_vhf", QString::number(auto_repeater_1_min_freq_vhf));
    xml.writeAttribute("auto_repeater_1_max_freq_vhf", QString::number(auto_repeater_1_max_freq_vhf));
    xml.writeAttribute("auto_repeater_1_min_freq_uhf", QString::number(auto_repeater_1_min_freq_uhf));
    xml.writeAttribute("auto_repeater_1_max_freq_uhf", QString::number(auto_repeater_1_max_freq_uhf));
    xml.writeAttribute("auto_repeater_2_min_freq_vhf", QString::number(auto_repeater_2_min_freq_vhf));
    xml.writeAttribute("auto_repeater_2_max_freq_vhf", QString::number(auto_repeater_2_max_freq_vhf));
    xml.writeAttribute("auto_repeater_2_min_freq_uhf", QString::number(auto_repeater_2_min_freq_uhf));
    xml.writeAttribute("auto_repeater_2_max_freq_uhf", QString::number(auto_repeater_2_max_freq_uhf));
    xml.writeAttribute("repeater_mode", QString::number(repeater_mode));
    xml.writeAttribute("rep_cc_limit", QString::number(rep_cc_limit));
    xml.writeAttribute("rep_slot_a", QString::number(rep_slot_a));
    xml.writeAttribute("rep_slot_b", QString::number(rep_slot_b));
    xml.writeEndElement();

    // Record
    xml.writeStartElement("Record");
    xml.writeAttribute("record_function", QString::number(record_function));
    xml.writeAttribute("record_delay", QString::number(record_delay));
    xml.writeEndElement();

    // Volume/Audio
    xml.writeStartElement("VolumeAudio");
    xml.writeAttribute("max_volume", QString::number(max_volume));
    xml.writeAttribute("max_headphone_volume", QString::number(max_headphone_volume));
    xml.writeAttribute("digi_mic_gain", QString::number(digi_mic_gain));
    xml.writeAttribute("enhanced_sound_quality", QString::number(enhanced_sound_quality));
    xml.writeAttribute("analog_mic_gain", QString::number(analog_mic_gain));
    xml.writeAttribute("power_on_volume_type", QString::number(power_on_volume_type));
    xml.writeAttribute("power_on_volume", QString::number(power_on_volume));
    xml.writeAttribute("rx_agc", QString::number(rx_agc));
    xml.writeAttribute("nx_mic_gain", QString::number(nx_mic_gain));
    xml.writeEndElement();

    // Satellite
    xml.writeStartElement("Satellite");
    xml.writeAttribute("sat_location", QString::number(sat_location));
    xml.writeAttribute("sat_tx_power", QString::number(sat_tx_power));
    xml.writeAttribute("sat_ana_sql", QString::number(sat_ana_sql));
    xml.writeAttribute("sat_aos_limit", QString::number(sat_aos_limit));
    xml.writeEndElement();
    
    xml.writeEndElement();
}
void Anytone::OptionalSettings::load(QXmlStreamReader &xml){
    if (xml.name() == "OptionalSettings"){
        QXmlStreamReader::TokenType token = QXmlStreamReader::NoToken;
        while (!xml.atEnd() && !xml.hasError()) {
            if(token == QXmlStreamReader::StartElement && xml.name() == "PowerOn"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("poweron_interface"))
                    poweron_interface = attributes.value("poweron_interface").toInt();
                if(attributes.hasAttribute("poweron_password"))
                    poweron_password = attributes.value("poweron_password").toInt();
                if(attributes.hasAttribute("default_startup_channel"))
                    default_startup_channel = attributes.value("default_startup_channel").toInt();
                if(attributes.hasAttribute("startup_zone_a"))
                    startup_zone_a = attributes.value("startup_zone_a").toInt();
                if(attributes.hasAttribute("startup_channel_a"))
                    startup_channel_a = attributes.value("startup_channel_a").toInt();
                if(attributes.hasAttribute("startup_zone_b"))
                    startup_zone_b = attributes.value("startup_zone_b").toInt();
                if(attributes.hasAttribute("startup_channel_b"))
                    startup_channel_b = attributes.value("startup_channel_b").toInt();
                if(attributes.hasAttribute("startup_gps_test"))
                    startup_gps_test = attributes.value("startup_gps_test").toInt();
                if(attributes.hasAttribute("startup_reset"))
                    startup_reset = attributes.value("startup_reset").toInt();
                if(attributes.hasAttribute("poweron_display_1"))
                    poweron_display_1 = QByteArray::fromHex(attributes.value("poweron_display_1").toString().toUtf8());
                if(attributes.hasAttribute("poweron_display_2"))
                    poweron_display_2 = QByteArray::fromHex(attributes.value("poweron_display_2").toString().toUtf8());
                if(attributes.hasAttribute("poweron_password_char"))
                    poweron_password_char = attributes.value("poweron_password_char").toString();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "PowerSave"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("auto_shutdown"))
                    auto_shutdown = attributes.value("auto_shutdown").toInt();
                if(attributes.hasAttribute("power_save"))
                    power_save = attributes.value("power_save").toInt();
                if(attributes.hasAttribute("auto_shutdown_type"))
                    auto_shutdown_type = attributes.value("auto_shutdown_type").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "Display"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("brightness"))
                    brightness = attributes.value("brightness").toInt();
                if(attributes.hasAttribute("auto_backlight_duration"))
                    auto_backlight_duration = attributes.value("auto_backlight_duration").toInt();
                if(attributes.hasAttribute("backlight_tx_delay"))
                    backlight_tx_delay = attributes.value("backlight_tx_delay").toInt();
                if(attributes.hasAttribute("menu_exit_time"))
                    menu_exit_time = attributes.value("menu_exit_time").toInt();
                if(attributes.hasAttribute("time_display"))
                    time_display = attributes.value("time_display").toInt();
                if(attributes.hasAttribute("last_caller"))
                    last_caller = attributes.value("last_caller").toInt();
                if(attributes.hasAttribute("call_display_mode"))
                    call_display_mode = attributes.value("call_display_mode").toInt();
                if(attributes.hasAttribute("callsign_display_color"))
                    callsign_display_color = attributes.value("callsign_display_color").toInt();
                if(attributes.hasAttribute("call_end_prompt_box"))
                    call_end_prompt_box = attributes.value("call_end_prompt_box").toInt();
                if(attributes.hasAttribute("display_channel_number"))
                    display_channel_number = attributes.value("display_channel_number").toInt();
                if(attributes.hasAttribute("display_current_contact"))
                    display_current_contact = attributes.value("display_current_contact").toInt();
                if(attributes.hasAttribute("standby_char_color"))
                    standby_char_color = attributes.value("standby_char_color").toInt();
                if(attributes.hasAttribute("standby_bk_picture"))
                    standby_bk_picture = attributes.value("standby_bk_picture").toInt();
                if(attributes.hasAttribute("show_last_call_on_launch"))
                    show_last_call_on_launch = attributes.value("show_last_call_on_launch").toInt();
                if(attributes.hasAttribute("separate_display"))
                    separate_display = attributes.value("separate_display").toInt();
                if(attributes.hasAttribute("ch_switching_keeps_caller"))
                    ch_switching_keeps_caller = attributes.value("ch_switching_keeps_caller").toInt();
                if(attributes.hasAttribute("backlight_rx_delay"))
                    backlight_rx_delay = attributes.value("backlight_rx_delay").toInt();
                if(attributes.hasAttribute("channel_name_color_a"))
                    channel_name_color_a = attributes.value("channel_name_color_a").toInt();
                if(attributes.hasAttribute("channel_name_color_b"))
                    channel_name_color_b = attributes.value("channel_name_color_b").toInt();
                if(attributes.hasAttribute("zone_name_color_a"))
                    zone_name_color_a = attributes.value("zone_name_color_a").toInt();
                if(attributes.hasAttribute("zone_name_color_b"))
                    zone_name_color_b = attributes.value("zone_name_color_b").toInt();
                if(attributes.hasAttribute("display_channel_type"))
                    display_channel_type = attributes.value("display_channel_type").toInt();
                if(attributes.hasAttribute("display_time_slot"))
                    display_time_slot = attributes.value("display_time_slot").toInt();
                if(attributes.hasAttribute("display_color_code"))
                    display_color_code = attributes.value("display_color_code").toInt();
                if(attributes.hasAttribute("date_display_format"))
                    date_display_format = attributes.value("date_display_format").toInt();
                if(attributes.hasAttribute("volume_bar"))
                    volume_bar = attributes.value("volume_bar").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "WorkMode"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("display_mode"))
                    display_mode = attributes.value("display_mode").toInt();
                if(attributes.hasAttribute("vf_mr_a"))
                    vf_mr_a = attributes.value("vf_mr_a").toInt();
                if(attributes.hasAttribute("vf_mr_b"))
                    vf_mr_b = attributes.value("vf_mr_b").toInt();
                if(attributes.hasAttribute("mem_zone_a"))
                    mem_zone_a = attributes.value("mem_zone_a").toInt();
                if(attributes.hasAttribute("mem_zone_b"))
                    mem_zone_b = attributes.value("mem_zone_b").toInt();
                if(attributes.hasAttribute("main_channel_set"))
                    main_channel_set = attributes.value("main_channel_set").toInt();
                if(attributes.hasAttribute("sub_channel_mode"))
                    sub_channel_mode = attributes.value("sub_channel_mode").toInt();
                if(attributes.hasAttribute("working_mode"))
                    working_mode = attributes.value("working_mode").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "VoxBT"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("vox_level"))
                    vox_level = attributes.value("vox_level").toInt();
                if(attributes.hasAttribute("vox_delay"))
                    vox_delay = attributes.value("vox_delay").toInt();
                if(attributes.hasAttribute("vox_detection"))
                    vox_detection = attributes.value("vox_detection").toInt();
                if(attributes.hasAttribute("bt_on_off_D878UVII"))
                    bt_on_off_D878UVII = attributes.value("bt_on_off_D878UVII").toInt();
                if(attributes.hasAttribute("bt_on_off_D890UV"))
                    bt_on_off_D890UV = attributes.value("bt_on_off_D890UV").toInt();
                if(attributes.hasAttribute("bt_int_mic"))
                    bt_int_mic = attributes.value("bt_int_mic").toInt();
                if(attributes.hasAttribute("bt_int_spk"))
                    bt_int_spk = attributes.value("bt_int_spk").toInt();
                if(attributes.hasAttribute("bt_mic_gain"))
                    bt_mic_gain = attributes.value("bt_mic_gain").toInt();
                if(attributes.hasAttribute("bt_spk_gain"))
                    bt_spk_gain = attributes.value("bt_spk_gain").toInt();
                if(attributes.hasAttribute("bt_hold_time"))
                    bt_hold_time = attributes.value("bt_hold_time").toInt();
                if(attributes.hasAttribute("bt_rx_delay"))
                    bt_rx_delay = attributes.value("bt_rx_delay").toInt();
                if(attributes.hasAttribute("bt_ptt_hold"))
                    bt_ptt_hold = attributes.value("bt_ptt_hold").toInt();
                if(attributes.hasAttribute("bt_ptt_sleep_time"))
                    bt_ptt_sleep_time = attributes.value("bt_ptt_sleep_time").toInt();
                if(attributes.hasAttribute("bt_nr_before"))
                    bt_nr_before = attributes.value("bt_nr_before").toInt();
                if(attributes.hasAttribute("bt_nr_after"))
                    bt_nr_after = attributes.value("bt_nr_after").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "STE"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("ste_type_of_ctcss"))
                    ste_type_of_ctcss = attributes.value("ste_type_of_ctcss").toInt();
                if(attributes.hasAttribute("ste_when_no_signal"))
                    ste_when_no_signal = attributes.value("ste_when_no_signal").toInt();
                if(attributes.hasAttribute("ste_time"))
                    ste_time = attributes.value("ste_time").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "FM"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("fm_vfo_mem"))
                    fm_vfo_mem = attributes.value("fm_vfo_mem").toInt();
                if(attributes.hasAttribute("fm_work_channel"))
                    fm_work_channel = attributes.value("fm_work_channel").toInt();
                if(attributes.hasAttribute("fm_monitor"))
                    fm_monitor = attributes.value("fm_monitor").toInt();
                if(attributes.hasAttribute("am_vfo_mem"))
                    am_vfo_mem = attributes.value("am_vfo_mem").toInt();
                if(attributes.hasAttribute("am_work_zone"))
                    am_work_zone = attributes.value("am_work_zone").toInt();
                if(attributes.hasAttribute("am_offset"))
                    am_offset = attributes.value("am_offset").toInt();
                if(attributes.hasAttribute("am_sql_level"))
                    am_sql_level = attributes.value("am_sql_level").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "KeyFunction"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("key_lock"))
                    key_lock = attributes.value("key_lock").toInt();
                if(attributes.hasAttribute("pf1_short_key_D878UVII"))
                    pf1_short_key_D878UVII = attributes.value("pf1_short_key_D878UVII").toInt();
                if(attributes.hasAttribute("pf2_short_key_D878UVII"))
                    pf2_short_key_D878UVII = attributes.value("pf2_short_key_D878UVII").toInt();
                if(attributes.hasAttribute("pf3_short_key_D878UVII"))
                    pf3_short_key_D878UVII = attributes.value("pf3_short_key_D878UVII").toInt();
                if(attributes.hasAttribute("p1_short_key_D878UVII"))
                    p1_short_key_D878UVII = attributes.value("p1_short_key_D878UVII").toInt();
                if(attributes.hasAttribute("p2_short_key_D878UVII"))
                    p2_short_key_D878UVII = attributes.value("p2_short_key_D878UVII").toInt();
                if(attributes.hasAttribute("pf1_long_key_D878UVII"))
                    pf1_long_key_D878UVII = attributes.value("pf1_long_key_D878UVII").toInt();
                if(attributes.hasAttribute("pf2_long_key_D878UVII"))
                    pf2_long_key_D878UVII = attributes.value("pf2_long_key_D878UVII").toInt();
                if(attributes.hasAttribute("pf3_long_key_D878UVII"))
                    pf3_long_key_D878UVII = attributes.value("pf3_long_key_D878UVII").toInt();
                if(attributes.hasAttribute("p1_long_key_D878UVII"))
                    p1_long_key_D878UVII = attributes.value("p1_long_key_D878UVII").toInt();
                if(attributes.hasAttribute("p2_long_key_D878UVII"))
                    p2_long_key_D878UVII = attributes.value("p2_long_key_D878UVII").toInt();
                if(attributes.hasAttribute("pf1_short_key_D890UV"))
                    pf1_short_key_D890UV = attributes.value("pf1_short_key_D890UV").toInt();
                if(attributes.hasAttribute("pf2_short_key_D890UV"))
                    pf2_short_key_D890UV = attributes.value("pf2_short_key_D890UV").toInt();
                if(attributes.hasAttribute("pf3_short_key_D890UV"))
                    pf3_short_key_D890UV = attributes.value("pf3_short_key_D890UV").toInt();
                if(attributes.hasAttribute("p1_short_key_D890UV"))
                    p1_short_key_D890UV = attributes.value("p1_short_key_D890UV").toInt();
                if(attributes.hasAttribute("p2_short_key_D890UV"))
                    p2_short_key_D890UV = attributes.value("p2_short_key_D890UV").toInt();
                if(attributes.hasAttribute("pf1_long_key_D890UV"))
                    pf1_long_key_D890UV = attributes.value("pf1_long_key_D890UV").toInt();
                if(attributes.hasAttribute("pf2_long_key_D890UV"))
                    pf2_long_key_D890UV = attributes.value("pf2_long_key_D890UV").toInt();
                if(attributes.hasAttribute("pf3_long_key_D890UV"))
                    pf3_long_key_D890UV = attributes.value("pf3_long_key_D890UV").toInt();
                if(attributes.hasAttribute("p1_long_key_D890UV"))
                    p1_long_key_D890UV = attributes.value("p1_long_key_D890UV").toInt();
                if(attributes.hasAttribute("p2_long_key_D890UV"))
                    p2_long_key_D890UV = attributes.value("p2_long_key_D890UV").toInt();
                if(attributes.hasAttribute("long_key_time_D890UV"))
                    long_key_time = attributes.value("long_key_time").toInt();
                if(attributes.hasAttribute("knob_lock"))
                    knob_lock = attributes.value("knob_lock").toInt();
                if(attributes.hasAttribute("keyboard_lock"))
                    keyboard_lock = attributes.value("keyboard_lock").toInt();
                if(attributes.hasAttribute("side_key_lock"))
                    side_key_lock = attributes.value("side_key_lock").toInt();
                if(attributes.hasAttribute("forced_key_lock"))
                    forced_key_lock = attributes.value("forced_key_lock").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "Other"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("address_book_sent_with_code"))
                    address_book_sent_with_code = attributes.value("address_book_sent_with_code").toInt();
                if(attributes.hasAttribute("tot"))
                    tot = attributes.value("tot").toInt();
                if(attributes.hasAttribute("language"))
                    language = attributes.value("language").toInt();
                if(attributes.hasAttribute("frequency_step"))
                    frequency_step = attributes.value("frequency_step").toInt();
                if(attributes.hasAttribute("sql_level_a"))
                    sql_level_a = attributes.value("sql_level_a").toInt();
                if(attributes.hasAttribute("sql_level_b"))
                    sql_level_b = attributes.value("sql_level_b").toInt();
                if(attributes.hasAttribute("tbst"))
                    tbst = attributes.value("tbst").toInt();
                if(attributes.hasAttribute("analog_call_hold_time"))
                    analog_call_hold_time = attributes.value("analog_call_hold_time").toInt();
                if(attributes.hasAttribute("call_channel_maintained"))
                    call_channel_maintained = attributes.value("call_channel_maintained").toInt();
                if(attributes.hasAttribute("priority_zone_a"))
                    priority_zone_a = attributes.value("priority_zone_a").toInt();
                if(attributes.hasAttribute("priority_zone_b"))
                    priority_zone_b = attributes.value("priority_zone_b").toInt();
                if(attributes.hasAttribute("mute_timing"))
                    mute_timing = attributes.value("mute_timing").toInt();
                if(attributes.hasAttribute("encryption_type"))
                    encryption_type = attributes.value("encryption_type").toInt();
                if(attributes.hasAttribute("tot_predict"))
                    tot_predict = attributes.value("tot_predict").toInt();
                if(attributes.hasAttribute("tx_power_agc"))
                    tx_power_agc = attributes.value("tx_power_agc").toInt();
                if(attributes.hasAttribute("noaa_moni"))
                    noaa_moni = attributes.value("noaa_moni").toInt();
                if(attributes.hasAttribute("noaa_scan"))
                    noaa_scan = attributes.value("noaa_scan").toInt();
                if(attributes.hasAttribute("noaa"))
                    noaa = attributes.value("noaa").toInt();
                if(attributes.hasAttribute("noaa_channel"))
                    noaa_channel = attributes.value("noaa_channel").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "DigitalFunc"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("group_call_hold_time"))
                    group_call_hold_time = attributes.value("group_call_hold_time").toInt();
                if(attributes.hasAttribute("private_call_hold_time"))
                    private_call_hold_time = attributes.value("private_call_hold_time").toInt();
                if(attributes.hasAttribute("manual_dial_group_call_hold_time"))
                    manual_dial_group_call_hold_time = attributes.value("manual_dial_group_call_hold_time").toInt();
                if(attributes.hasAttribute("manual_dial_private_call_hold_time"))
                    manual_dial_private_call_hold_time = attributes.value("manual_dial_private_call_hold_time").toInt();
                if(attributes.hasAttribute("voice_header_repetitions"))
                    voice_header_repetitions = attributes.value("voice_header_repetitions").toInt();
                if(attributes.hasAttribute("tx_preamble_duration"))
                    tx_preamble_duration = attributes.value("tx_preamble_duration").toInt();
                if(attributes.hasAttribute("filter_own_id"))
                    filter_own_id = attributes.value("filter_own_id").toInt();
                if(attributes.hasAttribute("digital_remote_kill"))
                    digital_remote_kill = attributes.value("digital_remote_kill").toInt();
                if(attributes.hasAttribute("digital_monitor"))
                    digital_monitor = attributes.value("digital_monitor").toInt();
                if(attributes.hasAttribute("digital_monitor_cc"))
                    digital_monitor_cc = attributes.value("digital_monitor_cc").toInt();
                if(attributes.hasAttribute("digital_monitor_id"))
                    digital_monitor_id = attributes.value("digital_monitor_id").toInt();
                if(attributes.hasAttribute("monitor_slot_hold"))
                    monitor_slot_hold = attributes.value("monitor_slot_hold").toInt();
                if(attributes.hasAttribute("remote_monitor"))
                    remote_monitor = attributes.value("remote_monitor").toInt();
                if(attributes.hasAttribute("sms_format"))
                    sms_format = attributes.value("sms_format").toInt();
                if(attributes.hasAttribute("digital_protocol"))
                    digital_protocol = attributes.value("digital_protocol").toInt();
                if(attributes.hasAttribute("reset_digital_protocol"))
                    reset_digital_protocol = attributes.value("reset_digital_protocol").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "AlertTone"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("sms_alert"))
                    sms_alert = attributes.value("sms_alert").toInt();
                if(attributes.hasAttribute("call_alert"))
                    call_alert = attributes.value("call_alert").toInt();
                if(attributes.hasAttribute("digi_call_reset_tone"))
                    digi_call_reset_tone = attributes.value("digi_call_reset_tone").toInt();
                if(attributes.hasAttribute("talk_permit"))
                    talk_permit = attributes.value("talk_permit").toInt();
                if(attributes.hasAttribute("key_tone"))
                    key_tone = attributes.value("key_tone").toInt();
                if(attributes.hasAttribute("digi_idle_channel_tone"))
                    digi_idle_channel_tone = attributes.value("digi_idle_channel_tone").toInt();
                if(attributes.hasAttribute("startup_sound"))
                    startup_sound = attributes.value("startup_sound").toInt();
                if(attributes.hasAttribute("tone_key_sound_adjustable"))
                    tone_key_sound_adjustable = attributes.value("tone_key_sound_adjustable").toInt();
                if(attributes.hasAttribute("analog_idle_channel_tone"))
                    analog_idle_channel_tone = attributes.value("analog_idle_channel_tone").toInt();
                if(attributes.hasAttribute("plugin_recording_tone"))
                    plugin_recording_tone = attributes.value("plugin_recording_tone").toInt();
                if(attributes.hasAttribute("call_permit_first_tone_freq"))
                    call_permit_first_tone_freq = attributes.value("call_permit_first_tone_freq").toInt();
                if(attributes.hasAttribute("call_permit_first_tone_period"))
                    call_permit_first_tone_period = attributes.value("call_permit_first_tone_period").toInt();
                if(attributes.hasAttribute("call_permit_second_tone_freq"))
                    call_permit_second_tone_freq = attributes.value("call_permit_second_tone_freq").toInt();
                if(attributes.hasAttribute("call_permit_second_tone_period"))
                    call_permit_second_tone_period = attributes.value("call_permit_second_tone_period").toInt();
                if(attributes.hasAttribute("call_permit_third_tone_freq"))
                    call_permit_third_tone_freq = attributes.value("call_permit_third_tone_freq").toInt();
                if(attributes.hasAttribute("call_permit_third_tone_period"))
                    call_permit_third_tone_period = attributes.value("call_permit_third_tone_period").toInt();
                if(attributes.hasAttribute("call_permit_fourth_tone_freq"))
                    call_permit_fourth_tone_freq = attributes.value("call_permit_fourth_tone_freq").toInt();
                if(attributes.hasAttribute("call_permit_fourth_tone_period"))
                    call_permit_fourth_tone_period = attributes.value("call_permit_fourth_tone_period").toInt();
                if(attributes.hasAttribute("call_permit_fifth_tone_freq"))
                    call_permit_fifth_tone_freq = attributes.value("call_permit_fifth_tone_freq").toInt();
                if(attributes.hasAttribute("call_permit_fifth_tone_period"))
                    call_permit_fifth_tone_period = attributes.value("call_permit_fifth_tone_period").toInt();
                if(attributes.hasAttribute("idle_channel_first_tone_freq"))
                    idle_channel_first_tone_freq = attributes.value("idle_channel_first_tone_freq").toInt();
                if(attributes.hasAttribute("idle_channel_first_tone_period"))
                    idle_channel_first_tone_period = attributes.value("idle_channel_first_tone_period").toInt();
                if(attributes.hasAttribute("idle_channel_second_tone_freq"))
                    idle_channel_second_tone_freq = attributes.value("idle_channel_second_tone_freq").toInt();
                if(attributes.hasAttribute("idle_channel_second_tone_period"))
                    idle_channel_second_tone_period = attributes.value("idle_channel_second_tone_period").toInt();
                if(attributes.hasAttribute("idle_channel_third_tone_freq"))
                    idle_channel_third_tone_freq = attributes.value("idle_channel_third_tone_freq").toInt();
                if(attributes.hasAttribute("idle_channel_third_tone_period"))
                    idle_channel_third_tone_period = attributes.value("idle_channel_third_tone_period").toInt();
                if(attributes.hasAttribute("idle_channel_fourth_tone_freq"))
                    idle_channel_fourth_tone_freq = attributes.value("idle_channel_fourth_tone_freq").toInt();
                if(attributes.hasAttribute("idle_channel_fourth_tone_period"))
                    idle_channel_fourth_tone_period = attributes.value("idle_channel_fourth_tone_period").toInt();
                if(attributes.hasAttribute("idle_channel_fifth_tone_freq"))
                    idle_channel_fifth_tone_freq = attributes.value("idle_channel_fifth_tone_freq").toInt();
                if(attributes.hasAttribute("idle_channel_fifth_tone_period"))
                    idle_channel_fifth_tone_period = attributes.value("idle_channel_fifth_tone_period").toInt();
                if(attributes.hasAttribute("call_reset_first_tone_freq"))
                    call_reset_first_tone_freq = attributes.value("call_reset_first_tone_freq").toInt();
                if(attributes.hasAttribute("call_reset_first_tone_period"))
                    call_reset_first_tone_period = attributes.value("call_reset_first_tone_period").toInt();
                if(attributes.hasAttribute("call_reset_second_tone_freq"))
                    call_reset_second_tone_freq = attributes.value("call_reset_second_tone_freq").toInt();
                if(attributes.hasAttribute("call_reset_second_tone_period"))
                    call_reset_second_tone_period = attributes.value("call_reset_second_tone_period").toInt();
                if(attributes.hasAttribute("call_reset_third_tone_freq"))
                    call_reset_third_tone_freq = attributes.value("call_reset_third_tone_freq").toInt();
                if(attributes.hasAttribute("call_reset_third_tone_period"))
                    call_reset_third_tone_period = attributes.value("call_reset_third_tone_period").toInt();
                if(attributes.hasAttribute("call_reset_fourth_tone_freq"))
                    call_reset_fourth_tone_freq = attributes.value("call_reset_fourth_tone_freq").toInt();
                if(attributes.hasAttribute("call_reset_fourth_tone_period"))
                    call_reset_fourth_tone_period = attributes.value("call_reset_fourth_tone_period").toInt();
                if(attributes.hasAttribute("call_reset_fifth_tone_freq"))
                    call_reset_fifth_tone_freq = attributes.value("call_reset_fifth_tone_freq").toInt();
                if(attributes.hasAttribute("call_reset_fifth_tone_period"))
                    call_reset_fifth_tone_period = attributes.value("call_reset_fifth_tone_period").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "AlertTone1"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("call_end_first_tone_freq"))
                    call_end_first_tone_freq = attributes.value("call_end_first_tone_freq").toInt();
                if(attributes.hasAttribute("call_end_first_tone_period"))
                    call_end_first_tone_period = attributes.value("call_end_first_tone_period").toInt();
                if(attributes.hasAttribute("call_end_second_tone_freq"))
                    call_end_second_tone_freq = attributes.value("call_end_second_tone_freq").toInt();
                if(attributes.hasAttribute("call_end_second_tone_period"))
                    call_end_second_tone_period = attributes.value("call_end_second_tone_period").toInt();
                if(attributes.hasAttribute("call_end_third_tone_freq"))
                    call_end_third_tone_freq = attributes.value("call_end_third_tone_freq").toInt();
                if(attributes.hasAttribute("call_end_third_tone_period"))
                    call_end_third_tone_period = attributes.value("call_end_third_tone_period").toInt();
                if(attributes.hasAttribute("call_end_fourth_tone_freq"))
                    call_end_fourth_tone_freq = attributes.value("call_end_fourth_tone_freq").toInt();
                if(attributes.hasAttribute("call_end_fourth_tone_period"))
                    call_end_fourth_tone_period = attributes.value("call_end_fourth_tone_period").toInt();
                if(attributes.hasAttribute("call_end_fifth_tone_freq"))
                    call_end_fifth_tone_freq = attributes.value("call_end_fifth_tone_freq").toInt();
                if(attributes.hasAttribute("call_end_fifth_tone_period"))
                    call_end_fifth_tone_period = attributes.value("call_end_fifth_tone_period").toInt();
                if(attributes.hasAttribute("call_all_first_tone_freq"))
                    call_all_first_tone_freq = attributes.value("call_all_first_tone_freq").toInt();
                if(attributes.hasAttribute("call_all_first_tone_period"))
                    call_all_first_tone_period = attributes.value("call_all_first_tone_period").toInt();
                if(attributes.hasAttribute("call_all_second_tone_freq"))
                    call_all_second_tone_freq = attributes.value("call_all_second_tone_freq").toInt();
                if(attributes.hasAttribute("call_all_second_tone_period"))
                    call_all_second_tone_period = attributes.value("call_all_second_tone_period").toInt();
                if(attributes.hasAttribute("call_all_third_tone_freq"))
                    call_all_third_tone_freq = attributes.value("call_all_third_tone_freq").toInt();
                if(attributes.hasAttribute("call_all_third_tone_period"))
                    call_all_third_tone_period = attributes.value("call_all_third_tone_period").toInt();
                if(attributes.hasAttribute("call_all_fourth_tone_freq"))
                    call_all_fourth_tone_freq = attributes.value("call_all_fourth_tone_freq").toInt();
                if(attributes.hasAttribute("call_all_fourth_tone_period"))
                    call_all_fourth_tone_period = attributes.value("call_all_fourth_tone_period").toInt();
                if(attributes.hasAttribute("call_all_fifth_tone_freq"))
                    call_all_fifth_tone_freq = attributes.value("call_all_fifth_tone_freq").toInt();
                if(attributes.hasAttribute("call_all_fifth_tone_period"))
                    call_all_fifth_tone_period = attributes.value("call_all_fifth_tone_period").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "GPSRanging"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("gps_power"))
                    gps_power = attributes.value("gps_power").toInt();
                if(attributes.hasAttribute("gps_positioning"))
                    gps_positioning = attributes.value("gps_positioning").toInt();
                if(attributes.hasAttribute("time_zone"))
                    time_zone = attributes.value("time_zone").toInt();
                if(attributes.hasAttribute("ranging_interval"))
                    ranging_interval = attributes.value("ranging_interval").toInt();
                if(attributes.hasAttribute("distance_unit"))
                    distance_unit = attributes.value("distance_unit").toInt();
                if(attributes.hasAttribute("gps_template_information"))
                    gps_template_information = attributes.value("gps_template_information").toInt();
                if(attributes.hasAttribute("gps_mode"))
                    gps_mode = attributes.value("gps_mode").toInt();
                if(attributes.hasAttribute("gps_roaming"))
                    gps_roaming = attributes.value("gps_roaming").toInt();
                if(attributes.hasAttribute("gps_information_char"))
                    gps_information_char = attributes.value("gps_information_char").toString();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "VFOScan"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("vfo_scan_type"))
                    vfo_scan_type = attributes.value("vfo_scan_type").toInt();
                if(attributes.hasAttribute("vfo_scan_start_freq_uhf"))
                    vfo_scan_start_freq_uhf = attributes.value("vfo_scan_start_freq_uhf").toInt();
                if(attributes.hasAttribute("vfo_scan_end_freq_uhf"))
                    vfo_scan_end_freq_uhf = attributes.value("vfo_scan_end_freq_uhf").toInt();
                if(attributes.hasAttribute("vfo_scan_start_freq_vhf"))
                    vfo_scan_start_freq_vhf = attributes.value("vfo_scan_start_freq_vhf").toInt();
                if(attributes.hasAttribute("vfo_scan_end_freq_vhf"))
                    vfo_scan_end_freq_vhf = attributes.value("vfo_scan_end_freq_vhf").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "AutoRepeater"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("auto_repeater_a"))
                    auto_repeater_a = attributes.value("auto_repeater_a").toInt();
                if(attributes.hasAttribute("auto_repeater_b"))
                    auto_repeater_b = attributes.value("auto_repeater_b").toInt();
                if(attributes.hasAttribute("auto_repeater_1_uhf"))
                    auto_repeater_1_uhf = attributes.value("auto_repeater_1_uhf").toInt();
                if(attributes.hasAttribute("auto_repeater_1_vhf"))
                    auto_repeater_1_vhf = attributes.value("auto_repeater_1_vhf").toInt();
                if(attributes.hasAttribute("auto_repeater_2_uhf"))
                    auto_repeater_2_uhf = attributes.value("auto_repeater_2_uhf").toInt();
                if(attributes.hasAttribute("auto_repeater_2_vhf"))
                    auto_repeater_2_vhf = attributes.value("auto_repeater_2_vhf").toInt();
                if(attributes.hasAttribute("repeater_check"))
                    repeater_check = attributes.value("repeater_check").toInt();
                if(attributes.hasAttribute("repeater_check_interval"))
                    repeater_check_interval = attributes.value("repeater_check_interval").toInt();
                if(attributes.hasAttribute("repeater_check_reconnections"))
                    repeater_check_reconnections = attributes.value("repeater_check_reconnections").toInt();
                if(attributes.hasAttribute("repeater_out_of_range_notify"))
                    repeater_out_of_range_notify = attributes.value("repeater_out_of_range_notify").toInt();
                if(attributes.hasAttribute("out_of_range_notify"))
                    out_of_range_notify = attributes.value("out_of_range_notify").toInt();
                if(attributes.hasAttribute("auto_roaming"))
                    auto_roaming = attributes.value("auto_roaming").toInt();
                if(attributes.hasAttribute("auto_roaming_start_condition"))
                    auto_roaming_start_condition = attributes.value("auto_roaming_start_condition").toInt();
                if(attributes.hasAttribute("auto_roaming_fixed_time"))
                    auto_roaming_fixed_time = attributes.value("auto_roaming_fixed_time").toInt();
                if(attributes.hasAttribute("roaming_effect_wait_time"))
                    roaming_effect_wait_time = attributes.value("roaming_effect_wait_time").toInt();
                if(attributes.hasAttribute("roaming_zone"))
                    roaming_zone = attributes.value("roaming_zone").toInt();
                if(attributes.hasAttribute("auto_repeater_1_min_freq_vhf"))
                    auto_repeater_1_min_freq_vhf = attributes.value("auto_repeater_1_min_freq_vhf").toInt();
                if(attributes.hasAttribute("auto_repeater_1_max_freq_vhf"))
                    auto_repeater_1_max_freq_vhf = attributes.value("auto_repeater_1_max_freq_vhf").toInt();
                if(attributes.hasAttribute("auto_repeater_1_min_freq_uhf"))
                    auto_repeater_1_min_freq_uhf = attributes.value("auto_repeater_1_min_freq_uhf").toInt();
                if(attributes.hasAttribute("auto_repeater_1_max_freq_uhf"))
                    auto_repeater_1_max_freq_uhf = attributes.value("auto_repeater_1_max_freq_uhf").toInt();
                if(attributes.hasAttribute("auto_repeater_2_min_freq_vhf"))
                    auto_repeater_2_min_freq_vhf = attributes.value("auto_repeater_2_min_freq_vhf").toInt();
                if(attributes.hasAttribute("auto_repeater_2_max_freq_vhf"))
                    auto_repeater_2_max_freq_vhf = attributes.value("auto_repeater_2_max_freq_vhf").toInt();
                if(attributes.hasAttribute("auto_repeater_2_min_freq_uhf"))
                    auto_repeater_2_min_freq_uhf = attributes.value("auto_repeater_2_min_freq_uhf").toInt();
                if(attributes.hasAttribute("auto_repeater_2_max_freq_uhf"))
                    auto_repeater_2_max_freq_uhf = attributes.value("auto_repeater_2_max_freq_uhf").toInt();
                if(attributes.hasAttribute("repeater_mode"))
                    repeater_mode = attributes.value("repeater_mode").toInt();
                if(attributes.hasAttribute("rep_cc_limit"))
                    rep_cc_limit = attributes.value("rep_cc_limit").toInt();
                if(attributes.hasAttribute("rep_slot_a"))
                    rep_slot_a = attributes.value("rep_slot_a").toInt();
                if(attributes.hasAttribute("rep_slot_b"))
                    rep_slot_b = attributes.value("rep_slot_b").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "Record"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("record_function"))
                    record_function = attributes.value("record_function").toInt();
                if(attributes.hasAttribute("record_delay"))
                    record_delay = attributes.value("record_delay").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "VolumeAudio"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("max_volume"))
                    max_volume = attributes.value("max_volume").toInt();
                if(attributes.hasAttribute("max_headphone_volume"))
                    max_headphone_volume = attributes.value("max_headphone_volume").toInt();
                if(attributes.hasAttribute("digi_mic_gain"))
                    digi_mic_gain = attributes.value("digi_mic_gain").toInt();
                if(attributes.hasAttribute("enhanced_sound_quality"))
                    enhanced_sound_quality = attributes.value("enhanced_sound_quality").toInt();
                if(attributes.hasAttribute("analog_mic_gain"))
                    analog_mic_gain = attributes.value("analog_mic_gain").toInt();
                if(attributes.hasAttribute("power_on_volume_type"))
                    power_on_volume_type = attributes.value("power_on_volume_type").toInt();
                if(attributes.hasAttribute("power_on_volume"))
                    power_on_volume = attributes.value("power_on_volume").toInt();
                if(attributes.hasAttribute("rx_agc"))
                    rx_agc = attributes.value("rx_agc").toInt();
                if(attributes.hasAttribute("nx_mic_gain"))
                    nx_mic_gain = attributes.value("nx_mic_gain").toInt();
            }else if(token == QXmlStreamReader::StartElement && xml.name() == "Satellite"){
                QXmlStreamAttributes attributes = xml.attributes();
                if(attributes.hasAttribute("sat_location"))
                    sat_location = attributes.value("sat_location").toInt();
                if(attributes.hasAttribute("sat_tx_power"))
                    sat_tx_power = attributes.value("sat_tx_power").toInt();
                if(attributes.hasAttribute("sat_ana_sql"))
                    sat_ana_sql = attributes.value("sat_ana_sql").toInt();
                if(attributes.hasAttribute("sat_aos_limit"))
                    sat_aos_limit = attributes.value("sat_aos_limit").toInt();
            }else if(token == QXmlStreamReader::StartElement){
                break;
            }
            token = xml.readNext();
        }
    }
}

