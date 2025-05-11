add_executable(tic-tac-toe main.cpp)
target_link_libraries(tic-tac-toe 
    PRIVATE
        toys::core
        fltk::fltk
)