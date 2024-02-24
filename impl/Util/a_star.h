#ifndef A_STAR_H
#define A_STAR_H

extern void find_path_in_grid(
    int* path_length,
    int** path,
    int blocked_count,
    int* blocked,
    int horizontal_element_count,
    int vertical_element_count,
    int start_index,
    int end_index
);

#endif /* A_STAR_H */
