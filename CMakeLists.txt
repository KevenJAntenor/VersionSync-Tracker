cmake_minimum_required(VERSION 3.8)

project(inf3173-232-tp1 LANGUAGES C CXX VERSION 1)

# faire un build dans les sources, c'est MAL
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(PreventInSourceBuilds)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()

option(ENABLE_TESTS "Enable tests" ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
link_libraries(Threads::Threads)

option(ENABLE_THREAD_SANITIZER "Compile with -fsanitize=thread" OFF)
if(ENABLE_THREAD_SANITIZER)
  add_compile_options(-fsanitize=thread)
  add_link_options(-fsanitize=thread)
endif()

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/inf3173/config.h)
add_subdirectory(src)

if (ENABLE_TESTS)
  enable_testing()
  include(CTest)
  add_subdirectory(test)
endif()

configure_file(env.sh.in env.sh)

# Package
string(TIMESTAMP TS "%Y%m%d%H%M%S")
set(CPACK_SOURCE_PACKAGE_FILE_NAME ${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}-${TS})
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES
	"/build/;/.git/;~$;CMakeLists.txt.user;/data/.*\\\\.png;/results/;${CPACK_SOURCE_IGNORE_FILES}")
include(CPack)
add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)


