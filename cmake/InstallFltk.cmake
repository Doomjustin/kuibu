include(FetchContent)

FetchContent_Declare(
    fltk
    GIT_REPOSITORY https://github.com/fltk/fltk.git
    GIT_TAG        release-1.4.3
    GIT_SHALLOW    TRUE
    GIT_PROGRESS   TRUE
)

option(FLTK_BUILD_FLUID "Build FLUID" OFF)
option(FLTK_BUILD_TEST "Build FLTK tests" OFF)

FetchContent_MakeAvailable(fltk)
