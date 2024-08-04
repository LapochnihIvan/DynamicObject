macro(set_default_properties)
    include(ProcessorCount)
    ProcessorCount(THREADS_COUNT)
    if(NOT THREADS_COUNT)
        set(THREADS_COUNT 1)
    endif()
    set(CMAKE_BUILD_PARALLEL_LEVEL ${THREADS_COUNT})

    set(CMAKE_CXX_STANDARD 20)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(CMAKE_CXX_FLAGS
            "${CMAKE_CXX_FLAGS}   \
            -Werror               \
            -pedantic-errors      \
            -Wall                 \
            -Wextra               \
            -Wpedantic            \
            -Wcast-align          \
            -Wcast-qual           \
            -Wconversion          \
            -Wctor-dtor-privacy   \
            -Wduplicated-branches \
            -Wduplicated-cond     \
            -Wextra-semi          \
            -Wfloat-equal         \
            -Wlogical-op          \
            -Wnon-virtual-dtor    \
            -Wold-style-cast      \
            -Woverloaded-virtual  \
            -Wredundant-decls     \
            -Wsign-conversion     \
            -Wsign-promo")
    endif()
endmacro()