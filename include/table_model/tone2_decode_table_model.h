#ifndef TONE2_DECODE_TABLE_MODEL_H
#define TONE2_DECODE_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStyledItemDelegate>
#include <QStringList>
#include <QColor>
#include <vector>

class Tone2DecodeTableModelDelegate : public QStyledItemDelegate {
    Q_OBJECT
public:
    explicit Tone2DecodeTableModelDelegate(QObject* parent = nullptr);

    QWidget* createEditor(QWidget* parent,
                           const QStyleOptionViewItem&,
                           const QModelIndex&) const override;

    void setEditorData(QWidget* editor,
                       const QModelIndex& index) const override;

    void setModelData(QWidget* editor,
                      QAbstractItemModel* model,
                      const QModelIndex& index) const override;
};
    
class Tone2DecodeTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColIndex = 0,
        ColTone1,
        ColTone2,
        ColResponse,
        ColName,
        ColCount
    };

    explicit Tone2DecodeTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Call this when your underlying channels vector changes or after reading from radio
    void reload();

private:
    QStringList m_headers;
};

#endif