
#include "am_zone_edit_dialog.h"
#include "ui_am_zone_edit_dialog.h"
#include "anytone_memory.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>

AmZoneEditDialog::AmZoneEditDialog(QWidget *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_AmZoneEditDialog>()),
    index(index)
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);

    connect(ui->pushChannelBtn, &QPushButton::clicked, this, &AmZoneEditDialog::pushChannel);
    connect(ui->popChannelBtn, &QPushButton::clicked, this, &AmZoneEditDialog::popChannel);
    connect(ui->pushScanBtn, &QPushButton::clicked, this, &AmZoneEditDialog::pushScanChannel);
    connect(ui->popScanBtn, &QPushButton::clicked, this, &AmZoneEditDialog::popScanChannel);
    connect(ui->orderIdBtn, &QPushButton::clicked, this, &AmZoneEditDialog::orderMemberId);
    connect(ui->orderNameBtn, &QPushButton::clicked, this, &AmZoneEditDialog::orderMemberName);
    connect(ui->orderUpBtn, &QPushButton::clicked, this, &AmZoneEditDialog::orderUp);
    connect(ui->orderDownBtn, &QPushButton::clicked, this, &AmZoneEditDialog::orderDown);
    connect(ui->nextBtn, &QPushButton::clicked, this, &AmZoneEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &AmZoneEditDialog::prevBtnClicked);

    loadData();
    
}
AmZoneEditDialog::~AmZoneEditDialog(){}

void AmZoneEditDialog::loadData(){
    setWindowTitle("AM Zone Edit---" + QString::number(index+1));
    zone = Anytone::Memory::am_zones.at(index);

    if(zone->member_channels.size() == 0) zone->name = "AM CH " + QString::number(index+1).rightJustified(3, '0');
    ui->nameTxt->setText(zone->name);

    available_channels.clear();
    for(Anytone::AmAir *ch : Anytone::Memory::am_air_list){
        if(ch->index < 256 && ch->frequency > 0 && zone->member_channels.indexOf(ch) == -1) available_channels.push_back(ch);
    }

    available_scan_channels.clear();
    for(Anytone::AmAir *ch : zone->member_channels){
        if(zone->scan_channels.indexOf(ch) == -1) available_scan_channels.push_back(ch);
    }

    member_channels = zone->member_channels;
    scan_channels = zone->scan_channels;

    updateChannelTables();
    ui->aChannelCmbx->setCurrentIndex(zone->aChannelIdx);
}

void AmZoneEditDialog::save(){
    // channel->name = ui->nameTxt->text();
    // channel->setFrequencyString(ui->frequencyTxt->text());
}

void AmZoneEditDialog::updateAChannelList(){
    QString channel_a_txt = ui->aChannelCmbx->currentText();
    QStringList channel_list = {};
    for(Anytone::AmAir *ch : member_channels){
        channel_list.push_back(ch->name);
    }
    ui->aChannelCmbx->clear();
    ui->aChannelCmbx->addItems(channel_list);
    int idx_a = channel_list.indexOf(channel_a_txt);
    if(idx_a != -1 ) ui->aChannelCmbx->setCurrentIndex(idx_a);
}


