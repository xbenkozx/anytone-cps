# Optional Setting
| Address | Length | Data |
| - | - | - |
| 0x2501470 | 0x3 | ?? 0xffffff |

## Power-on
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500006 | 0x1 | int | Power-on Interface |
| 0x2500007 | 0x1 | int | Power-on Password |
| 0x25000d7 | 0x1 | int | Default Startup Channel |
| 0x25000d8 | 0x1 | int | Startup Zone A |
| 0x25000d9 | 0x1 | int | Startup Zone B |
| 0x25000da | 0x1 | int | Startup Channel A (0xff = VFO) |
| 0x25000db | 0x1 | int | Startup Channel B |
| 0x25000eb | 0x1 | int | Startup GPS Test |
| 0x25000ec | 0x1 | int | Startup Reset |
| 0x2500600 | 0xe | string(14) | Power-on Display Line 1 |
| 0x2500610 | 0xe | string(14) | Power-on Display Line 2 |
| 0x2500620 | 0x8 | string(8) | Power-on Password Char |

## Alert Tone
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500029 | 0x1 | int | SMS Alert |
| 0x250002f | 0x1 | int | Call Alert |
| 0x2500032 | 0x1 | int | Digi Call ResetTone |
| 0x2500031 | 0x1 | int | Talk Permit |
| 0x2500000 | 0x1 | int | Key Tone |
| 0x2500036 | 0x1 | int | Digi Idle Channel Tone |
| 0x2500039 | 0x1 | int | Startup Sound |
| 0x25000bb | 0x1 | int | Tone/Key Sound Adjustable |
| 0x2501441 | 0x1 | int | Ana Idle Channel Tone |
| 0x25000b4 | 0x1 | int | Plug-in Recording Tone |
| 0x2500072 | 0x2 | int (BE) | Call Permit First Tone Frequency |
| 0x250007c | 0x2 | int (BE) | Call Permit First Tone Period * 10 |
| 0x2500074 | 0x2 | int (BE) | Call Permit Second Tone Frequency |
| 0x250007e | 0x2 | int (BE) | Call Permit Second Tone Period * 10 |
| 0x2500076 | 0x2 | int (BE) | Call Permit Third Tone Frequency |
| 0x2500080 | 0x2 | int (BE) | Call Permit Third Tone Period * 10 |
| 0x2500078 | 0x2 | int (BE) | Call Permit Fourth Tone Frequency |
| 0x2500082 | 0x2 | int (BE) | Call Permit Fourth Tone Period * 10 |
| 0x250007a | 0x2 | int (BE) | Call Permit Fifth Tone Frequency |
| 0x2500084 | 0x2 | int (BE) | Call Permit Fifth Tone Period * 10 |
| 0x2500086 | 0x2 | int (BE) | Idle Channel First Tone Frequency |
| 0x2500090 | 0x2 | int (BE) | Idle Channel First Tone Period |
| 0x2500088 | 0x2 | int (BE) | Idle Channel Second Tone Frequency |
| 0x2500092 | 0x2 | int (BE) | Idle Channel Second Tone Period |
| 0x250008a | 0x2 | int (BE) | Idle Channel Third Tone Frequency |
| 0x2500094 | 0x2 | int (BE) | Idle Channel Third Tone Period |
| 0x250008c | 0x2 | int (BE) | Idle Channel Fourth Tone Frequency |
| 0x2500096 | 0x2 | int (BE) | Idle Channel Fourth Tone Period |
| 0x250008e | 0x2 | int (BE) | Idle Channel Fifth Tone Frequency |
| 0x2500098 | 0x2 | int (BE) | Idle Channel Fifth Tone Period |
| 0x250009a | 0x2 | int (BE) | Call Reset First Tone Frequency |
| 0x25000a4 | 0x2 | int (BE) | Call Reset First Tone Period |
| 0x250009c | 0x2 | int (BE) | Call Reset Second Tone Frequency |
| 0x25000a6 | 0x2 | int (BE) | Call Reset Second Tone Period |
| 0x250009e | 0x2 | int (BE) | Call Reset Third Tone Frequency |
| 0x25000a8 | 0x2 | int (BE) | Call Reset Third Tone Period |
| 0x25000a0 | 0x2 | int (BE) | Call Reset Fourth Tone Frequency |
| 0x25000aa | 0x2 | int (BE) | Call Reset Fourth Tone Period |
| 0x25000a2 | 0x2 | int (BE) | Call Reset Fifth Tone Frequency |
| 0x25000ac | 0x2 | int (BE) | Call Reset Fifth Tone Period |


