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
    // cout << "PNXBomAnalysisCore::calculate" << endl;
    if (NULL == parameter) return E_INVALIDARG; // param check
    if (NULL == parameter->productItems) {
        cout << "- [error] parameter->productItems is NULL!" << endl;
        return E_INVALIDARG; // param check
    }

    if (!parameter->FirstProduct) {
        parameter->productItems->clear(); // clear list
        parameter->FirstPartNumber = "";  // clear partnumber
        return S_OK;
    }

    // TODO change to partnumber
    parameter->FirstPartNumber = parameter->FirstProduct->GetDisplayName();

    PNXBomItem firstItem;
    firstItem.partNumber       = parameter->FirstPartNumber;
    firstItem.parentPartNumber = "";

    // get properties
    int code = checkoutProperties(parameter->FirstProduct, firstItem);
    if (code) { // error
        cout << "- [error] " << (code = 1005) << ": can not convert to CATIAlias_var." << endl;
        return E_FAIL;
    }

    CATIProduct_var firstProduct = parameter->FirstProduct; // 获取参考产品

    // CATIProduct_var spRefParentPro = firstProduct->GetReferenceProduct(); // 获取参考产品
    CATIProduct_var spRefParentPro = firstProduct;

    if (NULL_var == spRefParentPro) return E_INVALIDARG; // 检查参考产品是否有效

    // CATIAlias_var aliasOnCurrentRootPrd = spRefParentPro; // 获取当前根产品的别名接口

    // CATUnicodeString strPathName = aliasOnCurrentRootPrd->GetAlias(); // 获取路径名称

    CATListValCATBaseUnknown_var* plistOfChildren = firstProduct->GetChildren(); // 获取子产品列表

    if (plistOfChildren == NULL || plistOfChildren->Size() == 0) { // 检查子产品列表是否有效
        cout << "- [error] sub items count = 0" << endl;           // 输出错误信息
        return S_OK;
    }
    CATUnicodeString lastPartNum("");   // 上一个零件编号
    int              lastPartCount = 1; // 上一个零件计数
    int              rowIndex      = 0; // 行索引

    std::map<CATUnicodeString, int> productMap;

    // 如果是零件编号属性

    for (int iProd = 1; iProd <= plistOfChildren->Size(); iProd++) { // 遍历子产品列表

        CATISpecObject_var spCurrentPrd = (*plistOfChildren)[ iProd ]; // 获取当前产品
        if (spCurrentPrd == NULL_var) { // 检查当前产品是否有效
            continue;
        }

        // get item
        PNXBomItem item;
        int        code = checkoutProperties(parameter->FirstProduct, item);
        if (code) { // error
            cout << "- [error] " << (code = 1007) << " : can not convert to CATIAlias_var." << endl;
            return E_FAIL;
        }

        parameter->productItems->push_back(item); // add to vector

        if (item.partNumber.GetLengthInChar() > 0) {
            // if (productMap.) }
        }
    }
    return S_OK;
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

    item.productAlias = aliasObj->GetAlias(); // get productAlias
    cout << "    - alias : " << item.productAlias << endl;

    // 获取产品属性接口
    CATIPrdProperties_var spPrdProperties = currentRef;
    if (NULL_var == spPrdProperties) {
        cout << "    - [error] " << (code = 1003) << " : can not get properties!" << endl;
        return code;
    }

    // get nomenclature
    spPrdProperties->GetNomenclature(item.nomenclature); // 获取零件名称
    spPrdProperties->GetInstanceName(item.productAlias);
    spPrdProperties->GetPartNumber(item.partNumber);
    spPrdProperties->GetRevision(item.revision);
    spPrdProperties->GetDefinition(item.definition);

    int index = 0;

    cout << endl;
    cout << "    |    index | property         | value          | " << endl;
    cout << "    | -------- | ---------------- | -------------- | " << endl;
    cout << "    | " << (index++) << " | nomenclature     | " << item.nomenclature << " |" << endl;
    cout << "    | " << (index++) << " | productAlias     | " << item.productAlias << " |" << endl;
    cout << "    | " << (index++) << " | partNumber     | " << item.partNumber << " |" << endl;
    cout << "    | " << (index++) << " | revision     | " << item.revision << " |" << endl;
    cout << "    | " << (index++) << " | definition     | " << item.definition << " |" << endl;

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

    cout << "    - listParamObj.Size() :" << listParamObj.Size() << endl;

    // protertyName
    static const CATUnicodeString propPartNumber("Part Number");            // 零件编号
    static const CATUnicodeString propMaterial("Material");                 // 材料
    static const CATUnicodeString propSurfaceTreatment("Surfacetreatment"); // 表面处理
    static const CATUnicodeString propWeight("Weight");                     // 重量

    for (int iProperty = 1; iProperty <= listParamObj.Size(); iProperty++) { // 遍历参数对象列表

        cout << " -  " << iProperty << endl;
        CATISpecObject_var spParamObject = listParamObj[ iProperty ]; // 获取参数对象
        if (NULL_var == spParamObject) {
            cout << "    | " << iProperty << " |   |   |" << endl;
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
        cout << "    | " << (index++) << " | " << strAttrName << " | " << strAttrValue << " |"
             << endl;

        // 变量类型
        if (strAttrName == propMaterial) // 如果是材料属性
            item.material = strAttrValue;
        else if (strAttrName == propSurfaceTreatment) // 如果是表面处理属性
            item.surfaceTreatment = strAttrValue;
        else if (strAttrName == propWeight) // 如果是重量属性
            item.weight = strAttrValue;
    }

    return 0; // ok
}
