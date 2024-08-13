cmake_minimum_required(VERSION 3.27)

if (NOT CMAKE_TOOLCHAIN_FILE AND
    DEFINED VCPKG_ROOT)
    # For Google test
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

project(DynamicObject)

if (NOT DYNAMIC_OBJECT_INSTALL)
    set(DYNAMIC_OBJECT_INSTALL ${PROJECT_IS_TOP_LEVEL})
endif()

if (NOT DYNAMIC_OBJECT_BUILD_TESTS)
    set(DYNAMIC_OBJECT_BUILD_TESTS ${PROJECT_IS_TOP_LEVEL})
endif()

include(cmake_scripts/set_default_properties.cmake)
include(cmake_scripts/generate_project_files_list.cmake)
include(cmake_scripts/create_config_files.cmake)

set_default_properties()

generate_project_files_list(
    DEST_HEADERS HEADERS
    DEST_SOURCES SOURCES
    CLASSES DynamicObject
)

add_library(DynamicObject ${HEADERS} ${SOURCES})
add_library(DynObj::DynamicObject ALIAS DynamicObject)

set(LIB_FILES_DIR "${CMAKE_SOURCE_DIR}/${CMAKE_INSTALL_LIBDIR}")
set_target_properties(
    DynamicObject
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIB_FILES_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${LIB_FILES_DIR}
)

target_include_directories(DynamicObject PRIVATE include)

create_config_files(
    DEST_VERSION_FILE_PATH VERSION_FILE_PATH
    DEST_CONFIG_FILE_PATH CONFIG_FILE_PATH
    DEST_CONFIG_INSTALL_DIR CONFIG_INSTALL_DIR
)

if (DYNAMIC_OBJECT_INSTALL)
    install(
        FILES ${VERSION_FILE_PATH} ${CONFIG_FILE_PATH}
        COMPONENT "${PROJECT_NAME}"
        DESTINATION ${CONFIG_INSTALL_DIR}
    )
    install(
        FILES "$<TARGET_FILE:DynamicObject>"
        COMPONENT "${PROJECT_NAME}"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
    install(
        FILES ${HEADERS}
        COMPONENT "${PROJECT_NAME}"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
endif()

if (DYNAMIC_OBJECT_BUILD_TESTS)

endif()
