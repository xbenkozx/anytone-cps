#include <QSaveFile>
#include "main_window.h"
#include "ui_main_window.h"
#include "memory/memory.h"

#include "user_settings.h"
#include "device.h"
#include <QSerialPortInfo>
#include <QLocale>
#include <QMenu>
#include "channel_table_model.h"
#include "zone_table_model.h"
#include "talkgroup_table_model.h"
#include "scanlist_table_model.h"
#include "radioid_table_model.h"
#include "roaming_zone_table_model.h"
#include "roaming_channel_table_model.h"
#include "fm_table_model.h"
#include "auto_repeater_table_model.h"
#include "digital_contacts_table_model.h"
#include "gps_roaming_table_model.h"
#include "prefabricated_sms_table_model.h"
#include "receive_group_call_table_model.h"
#include "aes_encryption_table_model.h"

#include "aes_encryption_code_dialog.h"
#include "alert_settings_dialog.h"
#include "aprs_settings_dialog.h"
#include "auto_repeater_edit_dialog.h"
#include "channel_edit_dialog.h"
#include "device_information_dialog.h"
#include "gps_roaming_edit_dialog.h"
#include "local_information_dialog.h"
#include "master_id_dialog.h"
#include "optional_settings_dialog.h"
#include "prefabricated_sms_edit_dialog.h"
#include "roaming_channel_edit_dialog.h"
#include "roaming_zone_edit_dialog.h"
#include "scan_list_edit_dialog.h"
#include "zone_edit_dialog.h"
#include "image_dialog.h"
#include "fm_edit_dialog.h"
#include "tone2_settings_dialog.h"
#include "tone5_settings_dialog.h"
#include "dtmf_settings_dialog.h"
#include "talk_alias_settings_dialog.h"
#include "expert_options_dialog.h"
#include "radio_id_edit_dialog.h"
#include "scan_edit_dialog.h"
#include "hotkey_settings_dialog.h"
#include "talkgroup_edit_dialog.h"
#include "hotkey_settings_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(std::make_unique<Ui_MainWindow>())
{
    ui->setupUi(this);
    Anytone::Memory::init();
    UserSettings::load();

    Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII;
    updateRadioModel();

    // Setup Dialogs

    threadpool = QThreadPool::globalInstance();
    selected_table_view = "Channel";

    setupUI();
    
    listChannels();

    // readFromRadio();
}

MainWindow::~MainWindow(){}

