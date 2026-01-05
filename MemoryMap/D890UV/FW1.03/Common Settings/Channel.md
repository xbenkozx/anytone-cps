# Channel Memory Addressing
Max Channels: 4000

| Address | Length | Data |
| - | - | - |
| 0x | 0x240 | Active Channels |
| 0x1000000 | 0x80 | Primary Channel Data <br/> 128 Channel Blocks. 0x4000 block offsets | 
| 0x | 0x40 | Secondary Channel Data <br/> Offset by 0x2000 from Primary Channel Data | 
| 0x  | 0x40 | Channel VFO A (Primary) | 
| 0x  | 0x40 | Channel VFO B (Primary) |
| 0x  | 0x40 | Channel VFO A (Secondary) | 
| 0x  | 0x40 | Channel VFO B (Secondary) |

## Active Channels
| Address | Length | Data |
| - | - | - |
| 0 | 1 bit | Active channel (bool) |

## Primary Channel Format
| Byte | Length | Bit | Type | Data |
| - | - | - | - | - |
| 0x0 | 0x4 | - | hex | RX Frequency | 
| 0x8 | - | 7-4 | Mode |
| 0x1c | 0x1 | - | Scan List |
| 0x20 | 0x1 | - | RX Color Code |
| 0x43 | 0x1 | - | TX Color Code |

## Secondary Channel Data
| Byte | Length | Bit | Type | Data |
| - | - | - | - | - |