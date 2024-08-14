#! create_config_files : Function witch creates config file
#
# This function creates DynamicObjectConfigVersion.cmake and
# DynamicObjectConfig.cmake for use find_package
#
# \param:DEST_VERSION_FILE_PATH Name of variable witch will contain path to
# DynamicObjectConfigVersion.cmake
# \param:DEST_CONFIG_FILE_PATH Name of variable witch will contain path to
# DynamicObjectConfig.cmake
# \param:DEST_CONFIG_INSTALL_DIR Name of variable witch will contain install
# destination of config files
# \param:INCLUDE_DIR Name of directory to set DynamicObject_INCLUDE_DIRS
function(create_config_files)
    set(
        ONE_VALUE_KEYWORDS
        DEST_VERSION_FILE_PATH
        DEST_CONFIG_FILE_PATH
        DEST_CONFIG_INSTALL_DIR
        INCLUDE_DIR
    )
    cmake_parse_arguments(
        "ARG"
        ""
        "${ONE_VALUE_KEYWORDS}"
        ""
        ${ARGN}
    )

    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    set(CONFIG_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/DynamicObject")
    set(CONFIG_INSTALL_DIR ${CONFIG_DIR})
    set(CONFIG_GENERATE_DIR "${CMAKE_SOURCE_DIR}/${CONFIG_DIR}")

    set(
        VERSION_FILE_PATH
        "${CONFIG_GENERATE_DIR}/DynamicObjectConfigVersion.cmake"
    )
    write_basic_package_version_file(
        ${VERSION_FILE_PATH}
        VERSION "0.1"
        COMPATIBILITY AnyNewerVersion # Guaranteed after first release
    )

    set(
        CONFIG_FILE_PATH
        "${CONFIG_GENERATE_DIR}/DynamicObjectConfig.cmake"
    )
    set(INCLUDE_DIR ${ARG_INCLUDE_DIR})
    configure_package_config_file(
        "cmake_scripts/DynamicObjectConfig.cmake.in"
        "${CONFIG_FILE_PATH}"
        INSTALL_DESTINATION CONFIG_INSTALL_DIR
    )

    set(${ARG_DEST_VERSION_FILE_PATH} ${VERSION_FILE_PATH})
    set(${ARG_DEST_CONFIG_FILE_PATH} ${CONFIG_FILE_PATH})
    set(${ARG_DEST_CONFIG_INSTALL_DIR} ${CONFIG_INSTALL_DIR})

    return(
        PROPAGATE
        ${ARG_DEST_VERSION_FILE_PATH}
        ${ARG_DEST_CONFIG_FILE_PATH}
        ${ARG_DEST_CONFIG_INSTALL_DIR})
endfunction()
