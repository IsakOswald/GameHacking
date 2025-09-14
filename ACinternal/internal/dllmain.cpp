// dllmain.cpp : Defines the entry point for the DLL application.
#include "rwm.hpp"
#include <Windows.h>
#include <thread>

using namespace Core;


DWORD WINAPI MainThread() {

    RWM rmw = RWM();

    while (true) {
        rmw.WritePlayerHealth(2000);
        rmw.WritePlayerAmmo(2000);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }


    

    return 0;
     
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MainThread), nullptr, 0, nullptr);
        break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
