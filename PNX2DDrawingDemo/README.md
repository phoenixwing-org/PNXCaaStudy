# 2D图纸元素属性设置演示

## 概述

本演示类展示了如何在CAA 2D图纸（Drawing）中设置箭头、直线等元素的thickness（粗细）等属性。

## 主要功能

### 1. 设置2D直线的thickness属性

```cpp
// 假设你已经有一个2D直线的指针
CATI2DLine* p2DLine = ...;

// 设置线宽为4
HRESULT hr = PNX2DDrawingDemo::SetLineThickness(p2DLine, 4);
```

### 2. 设置2D箭头的thickness属性

```cpp
// 假设你已经有一个2D箭头的指针
CATI2DArrow* p2DArrow = ...;

// 设置线宽为5
HRESULT hr = PNX2DDrawingDemo::SetArrowThickness(p2DArrow, 5);
```

### 3. 设置2D注释元素的thickness属性（通用方法）

```cpp
// 假设你已经有一个2D注释元素的指针
CATI2DAnnotation* p2DAnnotation = ...;

// 设置线宽为3
HRESULT hr = PNX2DDrawingDemo::SetAnnotationThickness(p2DAnnotation, 3);
```

### 4. 设置完整的属性（thickness + 颜色）

```cpp
// 设置线宽和颜色
HRESULT hr = PNX2DDrawingDemo::Set2DElementProperties(
    p2DAnnotation,  // 2D元素指针
    4,              // thickness（线宽）
    255,            // 红色分量 (0-255)
    0,              // 绿色分量 (0-255)
    0               // 蓝色分量 (0-255)
);
```

### 5. 从CATISpecObject设置属性

```cpp
// 从规格对象设置属性（适用于所有2D元素）
CATISpecObject* pSpecObject = ...;

HRESULT hr = PNX2DDrawingDemo::Set2DElementThicknessFromSpec(pSpecObject, 4);
```

## 核心接口说明

### CATIVisProperties
用于设置图形元素的视觉属性，包括：
- 线宽（thickness）
- 颜色（color）
- 线型（line type）
- 其他视觉属性

### CATVisPropertiesValues
属性值容器类，用于设置具体的属性值：
- `SetWidth(int iWidth)`: 设置线宽
- `SetColor(int iRed, int iGreen, int iBlue)`: 设置颜色

### SetPropertiesAtt() 方法参数说明

```cpp
piVisProperties->SetPropertiesAtt(
    attribut,              // CATVisPropertiesValues对象，包含要设置的属性值
    CATVPAllPropertyType, // 属性类型：应用所有属性
    CATVPLine            // 图形类型：应用到线条类型（直线、箭头等）
);
```

## 使用示例

### 完整示例：在2D图纸视图中设置元素属性

```cpp
#include "PNX2DDrawingDemo.h"
#include "CATI2DAnnotation.h"
#include "CATI2DLine.h"
#include "CATI2DArrow.h"
#include "CATISpecObject.h"

// 假设你有一个2D图纸视图中的元素
void SetDrawingElementProperties(CATISpecObject* ip2DElement) {
    if (NULL == ip2DElement) return;

    // 方法1: 尝试作为2D直线处理
    CATI2DLine* pi2DLine = NULL;
    HRESULT rc = ip2DElement->QueryInterface(IID_CATI2DLine, (void**)&pi2DLine);
    if (SUCCEEDED(rc) && pi2DLine != NULL) {
        PNX2DDrawingDemo::SetLineThickness(pi2DLine, 4);
        pi2DLine->Release();
        return;
    }

    // 方法2: 尝试作为2D箭头处理
    CATI2DArrow* pi2DArrow = NULL;
    rc = ip2DElement->QueryInterface(IID_CATI2DArrow, (void**)&pi2DArrow);
    if (SUCCEEDED(rc) && pi2DArrow != NULL) {
        PNX2DDrawingDemo::SetArrowThickness(pi2DArrow, 5);
        pi2DArrow->Release();
        return;
    }

    // 方法3: 作为通用2D注释元素处理
    CATI2DAnnotation* pi2DAnnotation = NULL;
    rc = ip2DElement->QueryInterface(IID_CATI2DAnnotation, (void**)&pi2DAnnotation);
    if (SUCCEEDED(rc) && pi2DAnnotation != NULL) {
        // 设置线宽和颜色
        PNX2DDrawingDemo::Set2DElementProperties(pi2DAnnotation, 4, 255, 0, 0);
        pi2DAnnotation->Release();
        return;
    }

    // 方法4: 直接使用规格对象
    PNX2DDrawingDemo::Set2DElementThicknessFromSpec(ip2DElement, 4);
}
```

## 关键要点

1. **接口获取顺序**：
   - 首先尝试获取特定接口（CATI2DLine, CATI2DArrow）
   - 如果失败，使用通用接口（CATI2DAnnotation）
   - 最后使用CATISpecObject接口

2. **属性设置**：
   - 使用`CATIVisProperties`接口设置视觉属性
   - 使用`CATVisPropertiesValues`对象存储属性值
   - 通过`SetPropertiesAtt()`方法应用属性

3. **thickness值范围**：
   - 通常为1-10像素
   - 值越大，线条越粗

4. **内存管理**：
   - 记得释放所有通过QueryInterface获取的接口指针
   - 使用Release()方法释放接口

## 需要的头文件

```cpp
// DrawingInterfaces Framework
#include "CATI2DAnnotation.h"
#include "CATI2DLine.h"
#include "CATI2DArrow.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// Visualization Framework
#include "CATIVisProperties.h"
#include "CATVisPropertiesValues.h"
```

## 注意事项

1. 确保在调用这些方法之前，2D元素已经创建并添加到图纸视图中
2. 某些属性可能需要图纸视图更新后才能看到效果
3. 不同的CATIA版本可能对属性值的支持有所不同
4. 建议在使用前检查HRESULT返回值，确保操作成功

