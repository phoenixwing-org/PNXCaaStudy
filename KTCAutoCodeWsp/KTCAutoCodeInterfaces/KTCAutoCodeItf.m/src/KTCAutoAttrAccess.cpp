/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoAttrAccess.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */
// CAT
#include "iostream.h"

// Local
#include "KTCAutoAttrAccess.h"

//-----------------------------------------------------------------------------
KTCAutoAttrAccess::KTCAutoAttrAccess()
    : available_(false) {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoAttrAccess::~KTCAutoAttrAccess() {
}
//-----------------------------------------------------------------------------
KTCAutoAttrAccess::KTCAutoAttrAccess(const KTCAutoAttrAccess& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoAttrAccess& KTCAutoAttrAccess::operator=(const KTCAutoAttrAccess& iOriginal) {

    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return *this;
}
//-----------------------------------------------------------------------------
bool KTCAutoAttrAccess::IsAvailable() const {
    return available_;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::initial(CATISpecObject_var value) {
    available_ = false; // false first
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetListValue(const CATUnicodeString&       name,
                                        CATListValCATISpecObject_var& value) const {
    value.RemoveAll();
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetSpecValue(const CATUnicodeString& name,
                                        CATISpecObject_var&     value) const {
    value = NULL_var;

    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetSpecValue(const CATUnicodeString& name, CATBoolean& value) const {
    value = CATFalse;

    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetSpecValue(const CATUnicodeString& name, int& value) const {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetSpecValue(const CATUnicodeString& name, double& value) const {
    value = 0;
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetValue(const CATUnicodeString& name, CATBoolean& value) const {
    value = CATFalse;
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetValue(const CATUnicodeString& name, int& value) const {
    value = 0;
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetValue(const CATUnicodeString& name, double& value) const {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetValue(const CATUnicodeString& name, CATUnicodeString& value) const {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::GetValue(const CATUnicodeString& name, KtString& value) const {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetListValue(const CATUnicodeString&             name,
                                        const CATListValCATISpecObject_var& value,
                                        CATBoolean                          checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetSpecValue(const CATUnicodeString&   name,
                                        const CATISpecObject_var& value, CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetSpecValue(const CATUnicodeString& name, CATBoolean value,
                                        CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetSpecValue(const CATUnicodeString& name, int value,
                                        CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetSpecValue(const CATUnicodeString& name, double value,
                                        CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetValue(const CATUnicodeString& name, int value,
                                    CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetValue(const CATUnicodeString& name, double value,
                                    CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetValue(const CATUnicodeString& name, CATBoolean value,
                                    CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetValue(const CATUnicodeString& name, const CATUnicodeString& value,
                                    CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoAttrAccess::SetValue(const CATUnicodeString& name, const KtString& value,
                                    CATBoolean checkExist) {
    cout << "- [ERROR] his function is NOT IMPL" << endl;
    return E_NOTIMPL;
}
