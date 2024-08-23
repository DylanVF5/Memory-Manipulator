#include "memorymanager.h"

void MemoryManager::GetPID()
{
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create snapshot\n";
        return;
    }
    if (Process32First(snapshot, &pEntry))
    {
        do
        {
            if (_wcsicmp(pEntry.szExeFile, targetName) == 0)
            {
                targetPID = pEntry.th32ProcessID;
                std::cout << "Found process " << targetName << " with PID: " << targetPID << std::endl;
                CloseHandle(snapshot);
                return;
            }
        } while (Process32Next(snapshot, &pEntry));
    }
    std::cerr << "Process not found\n";
    CloseHandle(snapshot);
}

std::uint64_t MemoryManager::GetBaseAddress()
{
    if (targetPID == 0)
    {
        std::cerr << "PID not set. Call GetPID() first.\n";
        return 0;
    }
    MODULEENTRY32 mEntry;
    mEntry.dwSize = sizeof(MODULEENTRY32);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, targetPID);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Failed to create module snapshot\n";
        return 0;
    }
    if (Module32First(snapshot, &mEntry))
    {
        do
        {
            if (_wcsicmp(mEntry.szModule, targetModule) == 0)
            {
                CloseHandle(snapshot);
                std::cout << "Found module base address: " << std::hex << (std::uint64_t)mEntry.modBaseAddr << std::dec << std::endl;
                return (std::uint64_t)mEntry.modBaseAddr;
            }
        } while (Module32Next(snapshot, &mEntry));
    }
    std::cerr << "Module not found\n";
    CloseHandle(snapshot);
    return 0;
}

void MemoryManager::GetHandle()
{
    if (targetPID == 0)
    {
        std::cerr << "PID not set. Call GetPID() first.\n";
        return;
    }
    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, targetPID);
    if (hProc == NULL)
    {
        std::cerr << "Failed to open process. Error code: " << GetLastError() << std::endl;
    }
    else
    {
        std::cout << "Successfully opened process handle\n";
    }
}