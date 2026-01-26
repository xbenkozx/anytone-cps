#include "gps_roaming_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/gps_roaming.h"
#include "zone.h"
#include "constants.h"

GpsRoamingTableModel::GpsRoamingTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Enabled",
        "Zone",
        "Latitude\nDegree",
        "Latitude\nMinute",
        "Lat Min Mark",
        "North/South",
        "Longitude\nDegree",
        "Longitude\n Minute",
        "Long Min Mark",
        "East/West",
        "Radius(Meter)"
    };
}

int GpsRoamingTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::gps_roaming_list.size());
}

int GpsRoamingTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant GpsRoamingTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant GpsRoamingTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::gps_roaming_list.size())) return {};
    Anytone::GpsRoaming *gps = Anytone::Memory::gps_roaming_list.at(row);
    if (!gps) return {};

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
            return Constants::OFF_ON.at(gps->enabled);
        case ColZone:
            if(gps->zone_idx == 0xff){
                return "Off";
            }else{
                return Anytone::Memory::zones.at(gps->zone_idx)->name;
            }
        case ColLatDeg:
            return QString::number(gps->lat_degree);
        case ColLatMin:
            return QString::number(gps->lat_minute);
        case ColLatMinMark:
            return QString::number(gps->lat_minute_decimal);
        case ColNS:
            return ns.at(gps->north_south);
        case ColLngDeg:
            return QString::number(gps->long_degree);
        case ColLngMin:
            return QString::number(gps->long_minute);
        case ColLngMinMark:
            return QString::number(gps->long_minute_decimal);
        case ColLngEW:
            return ew.at(gps->east_west);
        case ColRadius:
            return QString::number(gps->radius);
        default:
            return {};
    }
}

void GpsRoamingTableModel::reload() {
    beginResetModel();
    endResetModel();
}