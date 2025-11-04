/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @date  		2021-9-1
 * @file  		PNXV5V6AdapterAdn.cpp
 * @brief 	    Provide implementation to interface CATIPrtWksAddin
 *  reference to CAAAniCfg.cpp
 */

// Local Framework
#include "PNXV5V6AdapterAdn.h"

// ApplicationFrame Framework
#include "CATCommandHeader.h"  // needed to instanciate the header
#include "CATCreateWorkshop.h" // needed to manage workshop access

// Creates the PNXV5V6AdapterAdnHeader command header class
MacDeclareHeader(PNXV5V6AdapterAdnHeader);

// To declare that the class
// is a DataExtension of (late type) PNXV5V6AdapterAddin

CATImplementClass(PNXV5V6AdapterAdn, // ClassName
                  DataExtension, CATBaseUnknown,
                  PNXV5V6AdapterAddin); // Aliase namefor Dico file

//
// To declare that PNXV5V6AdapterAddin implements CATIPrtWksAddin, insert
// the following line in the interface dictionary :
//
// PNXV5V6AdapterAddin      CATIPrtWksAddin    libPNXV5V6AdapterAdn

#include "TIE_CATIPrtWksAddin.h" // needed to tie the implementation to its interface
TIE_CATIPrtWksAddin(PNXV5V6AdapterAdn);

// PNXV5V6AdapterAdn :
// constructor-------------------------------------------------
PNXV5V6AdapterAdn::PNXV5V6AdapterAdn() {
}
// PNXV5V6AdapterAdn :
// destructor-------------------------------------------------
PNXV5V6AdapterAdn::~PNXV5V6AdapterAdn() {
}
// Implements
// CATIPrtWksAddin::CreateCommands-------------------------------------------------
void PNXV5V6AdapterAdn::CreateCommands() {

    // Instantiation of the header class created by the macro MacDeclareHeader -
    // commands are always available and are represented by a push button

    //
    // step 1. new PNXV5V6AdapterAdnHeader for each icon
    //

    new PNXV5V6AdapterAdnHeader("PNXV5V6AdapterHdr", "PNXV5V6AdapterUI", "PNXV5V6AdapterCmd",
                                (void*)NULL);
}
// Implements
// CATIPrtWksAddin::CreateToolbars-------------------------------------------------
CATCmdContainer* PNXV5V6AdapterAdn::CreateToolbars() {

    //----------------------
    // Toolbar
    //----------------------

    //
    // step 2. new a toolbar
    //

    // PNXV5V6Adapter Toolbar
    NewAccess(CATCmdContainer, pV5V6AdapterWkb, PNXV5V6AdapterTlb);

    //
    // step 3. step by step create each icon hdr
    //

    // PNXV5V6AdapterHdr
    NewAccess(CATCmdStarter, pV5V6Adapter, PNXV5V6AdapterStr);
    SetAccessCommand(pV5V6Adapter, "PNXV5V6AdapterHdr");
    SetAccessChild(pV5V6AdapterWkb, pV5V6Adapter);

    //
    // step 4. AddToolbarView
    //
    AddToolbarView(pV5V6AdapterWkb, 1, UnDock); // visible toolbar

    return pV5V6AdapterWkb;
}
