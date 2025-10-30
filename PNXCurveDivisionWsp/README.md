# Bom分析

## 编译运行顺序
- 编译 KTCAutoCodeWsp\mk.bat
- 编译 PNXCurveDivisionWsp\mk.bat
- 运行 PNXCurveDivisionWsp\run.bat

## 添加工具条到Product

以 PNXCurveDivisionAdn.m为例
### 1. 字典文件配置

PNXCurveDivisionTlb.dico ： Addin
```
PNXCurveDivisionAddin    CATIPrtWksAddin                 libPNXCurveDivisionAdn
PNXCurveDivisionAddin	   CATIPRDWorkshopAddin	           libPNXCurveDivisionAdn
```

### 2. IdentityCard.h 配置
```cpp
// DO NOT EDIT :: THE CAA2 WIZARDS WILL ADD CODE HERE
AddPrereqComponent("System", Protected);
AddPrereqComponent("ApplicationFrame", Protected);
AddPrereqComponent("MechanicalModelerUI", Public);
AddPrereqComponent("ProductStructureUI", Protected); // 总成
AddPrereqComponent("GSMInterfaces", Protected);      // GSM
// END WIZARD EDITION ZONE
```

### 3. Imakefile.mk 配置
```
LINK_WITH = $(WIZARD_LINK_MODULES) \
             CATPrsWksPRDWorkshop \
             CATGitInterfaces
```

### 4. PNXCurveDivisionAdn.cpp 实现
```cpp
MacDeclareHeader(PNXCurveDivisionAdnHeader);

CATImplementClass(PNXCurveDivisionAdn, Implementation, CATBaseUnknown, CATnull);

// Link the implementation to its interface
// ---------------------------------------

// TIE or TIEchain definitions
#include "TIE_CATIPRDWorkshopAddin.h"
TIE_CATIPRDWorkshopAddin(PNXCurveDivisionAdn);

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXCurveDivisionAdn);

```

## 关键配置要点

### 必需的依赖模块：
- **GSMInterfaces** - 在IdentityCard中添加
- **CATGitInterfaces** - 在Imakefile.mk中添加

### CAA Help使用指导：
1. 启动Help Viewer：`C:\DS\RADE19\intel_a\code\bin\CNextHelpViewer.exe`
2. 设置workspace为：`C:\DS\B19\CAADoc`
3. 搜索 `CATIPRDWorkshopAddin` 获取详细API文档

### 接口文件位置：

mk错误，找不到接口
按下面的方法解决

- 主要接口文件：`CATIShapeDesignWorkshopAddin.h`
- 必需模块：`CATGitInterfaces`

这样配置后，您的CATIA插件就可以在总成(Product)工作台和GSD(创成式曲面设计)工作台中正常工作了。

## 编译和调试自动化
### 使用launch.json和tasks.json
正确的使用流程：
- 先启动 CATIA： 按 Ctrl+Shift+P （或F1）→ "Tasks: Run Task" → 选择 "Run CNext.exe"
- 等待 CATIA 完全启动
- 附加调试器： 按 F5 → 在进程列表中选择 CNEXT.exe
- 这样就可以正常调试了。

#### launch.json 配置调试CAA

参考： [./.vscode/launch.json](./.vscode/launch.json)

要点：
- symbolSearchPath：设置pdb的位置，可以输入多个目录，用分号分割
- processId：配置为选取进程
- request 设置为attach，附加到进程

#### tasks.json配置CAA编译任务
参考： [./.vscode/tasks.json](./.vscode/tasks.json)
- 启动任务方法：
    - 按F1 (或Ctrl+Shift+P )
    - 输入tasks:,在下拉列表里面选 `tasks: Run Task
    - 在新的选项里面选
        - `mkmk workspace`：可以编译当前目录
        - `Run CNext.exe` ：可以启动Catia
    - 在选项里面选`不再提示` 大概是第三个选项，这样以后就不需要提示了。
- 设置快捷键
    - 找到`tasks: Run Task`, 右面的齿轮设置
    - 比如设置F6
