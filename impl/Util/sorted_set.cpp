#include "impl/Util/sorted_set.h"

void init_sorted_set(SORTED_SET* set, int(*sort_fn)(const void*, const void*))
{
    srt_hset* item_set = shs_alloc(SHS_I, 0);
    srt_vector* item_vector = sv_alloc(
        sizeof(SET_ITEM),
        1,
        sort_fn
    );
    set->set = item_set;
    set->vec = item_vector;
    sv_sort(set->vec);
    // Probably need to use separate array for sorting vs storing elements.
}

SET_ITEM* sorted_set_peek(SORTED_SET* set)
{
    if (sv_size(set->vec) == 0) {
        return NULL;
    }
    return (SET_ITEM*)sv_at(set->vec, 0);
}

SET_ITEM* sorted_set_top(SORTED_SET* set)
{
    if (sv_size(set->vec) == 0) {
        return NULL;
    }
    SET_ITEM* top = (SET_ITEM*)sv_at(set->vec, 0);
    if (top != NULL) {
        shs_delete_i(set->set, ((SET_ITEM*)top)->id);
        sv_erase(&set->vec, 0, 1);
    }
    return top;
}

SET_ITEM* sorted_set_end(SORTED_SET* set)
{
    const int size = sv_size(set->vec);
    if (size == 0) {
        return NULL;
    }
    SET_ITEM* end = (SET_ITEM*)sv_at(set->vec, size - 1);
    if (end != NULL) {
        shs_delete_i(set->set, (end)->id);
        sv_erase(&set->vec, size - 1, 1);
    }
    return end;
}

SET_ITEM* sorted_set_at(SORTED_SET* set, int index)
{
    const int size = sv_size(set->vec);
    if (size == 0 || index < 0 || index >= size) {
        return NULL;
    }
    return (SET_ITEM*)sv_at(set->vec, index);
}

void sorted_set_add(SORTED_SET* set, SET_ITEM item)
{
    const int item_id = item.id;
    if (shs_count_i(set->set, item_id) == 1) {
        return;
    }
    shs_insert_i(&set->set, item_id);
    sv_push(&set->vec, (const void*)&item);
    sv_sort(set->vec);
}

int sorted_set_count(SORTED_SET* set)
{
    return sv_size(set->vec);
}
