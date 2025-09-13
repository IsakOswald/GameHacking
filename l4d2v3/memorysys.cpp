#include "memorysys.hpp"
#include <cstdint>
#include <iostream>

namespace Core
{
MemorySys::MemorySys(uintptr_t moduleBase, HANDLE hProcess) : _rwm(hProcess)
{
    _hProcess = hProcess;
    _moduleBase = moduleBase;
}

MemorySys::~MemorySys() = default;

void MemorySys::InitAddresses()
{
    _entityList = _moduleBase + 0x7E0774;
}
void MemorySys::ModifyTeamHealth(int HP)
{
    for (int i = 0; i < 4; i++)
    {
        uintptr_t entityPtr = _entityList + (i * 0x10);

        uintptr_t dereferencedEnt = _rwm.ReadProcessMem<uintptr_t>(entityPtr);

        if (!dereferencedEnt)
        {
            continue;
        }

        uintptr_t healthOffset = dereferencedEnt + 0xEC;

        int health = _rwm.ReadProcessMem<int>(healthOffset);

        std::cout << "P" << i + 1 << " HP -> " << health << std::endl;

        _rwm.WriteProcessMem(healthOffset, HP);
    }
}
void MemorySys::ModifyPlayerHealth(int HP) {}

} // namespace Core