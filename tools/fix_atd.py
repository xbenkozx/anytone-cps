import re, sys
import xml.etree.ElementTree as ET
src, dst = sys.argv[1], sys.argv[2]
t = open(src, encoding="utf-8").read()

# 1. Parrot -> 260097 (private call)
t, n = re.subn(r'(<Talkgroup id="\d+" dmr_id=)"9990"( call_alert="0" call_type="0" name="Parrot"/>)', r'\1"260097"\2', t)
assert n == 1, n

# 2. talkgroups: reuse an existing contact with the same DMR ID, else append a new one
ids = [int(x) for x in re.findall(r'<Talkgroup id="(\d+)"', t)]
state = {"next": max(ids) + 1, "added": ""}
by_dmr = {int(d): int(i) for i, d in re.findall(r'<Talkgroup id="(\d+)" dmr_id="(\d+)" call_alert="0" call_type="1"', t)}
def ensure_tg(dmr, name):
    if dmr in by_dmr: return by_dmr[dmr]
    i = state["next"]; state["next"] += 1; by_dmr[dmr] = i
    state["added"] += f'        <Talkgroup id="{i}" dmr_id="{dmr}" call_alert="0" call_type="1" name="{name}"/>\n'
    return i
NEEDED = [(26055, "TG26055 SP5KAB"), (26057, "TG26057 MASR"), (2605655, "TG2605655 Grodz")]
for dmr, name in NEEDED: ensure_tg(dmr, name)
new = {dmr: by_dmr[dmr] for dmr, _ in NEEDED}
# listening list SP5: national + region 5 (names from the BrandMeister Poland wiki)
LISTEN = [(260, "TG260 Poland"), (2600, "TG2600 Polonia"), (2605, "TG2605 Okreg 5"), (260501, "TG260501"),
          (26051, "SP5_WARSZAWA"), (26052, "TG26052 Komorow"), (26053, "TG26053 Mazovia"), (26054, "TG26054 Ciechan"),
          (26055, "TG26055 SP5KAB"), (26056, "TG26056 SP73VOT"), (2605655, "TG2605655 Grodz"), (26057, "TG26057 MASR"),
          (260577, "TG260577 Siedlce"), (26058, "TG26058 SP1PMY"), (26059, "TG26059 Ostrol")]
listen_ids = [ensure_tg(d, n) for d, n in LISTEN]
last = list(re.finditer(r'        <Talkgroup [^\n]*/>\n', t))[-1]
t = t[:last.end()] + state["added"] + t[last.end():]

# 3. TS2 channels: (repeater, old suffix) -> (new suffix, tg)
plan = {
 "SR5WB":  {"2605": 2605655, "260": 26057},
 "SR5WAD": {"2605": 26055,   "260": 26057},
 "SR5WU":  {"2605": 26055},
 "SR5WW":  {"2605": 26055},
 "SR5DVR": {"2605": 26057},
}
changed = []
def fix(m):
    line = m.group(0)
    nm = re.search(r' name="([^"]*)"', line).group(1)
    mm = re.fullmatch(r'(\S+) 2/(\d+)', nm)
    if not mm or mm.group(1) not in plan or mm.group(2) not in plan[mm.group(1)]:
        return line
    tg = plan[mm.group(1)][mm.group(2)]
    line = line.replace(f'name="{nm}"', f'name="{mm.group(1)} 2/{tg}"')
    line = re.sub(r'contact_idx="\d+"', f'contact_idx="{new[tg]}"', line)
    changed.append((nm, f"{mm.group(1)} 2/{tg}"))
    return line
t = re.sub(r'        <Channel [^\n]*/>\n', fix, t)

# 4. SP5 receive group list = national + region 5 (keeps existing entries, no duplicates)
def rx(m):
    cur = [int(x) for x in m.group(2).split("|") if x]
    for i in listen_ids:
        if i not in cur: cur.append(i)
    return m.group(1) + "|".join(str(x) for x in cur) + '"'
t, n = re.subn(r'(<ReceiveGroup id="\d+" name="SP5" tg_list=")([^"]*)"', rx, t)
assert n == 1
open(dst, "w", encoding="utf-8").write(t)

# checks
r = ET.parse(dst).getroot()
tg = {int(e.get("id")): e for e in r.iter("Talkgroup")}
assert len(tg) == len(list(r.iter("Talkgroup")))
chs = list(r.iter("Channel"))
assert len({c.get("id") for c in chs}) == len(chs)
assert len({c.get("name") for c in chs}) == len(chs), "duplicate channel names"
for c in chs:
    if c.get("channel_type") == "1": assert int(c.get("contact_idx")) in tg, c.get("name")
assert all(len(e.get("name")) <= 16 for e in tg.values()), [e.get("name") for e in tg.values() if len(e.get("name"))>16]
rg = [e for e in r.iter("ReceiveGroup") if e.get("name") == "SP5"][0]
assert all(int(x) in tg for x in rg.get("tg_list").split("|")) and len(rg.get("tg_list").split("|")) <= 64
print("SP5 RX list:", [tg[int(x)].get("dmr_id") for x in rg.get("tg_list").split("|")])
print(dst.split("/")[-1], "OK; TG:", new, "; channels changed:", len(changed))
for a, b in changed: print("  ", a, "->", b)