void AmZoneEditDialog::orderMemberId(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
            [](const Anytone::AmAir* a, const Anytone::AmAir* b) {
                return a->index < b->index;
            });
    updateChannelTables();
}
void AmZoneEditDialog::orderMemberName(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
        [](const Anytone::AmAir* a, const Anytone::AmAir* b) {
            return a->name < b->name;
        });
    updateChannelTables();
}
void AmZoneEditDialog::updateChannelTables(){
    // ---------- Member channels ----------
    auto *memberModel = new QStandardItemModel(this);
    memberModel->setColumnCount(2);

    for (int i = 0; i < static_cast<int>(member_channels.size()); ++i) {
        const auto &ch = member_channels[i];

        memberModel->setItem(i, 0,
            new QStandardItem(QString::number(ch->index + 1)));
        memberModel->setItem(i, 1,
            new QStandardItem(ch->name));
    }

    ui->memberChannelTableView->setModel(memberModel);


    // ---------- Available channels ----------
    auto *channelModel = new QStandardItemModel(this);
    channelModel->setColumnCount(2);

    for (int i = 0; i < static_cast<int>(available_channels.size()); ++i) {
        const auto &ch = available_channels[i];

        channelModel->setItem(i, 0,
            new QStandardItem(QString::number(ch->index + 1)));
        channelModel->setItem(i, 1,
            new QStandardItem(ch->name));
    }

    ui->availableChannelTableView->setModel(channelModel);

    // Scan Channels
    auto *memberScanModel = new QStandardItemModel(this);
    memberScanModel->setColumnCount(2);

    for (int i = 0; i < static_cast<int>(scan_channels.size()); ++i) {
        const auto &ch = scan_channels[i];

        memberScanModel->setItem(i, 0,
            new QStandardItem(QString::number(ch->index + 1)));
        memberScanModel->setItem(i, 1,
            new QStandardItem(ch->name));
    }

    ui->memberScanChannelTableView->setModel(memberScanModel);


    // Available Scan Channels
    auto *availableScanModel = new QStandardItemModel(this);
    availableScanModel->setColumnCount(2);

    for (int i = 0; i < static_cast<int>(available_scan_channels.size()); ++i) {
        const auto &ch = available_scan_channels[i];

        availableScanModel->setItem(i, 0,
            new QStandardItem(QString::number(ch->index + 1)));
        availableScanModel->setItem(i, 1,
            new QStandardItem(ch->name));
    }

    ui->availableScanChannelTableView->setModel(availableScanModel);


    // ---------- Restore selection ----------
    if (available_channel_selected_idx >= 0)
        ui->availableChannelTableView
            ->selectRow(available_channel_selected_idx);

    if (member_channel_selected_idx >= 0)
        ui->memberChannelTableView
            ->selectRow(member_channel_selected_idx);


    ui->availableChannelTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->availableChannelTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->availableChannelTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->availableChannelTableView->setColumnWidth(0, 50);
    ui->availableChannelTableView->setColumnWidth(1, 100);

    ui->memberChannelTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->memberChannelTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->memberChannelTableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->memberChannelTableView->setColumnWidth(0, 50);
    ui->memberChannelTableView->setColumnWidth(1, 100);

    updateAChannelList();
}
void AmZoneEditDialog::pushChannel(){
    if(ui->availableChannelTableView->selectionModel()->hasSelection()){
        auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
        if (!rows.isEmpty()) { 
            available_channel_selected_idx = rows.first().row();
        }
    }else if(available_channel_selected_idx > available_channels.size() - 1){
        return;
    }
    qDebug() << available_channel_selected_idx;
    member_channels.push_back(available_channels.at(available_channel_selected_idx));
    available_scan_channels.push_back(available_channels.at(available_channel_selected_idx));
    available_channels.erase(available_channels.begin() + available_channel_selected_idx);
    member_channel_selected_idx = static_cast<int>(member_channels.size()) - 1;
    updateChannelTables();
    QTimer::singleShot(0, ui->memberChannelTableView, &QTableView::scrollToBottom);
}
void AmZoneEditDialog::popChannel(){
    auto rows = ui->memberChannelTableView->selectionModel()->selectedRows();
    if (!rows.isEmpty()) {
        member_channel_selected_idx = rows.first().row();
    } else if (member_channel_selected_idx >
               static_cast<int>(member_channels.size()) - 1) {
        return;
    }
    if (member_channel_selected_idx < 0 ||
        member_channel_selected_idx >= static_cast<int>(member_channels.size()))
        return;
    Anytone::AmAir* ch = member_channels.at(member_channel_selected_idx);
    member_channels.removeOne(ch);
    available_scan_channels.removeOne(ch);
    scan_channels.removeOne(ch);
    available_channels.push_back(ch);
    std::sort(available_channels.begin(), available_channels.end(),
              [](const Anytone::AmAir* a, const Anytone::AmAir* b) {
                  return a->index < b->index;
              });

    auto it = std::find(available_channels.begin(), available_channels.end(), ch);
    if (it != available_channels.end()) {
        available_channel_selected_idx =
            static_cast<int>(std::distance(available_channels.begin(), it));
    } else {
        available_channel_selected_idx = -1;
    }
    updateChannelTables();
}
void AmZoneEditDialog::pushScanChannel(){
    if(ui->availableScanChannelTableView->selectionModel()->hasSelection()){
        auto rows = ui->availableScanChannelTableView->selectionModel()->selectedRows();
        if (!rows.isEmpty()) { available_scan_channel_selected_idx = rows.first().row(); }
    }else if(available_scan_channel_selected_idx > available_scan_channels.size() - 1){
        return;
    }
    scan_channels.push_back(available_scan_channels.at(available_scan_channel_selected_idx));
    available_scan_channels.erase(available_scan_channels.begin() + available_scan_channel_selected_idx);
    member_scan_channel_selected_idx = static_cast<int>(scan_channels.size()) - 1;
    updateChannelTables();
    QTimer::singleShot(0, ui->memberChannelTableView, &QTableView::scrollToBottom);
}
void AmZoneEditDialog::popScanChannel(){
    auto rows = ui->memberScanChannelTableView->selectionModel()->selectedRows();
    if (!rows.isEmpty()) {
        member_scan_channel_selected_idx = rows.first().row();
    } else if (member_scan_channel_selected_idx >
               static_cast<int>(scan_channels.size()) - 1) {
        return;
    }
    if (member_scan_channel_selected_idx < 0 ||
        member_scan_channel_selected_idx >= static_cast<int>(scan_channels.size()))
        return;
    Anytone::AmAir* ch = scan_channels.at(member_scan_channel_selected_idx);
    scan_channels.erase(scan_channels.begin() + member_scan_channel_selected_idx);
    available_scan_channels.push_back(ch);

    std::sort(available_scan_channels.begin(), available_scan_channels.end(),
              [](const Anytone::AmAir* a, const Anytone::AmAir* b) {
                  return a->index < b->index;
              });

    auto it = std::find(available_scan_channels.begin(), available_scan_channels.end(), ch);
    if (it != available_scan_channels.end()) {
        available_scan_channel_selected_idx =
            static_cast<int>(std::distance(available_scan_channels.begin(), it));
    } else {
        available_scan_channel_selected_idx = -1;
    }
    updateChannelTables();
}


void AmZoneEditDialog::orderUp(){
    if(!ui->memberChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->memberChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == 0) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::AmAir* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx - 1), ch);
    member_channel_selected_idx = idx - 1;
    updateChannelTables();
}
void AmZoneEditDialog::orderDown(){
    if(!ui->memberChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->memberChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == zone->member_channels.size() - 1) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::AmAir* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx + 1), ch);
    member_channel_selected_idx = idx + 1;
    updateChannelTables();
}

void AmZoneEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::am_zones.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::am_zones.size() - 1);
}
void AmZoneEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}

