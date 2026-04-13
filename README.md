# C++ 学习项目

## 跨平台编译说明

本项目支持 Windows 和 macOS 双平台开发。

### 方法1：使用 CMake（推荐）

#### Windows:
```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .
./Main.exe
```

#### macOS:
```bash
mkdir build
cd build
cmake ..
make
./Main
```

### 方法2：直接使用 g++

#### Windows:
```bash
g++ Main.cpp -o Main.exe -std=c++20
Main.exe
```

#### macOS:
```bash
g++ Main.cpp -o Main -std=c++20
./Main
```

### VSCode 配置说明

- `.vscode/c_cpp_properties.json` - 包含 Win32 和 Mac 两套配置
- `.vscode/tasks.json` - Windows 编译任务（Mac 需要自己配置）
- 编译产物（*.exe, *.out）已在 .gitignore 中忽略

### 注意事项

1. 两个平台都需要支持 C++20 标准
2. 编译产物不会提交到 Git
3. VSCode 会根据当前系统自动选择对应配置
