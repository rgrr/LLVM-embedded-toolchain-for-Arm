cmake_minimum_required(VERSION 3.13)


set(LIB_RTT rtt)

add_library(${LIB_RTT} STATIC
    rtt_stdio.c
    SEGGER/RTT/SEGGER_RTT_printf.c
    SEGGER/RTT/SEGGER_RTT.c
    SEGGER/RTT/SEGGER_RTT_ASM_ARMv7M.S
)


# List of include directories
target_include_directories(${LIB_RTT} PRIVATE
    SEGGER
    SEGGER/Config
    SEGGER/RTT
)
