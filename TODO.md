# Windows 验证 TODO

## 1. Windows 编译验证

- [ ] 确认已安装 CMake 3.25 或更高版本。
- [ ] 确认 `ROOT_DIR`、`ROOT_DIR_CORE` 和 `ROOT_DIR_INCLUDE` 环境变量配置正确。
- [ ] 执行 `KtCore/rebuild.ps1`，确认先清理 build 目录、导出头文件，再打开 Debug / Release 构建窗口。
- [ ] 确认公共头文件输出到 `%ROOT_DIR_INCLUDE%\KtCore`。
- [ ] 确认 Debug DLL 和 `.lib` 输出到 `%ROOT_DIR_CORE%\debug` 及对应 lib 目录。
- [ ] 确认 Release DLL 和 `.lib` 输出到 `%ROOT_DIR_CORE%\bin` 及对应 lib 目录。
- [ ] 确认 `KtCore_EXPORTS` 生效，DLL 导出符号正确。
- [ ] 启用 `KTCORE_BUILD_TESTS`，确认 `test_KtString` 可以链接同一构建中的 `KtCore` target。

## 2. CAA 编译适配

- [ ] CAA 工程使用 `<KtCore/...>` 头文件时，确认解析到 `%ROOT_DIR_INCLUDE%\KtCore`。
- [ ] CAA DLL 链接本地生成的 `KtCore.lib`，不使用仓库内 `find_package(KtCore)`。
- [ ] 确认 CAA DLL 运行时可以找到对应的 `KtCore.dll`。
- [ ] 确认 Debug CAA 工程链接 Debug 版本，Release CAA 工程链接 Release 版本。
- [ ] 编译依赖 KtCore 的 CAA 模块，确认没有头文件版本冲突。
- [ ] 确认 CAA 原有编译脚本与 `ROOT_DIR_CORE`、`ROOT_DIR_INCLUDE` 规则兼容。
- [ ] 确认 CAA 工程不依赖旧的平铺头文件目录或 `export.bat` 的旧路径。
