#ifndef __fileflt_h
#define __fileflt_h

#include "volhlp.h"
#include "../inc/fltevents.h"

class FileInterceptorContext : public EventData
{
public:
    FileInterceptorContext (
        __in PFLT_CALLBACK_DATA Data,
        __in PCFLT_RELATED_OBJECTS FltObjects,
        __in_opt PStreamContext StreamCtx,
        __in Interceptors InterceptorId,
        __in DriverOperationId Major,
        __in ULONG Minor,
        __in OperationPoint OperationType
        );

    ~FileInterceptorContext (
        );

    __checkReturn
    virtual
    NTSTATUS
    QueryParameter (
        __in_opt ULONG ParameterId,
        __drv_when(return==0, __deref_out_opt __drv_valueIs(!=0)) PVOID* Data,
        __deref_out_opt PULONG DataSize
        );

    __checkReturn
    virtual
    NTSTATUS
    ObjectRequest (
        __in ULONG Command,
        __out_opt PVOID OutputBuffer,
        __inout_opt PULONG OutputBufferSize
        );

    void
    SetCache1();

private:
    __checkReturn
    NTSTATUS
    CheckAccessToVolumeContext (
        );

    __checkReturn
    NTSTATUS
    CreateSectionForData (
        __deref_out PHANDLE Section,
        __out PLARGE_INTEGER Size
        );

private:
    // intercepted data
    PFLT_CALLBACK_DATA          m_Data;
    PCFLT_RELATED_OBJECTS       m_FltObjects;
    PVolumeContext              m_VolumeCtx;
    PStreamContext             m_StreamCtx;

    // service field
    LONG                        m_StreamFlagsTemp;
    LONG                        m_CacheSyncronizer;

    // data access
    HANDLE                      m_Section;
    PVOID                       m_SectionObject;
    PVOID                       m_MappedBase;

    // queryed parameters
    HANDLE                      m_RequestorProcessId;
    HANDLE                      m_RequestorThreadId;
    PInstanceContext           m_InstanceCtxt;
    PFLT_FILE_NAME_INFORMATION  m_FileNameInfo;
    PSID                        m_Sid;
    LUID                        m_Luid;

    ACCESS_MASK                 m_DesiredAccess;
    ULONG                       m_CreateOptions;
    ULONG                       m_CreateMode;

    BOOLEAN                     m_PreCreate;
};

#endif // __fileflt_h