void MainWindow::setupUI(){
    loading_dialog = new LoadingDialog(this);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);

    connect(ui->actionD878UVII, &QAction::triggered, this, &MainWindow::setRadioModel_D878UVII);
    connect(ui->actionD890UV, &QAction::triggered, this, &MainWindow::setRadioModel_D890UV);
    connect(ui->actionSet_Com, &QAction::triggered, this, &MainWindow::showComportDialog);
    connect(ui->actionSet_Com, &QAction::triggered, this, &MainWindow::showComportDialog);
    connect(ui->actionSet_Com, &QAction::triggered, this, &MainWindow::showComportDialog);

    connect(ui->actionBoot_Image, &QAction::triggered, this, &MainWindow::showBootImageDialog);
    connect(ui->actionStandby_BK_Picture_1, &QAction::triggered, this, &MainWindow::showBK1ImageDialog);
    connect(ui->actionStandby_Bk_Picture_2, &QAction::triggered, this, &MainWindow::showBK2ImageDialog);
    connect(ui->actionExpert_Options, &QAction::triggered, this, &MainWindow::showExpertOptions);   

    connect(ui->openFileBtn, &QToolButton::clicked, this, &MainWindow::openFile);
    connect(ui->saveFileBtn, &QToolButton::clicked, this, &MainWindow::saveFile);
        
    connect(ui->mainTreeWidget, &QTreeWidget::itemClicked, this, &MainWindow::onTreeItemClicked);
    connect(ui->comPortBtn, &QToolButton::clicked, this, &MainWindow::showComportDialog);
    connect(ui->readRadioBtn, &QToolButton::clicked, this, &MainWindow::showReadOptionsDialog);
    connect(ui->writeRadioBtn, &QToolButton::clicked, this, &MainWindow::showWriteOptionsDialog);
    connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::onMainTableDblClicked);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &MainWindow::showMainTableContextMenu);

    channel_copy_shortcut = new QShortcut(QKeySequence(Qt::Modifier::CTRL | Qt::Key::Key_C), ui->tableView);
    channel_cut_shortcut = new QShortcut(QKeySequence(Qt::Modifier::CTRL | Qt::Key::Key_X), ui->tableView);
    channel_paste_shortcut = new QShortcut(QKeySequence(Qt::Modifier::CTRL | Qt::Key::Key_V), ui->tableView);
    channel_undo_shortcut = new QShortcut(QKeySequence(Qt::Modifier::CTRL | Qt::Key::Key_Z), ui->tableView);
    channel_redo_shortcut = new QShortcut(QKeySequence(Qt::Modifier::CTRL | Qt::Modifier::SHIFT | Qt::Key::Key_Z), ui->tableView);
    channel_delete_shortcut = new QShortcut(QKeySequence(Qt::Key::Key_Delete), ui->tableView);
    channel_edit_shortcut = new QShortcut(QKeySequence(Qt::Key::Key_Return), ui->tableView);

    
    connect(channel_copy_shortcut, &QShortcut::activated, this, &MainWindow::copySelectedChannels);
    connect(channel_cut_shortcut, &QShortcut::activated, this, &MainWindow::cutSelectedChannels);
    connect(channel_paste_shortcut, &QShortcut::activated, this, &MainWindow::pasteSelectedChannels);
    connect(channel_undo_shortcut, &QShortcut::activated, this, &MainWindow::undoChannels);
    connect(channel_redo_shortcut, &QShortcut::activated, this, &MainWindow::redoChannels);
    connect(channel_delete_shortcut, &QShortcut::activated, this, &MainWindow::deleteSelectedChannels);
    connect(channel_edit_shortcut, &QShortcut::activated, this, &MainWindow::editChannel);;
}
void MainWindow::setupTreeView(){
    QVector<QPair<QString, QStringList>> tree_settings = {};
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII:
            tree_settings = d878uvii_tree_settings;
            break;
        case Anytone::RadioModel::D890UV:
            tree_settings = d890uv_tree_settings;
            break;
        default:
            break;
        
    }
    // Setup Settings Tree
    ui->mainTreeWidget->clear();
    for (const auto& [key, values] : tree_settings) {
        auto* mainTreeItem = new QTreeWidgetItem(ui->mainTreeWidget, QStringList{ key });
        for (const auto& value : values) {
            auto* sub_item = new QTreeWidgetItem(mainTreeItem, QStringList{ value });
            if(value == "Digital Contact List"){
                for(int i = 0; i < 500000; i+=20000){
                    QLocale systemLocale = QLocale::system();
                    QString title = systemLocale.toString(i+1) + "---" + systemLocale.toString(i+20000);
                    auto* dcl_item = new QTreeWidgetItem(sub_item, QStringList{ title });
                    dcl_item->setText(1, value);
                    dcl_item->setData(0, Qt::UserRole, i);
                }
            }else if(value == "Repeater Whitelist"){
                new QTreeWidgetItem(sub_item, QStringList{ "Talk Group Whitelist" });
                new QTreeWidgetItem(sub_item, QStringList{ "Digital Contact Whitelist" });
            }
        }
        mainTreeItem->setExpanded(true);
    }
}

