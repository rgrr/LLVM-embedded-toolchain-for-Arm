/*===- SYSVIEW.h - Segger SysView API header---------------------- --------===*\
|*
|* Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
|* See https://llvm.org/LICENSE.txt for license information.
|* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
|*
\*===----------------------------------------------------------------------===*/



#ifndef __SYSVIEW_H
#define __SYSVIEW_H

#ifdef __cplusplus
    extern "C" {
#endif


#ifndef SEGGER_SYSVIEW_OFF

    #include "SEGGER_RTT.h"
    #include "SEGGER_SYSVIEW.h"

    // some "high level" SystemView API
    void SYSVIEW_SetSystemInfo(const char *appName, const char *deviceName, const char *coreName, const char *osName);
    void SYSVIEW_Init(uint32_t sysFreq, uint32_t cpuFreq, uint64_t (*getTime)(void));
    void SYSVIEW_ConfigUpBuffer(void* pBuffer, unsigned BufferSize);

    void SYSVIEW_AddTask(uint32_t taskId, const char *name);
    void SYSVIEW_AddMarker(uint32_t markerId, const char *name);
    void SYSVIEW_AddInt(uint32_t intId, const char *name);

#else

    #define SYSVIEW_SetSystemInfo(...)
    #define SYSVIEW_Init(...)
    #define SYSVIEW_ConfigUpBuffer(...)

    #define SYSVIEW_AddTask(...)
    #define SYSVIEW_AddMarker(...)
    #define SYSVIEW_AddInt(...)

    #define SEGGER_SYSVIEW_Init(...)
    #define SEGGER_SYSVIEW_SetRAMBase(...)
    #define SEGGER_SYSVIEW_Start(...)                    
    #define SEGGER_SYSVIEW_Stop(...)                     
    #define SEGGER_SYSVIEW_GetSysDesc(...)               
    #define SEGGER_SYSVIEW_SendTaskList(...)             
    #define SEGGER_SYSVIEW_SendTaskInfo(...)             
    #define SEGGER_SYSVIEW_SendSysDesc(...)              
    #define SEGGER_SYSVIEW_IsStarted(...)                
    #define SEGGER_SYSVIEW_GetChannelID(...)             
 
    #define SEGGER_SYSVIEW_RecordVoid(...)               
    #define SEGGER_SYSVIEW_RecordU32(...)                
    #define SEGGER_SYSVIEW_RecordU32x2(...)              
    #define SEGGER_SYSVIEW_RecordU32x3(...)              
    #define SEGGER_SYSVIEW_RecordU32x4(...)              
    #define SEGGER_SYSVIEW_RecordU32x5(...)              
    #define SEGGER_SYSVIEW_RecordU32x6(...)              
    #define SEGGER_SYSVIEW_RecordU32x7(...)              
    #define SEGGER_SYSVIEW_RecordU32x8(...)              
    #define SEGGER_SYSVIEW_RecordU32x9(...)              
    #define SEGGER_SYSVIEW_RecordU32x10(...)             
    #define SEGGER_SYSVIEW_RecordString(...)             
    #define SEGGER_SYSVIEW_RecordSystime(...)            
    #define SEGGER_SYSVIEW_RecordEnterISR(...)           
    #define SEGGER_SYSVIEW_RecordExitISR(...)            
    #define SEGGER_SYSVIEW_RecordExitISRToScheduler(...) 
    #define SEGGER_SYSVIEW_RecordEnterTimer(...)         
    #define SEGGER_SYSVIEW_RecordExitTimer(...)          
    #define SEGGER_SYSVIEW_RecordEndCall(...)            
    #define SEGGER_SYSVIEW_RecordEndCallU32(...)         

    #define SEGGER_SYSVIEW_OnIdle(...)                   
    #define SEGGER_SYSVIEW_OnTaskCreate(...)             
    #define SEGGER_SYSVIEW_OnTaskTerminate(...)          
    #define SEGGER_SYSVIEW_OnTaskStartExec(...)          
    #define SEGGER_SYSVIEW_OnTaskStopExec(...)           
    #define SEGGER_SYSVIEW_OnTaskStartReady(...)         
    #define SEGGER_SYSVIEW_OnTaskStopReady(...)          
    #define SEGGER_SYSVIEW_MarkStart(...)                
    #define SEGGER_SYSVIEW_MarkStop(...)                 
    #define SEGGER_SYSVIEW_Mark(...)                     
    #define SEGGER_SYSVIEW_NameMarker(...)               

    #define SEGGER_SYSVIEW_HeapDefine(...)               
    #define SEGGER_SYSVIEW_HeapAlloc(...)                
    #define SEGGER_SYSVIEW_HeapAllocEx(...)              
    #define SEGGER_SYSVIEW_HeapFree(...)                 

    #define SEGGER_SYSVIEW_NameResource(...)             

    #define SEGGER_SYSVIEW_SendPacket(...)               

    #define SEGGER_SYSVIEW_EncodeU32(...)                
    #define SEGGER_SYSVIEW_EncodeData(...)               
    #define SEGGER_SYSVIEW_EncodeString(...)             
    #define SEGGER_SYSVIEW_EncodeId(...)                 
    #define SEGGER_SYSVIEW_ShrinkId(...)                 

    #define SEGGER_SYSVIEW_RegisterModule(...)           
    #define SEGGER_SYSVIEW_RecordModuleDescription(...)  
    #define SEGGER_SYSVIEW_SendModule(...)               
    #define SEGGER_SYSVIEW_SendModuleDescription(...)    
    #define SEGGER_SYSVIEW_SendNumModules(...)           

    #define SEGGER_SYSVIEW_PrintfHostEx(...)             
    #define SEGGER_SYSVIEW_VPrintfHostEx(...)            
    #define SEGGER_SYSVIEW_PrintfTargetEx(...)          
    #define SEGGER_SYSVIEW_VPrintfTargetEx(...)          
    #define SEGGER_SYSVIEW_PrintfHost(...)               
    #define SEGGER_SYSVIEW_VPrintfHost(...)              
    #define SEGGER_SYSVIEW_PrintfTarget(...)             
    #define SEGGER_SYSVIEW_VPrintfTarget(...)            
    #define SEGGER_SYSVIEW_WarnfHost(...)                
    #define SEGGER_SYSVIEW_VWarnfHost(...)               
    #define SEGGER_SYSVIEW_WarnfTarget(...)              
    #define SEGGER_SYSVIEW_VWarnfTarget(...)             
    #define SEGGER_SYSVIEW_ErrorfHost(...)               
    #define SEGGER_SYSVIEW_VErrorfHost(...)              
    #define SEGGER_SYSVIEW_ErrorfTarget(...)             
    #define SEGGER_SYSVIEW_VErrorfTarget(...)            

    #define SEGGER_SYSVIEW_Print(...)                    
    #define SEGGER_SYSVIEW_Warn(...)                     
    #define SEGGER_SYSVIEW_Error(...)                    

    #define SEGGER_SYSVIEW_EnableEvents(...)             
    #define SEGGER_SYSVIEW_DisableEvents(...)            

    #define SEGGER_SYSVIEW_Conf(...)                     
    #define SEGGER_SYSVIEW_X_GetTimestamp(...)           
    #define SEGGER_SYSVIEW_X_GetInterruptId(...)         

    #define SEGGER_SYSVIEW_X_StartComm(...)              
    #define SEGGER_SYSVIEW_X_OnEventRecorded(...)       

#endif


#ifdef __cplusplus
    }
#endif

#endif
