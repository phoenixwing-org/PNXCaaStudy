// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================

// Local Framework
#include "PNXECombinedCurveMf3DBehavior.h"

#include "iostream.h"

CATImplementClass(PNXECombinedCurveMf3DBehavior, DataExtension, CATBaseUnknown, CombinedCurve);

//-----------------------------------------------------------------------------
#include "TIE_CATIMf3DBehavior.h" // needed to tie the implementation to its interface
TIE_CATIMf3DBehavior(PNXECombinedCurveMf3DBehavior);
//-----------------------------------------------------------------------------

// To declare that CombinedCurve implements CATIMf3DBehavior, insert
// the following line in the interface dictionary:
//
// CombinedCurve  CATIMf3DBehavior  libPNXCombinedCurve

//-------------------------------------------------------------------------------------
PNXECombinedCurveMf3DBehavior::PNXECombinedCurveMf3DBehavior() {
    cout << "### " << __FUNCTION__ << endl;
}

//-------------------------------------------------------------------------------------
PNXECombinedCurveMf3DBehavior::~PNXECombinedCurveMf3DBehavior() {
    cout << "### " << __FUNCTION__ << endl;
}

//-------------------------------------------------------------------------------------
HRESULT PNXECombinedCurveMf3DBehavior::IsASolid() const {
    return E_FAIL;
}

//-------------------------------------------------------------------------------------

HRESULT PNXECombinedCurveMf3DBehavior::IsAShape() const {
    return S_OK;
}

//-------------------------------------------------------------------------------------

HRESULT PNXECombinedCurveMf3DBehavior::IsADatum() const

{
    return E_FAIL;
}
