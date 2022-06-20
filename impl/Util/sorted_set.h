#include <svector.h>
#include <shset.h>

typedef struct sorted_set {
    srt_vector* vec;
    srt_hset  * set;
} SORTED_SET;

typedef struct set_item {
    int id;
    unsigned int size;
    void* node;
} SET_ITEM;

extern void init_sorted_set(SORTED_SET* set, int(*sort_fn)(const void*, const void*));

extern SET_ITEM* sorted_set_peek(SORTED_SET* set);

extern SET_ITEM* sorted_set_top(SORTED_SET* set);

extern SET_ITEM* sorted_set_end(SORTED_SET* set);

extern void sorted_set_add(SORTED_SET* set, SET_ITEM item);

extern SET_ITEM* sorted_set_at(SORTED_SET* set, int index);

extern int sorted_set_count(SORTED_SET* set);
