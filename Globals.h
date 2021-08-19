#pragma once
#include <d3d9.h>


typedef long(__stdcall* Reset)(LPDIRECT3DDEVICE9, D3DPRESENT_PARAMETERS*);
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);

namespace Globals {
	__declspec(selectany) Reset oReset = NULL;
	__declspec(selectany) EndScene oEndScene = NULL;
	__declspec(selectany) bool showWindow = true;
	__declspec(selectany) HWND window = NULL;
	__declspec(selectany) WNDPROC oWndProc;
} 