project(table)

set(src "src/main.cpp"
        "src/backend.h" "src/backend.cpp")

set(rc "qml/qml.qrc")

add_executable(${PROJECT_NAME} WIN32 ${src} ${rc})
target_compile_definitions(${PROJECT_NAME}
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

add_subdirectory(test)
