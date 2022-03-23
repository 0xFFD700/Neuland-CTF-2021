#include <Windows.h>
#include <intrin.h>
#include <winternl.h>
#include <Utils\XorHelper.hpp>
#include "CryptedBuffer.h"
#include "CryptedString.h"

#define INPUT_BUFFER_SIZE 512

#define MakePtr(cast, x, y)		((cast)((ULONG_PTR)(x) + (ULONG_PTR)(y)))
#define MakeDelta(cast, x, y)	((cast)((ULONG_PTR)(x) - (ULONG_PTR)(y)))

typedef NTSTATUS(NTAPI *tNtProtectVirtualMemory)(
    IN HANDLE               ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN OUT PULONG           NumberOfBytesToProtect,
    IN ULONG                NewAccessProtection,
    OUT PULONG              OldAccessProtection);

typedef NTSTATUS(NTAPI* tNtCreateThreadEx)(
    PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, HANDLE, PVOID, PVOID, ULONG, ULONG_PTR, SIZE_T, SIZE_T, PVOID
    );

EXTERN_C
{
	#include <MinCRT\Startup.hpp>
	#pragma comment(linker, "/MERGE:.CRT=.text")

    extern IMAGE_DOS_HEADER __ImageBase;

    struct _STRING64
    {
        USHORT Length;                                                          //0x0
        USHORT MaximumLength;                                                   //0x2
        ULONGLONG Buffer;                                                       //0x8
    };

    struct _PEB64
    {
        UCHAR InheritedAddressSpace;                                            //0x0
        UCHAR ReadImageFileExecOptions;                                         //0x1
        UCHAR BeingDebugged;                                                    //0x2
        union
        {
            UCHAR BitField;                                                     //0x3
            struct
            {
                UCHAR ImageUsesLargePages : 1;                                    //0x3
                UCHAR IsProtectedProcess : 1;                                     //0x3
                UCHAR IsImageDynamicallyRelocated : 1;                            //0x3
                UCHAR SkipPatchingUser32Forwarders : 1;                           //0x3
                UCHAR IsPackagedProcess : 1;                                      //0x3
                UCHAR IsAppContainer : 1;                                         //0x3
                UCHAR IsProtectedProcessLight : 1;                                //0x3
                UCHAR IsLongPathAwareProcess : 1;                                 //0x3
            };
        };
        UCHAR Padding0[4];                                                      //0x4
        ULONGLONG Mutant;                                                       //0x8
        ULONGLONG ImageBaseAddress;                                             //0x10
        ULONGLONG Ldr;                                                          //0x18
        ULONGLONG ProcessParameters;                                            //0x20
        ULONGLONG SubSystemData;                                                //0x28
        ULONGLONG ProcessHeap;                                                  //0x30
        ULONGLONG FastPebLock;                                                  //0x38
        ULONGLONG AtlThunkSListPtr;                                             //0x40
        ULONGLONG IFEOKey;                                                      //0x48
        union
        {
            ULONG CrossProcessFlags;                                            //0x50
            struct
            {
                ULONG ProcessInJob : 1;                                           //0x50
                ULONG ProcessInitializing : 1;                                    //0x50
                ULONG ProcessUsingVEH : 1;                                        //0x50
                ULONG ProcessUsingVCH : 1;                                        //0x50
                ULONG ProcessUsingFTH : 1;                                        //0x50
                ULONG ProcessPreviouslyThrottled : 1;                             //0x50
                ULONG ProcessCurrentlyThrottled : 1;                              //0x50
                ULONG ProcessImagesHotPatched : 1;                                //0x50
                ULONG ReservedBits0 : 24;                                         //0x50
            };
        };
        UCHAR Padding1[4];                                                      //0x54
        union
        {
            ULONGLONG KernelCallbackTable;                                      //0x58
            ULONGLONG UserSharedInfoPtr;                                        //0x58
        };
        ULONG SystemReserved;                                                   //0x60
        ULONG AtlThunkSListPtr32;                                               //0x64
        ULONGLONG ApiSetMap;                                                    //0x68
        ULONG TlsExpansionCounter;                                              //0x70
        UCHAR Padding2[4];                                                      //0x74
        ULONGLONG TlsBitmap;                                                    //0x78
        ULONG TlsBitmapBits[2];                                                 //0x80
        ULONGLONG ReadOnlySharedMemoryBase;                                     //0x88
        ULONGLONG SharedData;                                                   //0x90
        ULONGLONG ReadOnlyStaticServerData;                                     //0x98
        ULONGLONG AnsiCodePageData;                                             //0xa0
        ULONGLONG OemCodePageData;                                              //0xa8
        ULONGLONG UnicodeCaseTableData;                                         //0xb0
        ULONG NumberOfProcessors;                                               //0xb8
        ULONG NtGlobalFlag;                                                     //0xbc
        union _LARGE_INTEGER CriticalSectionTimeout;                            //0xc0
        ULONGLONG HeapSegmentReserve;                                           //0xc8
        ULONGLONG HeapSegmentCommit;                                            //0xd0
        ULONGLONG HeapDeCommitTotalFreeThreshold;                               //0xd8
        ULONGLONG HeapDeCommitFreeBlockThreshold;                               //0xe0
        ULONG NumberOfHeaps;                                                    //0xe8
        ULONG MaximumNumberOfHeaps;                                             //0xec
        ULONGLONG ProcessHeaps;                                                 //0xf0
        ULONGLONG GdiSharedHandleTable;                                         //0xf8
        ULONGLONG ProcessStarterHelper;                                         //0x100
        ULONG GdiDCAttributeList;                                               //0x108
        UCHAR Padding3[4];                                                      //0x10c
        ULONGLONG LoaderLock;                                                   //0x110
        ULONG OSMajorVersion;                                                   //0x118
        ULONG OSMinorVersion;                                                   //0x11c
        USHORT OSBuildNumber;                                                   //0x120
        USHORT OSCSDVersion;                                                    //0x122
        ULONG OSPlatformId;                                                     //0x124
        ULONG ImageSubsystem;                                                   //0x128
        ULONG ImageSubsystemMajorVersion;                                       //0x12c
        ULONG ImageSubsystemMinorVersion;                                       //0x130
        UCHAR Padding4[4];                                                      //0x134
        ULONGLONG ActiveProcessAffinityMask;                                    //0x138
        ULONG GdiHandleBuffer[60];                                              //0x140
        ULONGLONG PostProcessInitRoutine;                                       //0x230
        ULONGLONG TlsExpansionBitmap;                                           //0x238
        ULONG TlsExpansionBitmapBits[32];                                       //0x240
        ULONG SessionId;                                                        //0x2c0
        UCHAR Padding5[4];                                                      //0x2c4
        union _ULARGE_INTEGER AppCompatFlags;                                   //0x2c8
        union _ULARGE_INTEGER AppCompatFlagsUser;                               //0x2d0
        ULONGLONG pShimData;                                                    //0x2d8
        ULONGLONG AppCompatInfo;                                                //0x2e0
        struct _STRING64 CSDVersion;                                            //0x2e8
        ULONGLONG ActivationContextData;                                        //0x2f8
        ULONGLONG ProcessAssemblyStorageMap;                                    //0x300
        ULONGLONG SystemDefaultActivationContextData;                           //0x308
        ULONGLONG SystemAssemblyStorageMap;                                     //0x310
        ULONGLONG MinimumStackCommit;                                           //0x318
        ULONGLONG SparePointers[2];                                             //0x320
        ULONGLONG PatchLoaderData;                                              //0x330
        ULONGLONG ChpeV2ProcessInfo;                                            //0x338
        ULONG AppModelFeatureState;                                             //0x340
        ULONG SpareUlongs[2];                                                   //0x344
        USHORT ActiveCodePage;                                                  //0x34c
        USHORT OemCodePage;                                                     //0x34e
        USHORT UseCaseMapping;                                                  //0x350
        USHORT UnusedNlsField;                                                  //0x352
        ULONGLONG WerRegistrationData;                                          //0x358
        ULONGLONG WerShipAssertPtr;                                             //0x360
        ULONGLONG EcCodeBitMap;                                                 //0x368
        ULONGLONG pImageHeaderHash;                                             //0x370
        union
        {
            ULONG TracingFlags;                                                 //0x378
            struct
            {
                ULONG HeapTracingEnabled : 1;                                     //0x378
                ULONG CritSecTracingEnabled : 1;                                  //0x378
                ULONG LibLoaderTracingEnabled : 1;                                //0x378
                ULONG SpareTracingBits : 29;                                      //0x378
            };
        };
        UCHAR Padding6[4];                                                      //0x37c
        ULONGLONG CsrServerReadOnlySharedMemoryBase;                            //0x380
        ULONGLONG TppWorkerpListLock;                                           //0x388
        struct LIST_ENTRY64 TppWorkerpList;                                     //0x390
        ULONGLONG WaitOnAddressHashTable[128];                                  //0x3a0
        ULONGLONG TelemetryCoverageHeader;                                      //0x7a0
        ULONG CloudFileFlags;                                                   //0x7a8
        ULONG CloudFileDiagFlags;                                               //0x7ac
        CHAR PlaceholderCompatibilityMode;                                      //0x7b0
        CHAR PlaceholderCompatibilityModeReserved[7];                           //0x7b1
        ULONGLONG LeapSecondData;                                               //0x7b8
        union
        {
            ULONG LeapSecondFlags;                                              //0x7c0
            struct
            {
                ULONG SixtySecondEnabled : 1;                                     //0x7c0
                ULONG Reserved : 31;                                              //0x7c0
            };
        };
        ULONG NtGlobalFlag2;                                                    //0x7c4
        ULONGLONG ExtendedFeatureDisableMask;                                   //0x7c8
    };
}