void MainWindow::copySelectedChannels(){
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selected_indexes.size() == 0) return;

    QVector<int> index_list;

    for(QModelIndex index : selected_indexes){
        if(index_list.indexOf(index.row()) == -1) index_list.append(index.row());
    }

    for(int i : index_list){
        channel_clipboard.push_back(Anytone::Memory::channels.at(i));
    }
}
void MainWindow::cutSelectedChannels(){
    qDebug() << "Cut";
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selected_indexes.size() == 0) return;

    QVector<int> index_list;

    for(QModelIndex index : selected_indexes){
        ui->tableView->model()->setData(
            index,
            QBrush(Qt::lightGray),
            Qt::ForegroundRole
        );
        if(index_list.indexOf(index.row()) == -1) index_list.append(index.row());
    }

    for(int i : index_list){
        channel_clipboard.push_back(Anytone::Memory::channels.at(i));
    }

    ui->tableView->clearSelection();
}
void MainWindow::pasteSelectedChannels(){
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selected_indexes.size() == 0) return;
    
    updateMemoryChannelHistory();
    
    int selected_row = selected_indexes[0].row();

    for(int i = 0; i < channel_clipboard.size(); i++){
        Anytone::Channel *ch = channel_clipboard.at(i);
        Anytone::Memory::channels.at(selected_row+i)->copy(ch);
        ch->clear();
    }
    channel_clipboard.clear();
    listChannels(false);
}
void MainWindow::deleteSelectedChannels(){
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selected_indexes.size() == 0) return;
    
    updateMemoryChannelHistory();
    
    QVector<int> index_list;

    for(QModelIndex index : selected_indexes){
        ui->tableView->model()->setData(index, QColor("silver"), Qt::ForegroundRole);
        if(index_list.indexOf(index.row()) == -1) index_list.append(index.row());
    }

    for(int i : index_list){
        Anytone::Memory::channels.at(i)->clear();
    }

    listChannels(false);
}
void MainWindow::undoChannels(){
    // # add current state
    // if self.channel_change_index == len(self.channel_change_history):
    //     print('deepcopy')
    //     self.channel_current_copy = copy.deepcopy(self.memory.channels)

    // if self.channel_change_index > 0:
    //     self.channel_change_index -= 1
    // self.memory.channels = self.channel_change_history[self.channel_change_index]
    // self.listMemoryChannels(False)
}
void MainWindow::redoChannels(){
    // if len(self.channel_change_history) == 0:
    //     return
    
    // self.data_saved = False

    // if self.channel_change_index < len(self.channel_change_history) - 1:
    //     self.channel_change_index += 1
    //     self.memory.channels = self.channel_change_history[self.channel_change_index]
    // elif self.channel_change_index == len(self.channel_change_history) - 1:
    //     self.channel_change_index += 1
    //     self.memory.channels = self.channel_current_copy

    // self.listMemoryChannels(False)
}
void MainWindow::updateMemoryChannelHistory(){
    // del self.channel_change_history[self.channel_change_index:]
    // channel_change_history.append(copy.deepcopy(self.memory.channels))
    // channel_change_index += 1
}
void MainWindow::editChannel(){
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selected_indexes.size() == 0) return;

    int index = selected_indexes.at(0).row();
    showChannelEditDialog(index);
}

