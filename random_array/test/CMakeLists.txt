add_executable(test_worker test_worker.cpp "../src/worker.cpp")
target_include_directories(test_worker PRIVATE "../src/")
target_link_libraries(test_worker PRIVATE Qt${QT_VERSION_MAJOR}::Test)
add_test(NAME test_worker COMMAND test_worker)