## Alert Tone 1
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2501446 | 0x2 | int (BE) | Call End Tone First Tone Frequency |
| 0x2501450 | 0x2 | int (BE) | Call End Tone First Tone Period |
| 0x2501448 | 0x2 | int (BE) | Call End Tone Second Tone Frequency |
| 0x2501452 | 0x2 | int (BE) | Call End Tone Second Tone Period |
| 0x250144a | 0x2 | int (BE) | Call End Tone Third Tone Frequency |
| 0x2501454 | 0x2 | int (BE) | Call End Tone Third Tone Period |
| 0x250144c | 0x2 | int (BE) | Call End Tone Fourth Tone Frequency |
| 0x2501456 | 0x2 | int (BE) | Call End Tone Fourth Tone Period |
| 0x250144e | 0x2 | int (BE) | Call End Tone Fifth Tone Frequency |
| 0x2501458 | 0x2 | int (BE) | Call End Tone Fifth Tone Period |
| 0x250145a | 0x2 | int (BE) | Call All Tone First Tone Frequency |
| 0x2501464 | 0x2 | int (BE) | Call All Tone First Tone Period |
| 0x250145b | 0x2 | int (BE) | Call All Tone Second Tone Frequency |
| 0x2501466 | 0x2 | int (BE) | Call All Tone Second Tone Period |
| 0x250145e | 0x2 | int (BE) | Call All Tone Third Tone Frequency |
| 0x2501468 | 0x2 | int (BE) | Call All Tone Third Tone Period |
| 0x2501460 | 0x2 | int (BE) | Call All Tone Fourth Tone Frequency |
| 0x250146a | 0x2 | int (BE) | Call All Tone Fourth Tone Period |
| 0x2501462 | 0x2 | int (BE) | Call All Tone Fifth Tone Frequency |
| 0x250146c | 0x2 | int (BE) | Call All Tone Fifth Tone Period |

## Display
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500026 | 0x1 | int | Brightness |
| 0x2500027 | 0x1 | int | Auto Backlight Duration |
| 0x25000e1 | 0x1 | int | Backlight Delay of TX |
| 0x2500037 | 0x1 | int | Menu Exit Time |
| 0x2500051 | 0x1 | int | Time Display |
| 0x250004d | 0x1 | int | Last Caller |
| 0x25000af | 0x1 | int | Call Display Mode |
| 0x25000bc | 0x1 | int | Call Sign Display Color |
| 0x250003a | 0x1 | int | Call End Prompt Box |
| 0x25000b8 | 0x1 | int | Display Channel Number |
| 0x25000b9 | 0x1 | int | Display Current Contact |
| 0x25000c0 | 0x1 | int | Standby Char Color |
| 0x25000c1 | 0x1 | int | Standby BK Picture |
| 0x25000c2 | 0x1 | int | Show Last Call On Launch |
| 0x25000e2 | 0x1 | int | Separate Display |
| 0x25000e3 | 0x1 | int | CH Switching Keeps Last Caller |
| 0x25000e4 | 0x1 | int | A Channel Name Color |
| 0x25000e6 | 0x1 | int | Receive Backlight Delay |
| 0x2501439 | 0x1 | int | B Channel Name Color |
| 0x250143d | 0x1 | int | Zone Name Color A |
| 0x250143e | 0x1 | int | Zone Name Color B |
| 0x2501440 | 0x1{0} | bool | Display Channel Type |
| 0x2501440 | 0x1{1} | bool | Display Time Slot |
| 0x2501440 | 0x1{3} | bool | Display Color Code |
| 0x2501442 | 0x1 | int | Date Display Format |
| 0x2500047 | 0x1 | int | Volume Bar |

