add_executable(test_table_backend test_table_backend.cpp "../src/backend.cpp")
target_include_directories(test_table_backend PRIVATE "../src/")
target_link_libraries(test_table_backend PRIVATE Qt${QT_VERSION_MAJOR}::Test)
add_test(NAME test_table_backend COMMAND test_table_backend)