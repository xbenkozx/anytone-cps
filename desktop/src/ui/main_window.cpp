#include <QSaveFile>
#include <QFileDialog>
#include "main_window.h"
#include "ui_main_window.h"
#include "memory/anytone_memory.h"

#include "user_settings.h"
#include "device.h"
#include <QSerialPortInfo>
#include <QLocale>
#include <QMenu>
#include <QMessageBox>
#include <QSpacerItem>
#include <QLayout>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
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
#include "arc4_encryption_table_model.h"
#include "encryption_table_model.h"
#include "analog_address_table_model.h"
#include "am_air_table_model.h"
#include "am_zone_table_model.h"
#include "talkgroup_whitelist_table_model.h"
#include "digital_contact_whitelist_table_model.h"

#include "aes_encryption_code_dialog.h"
#include "arc4_encryption_code_dialog.h"
#include "encryption_code_dialog.h"
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
#include "hotkey_settings_dialog.h"
#include "talkgroup_edit_dialog.h"
#include "hotkey_settings_dialog.h"
#include "analog_address_edit_dialog.h"
#include "import_export_dialog.h"
#include "satellite_dialog.h"
#include "about_dialog.h"
#include "am_air_edit_dialog.h"
#include "am_zone_edit_dialog.h"
#include "talkgroup_whitelist_edit_dialog.h"
#include "digital_contact_whitelist_edit_dialog.h"
#include "csv.h"
#include "satellite.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(std::make_unique<Ui_MainWindow>())
{
    ui->setupUi(this);
    Anytone::Memory::init();
    Anytone::Memory::initDigitalContacts();

    UserSettings::load();
    UserSettings::loadDefaults();
    UserSettings::saveDefaults();

    Anytone::Memory::setDefaults();

    Anytone::Memory::radio_model = UserSettings::radio_model;

    switch(UserSettings::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            setRadioModel_D878UVII();
            break;
        case Anytone::RadioModel::D890UV_FW103:
            setRadioModel_D890UV();
            break;
    }

    // Setup Dialogs

    threadpool = QThreadPool::globalInstance();
    selected_table_view = "Channel";

    

    setupUI();

    // CsvList csv;
    // csv.load("exports/export.LST");

    // readFromRadio();
}

