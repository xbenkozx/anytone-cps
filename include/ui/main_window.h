#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <memory>
#include <vector>
#include <map>
#include <QThreadPool>
#include <QVector>
#include <QPair>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QShortcut>
#include <QTreeWidgetItem>
#include "device.h"
#include "comport_dialog.h"
#include "loading_dialog.h"
#include "read_write_options_dialog.h"
#include "basic_dialog.h"
#include "retry_connection_dialog.h"
#include "channel.h"


class Ui_MainWindow;

class MainWindow : public QMainWindow 
{

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showEvent(QShowEvent *event) override;
    void setupUI();
    void setupTreeView();
    void saveFile(bool save_as = false);
    void saveFileAs();
    void openFile(QString filepath = "");
    void updateRadioModel();
    void showAlphaWarningMessage();
    void setRadioModel_D878UVII();
    void setRadioModel_D890UV();

    void copySelectedChannels();
    void cutSelectedChannels();
    void pasteSelectedChannels();
    void deleteSelectedChannels();
    void undoChannels();
    void redoChannels();
    void editChannel();
    void updateMemoryChannelHistory();

    // Dialogs
    void showComportDialog();
    void showReadOptionsDialog();
    void showWriteOptionsDialog();
    void showAesEncryptionDialog(int index);
    void showArc4EncryptionDialog(int index);
    void showEncryptionDialog(int index);
    void showAlertSettingsDialog();
    void showAnalogAddressEditDialog(int index);
    void showAprsSettingsDialog();
    void showAutoRepeaterEditDialog(int index);
    void showChannelEditDialog(int index);
    void showDeviceInformationDialog();
    void showDtmfSettingsDialog();
    void showExpertOptions();
    void showFmEditDialog(int index);
    void showGpsRoaming(int index);
    void showLocalInformationDialog();
    void showHotKeyDialog();
    void showMasterIdDialog();
    void showOptionalSettingsDialog();
    void showPrefabricatesSmsEditDialog(int index);
    void showRadioIdEditDialog(int index);
    void showRoamingChannelEditDialog(int index);
    void showRoamingZoneEditDialog(int index);
    void showScanListEditDialog(int index);
    void showTalkAliasSettingsDialog();
    void showTalkgroupEditDialog(int index);
    void showTone2SettingsDialog();
    void showTone5SettingsDialog();
    void showZoneEditDialog(int index);
    void showBootImageDialog();
    void showBK1ImageDialog();
    void showBK2ImageDialog();

    // Table Lists
    void listChannels(bool goto_top = true);
    void listZones(bool goto_top = true);
    void listTalkgroups(bool goto_top = true);
    void listScanLists(bool goto_top = true);
    void listRadioIds(bool goto_top = true);
    void listRoamingZones(bool goto_top = true);
    void listRoamingChannels(bool goto_top = true);
    void listFmChannels(bool goto_top = true);
    void listAutoRepeaterFrequencies(bool goto_top = true);
    void listDigitalContact(int page_index, bool goto_top = true);
    void listGpsRoaming(bool goto_top = true);
    void listPrefabricatedSms(bool goto_top = true);
    void listReceiveGroupCall(bool goto_top = true);
    void listAesEncryptionKeys(bool goto_top = true);
    void listArc4EncryptionKeys(bool goto_top = true);
    void listEncryptionKeys(bool goto_top = true);
    void listAnalogAddresses(bool goto_top = true);

    // Serial
    void readFromRadio();
    void readLocalInformation();
    void readFromRadioFinished(const int &result);
    void writeToRadio();
    void writeToRadioFinished(const int &result);
    

    int read_write_options = 0;
    bool debug = false;

    // UI

    void showList(QString list_name = "");


private slots:
    void onTreeItemClicked(QTreeWidgetItem* item, int column);
    void onMainTableDblClicked(QModelIndex index);
    void showMainTableContextMenu(QPoint pos);
    void saveBtnClicked();
    void openBtnClicked();
    void newBtnClicked();

private:
    void updateWindowTitle();
    QString selected_table_view = "";
    std::unique_ptr<Ui_MainWindow> ui;
    QThreadPool *threadpool;

    std::unique_ptr<ComportDialog> comport_dialog;
    std::unique_ptr<ReadWriteOptionsDialog> rwo_dialog;
    LoadingDialog *loading_dialog;

    QVector<Anytone::Channel*> channel_clipboard;

    QShortcut *channel_copy_shortcut = nullptr;
    QShortcut *channel_cut_shortcut = nullptr;
    QShortcut *channel_paste_shortcut = nullptr;
    QShortcut *channel_undo_shortcut = nullptr;
    QShortcut *channel_redo_shortcut = nullptr;
    QShortcut *channel_delete_shortcut = nullptr;
    QShortcut *channel_edit_shortcut = nullptr;

    
    QAbstractTableModel *table_model = nullptr;
    SerialWorker *adw;

    QVector<QPair<QString, QStringList>> d878uvii_tree_settings = {
        {
            {"Common Settings",
                {
                    "Channel",
                    "Zone",
                    "Scan List",
                    "Roaming Channel",
                    "Roaming Zone",
                    "FM",
                    "Auto Repeater Offset Frequencies",
                    "Device Information",
                    "Optional Settings",
                    "Alarm Settings",
                    "Local Information",
                    "Hot Key",
                    "APRS",
                    "GPS Roaming"
                }
            },
            {"Digital",
                {
                    "Master ID",
                    "Radio ID",
                    "Contact/Talk Group",
                    "Prefabricated SMS",
                    "Receive Group Call List",
                    "Encryption Code",
                    "AES Encryption Code",
                    "ARC4 Encryption Code",
                    "Digital Contact List",
                    "Friends List",
                    "Talk Alias Settings"
                }
            },
            {"Analog",
                {
                    "Analog Address Book",
                    "5Tone Settings",
                    "2Tone Settings",
                    "DTMF Settings"
                }
            }
        }
    };

    QVector<QPair<QString, QStringList>> d890uv_tree_settings = {
        {
            {"Common Settings",
                {
                    "Channel",
                    "Zone",
                    "Scan List",
                    "AM Air",
                    "AM Zone",
                    "FM",
                    "Auto Repeater Offset Frequencies",
                    "Device Information",
                    "Optional Settings",
                    "Alarm Settings",
                    "Local Information",
                    "Hot Key",
                    "APRS",
                    "GPS Roaming"
                }
            },
            {"DMR",
                {
                    "Master ID",
                    "Radio ID",
                    "Contact/Talk Group",
                    "Roaming Channel",
                    "Roaming Zone",
                    "Prefabricated SMS",
                    "Receive Group Call List",
                    "Encryption Code",
                    "AES Encryption Code",
                    "ARC4 Encryption Code",
                    "Digital Contact List",
                    "Friends List",
                    "AIR Alias Settings", //Talk Alias Settings
                    "Repeater Whitelist" //Talk Group White List, Digital Contact Whitelist
                }
            },
            {"Analog",
                {
                    "Analog Address Book",
                    "QDC 1200",
                    "QDC Address Book",
                    "5Tone Settings",
                    "2Tone Settings",
                    "DTMF Settings"
                }
            }
        }
    };

};

#endif

