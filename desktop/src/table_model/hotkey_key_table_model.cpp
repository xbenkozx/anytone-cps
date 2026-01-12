#include "hotkey_key_table_model.h"

#include <Qt>
#include <QBrush>
#include <QComboBox>
#include <QPushButton>

// include your actual Channel + Constants headers
#include "memory/at_memory.h"
#include "memory/hotkey.h"
#include "constants.h"
#include "prefabricated_sms.h"
#include "talkgroup.h"
#include "hotkey_settings_dialog.h"
#include "contact_selection_dialog.h"

HotKeyHotKeyDelegate::HotKeyHotKeyDelegate(QObject* parent)
    : QStyledItemDelegate(parent){}

QWidget* HotKeyHotKeyDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex &index) const {
    auto* edit = new QComboBox(parent);
    const int column = index.column();
    const int row = index.row();
    if(column == HotkeyKeyTableModel::ColMode){
        edit->addItems(QStringList{"Call", "Menu"});
    }else if(column == HotkeyKeyTableModel::ColMenu){
        edit->addItems(Constants::HOTKEY_MENU);
    }else if(column == HotkeyKeyTableModel::ColCallType){
        edit->addItem("Off", QVariant((uint8_t)0xff));
        edit->addItem("Analog", QVariant((uint8_t)0));
        edit->addItem("Digital", QVariant((uint8_t)1));
    }else if(column == HotkeyKeyTableModel::ColCallObj){
        Anytone::HotkeyKey *key = Anytone::Memory::hotkey->key_list.at(row);
        if(key->call_type == 0){
            edit->addItem("Off");
        }else if(key->call_type == 1){
            auto* btn = new QPushButton(parent);
            connect(btn, &QPushButton::pressed,
            [index]() {
                HotKeyHotKeyDelegate::onHotkeyButtonPressed(index);
            });
            
            return btn;
        }
    }else if(column == HotkeyKeyTableModel::ColDigiCallType){
        edit->addItems(QStringList{"Analog", "Digital"});
    }else if(column == HotkeyKeyTableModel::ColContent){
        edit->addItem("Off", QVariant((uint8_t)0xff));
        for(int i = 0; i < Anytone::Memory::prefabricated_sms_list.size(); i++){
            Anytone::PrefabricatedSms *sms = Anytone::Memory::prefabricated_sms_list.at(i);
            if(sms->text.isEmpty()) continue;
            edit->addItem(QString::number(i+1), QVariant::fromValue(i));
        }
    }

    
    return edit;
}
void HotKeyHotKeyDelegate::onHotkeyButtonPressed(const QModelIndex& index){
    const int row = index.row();
    ContactSelectionDialog csd(row);
    csd.exec();
}

void HotKeyHotKeyDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
    const int column = index.column();
    const int row = index.row();
     Anytone::HotkeyKey *key = Anytone::Memory::hotkey->key_list.at(row);
    if(column == HotkeyKeyTableModel::ColCallObj && key->call_type == 1){
        auto* edit = qobject_cast<QComboBox*>(editor);
    }else{
        auto* edit = qobject_cast<QComboBox*>(editor);
        edit->setCurrentText(index.data(Qt::DisplayRole).toString());
    }
    
}
void HotKeyHotKeyDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    
    const int column = index.column();
    const int row = index.row();
    Anytone::HotkeyKey *key = Anytone::Memory::hotkey->key_list.at(row);
    if(column == HotkeyKeyTableModel::ColCallObj && key->call_type == 1){

    }else{
        auto* edit = qobject_cast<QComboBox*>(editor);
        if(
            column == HotkeyKeyTableModel::ColCallType || column == HotkeyKeyTableModel::ColContent
        ){
            model->setData(index, edit->currentData(), Qt::EditRole);
        }else{
            model->setData(index, edit->currentIndex(), Qt::EditRole);
        }
    }
}

HotkeyKeyTableModel::HotkeyKeyTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "Key",
        "Mode",
        "Menu",
        "Call Type",
        "Call Object",
        "Digi Call Type",
        "Content"
    };
}

int HotkeyKeyTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::hotkey->key_list.size());
}

int HotkeyKeyTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant HotkeyKeyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant HotkeyKeyTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::hotkey->key_list.size())) return {};
    Anytone::HotkeyKey *key = Anytone::Memory::hotkey->key_list.at(row);
    if (!key) return {};


    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColKey:
            return key->name;

        case ColMode:
            return QStringList{"Call", "Menu"}.at(key->mode);

        case ColMenu:
            return Constants::HOTKEY_MENU.at(key->menu);

        case ColCallType:
            if(key->call_type == 0xff) return "Off";
            return QStringList{"Analog", "Digital"}.at(key->call_type);

        case ColCallObj:
            if(key->call_obj == 0xffffffff) return "Off";
            if(key->talkgroup) return key->talkgroup->name + "(" + QString::number(key->talkgroup->dmr_id) + ")";
            return QString::number(key->call_obj);

        case ColDigiCallType:
            if(key->digi_call_type == 0xff) return "Off";
            return QStringList{"Group Call", "", "", "Hot Text", "Call Type", "State Information"}.at(key->digi_call_type);

        case ColContent:
            if(key->content == 0xff) return "Off";
            return QString::number(key->content);
        
        default:
            return {};
    }
}

void HotkeyKeyTableModel::reload() {
    beginResetModel();
    endResetModel();
}

bool HotkeyKeyTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    const int row = index.row();
    if (row < 0 || row >= static_cast<int>(Anytone::Memory::hotkey->key_list.size())) return true;
    Anytone::HotkeyKey *key = Anytone::Memory::hotkey->key_list.at(row);

    int idx = -1;
    switch (index.column()) {
        case ColMode:
            key->mode = value.toInt();
            break;
        case ColMenu:
            key->menu = value.toInt();
            break;
        case ColCallType:
            key->call_type = value.toInt();
            break;
        case ColCallObj:
            // key->menu = value.toInt();
            break;
        case ColDigiCallType:
            // key->menu = value.toInt();
            break;
        case ColContent:
            // key->menu = value.toInt();
            break;
        default:
            break;
    }

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

Qt::ItemFlags HotkeyKeyTableModel::flags(const QModelIndex& index) const {
    
    const int column = index.column();
    if (!index.isValid() || column == 0) return Qt::NoItemFlags;

    const int row = index.row();
    Anytone::HotkeyKey *key = Anytone::Memory::hotkey->key_list.at(row);
    if(key->mode == 1){
        switch(column){
            case ColCallType:
            case ColCallObj:
            case ColDigiCallType:
            case ColContent:
                return Qt::NoItemFlags;
            default:
                break;
        }
    }else if(key->mode == 0){
        switch(column){
            case ColMenu:
                return Qt::NoItemFlags;
            default:
                break;
        }

        if(key->call_type == 0xff){
            switch(column){
                case ColCallObj:
                case ColDigiCallType:
                case ColContent:
                    return Qt::NoItemFlags;
                default:
                    break;
            }
        }else if(key->call_type == 0){
            switch(column){
                case ColDigiCallType:
                case ColContent:
                    return Qt::NoItemFlags;
                default:
                    break;
            }
        }else if(key->call_type == 1){
            if(column == ColContent && key->digi_call_type != 3 && key->digi_call_type != 5){
                return Qt::NoItemFlags;
            }
        }
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}