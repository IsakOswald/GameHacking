#include "ProcAndModule.hpp"
#include <TlHelp32.h>
#include <cstdint>
#include <handleapi.h>
#include <winnt.h>
namespace Core {
uintptr_t GetProcID(const char *search_name) {
  uintptr_t PID = 0;

  // Take a snapshot of all processes.
  HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  // Check if valid.
  if (hSnap == INVALID_HANDLE_VALUE) {
    return 0;
  }

  // Create a struct to populate with data.
  PROCESSENTRY32 pe32 = {};
  pe32.dwSize = sizeof(pe32);

  // Check if there is a first process. Fill data into pe32.
  if (Process32First(hSnap, &pe32)) {
    do {
      // Compare names.
      if (_strcmpi(search_name, pe32.szExeFile) == 0) {
        PID = pe32.th32ProcessID;
        break;
      }
      // Continue while there are more processes.
    } while (Process32Next(hSnap, &pe32));
  }

  CloseHandle(hSnap);

  return PID;
}

uintptr_t GetModuleBase(uintptr_t PID, const char *module_name) {
  uintptr_t MBASE = 0;

  // Create a snapshot of the modules in a process this time.
  HANDLE hSnap =
      CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
  if (hSnap == INVALID_HANDLE_VALUE) {
    return 0;
  }

  MODULEENTRY32 me32 = {};
  me32.dwSize = sizeof(me32);

  if (Module32First(hSnap, &me32)) {
    do {
      if (_strcmpi(module_name, me32.szModule) == 0) {
        // Get our moudle base address.
        MBASE = reinterpret_cast<uintptr_t>(me32.modBaseAddr);
        break;
      }
    } while (Module32Next(hSnap, &me32));
  }

  CloseHandle(hSnap);

  return MBASE;
}
} // namespace Core