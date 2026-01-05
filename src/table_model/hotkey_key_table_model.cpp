#include "hotkey_key_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/memory.h"
#include "memory/hotkey.h"
#include "constants.h"

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
            return QStringList{"Menu", "Call"}.at(key->mode);

        case ColMenu:
            return Constants::HOTKEY_MENU.at(key->menu);

        case ColCallType:
            if(key->call_type == 0xff) return "Off";
            return QStringList{"Analog", "Digital"}.at(key->call_type);

        case ColCallObj:
            if(key->call_obj == 0) return "None";
            return QString::number(key->call_obj);

        case ColDigiCallType:
            if(key->digi_call_type == 0xff) return "Off";
            return QStringList{"Group Call", "", "", "Hot Text", "Call Type", "State Information"}.at(key->digi_call_type);

        case ColContent:
            return QString::number(key->content);
        
        default:
            return {};
    }
}

void HotkeyKeyTableModel::reload() {
    beginResetModel();
    endResetModel();
}