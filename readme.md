<p align="center">
  <img src="desktop/icons/d878_icon.png" />
</p>

# anytone-cps
An open-source, cross-platform Customer Programming Software (CPS) for the AnyTone 878UVII series radios, written in c++.

This project aims to provide a modern, scriptable, and community-maintained alternative to the stock AnyTone CPS, while keeping the workflow familiar for existing users.

Currently, this project is in Alpha stage and is a work is progress. Make sure you have a backup of your codeplug in the event that you need to factory reset your radio. Not all functionality has been added but will be updated as soon as features become available. Currently, only FW version 4.00 is supported.

> **Note**  
> This project is not affiliated with, endorsed by, or supported by AnyTone / Qixiang. All trademarks are the property of their respective owners.

---

## Progress
| | D878UVII | D890UV | D168UV | D878UV | D868UV |
| - | :-: | :-: | :-: | :-: | :-: |
| UI | ![95%](https://progress-bar.xyz/95?width=100) | ![95%](https://progress-bar.xyz/95?width=100) | ![0%](https://progress-bar.xyz/0?width=100) | ![0%](https://progress-bar.xyz/0?width=100) | ![0%](https://progress-bar.xyz/0?width=100) |
| Serial | ![98%](https://progress-bar.xyz/98?width=100) | ![88%](https://progress-bar.xyz/88?width=100) | ![0%](https://progress-bar.xyz/0?width=100) | ![0%](https://progress-bar.xyz/0?width=100) | ![0%](https://progress-bar.xyz/0?width=100) |

## Supported Devices
- D878UVII

## Why?
The stock CPS for the 878UVII:

- Is Windows-only and does not run using WINE
- Makes bulk edits and codeplug management harder than it needs to be
- Slow Performance

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
| Data | D878UVII | D890UV | D168UV |
| - | :---: | :---: | :---: |
| Boot Image | R/W | R/W | |
| BK Image 1 | R/W | R/W | |
| BK Image 2 | R/W | R/W | |
| 2Tone Encode/Decode | R/W | | |
| 5Tone Encode/Decode | R/W | | |
| AES Encryption Code | R/W | R/W | |
| AM Air | - | R/W | - |
| AM Zone | - | R/W | - |
| Analog Address Book | R/W | R/W | |
| APRS | R/W | R/W | |
| ARC4 Encryption Code | R/W | R/W | |
| Auto Repeater Offset Frequencies | R/W | R/W | |
| Alarm Settings | R/W | R/W | |
| Channels | R/W | R/W | |
| Digital Contacts | R/W | R/W | |
| Digital Contact Whitelist | - | R/W | - |
| DTMF Encode/Decode | R/W | | |
| Encryption Code | R/W | R/W | |
| Local Information/Expert Options(AT_OPTIONS) | R/W | R/W | |
| FM Channels | R/W | R/W | |
| GPS Roaming | R/W | R/W | |
| HotKey HotKey | R/W | | |
| HotKey Quick Call | R/W | | |
| HotKey State | R/W | | |
| Master ID | R/W | R/W | |
| Optional Settings | R/W | R/W | |
| Prefabricated SMS | R/W | R/W | |
| QDC 1200 | - | | - |
| QDC Address Book | - | | - |
| Radio IDs | R/W | R/W | |
| Receive Groups | R/W | R/W | |
| Roaming Channels | R/W | R/W | |
| Roaming Zones | R/W | R/W | |
| Scan Lists | R/W | R/W | |
| Talk Alias Settings | R/W | R/W | |
| TalkGroups | R/W | R/W | |
| Talkgroup Whitelist | - | R/W | - |
| Zones | R/W | R/W | |

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
