/*===- rtt_sysview.c - startup code for Cortex-M with cycle counter--------===*\
|*
|* Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
|* See https://llvm.org/LICENSE.txt for license information.
|* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
|*
\*===----------------------------------------------------------------------===*/



#include "SEGGER_SYSVIEW.h"


#if SEGGER_SYSVIEW_CORE == SEGGER_SYSVIEW_CORE_CM3


#define DEMCR           (*(volatile unsigned long*) (0xE000EDFCuL))     // Debug Exception and Monitor Control Register
#define TRACEENA_BIT    (1uL << 24)                                     // Trace enable bit

#define DWT_CTRL        (*(volatile unsigned long*) (0xE0001000uL))     // DWT Control Register
#define NOCYCCNT_BIT    (1uL << 25)                                     // Cycle counter support bit
#define CYCCNTENA_BIT   (1uL << 0)                                      // Cycle counter enable bit


static void CycCnt_Init(void)
{
    //
    // If no debugger is connected, the DWT must be enabled by the application
    //
    if ((DEMCR & TRACEENA_BIT) == 0) {
        DEMCR |= TRACEENA_BIT;
    }

    //
    //  The cycle counter must be activated in order
    //  to use time related functions.
    //
    if ((DWT_CTRL & NOCYCCNT_BIT) == 0) {                  // Cycle counter supported?
        if ((DWT_CTRL & CYCCNTENA_BIT) == 0) {             // Cycle counter not enabled?
            DWT_CTRL |= CYCCNTENA_BIT;                     // Enable Cycle counter
        }
    }
}   // CycCnt_Init



__attribute__((weak)) void SEGGER_SYSVIEW_Conf(void)
{
    CycCnt_Init();
}   // SEGGER_SYSVIEW_Conf


#endif
