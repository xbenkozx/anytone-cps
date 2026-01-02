#include "optional_settings.h"

void Anytone::OptionalSettings::decode(QByteArray data_0000, QByteArray data_0600, QByteArray data_1280, QByteArray data_1400){
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
    bt_on_off = static_cast<uint8_t>(data_0000.at(0xb1));
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
    pf1_short_key = static_cast<uint8_t>(data_0000.at(0x10));
    pf2_short_key = static_cast<uint8_t>(data_0000.at(0x11));
    pf3_short_key = static_cast<uint8_t>(data_0000.at(0x12));
    p1_short_key = static_cast<uint8_t>(data_0000.at(0x13));
    p2_short_key = static_cast<uint8_t>(data_0000.at(0x14));
    pf1_long_key = static_cast<uint8_t>(data_0000.at(0x41));
    pf2_long_key = static_cast<uint8_t>(data_0000.at(0x42));
    pf3_long_key = static_cast<uint8_t>(data_0000.at(0x43));
    p1_long_key = static_cast<uint8_t>(data_0000.at(0x44));
    p2_long_key = static_cast<uint8_t>(data_0000.at(0x45));
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
    data_250146f = static_cast<uint8_t>(data_1400.at(0x6f));

    poweron_password_char.remove(QChar('\0'));
    gps_information_char.remove(QChar('\0'));
}
void Anytone::OptionalSettings::encode(QByteArray &data_2500000, QByteArray &data_2500600, QByteArray &data_2501280, QByteArray &data_2501400){
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
    data_2500000[0xb1] = bt_on_off;
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
    data_2500000[0x10] = pf1_short_key;
    data_2500000[0x11] = pf2_short_key;
    data_2500000[0x12] = pf3_short_key;
    data_2500000[0x13] = p1_short_key;
    data_2500000[0x14] = p2_short_key;
    data_2500000[0x41] = pf1_long_key;
    data_2500000[0x42] = pf2_long_key;
    data_2500000[0x43] = pf3_long_key;
    data_2500000[0x44] = p1_long_key;
    data_2500000[0x45] = p2_long_key;
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
    // AnyToneMemory.optional_settings.gps_roaming = int(data_0000[0x])

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

    // Unknown
    data_2501400[0x6f] = data_250146f;
}



