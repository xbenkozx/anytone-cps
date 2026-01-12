#include "tone2_decode_table_model.h"
#include "tone2_settings.h"

#include <Qt>
#include <QBrush>
#include <QLineEdit>
#include <QComboBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

#include "memory/at_memory.h"
// #include "memory/fm.h"
#include "constants.h"

Tone2DecodeTableModelDelegate::Tone2DecodeTableModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}

QWidget* Tone2DecodeTableModelDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex& index) const {
    
    if(index.column() == 4){
        auto* edit = new QLineEdit(parent);
        edit->setMaxLength(7);
        return edit;
    }else if(index.column() == 3){
        auto* edit = new QComboBox(parent);
        edit->addItems(QStringList{"None", "Beep Tone", "Beep Tone & Respond"});
        return edit;
    }else{
        auto* edit = new QLineEdit(parent);
        edit->setMaxLength(5);
        edit->setValidator(
            new QRegularExpressionValidator(
                QRegularExpression("^\\d*\\.?\\d*$"),
                edit
            )
        );
        return edit;
    }
}

void Tone2DecodeTableModelDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
                                        
    if(index.column() == 3){
        auto* edit = qobject_cast<QComboBox*>(editor);
        edit->setCurrentText(index.data(Qt::DisplayRole).toString());
    }else{
        auto* edit = qobject_cast<QLineEdit*>(editor);
        edit->setText(index.data(Qt::DisplayRole).toString());
    }
    
}

void Tone2DecodeTableModelDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    
    if(index.column() == 3){
        auto* edit = qobject_cast<QComboBox*>(editor);
        model->setData(index, edit->currentIndex(), Qt::EditRole);
    }else{
        auto* edit = qobject_cast<QLineEdit*>(editor);
        model->setData(index, edit->text(), Qt::EditRole);
    }
    
}

Tone2DecodeTableModel::Tone2DecodeTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "1st Tone\nFrequency[Hz]",
        "2nd Tone\nFrequency[Hz]",
        "Decoding Response",
        "Name"
    };
}

int Tone2DecodeTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::tone2_settings->decode_list.size());
}

int Tone2DecodeTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

Qt::ItemFlags Tone2DecodeTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant Tone2DecodeTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

bool Tone2DecodeTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Anytone::Tone2DecodeItem *item = Anytone::Memory::tone2_settings->decode_list.at(index.row());
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

        case ColResponse:
            item->decoding_response = value.toInt();
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

QVariant Tone2DecodeTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::tone2_settings->decode_list.size())) return {};
    Anytone::Tone2DecodeItem *item = Anytone::Memory::tone2_settings->decode_list.at(row);
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

        case ColResponse:
            return QStringList{"None", "Beep Tone", "Beep Tone & Respond"}.at(item->decoding_response);

        case ColName:
            return item->name;

        default:
            return {};
    }
}

void Tone2DecodeTableModel::reload() {
    beginResetModel();
    endResetModel();
}