# Changelog

Changes of the `mabalew/anytone-cps` fork since `0.0.1` (alpha 9, 2026-02-02). Entries say what was
verified and how; the long description of the July work is in [readme.md](readme.md).

**Version numbers.** A new feature visible to the user raises the minor number and resets the patch
number; every fix raises the patch number. Documentation, tests and developer tools do not change
the version. The versions between `0.0.2` and `0.10.3` were assigned afterwards from the commit
history (one version per change, in the order the changes were made) and were never released under
these numbers: `0.0.1` is the last released version and `0.11.0` is the next one. The current
version is stored in the file `VERSION`; the build checks that the first heading below matches it,
and the About window shows the version and this changelog.

## [0.11.0] - 2026-11-15

### Added
- File dialogs remember the last folder (stored in `settings.ini`, key `user/last_dir`). The
  Open / Save codeplug dialogs start in the folder of the last codeplug; CSV / LST import and
  export, image and `.bin` dialogs start in the last folder used. Save As also proposes the name
  of the current codeplug.
- The About window shows this changelog.

### Changed
- The version is written in one place, the file `VERSION`. CMake reads it, the application shows
  it, and the build fails if the first heading of this file differs. The separate "Build" number
  of the About window is gone: it belonged to the old numbering scheme.

### Fixed
- **Tool -> Satellite on the AT-D878UVII** looked like a successful write but wrote nothing: the
  satellite data area (`0x4A80000`) is only written for the D890UV. The write button is now
  disabled with a note on the D878UVII, and a request for it reports an error instead of success.

## [0.10.3] - 2026-11-14

### Fixed
- **Settings lost when reopening an `.atd` file.** `save()` wrote them, but `load()` looked for
  other attribute names or types, so the values silently came back as defaults:
  - APRS `to_call` and `sending_text` (the loader searched for `"to_call "` / `"sending_text "`
    with a trailing space, XML parsers drop it);
  - APRS fixed position 2-8 N/S and E/W flags (names with a stray `;` in the loader);
  - APRS fixed position latitude/longitude (written as decimal, read with `toInt()`, so always 0;
    now written with 8 decimals);
  - all 32 APRS receive filters (the filter index was taken from the wrong XML element, so every
    filter was loaded into filter 0);
  - optional settings `long_key_time` (guarded by an attribute name that is never written) and
    `am_fm_function`;
  - 5Tone `self_id`, `ptt_bot_encode_id`, `ptt_eot_encode_id`.

  Files saved by earlier versions already contain these values, so they load correctly now. The
  new `xml-roundtrip-test` (random radio image -> memory -> `.atd` -> memory -> radio image) found
  them; on the D878UVII the bytes lost through the file went from 416 to 32. Still open: 32 bytes
  of 2Tone data on the D878UVII and about 1870 bytes on the D890UV.

## [0.10.2] - 2026-11-14