void MainWindow::updateRadioModel(){
    setupTreeView();
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII:
            setWindowTitle("Anytone D878UVII CPS - 4.00");
            break;
        case Anytone::RadioModel::D890UV:
            setWindowTitle("Anytone D878UVII CPS - 4.00");
            break;
        default:
            break;
    }
}
void MainWindow::setRadioModel_D878UVII(){
    ui->actionD878UVII->setChecked(true);
    ui->actionD890UV->setChecked(false);
    Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII;
    updateRadioModel();
}
void MainWindow::setRadioModel_D890UV(){
    ui->actionD878UVII->setChecked(false);
    ui->actionD890UV->setChecked(true);
    Anytone::Memory::radio_model = Anytone::RadioModel::D890UV;
    updateRadioModel();
}
void MainWindow::listChannels(bool goto_top){
    delete table_model;
    table_model = new ChannelTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 100);
    ui->tableView->setColumnWidth(4, 50);
    ui->tableView->setColumnWidth(5, 50);
    ui->tableView->setColumnWidth(6, 100);
    ui->tableView->setColumnWidth(7, 100);
    ui->tableView->setColumnWidth(8, 200);
    ui->tableView->setColumnWidth(9, 150);
    ui->tableView->setColumnWidth(10, 100);
    ui->tableView->setColumnWidth(11, 100);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listZones(bool goto_top){
    delete table_model;
    table_model = new ZoneTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 200);
    ui->tableView->setColumnWidth(4, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listTalkgroups(bool goto_top){
    delete table_model;
    table_model = new TalkgroupTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 200);
    ui->tableView->setColumnWidth(4, 100);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listScanLists(bool goto_top){
    delete table_model;
    table_model = new ScanListTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 70);
    ui->tableView->setColumnWidth(3, 120);
    ui->tableView->setColumnWidth(4, 120);
    ui->tableView->setColumnWidth(5, 120);
    ui->tableView->setColumnWidth(6, 120);
    ui->tableView->setColumnWidth(7, 120);
    ui->tableView->setColumnWidth(8, 120);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listRadioIds(bool goto_top){
    delete table_model;
    table_model = new RadioIdTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 70);
    ui->tableView->setColumnWidth(2, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listRoamingZones(bool goto_top){
    delete table_model;
    table_model = new RoamingZoneTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 70);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listRoamingChannels(bool goto_top){
    delete table_model;
    table_model = new RoamingChannelTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 70);
    ui->tableView->setColumnWidth(4, 70);
    ui->tableView->setColumnWidth(5, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listFmChannels(bool goto_top){
    delete table_model;
    table_model = new FmTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 70);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listAutoRepeaterFrequencies(bool goto_top){
    delete table_model;
    table_model = new AutoRepeaterTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 150);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listDigitalContact(int page_index, bool goto_top){
    delete table_model;
    table_model = new DigitalContactsTableModel(this, page_index);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 100);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 150);
    ui->tableView->setColumnWidth(4, 150);
    ui->tableView->setColumnWidth(5, 100);
    ui->tableView->setColumnWidth(6, 100);
    ui->tableView->setColumnWidth(7, 150);
    ui->tableView->setColumnWidth(8, 150);
    ui->tableView->setColumnWidth(9, 150);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listGpsRoaming(bool goto_top){
    delete table_model;
    table_model = new GpsRoamingTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 100);
    ui->tableView->setColumnWidth(4, 100);
    ui->tableView->setColumnWidth(5, 100);
    ui->tableView->setColumnWidth(6, 100);
    ui->tableView->setColumnWidth(7, 100);
    ui->tableView->setColumnWidth(8, 100);
    ui->tableView->setColumnWidth(9, 100);
    ui->tableView->setColumnWidth(10, 100);
    ui->tableView->setColumnWidth(11, 100);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listPrefabricatedSms(bool goto_top){
    delete table_model;
    table_model = new PrefabricatedSmsTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 800);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listReceiveGroupCall(bool goto_top){
    delete table_model;
    table_model = new ReceiveGroupCallTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 50);
    ui->tableView->setColumnWidth(1, 200);
    ui->tableView->setColumnWidth(2, 70);
    ui->tableView->setColumnWidth(3, 800);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listAesEncryptionKeys(bool goto_top){
    delete table_model;
    table_model = new AesEncryptionTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 600);

    if(goto_top) ui->tableView->scrollToTop();
}

void MainWindow::showComportDialog(){
    comport_dialog = std::make_unique<ComportDialog>(this);
    comport_dialog->show();
}
void MainWindow::showReadOptionsDialog(){
    rwo_dialog = std::make_unique<ReadWriteOptionsDialog>(this);
    rwo_dialog->is_write = false;
    rwo_dialog->show();
}
void MainWindow::showWriteOptionsDialog(){
    rwo_dialog = std::make_unique<ReadWriteOptionsDialog>(this);
    rwo_dialog->is_write = true;
    rwo_dialog->show();
}
void MainWindow::showAesEncryptionDialog(int index){
    AesEncryptionCodeDialog aes_encryption_dialog(this, index);
    aes_encryption_dialog.exec();
    
}
void MainWindow::showAlertSettingsDialog(){
    AlertSettingsDialog alert_settings_dialog(this);
    alert_settings_dialog.exec();
}
void MainWindow::showAprsSettingsDialog(){
    AprsSettingsDialog aprs_settings_dialog(this);
    aprs_settings_dialog.exec();
}
void MainWindow::showAutoRepeaterEditDialog(int index){
    AutoRepeaterEditDialog auto_repeater_edit_dialog(this, index);
    auto_repeater_edit_dialog.exec();
    
}
void MainWindow::showChannelEditDialog(int index){
    ChannelEditDialog channel_edit_dialog(this, index);
    channel_edit_dialog.exec();
}
void MainWindow::showDeviceInformationDialog(){
    DeviceInformationDialog dialog(this);
    dialog.exec();
}
void MainWindow::showDtmfSettingsDialog(){
    DtmfSettingsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showExpertOptions(){
    ExpertOptionsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showFmEditDialog(int index){
    FmEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showGpsRoaming(int index){
    GpsRoamingEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showLocalInformationDialog(){
    LocalInformationDialog dialog(this);
    dialog.exec();
}
void MainWindow::showHotKeyDialog(){
    HotKeySettingsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showMasterIdDialog(){
    MasterIdDialog dialog(this);
    dialog.exec();
}
void MainWindow::showOptionalSettingsDialog(){
    OptionalSettingsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showPrefabricatesSmsEditDialog(int index){
    PrefabricatedSmsEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showRadioIdEditDialog(int index){
    RadioIdEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showRoamingChannelEditDialog(int index){
    RoamingChannelEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showRoamingZoneEditDialog(int index){
    RoamingZoneEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showScanListEditDialog(int index){
    ScanListEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showTalkAliasSettingsDialog(){
    TalkAliasSettingsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showTalkgroupEditDialog(int index){
    TalkgroupEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showTone2SettingsDialog(){
    Tone2SettingsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showTone5SettingsDialog(){
    Tone5SettingsDialog dialog(this);
    dialog.exec();
}
void MainWindow::showZoneEditDialog(int index){
    ZoneEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showBootImageDialog(){
    ImageDialog dialog(this, DeviceRWType::BOOT_IMAGE);
    dialog.exec();
}
void MainWindow::showBK1ImageDialog(){
    ImageDialog dialog(this, DeviceRWType::BK1_IMAGE);
    dialog.exec();
}
void MainWindow::showBK2ImageDialog(){
    ImageDialog dialog(this, DeviceRWType::BK2_IMAGE);
    dialog.exec();
}

void MainWindow::readFromRadio(){
    if(UserSettings::comport.size() == 0){
        qDebug() << "Error: Comport not set";
        return;
    }

    if(UserSettings::comport != QString("VIRTUAL")){
        bool com_connected = false;
        const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &portInfo : serialPortInfos) {
            if(UserSettings::comport == portInfo.portName()) com_connected = true;
        }
        if(!com_connected){
            BasicDialog bd1(this, "Error connecting to device", "Read From Radio");
            bd1.exec();
            return;
        }
    }

    loading_dialog->setWindowTitle("Radio Read");
    loading_dialog->show();

    // if(adw != nullptr) delete adw;
    adw = new SerialWorker();
    if(UserSettings::comport == QString("VIRTUAL")){
        adw->setVirtualFile(UserSettings::virtual_file_name);
    }else{
        adw->setComport(UserSettings::comport);
    }
    adw->setReadWriteOptions(UserSettings::read_write_options);
    QObject::connect(adw, &SerialWorker::update1, loading_dialog, &LoadingDialog::updateMainbar);
    QObject::connect(adw, &SerialWorker::update2, loading_dialog, &LoadingDialog::updateSubbar);
    QObject::connect(adw, &SerialWorker::finished, this, &MainWindow::readFromRadioFinished, Qt::QueuedConnection);
    threadpool->start(adw);
}
void MainWindow::readFromRadioFinished(const int &result){
    loading_dialog->close();
    showList();

    RetryConnectionDialog retry_dialog(this);
    retry_dialog.is_write = false;
    BasicDialog bd1(this, "Invalid Radio Model or Version", "Read From Radio");
    BasicDialog bd2(this, "Read Complete", "Read From Radio");

    switch(result){
        case DeviceStatus::STATUS_COM_ERROR:
            retry_dialog.exec();
            break;
        case DeviceStatus::STATUS_DEVICE_MISMATCH:
            bd1.exec();
            break;
        default:
            updateRadioModel();
            bd2.exec();
            // saveFile();
            break;          
    }
    
    
}
void MainWindow::writeToRadio(){
    if(UserSettings::comport.size() == 0){
        qDebug() << "Error: Comport not set";
        return;
    }

    if(UserSettings::comport != QString("VIRTUAL")){
        bool com_connected = false;
        const QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
        for (const QSerialPortInfo &portInfo : serialPortInfos) {
            if(UserSettings::comport == portInfo.portName()) com_connected = true;
        }
        if(!com_connected){
            BasicDialog bd1(this, "Error connecting to device", "Read From Radio");
            bd1.exec();
            return;
        }
    }

    loading_dialog->setWindowTitle("Radio Write");
    loading_dialog->show();

    // if(adw != nullptr) delete adw;
    adw = new SerialWorker();
    if(UserSettings::comport == QString("VIRTUAL")){
        adw->setVirtualFile(UserSettings::virtual_file_name);
    }else{
        adw->setComport(UserSettings::comport);
    }
    adw->is_write = true;
    adw->setReadWriteOptions(UserSettings::read_write_options);
    QObject::connect(adw, &SerialWorker::update1, loading_dialog, &LoadingDialog::updateMainbar);
    QObject::connect(adw, &SerialWorker::update2, loading_dialog, &LoadingDialog::updateSubbar);
    QObject::connect(adw, &SerialWorker::finished, this, &MainWindow::writeToRadioFinished, Qt::QueuedConnection);
    threadpool->start(adw);
}
void MainWindow::writeToRadioFinished(const int &result){
    loading_dialog->close();
    showList();

    RetryConnectionDialog retry_dialog(this);
    retry_dialog.is_write = true;
    BasicDialog bd1(this, "Invalid Radio Model or Version", "Write To Radio");
    BasicDialog bd2(this, "Write Complete", "Write To Radio");

    switch(result){
        case DeviceStatus::STATUS_COM_ERROR:
            retry_dialog.exec();
            break;
        case DeviceStatus::STATUS_DEVICE_MISMATCH:
            bd1.exec();
            break;
        default:
            bd2.exec();
            break;
    }
}
void MainWindow::onTreeItemClicked(QTreeWidgetItem* item, int column){
    if (!item) return;
    if(item->isDisabled()) return;
    if(item->text(0).contains("---")){
        listDigitalContact(item->data(0, Qt::UserRole).toInt());
        return;
    }
    showList(item->text(0));
}
void MainWindow::showMainTableContextMenu(QPoint pos){
    QModelIndexList selected_indexes = ui->tableView->selectionModel()->selectedIndexes();
    if(selected_indexes.size() == 0 || selected_table_view != "Channel") return;
    
        QMenu menu;
        
        // Add actions to the menu
        QAction edit_action("Edit", this);
        edit_action.setShortcut(QKeySequence("ENTER"));
        QAction cut_action("Cut", this);
        cut_action.setShortcut(QKeySequence("CTRL+X"));
        QAction copy_action("Copy", this);
        copy_action.setShortcut(QKeySequence("CTRL+C"));
        QAction paste_action("Paste", this);
        paste_action.setShortcut(QKeySequence("CTRL+V"));
        QAction delete_action("Delete", this);
        delete_action.setShortcut(QKeySequence("DEL"));
        menu.addAction(&edit_action);
        menu.addAction(&cut_action);
        menu.addAction(&copy_action);
        menu.addAction(&paste_action);
        menu.addAction(&delete_action);

        // Connect actions to their respective functions
        connect(&edit_action, &QAction::triggered, this, &MainWindow::editChannel);
        connect(&cut_action, &QAction::triggered, this, &MainWindow::cutSelectedChannels);
        connect(&copy_action, &QAction::triggered, this, &MainWindow::copySelectedChannels);
        connect(&paste_action, &QAction::triggered, this, &MainWindow::pasteSelectedChannels);
        connect(&delete_action, &QAction::triggered, this, &MainWindow::deleteSelectedChannels);
        menu.exec(ui->tableView->mapToGlobal(pos));
}
void MainWindow::showList(QString list_name){
    QString view = selected_table_view;
    if(list_name.size() > 0) view = list_name;

    if(view == "Channel"){
        selected_table_view = view;
        listChannels();
    }else if(view == "Zone"){
        selected_table_view = view;
        listZones();
    }else if(view == "Scan List"){
        selected_table_view = view;
        listScanLists();
    }else if(view == "Roaming Channel"){
        selected_table_view = view;
        listRoamingChannels();
    }else if(view == "Roaming Zone"){
        selected_table_view = view;
        listRoamingZones();
    }else if(view == "FM"){
        selected_table_view = view;
        listFmChannels();
    }else if(view == "Auto Repeater Offset Frequencies"){
        selected_table_view = view;
        listAutoRepeaterFrequencies();
    }else if(view == "Device Information"){
        showDeviceInformationDialog();
    }else if(view == "Optional Settings"){
        showOptionalSettingsDialog();
    }else if(view == "Alarm Settings"){
        showAlertSettingsDialog();
    }else if(view == "Local Information"){
        showLocalInformationDialog();
    }else if(view == "Hot Key"){
        showHotKeyDialog();
    }else if(view == "APRS"){
        showAprsSettingsDialog();
    }else if(view == "GPS Roaming"){
        selected_table_view = view;
        listGpsRoaming();
    }else if(view == "Master ID"){
        showMasterIdDialog();
    }else if(view == "Radio ID"){
        selected_table_view = view;
        listRadioIds();
    }else if(view == "Contact/Talk Group"){
        selected_table_view = view;
        listTalkgroups();
    }else if(view == "Prefabricated SMS"){
        selected_table_view = view;
        listPrefabricatedSms();
    }else if(view == "Receive Group Call List"){
        selected_table_view = view;
        listReceiveGroupCall();
    }else if(view == "Encryption Code"){
        selected_table_view = view;
        
    }else if(view == "AES Encryption Code"){
        selected_table_view = view;
        listAesEncryptionKeys();
    }else if(view == "ARC4 Encryption Code"){
        selected_table_view = view;
        
    }else if(view == "Friends List"){
        
    }else if(view == "Talk Alias Settings" || view == "AIR Alias Settings"){
        showTalkAliasSettingsDialog();
    }else if(view == "Analog Address Book"){
        
    }else if(view == "5Tone Settings"){
        showTone5SettingsDialog();
    }else if(view == "2Tone Settings"){
        showTone2SettingsDialog();
    }else if(view == "DTMF Settings"){
        showDtmfSettingsDialog();
    }else{
        qDebug() << view;
    }
}
void MainWindow::onMainTableDblClicked(QModelIndex index){
    int row_index = index.row();

    if(selected_table_view == "AES Encryption Code"){
        showAesEncryptionDialog(row_index);
    }else if(selected_table_view == "Auto Repeater Offset Frequencies"){
        showAutoRepeaterEditDialog(row_index);
    }else if(selected_table_view == "Channel"){
        showChannelEditDialog(row_index);
    }else if(selected_table_view == "FM"){
        showFmEditDialog(row_index);
    }else if(selected_table_view == "GPS Roaming"){
        showGpsRoaming(row_index);
    }else if(selected_table_view == "Radio ID"){
        showRadioIdEditDialog(row_index);
    }else if(selected_table_view == "Roaming Channel"){
        showRoamingChannelEditDialog(row_index);
    }else if(selected_table_view == "Roaming Zone"){
        showRoamingZoneEditDialog(row_index);
    }else if(selected_table_view == "Scan List"){
        showScanListEditDialog(row_index);
    }else if(selected_table_view == "Contact/Talk Group"){
        showTalkgroupEditDialog(row_index);
    }else if(selected_table_view == "Zone"){
        showZoneEditDialog(row_index);
    }else if(selected_table_view == "Prefabricated SMS"){
        showPrefabricatesSmsEditDialog(row_index);
    }
}
void MainWindow::saveFile(){
    QFile file("savefile.bin");
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_6_6);
        Anytone::Memory::saveData(out);
    }else{
        qDebug() << "Cannot open save file";
    }
}
void MainWindow::openFile(){
    QFile file("savefile.bin");
    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_6);
        Anytone::Memory::loadData(in);
        file.close();
    }

    showList();
}
