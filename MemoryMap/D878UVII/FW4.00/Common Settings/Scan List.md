# Scan List
| Address | Length | Data |
| - | - | - |
| 0x24c1340 | 0x20 | Active Scan List <br/> Bits are little endian | 
| 0x1080000 | 0x90 | Scan List Data <br/> Each list data is offset by 0x200 |

## Scan List Data
| Offset | Length | Data |
| - | - | - |
| 0x1 | 0x1 | Priority Channel Select |
| 0x2 | 0x2 | Priority Channel 1 (BE) </br> 0xffff = off <br/> 0x0000 = current channel <br/> 0xNNNN = channel index + 1 |
| 0x4 | 0x2 | Priority Channel 2 (BE) </br> 0xffff = off <br/> 0x0000 = current channel <br/> 0xNNNN = channel index + 1 |
| 0x6 | 0x1 | Look Back Time A|
| 0x8 | 0x1 | Look Back Time B |
| 0xa | 0x1 | Dropout Delay Time |
| 0xc | 0x1 | Dwell Time |
| 0xe | 0x1 | Revert Channel |
| 0xf | 0x10 | Name |
| 0x1f | 0x64 | Channel List | 