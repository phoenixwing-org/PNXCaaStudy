/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoCatalogParam.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// CAT
#include "CATISpecAttribute.h"
#include "iostream.h"

// auto code
#include "KTCAutoCatalogParam.h"
#include "KTCAutoDefine.h"

//-----------------------------------------------------------------------------
KTCAutoCatalogParam::KTCAutoCatalogParam()
    : name()
    , kind(tk_null)
    , inOut(sp_IN)
    , isList(0) {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoCatalogParam::~KTCAutoCatalogParam() {
}
//-----------------------------------------------------------------------------
KTCAutoCatalogParam::KTCAutoCatalogParam(const KTCAutoCatalogParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoCatalogParam& KTCAutoCatalogParam::operator=(const KTCAutoCatalogParam& iOriginal) {
    name   = iOriginal.name;
    kind   = iOriginal.kind;
    inOut  = iOriginal.inOut;
    isList = iOriginal.isList;
    return *this;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoCatalogParam::add_Attributes(CATISpecObject*                   startUp,
                                            std::vector<KTCAutoCatalogParam>& itemList) {
    if (!startUp) return E_INVALIDARG;
    if (itemList.size() == 0) return S_OK;
    HRESULT hr = S_OK;

    // 循环添加变量
    KTCAutoCatalogParam* item = &itemList.front(); // 第一个
    for (size_t i = 0; i < itemList.size(); i++, item++) {
        CATISpecAttribute* specAttribute = startUp->GetAttribute(item->name);

        // =======存在，提示错误=======
        if (specAttribute) {
            cout << " - Attribut `" << item->name << "`"
                 << " is already exist.CANNOT Set or Modify!" << endl;
            KTCRelease(specAttribute); // 手动释放
            continue;
        }

        // =======添加模式=======
        if (item->isList) // list
            specAttribute = startUp->AddAttribute(item->name, tk_list(item->kind), item->inOut);

        else // sigle
            specAttribute = startUp->AddAttribute(item->name, item->kind, item->inOut);

        // 输出信息
        if (specAttribute) {
            cout << " - Attribut `" << item->name << "`"
                 << " has been successfully added." << endl;
        }
        else {
            cout << " - [ERROR] Attribut `" << item->name << "`"
                 << " adds Failed." << endl;
            hr = E_FAIL;
        }
        KTCRelease(specAttribute); // 手动释放
    }

    return hr;
}
//-----------------------------------------------------------------------------
void KTCAutoCatalogParam::SetTKListValue(const CATUnicodeString& iName, TCKind iKind,
                                         CATAttrInOut iInOut) {
    name   = iName;
    kind   = iKind;
    inOut  = iInOut;
    isList = 1;
}
//-----------------------------------------------------------------------------
void KTCAutoCatalogParam::SetValue(const CATUnicodeString& iName, TCKind iKind,
                                   CATAttrInOut iInOut) {
    name   = iName;
    kind   = iKind;
    inOut  = iInOut;
    isList = 0;
}
