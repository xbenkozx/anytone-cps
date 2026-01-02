# FM
| Address | Length | Type | Data |
| - | - | - |
| 0x2480000 | 0x4 | hex | FM Frequency (HEX) (100 max) |
| 0x2480200 | 0x4 | int (BE) | VFO 1 Frequency |
| 0x2480210 | 1 bit | | bool | FM Active (BE) |
| 0x2480220 | 1 bit | | bool | Scan (BE) (1=add, 0=del) |