MainWindow::~MainWindow(){}
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);

    if(!debug){
        QTimer::singleShot(0, this, &MainWindow::showAlphaWarningMessage);
        // ui->actionD890UV_103->setDisabled(true);
    }

    if(UserSettings::last_save_file != ""){
        openFile(UserSettings::last_save_file, false);
    }else{
        showList();
    }

    
}
void MainWindow::setupUI(){
    loading_dialog = new LoadingDialog(this);

    // File Menu
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newBtnClicked);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openBtnClicked);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveBtnClicked);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveFileAs);

    // Radio Menu
    connect(ui->actionD878UVII_400, &QAction::triggered, this, &MainWindow::setRadioModel_D878UVII);
    connect(ui->actionD890UV_103, &QAction::triggered, this, &MainWindow::setRadioModel_D890UV);
    connect(ui->actionSet_Com, &QAction::triggered, this, &MainWindow::showComportDialog);
    connect(ui->actionSet_Com, &QAction::triggered, this, &MainWindow::showComportDialog);
    connect(ui->actionSet_Com, &QAction::triggered, this, &MainWindow::showComportDialog);

    // Tool Menu
    connect(ui->actionBoot_Image, &QAction::triggered, this, &MainWindow::showBootImageDialog);
    connect(ui->actionStandby_BK_Picture_1, &QAction::triggered, this, &MainWindow::showBK1ImageDialog);
    connect(ui->actionStandby_Bk_Picture_2, &QAction::triggered, this, &MainWindow::showBK2ImageDialog);
    connect(ui->actionExpert_Options, &QAction::triggered, this, &MainWindow::showExpertOptions); 
    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::showImportDialog);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::showExportDialog);
    connect(ui->actionDefault_Channel_Options, &QAction::triggered, this, &MainWindow::showDefaultChannelEditDialog);
    connect(ui->actionSatellite, &QAction::triggered, this, &MainWindow::showSatelliteDialog);

    // About Menu
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    

    // Tool Bar
    connect(ui->newFileBtn, &QToolButton::clicked, this, &MainWindow::newBtnClicked);
    connect(ui->openFileBtn, &QToolButton::clicked, this, &MainWindow::openBtnClicked);
    connect(ui->saveFileBtn, &QToolButton::clicked, this, &MainWindow::saveBtnClicked);
    connect(ui->comPortBtn, &QToolButton::clicked, this, &MainWindow::showComportDialog);
    connect(ui->readRadioBtn, &QToolButton::clicked, this, &MainWindow::showReadOptionsDialog);
    connect(ui->writeRadioBtn, &QToolButton::clicked, this, &MainWindow::showWriteOptionsDialog);
    connect(ui->tableView, &QTableView::doubleClicked, this, &MainWindow::onMainTableDblClicked);

    // Main Widgets
    connect(ui->mainTreeWidget, &QTreeWidget::itemClicked, this, &MainWindow::onTreeItemClicked);

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
        case Anytone::RadioModel::D878UVII_FW400:
            tree_settings = d878uvii_tree_settings;
            break;
        case Anytone::RadioModel::D890UV_FW103:
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
void MainWindow::showAlphaWarningMessage(){
    QMessageBox msg(this);
    msg.setWindowModality(Qt::WindowModal);
    msg.setIcon(QMessageBox::Warning);
    msg.setWindowTitle("Alpha Version Warning");
    msg.setText("This program is currently in ALPHA STAGE and only compatible with FW v4.00");
    msg.setInformativeText(
        "Some features may not function correctly or may be incomplete.\n\n"
        "Use with caution and report any issues you encounter.\n"
    );
    msg.setStandardButtons(QMessageBox::Ok);

    // QMessageBox uses a grid layout internally (typically)
    if (auto *grid = qobject_cast<QGridLayout*>(msg.layout())) {

        // Add an expanding spacer to force width
        auto *spacer = new QSpacerItem(
            500, 0,
            QSizePolicy::Expanding,   // horizontal
            QSizePolicy::Minimum      // vertical
        );

        // Put it on the same row as the buttons (last row), last column
        int row = grid->rowCount() - 1;
        int col = grid->columnCount();
        grid->addItem(spacer, row, col, 1, 1);
    }

    // Optional: set a minimum width instead of a giant resize
    msg.setMinimumWidth(500);

    msg.exec();
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
    UserSettings::radio_model = Anytone::Memory::radio_model;
    UserSettings::save();
    setupTreeView();
    updateWindowTitle();
}
void MainWindow::updateWindowTitle(){
    QString current_file_name = "new.rdt";
    if(!UserSettings::last_save_file.isEmpty()){
        current_file_name = UserSettings::last_save_file;
    }
    switch(Anytone::Memory::radio_model){
        case Anytone::RadioModel::D878UVII_FW400:
            setWindowTitle("Anytone D878UVII CPS - 4.00 [" + current_file_name + "]");
            break;
        case Anytone::RadioModel::D890UV_FW103:
            setWindowTitle("Anytone D890UV CPS - 1.03 [" + current_file_name + "]");
            break;
        default:
            break;
    }
}
void MainWindow::setRadioModel_D878UVII(){
    ui->actionD878UVII_400->setChecked(true);
    ui->actionD890UV_103->setChecked(false);
    Anytone::Memory::radio_model = Anytone::RadioModel::D878UVII_FW400;
    updateRadioModel();
}
void MainWindow::setRadioModel_D890UV(){
    ui->actionD878UVII_400->setChecked(false);
    ui->actionD890UV_103->setChecked(true);
    Anytone::Memory::radio_model = Anytone::RadioModel::D890UV_FW103;
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
void MainWindow::listArc4EncryptionKeys(bool goto_top){
    delete table_model;
    table_model = new Arc4EncryptionTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listEncryptionKeys(bool goto_top){
    delete table_model;
    table_model = new EncryptionTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listAnalogAddresses(bool goto_top){
    delete table_model;
    table_model = new AnalogAddressTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listAmAir(bool goto_top){
    delete table_model;
    table_model = new AmAirTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listAmZones(bool goto_top){
    delete table_model;
    table_model = new AmZoneTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 300);
    ui->tableView->setColumnWidth(2, 100);
    ui->tableView->setColumnWidth(3, 200);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listTalkgroupWhitelist(bool goto_top){
    delete table_model;
    table_model = new TalkgroupWhitelistTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);
    ui->tableView->setColumnWidth(2, 100);

    if(goto_top) ui->tableView->scrollToTop();
}
void MainWindow::listDigitalContactWhitelist(bool goto_top){
    delete table_model;
    table_model = new DigitalContactWhitelistTableModel(this);
    ui->tableView->setModel(table_model);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setSortingEnabled(false);

    ui->tableView->setColumnWidth(0, 70);
    ui->tableView->setColumnWidth(1, 100);

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
void MainWindow::showArc4EncryptionDialog(int index){
    Arc4EncryptionCodeDialog arc_encryption_dialog(this, index);
    arc_encryption_dialog.exec();
}
void MainWindow::showEncryptionDialog(int index){
    EncryptionCodeDialog encryption_dialog(this, index);
    encryption_dialog.exec();
}
void MainWindow::showAlertSettingsDialog(){
    AlertSettingsDialog alert_settings_dialog(this);
    alert_settings_dialog.exec();
}
void MainWindow::showAnalogAddressEditDialog(int index){
    AnalogAddressEditDialog encryption_dialog(this, index);
    encryption_dialog.exec();
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
void MainWindow::showDefaultChannelEditDialog(){
    showChannelEditDialog(-1);
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
void MainWindow::showImportDialog(){
    ImportExportDialog dialog(this);
    dialog.exec();
}
void MainWindow::showExportDialog(){
    ImportExportDialog dialog(this);
    dialog.is_export = true;
    dialog.exec();
}
void MainWindow::showSatelliteDialog(){
    SatelliteDialog dialog(this);
    dialog.exec();
}
void MainWindow::showAboutDialog(){
    AboutDialog dialog(this);
    dialog.exec();
}
void MainWindow::showAmAirEditDialog(int index){
    AmAirEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showAmZoneEditDialog(int index){
    AmZoneEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showTalkgroupWhitelistEditDialog(int index){
    TalkgroupWhitelistEditDialog dialog(this, index);
    dialog.exec();
}
void MainWindow::showDigitalContactWhitelistEditDialog(int index){
    DigitalContactWhitelistEditDialog dialog(this, index);
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

    
    adw = new SerialWorker();
    if(UserSettings::comport == QString("VIRTUAL")){
        adw->setVirtualFile(UserSettings::virtual_file_name);
    }else{
        adw->setComport(UserSettings::comport);
    }
    ui->tableView->setUpdatesEnabled(false);
    adw->setReadWriteOptions(UserSettings::read_write_options);
    QObject::connect(adw, &SerialWorker::update1, loading_dialog, &LoadingDialog::updateMainbar);
    QObject::connect(adw, &SerialWorker::update2, loading_dialog, &LoadingDialog::updateSubbar);
    QObject::connect(adw, &SerialWorker::finished, this, &MainWindow::readFromRadioFinished, Qt::QueuedConnection);
    threadpool->start(adw);
}
void MainWindow::readFromRadioFinished(const int &result){
    ui->tableView->setUpdatesEnabled(true);
    loading_dialog->m_isBusy = false;
    loading_dialog->close();
    // showList();

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
    loading_dialog->m_isBusy = false;
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
    ui->tableView->setUpdatesEnabled(true);
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
        listEncryptionKeys();
    }else if(view == "AES Encryption Code"){
        selected_table_view = view;
        listAesEncryptionKeys();
    }else if(view == "ARC4 Encryption Code"){
        selected_table_view = view;
        listArc4EncryptionKeys();
    }else if(view == "Friends List"){
        
    }else if(view == "Talk Alias Settings" || view == "AIR Alias Settings"){
        showTalkAliasSettingsDialog();
    }else if(view == "Analog Address Book"){
        selected_table_view = view;
        listAnalogAddresses();
    }else if(view == "AM Air"){
        selected_table_view = view;
        listAmAir();
    }else if(view == "AM Zone"){
        selected_table_view = view;
        listAmZones();
    }else if(view == "5Tone Settings"){
        showTone5SettingsDialog();
    }else if(view == "2Tone Settings"){
        showTone2SettingsDialog();
    }else if(view == "DTMF Settings"){
        showDtmfSettingsDialog();
    }else if(view == "Talk Group Whitelist"){
        selected_table_view = view;
        listTalkgroupWhitelist();
    }else if(view == "Digital Contact Whitelist"){
        selected_table_view = view;
        listDigitalContactWhitelist(); 
    }else{
        qDebug() << view;
    }
}
void MainWindow::onMainTableDblClicked(QModelIndex index){
    int row_index = index.row();

    if(selected_table_view == "AES Encryption Code"){
        showAesEncryptionDialog(row_index);
    }else if(selected_table_view == "ARC4 Encryption Code"){
        showArc4EncryptionDialog(row_index);
    }else if(selected_table_view == "Encryption Code"){
        showEncryptionDialog(row_index);
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
    }else if(selected_table_view == "Analog Address Book"){
        showAnalogAddressEditDialog(row_index);
    }else if(selected_table_view == "AM Air"){
        showAmAirEditDialog(row_index);
    }else if(selected_table_view == "AM Zone"){
        showAmZoneEditDialog(row_index);
    }else if(selected_table_view == "Talk Group Whitelist"){
        showTalkgroupWhitelistEditDialog(row_index);
    }else if(selected_table_view == "Digital Contact Whitelist"){
        showDigitalContactWhitelistEditDialog(row_index);
    }
    

    
}
void MainWindow::newBtnClicked(){
    Anytone::Memory::init();
    Anytone::Memory::initDigitalContacts();
    Anytone::Memory::setDefaults();
    UserSettings::last_save_file = "";
    UserSettings::save();
    updateWindowTitle();
    showList();
}
void MainWindow::saveBtnClicked(){
    saveFile();
}
void MainWindow::openBtnClicked(){
    openFile();
}
void MainWindow::saveFileAs(){
    saveFile(true);
}
void MainWindow::saveFile(bool save_as){
    QString filepath = UserSettings::last_save_file;
    if(save_as) filepath = "";

    #ifdef _WIN32
    QString default_path = "C:/Users/" + QString(getenv("USERNAME")) + "/Documents";
    #else
    QString default_path = "/home/" + QString(getenv("USER")) +  "/Documents";
    #endif


    if(filepath.isEmpty()){
        QString fname = QFileDialog::getSaveFileName(
            this,
            tr("Save Codeplug"),
            default_path,
            tr("Radio Data File (*.atd)")
        );

        if (fname.isEmpty())
            return;

        if (!fname.endsWith(".atd", Qt::CaseInsensitive)) {
            fname += ".atd";
        }

        filepath = fname;
    }
    UserSettings::last_save_file = filepath;
    UserSettings::save();
    QFile file(filepath);
    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        file.close();

        loading_dialog->setWindowTitle("Save File");
        loading_dialog->show();

        sfw = new SaveFileWorker();
        QObject::connect(sfw, &SaveFileWorker::update1, loading_dialog, &LoadingDialog::updateMainbar);
        QObject::connect(sfw, &SaveFileWorker::update2, loading_dialog, &LoadingDialog::updateSubbar);
        QObject::connect(sfw, &SaveFileWorker::finished, this, &MainWindow::fileFinished, Qt::QueuedConnection);
        sfw->filepath = filepath;
        sfw->user_init = true;
        sfw->is_write = true;
        threadpool->start(sfw);
    }else{
        QMessageBox::warning(this,
            tr("Open File"),
            tr("File could not be opened"));
    }

}
void MainWindow::openFile(QString filepath, bool user_init){
    if(filepath.isEmpty()){

        #ifdef _WIN32
        QString default_path = "C:/Users/" + QString(getenv("USERNAME")) + "/Documents";
        #else
        QString default_path = "/home/" + QString(getenv("USER")) +  "/Documents";
        #endif

        QString fname = QFileDialog::getOpenFileName(
            this,
            tr("Open Codeplug"),
            default_path,
            tr("Radio Data File (*.atd)")
        );

        if (fname.isEmpty())
            return;

        if (!fname.endsWith(".atd", Qt::CaseInsensitive)) {
            fname += ".atd";
        }

        filepath = fname;
    }
    QFile file(filepath);
    if(file.open(QIODevice::ReadOnly)){
        UserSettings::last_save_file = filepath;
        file.close();

        loading_dialog->setWindowTitle("Open File");
        loading_dialog->show();

        sfw = new SaveFileWorker();
        QObject::connect(sfw, &SaveFileWorker::update1, loading_dialog, &LoadingDialog::updateMainbar);
        QObject::connect(sfw, &SaveFileWorker::update2, loading_dialog, &LoadingDialog::updateSubbar);
        QObject::connect(sfw, &SaveFileWorker::finished, this, &MainWindow::fileFinished, Qt::QueuedConnection);
        sfw->filepath = filepath;
        sfw->user_init = user_init;
        sfw->is_write = false;
        threadpool->start(sfw);
    }else{
        if(user_init)
            QMessageBox::warning(this,
                tr("Open File"),
                tr("File could not be opened"));
        UserSettings::last_save_file = "";
    }

    UserSettings::save();
}
void MainWindow::fileFinished(const int &result){
    loading_dialog->m_isBusy = false;
    loading_dialog->close();
    updateWindowTitle();
    showList();

    switch(result){
        case SaveFileWorker::Result::NoDialog:
            //Success but no dialog
            break;
        case SaveFileWorker::Result::OpenFileOk:
            QMessageBox::information(this,
                tr("Open File"),
                tr("Open File OK"));
            break;
        case SaveFileWorker::Result::OpenFileError:
            QMessageBox::warning(this,
                tr("Open File"),
                tr("File could not be opened"));
            break;
        case SaveFileWorker::Result::SaveFileOk:
            QMessageBox::information(this,
                tr("Save File"),
                tr("Save File OK"));
            break;
        case SaveFileWorker::Result::SaveFileError:
            QMessageBox::warning(this,
                tr("Save File"),
                tr("File could not be written"));
            break;
    }
}

void SaveFileWorker::run(){
    connect(&Anytone::Memory::instance(), &Anytone::Memory::update1, this, &SaveFileWorker::update1);
    connect(&Anytone::Memory::instance(), &Anytone::Memory::update2, this, &SaveFileWorker::update2);
    QFile file(filepath);
    if(is_write){
        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
            QXmlStreamWriter xml(&file);
            xml.setAutoFormatting(true);
            Anytone::Memory::saveData(xml);
            file.close();
        }else{
            emit finished(Result::SaveFileError);
            return;
        }
    }else{
        if(file.open(QIODevice::ReadOnly)){
            QXmlStreamReader xml(&file);
            Anytone::Memory::loadData(xml);
            file.close();
        }else{
            emit finished(Result::OpenFileError);
            return;
        }
    }
    if(user_init) { 
        if(is_write){
            emit finished(Result::SaveFileOk); 
        }else{
            emit finished(Result::OpenFileOk);
        }
     } else { emit finished(Result::NoDialog); }
}
