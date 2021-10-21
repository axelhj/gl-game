#include "a_star.h"
#include "sorted_set.h"
#include "shset.h"
#include "svector.h"
#include <cstdlib>
#include <math.h>

typedef struct graph_node GRAPH_NODE;

typedef struct graph_node {
    int index;
    int x;
    int y;
    GRAPH_NODE* adjacent[8];
    float distance_accumulated;
    float estimated_cost;
    GRAPH_NODE* previous;
} GRAPH_NODE;

typedef struct grid_search_instance {
    int hor;
    int ver;
    GRAPH_NODE** nodes;
    int node_count;
    srt_hset* excluded_nodes;
    int excluded_nodes_count;
} GRID_SEARCH_INSTANCE;

static int compare(const void *a, const void *b) {
    return (
        ((GRAPH_NODE*)((SET_ITEM*)b)->node)->estimated_cost -
        ((GRAPH_NODE*)((SET_ITEM*)a)->node)->estimated_cost
    );
}

void init_node(GRAPH_NODE* node, int index, int hor, int ver)
{
    node->index = index;
    node->x = (int)fmod(index, hor);
    node->y = (int)index / hor;
    for (int i = 0; i < 8; ++i) {
        node->adjacent[i] = NULL;
    }
    node->distance_accumulated = 0;
    node->estimated_cost = 0;
    node->previous = NULL;
}

void init_grid_search(
    GRID_SEARCH_INSTANCE* grid_search,
    srt_hset* excluded_nodes,
    int hor,
    int ver
)
{
    grid_search->hor = hor;
    grid_search->ver = ver;
    grid_search->excluded_nodes = excluded_nodes;
    grid_search->excluded_nodes_count = shs_size(excluded_nodes);
    grid_search->node_count = hor * ver;
    // TODO: Figure out how to dispose of array afterwards without VLA.
    grid_search->nodes = (GRAPH_NODE**)malloc(sizeof(GRAPH_NODE*) * grid_search->node_count);
    for (int i = 0; i < grid_search->node_count; ++i) {
        grid_search->nodes[i] = NULL;
    }
}

GRAPH_NODE* find_or_create_node(
    GRID_SEARCH_INSTANCE* grid_search,
    int node_index
)
{
    if (shs_count_i(grid_search->excluded_nodes, node_index) > 0) {
        return NULL;
    }
    GRAPH_NODE* node = grid_search->nodes[node_index];
    if (node != NULL) {
        return node;
    }
    GRAPH_NODE* fresh_node = (GRAPH_NODE*)malloc(sizeof(GRAPH_NODE));
    init_node(fresh_node, node_index, grid_search->hor, grid_search->ver);
    grid_search->nodes[node_index] = fresh_node;
    return fresh_node;
}

void find_adjacent(GRID_SEARCH_INSTANCE* grid_search, int node_index)
{
    GRAPH_NODE* node = find_or_create_node(grid_search, node_index);
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < 8; ++i) {
        if (node->adjacent[i] != NULL) {
            return;
        }
    }
    for (int i = 0; i < 8; ++i) {
        node->adjacent[i] = NULL;
    }
    //  Skip diagonals for now. [node, cost]
    int x = (int)fmod(node_index, grid_search->hor);
    int y = (int)node_index / grid_search->hor;
    if (x != grid_search->hor - 1) {
        node->adjacent[1] = find_or_create_node(grid_search, node_index + 1);
    }
    if (y != grid_search->ver - 1) {
        node->adjacent[3] = find_or_create_node(grid_search, node_index + grid_search->hor);
    }
    if (x != 0) {
        node->adjacent[4] = find_or_create_node(grid_search, node_index - 1);
    }
    if (y != 0) {
        node->adjacent[6] = find_or_create_node(grid_search, node_index - grid_search->hor);
    }
}

float get_score(GRAPH_NODE* node)
{
    return node->distance_accumulated + node->estimated_cost;
}

float cost(GRAPH_NODE* a, GRAPH_NODE* b) {
    return abs(b->x - a->x) + abs(b->y - a->y);
}

