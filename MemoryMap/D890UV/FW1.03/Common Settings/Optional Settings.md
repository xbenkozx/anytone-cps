# Optional Setting
| Address | Length | Data |
| - | - | - |
| 0x2501470 | 0x3 | ?? 0xffffff |

## Power-on
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500006 | 0x1 | int | Power-on Interface |
| 0x3500007 | 0x1 | int | Power-on Password |
| 0x35000d6 | 0x1 | int | Default Startup Channel |
| 0x35000d7 | 0x1 | int | Startup Zone A |
| 0x35000d8 | 0x1 | int | Startup Zone B |
| 0x35000d9 | 0x1 | int | Startup Channel A (0xff = VFO) |
| 0x35000da | 0x1 | int | Startup Channel B |
| 0x35000eb? | 0x1 | int | Startup GPS Test (Not written) |
| 0x35000ea | 0x1 | int | Startup Reset |
| 0x3500900 | 0x1b | string(14) | Power-on Display Line 1 |
| 0x3500920 | 0x1b | string(14) | Power-on Display Line 2 |
| 0x3500940 | 0x8 | string(8) | Power-on Password Char |

## Alert Tone
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500029 | 0x1 | int | SMS Alert |
| 0x350002f | 0x1 | int | Call Alert |
| 0x3500032 | 0x1 | int | Digi Call ResetTone |
| 0x3500031 | 0x1 | int | Talk Permit |
| 0x3500000 | 0x1 | int | Key Tone |
| 0x3500036 | 0x1 | int | Digi Idle Channel Tone |
| 0x3500039 | 0x1 | int | Startup Sound |
| 0x35000bb | 0x1 | int | Tone/Key Sound Adjustable |
| 0x3500111 | 0x1 | int | Ana Idle Channel Tone |
| 0x35000b4 | 0x1 | int | Plug-in Recording Tone |
| 0x3500072 | 0x2 | int (BE) | Call Permit First Tone Frequency |
| 0x350007c | 0x2 | int (BE) | Call Permit First Tone Period * 10 |
| 0x3500074 | 0x2 | int (BE) | Call Permit Second Tone Frequency |
| 0x350007e | 0x2 | int (BE) | Call Permit Second Tone Period * 10 |
| 0x3500076 | 0x2 | int (BE) | Call Permit Third Tone Frequency |
| 0x3500080 | 0x2 | int (BE) | Call Permit Third Tone Period * 10 |
| 0x3500078 | 0x2 | int (BE) | Call Permit Fourth Tone Frequency |
| 0x3500082 | 0x2 | int (BE) | Call Permit Fourth Tone Period * 10 |
| 0x350007a | 0x2 | int (BE) | Call Permit Fifth Tone Frequency |
| 0x3500084 | 0x2 | int (BE) | Call Permit Fifth Tone Period * 10 |
| 0x3500086 | 0x2 | int (BE) | Idle Channel First Tone Frequency |
| 0x3500090 | 0x2 | int (BE) | Idle Channel First Tone Period |
| 0x3500088 | 0x2 | int (BE) | Idle Channel Second Tone Frequency |
| 0x3500092 | 0x2 | int (BE) | Idle Channel Second Tone Period |
| 0x350008a | 0x2 | int (BE) | Idle Channel Third Tone Frequency |
| 0x3500094 | 0x2 | int (BE) | Idle Channel Third Tone Period |
| 0x350008c | 0x2 | int (BE) | Idle Channel Fourth Tone Frequency |
| 0x3500096 | 0x2 | int (BE) | Idle Channel Fourth Tone Period |
| 0x350008e | 0x2 | int (BE) | Idle Channel Fifth Tone Frequency |
| 0x3500098 | 0x2 | int (BE) | Idle Channel Fifth Tone Period |
| 0x350009a | 0x2 | int (BE) | Call Reset First Tone Frequency |
| 0x35000a4 | 0x2 | int (BE) | Call Reset First Tone Period |
| 0x350009c | 0x2 | int (BE) | Call Reset Second Tone Frequency |
| 0x35000a6 | 0x2 | int (BE) | Call Reset Second Tone Period |
| 0x350009e | 0x2 | int (BE) | Call Reset Third Tone Frequency |
| 0x35000a8 | 0x2 | int (BE) | Call Reset Third Tone Period |
| 0x35000a0 | 0x2 | int (BE) | Call Reset Fourth Tone Frequency |
| 0x35000aa | 0x2 | int (BE) | Call Reset Fourth Tone Period |
| 0x35000a2 | 0x2 | int (BE) | Call Reset Fifth Tone Frequency |
| 0x35000ac | 0x2 | int (BE) | Call Reset Fifth Tone Period |


