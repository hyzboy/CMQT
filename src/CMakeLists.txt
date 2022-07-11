find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui Widgets Svg Xml VulkanSupport)

SET(CMQT_INCLUDE_PATH   ${CMQT_ROOT_INCLUDE_PATH}/hgl/qt)

SET(CMQT_WIDGET_INCLUDE_PATH   ${CMQT_INCLUDE_PATH}/widget)
SET(CMQT_DIALOG_INCLUDE_PATH   ${CMQT_INCLUDE_PATH}/dialog)

IF(WIN32)
    set(CMQT_MAIN_SOURCE  ${CMAKE_CURRENT_SOURCE_DIR}/QT5WinUCS2.cpp)
ELSEIF()
    set(CMQT_MAIN_SOURCE  ${CMAKE_CURRENT_SOURCE_DIR}/QT5UnixUTF8.cpp)
endif()

SET(CMQT_DIALOG_FILES ${CMQT_DIALOG_INCLUDE_PATH}/NameEdit.h
                      dialog/NameEdit.cpp)

SOURCE_GROUP("Dialog" FILES ${CMQT_DIALOG_FILES})

SET(CMQT_IMAGE_FILES image/SVGPixmap.cpp)

SOURCE_GROUP("Image" FILES ${CMQT_IMAGE_FILES})

SET(CMQT_Vulkan_FILES   ${CMQT_INCLUDE_PATH}/QtVulkanWindow.h
                        vulkan/QtVulkanWindow.cpp
                        vulkan/QtVulkanSurface.cpp)

SOURCE_GROUP("Vulkan" FILES ${CMQT_Vulkan_FILES})

add_cm_library(CMQT "CM" ${CMQT_DIALOG_FILES} ${CMQT_IMAGE_FILES} ${CMQT_Vulkan_FILES})

target_link_libraries(CMQT PUBLIC   Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Svg Qt5::Xml Qt5::VulkanSupport)