void __forceinline *_memset(void* buffer, int val, size_t size)
{
    __stosb(reinterpret_cast<PBYTE>(buffer), static_cast<BYTE>(val), size);
    return nullptr;
}

wchar_t towupper(wchar_t x)
{
    if (x >= L'a' && x < L'z')
    {
        x -= DynXor(ConstXor(32));
    }

    return x;
}

char _XXtoupper(char x)
{
    if (x >= 'a' && x < 'z')
    {
        x -= DynXor(ConstXor(32));
    }

    return x;
}

int __forceinline _wcsncmp(const wchar_t* cs, const wchar_t* ct, size_t count)
{
    if (count == 0)
        return 0;
    do {
        if (*cs != *ct++)
            return *cs - *--ct;
        if (*cs++ == 0)
            break;
    } while (--count != 0);
    return 0;
}

int __forceinline _wcsnicmp(const wchar_t* cs, const wchar_t* ct, size_t count)
{
    if (count == 0)
        return 0;
    do {
        if (towupper(*cs) != towupper(*ct++))
            return towupper(*cs) - towupper(*--ct);
        if (*cs++ == 0)
            break;
    } while (--count != 0);
    return 0;
}

int __forceinline _stricmp(const char* s1, const char* s2) {
    while (_XXtoupper((unsigned char)*s1) == _XXtoupper((unsigned char)*s2)) {
        if (*s1 == '\0')
            return 0;
        s1++; s2++;
    }

    return (int)_XXtoupper((unsigned char)*s1) -
        (int)_XXtoupper((unsigned char)*s2);
}