## GPS/Ranging
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500028 | 0x1 | int | GPS (Power) |
| 0x250003f | 0x1 | int | Get GPS Positioning |
| 0x2500030 | 0x1 | int | Time Zone |
| 0x25000b5 | 0x1 | int | Ranging Interval |
| 0x25000bd | 0x1 | int | Distance Unit |
| 0x2500053 | 0x1 | int | GPS Template Information |
| 0x2501280 | 0x20 | int | GPS Information Char |
| 0x2501435 | 0x1 | int | GPS Mode |
| 0x2501444 | 0x1 | int | GPS Roaming (Disabled in CPS) |

## VFO Scan
| Address | Length | Type | Data |
| - | - | - | - |
| 0x250000e | 0x1 | int (BE) | VFO Scan Type |
| 0x2500058 | 0x4 | int (BE) | VFO Scan Start Freq (UHF) / 100000 |
| 0x250005c | 0x4 | int (BE) | VFO Scan End Freq (UHF) / 100000  |
| 0x2500060 | 0x4 | int (BE) | VFO Scan Start Freq (VHF) / 100000  |
| 0x2500064 | 0x4 | int (BE) | VFO Scan End Freq (VHF) / 100000  |

## Auto Repeater
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500048 | 0x1 | int | Auto Repeater A |
| 0x25000d4 | 0x1 | int | Auto Repeater B |
| 0x2500068 | 0x1 | int | Auto Repeater 1 (UHF) (0xff = off) |
| 0x2500069 | 0x1 | int | Auto Repeater 1 (VHF) (0xff = off) |
| 0x2501422 | 0x1 | int | Auto Repeater 2 (UHF) (0xff = off) |
| 0x2501423 | 0x1 | int | Auto Repeater 2 (VHF) (0xff = off) |
| 0x25000dd | 0x1 | int | Repeater Check |
| 0x25000de | 0x1 | int | Repeater Check Interval |
| 0x25000df | 0x1 | int | Repeater Check Reconnections |
| 0x25000e5 | 0x1 | int | Repeater Out of Range Notify |
| 0x25000ea | 0x1 | int | Out of Range Notify |
| 0x25000e7 | 0x1 | int | Auto Roaming |
| 0x25000e0 | 0x1 | int | Auto Roaming Start Condition |
| 0x25000ba | 0x1 | int | Auto Roaming at Fixed Time |
| 0x25000bf | 0x1 | int | Roaming Effect Wait Time |
| 0x25000d5 | 0x1 | int | Roaming Zone |
| 0x25000c4 | 0x4 | int (BE) | Min Freq Of Auto Repeater 1 (VHF) |
| 0x25000c8 | 0x4 | int (BE) | Max Freq Of Auto Repeater 1 (VHF) |
| 0x25000cc | 0x4 | int (BE) | Min Freq Of Auto Repeater 1 (UHF) |
| 0x25000d0 | 0x4 | int (BE) | Max Freq Of Auto Repeater 1 (UHF) |
| 0x2501424 | 0x4 | int (BE) | Min Freq Of Auto Repeater 2 (VHF) |
| 0x2501428 | 0x4 | int (BE) | Max Freq Of Auto Repeater 2 (VHF) |
| 0x250142c | 0x4 | int (BE) | Min Freq Of Auto Repeater 2 (UHF) |
| 0x2501430 | 0x4 | int (BE) | Max Freq Of Auto Repeater 2 (UHF) |

## Record
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500022 | 0x1 | int | Record Function |

## Volume/Audio
| Address | Length | Type | Data |
| - | - | - | - |
| 0x250003b | 0x1 | Max Volume |
| 0x2500052 | 0x1 | Max Headphone Volume |
| 0x250000f | 0x1 | Digi Mic Gain |
| 0x2500057 | 0x1 | Enhanced Sound Quality |
| 0x2501443 | 0x1 | Ana Mic Gain |

## Work Mode
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500001 | 0x1 | Display Mode |
| 0x2500015 | 0x1 | VF/MR A |
| 0x250001f | 0x1 | MEM Zone A |
| 0x2500016 | 0x1 | VF/MR B |
| 0x2500020 | 0x1 | MEM Zone B |
| 0x250002c | 0x1 | Main Channel Set |
| 0x250002d | 0x1 | Sub-Channel Mode |
| 0x2500034 | 0x1 | Working Mode |

