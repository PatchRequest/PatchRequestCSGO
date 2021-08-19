#include <windows.h>
#include <kiero.h>
#include "Globals.h"
#include "Cheat.h"
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE; // skip to next window

    Globals::window = handle;
    return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
    Globals::window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return Globals::window;
}
DWORD WINAPI HackThread(HMODULE hModule) {
    bool attached = false;
    Memory::moduleBase = (uintptr_t)GetModuleHandle(L"client.dll");
    Memory::engine = (uintptr_t)GetModuleHandle(L"engine.dll");

    do {
        Memory::local_player = (uintptr_t)Memory::GetPointerAddress(Memory::moduleBase + hazedumper::signatures::dwLocalPlayer, {});
        Sleep(100);
    } while (!Memory::local_player);
    Cheat::loadPointerChains();
    do
    {
        if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
        {
            kiero::bind(42, (void**)&Globals::oEndScene, Cheat::hkEndScene);
            do
                Globals::window = GetProcessWindow();
            while (Globals::window == NULL);
            Globals::oWndProc = (WNDPROC)SetWindowLongPtr(Globals::window, GWL_WNDPROC, (LONG_PTR)Cheat::WndProc);
            attached = true;
        }
    } while (!attached);
    
    
    while(true){
        if (GetAsyncKeyState(VK_INSERT)) {
            Memory::windowActive = !Memory::windowActive;
        }
        Sleep(150);
    }
    
    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
       CreateThread(nullptr,0,(LPTHREAD_START_ROUTINE)HackThread,hModule,0,nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