unsigned int __forceinline _wcslen(const wchar_t* s)
{
    unsigned int chars = 0;

    while (*(s++) != L'\0')
    {
        chars++;
    }

    return chars;
}


PVOID __forceinline GetFunctionAddress(PVOID pModule, const char* pExportName)
{
    auto pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(pModule);
    auto pNtHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<uintptr_t>(pModule) + pDosHeader->e_lfanew);

    // get the export directory
    auto& baseExportDirectory = pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];
    if (baseExportDirectory.VirtualAddress == NULL || baseExportDirectory.Size == 0)
        return nullptr;

    auto pExports = MakePtr(PIMAGE_EXPORT_DIRECTORY, pModule, baseExportDirectory.VirtualAddress);
    auto pdwNames = MakePtr(PULONG, pModule, pExports->AddressOfNames);
    auto pwOrdinals = MakePtr(PUSHORT, pModule, pExports->AddressOfNameOrdinals);
    auto pdwFuncs = MakePtr(PULONG, pModule, pExports->AddressOfFunctions);

    for (ULONG i = 0; i < pExports->NumberOfNames; i++)
    {
        PCSTR szExportName = MakePtr(PCSTR, pModule, pdwNames[i]);

        if (!_stricmp(pExportName, szExportName))
        {
            ULONG dwFunc = pdwFuncs[pwOrdinals[i]];

            // detect export forwarding
            if (dwFunc >= baseExportDirectory.VirtualAddress &&
                dwFunc < baseExportDirectory.VirtualAddress + baseExportDirectory.Size)
            {
                return nullptr;
            }
            else
                return MakePtr(PVOID, pModule, dwFunc);
        }
    }

    return nullptr;
}

