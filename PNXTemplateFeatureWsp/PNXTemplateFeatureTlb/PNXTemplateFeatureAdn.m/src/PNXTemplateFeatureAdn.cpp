/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @date  		2025-12-17
 * @file  		PNXTemplateFeatureAdn.cpp
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 *  reference to CAAAniCfg.cpp
 */

// Local Framework
#include "PNXTemplateFeatureAdn.h"

// ApplicationFrame Framework
#include "CATCommandHeader.h"  // needed to instanciate the header
#include "CATCreateWorkshop.h" // needed to manage workshop access

// Creates the PNXTemplateFeatureAdnHeader command header class
MacDeclareHeader(PNXTemplateFeatureAdnHeader);

// To declare that the class
// is a DataExtension of (late type) PNXTemplateFeatureAddin

CATImplementClass(PNXTemplateFeatureAdn, // ClassName
                  DataExtension, CATBaseUnknown,
                  PNXTemplateFeatureAddin); // Aliase namefor Dico file

//
// To declare that PNXTemplateFeatureAddin implements CATIPrtWksAddin, insert
// the following line in the interface dictionary :
//
// PNXTemplateFeatureAddin      CATIPrtWksAddin    libPNXTemplateFeatureAdn

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXTemplateFeatureAdn);

// PNXTemplateFeatureAdn : constructor-------------------------------------------------
PNXTemplateFeatureAdn::PNXTemplateFeatureAdn() {
}
// PNXTemplateFeatureAdn : destructor-------------------------------------------------
PNXTemplateFeatureAdn::~PNXTemplateFeatureAdn() {
}
// Implements CATIPrtWksAddin::CreateCommands-------------------------------------------------
void PNXTemplateFeatureAdn::CreateCommands() {

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    //
    // step 1. new PNXTemplateFeatureAdnHeader for each icon
    //

    new PNXTemplateFeatureAdnHeader("PNXTemplateFeatureHdr", "PNXTemplateFeatureUI",
                                    "PNXTemplateFeatureCmd", (void*)NULL);
}
// Implements CATIPrtWksAddin::CreateToolbars-------------------------------------------------
CATCmdContainer* PNXTemplateFeatureAdn::CreateToolbars() {

    //----------------------
    // Toolbar
    //----------------------

    //
    // step 2. new a toolbar
    //

    // PNXTemplateFeature Toolbar
    NewAccess(CATCmdContainer, pTemplateFeatureWkb, PNXTemplateFeatureTlb);

    //
    // step 3. step by step create each icon hdr
    //

    // PNXTemplateFeatureHdr
    NewAccess(CATCmdStarter, pTemplateFeature, PNXTemplateFeatureStr);
    SetAccessCommand(pTemplateFeature, "PNXTemplateFeatureHdr");
    SetAccessChild(pTemplateFeatureWkb, pTemplateFeature);

    //
    // step 4. AddToolbarView
    //
    AddToolbarView(pTemplateFeatureWkb, 1, UnDock); // visible toolbar

    return pTemplateFeatureWkb;
}
