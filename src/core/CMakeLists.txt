configure_file(config.cppm.in ${CMAKE_CURRENT_LIST_DIR}/config.cppm @ONLY)

add_library(kb_core STATIC)

add_library(kb::core ALIAS kb_core)

target_sources(kb_core
    PUBLIC FILE_SET CXX_MODULES
    FILES
        config.cppm
)

target_link_libraries(kb_core
    PUBLIC
        Microsoft.GSL::GSL
        fmt::fmt
    PRIVATE
        spdlog::spdlog
        doctest::doctest
)

target_compile_features(kb_core 
    INTERFACE
        cxx_std_20
    PRIVATE
        cxx_std_23
)

target_compile_definitions(kb_core
    INTERFACE
        $<$<CONFIG:Debug>:KUI_BU_DEBUG>
        $<$<CONFIG:Release>:DOCTEST_CONFIG_DISABLE>
)


if (${PROJECT_NAME}_BUILD_TESTS)
    add_subdirectory(test)
endif()
