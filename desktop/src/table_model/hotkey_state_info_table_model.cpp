#include "hotkey_state_info_table_model.h"

#include <Qt>
#include <QBrush>
#include <QLineEdit>

// include your actual Channel + Constants headers
#include "memory/at_memory.h"
#include "memory/hotkey.h"
#include "constants.h"

HotKeyStateInfoDelegate::HotKeyStateInfoDelegate(QObject* parent)
    : QStyledItemDelegate(parent){}

QWidget* HotKeyStateInfoDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex&) const {
    auto* edit = new QLineEdit(parent);
    edit->setMaxLength(32);
    return edit;
}
void HotKeyStateInfoDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
    auto* edit = qobject_cast<QLineEdit*>(editor);
    edit->setText(index.data(Qt::DisplayRole).toString());
}
void HotKeyStateInfoDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    auto* edit = qobject_cast<QLineEdit*>(editor);
    model->setData(index, edit->text(), Qt::EditRole);
}

HotkeyStateInfoTableModel::HotkeyStateInfoTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    m_headers = {
        "No.",
        "State Information"
    };
}

int HotkeyStateInfoTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::hotkey->state_content_list.size());
}

int HotkeyStateInfoTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

QVariant HotkeyStateInfoTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

QVariant HotkeyStateInfoTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::hotkey->state_content_list.size())) return {};
    QString text = Anytone::Memory::hotkey->state_content_list.at(row);

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColInfo:
            return text;

        default:
            return {};
    }
}

void HotkeyStateInfoTableModel::reload() {
    beginResetModel();
    endResetModel();
}

bool HotkeyStateInfoTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    const int row = index.row();
    if (row < 0 || row >= static_cast<int>(Anytone::Memory::hotkey->state_content_list.size())) return true;

    int idx = -1;
    switch (index.column()) {
        case ColInfo:
            Anytone::Memory::hotkey->state_content_list[row] = value.toString();
            break;

        default:
            break;
    }

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

Qt::ItemFlags HotkeyStateInfoTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid() || index.column() == 0) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}