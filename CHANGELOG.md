# Changelog

Changes of the `mabalew/anytone-cps` fork. Entries describe what was verified and how; the
detailed description of the earlier fork changes is in [readme.md](readme.md).

## Unreleased (branch `feature/list-sort-reorder`)

### Added
- Sort by any column and move entries to top / up / down / bottom in the Channel, Zone, Roaming
  Channel, Contact/Talk Group and Analog Address Book lists, with *Apply Sort Order* and
  automatic remapping of all references.
- Edit dialog for the Receive Group Call List (double-click a row; name plus up to 64 talk groups).
- Headless tools: `list-order-test`, `contacts-tool` (dry / write / verify the contact database),
  `serial-peek` (read-only radio probe). Build with `-DANYTONE_BUILD_TESTS=ON`.
- `tools/fix_atd.py`, an example script that edits an `.atd` codeplug.

### Fixed
- Digital contact read cut off fields of records longer than one 0x80 byte buffer (long UTF-8
  names). The reader keeps a 2 KB margin and does not loop forever when a read returns nothing.
- Opening a file merged receive group lists into memory instead of replacing them.
- The reorder button bar squeezed the menu tree; menu and table are now in a resizable splitter.
- Digital emergency channel was read as one byte instead of two.
- Encoding the optional settings changed the in-memory priority zone A/B values.
- `readTalkgroupData` ignored the bank layout used by `writeTalkgroupData`.

### Changed
- The unimplemented *Friends List* menu entry is hidden.

### Verification
- `list-order-test` passes (about 2.2 million checks per codeplug, 0 failures) on a codeplug read
  from the radio, on generated codeplugs and on a synthetic one; it fails when the receive group
  fix is removed.
- The 116 540-contact database was written to an AT-D878UVII and read back block by block
  (449 697 blocks, 0 differences); reading it back through the application code on an
  in-memory image gives identical content.
- The GUI parts (sort / move buttons, receive group dialog, splitter) have no automated tests;
  they were checked by hand by the author, and the application starts and runs headless.

## 2026-11-13

### Fixed
- D878UVII channel transmit contact index: the index is a little-endian `uint32` at record
  offset `0x14` (it was read as two big-endian bytes at `0x13`, which is only correct for
  indexes below 256). Verified by decoding and re-encoding 555 channel records read from the
  radio (identical bytes). The D890UV layout is unchanged and unverified.

## Earlier

Talk group, digital contact, serial protocol, import, settings persistence and community fixes
are described in [readme.md](readme.md#changes-in-this-fork).
