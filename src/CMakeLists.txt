add_library(winSocketpair INTERFACE)

target_include_directories(winSocketpair INTERFACE ...)
target_sources(winSocketpair INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/winSocketpair.h
)

install(FILES 
    winSocketpair.h 
    DESTINATION include)
