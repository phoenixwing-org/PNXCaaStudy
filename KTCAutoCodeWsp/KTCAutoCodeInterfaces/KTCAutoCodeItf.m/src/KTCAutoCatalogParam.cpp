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

#include "iostream.h"

// Local
#include "KTCAutoCatalogParam.h"

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
HRESULT KTCAutoCatalogParam::CatalogAddAttribute(CATISpecObject*                   startUp,
                                                 std::vector<KTCAutoCatalogParam>& itemList) {
    cout << "TODO " << __FUNCTION__ << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
void KTCAutoCatalogParam::SetTKListValue(const CATUnicodeString& iName, TCKind iKind,
                                         CATAttrInOut iInOut) {
    name   = iName;
    kind   = iKind;
    inOut  = inOut;
    isList = 1;
}
//-----------------------------------------------------------------------------
void KTCAutoCatalogParam::SetValue(const CATUnicodeString& iName, TCKind iKind,
                                   CATAttrInOut iInOut) {
    name   = iName;
    kind   = iKind;
    inOut  = inOut;
    isList = 0;
}
