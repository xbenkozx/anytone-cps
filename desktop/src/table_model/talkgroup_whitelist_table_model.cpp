#include "talkgroup_whitelist_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/talkgroup_whitelist.h"
#include "constants.h"

TalkgroupWhitelistTableModel::TalkgroupWhitelistTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "DMR ID",
        "Call Type"
    };
}

int TalkgroupWhitelistTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::talkgroup_whitelist.size());
}

int TalkgroupWhitelistTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant TalkgroupWhitelistTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant TalkgroupWhitelistTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::talkgroup_whitelist.size())) return {};
    Anytone::TalkgroupWhitelist *tg = Anytone::Memory::talkgroup_whitelist.at(row);
    if (!tg) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (tg->dmr_id == 0);

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    if (empty) {
        if (col == ColIndex) {
            return QString::number(row + 1);
        }
        return {};
    }

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColDmrId:
            return QString::number(tg->dmr_id);

        case ColCallType:
            return Constants::CALL_TYPE.at(tg->call_type);

        default:
            return {};
    }
}

void TalkgroupWhitelistTableModel::reload() {
    beginResetModel();
    endResetModel();
}