#include "Cheat.h"
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Cheat {
    
    void InitImGui(LPDIRECT3DDEVICE9 pDevice)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
        ImGui_ImplWin32_Init(Globals::window);
        ImGui_ImplDX9_Init(pDevice);
    }

    LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

        if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return true;

        return CallWindowProc(Globals::oWndProc, hWnd, uMsg, wParam, lParam);
    }

    bool init = false;
    long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
    {
        if (!init)
        {
            InitImGui(pDevice);
            init = true;
        }

        

        if (Memory::windowActive) {
            Memory::isIngame = Cheat::isIngame();

            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Made by PatchRequest");

            ImGui::Text("Client State: %d", *Memory::dwClientState_state);


            if (Memory::isIngame) {
                ImGui::Text("Bomb Planted: %d", bombPlanted());
                ImGui::Text("health: %d", *Memory::m_iHealth);
                ImGui::Text("Crosshair ID: %d", *Memory::m_iCrosshairId);
            }
            if (Cheat::triggerBotBool) {
                Cheat::triggerBot();
            }
            if (Cheat::healthStatusBool) {
                Cheat::healthList();
            }

            ImGui::End();

            ImGui::EndFrame();
            ImGui::Render();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

        }
        
        return Globals::oEndScene(pDevice);

    }
    void loadPointerChains() {
        
        Memory::dwClientState_state = (int*)Memory::GetPointerAddress(Memory::engine + hazedumper::signatures::dwClientState, { hazedumper::signatures::dwClientState_State });
        Memory::dwGameRulesProxy = (uintptr_t)Memory::GetPointerAddress(Memory::moduleBase + hazedumper::signatures::dwGameRulesProxy, {});
        Memory::dwGlowObjectManager = (uintptr_t)Memory::GetPointerAddress(Memory::moduleBase + hazedumper::signatures::dwGlowObjectManager, {});

        Memory::dwEntityList = (uintptr_t)Memory::GetPointerAddress(Memory::moduleBase + hazedumper::signatures::dwEntityList, {});
        Memory::m_iHealth = (int*)Memory::GetPointerAddress(Memory::local_player, { hazedumper::netvars::m_iHealth });
        Memory::bombPlanted = (bool*)Memory::GetPointerAddress(Memory::dwGameRulesProxy, { hazedumper::netvars::m_bBombPlanted });
        Memory::m_iCrosshairId = (int*)Memory::GetPointerAddress(Memory::local_player, { hazedumper::netvars::m_iCrosshairId });
        Memory::myTeam = (int*)Memory::GetPointerAddress(Memory::local_player , { hazedumper::netvars::m_iTeamNum });
        Memory::dwForceAttack = (int*)Memory::GetPointerAddress(Memory::moduleBase + hazedumper::signatures::dwForceAttack, {});
         

    }
    bool isIngame() {
        return (*Memory::dwClientState_state == 6);
    }
    bool bombPlanted() {
        return *Memory::bombPlanted;
    }

    void triggerBot() {

        if (*Memory::m_iCrosshairId != 0 && *Memory::m_iCrosshairId < 64) {
            
            uintptr_t currentEnemy = *(uintptr_t*)(Memory::dwEntityList + (*Memory::m_iCrosshairId - 1) * 0x10);
            int* enemyHealth = (int*)(currentEnemy + hazedumper::netvars::m_iHealth);
            int* team = (int*)(currentEnemy + hazedumper::netvars::m_iTeamNum);

            ImGui::Text("TargetTeam %d", *team);
            ImGui::Text("MyTeam %d", *Memory::myTeam);
            
            if (*Memory::myTeam != *team && *Memory::dwForceAttack != 5 && *enemyHealth > 0) {
                *Memory::dwForceAttack = 5;
            }
            else {
                *Memory::dwForceAttack = 4;
            }
           
        }
        
     }
    void healthList() {
        

        for (size_t i = 0; i < 32; i++) {
            uintptr_t entity = *(uintptr_t*)(Memory::dwEntityList + i * 0x10);
            if (entity) {
                
                int* entityHealth = (int*)(entity + hazedumper::netvars::m_iHealth);
                int* entityTeam = (int*)(entity + hazedumper::netvars::m_iTeamNum);
               
                if (*Memory::myTeam != *entityTeam) {
                    ImGui::Text("Healt From %d: %d", i, *entityHealth);
                }

            }
        }
    }

}
