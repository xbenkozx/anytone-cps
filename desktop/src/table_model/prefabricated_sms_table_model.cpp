#include "prefabricated_sms_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/prefabricated_sms.h"
#include "constants.h"

PrefabricatedSmsTableModel::PrefabricatedSmsTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Text"
    };
}

int PrefabricatedSmsTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::prefabricated_sms_list.size());
}

int PrefabricatedSmsTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant PrefabricatedSmsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant PrefabricatedSmsTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::prefabricated_sms_list.size())) return {};
    Anytone::PrefabricatedSms *sms = Anytone::Memory::prefabricated_sms_list.at(row);
    if (!sms) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (sms->text.size() == 0);

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    if (empty) {
        // Keep index column visible, others blank like your previous "continue"
        if (col == ColIndex) {
            return QString::number(row + 1);
        }
        return {};
    }

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColText:
            return sms->text;

        default:
            return {};
    }
}

void PrefabricatedSmsTableModel::reload() {
    beginResetModel();
    endResetModel();
}