#include <iostream>
#include "memory/memorymanager.h"

int main()
{
    constexpr const wchar_t* targetName = L"Notepad.exe";
    const auto memory = std::make_unique<MemoryManager>(targetName, targetName);

    memory->GetPID();
    memory->GetHandle();

    const std::uint64_t base = memory->GetBaseAddress();

    std::printf("base: %llx\n", base);

    // example of reading a page of memory each iteration
    for (int i = 0; i < 25; i++)
    {
        std::uint64_t mem = memory->Read<std::uint64_t>(base + i * 0x1000);

        std::printf("memory: %llx\n", mem);
    }
}