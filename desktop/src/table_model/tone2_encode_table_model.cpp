#include "tone2_encode_table_model.h"
#include "tone2_settings.h"

#include <Qt>
#include <QBrush>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

#include "memory/at_memory.h"
// #include "memory/fm.h"
#include "constants.h"

Tone2EncodeTableModelDelegate::Tone2EncodeTableModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}

QWidget* Tone2EncodeTableModelDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex& index) const {
    auto* edit = new QLineEdit(parent);
    if(index.column() == 3){
        edit->setMaxLength(7);
    }else{
        edit->setMaxLength(5);
        edit->setValidator(
            new QRegularExpressionValidator(
                QRegularExpression("^\\d*\\.?\\d*$"),
                edit
            )
        );
    }
    return edit;
}

void Tone2EncodeTableModelDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
    auto* edit = qobject_cast<QLineEdit*>(editor);
    edit->setText(index.data(Qt::DisplayRole).toString());
}

void Tone2EncodeTableModelDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    auto* edit = qobject_cast<QLineEdit*>(editor);
    model->setData(index, edit->text(), Qt::EditRole);
    
}

Tone2EncodeTableModel::Tone2EncodeTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "1st Tone\nFrequency[Hz]",
        "2nd Tone\nFrequency[Hz]",
        "Name"
    };
}

int Tone2EncodeTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::tone2_settings->encode_list.size());
}

int Tone2EncodeTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

Qt::ItemFlags Tone2EncodeTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant Tone2EncodeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

bool Tone2EncodeTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Anytone::Tone2EncodeItem *item = Anytone::Memory::tone2_settings->encode_list.at(index.row());
    if(!item) return false;
    double freq = 0;
    switch (index.column()) {
        case ColTone1:
            freq = value.toDouble();
            if(freq != 0){
                if(freq < 288) freq = 288;
                if(freq > 3106) freq = 3106;
            }
            item->tone_frequency_1 = static_cast<uint16_t>(freq * 10);
            break;

        case ColTone2:
            freq = value.toDouble();
            if(freq < 288) freq = 288;
            if(freq > 3106) freq = 3106;
            item->tone_frequency_2 = static_cast<uint16_t>(freq * 10);
            break;

        case ColName:
            item->name = value.toString();
            break;

        default:
            break;
    }

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

QVariant Tone2EncodeTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::tone2_settings->encode_list.size())) return {};
    Anytone::Tone2EncodeItem *item = Anytone::Memory::tone2_settings->encode_list.at(row);
    if (!item) return {};

    const bool empty = (item->tone_frequency_1 == 0);

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

        case ColTone1:
            return QString::number(double(item->tone_frequency_1)/10, 'f', 1);

        case ColTone2:
            return QString::number(double(item->tone_frequency_2)/10, 'f', 1);

        case ColName:
            return item->name;

        default:
            return {};
    }
}

void Tone2EncodeTableModel::reload() {
    beginResetModel();
    endResetModel();
}