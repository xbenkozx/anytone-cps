# Changelog

Changes of the `mabalew/anytone-cps` fork. Entries describe what was verified and how; the
detailed description of the earlier fork changes is in [readme.md](readme.md).

## Unreleased

### Added
- Sort by any column and move entries to top / up / down / bottom in the Channel, Zone, Roaming
  Channel, Contact/Talk Group and Analog Address Book lists, with *Apply Sort Order* and
  automatic remapping of all references.
- Edit dialog for the Receive Group Call List (double-click a row; name plus up to 64 talk groups).
- Headless tools: `list-order-test`, `contacts-tool` (dry / write / verify the contact database),
  `serial-peek` (read-only radio probe). Build with `-DANYTONE_BUILD_TESTS=ON`.
- `tools/fix_atd.py`, an example script that edits an `.atd` codeplug.

### Fixed
- **Radio hung on the talk group list** (see [Incident 2026-11-14](#incident-2026-11-14-radio-hangs-in-the-talk-group-list)):
  the talk group index table at `0x2600000` ended with a terminator that started mid-block, so the
  radio counted 704 entries for 698 talk groups and froze on the invalid ones. The entries are now
  padded to a whole 16 byte block with valid indexes and followed by an aligned all-`0xff` block.
  `list-order-test` checks the table and fails without the fix.
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
