# CAA学习
 
[PNXBomAnalysisWsp\README.md](PNXBomAnalysisWsp\README.md)

## PNXCurveDivisionWsp
曲线等分的示例


## 管理员身份永久更改执行PowerShell策略
- 步骤1：以管理员身份运行 PowerShell
    - 在开始菜单搜索 "PowerShell"
    - 右键点击 "Windows PowerShell"
    - 选择 "以管理员身份运行"

- 步骤2：设置执行策略

```powershell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope LocalMachine
```