class CTF
{
public:

    XorPtr<PVOID> m_kernel32 = nullptr;
    XorPtr<PVOID> m_ntdll = nullptr;
    
    XorPtr<decltype(&GetStdHandle)> m_GetStdHandle = nullptr;
    XorPtr<decltype(&WriteConsoleW)> m_WriteConsoleW = nullptr;
    XorPtr<decltype(&ReadConsoleW)> m_ReadConsoleW = nullptr;
    XorPtr<decltype(&NtWaitForSingleObject)> m_NtWaitForSingleObject = nullptr;
    XorPtr<tNtCreateThreadEx> m_NtCreateThreadEx = nullptr;
    XorPtr<decltype(&NtClose)> m_NtClose = nullptr;
    XorPtr<decltype(&ExitProcess)> m_ExitProcess = nullptr;

    XorPtr<HANDLE> m_stdIn = NULL;
    XorPtr<HANDLE> m_stdOut = NULL;

    void __forceinline stdout(const wchar_t* text)
    {
        DWORD written = 0;
        m_WriteConsoleW.Get()(m_stdOut.Get(), static_cast<const void*>(text), _wcslen(text), &written, NULL);
    }

    DWORD __forceinline stdin(wchar_t* buffer, DWORD count)
    {
        DWORD read = 0;
        m_ReadConsoleW.Get()(m_stdIn.Get(), buffer, count, &read, NULL);

        for (DWORD i = read - 1; i > 0; i--)
        {
            if (buffer[i] == L'\r' || buffer[i] == L'\n')
            {
                buffer[i] = L'\0';
                read--;
            }
        }

        return read;
    }

    bool FakeFlag(const wchar_t* input)
    {
        wchar_t compareBuff[44];
        _memset(compareBuff, 0, sizeof(compareBuff));
        memcpy(compareBuff, L"xgstn{nope_not_entirely_the_right_direction}", 42 * sizeof(wchar_t));

        compareBuff[0] = L'n';
        compareBuff[1] = L'l';
        compareBuff[2] = L'a';
        compareBuff[3] = L'n';
        compareBuff[4] = L'd';

        if (_wcsncmp(input, compareBuff, 42) == 0)
        {
            stdout(XOR_STRING(L"Look closer.\n"));
            return false;
        }

        return true;
    }

    static DWORD RealFlagThread(LPVOID param)
    {
        // To make it even harder one could make sure to not even put the entire flag on the stack at once
        auto flagCr = CBufferCrypted<wchar_t, L'n', L'l', L'a', L'n', L'd', L'{', L't', L'h', L'e', L'_', L's', L't', L'4', L'c', L'k', L'_', L'i', L's', L'_', L't', L'h', L'e', L'_', L'a', L'n', L's', L'w', L'e', L'r', L'}'>();

        if (_wcsncmp(reinterpret_cast<const wchar_t*>(param), flagCr.Decrypt().Get(), INPUT_BUFFER_SIZE) == 0)
        {
            *reinterpret_cast<wchar_t*>(param) = L'X';
        }

        return 0;
    }

    XorPtr<decltype(&RealFlagThread)> m_RealFlagThreadPtr = RealFlagThread;

    void __forceinline RealFlag(wchar_t* input)
    {
        if (input[0] == L'X')
        {
            return;
        }

        HANDLE hThread = NULL;
        m_NtCreateThreadEx.Get()(&hThread, THREAD_ALL_ACCESS, NULL, reinterpret_cast<HANDLE>(-1), static_cast<PVOID>(m_RealFlagThreadPtr.Get()), static_cast<PVOID>(input), 0x00000004 /* THREAD_CREATE_FLAGS_HIDE_FROM_DEBUGGER */, 0, 0, 0, 0);
        m_NtWaitForSingleObject.Get()(hThread, FALSE, NULL);
        m_NtClose.Get()(hThread);

        if (input[0] == L'X')
        {
            stdout(XOR_STRING(L"Congratulations.\n"));
            m_ExitProcess.Get()(0);
        }
    }

