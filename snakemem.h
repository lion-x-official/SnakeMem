#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <random>
#include <intrin.h>

class SnakeMem {
private:
    DWORD processId = NULL;
    HANDLE hProcess = INVALID_HANDLE_VALUE;
    std::string processName;

    void RandomSleep() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10 + rand() % 50));
    }

    void ObfuscateMemory(uintptr_t address, size_t size) {
        std::vector<uint8_t> buffer(size);
        ReadProcessMemory(hProcess, (LPCVOID)address, buffer.data(), size, nullptr);
        for (auto& byte : buffer) byte ^= 0x5A;  // XOR-шифрование
        WriteProcessMemory(hProcess, (LPVOID)address, buffer.data(), size, nullptr);
    }

    uintptr_t MaskAddress(uintptr_t address) {
        return address ^ 0xDEADBEEF;
    }

public:
    SnakeMem(std::string processName);

    uintptr_t ReadPointer(uintptr_t base, DWORD offset);
    uintptr_t ReadPointers(uintptr_t base, const std::vector<unsigned int>& offsets);
    DWORD GetProcessId();
    HANDLE GetProcessHandle();
    uintptr_t GetModuleAddress(const char* module);

    template <typename T>
    bool Write(uintptr_t address, T value) {
        RandomSleep();
        DWORD oldProtect;
        address = MaskAddress(address);
        VirtualProtectEx(hProcess, (LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
        bool result = WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
        VirtualProtectEx(hProcess, (LPVOID)address, sizeof(T), oldProtect, &oldProtect);
        return result;
    }

    template <typename T>
    T Read(uintptr_t address) {
        RandomSleep();
        address = MaskAddress(address);
        T buffer;
        DWORD oldProtect;
        VirtualProtectEx(hProcess, (LPVOID)address, sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect);
        ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), nullptr);
        VirtualProtectEx(hProcess, (LPVOID)address, sizeof(T), oldProtect, &oldProtect);
        return buffer;
    }

    int ReadInt(uintptr_t address) { return Read<int>(address); }
    int8_t ReadInt8(uintptr_t address) { return Read<int8_t>(address); }
    uint8_t ReadUint8(uintptr_t address) { return Read<uint8_t>(address); }
    int16_t ReadInt16(uintptr_t address) { return Read<int16_t>(address); }
    uint16_t ReadUint16(uintptr_t address) { return Read<uint16_t>(address); }
    int32_t ReadInt32(uintptr_t address) { return Read<int32_t>(address); }
    uint32_t ReadUint32(uintptr_t address) { return Read<uint32_t>(address); }
    int64_t ReadInt64(uintptr_t address) { return Read<int64_t>(address); }
    uint64_t ReadUint64(uintptr_t address) { return Read<uint64_t>(address); }
    float ReadFloat(uintptr_t address) { return Read<float>(address); }
    double ReadDouble(uintptr_t address) { return Read<double>(address); }
    long double ReadLongDouble(uintptr_t address) { return Read<long double>(address); }
};
