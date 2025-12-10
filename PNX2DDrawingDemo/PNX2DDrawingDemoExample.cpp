/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @file        PNX2DDrawingDemoExample.cpp
 * @version     V1.0
 * @brief       2D图纸元素属性设置使用示例
 * @details     演示如何使用PNX2DDrawingDemo类设置2D图纸元素的属性
 * @date        2025-01-XX
 */

// Local Framework
#include "PNX2DDrawingDemo.h"

// DrawingInterfaces Framework
#include "CATI2DAnnotation.h"
#include "CATI2DLine.h"
#include "CATI2DArrow.h"
#include "CATIDrawingView.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// System Framework
#include "iostream.h"

//-----------------------------------------------------------------------------
// 示例1: 设置2D直线的thickness
//-----------------------------------------------------------------------------
void Example_SetLineThickness(CATI2DLine* ip2DLine) {
    cout << "=== 示例1: 设置2D直线的thickness ===" << endl;

    if (NULL == ip2DLine) {
        cout << "[ERROR] ip2DLine is NULL" << endl;
        return;
    }

    // 设置线宽为4
    HRESULT hr = PNX2DDrawingDemo::SetLineThickness(ip2DLine, 4);
    if (SUCCEEDED(hr)) {
        cout << "[SUCCESS] 2D直线线宽设置成功" << endl;
    } else {
        cout << "[FAILED] 2D直线线宽设置失败" << endl;
    }
}

//-----------------------------------------------------------------------------
// 示例2: 设置2D箭头的thickness
//-----------------------------------------------------------------------------
void Example_SetArrowThickness(CATI2DArrow* ip2DArrow) {
    cout << "=== 示例2: 设置2D箭头的thickness ===" << endl;

    if (NULL == ip2DArrow) {
        cout << "[ERROR] ip2DArrow is NULL" << endl;
        return;
    }

    // 设置线宽为5
    HRESULT hr = PNX2DDrawingDemo::SetArrowThickness(ip2DArrow, 5);
    if (SUCCEEDED(hr)) {
        cout << "[SUCCESS] 2D箭头线宽设置成功" << endl;
    } else {
        cout << "[FAILED] 2D箭头线宽设置失败" << endl;
    }
}

//-----------------------------------------------------------------------------
// 示例3: 设置2D元素的完整属性（thickness + 颜色）
//-----------------------------------------------------------------------------
void Example_Set2DElementFullProperties(CATI2DAnnotation* ip2DAnnotation) {
    cout << "=== 示例3: 设置2D元素的完整属性 ===" << endl;

    if (NULL == ip2DAnnotation) {
        cout << "[ERROR] ip2DAnnotation is NULL" << endl;
        return;
    }

    // 设置线宽为4，颜色为红色(255, 0, 0)
    HRESULT hr = PNX2DDrawingDemo::Set2DElementProperties(ip2DAnnotation, 4, 255, 0, 0);
    if (SUCCEEDED(hr)) {
        cout << "[SUCCESS] 2D元素属性设置成功（线宽=4，颜色=红色）" << endl;
    } else {
        cout << "[FAILED] 2D元素属性设置失败" << endl;
    }
}

//-----------------------------------------------------------------------------
// 示例4: 从CATISpecObject设置属性（通用方法）
//-----------------------------------------------------------------------------
void Example_SetFromSpecObject(CATISpecObject* ipSpecObject) {
    cout << "=== 示例4: 从CATISpecObject设置属性 ===" << endl;

    if (NULL == ipSpecObject) {
        cout << "[ERROR] ipSpecObject is NULL" << endl;
        return;
    }

    // 设置线宽为3
    HRESULT hr = PNX2DDrawingDemo::Set2DElementThicknessFromSpec(ipSpecObject, 3);
    if (SUCCEEDED(hr)) {
        cout << "[SUCCESS] 从SpecObject设置属性成功" << endl;
    } else {
        cout << "[FAILED] 从SpecObject设置属性失败" << endl;
    }
}

