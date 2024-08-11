cmake_minimum_required(VERSION 3.27)
project(DynamicObject)

include(cmake_scripts/set_default_properties.cmake)
include(cmake_scripts/generate_files_list.cmake)
include(cmake_scripts/create_config_file.cmake)

set_default_properties()

generate_target_sources_list(
    DEST SOURCES
    CLASSES DynamicObject
)

add_library(DynamicObject ${SOURCES})

target_include_directories(DynamicObject PRIVATE include)

create_config_file()
