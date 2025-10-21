// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// PNXECombinedCurveCkeFeature.cpp
// Provide implementation to interface
//    CATKweInstanceAdapter
//
//===================================================================
//
// Usage notes:
//
//===================================================================

#include "PNXECombinedCurveCkeFeature.h"

CATImplementClass(PNXECombinedCurveCkeFeature, DataExtension, CATBaseUnknown, CombinedCurve);

#include "TIE_CATICkeFeature.h"
TIEchain_CATICkeFeature(PNXECombinedCurveCkeFeature);

// LiteralFeatures
#include "CATGlobalFunctions.h"
#include "CATITypeDictionary.h"

#include "iostream.h"

#include "CATIType.h"
//-----------------------------------------------------------------------------
// PNXECombinedCurveCkeFeature : constructor
//-----------------------------------------------------------------------------
PNXECombinedCurveCkeFeature::PNXECombinedCurveCkeFeature()
    : CATKweInstanceAdapter() {
}
PNXECombinedCurveCkeFeature::~PNXECombinedCurveCkeFeature() {
}
//-----------------------------------------------------------------------------
// Implements CATKweInstanceAdapter::GetType
//-----------------------------------------------------------------------------
CATICkeType_var PNXECombinedCurveCkeFeature::GetType() const {
    cout << " PNXECombinedCurveCkeFeature" << endl;
    CATITypeDictionary_var TypeDic = CATGlobalFunctions::GetTypeDictionary();
    if (TypeDic != NULL_var) {
        CATIType_var oType;
        HRESULT      rc = TypeDic->FindTypeSafe("Curve", "", oType);
        if (SUCCEEDED(rc)) {
            return oType;
        }
    }
    return NULL_var;
}
