#pragma once
#include "../dependencies/common.h"

class MemoryManager
{
public:
	MemoryManager(const wchar_t* targetName, const wchar_t* targetModule) : targetName(targetName), targetModule(targetModule) {}

	void GetPID();
	std::uint64_t GetBaseAddress();
	void GetHandle();

	template<typename T>
	T Read(std::uint64_t address)
	{
		T buffer{};
		if (hProc != INVALID_HANDLE_VALUE)
		{
			if (ReadProcessMemory(hProc, reinterpret_cast<LPCVOID>(address), &buffer, sizeof(T), NULL))
			{
				return buffer;
			}
		}

		return NULL;
	}

	template<typename T>
	bool Write(std::uint64_t address, const T& value)
	{
		if (hProc != INVALID_HANDLE_VALUE)
		{
			if (WriteProcessMemory(hProc, reinterpret_cast<LPVOID>(address), &value, sizeof(T), NULL))
			{
				return true;
			}
		}

		return false;
	}

private:
	DWORD targetPID = 0;
	const wchar_t* targetName;
	const wchar_t* targetModule;
	HANDLE hProc = 0;
};