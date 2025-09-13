#pragma once

#include <Windows.h>
#include <iostream>

namespace Core
{
class ReadWriteMem
{
  private:
    HANDLE _hProcess;

  public:
    ReadWriteMem(HANDLE hProcess);
    ~ReadWriteMem();

    template <typename T> T ReadProcessMem(uintptr_t address)
    {
        T buffer{};

        if (!ReadProcessMemory(_hProcess, reinterpret_cast<LPCVOID>(address), &buffer,
                               sizeof(buffer), nullptr))
        {
            std::cerr << "Failed to read process memory @ 0x " << std::hex << address << std::endl;
            return T{};
        }

        std::cout << "Contents @ 0x" << std::hex << address << " is: " << buffer << std::endl;

        return buffer;
    }

    template <typename T> void WriteProcessMem(uintptr_t address, T value)
    {
        T buffer = value;
        if (!WriteProcessMemory(_hProcess, reinterpret_cast<LPVOID>(address), &buffer,
                                sizeof(buffer), nullptr))
        {
            std::cerr << "Failed to write process memory @ 0x" << std::hex << address << std::endl;
            return;
        }

        std::cout << "Successfully wrote " << value << " @ 0x" << std::hex << address << std::endl;
    }
};

} // namespace Core