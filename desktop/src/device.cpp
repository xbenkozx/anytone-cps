#include "device.h"
#include "int.h"

bool Device::verbose = false;

constexpr int kFmSlots = 128;

static inline int readU32beToInt(const QByteArray& data, int offset)
{
    if (offset < 0 || offset + 4 > data.size()) return 0;
    // If your Int::fromBytes supports 4 bytes, use that instead.
    // This is big-endian; flip if your storage is little-endian.
    const quint32 v =
        (quint8(data[offset + 0]) << 24) |
        (quint8(data[offset + 1]) << 16) |
        (quint8(data[offset + 2]) << 8)  |
        (quint8(data[offset + 3]) << 0);
    return static_cast<int>(v);
}

static inline QString readFixedStringUtf8(const QByteArray& data, int offset, int len)
{
    if (offset < 0 || offset + len > data.size()) return {};
    QString str = QString(data.mid(offset, len));
    str.remove(QChar('\0'));
    return str;
}

QByteArray VirtualDevice::readMemoryAddress(int address, int length) {
    if(length % 16 != 0) qDebug() << "ERR: Memory Alignment" << QByteArray::number(address).toHex();
    return bin_data.mid(address, length);
}
void VirtualDevice::writeMemoryAddress(int address, QByteArray data) {
    if(data.size() % 16 != 0) qDebug() << "ERR: Memory Alignment" << QString::number(address, 16) << QString::number(data.size(), 16);
    bin_data.replace(address, data.size(), data);
}
bool VirtualDevice::connect(QString filepath, int _n) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "ERR: Cannot open file";
        return false;
    }
    
    bin_data = file.readAll();

    file.close();

    return true;
}
void Device::readRadioData(){
    std::vector<QString> local_info = readDeviceInfo();

    if(local_info[0] == QString("ID878UV2") && local_info[1] == QString("V101")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII_FW400;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) readOtherData();
        if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) !=  DeviceRWType::NONE) readDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) readBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) readBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) readBk2Image();
    }else if(local_info[0] == QString("ID890UV") && local_info[1] == QString("V100")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D890UV_FW103;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) readOtherData();
        if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) !=  DeviceRWType::NONE) readDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) readBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) readBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) readBk2Image();
    }else{
        qDebug() << local_info[0] << local_info[1];
        emit finished(DeviceStatus::STATUS_DEVICE_MISMATCH);
    }
}
void Device::writeRadioData(){
    std::vector<QString> local_info = readDeviceInfo();

    if(local_info[0] == QString("ID878UV2") && local_info[1] == QString("V101")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII_FW400;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) writeOtherData();
        if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) != DeviceRWType::NONE) writeDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) writeBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) writeBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) writeBk2Image();
    }else if(local_info[0] == QString("ID890UV") && local_info[1] == QString("V100")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D890UV_FW103;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) writeOtherData();
        if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) !=  DeviceRWType::NONE) writeDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) writeBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) writeBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) writeBk2Image();
        if((read_write_options & DeviceRWType::SATELLITE_DATA) !=  DeviceRWType::NONE) writeSatelliteData();

    
    }else{
        qDebug() << local_info[0] << local_info[1];
        emit finished(DeviceStatus::STATUS_DEVICE_MISMATCH);
    }
}
QByteArray Device::readLocalInformation(){
    std::vector<QString> local_info = readDeviceInfo();
    if(local_info[0] == QString("ID878UV2") && local_info[1] == QString("V101")){
        return readMemory(Anytone::D878II_MAP.LocalInfo, 0x100);
    }else if(local_info[0] == QString("ID890UV") && local_info[1] == QString("V100")){
        return readMemory(Anytone::D890_MAP.LocalInfo, 0x100);
    }else{
        qDebug() << local_info[0] << local_info[1];
        emit finished(DeviceStatus::STATUS_DEVICE_MISMATCH);
        return QByteArray(0x100, 0);
    }
    
}
void Device::writeLocalInformation(QByteArray data){
    std::vector<QString> local_info = readDeviceInfo();

    if(local_info[0] == QString("ID878UV2") && local_info[1] == QString("V101")){
        return writeMemory(Anytone::D878II_MAP.LocalInfo, data);
    }else if(local_info[0] == QString("ID890UV") && local_info[1] == QString("V100")){
        return writeMemory(Anytone::D890_MAP.LocalInfo, data);
    }else{
        qDebug() << local_info[0] << local_info[1];
        emit finished(DeviceStatus::STATUS_DEVICE_MISMATCH);
    }
    
}

// Images
void Device::readBootImage(){
    image_data.clear();
    for(int i=0; i<0xa000; i+=0x10){
        image_data.append(readMemory(Anytone::Memory::Map()->BootImage + i, 0x10));
        if ((i % 0x400) == 0) {
            emit update1(i, 0, "");
        }
    }
    emit update1(0xa000, 0, "");
}
void Device::readBk1Image(){
    image_data.clear();
    for(int i=0; i<0xa000; i+=0x10){
        image_data.append(readMemory(Anytone::Memory::Map()->BK1Image + i, 0x10));
        if ((i % 0x400) == 0) {
            emit update1(i, 0, "");
        }
    }
    emit update1(0xa000, 0, "");
}
void Device::readBk2Image(){
    image_data.clear();
    for(int i=0; i<0xa000; i+=0x10){
        image_data.append(readMemory(Anytone::Memory::Map()->BK2Image + i, 0x10));
        if ((i % 0x400) == 0) {
            emit update1(i, 0, "");
        }
    }
    emit update1(0xa000, 0, "");
}
void Device::writeBootImage(){
    if(image_data.size() != 0xa000) return;
    for(int i=0; i<0xa000; i+=0x10){
        writeMemory(Anytone::Memory::Map()->BootImage + i, image_data.mid(i, 0x10));
        if ((i % 0x400) == 0) {
            emit update1(i, 0, ""); 
        }
    }
    emit update1(0xa000, 0, "");
}
void Device::writeBk1Image(){
    if(image_data.size() != 0xa000) return;
    for(int i=0; i<0xa000; i+=0x10){
        writeMemory(Anytone::Memory::Map()->BK1Image + i, image_data.mid(i, 0x10));
        if ((i % 0x400) == 0) {
            emit update1(i, 0, "");
        }
    }
    emit update1(0xa000, 0, "");
}
void Device::writeBk2Image(){
    if(image_data.size() != 0xa000) return;
    for(int i=0; i<0xa000; i+=0x10){
        writeMemory(Anytone::Memory::Map()->BK2Image + i, image_data.mid(i, 0x10));
        if ((i % 0x400) == 0) {
            emit update1(i, 0, "");
        }
    }
    emit update1(0xa000, 0, "");
}

// DIGITAL CONTACTS
void Device::readDigitalContacts(){
    // TODO: Implement for D168UV

    Anytone::Memory::initDigitalContacts();

    emit update1(0, 1, "Reading Data");

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    int k_DcBufSize = map->DigitalContactBufferLength;

    int contact_count = Int::fromBytes(readMemory(map->DigitalContactMeta, 0x10).mid(0, 4));
    QByteArray contact_data;
    contact_data.reserve(k_DcBufSize * contact_count);

    // contact_count = 10;

    int offset = 0;
    for(int i = 0; i < contact_count; i++){
        if(contact_count > 100 && i % int(contact_count/100) == 0){
            emit update2(i, contact_count, "Reading Contacts");
        }

        if(contact_data.size() - offset < k_DcBufSize){
            contact_data.append(getDigitalContactDataBuffer(contact_data.size()));
        }
        Anytone::DigitalContact *dc = Anytone::Memory::digital_contacts.at(i);

        parseDigitalContact(dc, contact_data, offset);
    }
}
void Device::parseDigitalContact(Anytone::DigitalContact *dc, QByteArray contact_data, int &offset){
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        parseDigitalContact_D878UVII(dc, contact_data, offset);
    }
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
        parseDigitalContact_D890UV(dc, contact_data, offset);
    }
}
void Device::parseDigitalContact_D878UVII(Anytone::DigitalContact *dc, QByteArray contact_data, int &offset){
    int eos = 0;

    dc->call_type = static_cast<uint8_t>(contact_data.at(offset));
    offset += 1;
    dc->radio_id = QString(contact_data.mid(offset, 0x4).toHex()).toInt();
    offset += 4;
    dc->call_alert = static_cast<uint8_t>(contact_data.at(offset));
    offset += 1;
    

    eos = contact_data.indexOf('\0', offset);
    dc->name = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 1;

    eos = contact_data.indexOf('\0', offset);
    dc->city = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 1;
    
    eos = contact_data.indexOf('\0', offset);
    dc->callsign = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 1;

    eos = contact_data.indexOf('\0', offset);
    dc->state = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 1;

    eos = contact_data.indexOf('\0', offset);
    dc->country = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 1;

    eos = contact_data.indexOf('\0', offset);
    dc->remarks = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 1;
}
void Device::parseDigitalContact_D890UV(Anytone::DigitalContact *dc, QByteArray contact_data, int &offset){
    int eos = 0;

    dc->call_type = static_cast<uint8_t>(contact_data.at(offset));
    offset += 1;
    dc->call_alert = static_cast<uint8_t>(contact_data.at(offset))==2;
    offset += 1;
    dc->radio_id = QString(contact_data.mid(offset, 0x4).toHex()).toInt();
    offset += 4;

    eos = contact_data.indexOf(QByteArray("\0\0", 2), offset);
    dc->name = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 2;

    eos = contact_data.indexOf(QByteArray("\0\0", 2), offset);
    dc->city = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 2;
    
    eos = contact_data.indexOf(QByteArray("\0\0", 2), offset);
    dc->callsign = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 2;

    eos = contact_data.indexOf(QByteArray("\0\0", 2), offset);
    dc->state = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 2;

    eos = contact_data.indexOf(QByteArray("\0\0", 2), offset);
    dc->country = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 2;

    eos = contact_data.indexOf(QByteArray("\0\0", 2), offset);
    dc->remarks = QString(contact_data.mid(offset, eos-offset));
    offset = eos + 2;

    offset++;

    dc->name.remove(QChar('\0'));
    dc->city.remove(QChar('\0'));
    dc->callsign.remove(QChar('\0'));
    dc->state.remove(QChar('\0'));
    dc->country.remove(QChar('\0'));
    dc->remarks.remove(QChar('\0'));

}

