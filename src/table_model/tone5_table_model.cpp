#include "tone5_table_model.h"
#include "tone5_settings.h"

#include <Qt>
#include <QBrush>
#include <QLineEdit>
#include <QComboBox>
#include <QRegularExpressionValidator>
#include <QRegularExpression>

#include "memory/memory.h"
// #include "memory/fm.h"
#include "constants.h"

Tone5TableModelDelegate::Tone5TableModelDelegate(QObject* parent)
    : QStyledItemDelegate(parent) {}

QWidget* Tone5TableModelDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex& index) const {
    
    if(index.column() == 2){
        auto* edit = new QLineEdit(parent);
        edit->setValidator(
            new QRegularExpressionValidator(
                QRegularExpression("^[0-9abcdefABCDEF]+$"),
                edit
            )
        );
        edit->setMaxLength(40);
        return edit;
    }else if(index.column() == 3){
        auto* edit = new QComboBox(parent);
        edit->addItems(Constants::DECODING_STANDARD);
        return edit;
    }else if(index.column() == 4){
        auto* edit = new QComboBox(parent);
        for(int i = 30; i < 101; i++){
            edit->addItem(QString::number(i));
        }
        return edit;
    }else{
        auto* edit = new QLineEdit(parent);
        edit->setMaxLength(7);
        return edit;
    }
}

void Tone5TableModelDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
                                        
    if(index.column() == 3 || index.column() == 4){
        auto* edit = qobject_cast<QComboBox*>(editor);
        edit->setCurrentText(index.data(Qt::DisplayRole).toString());
    }else{
        auto* edit = qobject_cast<QLineEdit*>(editor);
        edit->setText(index.data(Qt::DisplayRole).toString());
    }
    
}

void Tone5TableModelDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    
    if(index.column() == 3 || index.column() == 4){
        auto* edit = qobject_cast<QComboBox*>(editor);
        model->setData(index, edit->currentIndex(), Qt::EditRole);
    }else{
        auto* edit = qobject_cast<QLineEdit*>(editor);
        if(index.column() == 2){
            model->setData(index, edit->text().toUpper(), Qt::EditRole);
        }else{
            model->setData(index, edit->text(), Qt::EditRole);
        }
        
    }
    
}

Tone5TableModel::Tone5TableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Special Call",
        "Encode ID",
        "Encode/Decode\nStandard",
        "Time Of\nEncode Tone[ms]",
        "Name"
    };
}

int Tone5TableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::tone5_settings->special_call_list.size());
}

int Tone5TableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}

Qt::ItemFlags Tone5TableModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) return Qt::NoItemFlags;
    if(index.column() == 1){
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant Tone5TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}

bool Tone5TableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Anytone::SpecialCall *item = Anytone::Memory::tone5_settings->special_call_list.at(index.row());
    if(!item) return false;
    double freq = 0;
    switch (index.column()) {
        case ColSpecialCall:

        case ColEncodeId:
            item->encode_id = value.toString();
            break;
        case ColStandard:
            item->standard = value.toInt();
            break;
        case ColToneTime:
            item->tone_time = value.toInt();
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

QVariant Tone5TableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::tone5_settings->special_call_list.size())) return {};
    Anytone::SpecialCall *item = Anytone::Memory::tone5_settings->special_call_list.at(row);
    if (!item) return {};

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    if (role == Qt::BackgroundRole && col == 1) {
        return QBrush(QColor(230, 230, 230));  // light gray
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColSpecialCall:
            return "";

        case ColEncodeId:
            return item->encode_id;

        case ColStandard:
            return Constants::DECODING_STANDARD.at(item->standard);

        case ColToneTime:
            return QString::number(item->tone_time+30);
            break;

        case ColName:
            return item->name;

        default:
            return {};
    }
}

void Tone5TableModel::reload() {
    beginResetModel();
    endResetModel();
}