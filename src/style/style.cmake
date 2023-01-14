find_package(Qt${CM_QT_MAJOR_VERSION} ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Gui Widgets)

if(CM_QT_MAJOR_VERSION VERSION_EQUAL "5")
    include_directories(${Qt5Widgets_PRIVATE_INCLUDE_DIRS})
elseif(CM_QT_MAJOR_VERSION VERSION_EQUAL "6")
    include_directories(${Qt6Widgets_PRIVATE_INCLUDE_DIRS})
endif()

SET(CM_QT_STYLE_SOURCE ${CMQT_STYLE_PATH}/CMQTStyle.cpp)

source_group("QT Style" FILES ${CM_QT_STYLE_SOURCE})

SET(CMQT_STYLE_FILES    ${CM_QT_STYLE_SOURCE})

IF(CM_QT_EXTRA_STYLE)
    include_directories(${CMQT_STYLE_PATH}/shared)
    file(GLOB QTStyleSharedFiles  ${CMQT_STYLE_PATH}/shared/*.*)

    include_directories(${CMQT_STYLE_PATH}/bb10style)
    file(GLOB QTBB10StyleFiles  ${CMQT_STYLE_PATH}/bb10style/*.*)

    include_directories(${CMQT_STYLE_PATH}/cleanlooks)
    file(GLOB QTCleanLookStyleFiles  ${CMQT_STYLE_PATH}/cleanlooks/*.*)

    include_directories(${CMQT_STYLE_PATH}/motif)
    file(GLOB QTMotifStyleFiles  ${CMQT_STYLE_PATH}/motif/*.*)

    include_directories(${CMQT_STYLE_PATH}/plastique)
    file(GLOB QTPlastiqueStyleFiles  ${CMQT_STYLE_PATH}/plastique/*.*)

    source_group("QT Style\\Shared" FILES ${QTStyleSharedFiles})
    source_group("QT Style\\BB10" FILES ${QTBB10StyleFiles})
    source_group("QT Style\\Cleanlooks" FILES ${QTCleanLookStyleFiles})
    source_group("QT Style\\Motif" FILES ${QTMotifStyleFiles})
    source_group("QT Style\\Plastique" FILES ${QTPlastiqueStyleFiles})

    SET(CMQT_STYLE_FILES    ${CMQT_STYLE_FILES}
                            ${QTStyleSharedFiles}
                            ${QTBB10StyleFiles}
                            ${QTCleanLookStyleFiles}
                            ${QTMotifStyleFiles}
                            ${QTPlastiqueStyleFiles})
endif(CM_QT_EXTRA_STYLE)
