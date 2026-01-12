# Hot Key
| Address | Length | Type | Data |
| - | - | - | - |

## Analog Quick Call
| Address | Length | Type | Data |
| - | - | - | - |
| 0x25c0000 | 0x1 |  | Operation Type 1 |
| 0x25c0001 | 0x1 |  | Call ID 1 0xff = off |
| 0x25c0002 | 0x1 |  | Operation Type 2 |
| 0x25c0003 | 0x1 |  | Call ID 2 0xff = off |
| 0x25c0004 | 0x1 |  | Operation Type 3 |
| 0x25c0005 | 0x1 |  | Call ID 3 0xff = off |
| 0x25c0006 | 0x1 |  | Operation Type 4 |
| 0x25c0007 | 0x1 |  | Call ID 4 0xff = off |

## State Information
32 Items
0x25c0b00 set List
| Address | Length | Type | Data |
| - | - | - | - |
| 0x25c0100 | 0x20 |  | State Content |

## Hot Key
| Address | Index | Key |
| - | - | - |
| 0x25c0500 | 0 | Hot Key 1 |
| 0x | 1 | Hot Key 2 |
| 0x | 2 | Hot Key 3 |
| 0x | 3 | Hot Key 4 |
| 0x | 4 | Hot Key 5 |
| 0x | 5 | Hot Key 6 |
| 0x | 6 | Func Key + 0 |
| 0x | 7 | Func Key + 1 |
| 0x | 8 | Func Key + 2 |
| 0x | 9 | Func Key + 3 |
| 0x | 10 | Func Key + 4 |
| 0x | 11 | Func Key + 5 |
| 0x | 12 | Func Key + 6 |
| 0x | 13 | Func Key + 7 |
| 0x | 14 | Func Key + 8 |
| 0x | 15 | Func Key + 9 |
| 0x | 16 | Func Key + * |
| 0x | 17 | Func Key + # |

| Offset | Length | Type | Data |
| - | - | - | - |
| 0x0 | 0x1 |  | Mode |
| 0x1 | 0x1 |  | Menu |
| 0x2 | 0x1 |  | Call Type 0xff = off|
| 0x4 | 0x4 | int (BE) | Call Object (TG idx) |
| 0x3 | 0x1 |  | Digi Call Type (off= 0xff, group call=0x0, hot text=0x03, Call tip=0x4, information=0x5|
| 0x8 | 0x1 |  | Content (prefab sms idx)|