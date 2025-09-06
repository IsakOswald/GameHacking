#include <Windows.h>
#include <cstdint>

namespace Core {
uintptr_t GetProcID(const char *search_name);
uintptr_t GetModuleBase(uintptr_t PID, const char *module_name);
} // namespace Core
