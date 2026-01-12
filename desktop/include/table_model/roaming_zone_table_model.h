#ifndef ROAMING_ZONE_TABLE_MODEL_H
#define ROAMING_ZONE_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QColor>
#include <vector>

class RoamingZoneTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColIndex = 0,
        ColName,
        ColChannels,
        ColCount
    };

    explicit RoamingZoneTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void reload();

private:
    QStringList m_headers;
};

#endif