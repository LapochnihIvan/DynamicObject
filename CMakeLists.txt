cmake_minimum_required(VERSION 3.27)
project(DynamicObject)

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
set(LIB_FILES_DIR "${CMAKE_SOURCE_DIR}/lib")
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

install(
    FILES ${VERSION_FILE_PATH} ${CONFIG_FILE_PATH}
    COMPONENT "${PROJECT_NAME}"
    DESTINATION ${CONFIG_INSTALL_DIR}
)
