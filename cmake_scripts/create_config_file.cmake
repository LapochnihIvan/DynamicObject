#! create_config_file : Function witch creates config file
#
# This function creates DynamicObjectConfig.cmake for use find_package
function(create_config_file)
    include(GNUInstallDirs)
    include(CMakePackageConfigHelpers)

    set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/lib/cmake/DynamicObject")
    set(
        CONFIG_INSTALL_DIR
        "${CMAKE_INSTALL_LIBDIR}/cmake/DynamicObject"
    )

    set(VERSION_FILE_PATH "${CONFIG_DIR}/DynamicObjectConfigVersion.cmake")
    write_basic_package_version_file(
        ${VERSION_FILE_PATH}
        VERSION "0.1"
        COMPATIBILITY AnyNewerVersion # Guaranteed after first release
    )

    set(CONFIG_FILE_PATH "${CONFIG_DIR}/DynamicObjectConfig.cmake")
    set(INCLUDE_DIRS "../../../include") # Relative path from config directory
    configure_package_config_file(
        "cmake_scripts/DynamicObjectConfig.cmake.in"
        "${CONFIG_FILE_PATH}"
        INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
    )
    install(
        FILES ${VERSION_FILE_PATH} ${CONFIG_FILE_PATH}
        COMPONENT "${PROJECT_NAME}"
        DESTINATION ${CONFIG_INSTALL_DIR}
    )
endfunction()
