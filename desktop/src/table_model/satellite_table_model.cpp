#include "satellite_table_model.h"

#include <Qt>
#include <QBrush>
#include <QFont>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/satellite.h"
#include "constants.h"

SatelliteTableModel::SatelliteTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "ID",
        "Write",
        "Name",
        "Rx Freq[Hz]",
        "Tx Freq[Hz]",
        "CTC/DCS\nRX",
        "CTCSS RX",
        "DCS RX",
        "CTC/DCS\nTX",
        "CTCSS TX",
        "DCS TX",
        "APRS\nTX Freq[Hz]",
        "Arm Tx\nCdt",
        "Arm Ctc",
        "Arm Dcs"
    };
}

int SatelliteTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::satellite_data_list.size());
}

int SatelliteTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant SatelliteTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant SatelliteTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::satellite_data_list.size())) return {};
    Anytone::Satellite *sat = Anytone::Memory::satellite_data_list.at(row);
    if (!sat) return {};

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColWrite:
            return QStringList{"No", "Yes"}.at(sat->write_enable);

        case ColName:
            return sat->name;

        case ColRxFreq:
            return QString::number(sat->rx_frequency);

        case ColTxFreq:
            return QString::number(sat->tx_frequency);

        case ColCtcDcsRx:
            return QStringList{"Off", "CTCSS", "DCS"}.at(sat->ctcss_dcs_decode);

        case ColCtcssRx:
            if(sat->ctcss_dcs_decode == 1) return Constants::CTCSS_CODE.at(sat->ctcss_decode_tone);
            return {};

        case ColDcsRx:
            if(sat->ctcss_dcs_decode == 2) return Constants::DCS_CODE.at(sat->dcs_decode_tone);
            return {};

        case ColCtcDcsTx:
            return QStringList{"Off", "CTCSS", "DCS"}.at(sat->ctcss_dcs_encode);
        
        case ColCtcssTx:
            if(sat->ctcss_dcs_encode == 1) return Constants::CTCSS_CODE.at(sat->ctcss_encode_tone);
            return {};

        case ColDcsTx:
            if(sat->ctcss_dcs_encode == 2) return Constants::DCS_CODE.at(sat->dcs_encode_tone);
            return {};

        default:
            return {};
    }
}

void SatelliteTableModel::reload() {
    beginResetModel();
    endResetModel();
}