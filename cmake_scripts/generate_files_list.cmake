function(generate_files_list)
    set(
        ONE_VALUE_KEYWORDS
        INCLUDE_DIR
        SRC_DIR
        HEADERS_EXTENSION
        SRC_EXTENSION
        MAIN
        RESULT_VAR
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

    set(${ARG_RESULT_VAR} ${HEADERS} ${SRC})
    return(PROPAGATE ${ARG_RESULT_VAR})
endfunction()

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
    if(NOT ARG_DIR MATCHES "[*/]")
        set(ARG_DIR "${ARG_DIR}/")
    endif()

    if (NOT ARG_EXTENSION)
        set(ARG_EXTENSION ${ARG_EXTENSION_VAL_BY_DEFAULT})
    endif()
    if(NOT ARG_EXTENSION MATCHES "[.*]")
        set(ARG_EXTENSION ".${ARG_EXTENSION}")
    endif()

    list(TRANSFORM ${ARG_DEST} PREPEND "${ARG_DIR}")
    list(TRANSFORM ${ARG_DEST} APPEND "${ARG_EXTENSION}")

    return(PROPAGATE ${ARG_DEST})
endfunction()

