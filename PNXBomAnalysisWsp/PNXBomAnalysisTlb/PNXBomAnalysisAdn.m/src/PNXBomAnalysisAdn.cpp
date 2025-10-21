/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @date  		2021-9-1
 * @file  		PNXBomAnalysisAdn.cpp
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 *  reference to CAAAniCfg.cpp
 */

// Local Framework
#include "PNXBomAnalysisAdn.h"

// ApplicationFrame Framework
#include "CATCommandHeader.h"  // needed to instanciate the header
#include "CATCreateWorkshop.h" // needed to manage workshop access

// Creates the PNXBomAnalysisAdnHeader command header class
MacDeclareHeader(PNXBomAnalysisAdnHeader);

// To declare that the class
// is a DataExtension of (late type) PNXBomAnalysisAddin

CATImplementClass(PNXBomAnalysisAdn, // ClassName
                  DataExtension, CATBaseUnknown,
                  PNXBomAnalysisAddin); // Aliase namefor Dico file

//
// To declare that PNXBomAnalysisAddin implements CATIPrtWksAddin, insert
// the following line in the interface dictionary :
//
// PNXBomAnalysisAddin      CATIPrtWksAddin    libPNXBomAnalysisAdn

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXBomAnalysisAdn);

// TIE or TIEchain definitions
#include "TIE_CATIPRDWorkshopAddin.h"
TIE_CATIPRDWorkshopAddin(PNXBomAnalysisAdn);

// PNXBomAnalysisAdn :
// constructor-------------------------------------------------
PNXBomAnalysisAdn::PNXBomAnalysisAdn() {
}
// PNXBomAnalysisAdn :
// destructor-------------------------------------------------
PNXBomAnalysisAdn::~PNXBomAnalysisAdn() {
}
// Implements
// CATIPrtWksAddin::CreateCommands-------------------------------------------------
void PNXBomAnalysisAdn::CreateCommands() {

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    //
    // step 1. new PNXBomAnalysisAdnHeader for each icon
    //

    new PNXBomAnalysisAdnHeader("PNXBomAnalysisHdr", "PNXBomAnalysisUI", "PNXBomAnalysisCmd",
                                (void*)NULL);
}
// Implements
// CATIPrtWksAddin::CreateToolbars-------------------------------------------------
CATCmdContainer* PNXBomAnalysisAdn::CreateToolbars() {

    //----------------------
    // Toolbar
    //----------------------

    //
    // step 2. new a toolbar
    //

    // PNXBomAnalysis Toolbar
    NewAccess(CATCmdContainer, pBomAnalysisWkb, PNXBomAnalysisTlb);

    //
    // step 3. step by step create each icon hdr
    //

    // PNXBomAnalysisHdr
    NewAccess(CATCmdStarter, pBomAnalysis, PNXBomAnalysisStr);
    SetAccessCommand(pBomAnalysis, "PNXBomAnalysisHdr");
    SetAccessChild(pBomAnalysisWkb, pBomAnalysis);

    //
    // step 4. AddToolbarView
    //
    AddToolbarView(pBomAnalysisWkb, 1, UnDock); // visible toolbar

    return pBomAnalysisWkb;
}
