# Bom分析

## 编译运行顺序
- 编译 KTCAutoCodeWsp\mk.bat
- 编译 PNXBomAnalysisWsp\mk.bat
- 运行 PNXBomAnalysisWsp\run.bat

## 添加工具条到Product

以 PNXBomAnalysisAdn.m为例
### 1. 字典文件配置

PNXBomAnalysisTlb.dico ： Addin
```
PNXBomAnalysisAddin    CATIPrtWksAddin                 libPNXBomAnalysisAdn
PNXBomAnalysisAddin	   CATIPRDWorkshopAddin	           libPNXBomAnalysisAdn
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

### 4. PNXBomAnalysisAdn.cpp 实现
```cpp
MacDeclareHeader(PNXBomAnalysisAdnHeader);

CATImplementClass(PNXBomAnalysisAdn, Implementation, CATBaseUnknown, CATnull);

// Link the implementation to its interface
// ---------------------------------------

// TIE or TIEchain definitions
#include "TIE_CATIPRDWorkshopAddin.h"
TIE_CATIPRDWorkshopAddin(PNXBomAnalysisAdn);

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXBomAnalysisAdn);

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
