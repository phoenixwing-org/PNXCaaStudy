/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisCore.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 */

// ApplicationFrame Framework
#include "CATFrmEditor.h" // needed to retrieve the editor and then to highight objects

// ObjectModelerBase Framework
#include "CATIContainer.h" // needed to create a GS (Geometrical Set)

// ObjectSpecsModeler Framework
#include "CATICkeParm.h"
#include "CATIDescendants.h" // needed to aggregate the newly created Line Create By GSD
#include "CATIParmPublisher.h"
#include "CATIPrdProperties.h"
#include "CATIProduct.h"
#include "CATISpecObject.h" // needed to manage feature

// MechanicalModeler Framework
#include "CATIBasicTool.h" // To retrieve the current tool
#include "CATIGSMTool.h"   // GSMTool and HybridBody features

// MecModInterfaces Framework
#include "CATIPrtPart.h" // needed to look for a GSM tool

// Visualization Framework
#include "CATHSO.h"            // needed to highlight objects
#include "CATIVisProperties.h" // needed to change Line Create By GSD's graphical appearance
#include "iostream.h"          //need for CAA iostream.not c++

// System framework
#include "CATBoolean.h"
#include "CATGetEnvValue.h" // To define the type of development
#include "CATLib.h"
#include "CATMathTransformation.h"

// KTC Core Framework

// local Framework
#include "PNXBomAnalysisCore.h"

#include <map>
#include <time.h>

// Error title
#define KTC_DEBUG_COUT

