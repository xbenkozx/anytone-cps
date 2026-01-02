# Friends List
250 Items

Not Sure how this is loaded yet as it doesn't write with radio data. Maybe it writes with digital contact list.

| Address | Length | Data |
| 0x5500000 | *VARIABLE* | Digi Contact 1 |
| 0x4000000 | 0x | Contact Order |
| 0x4840000 | 0x4 | Number of Contacts |

# ID Blocks
0x4000000 - 0x401f400
0x4040000 - 0x405f400

# Data Blocks
Block Size: 0x186a0
Block Offset: 0x40000

0x5500000 - 0x55186a0
0x5540000 - 0x55586a0
0x6a80000 - 
0x6b00000 - 0x6d986a0
0x6dc0000 - 0x70586a0


## Digi Contact
| Offset | Length | Type | Data |
| 0x0 | 0x1 | int | Call Type |
| 0x1 | 0x4 | hex | DMR ID |
| 0x5 | 0x1 | int | Call Alert |
| 0x | 0x | str | Name 16 |
| 0x | 0x | str | City 15 |
| 0x | 0x | str | Callsign 8 |
| 0x | 0x | str | State 16 |
| 0x | 0x | str | Country 16 |
| 0x | 0x | str | Remarks 16 |

Theoretical Max Length 0x73
Max Blocks 580

## Contact Order
| Offset | Length | Bit | Data |
| - | - | - | - |
| 0x0 | 0x4 | - | DMR ID (Bit Shifted and then hex format) 16777215 = All Call |
| 0x0 | 0x0 | 0 | Call Type (0=Private, 1=Group)
| 0x4 | 0x4 | - | Data Offset |