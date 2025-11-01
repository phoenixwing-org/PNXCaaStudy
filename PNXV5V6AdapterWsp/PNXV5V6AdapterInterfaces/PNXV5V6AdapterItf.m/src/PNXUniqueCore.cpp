/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @date		2025-11-11
 * @brief
 */

// CAT
#include "CATISpecObject.h"
#include "iostream.h"

// Local
#include "PNXUniqueCore.h"
//-----------------------------------------------------------------------------
PNXUniqueCore::PNXUniqueCore() {
}
//-----------------------------------------------------------------------------
PNXUniqueCore::~PNXUniqueCore() {
}
//-----------------------------------------------------------------------------
PNXIMechanicalFeature_var PNXUniqueCore::checkoutUniqueClass() {
    cout << "PNXUniqueCore::checkoutUniqueClass" << endl;
    if (NULL_var == feature) return NULL_var;

    int code = 0;
#ifdef CATIAR424
    cout << "PNXUniqueCore::calculate for V6" << endl;
    // checkout CATIMmiMechanicalFeature
    CATIMmiMechanicalFeature_var base = NULL_var;
    HRESULT hr = feature->QueryInterface(IID_CATIMmiMechanicalFeature, (void**)&base);
    if (SUCCEEDED(hr) && base != NULL_var) {
        cout << "[ok] checkout CATIMmiMechanicalFeature:" << *base << endl;
        return base;
    }
    else {
        code = 100004;
        cout << "[error] Failed to checkout CATIMmiMechanicalFeature form feature" << endl;
        return NULL_var;
    }
#else //  CATIAV5R19
    cout << "PNXUniqueCore::calculate for V5" << endl;
    // checkout specObject
    CATISpecObject_var base = NULL_var;
    HRESULT            hr   = feature->QueryInterface(IID_CATISpecObject, (void**)&base);
    if (SUCCEEDED(hr) && base != NULL_var) {
        code = 0;
        cout << "[" << code << "] Base Object Name = " << base->GetDisplayName() << endl;
        return base;
    }
    else {
        code = 100005;
        cout << "[" << code << "] Failed to checkout CATISpecObject form feature" << endl;
        return NULL_var;
    }
#endif
    return NULL_var;
}
//-----------------------------------------------------------------------------
int PNXUniqueCore::calculate(PNXIMechanicalFeature_var spFeature) {
    cout << "PNXUniqueCore::calculate" << endl;
    if (NULL_var == spFeature) return 100001;

    int code = 0;
#ifdef CATIAR424
    cout << "PNXUniqueCore::calculate for V6" << endl;
    // checkout specObject
    CATIMmiMechanicalFeature_var base = NULL_var;
    HRESULT hr = spFeature->QueryInterface(IID_CATIMmiMechanicalFeature, (void**)&base);
    if (SUCCEEDED(hr) && base != NULL_var) {
        code = 0;
        cout << "[" << code << "] Base Object Name = " << base->GetDisplayName() << endl;
    }
    else {
        code = 100002;
        cout << "[" << code << "] Failed to checkout CATIMmiMechanicalFeature form input" << endl;
    }
#else //  CATIAV5R19
    cout << "PNXUniqueCore::calculate for V5" << endl;
    // checkout specObject
    CATISpecObject_var base = NULL_var;
    HRESULT            hr   = spFeature->QueryInterface(IID_CATISpecObject, (void**)&base);
    if (SUCCEEDED(hr) && base != NULL_var) {
        code = 0;
        cout << "[" << code << "] Base Object Name = " << base->GetDisplayName() << endl;
    }
    else {
        code = 100003;
        cout << "[" << code << "] Failed to checkout CATISpecObject form input" << endl;
    }
#endif

    return code;
}
