# KtCore

开源的C++基础库 

## CMake 依赖规则

同一个 Git 仓库内部的目标（包括 tests）必须直接使用仓库内已经创建的
CMake target，不使用 `find_package(KtCore)`，也不手动指定 KtCore 的头文件
目录或本地 `.lib` 路径。

例如：

```cmake
target_link_libraries(test_KtString PRIVATE KtCore)
```

CMake 会通过 `KtCore` target 自动传递本地源码的头文件目录、编译选项和链接
依赖。这样可以避免测试或其他内部目标错误地引用 SDK 安装目录中的头文件，
造成安装版本与当前本地源码不一致。

只有仓库外部的独立工程消费已安装的 KtCore SDK 时，才使用
`find_package(KtCore CONFIG REQUIRED)` 或显式导入本地库。

## 构建脚本

构建脚本不需要传入参数，按以下顺序执行：

1. 导出公共头文件
2. 编译 Debug
3. 编译 Release
4. 最后执行一次 Release install，生成 SDK package

macOS/Linux：

```bash
sh buildAll.sh
```

Windows：

```powershell
.\buildAll.ps1
```

头文件统一输出到 `ROOT_DIR_CORE/include/KtCore`。平台库由 CMake 按系统输出到
`ROOT_DIR/kt/core`、`ROOT_DIR/kt/macos/core` 或 `ROOT_DIR/kt/linux/core`，
CMake package 输出到对应平台目录下的 `lib/cmake/KtCore`。
