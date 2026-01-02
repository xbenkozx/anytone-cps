# Analog Address Book
These are not indexed and list removes empty entries

| Address | Length |  Data |
| 0x2900000 | 0x100 | Address Index |
| 0x2900100 | 0x100 | Bytes 0x0 if address set |
| 0x2940000 | 0x18 | Analog Addresses | 

# Analog Address
| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x7 | hex | Number |
| 0x7 | 0x1 | int | Number Length |
| 0x8 | 0xf | str | Name |