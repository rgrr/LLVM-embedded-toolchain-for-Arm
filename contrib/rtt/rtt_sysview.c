/*===- rtt_sysview.c - startup code for Cortex-M with cycle counter--------===*\
|*
|* Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
|* See https://llvm.org/LICENSE.txt for license information.
|* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
|*
\*===----------------------------------------------------------------------===*/


#include "SYSVIEW.h"
#include <stdio.h>
#include <string.h>


typedef struct {
    uint32_t    id;
    const char *name;
} SYSVIEW_INFO;


#define NUM_TASKS    32
static SYSVIEW_INFO  _aTasks[NUM_TASKS];
static int           _NumTasks;

#define NUM_MARKER   16
static SYSVIEW_INFO  _aMarker[NUM_MARKER];
static int           _NumMarker;

#define NUM_INTS     16
static SYSVIEW_INFO  _aInts[NUM_INTS];
static int           _NumInts;

static const char  *sysviewAppName;
static const char  *sysviewDeviceName;
static const char  *sysviewCoreName;
static const char  *sysviewOsName;



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



static void _cbSendSystemDesc(void)
{
    char buf[128];

    if (sysviewAppName != NULL) {
        sprintf(buf, "N=%s", sysviewAppName);
        SEGGER_SYSVIEW_SendSysDesc(buf);
    }
    if (sysviewDeviceName != NULL) {
        sprintf(buf, "D=%s", sysviewDeviceName);
        SEGGER_SYSVIEW_SendSysDesc(buf);
    }
    if (sysviewCoreName != NULL) {
        sprintf(buf, "C=%s", sysviewCoreName);
        SEGGER_SYSVIEW_SendSysDesc(buf);
    }
    if (sysviewOsName != NULL) {
        sprintf(buf, "O=%s", sysviewOsName);
        SEGGER_SYSVIEW_SendSysDesc(buf);
    }

    for (int n = 0; n < _NumInts; n++) {
        sprintf(buf, "I#%d=%s", _aInts[n].id, _aInts[n].name);
        SEGGER_SYSVIEW_SendSysDesc(buf);
    }
}   // _cbSendSystemDesc


static void _cbSendTaskList(void)
{
    for (int n = 0; n < _NumTasks; n++) {
        SEGGER_SYSVIEW_TASKINFO info;

        memset(&info, 0, sizeof(info));
        info.TaskID = _aTasks[n].id;
        info.sName  = _aTasks[n].name;
        SEGGER_SYSVIEW_SendTaskInfo(&info);
    }
    for (int n = 0; n < _NumMarker; n++) {
        SEGGER_SYSVIEW_NameMarker(_aMarker[n].id, _aMarker[n].name);
    }
}   // _cbSendTaskList


void SYSVIEW_AddTask(uint32_t taskId, const char *name)
{
    int n;

    SEGGER_SYSVIEW_OnTaskCreate(taskId);

    if (_NumTasks > NUM_TASKS) {
        return;
    }
    n = _NumTasks;
    _NumTasks++;

    _aTasks[n].id   = taskId;
    _aTasks[n].name = name;
}   // SYSVIEW_AddTask


void SYSVIEW_AddMarker(uint32_t markerId, const char *name)
{
    int n;

    if (_NumMarker > NUM_MARKER) {
        return;
    }
    n = _NumMarker;
    _NumMarker++;

    _aMarker[n].id   = markerId;
    _aMarker[n].name = name;
}   // SYSVIEW_AddMarker


void SYSVIEW_AddInt(uint32_t intId, const char *name)
{
    int n;

    if (_NumInts > NUM_INTS) {
        return;
    }
    n = _NumInts;
    _NumInts++;

    _aInts[n].id   = intId;
    _aInts[n].name = name;
}   // SYSVIEW_AddInt


void SYSVIEW_SetSystem(const char *appName, const char *deviceName, const char *coreName, const char *osName)
/**
 * Function descriptions go to /opt/SEGGER/SystemView_V<version>/Description/SYSVIEW_<osName>.txt
 */
{
    sysviewAppName    = appName;
    sysviewDeviceName = deviceName;
    sysviewCoreName   = coreName;
    sysviewOsName     = osName;
}   // SYSVIEW_SetSystem


void SYSVIEW_Init(uint32_t sysFreq, uint32_t cpuFreq, uint64_t (*getTime)(void))
{
    static SEGGER_SYSVIEW_OS_API osAPI = {NULL, _cbSendTaskList};

    osAPI.pfGetTime = getTime;
    SEGGER_SYSVIEW_Conf();
    SEGGER_SYSVIEW_Init(sysFreq, cpuFreq, &osAPI, _cbSendSystemDesc);
}   // SYSVIEW_Init


void SYSVIEW_ConfigUpBuffer(void* pBuffer, unsigned BufferSize)
{
    SEGGER_RTT_ConfigUpBuffer(SEGGER_SYSVIEW_RTT_CHANNEL, "SysView", pBuffer, BufferSize, SEGGER_RTT_MODE_NO_BLOCK_SKIP);
}   // SYSVIEW_ConfigUpBuffer
