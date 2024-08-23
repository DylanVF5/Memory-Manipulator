# Projects Utilizing:
- https://github.com/DylanVF5/Unreal-Engine-5-Base

# Memory Manager
- A Windows-based tool for external process memory manipulation.

# Features

- Process identification by name
- Module base address retrieval
- Process memory reading and writing

# Usage
```cpp
auto memory = std::make_unique<MemoryManager>(L"Notepad.exe", L"Notepad.exe");
memory->GetPID();
memory->GetHandle();
uint64_t base = memory->GetBaseAddress();

// Read memory
uint64_t value = memory->Read<uint64_t>(base + offset);

// Write memory
memory->Write<uint64_t>(base + offset, newValue);
```

# Purpose
- Designed for educational use in understanding Windows process memory manipulation. Use responsibly and only with processes you own or have permission to modify.
