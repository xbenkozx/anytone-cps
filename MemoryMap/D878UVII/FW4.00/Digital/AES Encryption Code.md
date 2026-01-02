# AES Encryption Code
255 Items
| Address | Length | Data |
| - | - | - |
| 0x24c4000 | 0x30 | Encryption 1 |
| 0x24c4040 | 0x30 | Encryption 2 |
| 0x24c8000 | 0x | Encryption Exists (LE bits) |

| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x1 | int | Encryption ID |
| 0x1 | 0x20 | hex | Encryption Key |
| 0x22 | 0x1 | int | Key Length |