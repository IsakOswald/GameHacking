#include "readWriteMem.hpp"

namespace Core
{

ReadWriteMem::ReadWriteMem(HANDLE hProcess)
{
    _hProcess = hProcess;
}
ReadWriteMem::~ReadWriteMem() = default;

} // namespace Core