#ifndef HOTKEY_STATE_INFO_TABLE_MODEL_H
#define HOTKEY_STATE_INFO_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QStringList>
#include <QColor>
#include <vector>

class HotKeyStateInfoDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit HotKeyStateInfoDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent,
                           const QStyleOptionViewItem&,
                           const QModelIndex&) const override;

    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const override;

    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;

};

class HotkeyStateInfoTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColIndex = 0,
        ColInfo,
        ColCount
    };

    explicit HotkeyStateInfoTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void reload();

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    QStringList m_headers;
};

#endif