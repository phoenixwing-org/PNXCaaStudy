// COPYRIGHT DASSAULT SYSTEMES 2000
#include <PNXECombinedCurveAttrBehavior.h>

// System Framework
#include "CATCollec.h"
#include "CATUnicodeString.h" // To handle Unicode String

// GeometricObjects Framework
#include "CATLine.h" // To put the CATLine IID in the CATBehaviorSpecs

// MechanicalModeler Framework
#include "CATIMfMonoDimResult.h" // To put the CATIMfMonoDimResult IID int the CATBehaviorSpecs

#include <iostream.h>

CATImplementClass(PNXECombinedCurveAttrBehavior, CodeExtension, CATBaseUnknown, CombinedCurve);

#include "TIE_CATIAttrBehavior.h"
TIE_CATIAttrBehavior(PNXECombinedCurveAttrBehavior);

//
// To declare that CombineCurve implements CATIAttrBehavior,
// insert these following lines in the interface dictionary:
//
//    CombinedCurve        CATIAttrBehavior    libPNXCombinedCurveReplace
//
//-----------------------------------------------------------------------------

//========================================================================
// Constructor - Destructor
//========================================================================
PNXECombinedCurveAttrBehavior::PNXECombinedCurveAttrBehavior()
    : CATBaseUnknown() {
    cout << "PNXECombinedCurveAttrBehavior::PNXECombinedCurveAttrBehavior" << endl;
}

PNXECombinedCurveAttrBehavior::~PNXECombinedCurveAttrBehavior() {
    cout << "PNXECombinedCurveAttrBehavior::~PNXECombinedCurveAttrBehavior" << endl;
}

//------------------------------------------------------------------------
//   GetRequestedBehavior
//------------------------------------------------------------------------
HRESULT PNXECombinedCurveAttrBehavior::GetRequestedBehavior(const CATUnicodeString* ipAttrId,
                                                            CATBehaviorSpecs**      oppBehavior) {
    cout << "PNXECombinedCurveAttrBehavior::GetRequestedBehavior" << endl;

    HRESULT exit = E_FAIL;
    if ((NULL != oppBehavior) && (NULL != ipAttrId)) {
        *oppBehavior = new CATBehaviorSpecs;

        if (NULL != *oppBehavior) {
            // If the input String is equal to "FirstPoint" which are the name
            // of two attributes then the Filter will be IID_CATIMfMonoDimResult
            // That is to say, we can Replace in those two attributes a Feature
            // implementing the interface CATIMfMonoDimResult by another one
            if (2 == ipAttrId->Compare("FirstPoint")) {
                CATListPV* aMyFirstList = new CATListPV;
                aMyFirstList->Append((void*)&IID_CATIMfMonoDimResult);
                (*oppBehavior)->Append(aMyFirstList);
                exit = S_OK;
            }
            // If the input String is equal to "MainDir" which are the name
            // of two attributes then the Filter will be IID_CATLine
            // That is to say, we can Replace in those two attributes a Feature
            // implementing the interface CATLine by another one
            else if (2 == ipAttrId->Compare("MainDir")) {
                CATListPV* aMyFirstList = new CATListPV;
                aMyFirstList->Append((void*)&IID_CATLine);
                (*oppBehavior)->Append(aMyFirstList);
                exit = S_OK;
            }
        }
    }

    return exit;
}
