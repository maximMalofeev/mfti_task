cmake_minimum_required(VERSION 3.14)

project(mfti_task LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Test REQUIRED)

enable_testing()

add_subdirectory(random_array)
add_subdirectory(table)
add_subdirectory(chart)
