#pragma once

#include <Windows.h>
#include <cstdint>

namespace Core {
// This file is responsible for getting the process handle and module base of
// sever.dll

class ProcAccess {
private:
  DWORD _ProcessID;

public:
  ProcAccess(DWORD PID);
  ~ProcAccess() = default; // Default destructor (deletes strings etc).
  HANDLE GetProcessHandle() const noexcept;
  uintptr_t GetServerDllBase(const char *moduleName) const noexcept;
};
} // namespace Core