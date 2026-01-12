// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================

// Local Framework
#include "PNXECombinedCurveInputDescription.h"

#include "iostream.h"

CATImplementClass(PNXECombinedCurveInputDescription, DataExtension, CATIInputDescription,
                  CombinedCurve);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIInputDescription, PNXECombinedCurveInputDescription);

// To declare that CombinedCurve implements PNXICombinedCurve, insert
// the following line in the interface dictionary:
//
// CombinedCurve  CATIInputDescription  libPNXCombinedCurve

//-------------------------------------------------------------------------------------
PNXECombinedCurveInputDescription::PNXECombinedCurveInputDescription()
    : CATIniInputDescriptionAdaptor() {
    cout << "### " << __FUNCTION__ << endl;
}

//-------------------------------------------------------------------------------------
PNXECombinedCurveInputDescription::~PNXECombinedCurveInputDescription() {
    cout << "### " << __FUNCTION__ << endl;
}

//-------------------------------------------------------------------------------------
HRESULT PNXECombinedCurveInputDescription::GetListOfModifiedFeatures(
    CATListValCATBaseUnknown_var& ListOfModifiedFeatures) {
    return E_FAIL;
}

//-------------------------------------------------------------------------------------

HRESULT PNXECombinedCurveInputDescription::GetMainInput(CATBaseUnknown_var& oMainInput) {
    return E_FAIL;
}

//-------------------------------------------------------------------------------------

HRESULT PNXECombinedCurveInputDescription::GetFeatureType(
    CATIInputDescription::FeatureType& oFeature_type) {
    cout << "### " << __FUNCTION__ << endl;

    oFeature_type = CATIInputDescription::FeatureType_Creation;
    return S_OK;
}
