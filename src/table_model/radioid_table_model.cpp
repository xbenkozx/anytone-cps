#include "radioid_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/memory.h"
#include "memory/radioid.h"
#include "constants.h"

RadioIdTableModel::RadioIdTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Radio ID",
        "Name"
    };
}

int RadioIdTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::radioids.size());
}

int RadioIdTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant RadioIdTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant RadioIdTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::radioids.size())) return {};
    Anytone::RadioId *rid = Anytone::Memory::radioids.at(row);
    if (!rid) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (rid->dmr_id == 0);

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

        case ColRadioId:
            return QString::number(rid->dmr_id);

        case ColName:
            return rid->name;

        default:
            return {};
    }
}

void RadioIdTableModel::reload() {
    beginResetModel();
    endResetModel();
}