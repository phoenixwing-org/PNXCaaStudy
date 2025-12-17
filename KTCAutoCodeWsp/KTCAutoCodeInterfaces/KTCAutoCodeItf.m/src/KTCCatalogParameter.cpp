/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCCatalogParameter.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

#include "iostream.h"

// Local
#include "KTCCatalogParameter.h"

//-----------------------------------------------------------------------------
KTCCatalogParameter::KTCCatalogParameter()
    : name()
    , kind(tk_null)
    , inOut(sp_IN)
    , isList(0) {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCCatalogParameter::~KTCCatalogParameter() {
}
//-----------------------------------------------------------------------------
KTCCatalogParameter::KTCCatalogParameter(const KTCCatalogParameter& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCCatalogParameter& KTCCatalogParameter::operator=(const KTCCatalogParameter& iOriginal) {
    name   = iOriginal.name;
    kind   = iOriginal.kind;
    inOut  = iOriginal.inOut;
    isList = iOriginal.isList;
    return *this;
}
//-----------------------------------------------------------------------------
HRESULT KTCCatalogParameter::CatalogAddAttribute(CATISpecObject*                   startUp,
                                                 std::vector<KTCCatalogParameter>& itemList) {

    cout << "TODO add code for KTCCatalogParameter::CatalogAddAttribute" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
void KTCCatalogParameter::SetTKListValue(const CATUnicodeString& iName, TCKind iKind,
                                         CATAttrInOut iInOut) {
    name   = iName;
    kind   = iKind;
    inOut  = inOut;
    isList = 1;
}
//-----------------------------------------------------------------------------
void KTCCatalogParameter::SetValue(const CATUnicodeString& iName, TCKind iKind,
                                   CATAttrInOut iInOut) {
    name   = iName;
    kind   = iKind;
    inOut  = inOut;
    isList = 0;
}
