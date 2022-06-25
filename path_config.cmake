macro(CMQTSetup CMQT_ROOT_PATH)

    message("CMQT_ROOT_PATH: " ${CMQT_ROOT_PATH})

    set(CMQT_ROOT_INCLUDE_PATH    ${CMQT_ROOT_PATH}/inc)
    set(CMQT_ROOT_SOURCE_PATH     ${CMQT_ROOT_PATH}/src)

    include_directories(${CMQT_ROOT_INCLUDE_PATH})
endmacro()
