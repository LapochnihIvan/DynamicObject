#! generate_files_list : Function witch generates list of sources for target
#
# This function transforms names of files with classes, classes templates,
# functions, functions templates and definitions (define, enum, using,
# constexpr, etc) to list of sources
#
# \param:DEST Name of variable witch will contain result
# \param:INCLUDE_DIR Name of directory with headers. Optionaly ends with "/".
# Value by default: "include/"
# \param:SRC_DIR Name of directory with sources. Optionaly ends with "/".
# Value by default: "src/"
# \param:HEADERS_EXTENSION Extension of headers. Optionaly begins with ".".
# Value by default: ".hpp"
# \param:SRC_EXTENSION Extension of sources. Optionaly begins with ".".
# Value by default: ".cpp"
# \param:MAIN Name of file with main function
# \groop:CLASSES List of files' names with classes
# \groop:TEMPLATE_CLASSES List of files' names with classes templates
# \groop:FUNC_FILES List of files' names with functions
# \groop:TEMPLATE_FUNC_FILES List of files' names with templates functions
# \groop:HEADERS_WITH_DEFINITIONS List of files' names with definitions (define,
# enum, using, constexpr, etc)
#
# Example:
# .. code-block:: cmake
#     generate_files_list(
#         DEST SOURCES
#         INCLUDE_DIR "headers"
#         SRC_DIR "sources"
#         HEADERS_EXTENSION "h"
#         SRC_EXTENSION "cxx"
#         CLASSES MyClass
#         TEMPLATE_CLASSES MyTemplateClass
#         FUNC_FILES myFuncs
#         TEMPLATE_FUNC_FILES myTemplateFuncs
#         HEADERS_WITH_DEFINITIONS myDefinitions
#     )
#
#     # SOURCES:
#     #     headers/MyClass.h headers/MyTemplateClass.h headers/myFuncs.h
#     #     headers/myTemplateFuncs.h headers/myDefinitions.h
#     #     sources/MyClass.cxx sources/myFuncs.cxx
#     add_executable(MyTarget ${SOURCES})
function(generate_files_list)
    set(
        ONE_VALUE_KEYWORDS
        DEST
        INCLUDE_DIR
        SRC_DIR
        HEADERS_EXTENSION
        SRC_EXTENSION
        MAIN
    )
    set(
        MULTI_VALUE_KEYWORDS
        CLASSES
        TEMPLATE_CLASSES
        FUNC_FILES
        TEMPLATE_FUNC_FILES
        HEADERS_WITH_DEFINITIONS
    )
    cmake_parse_arguments(
        "ARG"
        ""
        "${ONE_VALUE_KEYWORDS}"
        "${MULTI_VALUE_KEYWORDS}"
        ${ARGN}
    )

    set(
        HEADERS
        ${ARG_CLASSES}
        ${ARG_TEMPLATE_CLASSES}
        ${ARG_FUNC_FILES}
        ${ARG_TEMPLATE_FUNC_FILES}
        ${ARG_HEADERS_WITH_DEFINITIONS}
    )
    _add_dir_and_extension(
        DEST HEADERS
        DIR ${ARG_INCLUDE_DIR}
        DIR_VAL_BY_DEFAULT "include/"
        EXTENSION ${ARG_HEADERS_EXTENSION}
        EXTENSION_VAL_BY_DEFAULT ".hpp"
    )

    set(
        SRC
        ${ARG_CLASSES}
        ${ARG_FUNC_FILES}
        ${ARG_MAIN}
    )
    _add_dir_and_extension(
        DEST SRC
        DIR ${ARG_SRC_DIR}
        DIR_VAL_BY_DEFAULT "src/"
        EXTENSION ".cpp"
        EXTENSION_VAL_BY_DEFAULT ${ARG_SRC_EXTENSION}
    )

    set(${ARG_DEST} ${HEADERS} ${SRC})
    return(PROPAGATE ${ARG_DEST})
endfunction()

# Private fuction
function(_add_dir_and_extension)
    set(
        ONE_VALUE_KEYWORDS
        DEST
        DIR
        DIR_VAL_BY_DEFAULT
        EXTENSION
        EXTENSION_VAL_BY_DEFAULT
    )
    cmake_parse_arguments(
        "ARG"
        ""
        "${ONE_VALUE_KEYWORDS}"
        ""
        ${ARGN}
    )

    if (NOT ARG_DIR)
        set(ARG_DIR ${ARG_DIR_VAL_BY_DEFAULT})
    endif()
    if (NOT ARG_DIR MATCHES "[*/]")
        set(ARG_DIR "${ARG_DIR}/")
    endif()

    if (NOT ARG_EXTENSION)
        set(ARG_EXTENSION ${ARG_EXTENSION_VAL_BY_DEFAULT})
    endif()
    if (NOT ARG_EXTENSION MATCHES "[.*]")
        set(ARG_EXTENSION ".${ARG_EXTENSION}")
    endif()

    list(TRANSFORM ${ARG_DEST} PREPEND "${ARG_DIR}")
    list(TRANSFORM ${ARG_DEST} APPEND "${ARG_EXTENSION}")

    return(PROPAGATE ${ARG_DEST})
endfunction()