## Alert Tone 1
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500116 | 0x2 | int (BE) | Call End Tone First Tone Frequency |
| 0x3500120 | 0x2 | int (BE) | Call End Tone First Tone Period |
| 0x3500118 | 0x2 | int (BE) | Call End Tone Second Tone Frequency |
| 0x3500122 | 0x2 | int (BE) | Call End Tone Second Tone Period |
| 0x350011a | 0x2 | int (BE) | Call End Tone Third Tone Frequency |
| 0x3500124 | 0x2 | int (BE) | Call End Tone Third Tone Period |
| 0x350011c | 0x2 | int (BE) | Call End Tone Fourth Tone Frequency |
| 0x3500126 | 0x2 | int (BE) | Call End Tone Fourth Tone Period |
| 0x350011e | 0x2 | int (BE) | Call End Tone Fifth Tone Frequency |
| 0x3500128 | 0x2 | int (BE) | Call End Tone Fifth Tone Period |
| 0x350012a | 0x2 | int (BE) | Call All Tone First Tone Frequency |
| 0x3500134 | 0x2 | int (BE) | Call All Tone First Tone Period |
| 0x350012b | 0x2 | int (BE) | Call All Tone Second Tone Frequency |
| 0x3500136 | 0x2 | int (BE) | Call All Tone Second Tone Period |
| 0x350012e | 0x2 | int (BE) | Call All Tone Third Tone Frequency |
| 0x3500138 | 0x2 | int (BE) | Call All Tone Third Tone Period |
| 0x3500130 | 0x2 | int (BE) | Call All Tone Fourth Tone Frequency |
| 0x350013a | 0x2 | int (BE) | Call All Tone Fourth Tone Period |
| 0x3500132 | 0x2 | int (BE) | Call All Tone Fifth Tone Frequency |
| 0x350013c | 0x2 | int (BE) | Call All Tone Fifth Tone Period |

## Display
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500026 | 0x1 | int | Brightness |
| 0x3500027 | 0x1 | int | Auto Backlight Duration |
| 0x35000e1 | 0x1 | int | Backlight Delay of TX |
| 0x3500037 | 0x1 | int | Menu Exit Time |
| 0x3500051 | 0x1 | int | Time Display |
| 0x350004d | 0x1 | int | Last Caller |
| 0x35000af | 0x1 | int | Call Display Mode |
| 0x35000bc | 0x1 | int | Call Sign Display Color |
| 0x350003a | 0x1 | int | Call End Prompt Box |
| 0x35000b8 | 0x1 | int | Display Channel Number |
| 0x35000b9 | 0x1 | int | Display Current Contact |
| 0x35000c0 | 0x1 | int | Standby Char Color |
| 0x35000c1 | 0x1 | int | Standby BK Picture |
| 0x35000c2 | 0x1 | int | Show Last Call On Launch |
| 0x35000e1 | 0x1 | int | Separate Display |
| 0x35000e2 | 0x1 | int | CH Switching Keeps Last Caller |
| 0x35000e3 | 0x1 | int | A Channel Name Color |
| 0x35000e5 | 0x1 | int | Receive Backlight Delay |
| 0x3500109 | 0x1 | int | B Channel Name Color |
| 0x350010d | 0x1 | int | Zone Name Color A |
| 0x350010e | 0x1 | int | Zone Name Color B |
| 0x3500110 | 0x1{0} | bool | Display Channel Type |
| 0x3500110 | 0x1{1} | bool | Display Time Slot |
| 0x3500110 | 0x1{3} | bool | Display Color Code |
| 0x3500112 | 0x1 | int | Date Display Format |
| 0x3500047 | 0x1 | int | Volume Bar |

## GPS/Ranging
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500028 | 0x1 | int | GPS (Power) |
| 0x350003f | 0x1 | int | Get GPS Positioning |
| 0x3500030 | 0x1 | int | Time Zone |
| 0x35000b5 | 0x1 | int | Ranging Interval |
| 0x35000bd | 0x1 | int | Distance Unit |
| 0x3500053 | 0x1 | int | GPS Template Information |
| 0x3501280 | 0x40 | int | GPS Information Char |
| 0x3500105 | 0x1 | int | GPS Mode |
| 0x3500114 | 0x1 | int | GPS Roaming |

## VFO Scan
| Address | Length | Type | Data |
| - | - | - | - |
| 0x350000e | 0x1 | int (BE) | VFO Scan Type |
| 0x3500058 | 0x4 | int (BE) | VFO Scan Start Freq (UHF) / 100000 |
| 0x350005c | 0x4 | int (BE) | VFO Scan End Freq (UHF) / 100000  |
| 0x3500060 | 0x4 | int (BE) | VFO Scan Start Freq (VHF) / 100000  |
| 0x3500064 | 0x4 | int (BE) | VFO Scan End Freq (VHF) / 100000  |

