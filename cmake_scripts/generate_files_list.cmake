function(generate_files_list)
    set(
        MULTI_VALUE_KEYWORDS
        CLASSES
        TEMPLATE_CLASSES
        FUNC_FILES
        TEMPLATE_FUNC_FILES
        HEADERS_WITH_DEFINITIONS
        MAIN
    )
    cmake_parse_arguments(
        "GFL"
        ""
        "RESULT_VAR"
        "${MULTI_VALUE_KEYWORDS}"
        ${ARGN}
    )

    set(
        HEADERS
        ${GFL_CLASSES}
        ${GFL_TEMPLATE_CLASSES}
        ${GFL_FUNC_FILES}
        ${GFL_TEMPLATE_FUNC_FILES}
        ${GFL_HEADERS_WITH_DEFINITIONS}
    )
    list(TRANSFORM HEADERS PREPEND "include/")
    list(TRANSFORM HEADERS APPEND ".hpp")

    set(
        SRC
        ${GFL_CLASSES}
        ${GFL_FUNC_FILES}
        ${GFL_MAIN}
    )
    list(TRANSFORM SRC PREPEND "src/")
    list(TRANSFORM SRC APPEND ".cpp")

    set(${GFL_RESULT_VAR} ${HEADERS} ${SRC})
    return(PROPAGATE ${GFL_RESULT_VAR})
endfunction()