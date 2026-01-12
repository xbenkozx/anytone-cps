# Channel Memory Addressing
Max Channels: 4000

| Address | Length | Data |
| - | - | - |
| 0x | 0x240 | Active Channels |
| 0x1000000 | 0x80 | Channel Data <br/> 64 Channel Blocks. 0x4000 block offsets | 
| 0x  | 0x40 | Channel VFO A (Primary) | 
| 0x  | 0x40 | Channel VFO B (Primary) |
| 0x  | 0x40 | Channel VFO A (Secondary) | 
| 0x  | 0x40 | Channel VFO B (Secondary) |

## Active Channels
| Address | Length | Data |
| - | - | - |
| 0x3482a00 | 1 bit | Active channel (bool) |

## Primary Channel Format
| Byte | Length | Bit | Type | Data |
| - | - | - | - | - |
| 0x0 | 0x4 | - | hex | RX Frequency | 
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
| 0x10 | 0x2 | - | int | Custom CTCSS |
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
| 0x1b | 0x1 | - | int | Scan List (xff = None, Scan List index) |
| 0x1c | 0x1 | - | int | Receive Group Call List (0xff = None) |
| 0x1c | 0x1 | - | Scan List |
| 0x3b | 0x1 | - | TX Interrupt |
| 0x3e | 0x1 | - | Scrambler Set |
| 0x3f | 0x1 | - | Custom Scrambler |
| 0x20 | 0x1 | - | RX Color Code |
| 0x43 | 0x1 | - | TX Color Code |

## Secondary Channel Data
| Byte | Length | Bit | Type | Data |
| - | - | - | - | - |