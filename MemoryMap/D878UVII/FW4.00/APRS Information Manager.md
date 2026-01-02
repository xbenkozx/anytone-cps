# APRS Information Manager
| Address | Length | Data |
| - | - | - |
| 0x24c1300 | 0x20 | Active Zone List |
| 0x2540000 | 0x20 | Zone Name <br/> |
| 0x1000000 | 0x200 | Zone Channel List <br/> 0x200 offset; 200 Zones |
| 02500100 | 0x2 | Zone A Channel Index (little endian) |
| 02500300 | 0x2 | Zone B Channel Index (little endian) |
| 0x24c1300 | 0x20 | Zone Hide (bool) |