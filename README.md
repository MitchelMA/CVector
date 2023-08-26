# CVector
A simple vector (The CXX one) for dynamic memory handling

## Structure composition
The type `vector_t` can only be acquired as a pointer,
this is because the implementation of the structure is in the source file.  
This was done deliberately.  
The structure goes as follows:  
```C
struct vector_
{
    size_t elem_count
    size_t elem_capacity_count;
    size_t elem_size;
    void* start_addr;
}
```

## Important
When using the function `vector_create()`, You get a pointer to a *heap*
allocated object. Because of this, it is important to use
`vector_clean()` when you are done with the vector object.
