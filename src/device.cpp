#include "device.h"
#include "int.h"

QByteArray VirtualDevice::readMemoryAddress(int address, int length) {
    if(length % 16 != 0) qDebug() << "ERR: Memory Alignment" << QByteArray::number(address).toHex();
    return bin_data->mid(address, length);
}
void VirtualDevice::writeMemoryAddress(int address, QByteArray data) {
    if(data.size() % 16 != 0) qDebug() << "ERR: Memory Alignment" << QString::number(address, 16) << QString::number(data.size(), 16);
    bin_data->replace(address, data.size(), data);
}
void Device::readRadioData(){
    std::vector<QString> local_info = readDeviceInfo();

    if(local_info[0] == QString("ID878UV2") && local_info[1] == QString("V101")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) readOtherData();
        if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) !=  DeviceRWType::NONE) readDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) readBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) readBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) readBk2Image();
    }else if(local_info[0] == QString("ID890UV") && local_info[1] == QString("V100")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D890UV;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) readOtherData();
        // if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) !=  DeviceRWType::NONE) readDigitalContacts();
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
        Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII;
        if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) writeOtherData();
        if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) != DeviceRWType::NONE) writeDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) writeBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) writeBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) writeBk2Image();
    }else if(local_info[0] == QString("ID890UV") && local_info[1] == QString("V100")){
        Anytone::Memory::radio_model = Anytone::RadioModel::D890UV;
        // if((read_write_options & DeviceRWType::RADIO_DATA) != DeviceRWType::NONE) writeOtherData();
        // if((read_write_options & DeviceRWType::DIGITAL_CONTACTS) !=  DeviceRWType::NONE) writeDigitalContacts();
        if((read_write_options & DeviceRWType::BOOT_IMAGE) !=  DeviceRWType::NONE) writeBootImage();
        if((read_write_options & DeviceRWType::BK1_IMAGE) !=  DeviceRWType::NONE) writeBk1Image();
        if((read_write_options & DeviceRWType::BK2_IMAGE) !=  DeviceRWType::NONE) writeBk2Image();
    }else{
        qDebug() << local_info[0] << local_info[1];
        emit finished(DeviceStatus::STATUS_DEVICE_MISMATCH);
    }
}
QByteArray Device::readLocalInformation(){
    std::vector<QString> local_info = readDeviceInfo();
    if(local_info[0] == QString("ID878UV2") && local_info[1] == QString("V101")){
        return readMemory(Anytone::D878_MAP.LocalInfo, 0x100);
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
        return writeMemory(Anytone::D878_MAP.LocalInfo, data);
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
    int contact_count = Int::fromBytes(readMemory(0x4840000, 0x10).mid(0, 4));
    QByteArray contact_data;
    contact_data.reserve(0x80 * contact_count);

    int offset = 0;
    for(int i = 0; i < contact_count; i++){
        if(i % int(contact_count/100) == 0){
            emit update2(i, contact_count, "Reading Contacts");
        }

        if(contact_data.size() - offset < 0x80){
            contact_data.append(getDigitalContactDataBuffer(contact_data.size()));
        }
        Anytone::DigitalContact *dc = Anytone::Memory::digital_contacts.at(i);

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
}
QByteArray Device::getDigitalContactDataBuffer(int offset){
    QByteArray data;
    data.reserve(0x80);
    if(offset % 16 != 0){
        qDebug() << "ERR: Offset Alignment";
        return data;
    }

    for(int i = offset; i < offset + 0x80; i += 0x10){
        int addr_mod = i % 0x186a0;
        int block = int(((i - addr_mod) / 0x186a0));
        int addr = 0x5500000 + (block * 0x40000) + addr_mod;
        data.append(readMemory(addr, 0x10));
    }

    return data;
}
void Device::writeDigitalContacts(){
    int contact_count_addr = 0x4840000;
    int contact_order_addr = 0x4000000;
    int contact_data_addr = 0x5500000;

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
        if(contact_count % int(contact_total/100) == 0){
            emit update2(contact_count, contact_total, "Compressing Data");
        }

        if(contact->radio_id == 0) continue;
        int order_rid_int = (QString::number(contact->radio_id).rightJustified(8, '0').toUInt(nullptr, 16) << 1) + contact->call_type;
        QByteArray order_rid = Int::toBytes(order_rid_int, 4);
        QByteArray data_offset = Int::toBytes(contact_data.size(), 4);
        order_data_array.push_back(
            std::tuple<int, QByteArray, QByteArray>(order_rid_int, order_rid, data_offset)
        );

        contact_data.append(contact->call_type);
        contact_data.append(QByteArray::fromHex(QString::number(contact->radio_id).rightJustified(8, '0').toUtf8()));
        contact_data.append(contact->call_alert);
        contact_data.append(contact->name.toUtf8() + '\0');
        contact_data.append(contact->city.toUtf8() + '\0');
        contact_data.append(contact->callsign.toUtf8() + '\0');
        contact_data.append(contact->state.toUtf8() + '\0');
        contact_data.append(contact->country.toUtf8() + '\0');
        contact_data.append(contact->remarks.toUtf8() + '\0');        

        contact_count++;
    }

    int addr_mod = contact_data.size() % 0x186a0;
    int block = int((contact_data.size() - addr_mod) / 0x186a0);
    int end_address = contact_data_addr + (block * 0x40000) + addr_mod;

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

    emit update1(1, 3, "Writing Digital Contacts");
    for(int idx = 0; idx < order_data.size(); idx+=0x10){
        int addr_mod = idx % 0x1f400;
        int block = int((idx - addr_mod) / 0x1f400);
        int addr = contact_order_addr + (block * 0x40000) + addr_mod;
        QByteArray data = order_data.mid(idx, 0x10);
        writeMemory(addr, data);
        if(idx > 0 && int(idx / 0x10) % int((order_data.size() / (0x10 * 100))) == 0){
            emit update2(idx, order_data.size(), "Writing Order Data");
        }
    }

    emit update1(2, 3, "Writing Digital Contacts");
    for(int idx = 0; idx < order_data.size(); idx+=0x10){
        int addr_mod = idx % 0x186a0;
        int block = int((idx - addr_mod) / 0x186a0);
        int addr = contact_data_addr + (block * 0x40000) + addr_mod;
        QByteArray data = contact_data.mid(idx, 0x10);
        writeMemory(addr, data);
        if(idx > 0 && int(idx / 0x10) % int((contact_data.size() / (0x10 * 100))) == 0){
            emit update2(idx, contact_data.size(), "Writing Digital Data");
        }
    }

    emit update1(3, 3, "Writing Digital Contacts");
    emit update2(0, 0, "");

}

// Read Other Data
void Device::readOtherData(){
        Anytone::Memory::init();

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

        int steps = 16;

        emit update1(0, steps, "Reading Data");
        readChannelData();
        emit update1(1, steps, "Reading Data");
        readTalkgroupData();
        emit update1(2, steps, "Reading Data");
        readZoneData();
        emit update1(3, steps, "Reading Data");
        readRadioIdData();
        emit update1(4, steps, "Reading Data");
        readScanListData();
        emit update1(5, steps, "Reading Data");
        readFmData();
        emit update1(6, steps, "Reading Data");
        readRoamingChannelData();
        emit update1(7, steps, "Reading Data");
        readRoamingZoneData();
        emit update1(8, steps, "Reading Data");
        readSettings();
        emit update1(9, steps, "Reading Data");
        readGpsRoamingData();
        emit update1(10, steps, "Reading Data");
        readMasterId();
        emit update1(11, steps, "Reading Data");
        readAutoRepeaterFrequencyData();
        emit update1(12, steps, "Reading Data");
        readPrefabricatedSms();
        emit update1(13, steps, "Reading Data");
        readReceiveGroups();
        emit update1(14, steps, "Reading Data");
        readAesEncryptionKeys();
        readArc4EncryptionKeys();
        readEncryptionKeys();

        readAnalogAddress();

        emit update1(15, steps, "Linking Data");
        Anytone::Memory::linkReferences();
    }
void Device::readChannelData(){
    emit update2(0, 0, "Reading Channel Data");
    QByteArray channel_set_data = readMemory(Anytone::Memory::Map()->ChannelSet, 0x200);
    std::vector<int> channel_id_list;

    for (int i = 0; i < channel_set_data.size(); ++i) { 
        unsigned char byte = channel_set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            channel_id_list.push_back((i*8) + j);
        }
    }

    int offset = Anytone::Memory::Map()->ChannelData;
    int block_channels = Anytone::Memory::Map()->ChannelDataBlockSize;
    for(int i = 0; i < channel_id_list.size(); i++){
        emit update2(i, channel_id_list.size(), "Reading Channel Data");

        int idx = channel_id_list.at(i);
        if(idx >= Anytone::Memory::channels.size()) continue;
        int channel_data_block = int(idx / block_channels);
        int primary_data_address = offset + ((idx - (channel_data_block * block_channels)) * Anytone::Memory::Map()->ChannelDataOffset) + (channel_data_block * Anytone::Memory::Map()->ChannelDataBlockOffset);
        int secondary_data_address = primary_data_address + Anytone::Memory::Map()->ChannelDataSecondaryOffset;
        
        QByteArray channel_data = readMemory(primary_data_address, 0x40);
        channel_data.append(readMemory(secondary_data_address, 0x40));
         
        if(!is_alive){
            emit finished(DeviceStatus::STATUS_COM_ERROR);
            return;
        }

        Anytone::Channel *channel = Anytone::Memory::channels.at(idx);
        channel->decode(channel_data);
    }
}
void Device::readTalkgroupData(){
    QByteArray set_list_data = readMemory(0x2640000, 0x4f0);

    std::vector<int> id_list;
    for (int i = 0; i < set_list_data.size(); ++i) { 
        unsigned char byte = set_list_data.at(i);
        for(int j = 0; j < 8; j++){
            if(Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x2680000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Talkgroup Data");
        int idx = id_list.at(i);
        if(idx >= Anytone::Memory::talkgroups.size()) continue;
        int addr = offset + (idx * 0x64);
        QByteArray tg_data = readMemory(addr, 0x40);
        if(!is_alive) return;
        Anytone::Memory::talkgroups.at(idx)->decode(tg_data);
    }
}
void Device::readZoneData(){
    int zone_name_offset = 0x2540000;
    int zone_channel_offset = 0x1000000;
    int zone_a_channel_offset = 0x2500100;
    int zone_b_channel_offset = 0x2500300;
    int zone_hide_offset = 0x24c1360;

    QByteArray zone_set_data = readMemory(0x24c1300, 0x20);
    QByteArray zone_a_channel_data = readMemory(zone_a_channel_offset, 0x200);
    QByteArray zone_b_channel_data = readMemory(zone_b_channel_offset, 0x200);
    QByteArray zone_hide_data = readMemory(zone_hide_offset, 0x20);

    std::vector<int> id_list;
    for (int i = 0; i < zone_set_data.size(); ++i) { 
        unsigned char byte = zone_set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Zone Data");
        int idx = id_list.at(i);

        Anytone::Zone *zone = Anytone::Memory::zones.at(idx);
        if(!zone) return;

        // Name
        int addr = zone_name_offset + (idx * 0x20);
        QByteArray zone_name_data = readMemory(addr, 0x10);
        if(!is_alive) return;

        QString name = QString(zone_name_data);
        name.remove(QChar('\0'));
        zone->name = name;

        //Channels
        addr = zone_channel_offset + (idx * 0x200);
        QByteArray zone_channel_list_data = readMemory(addr, 0x200);
        for(int j = 0; j < zone_channel_list_data.size(); j+=2){
            int ch_idx = Int::fromBytes(zone_channel_list_data.mid(j, 2));
            if(ch_idx != 0xffff) zone->temp_member_channel_idxs.push_back(ch_idx);
        }

        zone->a_channel_idx = Int::fromBytes(zone_a_channel_data.mid(idx * 2, 2));
        zone->b_channel_idx = Int::fromBytes(zone_b_channel_data.mid(idx * 2, 2));
        zone->hide = Bit::test(zone_hide_data.at(int(idx/8)), idx % 8);
    }
}
void Device::readRadioIdData(){
    QByteArray set_data = readMemory(0x24c1320, 0x20);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x2580000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Scan List Data");

        int idx = id_list.at(i);
        if(idx >= Anytone::Memory::radioids.size()) continue;
        int addr = offset + (idx * 0x20);
        QByteArray data = readMemory(addr, 0x20);
        if(!is_alive) return;
        Anytone::Memory::radioids.at(idx)->decode(data);
    }
}
void Device::readScanListData(){
    QByteArray set_data = readMemory(0x24c1340, 0x20);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x1080000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Scan List Data");

        int idx = id_list.at(i);
        if(idx >= Anytone::Memory::scanlists.size()) continue;
        int addr = offset + (idx * 0x200);
        QByteArray scan_list_data = readMemory(addr, 0x90);
        if(!is_alive) return;
        Anytone::Memory::scanlists.at(idx)->decode(scan_list_data);
    }
}
void Device::readFmData(){
    QByteArray fm_data = readMemory(0x2480200, 0x30);

    Anytone::Memory::fm_channels.at(100)-> frequency = QString(fm_data.mid(0x0, 0x4).toHex()).toInt();
    QByteArray fm_freq_data = readMemory(0x2480000, 0x190);

    std::vector<int> read_line_list = {};
    for(int byte_idx = 0; byte_idx < 16; byte_idx++){
        emit update2(byte_idx, 16, "Reading FM Data");
        uint8_t active_byte = fm_data.at(0x10 + byte_idx);
        uint8_t scan_byte = fm_data.at(0x20 + byte_idx);
        for(int bit_index = 0; bit_index < 8; bit_index++){
            int fm_index = (byte_idx * 8) + bit_index;
            bool is_active = Bit::test(active_byte, bit_index);
            if(!is_active) continue;
            bool scan_add = Bit::test(scan_byte, bit_index);
            Anytone::FM *fm = Anytone::Memory::fm_channels.at(fm_index);
            fm->scan_add = scan_add;
            fm->frequency = QString(fm_freq_data.mid(fm_index*4, 0x4).toHex()).toInt();
        }
    }
}
void Device::readRoamingChannelData(){
    QByteArray set_data = readMemory(0x1042000, 0x20);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x1040000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Roaming Channel Data");

        int idx = id_list.at(i);
        if(idx >= Anytone::Memory::roaming_channels.size()) continue;
        int addr = offset + (idx * 0x20);
        QByteArray scan_list_data = readMemory(addr, 0x20);
        if(!is_alive) return;
        Anytone::Memory::roaming_channels.at(idx)->decode(scan_list_data);
    }
}
void Device::readRoamingZoneData(){
    QByteArray set_data = readMemory(0x1042080, 0x10);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x1043000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Roaming Zone Data");

        int idx = id_list.at(i);
        if(idx >= Anytone::Memory::roaming_zones.size()) continue;
        int addr = offset + (idx * 0x50);
        QByteArray scan_list_data = readMemory(addr, 0x50);
        if(!is_alive) return;
        Anytone::Memory::roaming_zones.at(idx)->decode(scan_list_data);
    }
}
void Device::readSettings(){
    emit update2(0, 0, "Reading Settings Data");
    QByteArray data_2500000 = readMemory(0x2500000, 0xf0);
    QByteArray data_2500600 = readMemory(0x2500600, 0x30);
    QByteArray data_2501280 = readMemory(0x2501280, 0x20);
    QByteArray data_2501400 = readMemory(0x2501400, 0x100);
    QByteArray data_24c1400 = readMemory(0x24c1400, 0x20);
    QByteArray data_24c1440 = readMemory(0x24c1440, 0x30);
    
    // data_2501400[0x1e] = TalkerAlias Display Priority
    // data_2501400[0x1f] = TalkerAlias Data Format
    Anytone::Memory::optional_settings->decode(data_2500000, data_2500600, data_2501280, data_2501400);
    Anytone::Memory::alarm_settings->decode(data_2500000, data_24c1400, data_24c1440);
    Anytone::Memory::dtmf_settings->tx_time = static_cast<uint8_t>(data_2500000.at(0x23));
    Anytone::Memory::talk_alias_settings->display_priority = static_cast<uint8_t>(data_2501400.at(0x1e));
    Anytone::Memory::talk_alias_settings->display_priority = static_cast<uint8_t>(data_2501400.at(0x1f));
    
    readAprsSettings();
    readToneSettings();
}
void Device::readAprsSettings(){
    QByteArray data_2501000 = readMemory(0x2501000, 0x240);
    QByteArray data_2501800 = readMemory(0x2501800, 0x100);
    Anytone::Memory::aprs_settings->decode(data_2501000, data_2501800);
}
void Device::readMasterId(){
    emit update2(0, 0, "Reading Master ID");
    QByteArray master_radioid_data = readMemory(0x2582000, 0x20);
    Anytone::Memory::master_radio_id->decode(master_radioid_data);
}
void Device::readGpsRoamingData(){
    QByteArray gps_roaming_data = readMemory(0x2504000, 0x400);
    for(int gps_idx = 0; gps_idx < 32; gps_idx++){
        emit update2(gps_idx, 32, "Reading GPS Roaming Data");
        int gps_addr = (gps_idx % 16) * 0x20;
        if(gps_idx >= 16) gps_addr += 0x10;
        Anytone::Memory::gps_roaming_list.at(gps_idx)->decode(gps_roaming_data.mid(gps_addr, 0x10));
    }
}
void Device::readAutoRepeaterFrequencyData(){
    QByteArray auto_repeater_offset_data = readMemory(0x24c2000, 0x3f0);
    for(int i =0; i<250; i++){
        Anytone::Memory::ar_offset_frequencies.at(i)->frequency = Int::fromBytes(auto_repeater_offset_data.mid(i*4, 4));
    }
}
void Device::readPrefabricatedSms(){
    std::vector<uint8_t> id_list = {};
    uint8_t current_idx = 0;
    while(current_idx <= 100){
        uint32_t addr = 0x1640000 + (current_idx * 0x10);
        QByteArray sms_data = readMemory(addr, 0x10);
        if(static_cast<uint8_t>(sms_data.at(3)) == 0xff) break;
        id_list.push_back(static_cast<uint8_t>(sms_data.at(3)));
        if(static_cast<uint8_t>(sms_data.at(2)) == 0xff) break;
        current_idx = static_cast<uint8_t>(sms_data.at(2));
    }

    int offset = 0x2140000;
    for(int i = 0; i < id_list.size(); i++){
        int idx = id_list.at(i);
        emit update2(i, id_list.size(), "Reading Prefabricated SMS");

        int block = int(((idx * 0x100) - idx % 0x800) / 0x800);
        int addr = offset + (block * 0x40000) + ((idx * 0x100) % 0x800);
        QByteArray sms_data = readMemory(addr, 0xd0);
        Anytone::Memory::prefabricated_sms_list.at(idx)->decode(sms_data);
    }

}
void Device::readReceiveGroups(){
    QByteArray set_data = readMemory(0x25c0b10, 0x10);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x2980000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading Receive Group Call List Data");

        int idx = id_list.at(i);
        int addr = idx * 0x2000;
        Anytone::Memory::receive_group_call_lists.at(idx)->decode(readMemory(addr, 0x30));

    }
}
void Device::readAesEncryptionKeys(){
    QByteArray set_data = readMemory(0x24c8000, 0x10);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x24c4000;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading AES Code Data");
        int addr = offset + (i*0x40);
        Anytone::Memory::aes_encryption_keys.at(i)->decode(readMemory(addr, 0x30));
    }
}
void Device::readArc4EncryptionKeys(){
    QByteArray set_data = readMemory(0x25c1c00, 0x10);
    std::vector<int> id_list;

    for (int i = 0; i < set_data.size(); ++i) { 
        unsigned char byte = set_data.at(i);
        for(int j = 0; j < 8; j++){
            if(!Bit::test(byte, j)) continue;
            id_list.push_back((i*8) + j);
        }
    }

    int offset = 0x25c0c00;
    for(int i = 0; i < id_list.size(); i++){
        emit update2(i, id_list.size(), "Reading ARC4 Code Data");
        int idx = id_list.at(i);
        int addr = offset + (i*0x10);
        Anytone::Memory::arc4_encryption_keys.at(i)->decode(readMemory(addr, 0x10));
    }
}
void Device::readEncryptionKeys(){
    int id_offset = 0x24c1700;
    int key_offset = 0x24c1810;

    QByteArray id_data = readMemory(id_offset, 0x40);
    QByteArray key_data = readMemory(key_offset, 0x40);
    for (int i = 0; i < 32; ++i) { 
        emit update2(i, 32, "Reading Encryption Code Data");
        Anytone::EncryptionCode *key = Anytone::Memory::encryption_keys.at(i);
        key->id = QString(id_data.mid(i*2, 2).toHex());
        key->key = QString(key_data.mid(i*2, 2).toHex());
    }
}
void Device::readToneSettings(){
    QByteArray data_24c1000 = readMemory(0x24c1000, 0xd0);
    QByteArray data_2500500 = readMemory(0x2500500, 0x100);
    
    
    Anytone::Memory::dtmf_settings->decode(data_24c1000, data_2500500);
    Anytone::Memory::tone5_settings->decode(data_24c1000);

    readTone2Settings();
}
void Device::readTone2Settings(){
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
void Device::readAnalogAddress(){
    QByteArray set_list = readMemory(0x2900100, 0x100);
    QByteArray id_list = readMemory(0x2900000, 0x100);

    QVector<int> idx_list;

    for(uint8_t i : id_list){
        if(i != 0xff){
            idx_list.append(i);
        }
    }

    int read_len = (idx_list.size() * 0x18);
    if(read_len % 16 != 0) read_len += 0x8;

    QByteArray data = readMemory(0x2940000, read_len);

    for(uint8_t i : idx_list){
        Anytone::AnalogAddress *item = Anytone::Memory::analog_addresses.at(i);
        item->decode(data.mid(i*0x18, 0x18));
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

    emit update1(0, 1, "Writing...");
    
    int idx = 0;
    for (auto const& [addr, data] : write_data) {
        emit update2(idx, write_data.size(), "Writing Data");
        if(is_alive) writeMemory(addr, data);
        idx += 1;
    }
}
void Device::writeChannelData(){
    int data_offset = 0x800000;
    QByteArray set_list(0x200, 0);
    auto* bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i = 0; i < Anytone::Memory::channels.size(); i++){
        Anytone::Channel *ch = Anytone::Memory::channels.at(i);
        if(ch->rx_frequency == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);

        Q_ASSERT(current_byte_idx >= 0 && current_byte_idx < set_list.size());
        if(ch->rx_frequency > 0) Bit::set(&bytes[current_byte_idx], i%8);

        int channel_data_block = int(i / 128);
        int primary_data_address = data_offset + ((i - (channel_data_block * 128)) * 0x40) + (channel_data_block * 0x40000);
        int secondary_data_address = primary_data_address + 0x2000;

        QByteArray data1 = ch->encodeData1();
        QByteArray data2 = ch->encodeData2();


        write_data[primary_data_address] = data1;
        write_data[secondary_data_address] = data2;
    }

    write_data[0x24c1500] = set_list;
}
void Device::writeZoneData(){
    int zone_set_list_addr = 0x24c1300; //0x20
    int zone_names_addr = 0x2540000;

    int zone_name_addr = 0x2540000;
    int zone_channel_offset = 0x1000000;
    int zone_a_channel_addr = 0x2500100;
    int zone_b_channel_addr = 0x2500300;
    int zone_hide_addr = 0x24c1360;

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
            write_data[zone_names_addr + (i * 0x20)] = zone->name.toUtf8().leftJustified(0x20, '\0');
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
void Device::writeTalkgroupData(){
    int tg_set_list_addr = 0x2640000;
    int tg_data_list_addr = 0x2680000;
    QByteArray tg_set_list_data(0x4e3, 0xff);
    auto* tg_set_list_bytes = reinterpret_cast<std::uint8_t*>(tg_set_list_data.data());
    QByteArray tg_data;

    for(int i=0; i < Anytone::Memory::talkgroups.size(); i++){
        Anytone::Talkgroup *tg = Anytone::Memory::talkgroups.at(i);
        int current_byte_idx = int((i - (i % 8))/8);
        if(tg->dmr_id > 0) Bit::clear(&tg_set_list_bytes[current_byte_idx], i%8);
        if(tg->dmr_id) tg_data += tg->encode();
    }

    tg_data = tg_data.leftJustified(tg_data.size() + 0x10 - (tg_data.size() % 0x10), '\0');
    tg_set_list_data = tg_set_list_data.leftJustified(0x4f0, '\0');

    write_data[tg_set_list_addr] = tg_set_list_data;
    write_data[tg_data_list_addr] = tg_data;
}
void Device::writeRadioIdData(){
    int set_list_addr = 0x24c1320;
    QByteArray set_list(0x20, 0);
    int data_addr = 0x2580000;
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::radioids.size(); i++){
        Anytone::RadioId *rid = Anytone::Memory::radioids.at(i);
        if(rid->dmr_id == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * 0x20)] = rid->encode();
    }

    write_data[set_list_addr] = set_list;
}
void Device::writeScanListData(){
    int set_list_addr = 0x24c1340;
    int data_addr = 0x1080000;
    QByteArray set_list(0x20, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::scanlists.size(); i++){
        Anytone::ScanList *sl = Anytone::Memory::scanlists.at(i);
        if(sl->channels.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * 0x200)] = sl->encode();
    }
    write_data[set_list_addr] = set_list;
}
void Device::writeFMChannelData(){
    int fm_active_scan_addr = 0x2480200;
    QByteArray fm_data(0x30, 0);
    QByteArray fm_freq_data(0x190, 0xff);
    auto* fm_data_bytes = reinterpret_cast<std::uint8_t*>(fm_data.data());

    for(int i=0; i < Anytone::Memory::fm_channels.size() - 1; i++){
        Anytone::FM *fm = Anytone::Memory::fm_channels.at(i);
        int current_byte_idx = int((i - (i % 8))/8);
        if(fm->frequency > 0) Bit::set(&fm_data_bytes[0x10 + current_byte_idx], i%8);
        if(fm->frequency > 0 && fm->scan_add) Bit::set(&fm_data_bytes[0x20 + current_byte_idx], i%8);

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

    write_data[fm_active_scan_addr] = fm_data;
    write_data[0x2480000] = fm_freq_data;
}
void Device::writeGpsRoamingData(){
    for(int gps_idx = 0; gps_idx < 32; gps_idx++){
        int gps_addr = 0x2504000 + ((gps_idx % 16) * 0x20);
        if(gps_idx >= 16) gps_addr += 0x10;
        write_data[gps_addr] = Anytone::Memory::gps_roaming_list.at(gps_idx)->encode();
    }
}
void Device::writeAutoRepeaterFrequencyData(){
    QByteArray data(0x3f0, 0);
    for(int i = 0; i < Anytone::Memory::ar_offset_frequencies.size(); i++){
        Anytone::AutoRepeaterOffsetFrequency *arf = Anytone::Memory::ar_offset_frequencies.at(i);
        int addr = i*4;
        data.replace(addr, 4, 
            Int::toBytes(arf->frequency, 4)
        );
    }
    write_data[0x24c2000] = data;
}
void Device::writeRoamingChannelData(){
    int set_list_addr = 0x1042000;
    int data_addr = 0x1040000;
    QByteArray set_list(0x20, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::roaming_channels.size(); i++){
        Anytone::RoamingChannel *rc = Anytone::Memory::roaming_channels.at(i);
        if(rc->rx_frequency == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * 0x200)] = rc->encode();
    }
    write_data[set_list_addr] = set_list;
}
void Device::writeRoamingZoneData(){
    int set_list_addr = 0x1042080;
    int data_addr = 0x1043000;
    QByteArray set_list(0x10, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::roaming_zones.size(); i++){
        Anytone::RoamingZone *rz = Anytone::Memory::roaming_zones.at(i);
        if(rz->channels.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * 0x200)] = rz->encode();

    }
    write_data[set_list_addr] = set_list;
}
void Device::writeSettingsData(){
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

    Anytone::Memory::alarm_settings->encode(data_2500000, data_24c1400, data_24c1440);
    Anytone::Memory::optional_settings->encode(data_2500000, data_2500600, data_2501280, data_2501400);

    data_2501400[0x6f] = Anytone::Memory::aprs_settings->fixed_location_beacon;

    data_2501400[0x1e] = Anytone::Memory::talk_alias_settings->display_priority;
    data_2501400[0x1f] = Anytone::Memory::talk_alias_settings->display_priority;
    

    write_data[data_2500000_addr] = data_2500000;
    write_data[data_2500600_addr] = data_2500600;
    write_data[data_2501280_addr] = data_2501280;
    write_data[data_2501400_addr] = data_2501400;
    write_data[data_24c1400_addr] = data_24c1400;
    write_data[data_24c1440_addr] = data_24c1440;

    writeAprsSettings();
}
void Device::writeAprsSettings(){
    int data_2501000_addr = 0x2501000;
    int data_2501800_addr = 0x2501800;

    QByteArray data_2501000(0x240, 0);
    QByteArray data_2501800(0x100, 0);
    
    Anytone::Memory::aprs_settings->encode(data_2501000, data_2501800);

    write_data[data_2501000_addr] = data_2501000;
    write_data[data_2501800_addr] = data_2501800;
}
void Device::writeMasterRadioIdData(){
    write_data[0x2582000] = Anytone::Memory::master_radio_id->encode();
}
void Device::writePrefabSms(){
    int set_list_addr = 0x1640000;
    int data_addr = 0x2140000;
    QByteArray set_list(0x20, 0);
    std::vector<Anytone::PrefabricatedSms*> active_sms = {};

    for(Anytone::PrefabricatedSms *sms : active_sms){
        if(sms->text.size() > 0) active_sms.push_back(sms);
    }
    
    for(int i = 0; i < active_sms.size(); i++){
        Anytone::PrefabricatedSms *sms = active_sms.at(i);
        int block = int(((i * 0x100) - i % 0x800) / 0x800);
        int addr = data_addr + (block * 0x40000) + ((i * 0x100) % 0x800);
        write_data[addr] = sms->encode();
    }
    
    // auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());
}
void Device::writeAesKeys(){
    int set_list_addr = 0x24c8000;
    int data_addr = 0x24c4000;
    QByteArray set_list(0x10, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::aes_encryption_keys.size(); i++){
        Anytone::AesEncryptionCode *key = Anytone::Memory::aes_encryption_keys.at(i);
        if(key->key.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * 0x40)] = key->encode();
    }

    write_data[set_list_addr] = set_list;

}
void Device::writeArc4Keys(){
    int set_list_addr = 0x25c1c00;
    int data_addr = 0x25c0c00;
    QByteArray set_list(0x10, 0);
    auto* set_list_bytes = reinterpret_cast<std::uint8_t*>(set_list.data());

    for(int i=0; i < Anytone::Memory::arc4_encryption_keys.size(); i++){
        Anytone::Arc4EncryptionCode *key = Anytone::Memory::arc4_encryption_keys.at(i);
        if(key->key.size() == 0) continue;
        int current_byte_idx = int((i - (i % 8))/8);
        Bit::set(&set_list_bytes[current_byte_idx], i%8);
        write_data[data_addr + (i * 0x10)] = key->encode();
    }

    write_data[set_list_addr] = set_list;

}
void Device::writeEncryptionKeys(){
    int id_offset = 0x24c1700;
    int key_offset = 0x24c1810;

    QByteArray id_data = readMemory(id_offset, 0x40);
    QByteArray key_data = readMemory(key_offset, 0x40);
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
void Device::writeToneSettings(){
    QByteArray data_24c1000(0xd0, 0);
    QByteArray data_2500500(0x100, 0xff);
    Anytone::Memory::dtmf_settings->encode(data_24c1000, data_2500500);
    Anytone::Memory::tone5_settings->encode(data_24c1000);

    write_data[0x24c1000] = data_24c1000;
    write_data[0x2500500] = data_2500500;

    writeTone2Settings();
}
void Device::writeTone2Settings(){
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
void SerialWorker::run(){
    if(comport.size() > 0){
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

        QObject::disconnect(device, &Device::finished, this, &SerialWorker::finished);
        QObject::disconnect(device, &Device::update1, this, &SerialWorker::update1);
        QObject::disconnect(device, &Device::update2, this, &SerialWorker::update2);

        delete device;
        device = nullptr;

    }else if(bin_filepath.size() > 0){
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

        QObject::disconnect(device, &Device::finished, this, &SerialWorker::finished);
        QObject::disconnect(device, &Device::update1, this, &SerialWorker::update1);
        QObject::disconnect(device, &Device::update2, this, &SerialWorker::update2);

        delete device;
        device = nullptr;
    }else{
        emit finished(DeviceStatus::STATUS_COM_ERROR);
        qDebug() << "Invalid serial device configuration";
    }
}
void SerialWorker::done(){
    qDebug() << "ready read";
}