QByteArray Device::getDigitalContactDataBuffer(int offset){

    const auto* map = Anytone::Memory::Map();
    if (!map) return QByteArray();

    int base = map->DigitalContactData;
    int k_DcBufSize = map->DigitalContactBufferLength;
    int k_DcBlkLen = map->DigitalContactDataBlockLength;
    int k_DcBlkStride = map->DigitalContactDataStride;

    QByteArray data;
    data.reserve(k_DcBufSize);
    if(offset % 16 != 0){
        qDebug() << "ERR: Offset Alignment";
        return data;
    }

    for(int i = offset; i < offset + k_DcBufSize; i += 0x10){
        int addr_mod = i % k_DcBlkLen;
        int block = int(((i - addr_mod) / k_DcBlkLen));
        int addr = base + (block * k_DcBlkStride) + addr_mod;
        data.append(readMemory(addr, 0x10));
    }

    return data;
}
void Device::writeDigitalContacts(){
    // TODO: Implement for D168UV
    
    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    int contact_data_addr = map->DigitalContactData;
    int contact_order_addr = map->DigitalContactOrder;
    int contact_count_addr = map->DigitalContactMeta;
    int k_DcBufSize = map->DigitalContactBufferLength;
    int k_DcBlkLen = map->DigitalContactDataBlockLength;
    int k_DcBlkStride = map->DigitalContactDataStride;
    int k_OrderBlkLen = map->DigitalContactOrderBlockLength;
    int k_OrderBlkStride = map->DigitalContactOrderBlockStride;

    QByteArray contact_data;
    QByteArray order_data;
    int contact_total = 0;
    int contact_count = 0;
    QVector<std::tuple<int, QByteArray, QByteArray>> order_data_array = {};

    emit update1(0, 3, "Writing Digital Contacts");

    for(int idx = 0; idx < Anytone::Memory::digital_contacts.size(); idx++){
        Anytone::DigitalContact *contact = Anytone::Memory::digital_contacts.at(idx);
        if(contact->radio_id > 0) contact_total++;
    }

    QVector<Anytone::DigitalContact*> sorted_contacts = Anytone::Memory::digital_contacts;

    std::stable_sort(sorted_contacts.begin(),
                sorted_contacts.end(),
                [](const Anytone::DigitalContact *a, const Anytone::DigitalContact *b) {
                    return a->call_type > b->call_type;
                });

    for(int idx = 0; idx < sorted_contacts.size(); idx++){
        Anytone::DigitalContact *contact = sorted_contacts.at(idx);
        if(contact_total > 100 && contact_count % int(contact_total/100) == 0){
            emit update2(contact_count, contact_total, "Compressing Data");
        }

        if(contact->radio_id == 0) continue;
        int order_rid_int = (QString::number(contact->radio_id).rightJustified(8, '0').toUInt(nullptr, 16) << 1) + contact->call_type;
        QByteArray order_rid = Int::toBytes(order_rid_int, 4);
        QByteArray data_offset = Int::toBytes(contact_data.size(), 4);
        order_data_array.push_back(
            std::tuple<int, QByteArray, QByteArray>(order_rid_int, order_rid, data_offset)
        );

        if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
            contact_data.append(contact->call_type);
            contact_data.append(QByteArray::fromHex(QString::number(contact->radio_id).rightJustified(8, '0').toUtf8()));
            contact_data.append(contact->call_alert);
            contact_data.append(contact->name.toUtf8() + '\0');
            contact_data.append(contact->city.toUtf8() + '\0');
            contact_data.append(contact->callsign.toUtf8() + '\0');
            contact_data.append(contact->state.toUtf8() + '\0');
            contact_data.append(contact->country.toUtf8() + '\0');
            contact_data.append(contact->remarks.toUtf8() + '\0');
        }
        
        if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){
            contact_data.append(contact->call_type);
            contact_data.append(contact->call_alert);
            contact_data.append(QByteArray::fromHex(QString::number(contact->radio_id).rightJustified(8, '0').toUtf8()));
            contact_data.append(Format::wideCharString(contact->name) + QByteArray("\0\0", 2));
            contact_data.append(Format::wideCharString(contact->city) + QByteArray("\0\0", 2));
            contact_data.append(Format::wideCharString(contact->callsign) + QByteArray("\0\0", 2));
            contact_data.append(Format::wideCharString(contact->state) + QByteArray("\0\0", 2));
            contact_data.append(Format::wideCharString(contact->country) + QByteArray("\0\0", 2));
            contact_data.append(Format::wideCharString(contact->remarks) + QByteArray("\0\0", 2));
        }

        contact_count++;
    }

    int addr_mod = contact_data.size() % k_DcBlkLen;
    int block = int((contact_data.size() - addr_mod) / k_DcBlkLen);
    int end_address = contact_data_addr + (block * k_DcBlkStride) + addr_mod;

    QByteArray contact_count_data;
    contact_count_data.append(Int::toBytes(contact_total, 4));
    contact_count_data.append(Int::toBytes(end_address, 4));
    contact_count_data.append(QByteArray(0x8, 0));

    writeMemory(contact_count_addr, contact_count_data);

    std::stable_sort(order_data_array.begin(),
        order_data_array.end(),
        [](const std::tuple<int, QByteArray, QByteArray> &a, const std::tuple<int, QByteArray, QByteArray> &b) {
            return std::get<0>(a) < std::get<0>(b);
        });

    for(std::tuple<int, QByteArray, QByteArray> a : order_data_array){
        order_data.append(std::get<1>(a));
        order_data.append(std::get<2>(a));
    }

    order_data.append(QByteArray(0x10 - (order_data.size() % 0x10), 0xff));
    contact_data.append(QByteArray(0x10 - (contact_data.size() % 0x10), 0));

    // Write order data
    int last_block = -1;
    int last_addr = 0;
    emit update1(1, 3, "Writing Digital Contacts");
    for(int idx = 0; idx < order_data.size(); idx+=0x10){
        int addr_mod = idx % k_OrderBlkLen;
        int block = int((idx - addr_mod) / k_OrderBlkLen);
        
        
        int addr = contact_order_addr + (block * k_OrderBlkStride) + addr_mod;
        QByteArray data = order_data.mid(idx, 0x10);
        
        writeMemory(addr, data);
        if(idx > 0 && int(idx / 0x10) % int((order_data.size() / (0x10 * 100))) == 0){
            emit update2(idx, order_data.size(), "Writing Order Data");
        }
    }

    // Write Contact Data
    int contact_data_modulo = int((contact_data.size() / (0x10 * 100)));
    emit update1(2, 3, "Writing Digital Contacts");
    for(int idx = 0; idx < contact_data.size(); idx+=0x10){
        int addr_mod = idx % k_DcBlkLen;
        int block = int((idx - addr_mod) / k_DcBlkLen);
        int addr = contact_data_addr + (block * k_DcBlkStride) + addr_mod;
        QByteArray data = contact_data.mid(idx, 0x10);
        writeMemory(addr, data);
        if(idx > 0 && int(idx / 0x10) % contact_data_modulo == 0){
            emit update2(idx, contact_data.size(), "Writing Digital Data");
        }
    }

    emit update1(3, 3, "Writing Digital Contacts");
    emit update2(0, 0, "");

}

// Read Other Data
void Device::readOtherData(){
        Anytone::Memory::init();

        // 878UVII
        // 0x1640800, 0x70 # SMS Set List? first 5 x0 of 100
        // 0x1640880, 0x10 # Set list? max 16 or 128
        // 0x24c0c80, 0x10 # Set list? max 16 or 128
        // 0x24c1800, 0x500 # all x0
        // 0x2501300, 0x10 # all 0xff
        // 0x2501500, 0x100 # all 0x00
        // 0x25c0000, 0x500 # HotKey Analog Quick Call
        // 0x25c0500, 0x360 # HotKey HotKey
        // 0x25c0b00, 0x30 # HotKey State Information Set List
        // 0x2600000, 0xf0 # list up to 56

        int steps = 25;
        int step = 0;
        
        readAmAir();
        emit update1(step++, steps, "Reading Data");
        readAmZones();
        emit update1(step++, steps, "Reading Data");
        readChannelData();
        emit update1(step++, steps, "Reading Data");
        readTalkgroupData();
        emit update1(step++, steps, "Reading Data");
        readZoneData();
        emit update1(step++, steps, "Reading Data");
        readRadioIdData();
        emit update1(step++, steps, "Reading Data");
        readScanListData();
        emit update1(step++, steps, "Reading Data");
        readFmData();
        emit update1(step++, steps, "Reading Data");
        readRoamingChannelData();
        emit update1(step++, steps, "Reading Data");
        readRoamingZoneData();
        emit update1(step++, steps, "Reading Data");
        readSettings();
        emit update1(step++, steps, "Reading Data");
        readAprsSettings();
        emit update1(step++, steps, "Reading Data");
        readToneSettings();
        emit update1(step++, steps, "Reading Data");
        readTone2Settings();
        emit update1(step++, steps, "Reading Data");
        readGpsRoamingData();
        emit update1(step++, steps, "Reading Data");
        readMasterId();
        emit update1(step++, steps, "Reading Data");
        readAutoRepeaterFrequencyData();
        emit update1(step++, steps, "Reading Data");
        readPrefabricatedSms();
        emit update1(step++, steps, "Reading Data");
        readReceiveGroups();
        emit update1(step++, steps, "Reading Data");
        readAesEncryptionKeys();
        emit update1(step++, steps, "Reading Data");
        readArc4EncryptionKeys();
        emit update1(step++, steps, "Reading Data");
        readEncryptionKeys();
        emit update1(step++, steps, "Reading Data");
        readHotKeySettings();
        emit update1(step++, steps, "Reading Data");
        readAnalogAddress();
        emit update1(step++, steps, "Reading Data");
        readTalkgroupWhitelist();
        emit update1(step++, steps, "Reading Data");
        readDigitalContactWhitelist();

        emit update1(steps-1, steps, "Linking Data");
        Anytone::Memory::linkReferences();
    }
