#include "Memory.hpp"
#include <cstdint>

int main() {
  const char *processName = "ac_client.exe";
  const char *moduleName = "ac_client.exe";

  uintptr_t ProcID = Core::GetProcID(processName);
  if (!ProcID) {
    std::cerr << "Process not found!\n";
    return 1;
  }

  uintptr_t ModuleBase = Core::GetModuleBase(ProcID, moduleName);
  if (!ModuleBase) {
    std::cerr << "Cant find module base\n";
    return 1;
  }

  std::cout << "Proccess ID is: " << ProcID << std::endl;
  std::cout << "Module base is: " << ModuleBase << std::endl;

  // On the stack is fine.
  Core::Memory<float> mem = Core::Memory<float>(ProcID);
  Core::Memory<uintptr_t> deref = Core::Memory<uintptr_t>(ProcID);

  // health address.
  uintptr_t BasePtr = ModuleBase + 0x17E0A8;
  uintptr_t LocalPlayer = deref.ReadProcessMemory(BasePtr);
  uintptr_t HealthAddr = LocalPlayer + 0xEC;

  float readValue = mem.ReadProcessMemory(HealthAddr);
  std::cout << "Health is: " << readValue << std::endl;

  Core::Memory<int> memInt(ProcID);
  int healthInt = memInt.ReadProcessMemory(HealthAddr);
  std::cout << "Health as int: " << healthInt << std::endl;

  mem.WriteProcessMemory(HealthAddr, 999);

  std::cout << "BasePtr: 0x" << std::hex << BasePtr << std::endl;
  std::cout << "LocalPlayer: 0x" << std::hex << LocalPlayer << std::endl;
  std::cout << "HealthAddr: 0x" << std::hex << HealthAddr << std::endl;

  std::cin.get();

  return 0;
}