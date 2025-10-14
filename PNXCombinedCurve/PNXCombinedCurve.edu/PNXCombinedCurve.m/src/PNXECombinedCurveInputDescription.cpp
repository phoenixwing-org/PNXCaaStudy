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
    cout << " PNXECombinedCurveInputDescription::PNXECombinedCurveInputDescription" << endl;
}

//-------------------------------------------------------------------------------------
PNXECombinedCurveInputDescription::~PNXECombinedCurveInputDescription() {
    cout << " PNXECombinedCurveInputDescription::~PNXECombinedCurveInputDescription" << endl;
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
    cout << " PNXECombinedCurveInputDescription::GetFeatureType" << endl;

    oFeature_type = CATIInputDescription::FeatureType_Creation;
    return S_OK;
}