## Vox/BT
| Address | Length | Type | Data |
| - | - | - | - |
| 0x250000c | 0x1 | VOX Level |
| 0x250000d | 0x1 | VOX Delay |
| 0x2500033 | 0x1 | VOX Detection |
| 0x25000b1 | 0x1 | BT On/Off |
| 0x25000b2 | 0x1 | BT + int Mic |
| 0x25000b3 | 0x1 | BT + int Spk |
| 0x25000b6 | 0x1 | BT Mic Gain |
| 0x25000b7 | 0x1 | BT Spk Gain |
| 0x25000ed | 0x1 | BT Hold Time |
| 0x25000ee | 0x1 | BT RX Delay |
| 0x2501421 | 0x1 | BT PTT Hold |
| 0x2501434 | 0x1 | PTT Sleep Time |

## STE
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500017 | 0x1 | STE Type Of CTCSS |
| 0x2500018 | 0x1 | STE When No Signal |
| 0x2501436 | 0x1 | STE Time |

## FM
| Address | Length | Type | Data |
| - | - | - | - |
| 0x250001e | 0x1 | FM VFO/MEM |
| 0x250001d | 0x1 | FM Work Channel |
| 0x250002b | 0x1 | FM Monitor |

## Power Save
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500003 | 0x1 | Auto Shutdown |
| 0x250000b | 0x1 | Power Save |
| 0x250143f | 0x1 | Auto Shutdown Type |

## Key Function
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500002 | 0x1 | Key Lock |
| 0x2500010 | 0x1 | PF1 Short Key |
| 0x2500011 | 0x1 | PF2 Short Key |
| 0x2500012 | 0x1 | PF3 Short Key |
| 0x2500013 | 0x1 | P1 Short Key |
| 0x2500014 | 0x1 | P2 Short Key |
| 0x2500041 | 0x1 | PF1 Long Key |
| 0x2500042 | 0x1 | PF2 Long Key |
| 0x2500043 | 0x1 | PF3 Long Key |
| 0x2500044 | 0x1 | P1 Long Key |
| 0x2500045 | 0x1 | P2 Long Key |
| 0x2500046 | 0x1 | Long Key Time |
| 0x25000be{0} | b1 | Knob Lock |
| 0x25000be{1} | b1 | Keyboard Lock |
| 0x25000be{3} | b1 | Side Key Lock |
| 0x25000be{4} | b1 | Forced Key Lock |

## Other
| Address | Length | Type | Data |
| - | - | - | - |
| 0x25000d5 | 0x1 | Address Book Is Sent With Its Own Code |
| 0x2500004 | 0x1 | TOT |
| 0x2500005 | 0x1 | Language |
| 0x2500008 | 0x1 | Frequency Step |
| 0x2500009 | 0x1 | SQL Level A |
| 0x250000a | 0x1 | SQL Level B |
| 0x250002e | 0x1 | TBST |
| 0x2500050 | 0x1 | Analog Call Hold Time |
| 0x250006e | 0x1 | Call Channel Is Maintained |
| 0x250006f | 0x1 | Priority Zone A (Zone Index - 1; 0xff = ZONE0)|
| 0x2500070 | 0x1 | Priority Zone B |
| 0x25000e9 | 0x1 | Mute Timing |
| 0x250143a | 0x1 | Encryption Type |
| 0x250143b | 0x1 | TOT Predict |
| 0x250143c | 0x1 | TX Power AGC |

## Digital Func
| Address | Length | Type | Data |
| - | - | - | - |
| 0x2500019 | 0x1 | Group Call Hold Time |
| 0x250001a | 0x1 | Private Call Hold Time |
| 0x2501437 | 0x1 | Manual Dial - Group TG Hold Time |
| 0x2501438 | 0x1 | Manual Dial - Private TG Hold Time |
| 0x250146e | 0x1 | Voice Header Repetitions |
| 0x250001c | 0x1 | TX Preamble Duration |
| 0x2500038 | 0x1 | Filter Own ID in MissCall |
| 0x250003c | 0x1 | Digital Remote Kill |
| 0x2500049 | 0x1 | Digital Monitor |
| 0x250004a | 0x1 | Digital Monitor CC |
| 0x250004b | 0x1 | Digital Montior ID |
| 0x250004c | 0x1 | Monitor Slot Hold |
| 0x250003e | 0x1 | Remote Monitor |
| 0x25000c3 | 0x1 | SMS Format |
