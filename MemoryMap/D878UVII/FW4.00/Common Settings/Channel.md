# Channel Memory Addressing
Max Channels: 4000

| Address | Length | Data |
| - | - | - |
| 0x24c1500 | 0x240 | Active Channels |
| 0x800000 | 0x40 | Primary Channel Data <br/> 128 Channel Blocks. 0x4000 block offsets | 
| 0x802000 | 0x40 | Secondary Channel Data <br/> Offset by 0x2000 from Primary Channel Data | 
| 0xFC0800  | 0x40 | Channel VFO A (Primary) | 
| 0xFC0840  | 0x40 | Channel VFO B (Primary) |
| 0xFC2800  | 0x40 | Channel VFO A (Secondary) | 
| 0xFC2840  | 0x40 | Channel VFO B (Secondary) |

## Active Channels
| Address | Length | Data |
| - | - | - |
| 0x24c1500 | 1 bit | Active channel (bool) |

## Primary Channel Format
| Byte | Length | Bit | Type | Data |
| - | - | - | - | - |
| 0x0 | 0x4 | hex | RX Frequency | 
| 0x4 | 0x4 | hex | Offset | 
| 0x8 | - | 7:6 | int | Offset Direction (0 = None, 1 = Positive, 2 = Negative)|
| 0x8 | - | 5:4 | int | Band Width (1 = 25kHz, 0 = 12.5kHz)|
| 0x8 | - | 3:2 | int | TX Power (0 = Low, 1 = Medium, 2 = High, 3 = Turbo) |
| 0x8 | - | 1:0 | int | Channel Type (0 = Analog, 1 = Digital, 2 = A+D, 3 = D+A) |
| 0x9 | - | 7 | bool | Talkaround |
| 0x9 | - | 6 | bool | Call Confirmation |
| 0x9 | - | 5 | bool | PTT Prohibit |
| 0x9 | - | 4 | bool | Reverse |
| 0x9 | - | 3:2 | int | CTCSS/DCS Encode (0 = Off, 1 = CTCSS, 2 = DCS) | 
| 0x9 | - | 1:0 | int | CTCSS/DCS Decode (0 = Off, 1 = CTCSS, 2 = DCS) | 
| 0xa | 0x1 | - | int | CTCSS Encode Index |
| 0xb | 0x1 | - | int | CTCSS Decode Index |
| 0xc | 0x2 | - | int | DCS Encode Index | 
| 0xe | 0x2 | - | int | DCS Decode Index |
| 0x10 | 0x1 | - | n/a | 0xCF (Unknown data) | 
| 0x11 | 0x1 | - | n/a | 0x09 (Unknown data) |
| 0x12 | 0x1 | - | int | 2tone Decode |
| 0x13 | 0x2 | - | int (BE) | Contact/TG ID index |
| 0x18 | 0x1 | - | int | Radio ID index |
| 0x19 | - | 7:6 | | |
| 0x19 | - | 5:4 | int | Squelch Mode (0 = Carrier, 1 = CTCSS/DCS) |
| 0x19 | - | 3:2 | | |
| 0x19 | - | 1:0 | int | PTT ID (0 = Off, 1 = Start, 2 = End, 3 = Start&End) |
| 0x1a | - | 7:6 | | | 
| 0x1a | - | 5:4 | int | Optional Signal (0 = off, 1 = DTMF, 2 = 2tone, 3 = 5tone)
| 0x1a | - | 3:2 | | |
| 0x1a | - | 1:0 | int | Busy Lock (0 = off, 1 = Different CDT, 2 = Channel Free) |
| 0x1c | 0x1 | - | int | Receive Group Call List (0xff = None) |
| 0x1b | 0x1 | - | int | Scan List (xff = None, Scan List index) |
| 0x1d | 0x1 | - | int | 2tone ID |
| 0x1e | 0x1 | - | int | 5tone ID |
| 0x1f | 0x1 | - | int | DTMF ID |
| 0x20 | 0x1 | - | int | RX Color Code index |
| 0x21 | - | 7 | bool | Work Alone | 
| 0x21 | - | 6 | | | 
| 0x21 | - | 5 | bool | APRS RX |
| 0x21 | - | 4 | bool | Slot Suit | 
| 0x21 | - | 3:2 | int | DMR Mode (0 = DMO/Simplex, 1 = DCDM/Double Slot, 2 = DCDM TS Split) <br/> Requires DMR Mode(52{6:7}) = DMO/Simplex | 
| 0x21 | - | 1 | int | TS (0 = TS1, 1 = TS2) | 
| 0x21 | - | 0 | bool | SMS Confirmation | 
| 0x22 | 0x1 | - | int | AES Encryption Key index | 
| 0x23 | 0x10 | - | string(16) | Channel Name |
| 0x33 | 0x1 | - | | | 
| 0x34 | - | 7:5 | | | 
| 0x34 | - | 4 | bool | Auto Scan | 
| 0x34 | - | 3 | bool | DataAckDisable | 
| 0x34 | - | 2 | int | ExcludeChannelRoaming | 
| 0x34 | - | 1 | int | DMR Mode (0 = repeater, 1 = DMO/Simplex) | 
| 0x34 | - | 0 | bool | Ranging | 
| 0x35 | 0x1 | - | int | APRS Report Type |
| 0x36 | 0x1 | - | int | Analog APRS PTT Mode |
| 0x37 | 0x1 | - | int | Digital APRS PTT Mode |
| 0x38 | 0x1 | - | int | Digital APRS Report Channel |
| 0x39 | 0x1 | - | int | Correct Frequency / 10 (signed) |
| 0x3a | 0x1 | - | int | Digital Encryption |
| 0x3b | - | 5 | int | Extend Encryption (0 = AES, 1 = ARC4) |
| 0x3b | - | 4 | bool | Send Talker Alias |
| 0x3b | - | 3 | bool | Analog APRS Mute |
| 0x3b | - | 2 | int | SMS Forbid |
| 0x3b | - | 1 | int | AES Random Key |
| 0x3b | - | 0 | int | AES Multiple Key |
| 0x4c | 0x1 | - | int | AnalogAPRSReportFreq index | 
| 0x4d | 0x1 | - | int | ARC4 Encryption Key index |

## Secondary Channel Data
| Byte | Length | Bit | Type | Data |
| - | - | - | - | - |
| 0x0 | 0x1 | - | int | R5toneBot (0x64 = customize) |
| 0x1 | 0x1 | - | int | R5toneEot (0x64 = customize) |
| 0x3 | 0x1 | - | int | TX Color Code index |