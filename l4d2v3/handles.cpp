#include "handles.hpp"
#include <TlHelp32.h>
#include <iostream>
#include <string.h>

namespace Core
{
Handles::Handles(uintptr_t ProcessID)
{
    _PID = ProcessID;
    _hProcess = nullptr;
    _moduleBase = 0;
}

Handles::~Handles()
{
    CloseHandle(_hProcess);
}

void Handles::getProcessHandle() noexcept
{

    HANDLE hTemp = OpenProcess(PROCESS_ALL_ACCESS, FALSE, _PID);
    if (hTemp == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to fetch process handle." << std::endl;
        _hProcess = 0;
        return;
    }

    std::cout << "Valid process handle successfully fetched." << std::endl;
    _hProcess = hTemp;
}
void Handles::getModuleBase(const char* moduleName) noexcept
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, _PID);

    if (!hSnap)
    {
        std::cerr << "Faild to fetch snapshot." << std::endl;
        return;
    }

    MODULEENTRY32 me32{};
    me32.dwSize = sizeof(me32);

    if (Module32First(hSnap, &me32))
    {
        do
        {
            if (_stricmp(moduleName, me32.szModule) == 0)
            {
                std::cout << "Module base for < " << moduleName << " > successfully fetched"
                          << std::endl;

                _moduleBase = reinterpret_cast<uintptr_t>(me32.modBaseAddr);
                break;
            }
        } while (Module32Next(hSnap, &me32));
    }

    CloseHandle(hSnap);
}
} // namespace Core