# CAA学习
 
[PNXBomAnalysisWsp\README.md](PNXBomAnalysisWsp\README.md)

## PNXCurveDivisionWsp
曲线等分的示例

## 环境变量设定

- 运行 `tools\baseEnv.bat` 设定需要的环境变量
    - 环境变量 `CAA_MK_VERSION`  设定为需要的版本，比如19
    - ROOT_DIR 自定义库根目录
    - ROOT_DIR_3rdParty 三方库根目录
    - ROOT_DIR_CORE core的目录


## 管理员身份永久更改执行PowerShell策略
- 步骤1：以管理员身份运行 PowerShell
    - 在开始菜单搜索 "PowerShell"
    - 右键点击 "Windows PowerShell"
    - 选择 "以管理员身份运行"

- 步骤2：设置执行策略

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine
```

## 关联文档
[parameter参数定义文件说明](parameter.md)