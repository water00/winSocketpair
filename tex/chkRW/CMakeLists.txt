add_executable(chkRW chkRW.cpp)
target_link_libraries(chkRW ws2_32.lib Mswsock.lib AdvApi32.lib)
target_link_libraries(chkRW winSocketpair)
