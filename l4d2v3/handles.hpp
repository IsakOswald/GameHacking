#pragma once
#include <Windows.h>
#include <cstdint>

namespace Core
{
class Handles
{
  private:
    uintptr_t _PID;
    uintptr_t _moduleBase;
    HANDLE _hProcess;

  public:
    Handles(uintptr_t ProcessID);
    ~Handles();

    void getProcessHandle() noexcept;
    void getModuleBase(const char* moduleName) noexcept;

    // Getter.
    HANDLE HProcess() const
    {
        return _hProcess;
    }

    uintptr_t ModuleBase() const
    {
        return _moduleBase;
    }
};
} // namespace Core