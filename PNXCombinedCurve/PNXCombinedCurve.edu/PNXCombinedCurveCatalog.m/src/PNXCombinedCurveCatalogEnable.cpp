// COPYRIGHT DASSAULT SYSTEMES 2000

// Local FrameWork
#include "PNXCombinedCurveCatalogEnable.h"
#include "iostream.h"

CATImplementClass(PNXCombinedCurveCatalogEnable, DataExtension, CATBaseUnknown, CombinedCurve);

//-----------------------------------------------------------------------------
// PNXCombinedCurveCatalogEnable : constructor
//-----------------------------------------------------------------------------
PNXCombinedCurveCatalogEnable::PNXCombinedCurveCatalogEnable() {
    cout << "PNXCombinedCurveCatalogEnable::PNXCombinedCurveCatalogEnable" << endl;
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCatalogEnable : destructor
//-----------------------------------------------------------------------------
PNXCombinedCurveCatalogEnable::~PNXCombinedCurveCatalogEnable() {
    cout << "PNXCombinedCurveCatalogEnable::~PNXCombinedCurveCatalogEnable" << endl;
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICatalogEnable.h" // needed to tie the implementation to its interface
TIE_CATICatalogEnable(PNXCombinedCurveCatalogEnable);

//
// To declare that CombinedCurve implements CATICatalogEnable , insert
// the following line in the interface dictionary :
//
// CombinedCurve      CATICatalogEnable    libPNXCombinedCurveCatalog
