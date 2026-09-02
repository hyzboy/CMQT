# QtULREExample：Qt 窗口外壳内运行 ULRE 引擎示例
#
# 仅当在 ULRE 集成构建中（存在 ULRE.Work 等 target）才编译，
# 因为该示例链接 ULRE 主树并复用 example/Basic 的 WorkObject。
# CMQT 独立构建时此示例被跳过。

if(NOT TARGET ULRE.Work)
    return()
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(QtULREExample WIN32 main.cpp)

# 复用 ULRE example 的 WorkObject 源码（main.cpp 中 #include）
target_include_directories(QtULREExample PRIVATE
    ${CMAKE_SOURCE_DIR}/example/Basic
    ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(QtULREExample PRIVATE
    Qt6::Widgets
    CMQT
    ${ULRE})

# Qt 的 signals/slots/emit 宏会破坏 ULRE 头中的同名标识符（如 EntityManager::slots 成员），
# 混编 Qt + ULRE 头时必须禁用 Qt 关键字宏
target_compile_definitions(QtULREExample PRIVATE QT_NO_KEYWORDS)

# 部署 Qt 平台插件（vcpkg 自动拷贝 bin DLL，但不含 plugins）
if(TARGET Qt6::QWindowsIntegrationPlugin)
    add_custom_command(TARGET QtULREExample POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:QtULREExample>/platforms"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:Qt6::QWindowsIntegrationPlugin>"
                "$<TARGET_FILE_DIR:QtULREExample>/platforms/"
        COMMENT "Deploy Qt platform plugin (qwindows)")
endif()

set_target_properties(QtULREExample PROPERTIES
    FOLDER "Examples/CMQT")

if(WIN32 AND COMMAND set_debugger_directory)
    set_debugger_directory(QtULREExample ${CMAKE_SOURCE_DIR})
endif()