    void __forceinline GetFlag()
    {
        wchar_t input[INPUT_BUFFER_SIZE + 1 /* null terminator */];
        _memset(input, 0, sizeof(input));

        stdout(XOR_STRING(L"Enter Password: "));
        stdin(input, INPUT_BUFFER_SIZE);

        if (FakeFlag(input))
        {
            RealFlag(input);
            stdout(XOR_STRING(L"Incorrect password.\n"));
        }
    }

    void SetModules(PVOID ntdll, PVOID kernel32)
    {
        if (m_ntdll.Get() == reinterpret_cast<PVOID>(0xDEADBEEF))
        {
            m_ntdll = ntdll;
        }

        if (m_kernel32.Get() == reinterpret_cast<PVOID>(0xBEEFDEAD))
        {
            m_kernel32 = kernel32;
        }

        m_GetStdHandle = reinterpret_cast<decltype(&GetStdHandle)>(GetFunctionAddress(m_kernel32.Get(), XOR_STRING("GetStdHandle")));
        m_WriteConsoleW = reinterpret_cast<decltype(&WriteConsoleW)>(GetFunctionAddress(m_kernel32.Get(), XOR_STRING("WriteConsoleW")));
        m_ReadConsoleW = reinterpret_cast<decltype(&ReadConsoleW)>(GetFunctionAddress(m_kernel32.Get(), XOR_STRING("ReadConsoleW")));
        m_ExitProcess = reinterpret_cast<decltype(&ExitProcess)>(GetFunctionAddress(m_kernel32.Get(), XOR_STRING("ExitProcess")));

        m_NtWaitForSingleObject = reinterpret_cast<decltype(&NtWaitForSingleObject)>(GetFunctionAddress(m_ntdll.Get(), XOR_STRING("NtWaitForSingleObject")));
        m_NtCreateThreadEx = reinterpret_cast<tNtCreateThreadEx>(GetFunctionAddress(m_ntdll.Get(), XOR_STRING("NtCreateThreadEx")));
        m_NtClose = reinterpret_cast<decltype(&NtClose)>(GetFunctionAddress(m_ntdll.Get(), XOR_STRING("NtClose")));

        m_stdIn = m_GetStdHandle.Get()(STD_INPUT_HANDLE);
        m_stdOut = m_GetStdHandle.Get()(STD_OUTPUT_HANDLE);
    }

    CTF()
    {
        m_ntdll = reinterpret_cast<PVOID>(0xDEADBEEF);
        m_kernel32 = reinterpret_cast<PVOID>(0xBEEFDEAD);
    }

};

CTF ctf = CTF();

