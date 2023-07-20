cmake_minimum_required(VERSION 3.13)
project(rtt)

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

target_link_libraries(${LIB_RTT_STDIO} PUBLIC 
    ${LIB_RTT}
)

install(
    FILES       "README.md"
    DESTINATION "/tmp/lib/rtt"
    COMPONENT   llvm-toolchain-libs
)
