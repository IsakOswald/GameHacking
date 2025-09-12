#pragma once

#include <Windows.h>
#include <iostream>
#include <memoryapi.h>
namespace Core {
class MemReadWrite {
private:
  HANDLE hProcess;

public:
  MemReadWrite(HANDLE processHandle) { hProcess = processHandle; };

  template <typename T> const T ReadMemory(uintptr_t address) const noexcept {
    // A buffer to read the contents back into.
    T buffer;
    if (!ReadProcessMemory(hProcess, reinterpret_cast<LPCVOID>(address),
                           &buffer, sizeof(buffer), nullptr)) {
      std::cerr << "Failed to read from 0x" << address;
    }

    return buffer;
  }

  template <typename T>
  void WriteMemory(uintptr_t address, T value) const noexcept {
    // Create a copy for the function call.
    T toWrite = value;
    // If the write fails.
    if (!WriteProcessMemory(hProcess, reinterpret_cast<LPVOID>(address),
                            &toWrite, sizeof(toWrite), nullptr)) {
      std::cerr << "Failed to write value < " << toWrite << " > @ 0x"
                << address;
    }

    // Otherwise the write was successful!
    std::cout << "Successful write!" << std::endl;
  }
};

} // namespace Core