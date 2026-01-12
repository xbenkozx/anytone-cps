#ifndef DIGITAL_CONTACTS_TABLE_MODEL_H
#define DIGITAL_CONTACTS_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QColor>
#include <vector>

class DigitalContactsTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColIndex = 0,
        ColRadioId,
        ColAlert,
        ColName,
        ColCity,
        ColType,
        ColCallsign,
        ColState,
        ColCountry,
        ColRemarks,
        ColCount
    };

    explicit DigitalContactsTableModel(QObject* parent = nullptr, int start_index = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Call this when your underlying channels vector changes or after reading from radio
    void reload();

private:
    int start_index = 0;
    QStringList m_headers;
};

#endif