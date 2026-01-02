# 5 Tone Settings
| Address | Length | Type | Data |
| - | - | - | - |
| 0x24c0000 | 0x200 | | Special Call List | 
| 0x24c0c80 | 0x10 | int | Special Call Active |
| 0x24c1023 | 0x1 | int | Self ID Length |
| 0x24c1025 | 0x7 | hex string | Self ID |
| 0x24c1022 | 0x1 | int | Decode Standard |
| 0x24c1021 | 0x1 | int | Decoding Response |
| 0x24c1024 | 0x1 | int | Time Of Decode Tone |
| 0x24c1034 | 0x1 | int | Decode Time |
| 0x24c1037 | 0x1{6-0} | int | 5Tone Dec Units |
| 0x24c1038 | 0x1 | int | Dis AnyID |

| 0x24c1036 | 0x1 | int | Pretime |
| 0x24c102e | 0x1 | int | AutoReset Time |
| 0x24c102c | 0x1 | int | Time Lapse After Decode |
| 0x24c102d | 0x1 | int | PTT ID Pause Time (off=0x0, 5=0x5...)|
| 0x24c102f | 0x1 | int | First Tone Length |
| 0x24c1032 | 0x1 | int | Stop Code (off=0x0, A=0xa...) |
| 0x24c1033 | 0x1 | int | Stop Time Length |
| 0x24c1035 | 0x1 | int | First Tone After Stop |
| 0x24c1030 | 0x1 | int | Encode Side Tone |
| 0x24c0d00 | 0x20 | | Information List |


| 0x24c1041 | 0x1 | int | PTT ID BOT Standard |
| 0x24c1042 | 0x1 | int | PTT ID BOT Encode ID Length |
| 0x24c1043 | 0x1 | int | PTT ID BOT Decode Time |
| 0x24c1044 | 0x18 | int | PTT ID BOT Encode ID |
| 0x24c1061 | 0x1 | int | PTT ID EOT Standard |
| 0x24c1062 | 0x1 | int | PTT ID EOT Encode ID Length |
| 0x24c1063 | 0x1 | int | PTT ID EOT Decode Time |
| 0x24c1064 | 0x18 | int | PTT ID EOT Encode ID |

## Information List
16 Entries
| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x1 | int | Function Option |
| 0x1 | 0x1 | int | Decoding Response |
| 0x2 | 0x1 | int | Information ID Length |
| 0x3 | 0xc | int | Information ID |
| 0x10 | 0x7 | int | Function Name |

## Special Call List
| Offset | Length | Type | Data |
| - | - | - | - |
| 0x4 | 0x | | |
| 0x4 | 0x10 | hex | Encode ID / |
| 0x1 | 0x | | Standard |
| 0x3 | 0x | | Time of Encode |
| 0x18 | 0x7 | str | Name |

Special Call Message
0xe1e2345e - ID=12345
Special Call ANI
hex << other_side_id + inteval_char + self_id + e
PTT ID
hex << self_id  + e