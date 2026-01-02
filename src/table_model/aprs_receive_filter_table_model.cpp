#include "aprs_receive_filter_table_model.h"

#include <Qt>
#include <QBrush>
#include <QComboBox>

// include your actual Channel + Constants headers
#include "memory/memory.h"
#include "memory/aprs_receive_filter.h"
#include "constants.h"

ComboBoxDelegate::ComboBoxDelegate(const QStringList& items, QObject* parent)
    : QStyledItemDelegate(parent), m_items(items) {}

QWidget* ComboBoxDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex&) const {
    auto* combo = new QComboBox(parent);
    combo->addItems(m_items);
    return combo;
}

void ComboBoxDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
    auto* combo = qobject_cast<QComboBox*>(editor);
    combo->setCurrentText(index.data(Qt::DisplayRole).toString());
}

void ComboBoxDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    auto* combo = qobject_cast<QComboBox*>(editor);
    model->setData(index, combo->currentText(), Qt::EditRole);
}

AprsReceiveFilterTableModel::AprsReceiveFilterTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Receive Filter",
        "Call Sign",
        "SSID"
    };
}

int AprsReceiveFilterTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::aprs_settings->receive_filters.size());
}

int AprsReceiveFilterTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

bool AprsReceiveFilterTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Anytone::AprsReceiveFilter *filter = Anytone::Memory::aprs_settings->receive_filters.at(index.row());
    if(!filter) return false;

    int idx = -1;
    switch (index.column()) {
        case ColEnabled:
            idx = QStringList{"Off", "On"}.indexOf(value.toString());
            if(idx != -1) filter->enabled = idx;
            break;

        case ColCallsign:
            filter->callsign = value.toString().toUpper().mid(0, 7);
            break;

        case ColSsid:
            idx = QStringList{
                    "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7",
                    "-8", "-9", "-10", "-11", "-12", "-13", "-14", "-15", "Off"
                }.indexOf(value.toString());
            if(idx != -1) filter->ssid = idx;
           break;

        default:
            break;
    }


    // if (cell == newText) return true; // no-op, but not a failure
    // cell = newText;

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

Qt::ItemFlags AprsReceiveFilterTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant AprsReceiveFilterTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant AprsReceiveFilterTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::aprs_settings->receive_filters.size())) return {};
    Anytone::AprsReceiveFilter *filter = Anytone::Memory::aprs_settings->receive_filters.at(row);
    if (!filter) return {};

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColEnabled:
            return QStringList{
                "Off", "On"
            }.at(filter->enabled);

        case ColCallsign:
            return filter->callsign;

        case ColSsid:
            return QStringList{
                "0", "-1", "-2", "-3", "-4", "-5", "-6", "-7",
                "-8", "-9", "-10", "-11", "-12", "-13", "-14", "-15", "Off"
            }.at(filter->ssid);

        default:
            return {};
    }
}

void AprsReceiveFilterTableModel::reload() {
    beginResetModel();
    endResetModel();
}