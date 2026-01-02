# APRS
APRS Fix Location Lat/Long Data is formatted as:
<br/>
```
LLMMDD
LL = Lat Integer
MM = Minute Integer
DD = Minute Decimal (up to 100, increment by 10)
DMM -> DM: (((DD / 100) + MM) / 60) + LL
```
| Address | Length | Type | Data |
| - | - | - |
| 0x2501001 | 0x4 | hex | TX Frequency 1 |
| 0x2501005 | 0x1 | int | TX Delay |
| 0x2501006 | 0x1 | int | Send Sub Tone |
| 0x2501007 | 0x1 | int | CTCSS |
| 0x2501008 | 0x1 | int | DCS |
| 0x250100a | 0x1 | int | Manual TX Interval |
| 0x250100b | 0x1 | int | Auto TX Interval |
| 0x250100c | 0x1 | int | TX Tone |
| 0x250100d | 0x1 | int | Fixed Location Beacon |
| 0x250100e | 0x3 | hex | FIX 1 Latitude LL MM DD |
| 0x2501011 | 0x1 | int | FIX 1 North/South |
| 0x2501012 | 0x3 | int | FIX 1 Longitude LL MM DD |
| 0x2501015 | 0x3 | int | FIX 1 East/West |
| 0x2501016 | 0x6 | int | TOCALL |
| 0x250101c | 0x1 | int | TOCALL SSID |
| 0x250101d | 0x6 | int | Your Call Sign |
| 0x2501023 | 0x1 | int | Your SSID |
| 0x2501024 | 0x15 | str | Digitpeater Path |
| 0x2501039 | 0x1 | int | APRS Symbol Table |
| 0x250103a | 0x1 | int | Map Icon |
| 0x250103b | 0x1 | int | TX Power |
| 0x250103c | 0x1 | int | Prewave Time |
| 0x250103f | 0x1 | int | 0xff |
| 0x2501040 | 0x2 | int | Digital Report 1-8 Channel (LE) (a20f = current channel) |
| 0x2501050 | 0x4 | int | Digital Report 1-8 APRS TG (HEX) |
| 0x2501070 | 0x1 | int | Digital Report 1-8 Call Type |
| 0x2501078 | 0x1 | int | Support for Roaming |
| 0x2501079 | 0x1 | int | Digital Report 1-8 Slot (LE) (0 = current slot) |
| 0x2501081 | 0x1 | int | Repeater Activation Delay |
| 0x2501082 | 0x1 | int | AprsDisTime Index |
| 0x2501083 | 0x23 | str | Digitpeater Path (cont'd) |
| 0x25010a6 | 0x2 | int | APRS Alt Data (LE) |
| 0x25010a8 | 0x1 | int | Filter Objects (Position, Mic-E, Object, Item, Message, WX Report, NMEA Report, Status Report)|
| 0x25010a9 | 0x1 | int | Filter Objects (Other)|
| 0x25010aa | 0x1 | int | Ana APRS TX Mode |
| 0x25010ab | 0x1 | int | PASS ALL |
| 0x25010ac | 0x4 | int | TX Frequency 2 |
| 0x25010b0 | 0x4 | int | TX Frequency 3 |
| 0x25010b4 | 0x4 | int | TX Frequency 4 |
| 0x25010b8 | 0x4 | int | TX Frequency 5 |
| 0x25010bc | 0x4 | int | TX Frequency 6 |
| 0x25010c0 | 0x4 | int | TX Frequency 7 |
| 0x25010c4 | 0x4 | int | TX Frequency 8 |
| 0x25010cd | 0x7 | int | FIX 2-8 Lat Integer LL |
| 0x25010d4 | 0x7 | int | FIX 2-8 Lat Minute Integer MM |
| 0x25010db | 0x7 | int | FIX 2-8 Lat Minute Decimal DD |
| 0x25010e2 | 0x7 | int | FIX 2-8 North/South |
| 0x25010fe | 0x7 | int | FIX 2-8 East/West |
| 0x2501200 | 0x3c | str | Sending Text |
| 0x250146f | 0x1 | int | Fixed Location Beacon (Duplicate) |