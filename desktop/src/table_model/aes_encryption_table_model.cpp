#include "aes_encryption_table_model.h"

#include <Qt>
#include <QBrush>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/aes_encryption_code.h"
#include "constants.h"

AesEncryptionTableModel::AesEncryptionTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Encryption ID",
        "Encryption Key"
    };
}

int AesEncryptionTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::aes_encryption_keys.size());
}

int AesEncryptionTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant AesEncryptionTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant AesEncryptionTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::aes_encryption_keys.size())) return {};
    Anytone::AesEncryptionCode *key = Anytone::Memory::aes_encryption_keys.at(row);
    if (!key) return {};

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    if (role == Qt::ForegroundRole) {
        if (col == ColKey && key->id == 0 && key->key_length > 0) {
            static const QBrush grayBrush(QColorConstants::Gray);
            return grayBrush;
        }
    }

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColId:
            if(key->id == 0) return "Off";
            return key->id;

        case ColKey:
            if(key->key_length == 0 && key->id > 0){
                return "XXXXXXXX";
            }else if(key->id == 0 && key->key_length == 0){
                return {};
            }else{
                return key->key;
            }

        default:
            return {};
    }
}

void AesEncryptionTableModel::reload() {
    beginResetModel();
    endResetModel();
}