### Fixed
- **Radio hung on the talk group list** (see [Incident 2026-11-14](#incident-2026-11-14-radio-hangs-in-the-talk-group-list)):
  the talk group index table at `0x2600000` ended with a terminator that started mid-block, so the
  radio counted 704 entries for 698 talk groups and froze on the invalid ones. The entries are now
  padded to a whole 16 byte block with valid indexes and followed by an aligned all-`0xff` block.
  `list-order-test` checks the table and fails without the fix.

## [0.10.1] - 2026-11-14

### Fixed
- Digital contact read cut off fields of records longer than one 0x80 byte buffer (long UTF-8
  names). The reader keeps a 2 KB margin and does not loop forever when a read returns nothing.

### Tools
- `contacts-tool` (dry / write / verify the contact database), `serial-peek` (read-only radio
  probe) and `tools/fix_atd.py` (example script that edits an `.atd` codeplug).
- The 116 540-contact database was written to an AT-D878UVII and read back block by block
  (449 697 blocks, 0 differences); reading it back through the application code gives identical
  content.

## [0.10.0] - 2026-11-14

### Added
- Edit dialog for the Receive Group Call List (double-click a row; name plus up to 64 talk groups).

## [0.9.3] - 2026-11-14

### Fixed
- Opening a file merged the receive group lists into memory instead of replacing them, so groups
  missing from the file kept data read from the radio earlier.

## [0.9.2] - 2026-11-14

### Fixed
- The new splitter did not expand in both directions and stretched the toolbar vertically.

## [0.9.1] - 2026-11-14

### Changed
- The unimplemented *Friends List* menu entry is hidden.

## [0.9.0] - 2026-11-14

### Added
- The menu tree and the table are in a splitter: the menu width can be dragged (the reorder bar of
  0.8.0 forced a minimum width and squeezed the menu).

## [0.8.1] - 2026-11-14

### Fixed
- The digital emergency channel was read as one byte instead of two.
- Encoding the optional settings changed the in-memory priority zone A/B values.
- `readTalkgroupData` ignored the bank layout used by `writeTalkgroupData`.

## [0.8.0] - 2026-11-14

### Added
- Sort by any column and move entries to top / up / down / bottom in the Channel, Zone, Roaming
  Channel, Contact/Talk Group and Analog Address Book lists, with *Apply Sort Order* and
  automatic remapping of all references (zones, scan lists, receive groups, roaming zones, channel
  contacts). VFO A/B keep their slots.
- `list-order-test` (build with `-DANYTONE_BUILD_TESTS=ON`): about 2.2 million checks per codeplug,
  0 failures, on a codeplug read from the radio, on generated codeplugs and on a synthetic one. The
  GUI parts have no automated tests; they were checked by hand by the author.

## [0.7.18] - 2026-11-13

### Fixed
- D878UVII channel transmit contact index: the index is a little-endian `uint32` at record
  offset `0x14` (it was read as two big-endian bytes at `0x13`, which is only correct for
  indexes below 256). Verified by decoding and re-encoding 555 channel records read from the
  radio (identical bytes). The D890UV layout is unchanged and unverified.

## [0.7.17] - 2026-07-13

### Fixed
- Bluetooth options for the D890UV used those of the D878 (community fix by @Serphentas).

## [0.7.16] - 2026-07-13

### Fixed
- Headers of the zone channel dialog (community fix by @Serphentas).

## [0.7.15] - 2026-07-13

### Fixed
- The Save, Exit and About menu actions did nothing (community fix by @Serphentas).

## [0.7.14] - 2026-07-13

### Fixed
- Retry logic for the satellite (Keplerian) data download (community fix by @Serphentas).

## [0.7.13] - 2026-07-13

### Fixed
- Copying a channel actually cut it (community fix by @Serphentas).

## [0.7.12] - 2026-07-13

### Fixed
- Segfault when editing a channel: child attributes of a channel were not initialised (community fix by @Serphentas).

## [0.7.11] - 2026-07-11

### Fixed
- Prefabricated SMS write stays disabled until a reference from the stock CPS is available: the
  radio still did not show the written templates.

## [0.7.10] - 2026-07-11

### Fixed
- The default power-on channel was written at the wrong offset (D878UVII).

## [0.7.9] - 2026-07-11

### Fixed
- Master ID (and the elements that follow it) did not load from a saved file.

## [0.7.8] - 2026-07-11

### Changed
- Prefabricated SMS read/write reimplemented in the layout used by qdmr (byte map, index,
  contiguous ids). The write was disabled again in 0.7.11.

## [0.7.7] - 2026-07-11

### Fixed
- Prefabricated SMS write stays disabled (format incomplete).

## [0.7.6] - 2026-07-11

### Fixed
- Prefabricated SMS write disabled: the format written was not the one the radio uses.

## [0.7.5] - 2026-07-11

### Fixed
- Writing no SMS no longer wipes the SMS already in the radio.

## [0.7.4] - 2026-07-11

### Fixed
- Prefabricated SMS write was a no-op (it iterated an empty list); the feature table in the readme
  was cut to the entries tested on a radio.

## [0.7.3] - 2026-07-11

### Fixed
- The APRS settings dialog had no save path at all; a full `save()` (about 90 fields) was added.

## [0.7.2] - 2026-07-11

### Fixed
- Several settings dialogs never wrote their edits back on OK: Master ID, Hotkey, AES code, analog
  address book, GPS roaming and AM zone.

## [0.7.1] - 2026-07-11

### Fixed
- The Down button in the Zone, AM Zone, Scan List and Roaming Zone member editors never moved the
  top entry.

## [0.7.0] - 2026-07-11

### Added
- Re-importing a repeater list updates the existing channels in place (matched by channel or
  roaming channel name) instead of adding duplicates.

## [0.6.0] - 2026-07-11

### Added
- Roaming channels and roaming zones are generated from imported DMR repeaters (CC1, slot 1, in
  zones of 64).

## [0.5.0] - 2026-07-10

### Added
- Import of DMR repeaters from przemienniki.net lists (12.5 kHz bandwidth).

## [0.4.0] - 2026-07-10

### Added
- Import of repeater lists from przemienniki.net as analog channels.

## [0.3.2] - 2026-07-10

### Fixed
- The channel CSV import ignored the Color Code and Slot columns.

## [0.3.1] - 2026-07-10

### Fixed
- Zones with unlinked members showed empty rows; they now show the names and log the member
  channels that could not be found.

## [0.3.0] - 2026-07-10

### Added
- Channel and zone CSV import in the import dialog.

## [0.2.4] - 2026-07-10

### Fixed
- The talk group index table at `0x2600000`, from which the radio builds its talk group list, was
  not written, so the radio showed only the first talk group.

## [0.2.3] - 2026-07-10

### Fixed
- Mid-session write failures left the radio stuck in "PC WRITE".

## [0.2.2] - 2026-07-10

### Fixed
- Retry after a failed write started a read, which wiped a fresh import; the table views crashed on
  values read from the radio that were out of range.

## [0.2.1] - 2026-07-10

### Fixed
- Crashes when reading a codeplug with erased or invalid data.

## [0.2.0] - 2026-07-09

### Added
- Talk group CSV import in the import dialog.

## [0.1.0] - 2026-07-09

### Added
- Digital contact CSV files without a header line can be imported.

## [0.0.6] - 2026-07-09

### Changed
- The CSV import logs how many rows were parsed and skipped.

## [0.0.5] - 2026-07-09

### Fixed
- Silent failures of the serial session and the connection retry.

## [0.0.4] - 2026-07-09

### Fixed
- Segfault when reading the digital contacts from the radio.

## [0.0.3] - 2026-07-09

### Fixed
- Crash and silent failures when writing the digital contacts.

## [0.0.2] - 2026-07-02

### Fixed
- The build failed against Qt older than 6.9.

## [0.0.1] - 2026-02-02

Release `v0.0.1-alpha9` of the upstream project (Build 9), the baseline of this changelog.

---

Commits that only change documentation (readme) do not appear in this list.

## Incident 2026-11-14: radio hangs in the talk group list

**Symptom.** After writing a codeplug with 698 talk groups to an AT-D878UVII (V101) the radio's
talk group list showed `n/704`. Pressing Up on the first entry to jump to the end froze the
radio; scrolling down one by one froze it at 699/704. The freeze survived the power switch
(the screen stayed on the list); only removing the battery helped. The last two visible entries
were the same talk group.

**Cause.** A read-only dump of the radio showed that the index table at `0x2600000` itself was
right (698 entries, indexes 0-697, no duplicates), and so were the bitmap, the order table at
`0x4800000` and the records. The end of the table was not. The writer appended 16 bytes of
`0xff` after the entries, but 698 entries are 2792 bytes, so the terminator started 8 bytes into
a 16 byte block, and `writeMemory` padded the tail with 8 zero bytes. The radio reads the table in
aligned 16 byte blocks until it meets an all-`0xff` block and counts every word before it: 2816
bytes / 4 = 704. Entries 699-702 were `0xffffffff` and 703-704 were zero, and the list froze on
the invalid indexes. The defect was introduced together with the index table in July 2026. By the same
arithmetic a codeplug with 686 talk groups would have made the radio count 692 entries; that
was not observed and no hang was reported at the time.

**Fix.** The entries are padded to a whole 16 byte block with valid indexes (the last one
repeated, so up to three repeated entries may appear at the end of the list), then the table is
ended with an aligned all-`0xff` block. Confirmed on the radio: after a normal write of "Other
Data" the list is correct and no longer freezes.

**Recovery for affected radios.** Write the codeplug again with the fixed version and only
"Other Data" selected. The digital contact database does not have to be rewritten.

**How it was found.** The radio could not be read while frozen (it did not enumerate on USB);
after a battery pull the table, the bitmap, the order table and the last records were read with
`serial-peek` and the counts compared with the file.

**Not changed, to be investigated.** The talk group bitmap is padded with zero bytes up to
`0x4f0` bytes, which marks slots 10008-10111 as in use (104 phantom entries). It did not cause
this freeze and was left as it is.