## Auto Repeater
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500048 | 0x1 | int | Auto Repeater A |
| 0x35000d4 | 0x1 | int | Auto Repeater B |
| 0x3500068 | 0x1 | int | Auto Repeater 1 (UHF) (0xff = off) |
| 0x3500069 | 0x1 | int | Auto Repeater 1 (VHF) (0xff = off) |
| 0x35000f1 | 0x1 | int | Auto Repeater 2 (UHF) (0xff = off) |
| 0x35000f2 | 0x1 | int | Auto Repeater 2 (VHF) (0xff = off) |
| 0x35000dd | 0x1 | int | Repeater Check |
| 0x35000de | 0x1 | int | Repeater Check Interval |
| 0x35000df | 0x1 | int | Repeater Check Reconnections |
| 0x35000e5 | 0x1 | int | Repeater Out of Range Notify |
| 0x35000ea | 0x1 | int | Out of Range Notify |
| 0x35000e7 | 0x1 | int | Auto Roaming |
| 0x35000e0 | 0x1 | int | Auto Roaming Start Condition |
| 0x35000ba | 0x1 | int | Auto Roaming at Fixed Time |
| 0x35000bf | 0x1 | int | Roaming Effect Wait Time |
| 0x35000d5 | 0x1 | int | Roaming Zone |
| 0x35000c4 | 0x4 | int (BE) | Min Freq Of Auto Repeater 1 (VHF) |
| 0x35000c8 | 0x4 | int (BE) | Max Freq Of Auto Repeater 1 (VHF) |
| 0x35000cc | 0x4 | int (BE) | Min Freq Of Auto Repeater 1 (UHF) |
| 0x35000d0 | 0x4 | int (BE) | Max Freq Of Auto Repeater 1 (UHF) |
| 0x35000f4 | 0x4 | int (BE) | Min Freq Of Auto Repeater 2 (VHF) |
| 0x35000f8 | 0x4 | int (BE) | Max Freq Of Auto Repeater 2 (VHF) |
| 0x35000fc | 0x4 | int (BE) | Min Freq Of Auto Repeater 2 (UHF) |
| 0x3500100 | 0x4 | int (BE) | Max Freq Of Auto Repeater 2 (UHF) |
| 0x3500143 | 0x1 | int | Repeater Mode |
| 0x3500144 | 0x1 | int | Rep Cc Limit |
| 0x3500145 | 0x1 | int | Rep Slot Path A |
| 0x3500146 | 0x1 | int | Rep Slot Path B |

## Record
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500022 | 0x1 | int | Record Function |
| 0x35000ae | 0x1 | int | Record Delay |

## Volume/Audio
| Address | Length | Type | Data |
| - | - | - | - |
| 0x350003b | 0x1 | Max Volume |
| 0x3500155 | 0x1 | Power On Volume Type |
| 0x3500156 | 0x1 | Power On Volume |
| 0x3500052 | 0x1 | Max Headphone Volume |
| 0x350000f | 0x1 | Digi Mic Gain |
| 0x3500057 | 0x1 | Enhanced Sound Quality |
| 0x3501133 | 0x1 | Ana Mic Gain |
| 0x3500147 | 0x1 | Rx AGC |
| 0x3500153 | 0x1 | NX Mic Gain |

## Work Mode
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500001 | 0x1 | Display Mode |
| 0x3500015 | 0x1 | VF/MR A |
| 0x350001f | 0x1 | MEM Zone A |
| 0x3500016 | 0x1 | VF/MR B |
| 0x3500020 | 0x1 | MEM Zone B |
| 0x350002c | 0x1 | Main Channel Set |
| 0x350002d | 0x1 | Sub-Channel Mode |
| 0x3500034 | 0x1 | Working Mode |

## Vox/BT
| Address | Length | Type | Data |
| - | - | - | - |
| 0x350000c | 0x1 | VOX Level |
| 0x350000d | 0x1 | VOX Delay |
| 0x3500033 | 0x1 | VOX Detection |
| 0x35000b1 | 0x1 | BT On/Off |
| 0x35000b2 | 0x1 | BT + int Mic |
| 0x35000b3 | 0x1 | BT + int Spk |
| 0x35000b6 | 0x1 | BT Mic Gain |
| 0x35000b7 | 0x1 | BT Spk Gain |
| 0x35000eb | 0x1 | BT Hold Time |
| 0x35000ec | 0x1 | BT RX Delay |
| 0x35000f0 | 0x1 | BT PTT Hold |
| 0x3500104 | 0x1 | PTT Sleep Time |
| 0x350014b | 0x1 | BT NR Before |
| 0x350014c | 0x1 | BT NR After |

