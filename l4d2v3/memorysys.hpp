#pragma once

#include "readWriteMem.hpp"
#include <Windows.h>

namespace Core
{
class MemorySys
{
  private:
    ReadWriteMem _rwm;
    HANDLE _hProcess;
    uintptr_t _moduleBase;
    uintptr_t _entityList;

  public:
    MemorySys(uintptr_t moduleBase, HANDLE hPrcoess);
    ~MemorySys();
    void InitAddresses();
    void ModifyTeamHealth(int HP);
    void ModifyPlayerHealth(int HP);
};

} // namespace Core