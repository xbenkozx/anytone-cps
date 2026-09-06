<p align="center">
  <img src="desktop/icons/d878_icon.png" />
</p>

# anytone-cps

> **This is a fork** of [xbenkozx/anytone-cps](https://github.com/xbenkozx/anytone-cps) with a series of
> bug fixes for reading/writing the radio, digital contact and talk group handling, and CSV imports.
> It also aggregates community pull requests that were left unmerged upstream (see
> [Community fixes](#community-fixes)). See [Changes in this fork](#changes-in-this-fork) below.
> All credit for the original project goes to its author, and for the community fixes to their authors.

An open-source, cross-platform Customer Programming Software (CPS) for the AnyTone 878UVII series radios, written in c++.

This project aims to provide a modern, scriptable, and community-maintained alternative to the stock AnyTone CPS, while keeping the workflow familiar for existing users.

Currently, this project is in Alpha stage and is a work is progress. Make sure you have a backup of your codeplug in the event that you need to factory reset your radio. Not all functionality has been added but will be updated as soon as features become available. Currently, only FW version 4.00 is supported.

> **Note**  
> This project is not affiliated with, endorsed by, or supported by AnyTone / Qixiang. All trademarks are the property of their respective owners.

---

## Changes in this fork

All changes below live on this fork's `main` branch and were verified against a real AnyTone
AT-D878UVII (FW 4.00 / V101) and with a `VirtualDevice` test harness (write/read roundtrips on
erased, zeroed and randomized codeplug images). The initial bug fix set (up to the UI fixes
section) is also available separately on the `fix/digital-contacts-write` branch.

### Talk groups
- Write the talk group **index table at `0x2600000`** (one little-endian `uint32` per talk group,
  `0xff`-terminated). The radio firmware builds its talk group list from this table; without it only
  a single talk group was visible after a write.
- Place talk group records at their list-index slots within 1000-entry banks (stride `0x40000`),
  matching the official codeplug layout, instead of packing used records consecutively.
- Wire up the **Talk Groups CSV import** in the Import dialog (the button existed but was disabled
  and unconnected).

### Digital contacts
- Fix a division-by-zero crash in `writeDigitalContacts` progress reporting that killed the
  application when writing between 1 and ~500 contacts.
- Skip the contact write when no contact has a Radio ID instead of writing a zero count to the
  radio (which wiped the contact database already stored in it).
- Validate the contact count read from the radio; erased or garbage metadata used to crash the
  application with SIGSEGV during a read.
- CSV import fixes: strip the UTF-8 BOM from the header line, support **header-less contact
  database exports** (e.g. `contacts_Europe_*.csv` DMR user databases, 9-column layout), guard
  against invalid row indices, and log how many rows were parsed/skipped.

### Serial protocol robustness
- `writeMemory` pads any block that is not a multiple of 16 bytes; a single unaligned block used to
  desync the whole session (frame declares 16 data bytes, fewer follow), after which the radio
  stopped acknowledging, all retries failed and the radio stayed stuck on the *PC WRITE* screen
  while discarding everything buffered (data only commits on `END`).
- All encoders now truncate names/strings to their fixed layout fields (`leftJustified(...,
  true)`); previously long or non-ASCII strings could overflow their slots.
- Fix a `QSerialPort` leak in the connection retry loop that kept the device locked, making every
  reconnection attempt fail.
- The `PROGRAM` handshake treated a timeout as success (comparison against an empty
  `QByteArray("\x00")`); a genuine 1-byte `0x00` reply was rejected instead.
- Short/no responses during reads abort the session with a logged address instead of silently
  producing an empty codeplug.
- After a failed session a best-effort `END` is sent so the radio exits the *PC READ*/*PC WRITE*
  screen.

### Reading resilience (erased/garbage codeplugs)
- Bounds-check every index decoded from the radio before using it: 5-tone/DTMF self-ID nibbles,
  2-tone set bitmaps (also fixed encode items never being read due to a copy-paste bug), analog
  address book ids, hotkey state bitmaps, and all reference linkers (zones, scan lists, roaming
  zones, receive groups, AM zones, hotkeys).
- Decoders bail out on truncated input instead of reading past the end.

### UI fixes
- The **Retry** dialog after a failed transfer had its actions swapped: retrying a failed write
  started a *read*, which also reinitializes program memory and silently discarded freshly
  imported data.
- Table views no longer crash on out-of-range enum values decoded from the radio
  (`Constants::safeAt`); the Roaming Channel *Slot* column showed the color code instead of the
  slot.
- Correct write ordering fixes: APRS settings were written to D890UV-only addresses on the
  D878UVII (and never on the D890UV), and receive groups used the radio-ID stride (0x20) instead
  of their own (0x200), overlapping the records.

### Channel and zone imports
- Wire up the **Channels** and **Zones** rows of the Import dialog (buttons were permanently
  disabled). Channels are always imported before zones so zone members can be linked in the same
  run; zones link their members to channels by name + RX/TX frequency.
- Zone CSV fixes: trim header names (the official export ends with `"Zone Hide "` including a
  trailing space, so the hide flag never parsed), bounds-check row numbers, tolerate member
  name/frequency lists of different lengths, and make reference linking idempotent (a read
  followed by an import used to duplicate zone/scan list/roaming members).
- Zones whose channels did not link are still shown by name (with a 0 channel count) and every
  unmatched member is logged, instead of rendering as blank rows.
- Channel CSV: parse the **Color Code** and **Slot** columns of the official export; imported DMR
  channels used to end up with color code 0 and slot 1 regardless of the file contents.

### Repeater list import (przemienniki.net)
- The Channels import field also accepts repeater directory exports from
  [przemienniki.net](https://przemienniki.net) (comma- or tab-separated, auto-detected by the
  `Callsign`/`Duplex` columns).
- The repeater's TX/RX perspective is translated to the radio's (repeater TX = radio RX), and the
  repeater's input CTCSS becomes the tone the radio encodes; `false` means no tone.
- FM repeaters become analog channels (12.5K bandwidth, matching the IARU R1 12.5 kHz channel
  raster); DMR repeaters become **two digital channels per repeater** (`<callsign> TS1`/`TS2`)
  with color code 1, since the export carries no CC/slot information. Rows with neither FM nor
  DMR modes are skipped with a log message.
- Each DMR repeater also gets a **roaming channel** (CC1, Slot1), grouped into `Roaming 1..N`
  roaming zones (64 channels each, the codeplug limit), so network roaming works out of the box.
  Also fixed the Roaming Channel view showing the TX frequency in the RX column.
- Imported channels fill the first free channel slots. **Re-importing an updated list matches
  channels and roaming channels by name and refreshes them in place** — no duplicates and nothing
  else in the codeplug is touched, so the safe workflow is: read from radio, import, write (no
  need to start from an empty codeplug).

### Settings persistence and editor fixes
- Several settings dialogs never wrote their edits back: **Master ID** and **Hotkey** had a
  `save()` method that was never called, and the **AES code**, **analog address book**, **GPS
  roaming** and **AM zone** editors only saved on prev/next navigation, so the entry shown when
  OK was pressed was lost. All are now saved on OK.
- The **APRS settings** dialog had no save path at all (~90 fields were displayed but never
  written back); a full `save()` was added and wired to OK.
- The **Down** button in the Zone, AM Zone, Scan List and Roaming Zone member editors never moved
  the top entry down (it kept the `Up` handler's guard); fixed in all four.

### Community fixes
This fork also carries pull requests that were left unmerged on the upstream project. All credit
goes to their authors; they are included here (with authorship preserved) so users get them in one
place:
- Fix a segfault when editing a channel (uninitialized pointers) — [@Serphentas](https://github.com/Serphentas), upstream PR #1
- Copying a channel no longer cuts it — [@Serphentas](https://github.com/Serphentas), upstream PR #2
- Retry logic for the satellite (Keplerian) data download — [@Serphentas](https://github.com/Serphentas), upstream PR #3
- Working Save / Exit / About menu actions and zone-dialog channel headers — [@Serphentas](https://github.com/Serphentas), upstream PR #4
- Correct Bluetooth options for the D890UV — [@Serphentas](https://github.com/Serphentas), upstream PR #5

---

## Supported Devices
- D878UVII

## Why?
The stock CPS for the 878UVII:

- Is Windows-only and does not run using WINE
- Makes bulk edits and codeplug management harder than it needs to be
- Slow Performance

## Planned Updates
- Repeater Book Import
- Get all functionality working and verified (possibly except firmware update — only one radio is
  available for testing, unless someone donates one :))

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
`R/W` = read and write implemented; `R` = read only. Only the entries below have been exercised
against a real radio; others were removed until tested.
| Data | D878UVII |
| - | :---: |
| Analog Address Book | R/W |
| APRS | R/W |
| Auto Repeater Offset Frequencies | R/W |
| Channels | R/W |
| Digital Contacts | R/W |
| Local Information/Expert Options(AT_OPTIONS) | R/W |
| FM Channels | R/W |
| GPS Roaming | R/W |
| HotKey HotKey | R/W |
| HotKey Quick Call | R/W |
| HotKey State | R/W |
| Master ID | R/W |
| Optional Settings | R/W |
| Prefabricated SMS | R |
| Radio IDs | R/W |
| Receive Groups | R/W |
| Roaming Channels | R/W |
| Roaming Zones | R/W |
| Talk Alias Settings | R/W |
| TalkGroups | R/W |
| Zones | R/W |

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
