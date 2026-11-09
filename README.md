# mymath.dll 动态链接库实验

Visual Studio 2017 工程：把加、减、乘、除四个运算模块编译成 **mymath.dll**，
再由 **UseMath** 控制台程序链接 `mymath.lib` 并运行，验证动态链接库的生成与使用。

- 平台：Visual Studio 2017，Debug | x86（Win32），C++
- 运行结果：

```text
a = 20262814
b = 10
20262814+10=20262824
20262814-10=20262804
20262814*10=202628140
20262814/10=2026281
```

## 目录结构

```text
.
├─ mymath.h                  # 导出声明（__declspec(dllexport)）
├─ add.cpp / sub.cpp         # 四个运算模块（DLL 的源文件）
├─ mul.cpp / div.cpp
├─ main.cpp                  # UseMath 控制台程序
├─ mymath/                   # mymath.dll 解决方案
│  ├─ mymath.sln
│  └─ mymath/                # 工程文件、dllmain.cpp、pch.*、framework.h
└─ UseMath/                  # UseMath 解决方案
   ├─ UseMath.sln
   └─ UseMath/               # 工程文件
```

## 生成与运行

1. 打开 `mymath/mymath.sln`，配置选 **Debug | x86**，生成解决方案
   → 输出 `mymath/Debug/mymath.dll`（同时生成导入库 `mymath.lib`）。
2. 打开 `UseMath/UseMath.sln`，同样选 **Debug | x86**，生成 → 输出 `UseMath/Debug/UseMath.exe`。
3. 把 `mymath.dll` 复制到 `UseMath.exe` 所在目录（或把两个工程放进同一个解决方案，
   VS 默认输出到同一个 Debug 目录），按 F5 运行，输出见上。

## 关键配置

| 位置 | 配置 |
| --- | --- |
| mymath.vcxproj | 配置类型：动态库(.dll)；预处理器定义含 `MYMATH_EXPORTS`；附加包含目录 `..\..` |
| UseMath.vcxproj | 链接器 → 附加依赖项：`mymath.lib`；附加库目录 `..\..\mymath\Debug`；附加包含目录 `..\..` |
| mymath.h | `__declspec(dllexport) int add/sub/mul/div(int, int);` |

> 工程中的包含目录、库目录都是相对路径，克隆到任意目录都能直接生成。

## 条件断点

在 `add` 函数的 `return a + b;` 一行按 F9，右键断点 → 条件，输入 `a == 20262814`，
按 F5 调试运行即可在条件成立时停下。

## 说明

- `mymath.h` 用 `__declspec(dllexport)` 导出四个函数，`mymath` 工程通过
  `MYMATH_EXPORTS` 宏保证编译时是导出而不是导入。
- 运行 `UseMath.exe` 时 `mymath.dll` 必须与 exe 同目录，否则会提示找不到 DLL。
- 整数除法：`20262814 / 10` 结果为 `2026281`。