void InitObf(PVOID *pNtdll, PVOID *pKernel32)
{
    auto volatile pebNum = ConstXor(0x00000060);

    if (*reinterpret_cast<wchar_t*>(0x7FFE0030) /* KUSER_SHARED_DATA->NtSystemRoot */ == L'\0')
    {
        // This is just to break optimization
        pebNum = ConstXor(0x00000070);
    }

    if (*reinterpret_cast<char*>(0x7FFE02D4) /* KUSER_SHARED_DATA->KdDebuggerEnabled */ == 0)
    {
        pebNum = DynXor(pebNum);
    }

    auto pPEB = reinterpret_cast<_PEB64*>(__readgsqword(pebNum));

    if (pPEB->BeingDebugged)
    {
        // Make program crash
        pPEB = reinterpret_cast<_PEB64*>(reinterpret_cast<uintptr_t>(pPEB) - 1);
    }

    auto BeginListEntry = &reinterpret_cast<PEB_LDR_DATA*>(pPEB->Ldr)->InMemoryOrderModuleList;
    auto CurrentListEntry = BeginListEntry->Flink;

    wchar_t szNtdll[10];
    wchar_t szKernel32[13];

    _memset(szNtdll, 0, sizeof(szNtdll));
    _memset(szKernel32, 0, sizeof(szKernel32));

    szNtdll[0] = L'n';
    szNtdll[1] = L't';
    szNtdll[2] = L'd';
    szNtdll[3] = L'l';
    szNtdll[4] = L'l';
    szNtdll[5] = L'.';
    szNtdll[6] = L'd';
    szNtdll[7] = L'l';
    szNtdll[8] = L'l';

    szKernel32[0] = L'k';
    szKernel32[1] = L'e';
    szKernel32[2] = L'r';
    szKernel32[3] = L'n';
    szKernel32[4] = L'e';
    szKernel32[5] = L'l';
    szKernel32[6] = L'3';
    szKernel32[7] = L'2';
    szKernel32[8] = L'.';
    szKernel32[9] = L'd';
    szKernel32[10] = L'l';
    szKernel32[11] = L'l';

    void* tmpNtdll = nullptr;
    void* tmpKernel32 = nullptr;

    do
    {
        auto CurrentEntry = CONTAINING_RECORD(CurrentListEntry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);
        auto CurrentModuleName = reinterpret_cast<PUNICODE_STRING>(&CurrentEntry->Reserved4[0]);

        if (DynXor(CurrentModuleName->Length) == ConstXor(18) && _wcsnicmp(CurrentModuleName->Buffer, szNtdll, DynXor(ConstXor(9))) == 0)
        {
            tmpNtdll = CurrentEntry->DllBase;
        }
        else if (DynXor(CurrentModuleName->Length) == ConstXor(24) && _wcsnicmp(CurrentModuleName->Buffer, szKernel32, DynXor(ConstXor(12))) == 0)
        {
            tmpKernel32 = CurrentEntry->DllBase;
        }

        //MessageBoxW(NULL, CurrentModuleName->Buffer, NULL, 0);

        CurrentListEntry = CurrentListEntry->Flink;
    } while (BeginListEntry != CurrentListEntry);

    _memset(szNtdll, 0, sizeof(szNtdll));
    _memset(szKernel32, 0, sizeof(szKernel32));

    if (pNtdll)
        *pNtdll = tmpNtdll;
    if (pKernel32)
        *pKernel32 = tmpKernel32;

    auto pNtProtectVirtualMemory = reinterpret_cast<tNtProtectVirtualMemory>(GetFunctionAddress(tmpNtdll, XOR_STRING("NtProtectVirtualMemory")));

    // Fix sections
    PIMAGE_DOS_HEADER pDosHeader = reinterpret_cast<PIMAGE_DOS_HEADER>(&__ImageBase);
    auto pNtHeader = reinterpret_cast<PIMAGE_NT_HEADERS64>(reinterpret_cast<uintptr_t>(&__ImageBase) + pDosHeader->e_lfanew);

    auto pFirstSection = reinterpret_cast<PIMAGE_SECTION_HEADER>(pNtHeader + 1);

    for (PIMAGE_SECTION_HEADER pSection = pFirstSection;
        pSection < pFirstSection + pNtHeader->FileHeader.NumberOfSections;
        pSection++)
    {
        DWORD dwSize = pSection->Misc.VirtualSize;
        PVOID pBaseAddress = reinterpret_cast<PVOID>(reinterpret_cast<uintptr_t>(&__ImageBase) + pSection->VirtualAddress);

        if (pSection->Name[1] == 'r' && pSection->Name[2] == 'd')
        {
            // Make .rdata (which is actually .data) writeable
            pNtProtectVirtualMemory(reinterpret_cast<HANDLE>(-1), &pBaseAddress, &dwSize, PAGE_READWRITE, &dwSize);
        }
        else if (pSection->Name[1] == 't')
        {
            // Make .text (which is actually .rdata) non-executable
            pNtProtectVirtualMemory(reinterpret_cast<HANDLE>(-1), &pBaseAddress, &dwSize, PAGE_READONLY, &dwSize);
        }
    }
}

int main()
{
    PVOID tmpNtdll, tmpKernel32;
    InitObf(&tmpNtdll, &tmpKernel32);

	CallStaticInitializers();

    ctf.SetModules(tmpNtdll, tmpKernel32);
    ctf.GetFlag();

	return 0;
}