//-----------------------------------------------------------------------------
// 示例5: 自动识别2D元素类型并设置属性
//-----------------------------------------------------------------------------
void Example_AutoDetectAndSetProperties(CATISpecObject* ip2DElement) {
    cout << "=== 示例5: 自动识别2D元素类型并设置属性 ===" << endl;

    if (NULL == ip2DElement) {
        cout << "[ERROR] ip2DElement is NULL" << endl;
        return;
    }

    HRESULT hr = E_FAIL;

    // 尝试作为2D直线处理
    CATI2DLine* pi2DLine = NULL;
    hr = ip2DElement->QueryInterface(IID_CATI2DLine, (void**)&pi2DLine);
    if (SUCCEEDED(hr) && pi2DLine != NULL) {
        cout << "[INFO] 检测到2D直线，设置线宽为4" << endl;
        PNX2DDrawingDemo::SetLineThickness(pi2DLine, 4);
        pi2DLine->Release();
        pi2DLine = NULL;
        return;
    }

    // 尝试作为2D箭头处理
    CATI2DArrow* pi2DArrow = NULL;
    hr = ip2DElement->QueryInterface(IID_CATI2DArrow, (void**)&pi2DArrow);
    if (SUCCEEDED(hr) && pi2DArrow != NULL) {
        cout << "[INFO] 检测到2D箭头，设置线宽为5" << endl;
        PNX2DDrawingDemo::SetArrowThickness(pi2DArrow, 5);
        pi2DArrow->Release();
        pi2DArrow = NULL;
        return;
    }

    // 尝试作为通用2D注释元素处理
    CATI2DAnnotation* pi2DAnnotation = NULL;
    hr = ip2DElement->QueryInterface(IID_CATI2DAnnotation, (void**)&pi2DAnnotation);
    if (SUCCEEDED(hr) && pi2DAnnotation != NULL) {
        cout << "[INFO] 检测到2D注释元素，设置线宽为3，颜色为蓝色" << endl;
        PNX2DDrawingDemo::Set2DElementProperties(pi2DAnnotation, 3, 0, 0, 255);
        pi2DAnnotation->Release();
        pi2DAnnotation = NULL;
        return;
    }

    // 最后尝试直接使用SpecObject
    cout << "[INFO] 使用通用方法设置属性" << endl;
    PNX2DDrawingDemo::Set2DElementThicknessFromSpec(ip2DElement, 2);
}

//-----------------------------------------------------------------------------
// 示例6: 批量设置多个2D元素的属性
//-----------------------------------------------------------------------------
void Example_BatchSetProperties(CATLISTV(CATISpecObject_var) iList2DElements) {
    cout << "=== 示例6: 批量设置多个2D元素的属性 ===" << endl;

    int count = iList2DElements.Size();
    cout << "[INFO] 共有 " << count << " 个2D元素需要设置属性" << endl;

    for (int i = 1; i <= count; i++) {
        CATISpecObject_var element = iList2DElements[i];
        if (NULL_var != element) {
            cout << "[INFO] 处理第 " << i << " 个元素" << endl;
            
            // 根据索引设置不同的线宽
            int thickness = 2 + (i % 3); // 线宽在2-4之间变化
            
            HRESULT hr = PNX2DDrawingDemo::Set2DElementThicknessFromSpec(element, thickness);
            if (SUCCEEDED(hr)) {
                cout << "[SUCCESS] 元素 " << i << " 设置成功（线宽=" << thickness << "）" << endl;
            } else {
                cout << "[FAILED] 元素 " << i << " 设置失败" << endl;
            }
        }
    }

    cout << "[INFO] 批量设置完成" << endl;
}

//-----------------------------------------------------------------------------
// 主函数示例（仅供参考，实际使用时需要根据具体情况调用）
//-----------------------------------------------------------------------------
/*
void MainExample() {
    // 注意：以下代码需要在实际的2D图纸环境中使用
    // 这里只是展示调用方式

    // 假设你已经有了2D图纸视图和元素
    CATIDrawingView* pDrawingView = ...;
    CATISpecObject* p2DElement = ...;

    // 示例1: 设置直线属性
    CATI2DLine* pLine = ...;
    Example_SetLineThickness(pLine);

    // 示例2: 设置箭头属性
    CATI2DArrow* pArrow = ...;
    Example_SetArrowThickness(pArrow);

    // 示例3: 设置完整属性
    CATI2DAnnotation* pAnnotation = ...;
    Example_Set2DElementFullProperties(pAnnotation);

    // 示例4: 从SpecObject设置
    Example_SetFromSpecObject(p2DElement);

    // 示例5: 自动识别并设置
    Example_AutoDetectAndSetProperties(p2DElement);

    // 示例6: 批量设置
    CATLISTV(CATISpecObject_var) listElements;
    // ... 填充列表 ...
    Example_BatchSetProperties(listElements);
}
*/

