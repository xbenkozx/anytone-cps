#include "hotkey_quick_call_table_model.h"

#include <Qt>
#include <QBrush>
#include <QComboBox>

// include your actual Channel + Constants headers
#include "memory/anytone_memory.h"
#include "memory/hotkey.h"
#include "constants.h"
#include "dtmf_settings.h"

HotKeyQuickCallDelegate::HotKeyQuickCallDelegate(QObject* parent)
    : QStyledItemDelegate(parent){}

QWidget* HotKeyQuickCallDelegate::createEditor(QWidget* parent,
                                        const QStyleOptionViewItem&,
                                        const QModelIndex &index) const {
    auto* combo = new QComboBox(parent);
    const int row = index.row();
    Anytone::AnalogQuickCall *quick_call = Anytone::Memory::hotkey->quick_call_list.at(row);
    if(index.column() == HotKeyQuickCallTableModel::ColOperation){
        combo->addItems(QStringList{"Off", "DTMF", "2Tone", "5Tone"});
    }else if(index.column() == HotKeyQuickCallTableModel::ColCallId){
        combo->addItem("Off", QVariant::fromValue((uint8_t)0xff));
        if(quick_call->operation_type == 1){
            Anytone::DTMFSettings *dtmf = Anytone::Memory::dtmf_settings;
            QStringList dtmf_list = {
                dtmf->m1, dtmf->m2, dtmf->m3, dtmf->m4, dtmf->m5, dtmf->m6, dtmf->m7, dtmf->m8,
                dtmf->m9, dtmf->m10, dtmf->m11, dtmf->m12, dtmf->m13, dtmf->m14, dtmf->m15, dtmf->m16
            };

            for(int i = 0; i < dtmf_list.size(); i++){
                QString s = dtmf_list.at(i);
                if(s.isEmpty()) continue;
                combo->addItem(QString::number(i+1), QVariant::fromValue(i));
            }

        }else if(quick_call->operation_type == 2){

        }else if(quick_call->operation_type == 3){

        }
    }
    return combo;
}
void HotKeyQuickCallDelegate::setEditorData(QWidget* editor,
                                     const QModelIndex& index) const {
    auto* combo = qobject_cast<QComboBox*>(editor);
    combo->setCurrentText(index.data(Qt::DisplayRole).toString());
}
void HotKeyQuickCallDelegate::setModelData(QWidget* editor,
                                    QAbstractItemModel* model,
                                    const QModelIndex& index) const {
    auto* combo = qobject_cast<QComboBox*>(editor);
    if(index.column() == HotKeyQuickCallTableModel::ColOperation){
        model->setData(index, combo->currentIndex(), Qt::EditRole);
    }else if(index.column() == HotKeyQuickCallTableModel::ColCallId){
         model->setData(index, combo->currentData(), Qt::EditRole);
    }
}

HotKeyQuickCallTableModel::HotKeyQuickCallTableModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    // Use your existing TABLE_HEADERS here
    m_headers = {
        "No.",
        "Operation Type",
        "Call ID"
    };
}
int HotKeyQuickCallTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return static_cast<int>(Anytone::Memory::hotkey->quick_call_list.size());
}
int HotKeyQuickCallTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) return 0;
    return ColCount;
}
QVariant HotKeyQuickCallTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        if (section >= 0 && section < m_headers.size()) return m_headers[section];
    }
    return {};
}
QVariant HotKeyQuickCallTableModel::data(const QModelIndex& idx, int role) const {
    if (!idx.isValid()) return {};

    const int row = idx.row();
    const int col = idx.column();

    if (row < 0 || row >= static_cast<int>(Anytone::Memory::hotkey->quick_call_list.size())) return {};
    Anytone::AnalogQuickCall *item = Anytone::Memory::hotkey->quick_call_list.at(row);
    if (!item) return {};

    // ---- Alignment (fast: role computed, not stored per-cell) ----
    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    // ---- Display text ----
    if (role != Qt::DisplayRole) return {};

    switch (col) {
        case ColIndex:
            return QString::number(row + 1);

        case ColOperation:
            return QStringList{"Off", "DTMF", "2Tone", "5Tone"}.at(item->operation_type);

        case ColCallId:
            if(item->call_id == 0xff) return "Off";
            return QString::number(item->call_id + 1);

        default:
            return {};
    }
}
void HotKeyQuickCallTableModel::reload() {
    beginResetModel();
    endResetModel();
}

bool HotKeyQuickCallTableModel::setData(const QModelIndex& index, const QVariant& value, int role) {
    if (!index.isValid() || role != Qt::EditRole) return false;

    Anytone::AnalogQuickCall *filter = Anytone::Memory::hotkey->quick_call_list.at(index.row());
    if(!filter) return false;

    int idx = -1;
    switch (index.column()) {
        case ColOperation:
            filter->operation_type = value.toInt();
            break;

        case ColCallId:
            filter->call_id = value.toInt();
            break;

        default:
            break;
    }

    emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    return true;
}

Qt::ItemFlags HotKeyQuickCallTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid() || index.column() == 0) return Qt::NoItemFlags;
    Anytone::AnalogQuickCall *quick_call = Anytone::Memory::hotkey->quick_call_list.at(index.row());
    if(quick_call->operation_type == 0 && index.column() == ColCallId) return Qt::NoItemFlags;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}