//-----------------------------------------------------------------------------
PNXBomAnalysisCore::PNXBomAnalysisCore() {
}
//-----------------------------------------------------------------------------
PNXBomAnalysisCore::~PNXBomAnalysisCore() {
}
//-----------------------------------------------------------------------------
HRESULT PNXBomAnalysisCore::pretreat() {
    // cout << "PNXBomAnalysisCore::pretreat" << endl;
    if (NULL == parameter) return E_INVALIDARG; // param check

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT PNXBomAnalysisCore::calculate() {
    if (NULL == parameter) return E_INVALIDARG; // param check
    if (NULL == parameter->productItems) {
        cout << "- [error] parameter->productItems is NULL!" << endl;
        return E_INVALIDARG; // param check
    }

    // clear
    parameter->productItems->clear(); // clear list
    parameter->FirstPartNumber = "";  // TODO delete

    int count = bomAnalysis(parameter->FirstProduct, "");
    cout << "- total pruduct count = " << count << endl;

    return S_OK;
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCore::bomAnalysis(CATISpecObject_var      currentPrd,
                                    const CATUnicodeString& parentPartNumber) {
    if (!currentPrd) return 0;
    if (NULL == parameter->productItems) return 0;

    // cout << "### calculate Bom" << endl;
    // first product item
    PNXBomItem item;
    item.ParentPartNumber = parentPartNumber;

    // get properties
    int code = checkoutProperties(currentPrd, item);
    if (code) { // error
        cout << "- [error] " << (code = 1005) << ": can not convert to CATIAlias_var." << endl;
        return 0;
    }
    int count = 0;
    parameter->productItems->push_back(item); // add to vector
    count++;

    // 转换第一个产品
    CATIProduct_var firstProduct = currentPrd;         // 获取产品
    if (NULL_var == firstProduct) return E_INVALIDARG; // 检查参考产品是否有效

    CATListValCATBaseUnknown_var* plistOfChildren = firstProduct->GetChildren(); // 获取子产品列表
    if (plistOfChildren == NULL || plistOfChildren->Size() == 0) { // 检查子产品列表是否有效
        cout << "- [error] sub items count = 0" << endl;           // 输出错误信息
        return S_OK;
    }
    CATUnicodeString lastPartNum("");   // 上一个零件编号
    int              lastPartCount = 1; // 上一个零件计数
    int              rowIndex      = 0; // 行索引

    std::map<CATUnicodeString, int> productMap;

    // 遍历子产品列表
    for (int iProd = 1; iProd <= plistOfChildren->Size(); iProd++) {
        // 获取当前产品
        CATISpecObject_var spCurrentPrd = (*plistOfChildren)[ iProd ];
        if (spCurrentPrd == NULL_var) { // 检查当前产品是否有效
            continue;
        }

        // 递归调用
        count += bomAnalysis(spCurrentPrd, item.PartNumber);
    }
    return count;
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCore::checkoutProperties(CATISpecObject_var productObject, PNXBomItem& item) {
    int code = 0;
    if (productObject == NULL_var) { // error
        cout << "    - [error] " << (code = 1009) << ": input productObject is NULL.";
        return code;
    }

    // 获取当前产品
    CATIProduct_var currentPrd;

    // 查询产品接口
    HRESULT rc = productObject->QueryInterface(IID_CATIProduct, (void**)&currentPrd);
    if (FAILED(rc) || currentPrd == NULL_var) { // error
        cout << "    - [error] " << (code = 1001) << ": can not convert to CATIProduct_var.";
        return code;
    }

    // 获取子产品的参考产品
    CATIProduct_var currentRef = currentPrd->GetReferenceProduct();
    if (currentRef == NULL_var) { // error
        cout << "    - [error] " << (code = 1002) << ": can not GetReferenceProduct().";
        return code;
    }

    // 获取当前产品的别名接口
    CATIAlias_var aliasObj = currentRef;
    if (!aliasObj) { // error
        cout << "- [error] " << (code = 1003) << ": can not convert to CATIAlias_var." << endl;
        return code;
    }

    item.ProductAlias = aliasObj->GetAlias(); // get productAlias
    // cout << "- ProductAlias : " << item.ProductAlias << endl;

    // 获取产品属性接口
    CATIPrdProperties_var spPrdProperties = currentRef;
    if (NULL_var == spPrdProperties) {
        cout << "    - [error] " << (code = 1003) << " : can not get properties!" << endl;
        return code;
    }

    // get main properties
    spPrdProperties->GetPartNumber(item.PartNumber); // 零件号
    spPrdProperties->GetRevision(item.Revision);     // 版本

    // 来源
    CatProductSource refSource;
    spPrdProperties->GetSource(refSource); // 来源

    // catProductSourceUnknown, catProductMade, catProductBought
    switch (refSource) {
    case catProductMade:
        item.Source = "Made";
        break;
    case catProductBought:
        item.Source = "Bought";
        break;
    default: // catProductSourceUnknown
        item.Source = "Unknown";
        break;
    }
    spPrdProperties->GetDefinition(item.Definition);           // 定义
    spPrdProperties->GetNomenclature(item.Nomenclature);       // 获取零件名称
    spPrdProperties->GetDescriptionRef(item.Nomenclature);     // 获取零件名称
    spPrdProperties->GetInstanceName(item.InstanceName);       // 实例名
    spPrdProperties->GetDescriptionInst(item.DescriptionInst); // 实例描述

    CATBoolean activateBOM;
    spPrdProperties->GetActivateBOM(activateBOM);
    item.ActivateBOM = activateBOM != CATFalse ? "1" : "0";

    int index = 0;

    // 声明参数发布者指针
    CATIParmPublisher* piParmPublisher = NULL;
    spPrdProperties->GetUserProperties(piParmPublisher, true); // 获取用户属性
    if (NULL == piParmPublisher) {
        cout << "    - [error] " << (code = 1004) << " : can not get CATIParmPublisher!" << endl;
        return code;
    }

    // 获取所有知识工程参数
    CATLISTV(CATISpecObject_var) listParamObj = NULL; // 声明参数对象列表
    piParmPublisher->GetAllChildren("CATICkeParm", listParamObj);
    piParmPublisher->Release(); // 释放参数发布者
    piParmPublisher = NULL;     // 将指针设置为空

    if (listParamObj.Size() == 0) return 0; // ok

    // cout << "    - listParamObj.Size() :" << listParamObj.Size() << endl;

    // protertyName
    static const CATUnicodeString propMaterial("Material");                 // 材料
    static const CATUnicodeString propSurfaceTreatment("Surfacetreatment"); // 表面处理
    static const CATUnicodeString propWeight("Weight");                     // 重量

    for (int iProperty = 1; iProperty <= listParamObj.Size(); iProperty++) { // 遍历参数对象列表

        // cout << " -  " << iProperty << endl;
        CATISpecObject_var spParamObject = listParamObj[ iProperty ]; // 获取参数对象
        if (NULL_var == spParamObject) {
            // cout << "    | " << iProperty << " |   |   |" << endl;
            continue; // 跳过无效参数对象
        }
        CATUnicodeString strAttrName = spParamObject->GetDisplayName(); // 获取属性名称

        CATUnicodeString strAttrValue(""); // 声明属性值变量

        CATICkeParm_var spCkeParm = spParamObject; // 获取知识工程参数接口
        if (NULL_var != spCkeParm) {               // 检查知识工程参数接口是否有效
            CATICkeInst_var spCkeInst = spCkeParm->Value(); // 获取参数实例
            if (NULL_var != spCkeInst) {                    // 检查参数实例是否有效
                strAttrValue = spCkeInst->AsString();       // 获取参数值字符串
            }
        }

        // cout << "    | " << (++index) << " | " << strAttrName << " | " << strAttrValue << " |"
        //      << endl;

        // 变量类型 修改为你的类型
        // if (strAttrName == propMaterial) // 如果是材料属性
        //     item.material = strAttrValue;
        // else if (strAttrName == propSurfaceTreatment) // 如果是表面处理属性
        //     item.surfaceTreatment = strAttrValue;
        // else if (strAttrName == propWeight) // 如果是重量属性
        //     item.weight = strAttrValue;
    }

    return 0; // ok
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCore::dumpJsonL() {
    if (!parameter || !(parameter->productItems)) return 0;
    int                      code         = 0;
    std::vector<PNXBomItem>& productItems = *(parameter->productItems);
    if (productItems.size() == 0) return 0;

    cout << "### Bom in JsonL format" << endl;

    cout << "```json" << endl;
    for (int i = 0; i < productItems.size(); i++) { // 遍历参数对象列表
        dumpJson(productItems[ i ]);
    }
    cout << "```" << endl;

    return 0; // ok
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCore::dumpJson(const PNXBomItem& item) {
    cout << PNXBomAnalysisParam::convertJson(item) << endl;
    return 0;
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCore::dumpMarkdown() {
    if (!parameter || !(parameter->productItems)) return 0;
    int                      code         = 0;
    std::vector<PNXBomItem>& productItems = *(parameter->productItems);
    if (productItems.size() == 0) return 0;

    cout << "### Bom in markdown format" << endl;
    for (int i = 0; i < productItems.size(); i++) { // 遍历参数对象列表
        dumpMarkdown(productItems[ i ]);
    }

    return 0; // ok
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCore::dumpMarkdown(const PNXBomItem& item) {
    cout << "- ProductAlias : " << item.ProductAlias << endl;

    int index = 0;

    cout << endl;
    // clang-format off
    cout << "    |    index | property         | value          | " << endl;
    cout << "    | -------- | ---------------- | -------------- | " << endl;
    cout << "    | " << (++index) << " | PartNumber  | " << item.PartNumber << " |" << endl;
    cout << "    | " << (++index) << " | Revision  | " << item.Revision << " |" << endl;
    cout << "    | " << (++index) << " | Source  | " << item.Source << " |" << endl;
    cout << "    | " << (++index) << " | Definition  | " << item.Definition << " |" << endl;
    cout << "    | " << (++index) << " | Nomenclature  | " << item.Nomenclature << " |" << endl;
    cout << "    | " << (++index) << " | DscriptionRef  | " << item.DscriptionRef << " |" << endl;
    cout << "    | " << (++index) << " | InstanceName  | " << item.InstanceName << " |" << endl;
    cout << "    | " << (++index) << " | DescriptionInst | " << item.DescriptionInst << " |"         << endl;
    cout << "    | " << (++index) << " | ActivateBOM  | " << item.ActivateBOM << " |" << endl;
    cout << "    | " << (++index) << " | ProductAlias  | " << item.ProductAlias << " |" << endl;
    cout << "    | " << (++index) << " | ParentPartNumber | " << item.ParentPartNumber << " |" << endl;

    // clang-format on

    return 0; // ok
}