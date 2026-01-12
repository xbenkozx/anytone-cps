#include "channel_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/channel.h"
#include "constants.h"

ChannelTableModel::ChannelTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Receive\nFrequency",
        "Transmit\nFrequency",
        "Channel Type",
        "Power",
        "Band\nWidth",
        "CTCSS/DCS\nDecode",
        "CTCSS/DCS\nEncode",
        "Channel Name",
        "Contact",
        "Radio ID",
        "Optional Signal"
    };
}

int ChannelTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::channels.size());
}

int ChannelTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant ChannelTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

bool ChannelTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;

    if (role == Qt::ForegroundRole) {
        QBrush brush;

        // accept either QBrush or QColor
        if (value.canConvert<QBrush>()) {
            brush = value.value<QBrush>();
        } else if (value.canConvert<QColor>()) {
            brush = QBrush(value.value<QColor>());
        } else {
            return false;
        }

        m_fgOverrides[QPersistentModelIndex(index)] = brush;
        emit dataChanged(index, index, {Qt::ForegroundRole});
        return true;
    }

    return QAbstractTableModel::setData(index, value, role);
}

QVariant ChannelTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::channels.size())) return {};
    Anytone::Channel *channel = Anytone::Memory::channels.at(row);
    if (!channel) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (channel->rx_frequency == 0);

    
    if (role == Qt::ForegroundRole) {
        QPersistentModelIndex pidx(idx);
        auto it = m_fgOverrides.constFind(pidx);
        if (it != m_fgOverrides.constEnd())
            return *it;

        // your existing computed coloring
        if (col == ColOptional && channel->channel_type == 1) {
            static const QBrush grayBrush(QColorConstants::Gray);
            return grayBrush;
        } else if (col == ColContact && channel->channel_type == 0) {
            static const QBrush grayBrush(QColorConstants::Gray);
            return grayBrush;
        } else if (col == ColRadioId && channel->channel_type == 0) {
            static const QBrush grayBrush(QColorConstants::Gray);
            return grayBrush;
        }
        return {};
    }

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    if (empty) {
        // Keep index column visible, others blank like your previous "continue"
        if (col == ColIndex) {
            if (row == 4000) return QStringLiteral("VFO A");
            if (row == 4001) return QStringLiteral("VFO B");
            return QString::number(row + 1);
        }
        return {};
    }

    switch (col) {
        case ColIndex:
            if (row == 4000) return QStringLiteral("VFO A");
            if (row == 4001) return QStringLiteral("VFO B");
            return QString::number(row + 1);

        case ColRx:
            return channel->getRxFrequencyString();

        case ColTx:
            return channel->getTxFrequencyString();

        case ColType:
            return Constants::CHANNEL_TYPE.at(channel->channel_type);

        case ColPower:
            return Constants::TX_POWER.at(channel->tx_power);

        case ColBW:
            return Constants::BAND_WIDTH.at(channel->band_width);

        case ColDecode: {
            if (channel->ctcss_dcs_decode == 1)
                return Constants::CTCSS_CODE.at(channel->ctcss_decode_tone);
            if (channel->ctcss_dcs_decode == 2)
                return Constants::DCS_CODE.at(channel->dcs_decode_tone);
            return QStringLiteral("Off");
        }

        case ColEncode: {
            if (channel->ctcss_dcs_encode == 1)
                return Constants::CTCSS_CODE.at(channel->ctcss_encode_tone);
            if (channel->ctcss_dcs_encode == 2)
                return Constants::DCS_CODE.at(channel->dcs_encode_tone);
            return QStringLiteral("Off");
        }

        case ColName:
            return channel->name;

        case ColContact:
            if(channel->contact == nullptr) return {};
            return channel->contact->name;
        case ColRadioId:
            if(channel->radioid == nullptr) return {};
            return channel->radioid->name;
        case ColOptional:
            return (channel->optional_signal == 0)
                ? QStringLiteral("Off")
                : QString::number(channel->optional_signal);

        default:
            return {};
    }
}

void ChannelTableModel::reload() {
    beginResetModel();
    endResetModel();
}