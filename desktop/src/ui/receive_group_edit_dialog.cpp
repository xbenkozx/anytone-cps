
#include <algorithm> 
#include "receive_group_edit_dialog.h"
#include "ui_receive_group_edit_dialog.h"
#include "memory/anytone_memory.h"
#include "main_window.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include <QMessageBox>


ReceiveGroupEditDialog::ReceiveGroupEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_ReceiveGroupEditDialog>())
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
ReceiveGroupEditDialog::~ReceiveGroupEditDialog(){}

void ReceiveGroupEditDialog::setupUI(){
    connect(ui->pushChannelBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::pushChannel);
    connect(ui->popChannelBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::popChannel);
    connect(ui->orderIdBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::orderMemberId);
    connect(ui->orderNameBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::orderMemberName);
    connect(ui->orderUpBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::orderUp);
    connect(ui->orderDownBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::orderDown);
    connect(ui->orderAvailableIdBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::orderAvailableId);
    connect(ui->orderAvailableNameBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::orderAvailableName);
    connect(ui->okBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::saveClose);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::close);
    connect(ui->nextBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &ReceiveGroupEditDialog::prevBtnClicked);
}
void ReceiveGroupEditDialog::loadData(){
    setWindowTitle("Receive Group Edit---" + QString::number(index+1));
    group = Anytone::Memory::receive_group_call_lists.at(index);

    if(group->talkgroups.size() == 0 && group->name.isEmpty()) group->name = "Receive Group " + QString::number(index+1);

    available_channels.clear();
    for(Anytone::Talkgroup *ch : Anytone::Memory::talkgroups){
        if(!ch->name.isEmpty() && std::find(group->talkgroups.begin(), group->talkgroups.end(), ch) == group->talkgroups.end()) available_channels.push_back(ch);
    }

    member_channels = QVector<Anytone::Talkgroup*>(group->talkgroups.begin(), group->talkgroups.end());

    updateChannelTables();

    ui->nameTxt->setText(group->name);
}
void ReceiveGroupEditDialog::save(){
    group->name = ui->nameTxt->text();
    group->talkgroups = std::vector<Anytone::Talkgroup*>(member_channels.begin(), member_channels.end());
}
void ReceiveGroupEditDialog::orderAvailableId(){
    orderAvailable(0);
}
void ReceiveGroupEditDialog::orderAvailableName(){
    orderAvailable(1);
}
void ReceiveGroupEditDialog::orderAvailable(int sort_type){
    if(sort_type == 0){
        std::stable_sort(available_channels.begin(), available_channels.end(),
            [](const Anytone::Talkgroup* a, const Anytone::Talkgroup* b) {
                return a->id < b->id;
            });
    }else{
        std::stable_sort(available_channels.begin(), available_channels.end(),
            [](const Anytone::Talkgroup* a, const Anytone::Talkgroup* b) {
                return a->name < b->name;
            });
    }
    updateChannelTables();
}
void ReceiveGroupEditDialog::orderMemberId(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
            [](const Anytone::Talkgroup* a, const Anytone::Talkgroup* b) {
                return a->id < b->id;
            });
    updateChannelTables();
}
void ReceiveGroupEditDialog::orderMemberName(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
        [](const Anytone::Talkgroup* a, const Anytone::Talkgroup* b) {
            return a->name < b->name;
        });
    updateChannelTables();
}
void ReceiveGroupEditDialog::updateChannelTables(){
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
void ReceiveGroupEditDialog::pushChannel(){
    if(ui->availableChannelTableView->selectionModel()->hasSelection()){
        auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
        if (!rows.isEmpty()) { available_channel_selected_idx = rows.first().row(); }
    }else if(available_channel_selected_idx > available_channels.size() - 1){
        return;
    }
    if(member_channels.size() >= 64){
        QMessageBox::warning(this, tr("Receive Group"), tr("A receive group can hold at most 64 talk groups."));
        return;
    }
    if(available_channel_selected_idx < 0 || available_channel_selected_idx >= available_channels.size()) return;
    member_channels.push_back(available_channels.at(available_channel_selected_idx));
    available_channels.erase(available_channels.begin() + available_channel_selected_idx);
    member_channel_selected_idx = static_cast<int>(member_channels.size()) - 1;
    updateChannelTables();
    QTimer::singleShot(0, ui->memberTableView, &QTableView::scrollToBottom);
}
void ReceiveGroupEditDialog::popChannel(){
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
    Anytone::Talkgroup* ch = member_channels.at(member_channel_selected_idx);
    member_channels.erase(member_channels.begin() + member_channel_selected_idx);
    available_channels.push_back(ch);
    std::sort(available_channels.begin(), available_channels.end(),
              [](const Anytone::Talkgroup* a, const Anytone::Talkgroup* b) {
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
void ReceiveGroupEditDialog::orderUp(){
    if(!ui->memberTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->memberTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == 0) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::Talkgroup* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx - 1), ch);
    member_channel_selected_idx = idx - 1;
    updateChannelTables();
}
void ReceiveGroupEditDialog::orderDown(){
    if(!ui->memberTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->memberTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if (idx < 0 || idx >= static_cast<int>(member_channels.size()) - 1)
        return;
        
    Anytone::Talkgroup* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx + 1), ch);
    member_channel_selected_idx = idx + 1;
    updateChannelTables();
}
void ReceiveGroupEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::receive_group_call_lists.size() - 1){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::receive_group_call_lists.size() - 1);
}
void ReceiveGroupEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void ReceiveGroupEditDialog::saveClose(){
    save();
    close();
}