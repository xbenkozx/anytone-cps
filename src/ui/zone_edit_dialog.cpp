#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include "zone_edit_dialog.h"
#include "ui_zone_edit_dialog.h"
#include "main_window.h"

ZoneEditDialog::ZoneEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_ZoneEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    
    this->index = index;
    main_window = parent;

    available_channels = {};
    member_channels = {};

    setupUI();
    loadData();
    
}
ZoneEditDialog::~ZoneEditDialog(){}

void ZoneEditDialog::setupUI(){
    connect(ui->pushChannelBtn, &QPushButton::clicked, this, &ZoneEditDialog::pushChannel);
    connect(ui->popChannelBtn, &QPushButton::clicked, this, &ZoneEditDialog::popChannel);
    connect(ui->orderIdBtn, &QPushButton::clicked, this, &ZoneEditDialog::orderMemberId);
    connect(ui->orderNameBtn, &QPushButton::clicked, this, &ZoneEditDialog::orderMemberName);
    connect(ui->orderUpBtn, &QPushButton::clicked, this, &ZoneEditDialog::orderUp);
    connect(ui->orderDownBtn, &QPushButton::clicked, this, &ZoneEditDialog::orderDown);
    connect(ui->orderAvailableIdBtn, &QPushButton::clicked, this, &ZoneEditDialog::orderAvailableId);
    connect(ui->orderAvailableNameBtn, &QPushButton::clicked, this, &ZoneEditDialog::orderAvailableName);
    connect(ui->okBtn, &QPushButton::clicked, this, &ZoneEditDialog::saveClose);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &ZoneEditDialog::close);
    connect(ui->nextBtn, &QPushButton::clicked, this, &ZoneEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &ZoneEditDialog::prevBtnClicked);

    updateChannelSelectLists();
}
void ZoneEditDialog::loadData(){
    setWindowTitle("Zone Edit---" + QString::number(index+1));
    zone = Anytone::Memory::zones.at(index);

    if(zone->channels.size() == 0) zone->name = "Zone " + QString::number(index+1);

    available_channels.clear();
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency > 0 && zone->channels.indexOf(ch) == -1) available_channels.push_back(ch);
    }

    member_channels = zone->channels;

    updateChannelTables();

    ui->nameTxt->setText(zone->name);
    ui->aChannelCmbx->setCurrentIndex(zone->a_channel_idx);
    ui->bChannelCmbx->setCurrentIndex(zone->b_channel_idx);
    ui->zoneHideChbx->setChecked(zone->hide);
}
void ZoneEditDialog::save(){
    zone->name = ui->nameTxt->text();
    zone->channels = member_channels;
    zone->hide = ui->zoneHideChbx->isChecked();
    zone->a_channel_idx = ui->aChannelCmbx->currentIndex();
    zone->b_channel_idx = ui->bChannelCmbx->currentIndex();
    zone->a_channel = zone->channels.at(zone->a_channel_idx);
    zone->b_channel = zone->channels.at(zone->b_channel_idx);

    main_window->listZones(false);
}
void ZoneEditDialog::orderAvailableId(){
    orderAvailable(0);
}
void ZoneEditDialog::orderAvailableName(){
    orderAvailable(1);
}
void ZoneEditDialog::orderAvailable(int sort_type){
    if(sort_type == 0){
        std::stable_sort(available_channels.begin(), available_channels.end(),
            [](const Anytone::Channel* a, const Anytone::Channel* b) {
                return a->id < b->id;
            });
    }else{
        std::stable_sort(available_channels.begin(), available_channels.end(),
            [](const Anytone::Channel* a, const Anytone::Channel* b) {
                return a->name < b->name;
            });
    }
    updateChannelTables();
}
void ZoneEditDialog::orderMemberId(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
            [](const Anytone::Channel* a, const Anytone::Channel* b) {
                return a->id < b->id;
            });
}
void ZoneEditDialog::orderMemberName(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
        [](const Anytone::Channel* a, const Anytone::Channel* b) {
            return a->name < b->name;
        });
}
void ZoneEditDialog::updateChannelTables(){
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

    updateChannelSelectLists();
}
void ZoneEditDialog::pushChannel(){
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
void ZoneEditDialog::popChannel(){
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
    Anytone::Channel* ch = member_channels.at(member_channel_selected_idx);
    member_channels.erase(member_channels.begin() + member_channel_selected_idx);
    available_channels.push_back(ch);
    std::sort(available_channels.begin(), available_channels.end(),
              [](const Anytone::Channel* a, const Anytone::Channel* b) {
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
void ZoneEditDialog::orderUp(){
    if(!ui->availableChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == 0) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::Channel* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx - 1), ch);
    member_channel_selected_idx = idx - 1;
    updateChannelTables();
}
void ZoneEditDialog::orderDown(){
    if(!ui->availableChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == zone->channels.size() - 1) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::Channel* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx + 1), ch);
    member_channel_selected_idx = idx + 1;
    updateChannelTables();
}
void ZoneEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::zones.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::zones.size() - 1);
}
void ZoneEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void ZoneEditDialog::saveClose(){
    save();
    close();
}
void ZoneEditDialog::updateChannelSelectLists(){
    QString channel_a_txt = ui->aChannelCmbx->currentText();
    QString channel_b_txt = ui->bChannelCmbx->currentText();
    QStringList channel_list = {};
    for(Anytone::Channel *ch : member_channels){
        channel_list.push_back(ch->name);
    }
    ui->aChannelCmbx->clear();
    ui->bChannelCmbx->clear();
    ui->aChannelCmbx->addItems(channel_list);
    ui->bChannelCmbx->addItems(channel_list);
    int idx_a = channel_list.indexOf(channel_a_txt);
    if(idx_a != -1 ) ui->aChannelCmbx->setCurrentIndex(idx_a);
    int idx_b = channel_list.indexOf(channel_b_txt);
    if(idx_b != -1 ) ui->bChannelCmbx->setCurrentIndex(idx_b);
}
