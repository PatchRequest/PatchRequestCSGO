#pragma once
#include <windows.h>
#include <kiero.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include <d3d9.h>
#include "imgui/imgui_impl_win32.h"
#include "Globals.h"
#include <tchar.h>
#include "csgo.hpp"
#include "mem/mem.h"

namespace Cheat {
	long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice);
	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitImGui(LPDIRECT3DDEVICE9 pDevice);
	void loadPointerChains();
	bool isIngame();
	bool bombPlanted();
	void triggerBot();
	void healthList();

	__declspec(selectany) bool triggerBotBool = false;
	__declspec(selectany) bool healthStatusBool = false;
}
