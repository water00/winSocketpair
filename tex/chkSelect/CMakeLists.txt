add_executable(chkSelect chkSelect.cpp)
target_link_libraries(chkSelect ws2_32.lib Mswsock.lib AdvApi32.lib)
target_link_libraries(chkSelect winSocketpair)