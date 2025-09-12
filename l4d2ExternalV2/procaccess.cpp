#include "procaccess.hpp"
#include <TlHelp32.h>
#include <cstdint>
#include <handleapi.h>
#include <iostream>
#include <winnt.h>

namespace Core {
ProcAccess::ProcAccess(DWORD PID) { _ProcessID = PID; }
HANDLE ProcAccess::GetProcessHandle() const noexcept {
  // Get a handle to the process with all permissions on the specified process
  // ID.
  HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, _ProcessID);

  // Check If valid.
  if (!hProcess) {
    std::cerr << "Error fetching process handle.";
    return 0;
  }

  return hProcess;
}

uintptr_t ProcAccess::GetServerDllBase(const char *moduleName) const noexcept {

  // This struct holds information about each module in the snapshot
  MODULEENTRY32 me32{};
  me32.dwSize = sizeof(me32);

  // Create a snapshot.
  HANDLE hSnapshot = CreateToolhelp32Snapshot(
      TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, _ProcessID);

  // Check if valid.
  if (hSnapshot == INVALID_HANDLE_VALUE) {
    std::cerr << "Error fetching snapshot.";
    return 0;
  }

  // Check if the first module exists in the snapshot.
  if (Module32First(hSnapshot, &me32)) {
    // Loop over the snapshots untill we find the matching module specified in
    // paramater.
    do {
      if (_stricmp(moduleName, me32.szModule) == 0) {
        return reinterpret_cast<uintptr_t>(me32.modBaseAddr);
      }
    } while (Module32Next(hSnapshot, &me32));
  }

  // We are done with the snapshot handle.
  CloseHandle(hSnapshot);
  return 0;
}
} // namespace Core