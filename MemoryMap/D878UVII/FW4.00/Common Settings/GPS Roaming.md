# GPS Roaming
32 Channels
Channels are interlaced (ie. 1,17,2,18,3,19...)
| Address | Length | Data |
| 0x2504000 | 0x10 | GPS Roaming 1 |
| 0x2504020 | 0x10 | GPS Roaming 3 |
| 0x25043e0 | 0x10 | GPS Roaming 32 |

| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x1 | int | On/Off |
| 0x1 | 0x1 | int | Zone (0xff = off) |
| 0x2 | 0x1 | int | Lat Degree |
| 0x3 | 0x1 | int | Lat Minute |
| 0x4 | 0x1 | int | Lat Minute Decimal |
| 0x5 | 0x1 | int | North/South |
| 0x6 | 0x1 | int | Long Degree |
| 0x7 | 0x1 | int | Long Minute |
| 0x8 | 0x1 | int | Long Minute Decimal |
| 0x9 | 0x1 | int | East/West |
| 0xc | 0x4 | int (LE) | Radius |