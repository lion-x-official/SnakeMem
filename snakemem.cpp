#include "snakemem.h"
#include <iostream>
#include <tlhelp32.h>
#include <windows.h>

SnakeMem::SnakeMem(std::string processName) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    this->processId = 0;
    this->hProcess = NULL;
    this->processName = processName;

    if (processName.find(".exe") == std::string::npos) {
        processName += ".exe";
    }

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        CloseHandle(hProcessSnap);
        return;
    }

    do {
        if (strcmp(pe32.szExeFile, processName.c_str()) == 0) {
            this->processId = pe32.th32ProcessID;
            this->hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->processId);
            break;
        }
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

uintptr_t SnakeMem::ReadPointer(uintptr_t base, DWORD offset) {
    uintptr_t addr = base + offset;
    if (!ReadProcessMemory(this->hProcess, (BYTE*)addr, &addr, sizeof(addr), nullptr)) {
        return 0;
    }
    return addr;
}

uintptr_t SnakeMem::ReadPointers(uintptr_t base, const std::vector<unsigned int>& offsets) {
    uintptr_t addr = base;
    for (unsigned int offset : offsets) {
        addr += offset;
        if (!ReadProcessMemory(this->hProcess, (BYTE*)addr, &addr, sizeof(addr), nullptr)) {
            return 0;
        }
    }
    return addr;
}

DWORD SnakeMem::GetProcessId() {
    return this->processId;
}

HANDLE SnakeMem::GetProcessHandle() {
    return this->hProcess;
}

uintptr_t SnakeMem::GetModuleAddress(const char* module) {
    HANDLE hModuleSnap;
    MODULEENTRY32 me32;
    uintptr_t moduleAddress = 0;

    hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->processId);
    if (hModuleSnap == INVALID_HANDLE_VALUE) {
        return 0;
    }

    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32)) {
        CloseHandle(hModuleSnap);
        return 0;
    }

    do {
        if (strcmp(me32.szModule, module) == 0) {
            moduleAddress = (uintptr_t)me32.modBaseAddr;
            break;
        }
    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return moduleAddress;
}
