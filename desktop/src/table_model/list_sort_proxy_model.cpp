#include "list_sort_proxy_model.h"

#include <QCollator>

ListSortProxyModel::ListSortProxyModel(Anytone::ListOrder::Kind kind, QObject *parent)
    : QSortFilterProxyModel(parent), m_kind(kind)
{
    setDynamicSortFilter(false);
}

int ListSortProxyModel::slotOf(const QModelIndex &proxy_index) const {
    return mapToSource(proxy_index).row();
}

QVector<int> ListSortProxyModel::viewSlots() const {
    QVector<int> order;
    order.reserve(rowCount());
    for(int row = 0; row < rowCount(); row++){
        order.append(slotOf(index(row, 0)));
    }
    return order;
}

bool ListSortProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const {
    const bool ascending = sortOrder() == Qt::AscendingOrder;
    const int row_l = left.row();
    const int row_r = right.row();

    // 0 = used entry, 1 = empty slot, 2 = fixed slot; flipped for descending
    // sorts because the proxy reverses the result.
    auto rank = [this](int row){
        if(row >= Anytone::ListOrder::count(m_kind)) return 2;
        return Anytone::ListOrder::isEmpty(m_kind, row) ? 1 : 0;
    };
    const int rank_l = rank(row_l);
    const int rank_r = rank(row_r);
    if(rank_l != rank_r) return ascending ? rank_l < rank_r : rank_l > rank_r;

    // equal entries keep their natural order in both directions
    auto by_row = [&]{ return ascending ? row_l < row_r : row_l > row_r; };
    if(rank_l != 0) return by_row();

    const QString text_l = sourceModel()->data(left, Qt::DisplayRole).toString();
    const QString text_r = sourceModel()->data(right, Qt::DisplayRole).toString();

    // empty text < numbers < other text
    bool num_l = false, num_r = false;
    const double value_l = text_l.toDouble(&num_l);
    const double value_r = text_r.toDouble(&num_r);
    auto kind_of = [](const QString &t, bool num){ return t.isEmpty() ? 0 : num ? 1 : 2; };
    const int kind_l = kind_of(text_l, num_l);
    const int kind_r = kind_of(text_r, num_r);
    if(kind_l != kind_r) return kind_l < kind_r;

    if(kind_l == 1){
        if(value_l != value_r) return value_l < value_r;
        return by_row();
    }
    if(kind_l == 2){
        static const QCollator collator = []{
            QCollator c;
            c.setNumericMode(true);
            c.setCaseSensitivity(Qt::CaseInsensitive);
            return c;
        }();
        const int cmp = collator.compare(text_l, text_r);
        if(cmp != 0) return cmp < 0;
    }
    return by_row();
}
