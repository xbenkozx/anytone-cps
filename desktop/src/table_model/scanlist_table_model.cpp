#include "scanlist_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/at_memory.h"
#include "memory/scanlist.h"
#include "constants.h"

ScanListTableModel::ScanListTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Name",
        "Channels",
        "Priority Channel 1",
        "Priority Channel 2",
        "Look Back Time A",
        "Look Back Time B",
        "Dropout Delay",
        "Dwell Time"
    };
}

int ScanListTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::scanlists.size());
}

int ScanListTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant ScanListTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant ScanListTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::scanlists.size())) return {};
    Anytone::ScanList *sl = Anytone::Memory::scanlists.at(row);
    if (!sl) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (sl->channels.size() == 0);

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

        case ColName:
            return sl->name;

        case ColChannels:
            return int(sl->channels.size());

        case ColPriority1:
            if(sl->priority_channel_1 == 0xffff){
                return Constants::SCAN_LIST_PRIORITY_CHANNEL_SELECT.at(0);
            }else if(sl->priority_channel_1 == 0){
                return Constants::SCAN_LIST_PRIORITY_CHANNEL_SELECT.at(1);
            }else{
                sl->channels.at(sl->priority_channel_1-1)->name;
            }

        case ColPriority2:
            if(sl->priority_channel_2 == 0xffff){
                return Constants::SCAN_LIST_PRIORITY_CHANNEL_SELECT.at(0);
            }else if(sl->priority_channel_2 == 0){
                return Constants::SCAN_LIST_PRIORITY_CHANNEL_SELECT.at(1);
            }else{
                sl->channels.at(sl->priority_channel_2-1)->name;
            }

        case ColLbTimeA:
            return Constants::SCAN_LIST_LOOK_BACK_TIME.at(sl->lookback_time_a);
        case ColLbTimeB:
            return Constants::SCAN_LIST_LOOK_BACK_TIME.at(sl->lookback_time_b);
        case ColDropout:
            return Constants::SCAN_LIST_DROPOUT_DELAY_DWELL_TIME.at(sl->dropout_delay_time);
        case ColDwell:
            return Constants::SCAN_LIST_DROPOUT_DELAY_DWELL_TIME.at(sl->dwell_time);

        default:
            return {};
    }
}

void ScanListTableModel::reload() {
    beginResetModel();
    endResetModel();
}