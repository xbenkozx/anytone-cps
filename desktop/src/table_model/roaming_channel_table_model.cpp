#include "roaming_channel_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/at_memory.h"
#include "memory/roaming_channel.h"
#include "constants.h"

RoamingChannelTableModel::RoamingChannelTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "RX Frequency",
        "TX Frequency",
        "Color Code",
        "Slot",
        "Name"
    };
}

int RoamingChannelTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::roaming_channels.size());
}

int RoamingChannelTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant RoamingChannelTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant RoamingChannelTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::roaming_channels.size())) return {};
    Anytone::RoamingChannel *ch = Anytone::Memory::roaming_channels.at(row);
    if (!ch) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (ch->rx_frequency == 0);

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

        case ColRxFreq:
            return ch->getRxFrequencyString();
        case ColTxFreq:
            return ch->getTxFrequencyString();
        case ColColorCode:
            return Constants::ROAMING_CHANNEL_COLOR_CODE.at(ch->color_code);
        case ColSlot:
            return Constants::ROAMING_CHANNEL_SLOT.at(ch->color_code);
        case ColName:
            return ch->name;

        default:
            return {};
    }
}

void RoamingChannelTableModel::reload() {
    beginResetModel();
    endResetModel();
}