void Device::readAesEncryptionKeys()
{
    // TODO: Implement for D168UV
    constexpr int kAesSetBytes = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->AESSet, kAesSetBytes);
    if (!is_alive) return;

    // Build enabled key IDs from bitmap
    std::vector<int> keyIds;
    keyIds.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                keyIds.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base = map->AESData;

    for (size_t i = 0; i < keyIds.size(); ++i) {
        if (!is_alive) return;

        emit update2(static_cast<int>(i),
                     static_cast<int>(keyIds.size()),
                     "Reading AES Code Data");

        const int keyId = keyIds[i];
        const int addr  = base + (keyId * map->AESDataOffset);

        if (keyId < 0 || keyId >= static_cast<int>(Anytone::Memory::aes_encryption_keys.size()))
            continue;

        auto* key = Anytone::Memory::aes_encryption_keys.at(keyId);
        if (!key)
            continue;

        const QByteArray keyData = readMemory(addr, map->AESDataLength);
        if (!is_alive) return;

        key->decode(keyData);
    }
}
void Device::readAmAir(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103) {
        qDebug() << "Skipping AM Air";
        return;
    }

    const auto* map = Anytone::Memory::Map();
    if (!map) return;
    

    QByteArray setData = readMemory(map->AmAirSet, 0x20);
    std::vector<int> idList;
    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                idList.push_back(byteIndex * 8 + bit);
            }
        }
    }

    int base = map->AmAirData;
    int stride = map->AmAirDataStride;
    int len = map->AmAirDataLength;

    Anytone::AmAir *vfo_am = Anytone::Memory::am_air_list[256];
    vfo_am->decode(readMemory(map->AmAirVfo, len));

    for (size_t i = 0; i < idList.size(); ++i) {
        if (!is_alive) {
            emit finished(DeviceStatus::STATUS_COM_ERROR);
            return;
        }
        emit update2(static_cast<int>(i),
                     static_cast<int>(idList.size()),
                     "Reading AM Air Data");

        const int idx = idList[i];
        if (idx < 0 || idx >= Anytone::Memory::am_air_list.size())
            continue;

        int addr = base + (idx * stride);
        QByteArray data = readMemory(addr, len);
        Anytone::AmAir *am = Anytone::Memory::am_air_list[idx];
        am->decode(data);
    }
}
void Device::readAmZones(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103) {
        qDebug() << "Skipping AM Zones";
        return;
    }

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    QByteArray setData = readMemory(map->AmZoneSet, 0x10);
    QByteArray aChannelData = readMemory(map->AmZoneAChannel, 0x10);
    

    std::vector<int> idList;
    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                idList.push_back(byteIndex * 8 + bit);
            }
        }
    }

    int base = map->AmZoneData;
    int stride = map->AmZoneDataStride;
    int len = map->AmZoneDataLength;

    for (size_t i = 0; i < idList.size(); ++i) {
        if (!is_alive) {
            emit finished(DeviceStatus::STATUS_COM_ERROR);
            return;
        }
        emit update2(static_cast<int>(i),
                     static_cast<int>(idList.size()),
                     "Reading AM Zone Data");

        const int idx = idList[i];
        if (idx < 0 || idx >= Anytone::Memory::am_zones.size())
            continue;

        int addr = base + (idx * stride);
        QByteArray data = readMemory(addr, len);
        Anytone::AmZone *az = Anytone::Memory::am_zones[idx];
        az->decode(data);

        az->aChannelIdx = Int::fromBytes(aChannelData.mid(idx*2, 2));

        QByteArray scanChannelData = readMemory(map->AmZoneScan + (idx * 0x10), 0x10);

        for (int byteIndex = 0; byteIndex < 4; ++byteIndex) {
            const quint8 bits = static_cast<quint8>(scanChannelData.at((idx * 4) + byteIndex));
            for (int bit = 0; bit < 8; ++bit) {
                if (Bit::test(bits, bit)) {
                    int i = byteIndex * 8 + bit;
                    if(i < az->member_channel_idxs.size()) az->scan_channel_idxs.append(az->member_channel_idxs[i]);
                }
            }
        }
    }

}
void Device::readAnalogAddress(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    QByteArray set_list = readMemory(map->AnalogBookSet, 0x100);
    QByteArray id_list = readMemory(map->AnalogBookId, 0x100);

    QVector<int> idx_list;

    for(uint8_t i : id_list){
        if(i != 0xff){
            idx_list.append(i);
        }
    }

    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400) {
        int read_len = (idx_list.size() * 0x18);
        if(read_len % 16 != 0) read_len += 0x8;

        QByteArray data = readMemory(map->AnalogBookData, read_len);

        for(uint8_t i : idx_list){
            Anytone::AnalogAddress *item = Anytone::Memory::analog_addresses.at(i);
            item->decode(data.mid(i*map->AnalogBookDataStride, map->AnalogBookDataLength));
        }
    }

    if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103) {
        int base = map->AnalogBookData;
        int stride = map->AnalogBookDataStride;
        int len = map->AnalogBookDataLength;

        for(uint8_t i : idx_list){
            int addr = base + (i * stride);
            QByteArray data = readMemory(addr, len);
            Anytone::AnalogAddress *item = Anytone::Memory::analog_addresses.at(i);
            item->decode(data);
        }
    }
}
void Device::readAprsSettings(){
    // TODO: Implement for D168UV

    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400) {
        QByteArray data_2501000 = readMemory(0x2501000, 0x240);
        QByteArray data_2501800 = readMemory(0x2501800, 0x100);
        Anytone::Memory::aprs_settings->decode_D878UVII(data_2501000, data_2501800);
    }

    if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103) {
        QByteArray data_3501000 = readMemory(0x3501000, 0x260);
        QByteArray data_3501800 = readMemory(0x3501300, 0x100);
        Anytone::Memory::aprs_settings->decode_D890UV(data_3501000, data_3501800);
    }
}
void Device::readArc4EncryptionKeys()
{
    // TODO: Implement for D168UV
    constexpr int kArc4SetBytes = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->Arc4Set, kArc4SetBytes);
    if (!is_alive) return;

    // Build enabled key IDs from bitmap
    std::vector<int> keyIds;
    keyIds.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                keyIds.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base = map->Arc4Data;

    for (size_t i = 0; i < keyIds.size(); ++i) {
        if (!is_alive) return;

        emit update2(static_cast<int>(i),
                     static_cast<int>(keyIds.size()),
                     "Reading ARC4 Code Data");

        const int keyId = keyIds[i];
        const int addr  = base + (keyId * map->Arc4DataOffset);

        if (keyId < 0 || keyId >= static_cast<int>(Anytone::Memory::arc4_encryption_keys.size()))
            continue;

        auto* key = Anytone::Memory::arc4_encryption_keys.at(keyId);
        if (!key)
            continue;

        const QByteArray keyData = readMemory(addr, map->Arc4DataLength);
        if (!is_alive) return;

        key->decode(keyData);
    }
}
void Device::readAutoRepeaterFrequencyData()
{
    // TODO: Implement for D168UV
    constexpr int kEntryCount   = 250;
    constexpr int kEntryBytes   = 4;
    constexpr int kReadBytes    = 0x3F0;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray data = readMemory(map->AutoRepeaterData, kReadBytes);
    if (!is_alive) return;

    const int outCount = std::min(kEntryCount,
                                  static_cast<int>(Anytone::Memory::ar_offset_frequencies.size()));
    const int maxEntriesInBuffer = data.size() / kEntryBytes;
    const int count = std::min(outCount, maxEntriesInBuffer);

    for (int i = 0; i < count; ++i) {
        auto* entry = Anytone::Memory::ar_offset_frequencies.at(i);
        if (!entry) continue;

        entry->frequency = Int::fromBytes(data.mid(i * kEntryBytes, kEntryBytes));
    }
}
void Device::readChannelData()
{
    // TODO: Implement for D168UV
    emit update2(0, 0, "Reading Channel Data");

    constexpr int kChannelSetBytes   = 0x200;
    constexpr int kChunkBytes        = 0x40;
    constexpr int kPrimaryBytes      = kChunkBytes;
    constexpr int kSecondaryBytes    = kChunkBytes;
    constexpr int kCombinedBytes     = kPrimaryBytes + kSecondaryBytes;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray channelSetData = readMemory(map->ChannelSet, kChannelSetBytes);
    if (!is_alive) {
        emit finished(DeviceStatus::STATUS_COM_ERROR);
        return;
    }

    // Build enabled channel IDs from bitmap
    std::vector<int> channelIds;
    channelIds.reserve(channelSetData.size() * 2);

    for (int byteIndex = 0; byteIndex < channelSetData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(channelSetData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                channelIds.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base              = map->ChannelData;
    const int blockSize         = map->ChannelDataBlockSize;       // channels per block
    const int entryStride       = map->ChannelDataOffset;          // bytes per channel entry in block
    const int blockStride       = map->ChannelDataBlockOffset;     // bytes between blocks
    const int secondaryOffset   = map->ChannelDataSecondaryOffset; // bytes from primary to secondary

    const int channelCount = static_cast<int>(Anytone::Memory::channels.size());

    for (size_t i = 0; i < channelIds.size(); ++i) {
        if (!is_alive) {
            emit finished(DeviceStatus::STATUS_COM_ERROR);
            return;
        }

        emit update2(static_cast<int>(i),
                     static_cast<int>(channelIds.size()),
                     "Reading Channel Data");

        const int idx = channelIds[i];
        if (idx < 0 || idx >= channelCount)
            continue;

        const int blockIndex   = idx / blockSize;
        const int indexInBlock = idx - (blockIndex * blockSize);

        const int primaryAddr =
            base + (blockIndex * blockStride) + (indexInBlock * entryStride);

        const int secondaryAddr = primaryAddr + secondaryOffset;

        QByteArray data;
        data.reserve(kCombinedBytes);

        data.append(readMemory(primaryAddr,  kPrimaryBytes));
        data.append(readMemory(secondaryAddr, kSecondaryBytes));

        if (!is_alive) {
            emit finished(DeviceStatus::STATUS_COM_ERROR);
            return;
        }

        Anytone::Channel* channel = Anytone::Memory::channels.at(idx);
        if (!channel)
            continue;

        channel->decode(data);
    }
}
void Device::readDigitalContactWhitelist(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103){
        qDebug() << "Skipping Digital Contact Whitelist";
        return;
    }

    emit update2(0, 0, "Reading Digital Contact Whitelist");

    bool reading = true;
    int count = 0;
    do {
        QByteArray data = readMemory(0x4c82000 + (count * 0x10), 0x10);
        if (!is_alive) return;
        if(data.mid(0x0, 0x8) != QByteArray(0x8, 0xff)){
            int id = Int::fromBytes(data.mid(0x4, 4));
            if(id < Anytone::Memory::digital_contact_whitelist.size()){
                Anytone::TalkgroupWhitelist *dc = Anytone::Memory::digital_contact_whitelist.at(id);
                int dmr_id_b = Int::fromBytes(data.mid(0x0, 4));
                dc->dmr_id = Int::toBytes(dmr_id_b >> 1, 4, Endian::Big).toHex().toInt();
                dc->call_type = dmr_id_b & 0x1;
            }
        }

        if(data.mid(0x8, 0x8) != QByteArray(0x8, 0xff)) {
            int id = Int::fromBytes(data.mid(0xc, 4));
            if(id < Anytone::Memory::digital_contact_whitelist.size()){
                Anytone::TalkgroupWhitelist *dc = Anytone::Memory::digital_contact_whitelist.at(id);
                int dmr_id_b = Int::fromBytes(data.mid(0x0, 4));
                dc->dmr_id = Int::toBytes(dmr_id_b >> 1, 4, Endian::Big).toHex().toInt();
                dc->call_type = dmr_id_b & 0x1;
            }
        }else{
            reading = false;
        }
        count++;

    } while (reading && count < 10);
}
void Device::readEncryptionKeys(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    QByteArray id_data = readMemory(map->EncryptionCodeId, 0x40);
    QByteArray key_data = readMemory(map->EncryptionCodeKey, 0x40);
    for (int i = 0; i < 32; ++i) { 
        emit update2(i, 32, "Reading Encryption Code Data");
        Anytone::EncryptionCode *key = Anytone::Memory::encryption_keys.at(i);
        key->id = QString(id_data.mid(i*2, 2).toHex());
        key->key = QString(key_data.mid(i*2, 2).toHex());
    }
}
void Device::readFmData()
{
    // TODO: Implement for D168UV
    using Anytone::Memory;

    if (!is_alive) return;

    if (Memory::radio_model == Anytone::RadioModel::D878UVII_FW400) {
        // Layout for D878UVII FW400
        constexpr int kMetaAddr         = 0x2480200;
        constexpr int kMetaLen          = 0x30;
        constexpr int kFreqTableAddr    = 0x2480000;
        constexpr int kFreqTableLen     = 0x190;

        constexpr int kHomeFreqOff      = 0x00; // 4 bytes
        constexpr int kActiveMaskBase   = 0x10; // 16 bytes
        constexpr int kScanMaskBase     = 0x20; // 16 bytes

        const QByteArray meta   = readMemory(kMetaAddr, kMetaLen);
        const QByteArray table  = readMemory(kFreqTableAddr, kFreqTableLen);
        if (!is_alive) return;

        // Get VFO Frequency
        if (Memory::fm_channels.size() > 100 && Memory::fm_channels.at(100)) {
            Memory::fm_channels.at(100)->frequency = meta.mid(kHomeFreqOff, 0x4).toHex().toInt();
        }

        // Get Frequencies
        for (int byteIdx = 0; byteIdx < 16; ++byteIdx) {
            emit update2(byteIdx, 16, "Reading FM Data");

            const quint8 activeByte = static_cast<quint8>(meta.at(kActiveMaskBase + byteIdx));
            const quint8 scanByte   = static_cast<quint8>(meta.at(kScanMaskBase + byteIdx));

            for (int bit = 0; bit < 8; ++bit) {
                const int fmIndex = byteIdx * 8 + bit;
                if (fmIndex < 0 || fmIndex >= static_cast<int>(Memory::fm_channels.size()))
                    continue;

                if (!Bit::test(activeByte, bit))
                    continue;

                auto* fm = Memory::fm_channels.at(fmIndex);
                if (!fm) continue;

                fm->scan_add = Bit::test(scanByte, bit);

                // 4 bytes per entry
                fm->frequency = table.mid(fmIndex * 4, 0x4).toHex().toInt();
            }
        }

        return;
    }

    if (Memory::radio_model == Anytone::RadioModel::D890UV_FW103) {
        // Layout for D890UV FW103
        constexpr int kMetaAddr           = 0x3402000;
        constexpr int kMetaLen            = 0x60;

        constexpr int kActiveMaskBase     = 0x40; // 16 bytes
        constexpr int kScanMaskBase       = 0x50; // 16 bytes

        constexpr int kEntryAddrBase      = 0x3400000;
        constexpr int kEntryLen           = 0x40; // per-channel blob?
        constexpr int kEntryFreqOff       = 0x00; // 4 bytes
        constexpr int kEntryNameOff       = 0x04;
        constexpr int kEntryNameLen       = 0x20;

        const QByteArray meta = readMemory(kMetaAddr, kMetaLen);
        if (!is_alive) return;

        // Get VFO Channel
        if (Memory::fm_channels.size() > 100 && Memory::fm_channels.at(100)) {
            auto* home = Memory::fm_channels.at(100);
            home->frequency = meta.mid(kEntryFreqOff, 0x4).toHex().toInt();
            if(home->frequency < 0xffffffff)
                home->name = readFixedStringUtf8(meta, kEntryNameOff, kEntryNameLen);
        }

        for (int byteIdx = 0; byteIdx < 16; ++byteIdx) {
            emit update2(byteIdx, 16, "Reading FM Data");

            const quint8 activeByte = static_cast<quint8>(meta.at(kActiveMaskBase + byteIdx));
            const quint8 scanByte   = static_cast<quint8>(meta.at(kScanMaskBase + byteIdx));

            for (int bit = 0; bit < 8; ++bit) {
                const int fmIndex = byteIdx * 8 + bit;
                if (fmIndex < 0 || fmIndex >= static_cast<int>(Memory::fm_channels.size()))
                    continue;

                if (!Bit::test(activeByte, bit))
                    continue;

                auto* fm = Memory::fm_channels.at(fmIndex);
                if (!fm) continue;

                fm->scan_add = Bit::test(scanByte, bit);
                
                const int entryAddr = kEntryAddrBase + (fmIndex * kEntryLen);

                const QByteArray entry = readMemory(entryAddr, kEntryLen);
                if (!is_alive) return;

                fm->frequency = entry.mid(kEntryFreqOff, 0x4).toHex().toInt();
                fm->name      = readFixedStringUtf8(entry, kEntryNameOff, kEntryNameLen);
            }
        }

        return;
    }
}
void Device::readGpsRoamingData()
{
    // TODO: Implement for D168UV
    constexpr int kEntryCount      = 32;
    constexpr int kStrideBytes     = 0x20;
    constexpr int kEntryBytes      = 0x10;
    constexpr int kSecondHalfBias  = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray data = readMemory(map->GpsRoamingData, map->GpsRoamingDataLength);
    if (!is_alive) return;

    const int listCount = static_cast<int>(Anytone::Memory::gps_roaming_list.size());
    const int count = std::min(kEntryCount, listCount);

    for (int idx = 0; idx < count; ++idx) {
        if (!is_alive) return;

        emit update2(idx, kEntryCount, "Reading GPS Roaming Data");

        const int base = (idx % 16) * kStrideBytes;
        const int addr = base + ((idx >= 16) ? kSecondHalfBias : 0);

        if (addr < 0 || addr + kEntryBytes > data.size())
            continue;

        auto* entry = Anytone::Memory::gps_roaming_list.at(idx);
        if (!entry)
            continue;

        entry->decode(data.mid(addr, kEntryBytes));
    }
}
void Device::readHotKeySettings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV

    if(Anytone::Memory::radio_model != Anytone::RadioModel::D878UVII_FW400) {
        qDebug() << "Skipping HotKey Settings";
        return;
    }

    QByteArray state_info_set_data = readMemory(0x25c0b00, 0x10);
    QByteArray quick_call_data = readMemory(0x25c0000, 0x10);
    QByteArray hotkey_data = readMemory(0x25c0500, 0x360);

    std::vector<int> state_info_id_list;

    for (int i = 0; i < state_info_set_data.size(); ++i) { 
        unsigned char byte = state_info_set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            state_info_id_list.push_back((i*8) + j);
        }
    }

    Anytone::Hotkey *hotkey = Anytone::Memory::hotkey;

    for(int idx : state_info_id_list){
        hotkey->state_content_list[idx] = QString(readMemory(0x25c0000 + (idx * 0x20), 0x20));
    }
    
    for(int i = 0; i < hotkey->key_list.size(); i++){
        Anytone::HotkeyKey *key = hotkey->key_list.at(i);
        QByteArray data = hotkey_data.mid(0x30 * i, 0x30);
        key->mode = static_cast<uint8_t>(data.at(0));
        key->menu = static_cast<uint8_t>(data.at(1));
        key->call_type = static_cast<uint8_t>(data.at(2));
        key->digi_call_type = static_cast<uint8_t>(data.at(3));
        key->call_obj = Int::fromBytes(data.mid(0x4, 0x4));
        key->content = static_cast<uint8_t>(data.at(8));
    }

    hotkey->quick_call_list.at(0)->operation_type = static_cast<uint8_t>(quick_call_data.at(0));
    hotkey->quick_call_list.at(0)->call_id = static_cast<uint8_t>(quick_call_data.at(1));
    hotkey->quick_call_list.at(1)->operation_type = static_cast<uint8_t>(quick_call_data.at(2));
    hotkey->quick_call_list.at(1)->call_id = static_cast<uint8_t>(quick_call_data.at(3));
    hotkey->quick_call_list.at(2)->operation_type = static_cast<uint8_t>(quick_call_data.at(4));
    hotkey->quick_call_list.at(2)->call_id = static_cast<uint8_t>(quick_call_data.at(5));
    hotkey->quick_call_list.at(3)->operation_type = static_cast<uint8_t>(quick_call_data.at(6));
    hotkey->quick_call_list.at(3)->call_id = static_cast<uint8_t>(quick_call_data.at(7));
    
}
void Device::readMasterId(){
    // TODO: Implement for D168UV
    emit update2(0, 0, "Reading Master ID");

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    int dataOffset = map->MasterIdData;
    int dataLen = map->MasterIdDataLength;
    QByteArray master_radioid_data = readMemory(dataOffset, dataLen);
    Anytone::Memory::master_radio_id->decode(master_radioid_data);
}
void Device::readPrefabricatedSms()
{
    // TODO: Implement for D168UV
    constexpr int  kSetEntryBytes   = 0x10;
    constexpr int  kMaxFollow       = 100;
    constexpr quint8 kEnd           = 0xFF;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    // ---- Walk the linked list / chain to gather SMS indices
    std::vector<int> ids;
    ids.reserve(32);

    std::vector<bool> seen(256, false);

    quint8 current = 0;
    for (int hops = 0; hops <= kMaxFollow; ++hops) {
        if (!is_alive) return;

        const quint32 addr = static_cast<quint32>(map->PrefabSmsSet) + (static_cast<quint32>(current) * kSetEntryBytes);
        const QByteArray entry = readMemory(addr, kSetEntryBytes);
        if (!is_alive) return;

        if (entry.size() < 4) break; // defensive

        const quint8 next = static_cast<quint8>(entry.at(2));
        const quint8 id   = static_cast<quint8>(entry.at(3));

        if (id == kEnd) break;

        if (!seen[id]) {
            ids.push_back(id);
            seen[id] = true;
        } else {
            // cycle detected
            break;
        }

        if (next == kEnd) break;
        current = next;
    }

    // ---- Read + decode each SMS
    const int base        = map->PrefabSmsData;
    const int entryStride = map->PrefabSmsDataOffset;
    const int blockSize   = map->PrefabSmsDataBlockSize;     // bytes per block
    const int blockStride = map->PrefabSmsDataBlockOffset;   // bytes between blocks
    const int dataLen     = map->PrefabSmsDataLength;

    const int listSize = static_cast<int>(Anytone::Memory::prefabricated_sms_list.size());
    const int total    = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Prefabricated SMS");

        const int idx = ids[i];
        if (idx < 0 || idx >= listSize) continue;

        auto* sms = Anytone::Memory::prefabricated_sms_list.at(idx);
        if (!sms) continue;

        // Compute offset in bytes from start of table for this entry
        const int byteOffset = idx * entryStride;

        // Map that into block-based addressing
        const int blockIndex   = byteOffset / blockSize;
        const int offsetInBlock = byteOffset % blockSize;

        const int addr = base + (blockIndex * blockStride) + offsetInBlock;

        const QByteArray smsData = readMemory(addr, dataLen);
        if (!is_alive) return;

        sms->decode(smsData);
    }
}
void Device::readRadioIdData()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes = 0x20;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->RadioIdSet, kSetBytes);
    if (!is_alive) return;

    // Build enabled IDs from bitmap
    std::vector<int> ids;
    ids.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                ids.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base    = map->RadioIdData;
    const int stride  = map->RadioIdDataOffset;
    const int dataLen = map->RadioIdDataLength;

    const int maxList = static_cast<int>(Anytone::Memory::radioids.size());
    const int total   = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Radio ID Data");

        const int idx = ids[i];
        if (idx < 0 || idx >= maxList)
            continue;

        auto* radioId = Anytone::Memory::radioids.at(idx);
        if (!radioId)
            continue;

        const int addr = base + (idx * stride);
        const QByteArray data = readMemory(addr, dataLen);
        if (!is_alive) return;

        radioId->decode(data);
    }
}
void Device::readReceiveGroups()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->ReceiveGroupSet, kSetBytes);
    if (!is_alive) return;

    // Build enabled IDs from bitmap
    std::vector<int> ids;
    ids.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                ids.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base    = map->ReceiveGroupData;
    const int stride  = map->ReceiveGroupDataOffset;
    const int dataLen = map->ReceiveGroupDataLength;

    const int listSize = static_cast<int>(Anytone::Memory::receive_group_call_lists.size());
    const int total    = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Receive Group Call List Data");

        const int idx = ids[i];
        if (idx < 0 || idx >= listSize)
            continue;

        auto* group = Anytone::Memory::receive_group_call_lists.at(idx);
        if (!group)
            continue;

        const int addr = base + (idx * stride);
        const QByteArray data = readMemory(addr, dataLen);
        if (!is_alive) return;

        group->decode(data);
    }
}
void Device::readRoamingChannelData()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes = 0x20;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->RoamingChannelSet, kSetBytes);
    if (!is_alive) return;

    // Build enabled IDs from bitmap
    std::vector<int> ids;
    ids.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                ids.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base    = map->RoamingChannelData;
    const int stride  = map->RoamingChannelDataOffset;
    const int dataLen = map->RoamingChannelDataLength;

    const int listSize = static_cast<int>(Anytone::Memory::roaming_channels.size());
    const int total    = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Roaming Channel Data");

        const int idx = ids[i];
        if (idx < 0 || idx >= listSize)
            continue;

        auto* roaming = Anytone::Memory::roaming_channels.at(idx);
        if (!roaming)
            continue;

        const int addr = base + (idx * stride);
        const QByteArray data = readMemory(addr, dataLen);
        if (!is_alive) return;

        roaming->decode(data);
    }
}
void Device::readRoamingZoneData()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->RoamingZoneSet, kSetBytes);
    if (!is_alive) return;

    // Build enabled IDs from bitmap
    std::vector<int> ids;
    ids.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                ids.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base    = map->RoamingZoneData;
    const int stride  = map->RoamingZoneDataOffset;
    const int dataLen = map->RoamingZoneDataLength;

    const int listSize = static_cast<int>(Anytone::Memory::roaming_zones.size());
    const int total    = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Roaming Zone Data");

        const int idx = ids[i];
        if (idx < 0 || idx >= listSize)
            continue;

        auto* zone = Anytone::Memory::roaming_zones.at(idx);
        if (!zone)
            continue;

        const int addr = base + (idx * stride);
        const QByteArray data = readMemory(addr, dataLen);
        if (!is_alive) return;

        zone->decode(data);
    }
}
void Device::readScanListData()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes = 0x20;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->ScanListSet, kSetBytes);
    if (!is_alive) return;

    // Build enabled IDs from bitmap
    std::vector<int> ids;
    ids.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                ids.push_back(byteIndex * 8 + bit);
            }
        }
    }

    const int base    = map->ScanListData;
    const int stride  = map->ScanListDataOffset;
    const int dataLen = map->ScanListDataLength;

    const int listSize = static_cast<int>(Anytone::Memory::scanlists.size());
    const int total    = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Scan List Data");

        const int idx = ids[i];
        if (idx < 0 || idx >= listSize)
            continue;

        auto* scanList = Anytone::Memory::scanlists.at(idx);
        if (!scanList)
            continue;

        const int addr = base + (idx * stride);
        const QByteArray data = readMemory(addr, dataLen);
        if (!is_alive) return;

        scanList->decode(data);
    }
}
void Device::readSettings()
{
    // TODO: Implement for D168UV
    emit update2(0, 0, "Reading Settings Data");

    const auto model = Anytone::Memory::radio_model;

    if (model == Anytone::RadioModel::D878UVII_FW400) {
        // --- D878UVII FW400 blocks
        constexpr quint32 kA_2500000 = 0x2500000; constexpr int kL_2500000 = 0xF0;
        constexpr quint32 kA_2500600 = 0x2500600; constexpr int kL_2500600 = 0x30;
        constexpr quint32 kA_2501280 = 0x2501280; constexpr int kL_2501280 = 0x20;
        constexpr quint32 kA_2501400 = 0x2501400; constexpr int kL_2501400 = 0x100;
        constexpr quint32 kA_24C1400 = 0x24C1400; constexpr int kL_24C1400 = 0x20;
        constexpr quint32 kA_24C1440 = 0x24C1440; constexpr int kL_24C1440 = 0x30;

        const QByteArray d2500000 = readMemory(kA_2500000, kL_2500000);
        const QByteArray d2500600 = readMemory(kA_2500600, kL_2500600);
        const QByteArray d2501280 = readMemory(kA_2501280, kL_2501280);
        const QByteArray d2501400 = readMemory(kA_2501400, kL_2501400);
        const QByteArray d24c1400 = readMemory(kA_24C1400, kL_24C1400);
        const QByteArray d24c1440 = readMemory(kA_24C1440, kL_24C1440);

        if (!is_alive) return;

        if (Anytone::Memory::optional_settings)
            Anytone::Memory::optional_settings->decode_D878UVII(d2500000, d2500600, d2501280, d2501400);

        if (Anytone::Memory::alarm_settings)
            Anytone::Memory::alarm_settings->decode_D878UVII(d2500000, d24c1400, d24c1440);

        // Defensive bounds checks before indexing
        if (Anytone::Memory::dtmf_settings && d2500000.size() > 0x23)
            Anytone::Memory::dtmf_settings->tx_time = static_cast<uint8_t>(d2500000.at(0x23));

        if (Anytone::Memory::talk_alias_settings && d2501400.size() > 0x1e)
            Anytone::Memory::talk_alias_settings->display_priority = static_cast<uint8_t>(d2501400.at(0x1e));
            Anytone::Memory::talk_alias_settings->data_format = static_cast<uint8_t>(d2501400.at(0x1f));

        return;
    }

    if (model == Anytone::RadioModel::D890UV_FW103) {
        // --- D890UV FW103 blocks
        const QByteArray d3482e00 = readMemory(0x3482e00, 0x10);
        const QByteArray d3483000 = readMemory(0x3483000, 0x30);
        const QByteArray d3500000 = readMemory(0x3500000, 0x200);
        const QByteArray d3500900 = readMemory(0x3500900, 0x60);
        const QByteArray d3501280 = readMemory(0x3501280, 0x30);

        if (!is_alive) return;

        if (Anytone::Memory::optional_settings)
            Anytone::Memory::optional_settings->decode_D890UV(d3500000, d3500900, d3501280);

        if (Anytone::Memory::alarm_settings)
            Anytone::Memory::alarm_settings->decode_D890UV(d3483000, d3482e00, d3500000);

        if (Anytone::Memory::talk_alias_settings && d3500000.size() > 0xee)
            Anytone::Memory::talk_alias_settings->display_priority = static_cast<uint8_t>(d3500000.at(0xed));
            Anytone::Memory::talk_alias_settings->data_format = static_cast<uint8_t>(d3500000.at(0xee));

        return;
    }
}
void Device::readTalkgroupData()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes = 0x4F0;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const QByteArray setData = readMemory(map->TalkgroupSet, kSetBytes);
    if (!is_alive) return;

    // NOTE: Inverted logic preserved:
    // if the bit is NOT set, include the index.
    std::vector<int> ids;
    ids.reserve(setData.size() * 2);

    for (int byteIndex = 0; byteIndex < setData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(setData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit))  // bit set => skip
                continue;

            ids.push_back(byteIndex * 8 + bit);
        }
    }

    const int base    = map->TalkgroupData;
    const int stride  = map->TalkgroupDataOffset;
    const int dataLen = map->TalkgroupDataLength;

    const int listSize = static_cast<int>(Anytone::Memory::talkgroups.size());
    const int total    = static_cast<int>(ids.size());

    for (int i = 0; i < total; ++i) {
        if (!is_alive) return;

        emit update2(i, total, "Reading Talkgroup Data");

        const int idx = ids[i];
        if (idx < 0 || idx >= listSize)
            continue;

        auto* tg = Anytone::Memory::talkgroups.at(idx);
        if (!tg)
            continue;

        const int addr = base + (idx * stride);
        const QByteArray data = readMemory(addr, dataLen);
        if (!is_alive) return;

        tg->decode(data);
    }
}
void Device::readTalkgroupWhitelist(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103){
        qDebug() << "Skipping Talkgroup Whitelist";
        return;
    }

    emit update2(0, 0, "Reading Talkgroup Whitelist");

    bool reading = true;
    int count = 0;
    do {
        QByteArray data = readMemory(0x4c80000 + (count * 0x10), 0x10);
        if (!is_alive) return;
        if(data.mid(0x0, 0x8) != QByteArray(0x8, 0xff)){
            int id = Int::fromBytes(data.mid(0x4, 4));
            if(id < Anytone::Memory::talkgroup_whitelist.size()){
                Anytone::TalkgroupWhitelist *tg = Anytone::Memory::talkgroup_whitelist.at(id);
                int dmr_id_b = Int::fromBytes(data.mid(0x0, 4));
                tg->dmr_id = Int::toBytes(dmr_id_b >> 1, 4, Endian::Big).toHex().toInt();
                tg->call_type = dmr_id_b & 0x1;
            }
        }

        if(data.mid(0x8, 0x8) != QByteArray(0x8, 0xff)) {
            int id = Int::fromBytes(data.mid(0xc, 4));
            if(id < Anytone::Memory::talkgroup_whitelist.size()){
                Anytone::TalkgroupWhitelist *tg = Anytone::Memory::talkgroup_whitelist.at(id);
                int dmr_id_b = Int::fromBytes(data.mid(0x0, 4));
                tg->dmr_id = Int::toBytes(dmr_id_b >> 1, 4, Endian::Big).toHex().toInt();
                tg->call_type = dmr_id_b & 0x1;
            }
        }else{
            reading = false;
        }
        count++;

    } while (reading && count < 10);
}
void Device::readToneSettings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV

    if(Anytone::Memory::radio_model != Anytone::RadioModel::D878UVII_FW400) {
        qDebug() << "Skipping Tone Settings";
        return;
    }

    QByteArray data_24c1000 = readMemory(0x24c1000, 0xd0);
    QByteArray data_2500500 = readMemory(0x2500500, 0x100);
    
    
    Anytone::Memory::dtmf_settings->decode(data_24c1000, data_2500500);
    Anytone::Memory::tone5_settings->decode(data_24c1000);
}
void Device::readTone2Settings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV

    if(Anytone::Memory::radio_model != Anytone::RadioModel::D878UVII_FW400) {
        qDebug() << "Skipping 2Tone Settings";
        return;
    }

    QByteArray data_24c1290 = readMemory(0x24c1290, 0x10);
    QByteArray data_24c1100 = readMemory(0x24c1100, 0x180);
    QByteArray data_24c2400 = readMemory(0x24c2400, 0x100);
    QByteArray data_24c2600 = readMemory(0x24c2600, 0x10); // Tone2 Decode set list
    QByteArray data_24c1280 = readMemory(0x24c1280, 0x10); // Tone2 Encode set list

    Anytone::Memory::tone2_settings->decode(data_24c1290);
    std::vector<int> tone2_decode_id_list;
    for (int i = 0; i < data_24c2600.size(); ++i) { 
        unsigned char byte = data_24c2600.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            tone2_decode_id_list.push_back((i*8) + j);
        }
    }
    for(int i = 0; i < tone2_decode_id_list.size(); i++){
        int idx = tone2_decode_id_list.at(i);
        Anytone::Tone2DecodeItem *item = Anytone::Memory::tone2_settings->decode_list.at(idx);
        item->decode(data_24c2400.mid(idx*0x20, 0x20));
    }

    std::vector<int> tone2_encode_id_list;
    for (int i = 0; i < data_24c1280.size(); ++i) { 
        unsigned char byte = data_24c1280.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            tone2_decode_id_list.push_back((i*8) + j);
        }
    }
    for(int i = 0; i < tone2_encode_id_list.size(); i++){
        int idx = tone2_encode_id_list.at(i);
        Anytone::Tone2EncodeItem *item = Anytone::Memory::tone2_settings->encode_list.at(idx);
        item->decode(data_24c1100.mid(idx*0x10, 0x10));
    }

}
void Device::readZoneData()
{
    // TODO: Implement for D168UV
    // --- Constants / types
    constexpr int kZoneSetBytes        = 0x20;
    constexpr int kZoneChannelsBytes   = 0x200;
    constexpr int kInvalidChannelIndex = 0xFFFF;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    const int zoneNameBase      = map->ZonesName;
    const int zoneChannelsBase  = map->ZoneChannels;
    const int zoneAChannelBase  = map->ZoneAChannel;
    const int zoneBChannelBase  = map->ZoneBChannel;
    const int zoneHideBase      = map->ZoneHide;

    // --- Read blocks (batch reads where you already do)
    const QByteArray zoneSetData   = readMemory(map->ZoneSet, kZoneSetBytes);
    const QByteArray aChannelData  = readMemory(zoneAChannelBase, kZoneChannelsBytes);
    const QByteArray bChannelData  = readMemory(zoneBChannelBase, kZoneChannelsBytes);
    const QByteArray hideData      = readMemory(zoneHideBase, kZoneSetBytes);

    if (!is_alive) return;

    // --- Build list of enabled zone IDs from bitmap
    std::vector<int> zoneIds;
    zoneIds.reserve(zoneSetData.size() * 2); // rough reserve; cheap improvement

    for (int byteIndex = 0; byteIndex < zoneSetData.size(); ++byteIndex) {
        const quint8 bits = static_cast<quint8>(zoneSetData.at(byteIndex));
        for (int bit = 0; bit < 8; ++bit) {
            if (Bit::test(bits, bit)) {
                zoneIds.push_back(byteIndex * 8 + bit);
            }
        }
    }

    // --- Iterate zones
    for (size_t i = 0; i < zoneIds.size(); ++i) {
        if (!is_alive) return;

        emit update2(static_cast<int>(i),
                     static_cast<int>(zoneIds.size()),
                     "Reading Zone Data");

        const int idx = zoneIds[i];

        if (idx < 0 || idx >= static_cast<int>(Anytone::Memory::zones.size()))
            continue;

        Anytone::Zone* zone = Anytone::Memory::zones.at(idx);
        if (!zone)
            continue;

        zone->temp_member_channel_idxs.clear();

        // --- Name (fixed-length, null-terminated)
        {
            const int addr = zoneNameBase + (idx * map->ZoneDataOffset);
            const QByteArray nameBytes = readMemory(addr, map->ZoneDataLength);
            if (!is_alive) return;

            zone->name = QString(nameBytes).remove(QChar('\0'));
        }

        // --- Channels list (0x200 bytes, 16-bit indices)
        {
            const int addr = zoneChannelsBase + (idx * kZoneChannelsBytes);
            const QByteArray chData = readMemory(addr, kZoneChannelsBytes);
            if (!is_alive) return;

            for (int off = 0; off + 1 < chData.size(); off += 2) {
                const int chIdx = Int::fromBytes(chData.mid(off, 2));
                if (chIdx != kInvalidChannelIndex) {
                    zone->temp_member_channel_idxs.push_back(chIdx);
                }
            }
        }

        // --- A/B channel indices (16-bit each at idx*2)
        zone->a_channel_idx = Int::fromBytes(aChannelData.mid(idx * 2, 2));
        zone->b_channel_idx = Int::fromBytes(bChannelData.mid(idx * 2, 2));

        // --- Hide bitmap
        const int hideByteIndex = idx / 8;
        const int hideBitIndex  = idx % 8;
        if (hideByteIndex >= 0 && hideByteIndex < hideData.size()) {
            zone->hide = Bit::test(static_cast<quint8>(hideData.at(hideByteIndex)), hideBitIndex);
        } else {
            zone->hide = false;
        }
    }
}

