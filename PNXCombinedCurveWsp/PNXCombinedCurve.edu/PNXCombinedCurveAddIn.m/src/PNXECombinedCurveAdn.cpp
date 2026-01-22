// COPYRIGHT DASSAULT SYSTEMES 2000
//===========================================================================
// PNXECombinedCurveAdn.cpp
// Provide implementation to interface
//      CATIShapeDesignWorkshopAddin
//
//===========================================================================

// Local Framework
#include "PNXECombinedCurveAdn.h"

// ApplicationFrame Framework
#include "CATCommandHeader.h"  // needed to instanciate the header
#include <CATCreateWorkshop.h> // needed to manage workshop access

// Creates the PNXECombinedCurveAdnHeader command header class
MacDeclareHeader(PNXECombinedCurveAdnHeader);

// To declare that the class
// is a DataExtension of (late type) PNXCombinedCurveAddin

CATImplementClass(PNXECombinedCurveAdn, DataExtension, CATBaseUnknown, PNXCombinedCurveAddin);

//
// To declare that PNXCombinedCurveAddin implements CATIShapeDesignWorkshopAddin, insert
// the following line in the interface dictionary :
//
// PNXCombinedCurveAddin      CATIShapeDesignWorkshopAddin    libPNXCombinedCurveAddIn

#include <TIE_CATIShapeDesignWorkshopAddin.h> // needed to tie the implementation to its interface
TIE_CATIShapeDesignWorkshopAddin(PNXECombinedCurveAdn);

//-----------------------------------------------------------------------------
// PNXECombinedCurveAdn : constructor
//-----------------------------------------------------------------------------

PNXECombinedCurveAdn::PNXECombinedCurveAdn() {
}

//-----------------------------------------------------------------------------
// PNXECombinedCurveAdn : destructor
//-----------------------------------------------------------------------------

PNXECombinedCurveAdn::~PNXECombinedCurveAdn() {
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateCommands
//-----------------------------------------------------------------------------

void PNXECombinedCurveAdn::CreateCommands() {

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    new PNXECombinedCurveAdnHeader("PNXCombinedCurveHdr", "PNXCombinedCurveUI",
                                   "PNXCombinedCurveCmd", (void*)NULL);
}

//-----------------------------------------------------------------------------
// Implements CATIShapeDesignWorkshopAddin::CreateToolbars
//-----------------------------------------------------------------------------

CATCmdContainer* PNXECombinedCurveAdn::CreateToolbars() {

    // CombinedCurve Toolbar
    NewAccess(CATCmdContainer, pCombinedCurveWkb, PNXCombinedCurveTlb);

    NewAccess(CATCmdStarter, pCombinedCurve, PNXCombinedCurveStr);
    SetAccessCommand(pCombinedCurve, "PNXCombinedCurveHdr");
    SetAccessChild(pCombinedCurveWkb, pCombinedCurve);

    AddToolbarView(pCombinedCurveWkb, -1, Top); // Unvisible toolbar

    return pCombinedCurveWkb;
}
