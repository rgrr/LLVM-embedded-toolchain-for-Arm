cmake_minimum_required(VERSION 3.13)
project(rtt C ASM)

#
# bare RTT files from Segger
#
set(LIB_RTT rtt)

add_library(${LIB_RTT} STATIC
    SEGGER/RTT/SEGGER_RTT_printf.c
    SEGGER/RTT/SEGGER_RTT.c
    SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.S
)

target_include_directories(${LIB_RTT} PUBLIC
    SEGGER
    SEGGER/Config
    SEGGER/RTT
)


#
# RTT files from Segger including picolib stdio logic
# 
set(LIB_RTT_STDIO rtt_stdio)

add_library(${LIB_RTT_STDIO} STATIC
    rtt_stdio.c
)

target_link_libraries(${LIB_RTT_STDIO} PUBLIC ${LIB_RTT})

#
# bare SysView files from Segger
# 
set(LIB_RTT_SYSVIEW rtt_sysview)

add_library(${LIB_RTT_SYSVIEW} STATIC
    rtt_sysview.c
    SEGGER/RTT/SEGGER_SYSVIEW.c
)

target_link_libraries(${LIB_RTT_SYSVIEW} PUBLIC ${LIB_RTT})


#
# install output files
#
install(
    FILES       ${CMAKE_BINARY_DIR}/lib${LIB_RTT}.a
                ${CMAKE_BINARY_DIR}/lib${LIB_RTT_STDIO}.a
                ${CMAKE_BINARY_DIR}/lib${LIB_RTT_SYSVIEW}.a
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/
    COMPONENT   llvm-toolchain-libs
)
install(
    FILES       SEGGER/Config/Global.h
                SEGGER/Config/SEGGER_RTT_Conf.h
                SEGGER/Config/SEGGER_SYSVIEW_Conf.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/SEGGER/Config/
    COMPONENT   llvm-toolchain-libs
)
install(
    FILES       SEGGER/RTT/SEGGER.h
                SEGGER/RTT/SEGGER_RTT.h
                SEGGER/RTT/SEGGER_SYSVIEW.h
                SEGGER/RTT/SEGGER_SYSVIEW_ConfDefaults.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/SEGGER/RTT/
    COMPONENT   llvm-toolchain-libs
)