// Write Other Data
void Device::writeOtherData(){
    writeChannelData();
    writeZoneData();
    writeTalkgroupData();
    writeRadioIdData();
    writeScanListData();
    writeFMChannelData();
    writeGpsRoamingData();
    writeAutoRepeaterFrequencyData();
    writeRoamingChannelData();
    writeRoamingZoneData();
    writeSettingsData();
    writeMasterRadioIdData();
    writePrefabSms();
    writeAesKeys();
    writeArc4Keys();
    writeEncryptionKeys();
    writeToneSettings();
    writeHotKeySettings();
    writeReceiveGroups();
    writeAnalogAddress();
    writeAmAir();
    writeAmZones();
    writeTalkgroupWhitelist();
    writeDigitalContactWhitelist();

    emit update1(0, 1, "Writing...");
    
    int idx = 0;
    for (auto const& [addr, data] : write_data) {
        emit update2(idx, write_data.size(), "Writing Data");
        if(is_alive && addr > 0) writeMemory(addr, data);
        idx += 1;
    }
}
void Device::writeAesKeys(){

    // TODO: Implement for D168UV

    if(verbose) qDebug() << "Writing AES Keys";
    constexpr int kAesSetBytes = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;


    int set_list_addr = map->AESSet;
    int data_addr = map->AESData;
    QByteArray set_list(kAesSetBytes, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::aes_encryption_keys.size(); i++){
        Anytone::AesEncryptionCode *key = Anytone::Memory::aes_encryption_keys.at(i);
        if(key->key.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * map->AESDataOffset)] = key->encode();
    }

    write_data[set_list_addr] = set_list;

}
void Device::writeAmAir(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103) {
        qDebug() << "Skipping AM Air";
        return;
    }

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    int base = map->AmAirData;
    int stride = map->AmAirDataStride;
    int len = map->AmAirDataLength;

    Anytone::AmAir *vfo_am = Anytone::Memory::am_air_list[256];
    write_data[map->AmAirVfo] = vfo_am->encode();

    QByteArray setList(0x20, 0);
    auto* bytes = reinterpret_cast<quint8*>(setList.data());
    for (int i = 0; i < Anytone::Memory::am_air_list.size(); ++i) {
        auto* am = Anytone::Memory::am_air_list.at(i);
        if (!am) continue;

        if (am->frequency <= 0)
            continue;

        const int byteIndex = i / 8;
        const int bitIndex  = i % 8;

        if (byteIndex >= 0 && byteIndex < setList.size()) {
            Bit::set(&bytes[byteIndex], bitIndex);
        } else {
            continue;
        }

        int addr = base + (i * stride);
        const QByteArray encoded = am->encode();
        write_data[addr] = encoded;
    }
}
void Device::writeAmZones(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103) {
        qDebug() << "Skipping AM Air";
        return;
    }

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    int base = map->AmZoneData;
    int stride = map->AmZoneDataStride;
    int len = map->AmZoneDataLength;

    QByteArray setList(0x10, 0);
    QByteArray aChannelData(0x10, 0);
    // QByteArray scanChannelData(0x10, 0);

    auto* bytes = reinterpret_cast<quint8*>(setList.data());
    for (int i = 0; i < Anytone::Memory::am_zones.size(); ++i) {
        auto* zone = Anytone::Memory::am_zones.at(i);
        if (!zone) continue;

        // Consider a channel "present" if it has an RX frequency
        if (zone->scan_channels.size() == 0 && zone->member_channels.size() == 0)
            continue;

        // --- Set bitmap
        const int byteIndex = i / 8;
        const int bitIndex  = i % 8;

        if (byteIndex >= 0 && byteIndex < setList.size()) {
            Bit::set(&bytes[byteIndex], bitIndex);
        } else {
            // Should never happen if kSetBytes matches channel capacity
            continue;
        }

        QByteArray scanChannelData(0x10, 0);
        auto* scan_bytes = reinterpret_cast<quint8*>(scanChannelData.data());
        for(auto *ch : zone->scan_channels){
            int ch_idx = zone->member_channels.indexOf(ch);
            const int scanByteIndex = ch_idx / 8;
            const int scanBitIndex  = ch_idx % 8;
            Bit::set(&scan_bytes[scanByteIndex], scanBitIndex);
        }

        aChannelData[i] = zone->member_channels.indexOf(zone->aChannel);
        int addr = base + (i * stride);
        write_data[addr] = zone->encode();
        write_data[map->AmZoneScan + (i * 0x10)] = scanChannelData;

    }

    write_data[map->AmZoneSet] = setList;
    write_data[map->AmZoneAChannel] = aChannelData;
    

}
void Device::writeAnalogAddress(){
    if(verbose) qDebug() << "Writing Analog Address Book";

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    QByteArray setListData(0x100, 0xff);
    QByteArray idListData(0x100, 0xff);

    
    int index = 0;
    int base = map->AnalogBookData;
    int stride = map->AnalogBookDataStride;
    QByteArray data;
    for(Anytone::AnalogAddress *address : Anytone::Memory::analog_addresses){
        if(address->number == 0) continue;
        data.append(address->encode());
        setListData[index] = 0;
        idListData[index] = index;
        index++;
    }

    if(data.size() % 16 != 0) data.append(QByteArray(16 - (data.size() % 16), 0xff));
    
    write_data[map->AnalogBookData] = data;
    write_data[map->AnalogBookSet] = setListData;
    write_data[map->AnalogBookId] = idListData;
}
void Device::writeAprsSettings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV
    
    if(verbose) qDebug() << "Writing APRS Settings";

    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400) {
        int data_2501000_addr = 0x2501000;
        int data_2501800_addr = 0x2501800;

        QByteArray data_2501000(0x240, 0);
        QByteArray data_2501800(0x100, 0);
        
        Anytone::Memory::aprs_settings->encode_D878UVII(data_2501000, data_2501800);

        write_data[data_2501000_addr] = data_2501000;
        write_data[data_2501800_addr] = data_2501800;
    }

    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103) {
        int data_3501000_addr = 0x3501000;
        int data_3501300_addr = 0x3501300;

        QByteArray data_3501000(0x260, 0);
        QByteArray data_3501300(0x100, 0);
        
        Anytone::Memory::aprs_settings->encode_D890UV(data_3501000, data_3501300);

        data_3501000.replace(0x100, 0x100, QByteArray(0x100, 0xff));

        write_data[data_3501000_addr] = data_3501000;
        write_data[data_3501300_addr] = data_3501300;
    }
}
void Device::writeArc4Keys(){

    // TODO: Implement for D168UV
    constexpr int kArc4SetBytes = 0x10;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing ARC4 Keys";

    int set_list_addr = map->Arc4Set;
    int data_addr = map->Arc4Data;
    QByteArray set_list(kArc4SetBytes, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::arc4_encryption_keys.size(); i++){
        Anytone::Arc4EncryptionCode *key = Anytone::Memory::arc4_encryption_keys.at(i);
        if(key->key.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * map->Arc4DataOffset)] = key->encode();
    }

    write_data[set_list_addr] = set_list;

}
void Device::writeAutoRepeaterFrequencyData(){
    // TODO: Implement for D168UV
    constexpr int kDataBytes    = 0x3F0;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Auto Repeater Data";
    
    QByteArray data(kDataBytes, 0);
    for(int i = 0; i < Anytone::Memory::ar_offset_frequencies.size(); i++){
        Anytone::AutoRepeaterOffsetFrequency *arf = Anytone::Memory::ar_offset_frequencies.at(i);
        int addr = i*4;
        data.replace(addr, 4, 
            Int::toBytes(arf->frequency, 4)
        );
    }
    write_data[map->AutoRepeaterData] = data;
}
void Device::writeChannelData()
{
    // TODO: Implement for D168UV
    constexpr int kSetBytes   = 0x200;
    constexpr int kChunkBytes = 0x40;
    constexpr int kTotalBytes = kChunkBytes * 2;

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Channels";

    // Cache map values used in the hot loop
    const int setAddr          = map->ChannelSet;
    const int base             = map->ChannelData;
    const int blockSize        = map->ChannelDataBlockSize;       // channels per block
    const int entryStride      = map->ChannelDataOffset;          // bytes per channel entry in block
    const int blockStride      = map->ChannelDataBlockOffset;     // bytes between blocks
    const int secondaryOffset  = map->ChannelDataSecondaryOffset; // primary->secondary offset

    QByteArray setList(kSetBytes, 0);
    auto* bytes = reinterpret_cast<quint8*>(setList.data());

    const int channelCount = static_cast<int>(Anytone::Memory::channels.size());

    for (int i = 0; i < channelCount; ++i) {
        auto* ch = Anytone::Memory::channels.at(i);
        if (!ch) continue;

        // Consider a channel "present" if it has an RX frequency
        if (ch->rx_frequency <= 0)
            continue;

        // --- Set bitmap
        const int byteIndex = i / 8;
        const int bitIndex  = i % 8;

        if (byteIndex >= 0 && byteIndex < setList.size()) {
            Bit::set(&bytes[byteIndex], bitIndex);
        } else {
            // Should never happen if kSetBytes matches channel capacity
            continue;
        }

        // --- Compute addresses
        const int blockIndex   = i / blockSize;
        const int indexInBlock = i - (blockIndex * blockSize);

        const int primaryAddr =
            base + (blockIndex * blockStride) + (indexInBlock * entryStride);

        const int secondaryAddr = primaryAddr + secondaryOffset;

        // --- Encode + split
        const QByteArray encoded = ch->encodeData();
        if (encoded.size() < kTotalBytes) {
            // Either skip or pad; skipping is safest unless you *require* writing partials
            continue;
        }

        write_data[primaryAddr]   = encoded.mid(0,          kChunkBytes);
        write_data[secondaryAddr] = encoded.mid(kChunkBytes, kChunkBytes);
    }

    // Finally, write the set bitmap
    write_data[setAddr] = setList;
}
void Device::writeDigitalContactWhitelist(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103){
        qDebug() << "Skipping Digital Contact Whitelist";
        return;
    }

    QVector<Anytone::TalkgroupWhitelist*> list = {};

    for(auto* tg : Anytone::Memory::digital_contact_whitelist){
        if(tg->dmr_id > 0){
            list.append(tg);
        }
    }

    int d_size = list.size() * 0x8;
    if(d_size % 16 != 0) d_size += 8;
    QByteArray data = QByteArray(d_size, 0xff);

    int index = 0;
    for(auto* tg : list){
        int offset = (index*8);
        data.replace(offset + 4, 4, Int::toBytes(index, 4));

        int dmr_id_b = Int::fromBytes(QByteArray::fromHex(QByteArray::number(tg->dmr_id)), Endian::Big);
        dmr_id_b = dmr_id_b << 1;
        if(tg->call_type > 0) dmr_id_b+=1;

        data.replace(offset, 4, Int::toBytes(dmr_id_b, 4));

        index++;
    }

    write_data[0x4c82000] = data;


}
void Device::writeEncryptionKeys(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Encryption Keys";

    int id_offset = map->EncryptionCodeId;
    int key_offset = map->EncryptionCodeKey;

    QByteArray id_data(0x40, 0);
    QByteArray key_data(0x40, 0);
    for (int i = 0; i < 32; ++i) {
        Anytone::EncryptionCode *key = Anytone::Memory::encryption_keys.at(i);
        id_data.replace(i*2, 2, 
            QByteArray::fromHex(key->id.rightJustified(4, '0').toUtf8())
        );
        key_data.replace(i*2, 2, 
            QByteArray::fromHex(key->key.rightJustified(4, '0').toUtf8())
        );
    }

    write_data[id_offset] = id_data;
    write_data[key_offset] = key_data;

}
void Device::writeFMChannelData(){
    // TODO: Implement for D168UV

    if(verbose) qDebug() << "Writing FM Channels";
    using Anytone::Memory;

    if (!is_alive) return;

    if (Memory::radio_model == Anytone::RadioModel::D878UVII_FW400) {
        constexpr int kMetaAddr         = 0x2480200;
        constexpr int kMetaLen          = 0x30;
        constexpr int kFreqTableAddr    = 0x2480000;
        constexpr int kFreqTableLen     = 0x190;

        constexpr int kActiveMaskBase   = 0x10; // 16 bytes
        constexpr int kScanMaskBase     = 0x20; // 16 bytes

        
        QByteArray fm_data(kMetaLen, 0);
        QByteArray fm_freq_data(kFreqTableLen, 0xff);
        auto* fm_data_bytes = reinterpret_cast<std::uint8_t*>(fm_data.data());

        for(int i=0; i < Anytone::Memory::fm_channels.size() - 1; i++){
            Anytone::FM *fm = Anytone::Memory::fm_channels.at(i);
            int current_byte_idx = int((i - (i % 8))/8);
            if(fm->frequency > 0) Bit::set(&fm_data_bytes[kActiveMaskBase + current_byte_idx], i%8);
            if(fm->frequency > 0 && fm->scan_add) Bit::set(&fm_data_bytes[kScanMaskBase + current_byte_idx], i%8);

            fm_freq_data.replace((i * 4), 4, 
                QByteArray::fromHex(QString::number(fm->frequency).rightJustified(8, '0').toUtf8())
            );
        }

        for(int i = 0; i < fm_freq_data.size(); i+=0x10){
            QByteArray lb = fm_freq_data.mid(i, 16);
            if(lb == QByteArray(0x10, 0)){
                fm_freq_data.replace(i, 16, 
                    QByteArray(16, 0xff)
                );
            }
        }

        Anytone::FM *vfo = Anytone::Memory::fm_channels.at(Anytone::Memory::fm_channels.size()-1);
        fm_data.replace(0, 4, 
            QByteArray::fromHex(QString::number(vfo->frequency).rightJustified(8, '0').toUtf8())
        );

        write_data[kMetaAddr] = fm_data;
        write_data[kFreqTableAddr] = fm_freq_data;
    }

    if (Memory::radio_model == Anytone::RadioModel::D890UV_FW103) {
        constexpr int kMetaAddr         = 0x3402000;
        constexpr int kMetaLen          = 0x60;
        constexpr int kFreqTableAddr    = 0x3400000;
        constexpr int kFreqTableLen     = 0x1900;

        constexpr int kActiveMaskBase   = 0x40; // 16 bytes
        constexpr int kScanMaskBase     = 0x50; // 16 bytes

        
        QByteArray fm_data(kMetaLen, 0);
        QByteArray fm_freq_data(kFreqTableLen, 0xff);
        auto* fm_data_bytes = reinterpret_cast<std::uint8_t*>(fm_data.data());

        for(int i=0; i < Anytone::Memory::fm_channels.size() - 1; i++){
            Anytone::FM *fm = Anytone::Memory::fm_channels.at(i);
            int current_byte_idx = int((i - (i % 8))/8);
            if(fm->frequency > 0) {
                Bit::set(&fm_data_bytes[kActiveMaskBase + current_byte_idx], i%8);
                if(fm->scan_add) Bit::set(&fm_data_bytes[kScanMaskBase + current_byte_idx], i%8);
                
                QByteArray kFmData(0x40, 0x0);
                kFmData.replace(0, 4, QByteArray::fromHex(QString::number(fm->frequency).rightJustified(8, '0').toUtf8()));
                kFmData.replace(0x4, 0x20, Format::wideCharString(fm->name).leftJustified(0x20, '\0'));

                fm_freq_data.replace((i * 0x40), 0x40, kFmData);
            }
        }

        Anytone::FM *vfo = Anytone::Memory::fm_channels.at(Anytone::Memory::fm_channels.size()-1);
        if(vfo->frequency < 0xffffffff && vfo->frequency > 0){
            fm_data.replace(0, 4, 
                QByteArray::fromHex(QString::number(vfo->frequency).rightJustified(8, '0').toUtf8())
            );
            
            fm_data.replace(0x4, 0x20, Format::wideCharString(vfo->name).leftJustified(0x20, '\0'));
        }else{
            fm_data.replace(0, 0x40, QByteArray(0x40, 0xff));
        }

        write_data[kMetaAddr] = fm_data;
        write_data[kFreqTableAddr] = fm_freq_data;

    }
}
void Device::writeGpsRoamingData(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing GPS Roaming";
    for(int gps_idx = 0; gps_idx < 32; gps_idx++){
        int gps_addr = map->GpsRoamingData + ((gps_idx % 16) * 0x20);
        if(gps_idx >= 16) gps_addr += 0x10;
        write_data[gps_addr] = Anytone::Memory::gps_roaming_list.at(gps_idx)->encode();
    }
}
void Device::writeHotKeySettings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D878UVII_FW400) {
        qDebug() << "Skipping HotKey Settings";
        return;
    }
    if(verbose) qDebug() << "Writing HotKey Settings";
    QByteArray state_info_set_data = readMemory(0x10, 0);
    QByteArray quick_call_data = readMemory(0x10, 0);
    QByteArray hotkey_data = readMemory(0x360, 0);

    Anytone::Hotkey *hotkey = Anytone::Memory::hotkey;
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(state_info_set_data.data());
    for(int i = 0; i < hotkey->state_content_list.size(); i++){
        if(hotkey->state_content_list.at(i).isEmpty()) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[0x25c0000 + (i * 0x20)] = hotkey->state_content_list.at(i).leftJustified('\x00').toUtf8();
    }

    
    for(int i = 0; i < hotkey->key_list.size(); i++){
        Anytone::HotkeyKey *key = hotkey->key_list.at(i);
        QByteArray data(0x30, 0);
        data[0] = key->mode;
        data[1] = key->menu;
        data[2] = key->call_type;
        data[3] = key->digi_call_type;
        data.replace(0x4, 0x4, Int::toBytes(key->call_obj, 4));
        data[8] = key->content;

        hotkey_data.replace(0x30, 0x30, data);
    }


    quick_call_data[0] = hotkey->quick_call_list.at(0)->operation_type;
    quick_call_data[1] = hotkey->quick_call_list.at(0)->call_id;
    quick_call_data[2] = hotkey->quick_call_list.at(1)->operation_type;
    quick_call_data[3] = hotkey->quick_call_list.at(1)->call_id;
    quick_call_data[4] = hotkey->quick_call_list.at(2)->operation_type;
    quick_call_data[5] = hotkey->quick_call_list.at(2)->call_id;
    quick_call_data[6] = hotkey->quick_call_list.at(3)->operation_type;
    quick_call_data[7] = hotkey->quick_call_list.at(3)->call_id;

    write_data[0x25c0b00] = state_info_set_data;
    write_data[0x25c0000] = quick_call_data;
    write_data[0x25c0500] = hotkey_data;
}
void Device::writeMasterRadioIdData(){
    // TODO: Implement for D168UV
    
    const auto* map = Anytone::Memory::Map();
    if (!map) return;
    
    if(verbose) qDebug() << "Writing Master Radio ID";
    write_data[map->MasterIdData] = Anytone::Memory::master_radio_id->encodeData();
}
void Device::writePrefabSms(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Prefab SMS";
    
    int link_list_addr = map->PrefabSmsSet;
    int data_addr = map->PrefabSmsData;
    int data_stride = map->PrefabSmsDataOffset;
    int dataBlockLen = map->PrefabSmsDataBlockSize;
    int dataBlockStride = map->PrefabSmsDataBlockOffset;
    QByteArray link_list;
    std::vector<Anytone::PrefabricatedSms*> active_sms = {};

    for(Anytone::PrefabricatedSms *sms : active_sms){
        if(sms->text.size() > 0) active_sms.push_back(sms);
    }

    // Create Link List
    for(int i = 0; i < active_sms.size(); i++){
        QByteArray link_list_line(0x10, 0);

        link_list_line[0x3] = active_sms[i]->id;

        if(i < active_sms.size() - 1){
            link_list_line[0x2] = active_sms[i+1]->id;
        }else{
            link_list_line[0x2] = 0xff;
        }
        link_list.append(link_list_line);
    }
    
    for(int i = 0; i < active_sms.size(); i++){
        Anytone::PrefabricatedSms *sms = active_sms.at(i);
        int block = int(((i * data_stride) - i % dataBlockLen) / dataBlockLen);
        int addr = data_addr + (block * dataBlockStride) + ((i * data_stride) % dataBlockLen);
        QByteArray data = sms->encodeData();
        write_data[addr] = data;
    }
}
void Device::writeRadioIdData(){
    // TODO: Implement for D168UV
    
    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Radio IDs";

    int set_list_addr = map->RadioIdSet;
    QByteArray set_list(0x20, 0);
    int data_addr = map->RadioIdData;
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::radioids.size(); i++){
        Anytone::RadioId *rid = Anytone::Memory::radioids.at(i);
        if(rid->dmr_id == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * map->RadioIdDataOffset)] = rid->encode();
    }

    write_data[set_list_addr] = set_list;
}
void Device::writeReceiveGroups(){
     const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Radio IDs";

    int set_list_addr = map->ReceiveGroupSet;
    QByteArray set_list(0x10, 0);
    int data_addr = map->ReceiveGroupData;
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::receive_group_call_lists.size(); i++){
        Anytone::ReceiveGroup *rid = Anytone::Memory::receive_group_call_lists.at(i);
        if(rid->talkgroups.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * map->RadioIdDataOffset)] = rid->encode();
    }

    write_data[set_list_addr] = set_list;
    
}
void Device::writeRoamingChannelData(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Roaming Channels";

    int set_list_addr = map->RoamingChannelSet;
    int data_addr = map->RoamingChannelData;
    QByteArray set_list(0x20, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::roaming_channels.size(); i++){
        Anytone::RoamingChannel *rc = Anytone::Memory::roaming_channels.at(i);
        if(rc->rx_frequency == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * map->RoamingChannelDataOffset)] = rc->encode();
    }
    write_data[set_list_addr] = set_list;
}
void Device::writeRoamingZoneData(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;
    
    if(verbose) qDebug() << "Writing Roaming Zones";

    int set_list_addr = map->RoamingZoneSet;
    int data_addr = map->RoamingZoneData;
    QByteArray set_list(0x10, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    const int stride  = map->RoamingZoneDataOffset;
    // const int dataLen = map->RoamingZoneDataLength;

    for(int i=0; i < Anytone::Memory::roaming_zones.size(); i++){
        Anytone::RoamingZone *rz = Anytone::Memory::roaming_zones.at(i);
        if(rz->channels.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * stride)] = rz->encode();

    }
    write_data[set_list_addr] = set_list;
}
void Device::writeScanListData(){
    // TODO: Implement for D168UV

    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Scan Lists";
    int set_list_addr = map->ScanListSet;
    int data_addr = map->ScanListData;
    QByteArray set_list(0x20, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::scanlists.size(); i++){
        Anytone::ScanList *sl = Anytone::Memory::scanlists.at(i);
        if(sl->channels.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * map->ScanListDataOffset)] = sl->encode();
    }
    write_data[set_list_addr] = set_list;
}
void Device::writeSettingsData(){
    
    if(verbose) qDebug() << "Writing Settings";
    // TODO: Implement for D168UV
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D878UVII_FW400){
        int data_2500000_addr = 0x2500000;
        int data_2500600_addr = 0x2500600;
        int data_2501280_addr = 0x2501280;
        int data_2501400_addr = 0x2501400;
        int data_24c1400_addr = 0x24c1400;
        int data_24c1440_addr = 0x24c1440;

        QByteArray data_2500000(0xf0, 0);
        QByteArray data_2500600(0x30, 0);
        QByteArray data_2501280(0x20, 0);
        QByteArray data_2501400(0x100, 0);
        QByteArray data_24c1400(0x20, 0);
        QByteArray data_24c1440(0x30, 0);

        if (Anytone::Memory::alarm_settings)
            Anytone::Memory::alarm_settings->encode_D878UVII(data_2500000, data_24c1400, data_24c1440);
        if (Anytone::Memory::optional_settings)
            Anytone::Memory::optional_settings->encode_D878UVII(data_2500000, data_2500600, data_2501280, data_2501400);

        data_2501400[0x6f] = Anytone::Memory::aprs_settings->fixed_location_beacon;

        data_2501400[0x1e] = Anytone::Memory::talk_alias_settings->display_priority;
        data_2501400[0x1f] = Anytone::Memory::talk_alias_settings->data_format;
        

        write_data[data_2500000_addr] = data_2500000;
        write_data[data_2500600_addr] = data_2500600;
        write_data[data_2501280_addr] = data_2501280;
        write_data[data_2501400_addr] = data_2501400;
        write_data[data_24c1400_addr] = data_24c1400;
        write_data[data_24c1440_addr] = data_24c1440;

        writeAprsSettings();
    }
    if(Anytone::Memory::radio_model == Anytone::RadioModel::D890UV_FW103){

        constexpr quint32 kA_3482e00 = 0x3482e00;
        constexpr quint32 kA_3483000 = 0x3483000;
        constexpr quint32 kA_3500000 = 0x3500000; constexpr int kL_3500000 = 0x200;
        constexpr quint32 kA_3500900 = 0x3500900; constexpr int kL_3500900 = 0x60;
        constexpr quint32 kA_3501280 = 0x3501280; constexpr int kL_3501280 = 0x30;

        QByteArray d3482e00 = QByteArray(0x10, 0);
        QByteArray d3483000 = QByteArray(0x30, 0);
        QByteArray d3500000 = QByteArray(kL_3500000, 0);
        QByteArray d3500900 = QByteArray(kL_3500900, 0);
        QByteArray d3501280 = QByteArray(kL_3501280, 0);

        if (!is_alive) return;

        // Alarm Settings
        if (Anytone::Memory::alarm_settings)
            Anytone::Memory::alarm_settings->encode_D890UV(d3483000, d3482e00, d3500000);

        // Optional Settings
        if (Anytone::Memory::optional_settings)
            Anytone::Memory::optional_settings->encode_D890UV(d3500000, d3500900, d3501280);

        // APRS Settings



        // Air Alias Settings
        if (Anytone::Memory::talk_alias_settings){
            d3500000[0xed] = Anytone::Memory::talk_alias_settings->display_priority;
            d3500000[0xee] = Anytone::Memory::talk_alias_settings->data_format;
        }

        write_data[kA_3482e00] = d3482e00;
        write_data[kA_3483000] = d3483000;
        write_data[kA_3500000] = d3500000;
        write_data[kA_3500900] = d3500900;
        write_data[kA_3501280] = d3501280;

        writeAprsSettings();
    }
}
void Device::writeTalkgroupData(){
    // TODO: Implement for D168UV
    const auto* map = Anytone::Memory::Map();
    if(!map) return;

    if(verbose) qDebug() << "Writing Talkgroups";

    int tg_set_list_addr = map->TalkgroupSet;
    int tg_data_list_addr = map->TalkgroupData;
    int tg_order_data_addr = map->TalkgroupOrder;
    QByteArray tg_set_list_data(0x4e3, 0xff);
    auto* tg_set_list_bytes = reinterpret_cast<std::uint8_t*>(tg_set_list_data.data());
    QByteArray tg_data;

    std::map<int, int> tg_order = {};

    for(int i=0; i < Anytone::Memory::talkgroups.size(); i++){
        Anytone::Talkgroup *tg = Anytone::Memory::talkgroups.at(i);
        int current_byte_idx = int((i - (i % 8))/8);
        if(tg->dmr_id > 0) {
            Bit::clear(&tg_set_list_bytes[current_byte_idx], i%8);
            tg_data += tg->encode();
            int ordered_dmr_id = tg->dmr_id;

            QByteArray dmr_bytes = QByteArray::fromHex(QString::number(tg->dmr_id).rightJustified(8, '0').toUtf8());
            int dmr_id_num = (Int::fromBytes(dmr_bytes, Endian::Big) << 1) + tg->call_type;
            tg_order[dmr_id_num] = tg->id;
        }
    }

    // Pad Talkgroup data
    tg_data = tg_data.leftJustified(tg_data.size() + 0x10 - (tg_data.size() % 0x10), '\0');
    tg_set_list_data = tg_set_list_data.leftJustified(0x4f0, '\0');

    // Talkgroup order data
    QByteArray tg_order_data;
    for (auto const& [tg_dmr_id, tg_id] : tg_order) {
        tg_order_data.append(Int::toBytes(tg_dmr_id, 4));
        tg_order_data.append(Int::toBytes(tg_id, 4));
    }
    // Pad Talkgroup Order data
    tg_order_data = tg_order_data.leftJustified(tg_order_data.size() + 0x10 - (tg_order_data.size() % 0x10), 0xff);

    write_data[tg_set_list_addr] = tg_set_list_data;
    write_data[tg_data_list_addr] = tg_data;
    write_data[tg_order_data_addr] = tg_order_data;
}
void Device::writeTalkgroupWhitelist(){
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D890UV_FW103){
        qDebug() << "Skipping Digital Contact Whitelist";
        return;
    }

    QVector<Anytone::TalkgroupWhitelist*> list = {};

    for(auto* tg : Anytone::Memory::talkgroup_whitelist){
        if(tg->dmr_id > 0){
            list.append(tg);
        }
    }

    int d_size = list.size() * 0x8;
    if(d_size % 16 != 0) d_size += 8;
    QByteArray data = QByteArray(d_size, 0xff);

    int index = 0;
    for(auto* tg : list){
        int offset = (index*8);
        data.replace(offset + 4, 4, Int::toBytes(index, 4));

        int dmr_id_b = Int::fromBytes(QByteArray::fromHex(QByteArray::number(tg->dmr_id)), Endian::Big);
        dmr_id_b = dmr_id_b << 1;
        if(tg->call_type > 0) dmr_id_b+=1;

        data.replace(offset, 4, Int::toBytes(dmr_id_b, 4));

        index++;
    }

    write_data[0x4c80000] = data;
}
void Device::writeToneSettings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D878UVII_FW400) {
        qDebug() << "Skipping Tone Settings";
        return;
    }
    if(verbose) qDebug() << "Writing Tone Settings";
    QByteArray data_24c1000(0xd0, 0);
    QByteArray data_2500500(0x100, 0xff);
    Anytone::Memory::dtmf_settings->encode(data_24c1000, data_2500500);
    Anytone::Memory::tone5_settings->encode(data_24c1000);

    write_data[0x24c1000] = data_24c1000;
    write_data[0x2500500] = data_2500500;

    writeTone2Settings();
}
void Device::writeTone2Settings(){
    // TODO: Implement for D890UV
    // TODO: Implement for D168UV
    if(Anytone::Memory::radio_model != Anytone::RadioModel::D878UVII_FW400) {
        qDebug() << "Skipping 2Tone Settings";
        return;
    }
    if(verbose) qDebug() << "Writing 2Tone Settings";
    QByteArray data_24c1290(0x10, 0);
    QByteArray data_24c1100(0x180, 0xff);
    QByteArray data_24c2400(0x100, 0xff);
    QByteArray tone2_encode_frequency_set_data = QByteArray(0x10, 0); //0x24c1280
    QByteArray tone2_decode_frequency_set_data = QByteArray(0x10, 0); //0x24c2600


    Anytone::Memory::tone2_settings->encode(data_24c1290);

    // 2Tone Encode Frequency Set List Data
    auto* tone2_encode_frequency_set_bytes = reinterpret_cast<std::uint8_t*>(tone2_encode_frequency_set_data.data());
    for(int i=0; i < Anytone::Memory::tone2_settings->encode_list.size(); i++){
        Anytone::Tone2EncodeItem *item = Anytone::Memory::tone2_settings->encode_list.at(i);
        if(item->tone_frequency_1 > 0) {
            int current_byte_idx = int((i - (i % 8))/8);
            Bit::set(&tone2_encode_frequency_set_bytes[current_byte_idx], i%8);
            data_24c2400.replace(i*0x20, 0x20, item->encode());
        }
    }

    // 2Tone Decode Frequency Set List Data
    auto* tone2_decode_frequency_set_bytes = reinterpret_cast<std::uint8_t*>(tone2_decode_frequency_set_data.data());
    for(int i=0; i < Anytone::Memory::tone2_settings->decode_list.size(); i++){
        Anytone::Tone2DecodeItem *item = Anytone::Memory::tone2_settings->decode_list.at(i);
        if(item->tone_frequency_1 > 0) {
            int current_byte_idx = int((i - (i % 8))/8);
            Bit::set(&tone2_decode_frequency_set_bytes[current_byte_idx], i%8);
            data_24c1100.replace(i*0x10, 0x10, item->encode());
        }
    }

    write_data[0x24c1280] = data_24c1290;
    write_data[0x24c1100] = data_24c1100;
    write_data[0x24c2400] = data_24c2400;

    write_data[0x24c1280] = tone2_encode_frequency_set_data;
    write_data[0x24c2600] = tone2_decode_frequency_set_data;
}
void Device::writeZoneData(){

    // TODO: Implement for D168UV
    const auto* map = Anytone::Memory::Map();
    if (!map) return;

    if(verbose) qDebug() << "Writing Zones";

    int zone_set_list_addr = map->ZoneSet; //0x20
    int zone_name_addr = map->ZonesName;
    int zone_channel_offset = map->ZoneChannels;
    int zone_a_channel_addr = map->ZoneAChannel;
    int zone_b_channel_addr = map->ZoneBChannel;
    int zone_hide_addr = map->ZoneHide;

    QByteArray zone_set_list_data = QByteArray(0x20, 0);
    QByteArray zone_name_data = QByteArray(0x1f40, 0xff);
    QByteArray zone_a_channel_data = QByteArray(0x200, 0);
    QByteArray zone_b_channel_data = QByteArray(0x200, 0);
    QByteArray zone_hide_data = QByteArray(0x20, 0);


    auto* zone_set_list_bytes = reinterpret_cast<std::uint8_t*>(zone_set_list_data.data());
    auto* zone_hide_bytes = reinterpret_cast<std::uint8_t*>(zone_hide_data.data());

    for(int i=0; i < Anytone::Memory::zones.size(); i++){
        Anytone::Zone *zone = Anytone::Memory::zones.at(i);
        int current_byte_idx = int((i - (i % 8))/8);
        if(zone->channels.size() == 0){
            zone_a_channel_data.replace(i*2, 2,
                Int::toBytes(0, 2)
            );
            zone_b_channel_data.replace(i*2, 2,
                Int::toBytes(1, 2)
            );
        }else{
            
            Bit::set(&zone_set_list_bytes[current_byte_idx], i%8);
            write_data[zone_name_addr + (i * map->ZoneDataOffset)] = Format::wideCharString(zone->name).leftJustified(map->ZoneDataLength, '\0');
            QByteArray zone_channel_data(0x200, 0xff);
            for(int ch_idx = 0; ch_idx < zone->channels.size(); ch_idx++){
                Anytone::Channel *ch = zone->channels.at(ch_idx);
                zone_channel_data.replace(ch_idx*2, 2,
                    Int::toBytes(ch->id, 2)
                );
            }

            write_data[zone_channel_offset + (i * 0x200)] = zone_channel_data;
            zone_a_channel_data.replace(i*2, 2,
                Int::toBytes(zone->a_channel_idx, 2)
            );
            zone_b_channel_data.replace(i*2, 2,
                Int::toBytes(zone->b_channel_idx, 2)
            );
        }
        if(zone->hide) Bit::set(&zone_hide_bytes[current_byte_idx], i%8);
    }

    write_data[zone_a_channel_addr] = zone_a_channel_data;
    write_data[zone_b_channel_addr] = zone_b_channel_data;
    write_data[zone_hide_addr] = zone_hide_data;
    write_data[zone_set_list_addr] = zone_set_list_data;
}
void Device::writeSatelliteData(){
    QVector<Anytone::Satellite*> sat_list = {};
    for(Anytone::Satellite *sat : Anytone::Memory::satellite_data_list){
        if(sat->write_enable == 1) sat_list.append(sat);
    }
    for(int i = 0; i < sat_list.size(); i++){
        emit update1(i, sat_list.size(), "");
        Anytone::Satellite *sat = sat_list.at(i);
        writeMemory(0x4a80000 + (i * 0x200), sat->encode());
    }
}

