#include <Windows.h>
#include <cstdint>
#include <iostream>

DWORD WINAPI myMainThread(LPVOID lpParam) {

  HMODULE hModule = (HMODULE)lpParam; // Cast the void pointer back to HMODU
  // LE
  uintptr_t server_base =
      reinterpret_cast<uintptr_t>(GetModuleHandleA("server.dll"));

  if (!server_base) {
    std::cerr << "Error getting the module handle\n";
    return 0;
  }

  // Entity list is at offset 0x7E0774
  uintptr_t entityListAddress =
      server_base +
      0x7E0774; // This is the address of the ptr to the entity list.

  // EntityListAddress is a pointer to the heap which points to many different
  // entities. We want the first element for iteration.
  uintptr_t *entityArrayBase = *(uintptr_t **)(entityListAddress);

  for (int i = 0; i < 4; i++) {
    // Select the entity in the entity list. We need to cast to uintptr_t to get
    // raw byte arithemitic.
    uintptr_t selectedEntity = (uintptr_t)entityArrayBase + (i * 0x10);

    int *healthAddress =
        (int *)(selectedEntity +
                0xEC); // Take the offset for health insdie the selected entity.

    // Set health
    *healthAddress = 5000000;
  }

  return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
  if (dwReason == DLL_PROCESS_ATTACH) {
    DisableThreadLibraryCalls(hModule); // optional optimization
    ::CreateThread(nullptr, 0, myMainThread, hModule, 0, nullptr);
  }
  return TRUE;
}
