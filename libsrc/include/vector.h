//
// Created by Mitchel on 17-7-2023.
//

#ifndef VECTOR_H__
#define VECTOR_H__

#ifndef VECTOR_START_CAPACITY
    #define VECTOR_START_CAPACITY 8
#endif // start-capacity

#include <stdbool.h>
#include <stddef.h>

#include "../private/private_macros.h"


typedef struct vector_ vector_t;

/**
 * Creates a vector with elem_size as memory-block partitions.
 * @param elem_size The size of the elements that the vector will be populated with.
 * @return A pointer to a `struct vector_` that lives on the heap.
 */
NODISCARD
vector_t* vector_create(size_t elem_size);

/**
 * Creates a vector from an array.
*/
NODISCARD
vector_t* vector_create_from(size_t elem_size, size_t elem_count, const void* start_addr);

/**
 * Deletes the vector and its memory-block from the heap..
 * @param vec
 */
void vector_clean(vector_t* vec);

/**
 * Cleans up each individual element in the vector, and then calls vector_clean to clean up the vector itself.
 * @param vec The vector to be cleaned up.
 * @param clean_func The cleaning function that cleans each individual element.
 */
void vector_clean_deep(vector_t* vec, void (*clean_func)(void*));

/**
 * Gets the amount of elements in the vector.
 * @param vec
 * @return
 */
size_t vector_get_elem_count(const vector_t* vec);
/**
 * Gets the capacity of the vector.
 * @param vec
 * @return
 */
size_t vector_get_capacity(const vector_t* vec);
/**
 * Gets the size of a block-partition (a.k.a the size of an individual element).
 * @param vec
 * @return
 */
size_t vector_get_elem_size(const vector_t* vec);
/**
 * Gets the start address of the memory-block.
 * \n\n
 * <b>
 * *
 * Should only be used when extreme speed is necessary, as
 * this block gets reallocated on capacity increase/decrease thus not
 * guaranteeing that the location stays the same all throughout the program.
 * </b>
 * @param vec
 * @return
 */
void* vector_get_start_addr_(const vector_t* vec);

/**
 * Retrieve a pointer to an element.\n
 * Example:\n
 *
 * int* my_int;\n
 * vector_elem_at(my_int_vec, 1, &my_int);
 * @param vec
 * @param index
 * @param out
 * @return
 */
bool vector_elem_at(const vector_t* vec, size_t index, void** out);
/**
 * As apposed to `vector_elem_at`, this function should be used when
 * the vector contains pointers to objects on the heap and has and elem_size
 * that is equal to that of `uintptr_t`.
 * @param vec
 * @param index
 * @param out
 * @return
 */
bool vector_elem_at_ptr(const vector_t* vec, size_t index, void* out);

/**
 * Pushes an element to the top op the vector.
 * @param vec
 * @param elem
 */
void vector_push(vector_t* vec, void* elem);
/**
 * Pushes elements to the top of the vector in the order that they are presented.
 */
#define vector_push_ex(vector_ptr, ...) vector_add_with_(vector_ptr, vector_push, __VA_ARGS__, NULL)
/**
 * Appends an element to the end of the vector.
 * @param vec
 * @param elem
 */
void vector_append(vector_t* vec, void* elem);
/**
 * Appends multiple elements to the end of the vector in the order that the elements are presented.
 */
#define vector_append_ex(vector_ptr, ...) vector_add_with_(vector_ptr, vector_append, __VA_ARGS__, NULL)

/**
 * Inserts an element at the specified index, shoving the
 * element that was previously there one down.
 * @param vec
 * @param index
 * @param elem
 * @return
 */
bool vector_insert_to(vector_t* vec, size_t index, void* elem);

/**
 * Inserts elements into the vector starting from `index` in the order that the elements are presented.
 */
#define vector_insert_to_ex(vector_ptr, index, ...) vector_insert_ex_(vector_ptr, index, __VA_ARGS__, NULL)

/**
 * Makes a copy from `start_index` with `elem_count` amount of items.
 * @param vec
 * @param start_index
 * @param elem_count When `0`, this value will automatically be calculated for all the elements starting from `start_index`.
 * @return
 */
NODISCARD
vector_t* vector_copy(const vector_t* vec, size_t start_index, size_t elem_count);

/**
 * Makes a deep-copied vector from `start_index` with `elem_count` amount of items, using the given `copy_func`.
 * @param vec The vector to-be copied.
 * @param start_index The starting index.
 * @param elem_count When `0`, this value will automatically be calculated as to copy the whole vector.
 * @param copy_func This is the function that's used to copy each individual element, the first argument is the `dest`,
 *                  the second the `src` and it returns `true` on success and `false` on failure
 * @return A pointer to a heap allocated copy of `vec`.
 */
NODISCARD
vector_t*
vector_copy_deep(
    const vector_t* vec,
    size_t start_index,
    size_t elem_count,
    bool (*copy_func)(void* /* dest */, const void* /* src */)
);

/**
 * Copies a vector into another vector at `dst_index` from `src_index` for `elem_count` amount of items.
 * @param dst
 * @param dst_index
 * @param src
 * @param src_index
 * @param elem_count When `0`, this value will automatically be calculated for all the elements starting from `src_index`.
 * @return
 */
bool vector_copy_into(vector_t* dst, size_t dst_index, const vector_t* src, size_t src_index,
                      size_t elem_count);

/**
 * Appends `_Src` to `_Dst` by deep-copy from `_Start_index` (of _Src) with `_Elem_count` amount of items.
 */
#define vector_append_to(_Dst, _Src, _Start_index, _Elem_count) \
    vector_copy_into(_Dst, vector_get_elem_count(_Dst), _Src, _Start_index, _Elem_count)

/**
 * Pushes `_Src` on top of `_Dst` by deep-copy from `_Start_index` (of _Src_ with `_Elem_count` amount of items.
 */
#define vector_push_to(_Dst, _Src, _Start_index, _Elem_count) \
    vector_copy_into(_Dst, 0, _Src, _Start_index, _Elem_count)

/**
 * Removes the top element from the vector and copies it into `out`.
 * @param vec
 * @param out
 * @return
 */
bool vector_pop(vector_t* vec, void* out);
/**
 * Removes the last element from the vector and copies it into `out`.
 * @param vec
 * @param out
 * @return
 */
bool vector_dequeue(vector_t* vec, void* out);
/**
 * Removes the element at the specified index from the vector and copies it into `out`.
 * @param vec
 * @param index
 * @param out
 * @return
 */
bool vector_remove_at(vector_t* vec, size_t index, void* out);


void vector_add_with_(vector_t* vec, void(*method)(vector_t*, void*), ...);
bool vector_insert_ex_(vector_t* vec, size_t start_index, ...);

#endif // VECTOR_H__
