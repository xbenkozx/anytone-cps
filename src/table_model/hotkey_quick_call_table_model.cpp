#include "hotkey_quick_call_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/memory.h"
#include "memory/hotkey.h"
#include "constants.h"

HotKeyQuickCallTableModel::HotKeyQuickCallTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Operation Type",
        "Call ID"
    };
}

int HotKeyQuickCallTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::hotkey->quick_call_list.size());
}

int HotKeyQuickCallTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant HotKeyQuickCallTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant HotKeyQuickCallTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::hotkey->quick_call_list.size())) return {};
    Anytone::AnalogQuickCall *item = Anytone::Memory::hotkey->quick_call_list.at(row);
    if (!item) return {};

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColOperation:
            return QStringList{"Off", "DTMF", "2Tone", "5Tone"}.at(item->operation_type);

        case ColCallId:
            if(item->call_id == 0xff) return "Off";
            return QString::number(item->call_id + 1);

        default:
            return {};
    }
}

void HotKeyQuickCallTableModel::reload() {
    beginResetModel();
    endResetModel();
}