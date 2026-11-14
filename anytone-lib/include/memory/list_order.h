#ifndef ANYTONE_LIST_ORDER_H
#define ANYTONE_LIST_ORDER_H

#include <QVector>

namespace Anytone {

    // Reordering of the fixed-size slot lists (channels, zones, ...).
    //
    // In a codeplug the id of an entry is its slot in the radio's memory and
    // other objects refer to entries by that id.  Reordering therefore has
    // three steps that always happen together in apply():
    //   1. the entries are permuted inside Memory::<list>,
    //   2. every entry gets the id of its new slot,
    //   3. every stored index that points into the list is translated from the
    //      old slot to the new slot (zone/scan list members are pointers and
    //      follow the objects automatically, but the index fields do not).
    //
    // A permutation is a QVector<int> "order" with order[new_slot] = old_slot.
    class ListOrder {
    public:
        enum class Kind {
            Channel,
            Zone,
            Talkgroup,
            RoamingChannel,
            AnalogAddress
        };
        enum class Move {
            Up,
            Down,
            Top,
            Bottom
        };

        // Number of slots that take part in reordering. Slots at or above this
        // value are fixed (channels 4000/4001 are VFO A/B).
        static int count(Kind kind);
        // Slot holds no usable entry (same definition the writers use).
        static bool isEmpty(Kind kind, int slot);
        // The radio does not keep empty slots (zones, analog address book), so
        // every move also packs the used entries to the front.
        static bool compacts(Kind kind);

        // Permutation for moving the entries in the given slots; empty if the
        // move would not change anything.
        static QVector<int> orderForMove(Kind kind, const QVector<int> &selected_slots, Move move);
        // Permutation for "make the list look like this view": view_slots are
        // the slots in display order. Fixed slots are ignored, used entries
        // come first (in view order), empty slots follow. Empty result if
        // view_slots does not contain every slot exactly once.
        static QVector<int> orderForView(Kind kind, const QVector<int> &view_slots);

        static bool isValidOrder(Kind kind, const QVector<int> &order);
        // Permute the list, renumber the ids and remap all references.
        // Returns false (and changes nothing) if order is not valid. For lists
        // that compact() the used entries are packed to the front as well.
        static bool apply(Kind kind, const QVector<int> &order);
    };
}

#endif
