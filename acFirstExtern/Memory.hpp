#pragma once

#include "ProcAndModule.hpp"
#include <TlHelp32.h>
#include <Windows.h>
#include <cstdint>
#include <iostream>
#include <memoryapi.h>
#include <winnt.h>

namespace Core {
template <typename T> class Memory {

  HANDLE hProc;
  uintptr_t healthAddr;

public:
  T ReadProcessMemory(uintptr_t address);
  void WriteProcessMemory(uintptr_t address, T write);

  Memory(uintptr_t pid);
  ~Memory();
};

// Definitions
template <typename T> Memory<T>::Memory(uintptr_t pid) {
  this->hProc = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
}

template <typename T> T Memory<T>::ReadProcessMemory(uintptr_t address) {
  T value{};
  ::ReadProcessMemory(hProc, reinterpret_cast<LPCVOID>(address), &value,
                      sizeof(T), nullptr);
  return value;
}

template <typename T>
void Memory<T>::WriteProcessMemory(uintptr_t address, T write) {
  if (::WriteProcessMemory(hProc, reinterpret_cast<LPVOID>(address), &write,
                           sizeof(write), nullptr)) {
    std::cout << "We have written " << write << std::endl;
  }
}

template <typename T> Memory<T>::~Memory<T>() {
  if (hProc) {
    CloseHandle(hProc);
  }
}

} // namespace Core
