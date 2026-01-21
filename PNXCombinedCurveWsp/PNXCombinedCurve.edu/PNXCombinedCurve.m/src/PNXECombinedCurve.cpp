// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================
//
// PNXECombinedCurve.cpp
// Provide implementation to interface
//      PNXICombinedCurve
//======================================================================================

// Local Framework
#include "PNXECombinedCurve.h"

// ObjectSpecsModeler
#include "CATIDescendants.h"

// MecModInterfaces Framework
#include "CATIMfBRep.h"

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h" // needed to access feature attributes
#include "CATISpecAttrKey.h"    // needed to access to the feature attribute values
#include "CATISpecObject.h"     // needed to manage/query features

CATImplementClass(PNXECombinedCurve, DataExtension, CATBaseUnknown, CombinedCurve);

//-------------------------------------------------------------------------------------
// PNXECombinedCurve : constructor
//-------------------------------------------------------------------------------------
PNXECombinedCurve::PNXECombinedCurve()
    : CATBaseUnknown()
    , ktcSpecRW() {
    ktcSpecRW.initial(this); // initial{
}

//-------------------------------------------------------------------------------------
// PNXECombinedCurve : destructor
//-------------------------------------------------------------------------------------
PNXECombinedCurve::~PNXECombinedCurve() {
}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_PNXICombinedCurve.h" // needed to tie the implementation to its interface
TIE_PNXICombinedCurve(PNXECombinedCurve);

// To declare that CombinedCurve implements PNXICombinedCurve, insert
// the following line in the interface dictionary:
//
// CombinedCurve  PNXICombinedCurve  libPNXCombinedCurve

// DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
// START KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS CPP GET

// clang-format off

//-----------------------------------------------
CATISpecObject_var PNXECombinedCurve::GetFirstPoint() const // 2
{
    CATISpecObject_var value(NULL_var);
    ktcSpecRW.GetSpecValue("FirstPoint", value);
    return value;
}
//-----------------------------------------------
CATISpecObject_var PNXECombinedCurve::GetMainDir() const // 3
{
    CATISpecObject_var value;
    ktcSpecRW.GetSpecValue("MainDir", value);
    return value;
}

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS CPP GET

// DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
// START KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS CPP SET

// clang-format off

//-----------------------------------------------
HRESULT PNXECombinedCurve::SetFirstPoint(const CATISpecObject_var& value, const CATBoolean& checkExist) // 2
{
    return ktcSpecRW.SetSpecValue("FirstPoint", value, checkExist);
}
//-----------------------------------------------
HRESULT PNXECombinedCurve::SetMainDir(const CATISpecObject_var& value, const CATBoolean& checkExist) // 3
{
    return ktcSpecRW.SetSpecValue("MainDir", value, checkExist);
}

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS CPP SET
