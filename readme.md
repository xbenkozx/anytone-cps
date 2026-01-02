<p align="center">
  <img src="icons/d878_icon.png" />
</p>

# anytone-878uvii-cps
An open-source, cross-platform Customer Programming Software (CPS) for the AnyTone 878UVII series radios, written in c++.

This project aims to provide a modern, scriptable, and community-maintained alternative to the stock AnyTone CPS, while keeping the workflow familiar for existing users.

Currently, this project is in Alpha stage and is a work is progress. Make sure you have a backup of your codeplug in the event that you need to factory reset your radio. Not all functionality has been added but will be updated as soon as features become available. Currently, only FW version 4.00 is supported.

> **Note**  
> This project is not affiliated with, endorsed by, or supported by AnyTone / Qixiang. All trademarks are the property of their respective owners.

---

## Progress
| | |
| - | - |
| UI | ![90%](https://progress-bar.xyz/90?width=100) |
| Serial | ![90%](https://progress-bar.xyz/90?width=100) |
| CSV | ![0%](https://progress-bar.xyz/19?width=100) | 

## Supported Devices
- D878UVII

## Why?
The stock CPS for the 878UVII:

- Is Windows-only and does not run using WINE
- Makes bulk edits and codeplug management harder than it needs to be

## Planned Updates
- Repeater Book Import
- Expansion to other radio models (D878UV, D890UV, D168UV)

# Reporting Bugs & Requesting Features

- **Bugs**: Please include:
    - OS and version
    - Radio model and firmware version
    - Description of what you were doing
    - Error output / stack trace
- **Feature requests**: Explain:
    - What problem you’re trying to solve
    - How you currently work around it (if at all)
    - Any reference code / examples that might help

---

# Feature Set
## Serial Data
These are not fully tested.
| Data | Read/Write |
| - | :---: |
| Boot Image | R/W |
| BK Image 1 | R/W |
| BK Image 2 | R/W |
| 2Tone Encode/Decode | R/W |
| 5Tone Encode/Decode | R/W |
| AES Encryption Code | R/W |
| Analog Address Book | |
| APRS | R/W |
| ARC4 Encryption Code | |
| Auto Repeater Offset Frequencies | R/W |
| Alarm Settings | R/W |
| Channels | R/W |
| Digital Contacts | R/W |
| DTMF Encode/Decode | R/W |
| Encryption Code | |
| Local Information/Expert Options(AT_OPTIONS) | R |
| FM Channels | R/W |
| GPS Roaming | R/W |
| HotKey HotKey | |
| HotKey Quick Call | |
| HotKey State | |
| Master ID | R/W |
| Optional Settings | R/W |
| Prefabricated SMS | R/W |
| Radio IDs | R/W |
| Roaming Channels | R/W |
| Roaming Zones | R/W |
| Scan Lists | R/W |
| TalkGroups | R/W |
| Zones | R/W |

## CSV Import/Export
| Data | Import/Export |
| - | :---: |
| 2Tone Encode | |
| 5Tone Encode | |
| AES Encryption Code | |
| Alert Tone | |
| Analog Address Book | |
| APRS | |
| ARC4 Encryption Code | |
| Auto Repeater Offset Frequencies | |
| Channels | |
| Digital Contacts | |
| DTMF Encode | |
| FM Channels | |
| GPS Roaming | |
| HotKey HotKey | |
| HotKey Quick Call | |
| HotKey State | |
| Optional Settings | |
| Prefabricated SMS | |
| Radio IDs | I |
| Roaming Channels | |
| Roaming Zones | |
| Scan Lists | |
| TalkGroups | |
| Zones | |

---

# Donations
As this project take a quite a bit of time as well as costs to purchase new radios to be able to support them, donations are appreciated but not required.
You can send money via paypal to k7dmg@protonmail.com.

# Troubleshooting

## Serial Device Not Accessible
If you are having issues where the  COM port cannot be opened, you may need to add yourself to the dialout user group.

    sudo usermod -a -G dialout <username>

After running the command, logout then back in and the serial ports should now be accessible.


# License
anytone-cps - A multi-platform CPS for Anytone radios.

This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.