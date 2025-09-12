#include "memreadwrite.hpp"
#include "procaccess.hpp"
#include <cstdint>
#include <iostream>
using namespace Core;

int main() {
  // Set up ProcAccess class
  ProcAccess pa = ProcAccess(8716);
  // Get a handle to the process using the ProcID in construction.
  HANDLE hProcess = pa.GetProcessHandle();
  uintptr_t dllBase = pa.GetServerDllBase("server.dll");

  // Create mrw with that process handle.
  MemReadWrite mrw = MemReadWrite(hProcess);

  // Set up addresses.
  uintptr_t localPlayerPtr = (uintptr_t)dllBase + 0x7E0774;
  // Read the local player pointer to get inside the class.
  if (!localPlayerPtr) {

    return -1;
  }

  uintptr_t localPlayer = mrw.ReadMemory<uintptr_t>(localPlayerPtr);
  // Move offsets (byte wise) and read.
  int p_health = mrw.ReadMemory<int>(localPlayer + 0xEC);
  std::cout << "Player health is ->  " << p_health << std::endl;

  // Write.
  mrw.WriteMemory<int>(localPlayer + 0xEC, 10000);

  // Clean up the handle.
  CloseHandle(hProcess);

  // Allow user to see info.
  std::cin.get();

  return 0;
}