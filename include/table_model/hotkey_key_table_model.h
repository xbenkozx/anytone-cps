#ifndef HOTKEY_KEY_TABLE_MODEL_H
#define HOTKEY_KEY_TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QColor>
#include <vector>

class HotkeyKeyTableModel final : public QAbstractTableModel {
    Q_OBJECT
public:
    enum Col {
        ColKey,
        ColMode,
        ColMenu,
        ColCallType,
        ColCallObj,
        ColDigiCallType,
        ColContent,
        ColCount
    };

    explicit HotkeyKeyTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Call this when your underlying channels vector changes or after reading from radio
    void reload();

private:
    QStringList m_headers;
};

#endif