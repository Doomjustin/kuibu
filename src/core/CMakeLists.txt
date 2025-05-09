configure_file(config.cppm.in ${CMAKE_CURRENT_LIST_DIR}/config.cppm @ONLY)

add_library(toys_core STATIC)

add_library(toys::core ALIAS toys_core)

target_sources(toys_core
    PUBLIC FILE_SET CXX_MODULES
    FILES
        config.cppm
        random.cppm
)

target_link_libraries(toys_core
    PUBLIC
        Microsoft.GSL::GSL
        fmt::fmt
    PRIVATE
        spdlog::spdlog
        doctest::doctest
)

target_compile_features(toys_core 
    INTERFACE
        cxx_std_20
    PRIVATE
        cxx_std_23
)

target_compile_definitions(toys_core
    INTERFACE
        $<$<CONFIG:Debug>:TOYS_DEBUG>
        $<$<CONFIG:Release>:DOCTEST_CONFIG_DISABLE>
)


if (${PROJECT_NAME}_BUILD_TESTS)
    add_subdirectory(test)
endif()
