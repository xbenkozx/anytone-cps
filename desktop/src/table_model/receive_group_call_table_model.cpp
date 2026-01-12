#include "receive_group_call_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/at_memory.h"
#include "memory/receive_group_call_list.h"
#include "talkgroup.h"
#include "constants.h"

ReceiveGroupCallTableModel::ReceiveGroupCallTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Group Name",
        "Group\nContacts",
        "Contact"
    };
}

int ReceiveGroupCallTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::receive_group_call_lists.size());
}

int ReceiveGroupCallTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant ReceiveGroupCallTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant ReceiveGroupCallTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::receive_group_call_lists.size())) return {};
    Anytone::ReceiveGroup *rgcl = Anytone::Memory::receive_group_call_lists.at(row);
    if (!rgcl) return {};

    // Optional: hide "empty" rows like you did when rx_frequency == 0
    // With QAbstractTableModel you typically *don’t skip rows*; you just show blanks.
    const bool empty = (rgcl->talkgroups.size() == 0);

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
    QString name_list = "";
    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColName:
            return rgcl->name;

        case ColGroups:
            return QString::number(rgcl->talkgroups.size());

        case ColContact:
            
            for(Anytone::Talkgroup *tg : rgcl->talkgroups){
                name_list += "|" + tg->name;
            }
            return name_list.removeAt(0);

        default:
            return {};
    }
}

void ReceiveGroupCallTableModel::reload() {
    beginResetModel();
    endResetModel();
}