void SerialWorker::run(){
    if(comport.size() > 0){
        runSerial();
    }else if(bin_filepath.size() > 0){
        runVirtual();
    }else{
        emit finished(DeviceStatus::STATUS_COM_ERROR);
        qDebug() << "Invalid serial device configuration";
    }
}
void SerialWorker::runVirtual(){
    device = new VirtualDevice();
    device->image_data = image_data;
    device->read_write_options = rw_options;

    QObject::connect(device, &Device::finished, this, &SerialWorker::finished);
    QObject::connect(device, &Device::update1, this, &SerialWorker::update1);
    QObject::connect(device, &Device::update2, this, &SerialWorker::update2);

    if(device->connect(bin_filepath)){
        if(!is_write) {
            device->readRadioData();
        }else{
            device->writeRadioData();
            static_cast<VirtualDevice*>(device)->save("saved.bin");
        }
    }

    emit finished(DeviceStatus::STATUS_SUCCESS);
    emit imageDataReady(device->image_data);

    delete device;
    device = nullptr;
}
void SerialWorker::runSerial(){
    device = new SerialDevice();
    device->image_data = image_data;
    device->read_write_options = rw_options;

    QObject::connect(device, &Device::finished, this, &SerialWorker::finished);
    QObject::connect(device, &Device::update1, this, &SerialWorker::update1);
    QObject::connect(device, &Device::update2, this, &SerialWorker::update2);

    device->is_alive = false;

    while(!device->is_alive && connection_attempt < 5){
        connection_attempt++;
        if(device->connect(comport)){
            if(!is_write) {
                device->readRadioData();
            }else{
                device->writeRadioData();
            }
            if(device->is_alive) device->endProgMode();
        }
        if(!device->is_alive) QThread::msleep(1000);
    }

    if(device->is_alive){
        emit finished(DeviceStatus::STATUS_SUCCESS);
        emit imageDataReady(device->image_data);
    }else{
        emit finished(DeviceStatus::STATUS_COM_ERROR);
    }

    static_cast<SerialDevice*>(device)->port->close();

    delete device;
    device = nullptr;
}
void SerialWorker::done(){
    qDebug() << "ready read";
}