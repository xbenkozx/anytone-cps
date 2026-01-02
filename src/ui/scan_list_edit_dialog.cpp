#include <QStandardItemModel>
#include <QStandardItem>
#include <QTimer>
#include "scan_list_edit_dialog.h"
#include "ui_scan_edit_dialog.h"
#include "main_window.h"
#include "constants.h"

ScanListEditDialog::ScanListEditDialog(MainWindow *parent, int index) :
    QDialog(parent),
    ui(std::make_unique<Ui_ScanEditDialog>())
{
    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    
    this->index = index;
    main_window = parent;

    loadData();
    
}
ScanListEditDialog::~ScanListEditDialog(){}

void ScanListEditDialog::setupUI(){

    ui->priorityChannelSelectCmbx->addItems(Constants::SCAN_LIST_PRIORITY_CHANNEL_SELECT);
    ui->revertChannelCmbx->addItems(Constants::SCAN_LIST_REVERT_CHANNEL);
    ui->lookBackTimeACmbx->addItems(Constants::SCAN_LIST_LOOK_BACK_TIME);
    ui->lookBackTimeBCmbx->addItems(Constants::SCAN_LIST_LOOK_BACK_TIME);
    ui->dropoutDelayCmbx->addItems(Constants::SCAN_LIST_DROPOUT_DELAY_DWELL_TIME);
    ui->dwellTimeCmbx->addItems(Constants::SCAN_LIST_DROPOUT_DELAY_DWELL_TIME);

    connect(ui->pushChannelBtn, &QPushButton::clicked, this, &ScanListEditDialog::pushChannel);
    connect(ui->popChannelBtn, &QPushButton::clicked, this, &ScanListEditDialog::popChannel);
    connect(ui->orderIdBtn, &QPushButton::clicked, this, &ScanListEditDialog::orderMemberId);
    connect(ui->orderNameBtn, &QPushButton::clicked, this, &ScanListEditDialog::orderMemberName);
    connect(ui->orderUpBtn, &QPushButton::clicked, this, &ScanListEditDialog::orderUp);
    connect(ui->orderDownBtn, &QPushButton::clicked, this, &ScanListEditDialog::orderDown);
    connect(ui->orderAvailableIdBtn, &QPushButton::clicked, this, &ScanListEditDialog::orderAvailableId);
    connect(ui->orderAvailableNameBtn, &QPushButton::clicked, this, &ScanListEditDialog::orderAvailableName);
    connect(ui->okBtn, &QPushButton::clicked, this, &ScanListEditDialog::saveClose);
    connect(ui->cancelBtn, &QPushButton::clicked, this, &ScanListEditDialog::close);
    connect(ui->nextBtn, &QPushButton::clicked, this, &ScanListEditDialog::nextBtnClicked);
    connect(ui->prevBtn, &QPushButton::clicked, this, &ScanListEditDialog::prevBtnClicked);
    connect(ui->priorityChannelSelectCmbx, &QComboBox::currentIndexChanged, 
        this, &ScanListEditDialog::priorityChannelSelectChanged);

    updatePriorityChannelList();
}
void ScanListEditDialog::loadData(){
    setWindowTitle("Zone Edit---" + QString::number(index+1));
    scanlist = Anytone::Memory::scanlists.at(index);

    if(scanlist->channels.size() == 0) scanlist->name = "ScanList " + QString::number(index+1);

    available_channels.clear();
    for(Anytone::Channel *ch : Anytone::Memory::channels){
        if(ch->rx_frequency > 0 && scanlist->channels.indexOf(ch) == -1) available_channels.push_back(ch);
    }

    member_channels = scanlist->channels;

    setupUI();
    updateChannelTables();

    ui->nameTxt->setText(scanlist->name);
    ui->priorityChannelSelectCmbx->setCurrentIndex(scanlist->priority_channel_select);
    
    if(scanlist->priority_channel_1 == 0xffff){
        ui->priorityChannel1Cmbx->setCurrentIndex(0);
    }else if(scanlist->priority_channel_1 == 0){
        ui->priorityChannel1Cmbx->setCurrentIndex(1);
    }else{
        ui->priorityChannel1Cmbx->setCurrentIndex(scanlist->priority_channel_1 + 1);
    }

    if(scanlist->priority_channel_2 == 0xffff){
        ui->priorityChannel2Cmbx->setCurrentIndex(0);
    }else if(scanlist->priority_channel_2 == 0){
        ui->priorityChannel2Cmbx->setCurrentIndex(1);
    }else{
        ui->priorityChannel2Cmbx->setCurrentIndex(scanlist->priority_channel_2 + 1);
    }

    ui->revertChannelCmbx->setCurrentIndex(scanlist->revert_channel);
    ui->lookBackTimeACmbx->setCurrentIndex(scanlist->lookback_time_a);
    ui->lookBackTimeBCmbx->setCurrentIndex(scanlist->lookback_time_b);
    ui->dropoutDelayCmbx->setCurrentIndex(scanlist->dropout_delay_time);
    ui->dwellTimeCmbx->setCurrentIndex(scanlist->dwell_time);

    priorityChannelSelectChanged();
}
void ScanListEditDialog::save(){
    scanlist->name = ui->nameTxt->text();
    scanlist->channels = member_channels;

    int priority_channel_1 = ui->priorityChannel1Cmbx->currentIndex();
    if(priority_channel_1 == 0){
        scanlist->priority_channel_1 = 0xffff;
    }else if(priority_channel_1 == 1){
        scanlist->priority_channel_1 = 0;
    }else{
        scanlist->priority_channel_1 = priority_channel_1 - 1;
    }

    int priority_channel_2 = ui->priorityChannel2Cmbx->currentIndex();
    if(priority_channel_2 == 0){
        scanlist->priority_channel_2 = 0xffff;
    }else if(priority_channel_2 == 1){
        scanlist->priority_channel_2 = 0;
    }else{
        scanlist->priority_channel_2 = priority_channel_2 - 1;
    }

    scanlist->priority_channel_2 = ui->priorityChannel2Cmbx->currentIndex();
    scanlist->revert_channel = ui->revertChannelCmbx->currentIndex();
    scanlist->lookback_time_a = ui->lookBackTimeACmbx->currentIndex();
    scanlist->lookback_time_b = ui->lookBackTimeBCmbx->currentIndex();
    scanlist->dropout_delay_time = ui->dropoutDelayCmbx->currentIndex();
    scanlist->dwell_time = ui->dwellTimeCmbx->currentIndex();
    scanlist->channels = member_channels;

    main_window->listScanLists(false);
}
void ScanListEditDialog::orderAvailableId(){
    orderAvailable(0);
}
void ScanListEditDialog::orderAvailableName(){
    orderAvailable(1);
}
void ScanListEditDialog::orderAvailable(int sort_type){
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
void ScanListEditDialog::orderMemberId(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
            [](const Anytone::Channel* a, const Anytone::Channel* b) {
                return a->id < b->id;
            });
}
void ScanListEditDialog::orderMemberName(){
    std::stable_sort(member_channels.begin(), member_channels.end(),
        [](const Anytone::Channel* a, const Anytone::Channel* b) {
            return a->name < b->name;
        });
}
void ScanListEditDialog::updateChannelTables(){
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

    updatePriorityChannelList();
}
void ScanListEditDialog::pushChannel(){
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
void ScanListEditDialog::popChannel(){
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
void ScanListEditDialog::orderUp(){
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
void ScanListEditDialog::orderDown(){
    if(!ui->availableChannelTableView->selectionModel()->hasSelection()) return;
    auto rows = ui->availableChannelTableView->selectionModel()->selectedRows();
    int idx = rows.first().row();
    if(idx == scanlist->channels.size() - 1) return;
    if (idx <= 0 || idx >= static_cast<int>(member_channels.size()))
        return;
        
    Anytone::Channel* ch = member_channels.at(idx);
    member_channels.erase(member_channels.begin() + idx);
    member_channels.insert(member_channels.begin() + (idx + 1), ch);
    member_channel_selected_idx = idx + 1;
    updateChannelTables();
}
void ScanListEditDialog::nextBtnClicked(){
    save();
    if(index < Anytone::Memory::channels.size() - 2){
        index++;
        loadData();
    }

    ui->prevBtn->setDisabled(false);
    ui->nextBtn->setDisabled(index == Anytone::Memory::channels.size() - 1);
}
void ScanListEditDialog::prevBtnClicked(){
    save();
    if(index > 0){
        index -= 1;
        loadData();
    }
    ui->prevBtn->setDisabled(index==0);
    ui->nextBtn->setDisabled(false);
}
void ScanListEditDialog::saveClose(){
    save();
    close();
}
void ScanListEditDialog::updatePriorityChannelList(){
    QString priority_channel_1_txt = ui->priorityChannel1Cmbx->currentText();
    QString priority_channel_2_txt = ui->priorityChannel2Cmbx->currentText();
    QStringList priority_channel_list = Constants::SCAN_LIST_PRIORITY_CHANNEL;
    for(Anytone::Channel *ch : member_channels){
        priority_channel_list.push_back(ch->name);
    }
    ui->priorityChannel1Cmbx->clear();
    ui->priorityChannel2Cmbx->clear();
    ui->priorityChannel1Cmbx->addItems(priority_channel_list);
    ui->priorityChannel2Cmbx->addItems(priority_channel_list);
    int idx_a = priority_channel_list.indexOf(priority_channel_1_txt);
    if(idx_a != -1 ) ui->priorityChannel1Cmbx->setCurrentIndex(idx_a);
    int idx_b = priority_channel_list.indexOf(priority_channel_2_txt);
    if(idx_b != -1 ) ui->priorityChannel2Cmbx->setCurrentIndex(idx_b);
}
void ScanListEditDialog::priorityChannelSelectChanged(){
    int idx = ui->priorityChannelSelectCmbx->currentIndex();
    switch(idx){
        case 0:
            ui->priorityChannel1Cmbx->setDisabled(true);
            ui->priorityChannel2Cmbx->setDisabled(true);
            break;
        case 1:
            ui->priorityChannel1Cmbx->setDisabled(false);
            ui->priorityChannel2Cmbx->setDisabled(true);
            break;
        case 2:
            ui->priorityChannel1Cmbx->setDisabled(true);
            ui->priorityChannel2Cmbx->setDisabled(false);
            break;
        case 3:
            ui->priorityChannel1Cmbx->setDisabled(false);
            ui->priorityChannel2Cmbx->setDisabled(false);
            break;
        default:
            break;
    }
}
