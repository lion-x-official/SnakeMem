﻿# 🐍 SnakeMem

SnakeMem is a lightweight and efficient C++ library for working with process memory on Windows. It allows developers to read and write process memory, retrieve module information, and manipulate pointers with ease.

## 🚀 Key Features

- **Memory Reading**: `ReadInt`, `ReadFloat`, `ReadPointer`, etc.
- **Memory Writing**: `Write<T>`, `WritePointer`
- **Pointer Handling**: `ReadPointers`, `WritePointer`
- **Module Address Retrieval**: `GetModuleAddress`
- **Process Management**: `GetProcessId`, `IsProcessActive`, `CloseProcess`
- **Reverse Pointer Search**: `ReverseSearchPointer`

---

## 📌 Installation

Clone the repository and navigate to the project folder:

```sh
git clone https://github.com/lion-x-official/SnakeMem.git
cd SnakeMem
```

---

## 📖 Usage Guide

### 🔍 Memory Reading
- `ReadInt(uintptr_t address)`: Reads an integer from memory.
- `ReadFloat(uintptr_t address)`: Reads a floating-point value.
- `ReadDouble(uintptr_t address)`: Reads a double-precision floating-point value.
- `ReadPointer(uintptr_t base, DWORD offset)`: Reads a pointer with a single offset.
- `ReadPointers(uintptr_t base, const std::vector<unsigned int>& offsets)`: Reads a pointer with multiple offsets.

### ✍️ Memory Writing
- `Write<T>(uintptr_t address, T value)`: Writes a value of type `T` to memory.
- `WritePointer(uintptr_t address, uintptr_t value)`: Writes a pointer to memory.

### 🖥️ Process and Module Management
- `GetProcessId()`: Retrieves the process ID.
- `GetProcessHandle()`: Returns the process handle.
- `GetModuleAddress(const char* module)`: Gets the base address of a module.

### ⚙️ Process Control
- `IsProcessActive()`: Checks if the target process is running.
- `CloseProcess()`: Closes the handle to the process.

### 🔄 Pointer Manipulation
- `ReverseSearchPointer(uintptr_t start, uintptr_t end, uintptr_t targetValue)`: Searches memory for a specific pointer value.

---

## 🛠 Compilation

SnakeMem can be used in any C++ project. To compile, use MinGW or MSVC:

```sh
g++ -o example.exe example.cpp -std=c++17 -Wall
```

---

## ⚠️ Disclaimer

Using SnakeMem to modify the behavior of third-party software may violate terms of service agreements. Use responsibly and at your own risk!

---

## 📜 License - MIT

```
MIT License

Copyright (c) 2025 LionX

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

---

🔗 **GitHub Repository**: [lion-x-official/SnakeMem](https://github.com/lion-x-official/SnakeMem)

