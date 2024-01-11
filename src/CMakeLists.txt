add_library(core
    fileops.c
    fileops.h

    utils.c
    utils.h
)
target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(core PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../include)

add_executable(bumpvers bumpvers.c)
target_link_libraries(bumpvers PRIVATE core)

add_executable(benchmark benchmark.c)
target_link_libraries(benchmark PRIVATE core)