## STE
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500017 | 0x1 | STE Type Of CTCSS |
| 0x3500018 | 0x1 | STE When No Signal |
| 0x3500106 | 0x1 | STE Time |

## FM
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500021 | 0x1 | AM/FM Function |
| 0x350001e | 0x1 | FM VFO/MEM |
| 0x350001d | 0x1 | FM Work Channel |
| 0x350002b | 0x1 | FM Monitor |
| 0x350013f | 0x1 | AM VFO/MEM |
| 0x3500140 | 0x1 | AM Work Zone |
| 0x3500141 | 0x1 | AM Offset |
| 0x3500142 | 0x1 | AM Sql Level |

## Power Save
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500003 | 0x1 | Auto Shutdown |
| 0x350000b | 0x1 | Power Save |
| 0x350010f | 0x1 | Auto Shutdown Type |

## Key Function
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500002 | 0x1 | Key Lock |
| 0x3500010 | 0x1 | PF1 Short Key |
| 0x3500011 | 0x1 | PF2 Short Key |
| 0x3500012 | 0x1 | PF3 Short Key |
| 0x3500013 | 0x1 | P1 Short Key |
| 0x3500014 | 0x1 | P2 Short Key |
| 0x3500041 | 0x1 | PF1 Long Key |
| 0x3500042 | 0x1 | PF2 Long Key |
| 0x3500043 | 0x1 | PF3 Long Key |
| 0x3500044 | 0x1 | P1 Long Key |
| 0x3500045 | 0x1 | P2 Long Key |
| 0x3500046 | 0x1 | Long Key Time |
| 0x35000be{0}? | b1 | Knob Lock |
| 0x35000be{1}? | b1 | Keyboard Lock |
| 0x35000be{3}? | b1 | Side Key Lock |
| 0x35000be{4}? | b1 | Forced Key Lock |

## Other
| Address | Length | Type | Data |
| - | - | - | - |
| 0x35000d5 | 0x1 | Address Book Is Sent With Its Own Code |
| 0x3500004 | 0x1 | TOT |
| 0x3500005 | 0x1 | Language |
| 0x3500008 | 0x1 | Frequency Step |
| 0x3500009 | 0x1 | SQL Level A |
| 0x350000a | 0x1 | SQL Level B |
| 0x350002e | 0x1 | TBST |
| 0x3500050 | 0x1 | Analog Call Hold Time |
| 0x350006e | 0x1 | Call Channel Is Maintained |
| 0x350006f | 0x1 | Priority Zone A (Zone Index - 1; 0xff = ZONE0)|
| 0x3500070 | 0x1 | Priority Zone B |
| 0x35000e8 | 0x1 | Mute Timing |
| 0x350010a | 0x1 | Encryption Type |
| 0x350010b | 0x1 | TOT Predict |
| 0x350010c | 0x1 | TX Power AGC |
| 0x3500157 | 0x1 | NOAA Moni |
| 0x3500158 | 0x1 | NOAA Scan |
| 0x35000ef | 0x1 | NOAA |
| 0x350013e | 0x1 | NOAA Channel |

## Digital Func
| Address | Length | Type | Data |
| - | - | - | - |
| 0x3500019 | 0x1 | Group Call Hold Time |
| 0x350001a | 0x1 | Private Call Hold Time |
| 0x3500107 | 0x1 | Manual Dial - Group TG Hold Time |
| 0x3500108 | 0x1 | Manual Dial - Private TG Hold Time |
| 0x350001b | 0x1 | Voice Header Repetitions |
| 0x350001c | 0x1 | TX Preamble Duration |
| 0x3500038 | 0x1 | Filter Own ID in MissCall |
| 0x350003c | 0x1 | Digital Remote Kill |
| 0x3500049 | 0x1 | Digital Monitor |
| 0x350004a | 0x1 | Digital Monitor CC |
| 0x350004b | 0x1 | Digital Montior ID |
| 0x350004c | 0x1 | Monitor Slot Hold |
| 0x350003e | 0x1 | Remote Monitor |
| 0x35000c3 | 0x1 | SMS Format |
| 0x | 0x1 | Digital Protocol (Can't Change Yet) |
| 0x3500154 | 0x1 | Reset Digital Protocol |

## Satellite
| Address | Length | Type | Data |
| - | - | - | - | - |
| 0x350014e | 0x1 | int | Sat Location |
| 0x350100d | 0x1 | int | Sat Location |
| 0x350014f | 0x1 | int | Sat TX Power |
| 0x3500150 | 0x1 | int | Sat Ana SQL |
| 0x3500151 | 0x1 | int | Sat AOS |