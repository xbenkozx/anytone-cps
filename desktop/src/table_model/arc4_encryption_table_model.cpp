#include "arc4_encryption_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/arc4_encryption_code.h"
#include "constants.h"

Arc4EncryptionTableModel::Arc4EncryptionTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Encryption ID",
        "Encryption Key"
    };
}

int Arc4EncryptionTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::arc4_encryption_keys.size());
}

int Arc4EncryptionTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant Arc4EncryptionTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant Arc4EncryptionTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::arc4_encryption_keys.size())) return {};
    Anytone::Arc4EncryptionCode *key = Anytone::Memory::arc4_encryption_keys.at(row);
    if (!key) return {};

    const bool empty = (key->id == 0);

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

        case ColId:
            return key->id;

        case ColKey:
            return key->key;

        default:
            return {};
    }
}

void Arc4EncryptionTableModel::reload() {
    beginResetModel();
    endResetModel();
}