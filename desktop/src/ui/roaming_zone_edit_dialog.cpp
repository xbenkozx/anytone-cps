
#include <algorithm> 
#include "roaming_zone_edit_dialog.h"
#include "ui_roaming_zone_edit_dialog.h"
#include "memory/anytone_memory.h"
#include "main_window.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>


RoamingZoneEditDialog::RoamingZoneEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_RoamingZoneEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    this->index = index;
    this->main_window = parent;

    available_channels = {};
    member_channels = {};

    setupUI();
    loadData();
    
}
RoamingZoneEditDialog::~RoamingZoneEditDialog(){}

void RoamingZoneEditDialog::setupUI(){
    connect(ui->pushChannelBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::pushChannel);
    connect(ui->popChannelBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::popChannel);
    connect(ui->orderIdBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::orderMemberId);
    connect(ui->orderNameBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::orderMemberName);
    connect(ui->orderUpBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::orderUp);
    connect(ui->orderDownBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::orderDown);
    connect(ui->orderAvailableIdBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::orderAvailableId);
    connect(ui->orderAvailableNameBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::orderAvailableName);
    connect(ui->okBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::saveClose);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::close);
    connect(ui->nextBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &RoamingZoneEditDialog::prevBtnClicked);
}
void RoamingZoneEditDialog::loadData(){
    setWindowTitle("Roaming Zone Edit---" + QString::number(index+1));
    zone = Anytone::Memory::roaming_zones.at(index);

    if(zone->channels.size() == 0) zone->name = "Roam Zone " + QString::number(index+1);

    available_channels.clear();
    for(Anytone::RoamingChannel *ch : Anytone::Memory::roaming_channels){
        if(ch->rx_frequency > 0 && zone->channels.indexOf(ch) == -1) available_channels.push_back(ch);
    }

    member_channels = zone->channels;

    updateChannelTables();

    ui->nameTxt->setText(zone->name);
}
void RoamingZoneEditDialog::save(){
    zone->name = ui->nameTxt->text();
    zone->channels = member_channels;
}
void RoamingZoneEditDialog::orderAvailableId(){
    orderAvailable(0);
}
void RoamingZoneEditDialog::orderAvailableName(){
    orderAvailable(1);
}
void RoamingZoneEditDialog::orderAvailable(int sort_type){
    if(sort_type == 0){
        std::stable_sort(available_channels.begin(), available_channels.end(),
            [](const Anytone::RoamingChannel* a, const Anytone::RoamingChannel* b) {
                return a->id < b->id;
            });
    }else{
        std::stable_sort(available_channels.begin(), available_channels.end(),
            [](const Anytone::RoamingChannel* a, const Anytone::RoamingChannel* b) {
                return a->name < b->name;
            });
    }
    updateChannelTables();
}
void RoamingZoneEditDialog::orderMemberId(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
            [](const Anytone::RoamingChannel* a, const Anytone::RoamingChannel* b) {
                return a->id < b->id;
            });
}
void RoamingZoneEditDialog::orderMemberName(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
        [](const Anytone::RoamingChannel* a, const Anytone::RoamingChannel* b) {
            return a->name < b->name;
        });
}
void RoamingZoneEditDialog::updateChannelTables(){
    // ---------- Member channels ----------
    auto *memberModel = new QStandardItemModel(this);
    memberModel->setColumnCount(2);

    for (int i = 0; i < static_cast<int>(member_channels.size()); ++i) {
        const auto &ch = member_channels[i];

        memberModel->setItem(i, 0,
            new QStandardItem(QString::number(ch->id + 1)));
        memberModel->setItem(i, 1,
            new QStandardItem(ch->name));
    }

    ui->memberTableView->setModel(memberModel);


    // ---------- Available channels ----------
    auto *channelModel = new QStandardItemModel(this);
    channelModel->setColumnCount(2);

    for (int i = 0; i < static_cast<int>(available_channels.size()); ++i) {
        const auto &ch = available_channels[i];

        channelModel->setItem(i, 0,
            new QStandardItem(QString::number(ch->id + 1)));
        channelModel->setItem(i, 1,
            new QStandardItem(ch->name));
    }

    ui->availableChannelTableView->setModel(channelModel);


    // ---------- Restore selection ----------
    if (available_channel_selected_idx >= 0)
        ui->availableChannelTableView
            ->selectRow(available_channel_selected_idx);

    if (member_channel_selected_idx >= 0)
        ui->memberTableView
            ->selectRow(member_channel_selected_idx);


    ui->availableChannelTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->availableChannelTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->availableChannelTableView->setColumnWidth(0, 50);

    ui->memberTableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->memberTableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->memberTableView->setColumnWidth(0, 50);
    
}
void RoamingZoneEditDialog::pushChannel(){
    if(ui->availableChannelTableView->selectionModel()->hasSelection()){
        auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
        if (!rows.isEmpty()) { available_channel_selected_idx = rows.first().row(); }
    }else if(available_channel_selected_idx > available_channels.size() - 1){
        return;
    }
    member_channels.push_back(available_channels.at(available_channel_selected_idx));
    available_channels.erase(available_channels.begin() + available_channel_selected_idx);
    member_channel_selected_idx = static_cast<int>(member_channels.size()) - 1;
    updateChannelTables();
    QTimer::singleShot(0, ui->memberTableView, &QTableView::scrollToBottom);
}
void RoamingZoneEditDialog::popChannel(){
    auto rows = ui->memberTableView->selectionModel()->selectedRows();
    if (!rows.isEmpty()) {
        member_channel_selected_idx = rows.first().row();
    } else if (member_channel_selected_idx >
               static_cast<int>(member_channels.size()) - 1) {
        return;
    }
    if (member_channel_selected_idx < 0 ||
        member_channel_selected_idx >= static_cast<int>(member_channels.size()))
        return;
    Anytone::RoamingChannel* ch = member_channels.at(member_channel_selected_idx);
    member_channels.erase(member_channels.begin() + member_channel_selected_idx);
    available_channels.push_back(ch);
    std::sort(available_channels.begin(), available_channels.end(),
              [](const Anytone::RoamingChannel* a, const Anytone::RoamingChannel* b) {
                  return a->id < b->id;
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
void RoamingZoneEditDialog::orderUp(){
    if(!ui->availableChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == 0) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::RoamingChannel* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx - 1), ch);
    member_channel_selected_idx = idx - 1;
    updateChannelTables();
}
void RoamingZoneEditDialog::orderDown(){
    if(!ui->availableChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == zone->channels.size() - 1) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::RoamingChannel* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx + 1), ch);
    member_channel_selected_idx = idx + 1;
    updateChannelTables();
}
void RoamingZoneEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::roaming_channels.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::roaming_channels.size() - 1);
}
void RoamingZoneEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void RoamingZoneEditDialog::saveClose(){
    save();
    close();
}