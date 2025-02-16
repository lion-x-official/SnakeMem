#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>

class SnakeMem {
private:
	DWORD processId = NULL;
	HANDLE hProcess = INVALID_HANDLE_VALUE;
	std::string processName;

public:
	SnakeMem(std::string processName);

	uintptr_t ReadPointer(uintptr_t base, DWORD offset);

	uintptr_t ReadPointers(uintptr_t base, const std::vector<unsigned int>& offsets);

	DWORD GetProcessId();
	HANDLE GetProcessHandle();
	uintptr_t GetModuleAddress(const char* module);

	template <typename T>
	bool Write(uintptr_t address, T value) {
		return WriteProcessMemory(hProcess, (LPVOID)address, &value, sizeof(T), nullptr);
	}

	template <typename T>
	T Read(uintptr_t address) {
		T buffer;
		if (!ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), nullptr)) {
			std::cerr << "Error reading memory at address: " << std::hex << address << std::dec << std::endl;
		}
		return buffer;
	}

	bool WritePointer(uintptr_t address, uintptr_t value) {
		return Write<uintptr_t>(address, value);
	}

	uintptr_t ReverseSearchPointer(uintptr_t start, uintptr_t end, uintptr_t targetValue) {
		for (uintptr_t addr = start; addr < end; addr += sizeof(uintptr_t)) {
			uintptr_t value = Read<uintptr_t>(addr);
			if (value == targetValue) {
				return addr;
			}
		}
		return 0;
	}

	bool IsProcessActive() {
		DWORD exitCode;
		if (GetExitCodeProcess(hProcess, &exitCode)) {
			return exitCode == STILL_ACTIVE;
		}
		return false;
	}

	void CloseProcess() {
		if (hProcess != INVALID_HANDLE_VALUE) {
			CloseHandle(hProcess);
			hProcess = INVALID_HANDLE_VALUE;
		}
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
