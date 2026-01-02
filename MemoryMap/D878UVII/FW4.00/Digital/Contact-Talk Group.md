# Contact\Talk Group
10000 Items
| Address | Length | Data |
| - | - | - |
| 0x4800000 | 0x | 
| 0x2680000 | 0x64 | TG 1 |

| Offset | Length | Type | Data |
| - | - | - | - |
| 0x00 | 0x1 | int | Call Type |
| 0x01 | 0x10 | string() | Name |
| 0x22 | 0x1 | int | Call Alert (0 = None, 1 = Ring, 2 = Online Alert) |
| 0x23 | 0x4 | hex | TG/DMR ID |

Ordered List
This list is ordered by TG ID
| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x4 | int (BE) | Talkgroup ID (LSB is private/group call and then bit shifted right for the TG ID) |
| 0x4 | 0x4 | int (BE) | Talkgroup Index |