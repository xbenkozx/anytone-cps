# Roaming Zone
250 Channels
| Address | Length | Data |
| 0x1040000 | 0x | Roam Channel 1 |
| 0x1040020 | 0x | Roam Channel 2 |

| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x4 | hex | RX Frequency | 
| 0x4 | 0x4 | hex | TX Frequency |
| 0x8 | 0x1 | int | Color Code |
| 0x9 | 0x1 | int | Slot (No Use = ) |
| 0xa | 0x10 | string(16) | Name |
