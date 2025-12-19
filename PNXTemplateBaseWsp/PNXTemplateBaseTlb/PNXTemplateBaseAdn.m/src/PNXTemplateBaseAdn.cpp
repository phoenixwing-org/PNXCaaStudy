/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @date  		2025-12-17
 * @file  		PNXTemplateBaseAdn.cpp
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 *  reference to CAAAniCfg.cpp
 */

// Local Framework
#include "PNXTemplateBaseAdn.h"

// ApplicationFrame Framework
#include "CATCommandHeader.h"  // needed to instanciate the header
#include "CATCreateWorkshop.h" // needed to manage workshop access

// Creates the PNXTemplateBaseAdnHeader command header class
MacDeclareHeader(PNXTemplateBaseAdnHeader);

// To declare that the class
// is a DataExtension of (late type) PNXTemplateBaseAddin

CATImplementClass(PNXTemplateBaseAdn, // ClassName
                  DataExtension, CATBaseUnknown,
                  PNXTemplateBaseAddin); // Aliase namefor Dico file

//
// To declare that PNXTemplateBaseAddin implements CATIPrtWksAddin, insert
// the following line in the interface dictionary :
//
// PNXTemplateBaseAddin      CATIPrtWksAddin    libPNXTemplateBaseAdn

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXTemplateBaseAdn);

// PNXTemplateBaseAdn : constructor-------------------------------------------------
PNXTemplateBaseAdn::PNXTemplateBaseAdn() {
}
// PNXTemplateBaseAdn : destructor-------------------------------------------------
PNXTemplateBaseAdn::~PNXTemplateBaseAdn() {
}
// Implements CATIPrtWksAddin::CreateCommands-------------------------------------------------
void PNXTemplateBaseAdn::CreateCommands() {

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    //
    // step 1. new PNXTemplateBaseAdnHeader for each icon
    //

    new PNXTemplateBaseAdnHeader("PNXTemplateBaseHdr", "PNXTemplateBaseUI", "PNXTemplateBaseCmd",
                                 (void*)NULL);
}
// Implements CATIPrtWksAddin::CreateToolbars-------------------------------------------------
CATCmdContainer* PNXTemplateBaseAdn::CreateToolbars() {

    //----------------------
    // Toolbar
    //----------------------

    //
    // step 2. new a toolbar
    //

    // PNXTemplateBase Toolbar
    NewAccess(CATCmdContainer, pTemplateBaseWkb, PNXTemplateBaseTlb);

    //
    // step 3. step by step create each icon hdr
    //

    // PNXTemplateBaseHdr
    NewAccess(CATCmdStarter, pTemplateBase, PNXTemplateBaseStr);
    SetAccessCommand(pTemplateBase, "PNXTemplateBaseHdr");
    SetAccessChild(pTemplateBaseWkb, pTemplateBase);

    //
    // step 4. AddToolbarView
    //
    AddToolbarView(pTemplateBaseWkb, 1, UnDock); // visible toolbar

    return pTemplateBaseWkb;
}
