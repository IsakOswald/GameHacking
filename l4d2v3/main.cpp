#include "handles.hpp"
#include "memorysys.hpp"
#include <chrono>
#include <thread>

using namespace Core;

int main()
{
    Handles handles = Handles(1660);
    handles.getProcessHandle();
    handles.getModuleBase("server.dll");

    MemorySys memsys = MemorySys(handles.ModuleBase(), handles.HProcess());

    memsys.InitAddresses();

    std::thread t1(
        [&memsys]()
        {
            while (true)
            {
                memsys.ModifyTeamHealth(7);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
            }
        });

    t1.join();
    return -1;
}
