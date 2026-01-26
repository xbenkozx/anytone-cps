#include "digital_contacts_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/digital_contact.h"
#include "constants.h"

DigitalContactsTableModel::DigitalContactsTableModel(QObject* parent, int start_index)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "TG/DMR ID",
        "Call Alert",
        "Name",
        "City",
        "Call Type",
        "Callsign",
        "State/Prov",
        "Country",
        "Remarks"
    };

    this->start_index = start_index;
}

int DigitalContactsTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(20000);
}

int DigitalContactsTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant DigitalContactsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant DigitalContactsTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(20000)) return {}; //Anytone::Memory::digital_contacts.size()
    Anytone::DigitalContact *dc = Anytone::Memory::digital_contacts.at(start_index + row);
    if (!dc) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (dc->radio_id == 0);

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    if (empty) {
        // Keep index column visible, others blank like your previous "continue"
        if (col == ColIndex) {
            return QString::number(dc->id+1);
        }
        return {};
    }

    switch (col) {
        case ColIndex:
            return QString::number(dc->id+1);

        case ColRadioId:
            return QString::number(dc->radio_id);

        case ColAlert:
            if(dc->call_alert < 0 || dc->call_alert > 1){
                // qDebug() << dc->id << " " << dc->call_alert;
                return {};
            }
            return Constants::CALL_ALERT.at(dc->call_alert);

        case ColName:
            return dc->name;
        case ColCity:
            return dc->city;
        case ColType:
            if(dc->call_type < 0 || dc->call_type > 2){
                // qDebug() << dc->id << " " << dc->call_alert;
                return {};
            }
            return Constants::CALL_TYPE.at(dc->call_type);

        case ColCallsign:
            return dc->callsign;

        case ColState:
            return dc->state;

        case ColCountry:
            return dc->country;

        case ColRemarks:
            return dc->remarks;

        default:
            return {};
    }
}

void DigitalContactsTableModel::reload() {
    beginResetModel();
    endResetModel();
}