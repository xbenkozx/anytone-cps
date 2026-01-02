# 2 Tone Settings
| Address | Length | Type | Data |
| - | - | - | - |
| 0x24c1280 | 0x6 | int | Encode Active List |
| 0x24c1299 | 0x1 | int | Encode 1st Tone Duration |
| 0x24c129a | 0x1 | int | Encode 2nd Tone Duration |
| 0x24c129b | 0x1 | int | Encode Long Tone Duration |
| 0x24c129c | 0x1 | int | Encode Gap Time |
| 0x24c129d | 0x1 | int | Encode Auto Reset Time |
| 0x24c129e | 0x1 | bool | Encode Side Tone |
| 0x24c1100 | 0x10 | | Encode List 0xff=empty |

# Encode List
| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x2 | | 1st Tone Freq / 10 |
| 0x2 | 0x2 | | 2nd Tone Freq / 10 |
| 0x8 | 0x7 | string | Name |


# Decode List
| Address | Length | Data |
| 0x24c2400 | 0x20 | Decode List Item |
| 0x24c2600 | 0x2 | Set List |

| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x2 | | 1st Tone Freq / 10 |
| 0x2 | 0x2 | | 2nd Tone Freq / 10 |
| 0x4 | 0x1 | | Decoding Response |
| 0x5 | 0x7 | string | Name |