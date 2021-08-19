#pragma once

#include <windows.h>
#include <vector>



namespace Memory {

	__declspec(selectany) uintptr_t moduleBase = NULL;
	__declspec(selectany) uintptr_t engine = NULL;
	__declspec(selectany) uintptr_t local_player = NULL;
	__declspec(selectany) uintptr_t dwGameRulesProxy = NULL;
	__declspec(selectany) uintptr_t dwEntityList = NULL;
	__declspec(selectany) uintptr_t dwGlowObjectManager = NULL;

	__declspec(selectany) int* dwClientState_state = NULL;
	__declspec(selectany) int* myTeam = NULL;
	__declspec(selectany) int* m_iHealth = NULL;
	__declspec(selectany) int* m_iCrosshairId = NULL;
	__declspec(selectany) int* dwForceAttack = NULL;
	__declspec(selectany) bool* bombPlanted = NULL;
	__declspec(selectany) bool isIngame = false;
	__declspec(selectany) bool windowActive = false;

	uintptr_t GetPointerAddress(uintptr_t ptr, std::vector<uintptr_t> offsets);
	void MemPatch(BYTE* dst, BYTE* src, unsigned int size);
	void memNop(BYTE* dst, unsigned int size);

}