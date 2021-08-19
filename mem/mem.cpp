#pragma once

#include <windows.h>
#include <vector>
namespace Memory {
    uintptr_t GetPointerAddress(uintptr_t ptr, std::vector<uintptr_t> offsets) {
        uintptr_t addr = ptr;
        for (int i = 0; i < offsets.size(); i++) {
            addr = *(uintptr_t*)addr;
            addr += offsets[i];

        }
        return addr;
    }

    void MemPatch(BYTE* dst, BYTE* src, unsigned int size) {
        DWORD oldprotect;
        VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
        memcpy(dst, src, size);
        VirtualProtect(dst, size, oldprotect, &oldprotect);
    }

    void memNop(BYTE* dst, unsigned int size) {
        DWORD oldprotect;
        VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
        memset(dst, 0x90, size);
        VirtualProtect(dst, size, oldprotect, &oldprotect);

    }
}