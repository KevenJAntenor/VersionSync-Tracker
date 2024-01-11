enable_testing()
add_executable(test_fileops
  test_fileops_main.cpp
  test_fileops.cpp
)
target_link_libraries(test_fileops PRIVATE core GTest::gtest)
add_test(NAME test_fileops COMMAND test_fileops)

set_tests_properties(test_fileops PROPERTIES TIMEOUT 10)

