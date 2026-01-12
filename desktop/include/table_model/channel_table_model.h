#ifndef CHANNEL_TABLE_MODEL_H
#define CHANNEL_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QColor>
#include <QHash>
#include <QPersistentModelIndex>
#include <QBrush>
#include <vector>

#include "memory/at_memory.h"
#include "channel.h"

class ChannelTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColIndex = 0,
        ColRx,
        ColTx,
        ColType,
        ColPower,
        ColBW,
        ColDecode,
        ColEncode,
        ColName,
        ColContact,
        ColRadioId,
        ColOptional,
        ColCount
    };

    explicit ChannelTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Call this when your underlying channels vector changes or after reading from radio
    void reload();

private:
    QStringList m_headers;
    QHash<QPersistentModelIndex, QBrush> m_fgOverrides;
};

#endif