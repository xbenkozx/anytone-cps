#ifndef HOTKEY_QUICK_CALL_TABLE_MODEL_H
#define HOTKEY_QUICK_CALL_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QStringList>
#include <QColor>
#include <vector>

class HotKeyQuickCallDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit HotKeyQuickCallDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent,
                           const QStyleOptionViewItem&,
                           const QModelIndex&) const override;

    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const override;

    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;

};

class HotKeyQuickCallTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColIndex = 0,
        ColOperation,
        ColCallId,
        ColCount
    };

    explicit HotKeyQuickCallTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
                        
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Call this when your underlying channels vector changes or after reading from radio
    void reload();

private:
    QStringList m_headers;
};

#endif