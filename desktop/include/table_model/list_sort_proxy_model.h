#ifndef LIST_SORT_PROXY_MODEL_H
#define LIST_SORT_PROXY_MODEL_H

#include <QSortFilterProxyModel>
#include <QVector>
#include "memory/list_order.h"

// Display-only sort for the slot lists (channels, zones, ...).
// Sorting the view never touches the codeplug; Anytone::ListOrder renumbers the
// entries when the user applies the order. Empty slots and fixed slots (VFO
// A/B) always stay at the end, in both sort directions.
class ListSortProxyModel final : public QSortFilterProxyModel {
    Q_OBJECT
public:
    explicit ListSortProxyModel(Anytone::ListOrder::Kind kind, QObject *parent = nullptr);

    Anytone::ListOrder::Kind kind() const { return m_kind; }
    bool isSorted() const { return sortColumn() >= 0; }
    // Slot (source row) of a proxy index
    int slotOf(const QModelIndex &proxy_index) const;
    // All slots in display order
    QVector<int> viewSlots() const;

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    Anytone::ListOrder::Kind m_kind;
};

#endif
