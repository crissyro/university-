add_library(data_structures
        bitset/bitset.c
        unorderedset/unorderedset.c
        orderedset/orderedset.c
        vector/vector.c
        vector/vector_void.c
        matrix/matrix.c
)

target_link_libraries(data_structures algorithms)
