/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @date  		2021-9-1
 * @file  		PNXCurveDivisionAdn.cpp
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 *  reference to CAAAniCfg.cpp
 */

// Local Framework
#include "PNXCurveDivisionAdn.h"

// ApplicationFrame Framework
#include "CATCommandHeader.h"  // needed to instanciate the header
#include "CATCreateWorkshop.h" // needed to manage workshop access

// Creates the PNXCurveDivisionAdnHeader command header class
MacDeclareHeader(PNXCurveDivisionAdnHeader);

// To declare that the class
// is a DataExtension of (late type) PNXCurveDivisionAddin

CATImplementClass(PNXCurveDivisionAdn, // ClassName
                  DataExtension, CATBaseUnknown,
                  PNXCurveDivisionAddin); // Aliase namefor Dico file

//
// To declare that PNXCurveDivisionAddin implements CATIPrtWksAddin, insert
// the following line in the interface dictionary :
//
// PNXCurveDivisionAddin      CATIPrtWksAddin    libPNXCurveDivisionAdn

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXCurveDivisionAdn);

// PNXCurveDivisionAdn :
// constructor-------------------------------------------------
PNXCurveDivisionAdn::PNXCurveDivisionAdn() {
}
// PNXCurveDivisionAdn :
// destructor-------------------------------------------------
PNXCurveDivisionAdn::~PNXCurveDivisionAdn() {
}
// Implements
// CATIPrtWksAddin::CreateCommands-------------------------------------------------
void PNXCurveDivisionAdn::CreateCommands() {

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    //
    // step 1. new PNXCurveDivisionAdnHeader for each icon
    //

    new PNXCurveDivisionAdnHeader("PNXCurveDivisionHdr", "PNXCurveDivisionUI", "PNXCurveDivisionCmd",
                                (void*)NULL);
}
// Implements
// CATIPrtWksAddin::CreateToolbars-------------------------------------------------
CATCmdContainer* PNXCurveDivisionAdn::CreateToolbars() {

    //----------------------
    // Toolbar
    //----------------------

    //
    // step 2. new a toolbar
    //

    // PNXCurveDivision Toolbar
    NewAccess(CATCmdContainer, pCurveDivisionWkb, PNXCurveDivisionTlb);

    //
    // step 3. step by step create each icon hdr
    //

    // PNXCurveDivisionHdr
    NewAccess(CATCmdStarter, pCurveDivision, PNXCurveDivisionStr);
    SetAccessCommand(pCurveDivision, "PNXCurveDivisionHdr");
    SetAccessChild(pCurveDivisionWkb, pCurveDivision);

    //
    // step 4. AddToolbarView
    //
    AddToolbarView(pCurveDivisionWkb, 1, UnDock); // visible toolbar

    return pCurveDivisionWkb;
}
