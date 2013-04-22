#include <Bibim/Config.h>
#include <Bibim/FWD.h>
#include <Bibim/Assert.h>

#if (defined(BIBIM_PLATFORM_WINDOWS))
#   include <windows.h>

#   pragma pack( push, before_imagehlp, 8 )
#   include <imagehlp.h>
#   pragma pack( pop, before_imagehlp )

#   include <Tlhelp32.h>
#   include <Psapi.h>
#   include <new.h>

#   include <string>
#   include <sstream>
#   include <fstream>

    namespace Bibim
    {
        namespace
        {
            static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI DummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER /*lpTopLevelExceptionFilter*/)
            {
                return NULL;
            }

            static LONG CALLBACK ExceptionFilter(struct _EXCEPTION_POINTERS *ep)
            {
                if (ep == NULL)
                    return EXCEPTION_EXECUTE_HANDLER;

                HINSTANCE dbghelp = LoadLibrary("dbghelp.dll");
                if (dbghelp == NULL)
                    return EXCEPTION_EXECUTE_HANDLER;

                typedef BOOL (__stdcall *MiniDumpWriteFunction)(IN HANDLE hProcess, 
                                                                IN DWORD ProcessId,
                                                                IN HANDLE hFile,
                                                                IN MINIDUMP_TYPE DumpType,
                                                                IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
                                                                IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
                                                                IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL);

                MiniDumpWriteFunction writeMiniDump = reinterpret_cast<MiniDumpWriteFunction>(GetProcAddress(dbghelp, "MiniDumpWriteDump"));
                if (writeMiniDump == NULL)
                {
                    FreeLibrary(dbghelp);
                    return EXCEPTION_EXECUTE_HANDLER;
                }
                
                {
                    char moduleFileNameCharacters[MAX_PATH]  = { '\0', };

                    MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
                    exceptionInfo.ThreadId = GetCurrentThreadId();
                    exceptionInfo.ExceptionPointers = ep;
                    exceptionInfo.ClientPointers = FALSE;

                    GetModuleFileName(NULL, moduleFileNameCharacters, sizeof(moduleFileNameCharacters));

                    std::string moduleFileName = moduleFileNameCharacters;
                    std::string::size_type filenameIndex = moduleFileName.rfind('\\');
                    
                    SYSTEMTIME CurrentTime;
                    GetSystemTime(&CurrentTime);

                    std::ostringstream dumpFileNameStream;
                    dumpFileNameStream << moduleFileName.substr(0, filenameIndex + 1);
                    dumpFileNameStream << "ERROR ";
                    dumpFileNameStream << CurrentTime.wYear << "-" << CurrentTime.wMonth << "-" << CurrentTime.wDay << " " << CurrentTime.wHour << "-" << CurrentTime.wMinute << "-" << CurrentTime.wSecond;
                    dumpFileNameStream << ".dmp";

                    HANDLE fileHandle = CreateFile( dumpFileNameStream.str().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
                    if (fileHandle != INVALID_HANDLE_VALUE)
                    {
                        std::ostringstream alertMessageStream;
                        alertMessageStream << "엄청난 오류가 발생했습니다." << std::endl;
                        alertMessageStream << "오류를 빨리 해결하기 위해 여러가지 정보를 수집할게요." << std::endl;
                        alertMessageStream << "정보 수집이 끝나면 자동으로 종료될테니 기다려주세요." << std::endl;
                        alertMessageStream << "프로그램이 끝나면 실행 파일과 같은 폴더에 있는 " << dumpFileNameStream.str() << "를 보내주세요.";

                        MessageBox(NULL, alertMessageStream.str().c_str(), "ERROR", MB_ICONERROR);
                        writeMiniDump(GetCurrentProcess(), GetCurrentProcessId(), fileHandle, MiniDumpNormal, &exceptionInfo, NULL, NULL);
                        CloseHandle(fileHandle);
                    }
                }

                FreeLibrary(dbghelp);

                return EXCEPTION_EXECUTE_HANDLER;
            }

            static void HookAPISetUnhandledExceptionFilter()
            {
                HMODULE kernel32 = LoadLibrary("kernel32.dll");
                if (kernel32 == NULL)
                    return;

                void* orgEntry = GetProcAddress(kernel32, "SetUnhandledExceptionFilter");
                if (orgEntry == NULL)
                    return;

                unsigned char newJump[100];
                unsigned char* orgEntryAddress = reinterpret_cast<unsigned char*>(orgEntry) + 5; // add 5 for 5 op-codes for jmp far

                void* newFunction = &DummySetUnhandledExceptionFilter;

                unsigned char* newEntryAddress = reinterpret_cast<unsigned char*>(newFunction);
                ptrdiff_t relativeAddress  = newEntryAddress - orgEntryAddress;

                newJump[0] = 0xE9;  // JMP absolute
                memcpy(&newJump[1], &relativeAddress, sizeof(ptrdiff_t));

                SIZE_T bytesWritten = 0;
                WriteProcessMemory( GetCurrentProcess(), orgEntry, newJump, sizeof(newFunction) + 1, &bytesWritten );
            }

            static void InvalidParameterHandler(const wchar_t* /*expression*/,
                                                const wchar_t* /*function*/,
                                                const wchar_t* /*file*/,
                                                unsigned int /*line*/,
                                                uintptr_t /*pReserved*/)
            {
                BBBreak();
            }

            static void PurecallHandler()
            {
                BBBreak();
            }

            static int NewHandler(size_t /*size*/)
            {
                BBBreak();
                return 0;
            }
        }

        inline void InitializeCrashDump()
        {
            ::SetUnhandledExceptionFilter(ExceptionFilter);
            ::_set_invalid_parameter_handler(InvalidParameterHandler);
            ::_set_purecall_handler(PurecallHandler);
            ::_set_new_handler(NewHandler);

            HookAPISetUnhandledExceptionFilter();
        }
    }

#   else
    namespace Bibim
    {
        inline void InitializeCrashDump() { }
    }
#endif