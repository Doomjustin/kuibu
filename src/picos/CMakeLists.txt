add_executable(picos main.cpp)

target_link_libraries(picos PRIVATE toys::core)

target_compile_features(picos PRIVATE cxx_std_23)