GRAPH_NODE* find_path(GRID_SEARCH_INSTANCE* grid_search, GRAPH_NODE* start, GRAPH_NODE* end)
{
    SORTED_SET sorted_nodes;
    init_sorted_set(&sorted_nodes, compare);
    GRAPH_NODE* current = start;
    srt_hset* visited_nodes = shs_alloc(SHS_I, grid_search->node_count);
    shs_insert_i(&visited_nodes, start->index);
    srt_vector* path = sv_alloc(
        sizeof(GRAPH_NODE*),
        1,
        NULL
    );
    while (true) {
        find_adjacent(grid_search, current->index);
        for (int i = 0; i < 8; ++i) {
            GRAPH_NODE* node = current->adjacent[i];
            if (node == NULL) {
                continue;
            }
            if (node->estimated_cost == 0) {
                node->estimated_cost = cost(node, end);
            }
            int new_accumulated_distance = current->distance_accumulated + 1;
            if (
                node->distance_accumulated == 0 ||
                new_accumulated_distance < node->distance_accumulated
            ) {
                node->previous = current;
                node->distance_accumulated = new_accumulated_distance;
                SET_ITEM item;
                item.id = node->index;
                item.size = sizeof (GRAPH_NODE);
                item.node = (void*)node;
                sorted_set_add(&sorted_nodes, item);
            }
        }
        if (current->index == end->index) {
            sv_clear(path);
            sv_push(&path, end);
            GRAPH_NODE* node = end->previous;
            while (node->index != start->index) {
                sv_push(&path, node);
                node = node->previous;
            }
            sv_push(&path, start);
            return end;
        }
        if ((int)shs_size(visited_nodes) == (grid_search->node_count - grid_search->excluded_nodes_count)) {
            return NULL;
        }
        SET_ITEM* item = sorted_set_top(&sorted_nodes);
        GRAPH_NODE* node;
        node = item == NULL ? NULL : (GRAPH_NODE*)item->node;
        while (
            (node == NULL && sorted_set_count(&sorted_nodes) != 0) ||
            (node != NULL && shs_count_i(visited_nodes, node->index))
        )
        {
            SET_ITEM* item = sorted_set_top(&sorted_nodes);
            if (item == NULL) {
                return NULL;
            }
            node = (GRAPH_NODE*)item->node;
        }
        current = node;
        shs_insert_i(&visited_nodes, node->index);
        if (current == NULL) {
            return NULL;
        }
    }
}

void find_path_in_grid(
    int* path_length,
    int** path,
    int blocked_count,
    int* blocked,
    int horizontal_element_count,
    int vertical_element_count,
    int start_index,
    int end_index
) {
    srt_hset* excluded_items = shs_alloc(SHS_I, blocked_count);
    for (int i = 0; i < blocked_count; ++i) {
        shs_insert_i(&excluded_items, blocked[i]);
    }
    int i = 0;
    GRID_SEARCH_INSTANCE* grid_search = (GRID_SEARCH_INSTANCE*)malloc(sizeof(GRID_SEARCH_INSTANCE));
    init_grid_search(grid_search, excluded_items, horizontal_element_count, vertical_element_count);
    GRAPH_NODE* result = find_path(
        grid_search,
        find_or_create_node(grid_search, start_index),
        find_or_create_node(grid_search, end_index)
    );
    *path_length = 0;
    GRAPH_NODE* graph_iterator = result;
    while (
       graph_iterator != NULL &&
       graph_iterator->index != start_index
   ) {
        ++*path_length;
        if (graph_iterator->previous != NULL) {
            graph_iterator = graph_iterator->previous;
        } else {
            break;
        }
    }
    if (*path_length > 0 && result != NULL) {
        *path = (int*)malloc(sizeof(int) * ((*path_length) + 1));
        graph_iterator = result;
        for (int i = 0; i < (*path_length) && graph_iterator != NULL; ++i) {
            (*path)[i] = graph_iterator->index;
            graph_iterator = graph_iterator->previous;
        }
        (*path)[*path_length] = graph_iterator->index;
    }
}
