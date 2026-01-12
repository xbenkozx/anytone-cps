# Zone
| Address | Length | Data |
| - | - | - |
| 0x24c1300? | 0x20 | Active Zone List |
| 0x2540000? | 0x20 | Zone Name |
| 0x2000000 | 0x200 | Zone Channel List <br/> 0x200 offset; 200 Zones |
| 0x2500100? | 0x2 | Zone A Channel Index (big endian) |
| 0x2500300? | 0x2 | Zone B Channel Index (big endian) |
| 0x24c1360? | 0x20 | Zone Hide (bool) |