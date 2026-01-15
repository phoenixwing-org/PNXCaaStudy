/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXETemplateBaseEdit.cpp
 * @brief       Provide implementation to interface
 */

// System Framework
#include "CATCommand.h"

// Local FrameWork
#include "PNXETemplateBaseEdit.h"
#include "PNXTemplateBaseCmd.h" // needed to return the User Feature edition command

CATImplementClass(PNXETemplateBaseEdit, DataExtension, CATIEdit, PNXTemplateBase);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, PNXETemplateBaseEdit);

//
// To declare that PNXTemplateBase implements CATIEdit , insert
// the following line in the interface dictionary :
//
// PNXTemplateBase      CATIEdit    libPNXTemplateBaseUI

//-----------------------------------------------------------------------------
// PNXETemplateBaseEdit : constructor
//-----------------------------------------------------------------------------
PNXETemplateBaseEdit::PNXETemplateBaseEdit() {
}

//-----------------------------------------------------------------------------
// PNXETemplateBaseEdit : destructor
//-----------------------------------------------------------------------------
PNXETemplateBaseEdit::~PNXETemplateBaseEdit() {
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand* PNXETemplateBaseEdit::Activate(CATPathElement*) {
    // creates the edition command
    CATCommand* pCommand = new PNXTemplateBaseCmd();
    return pCommand;
}
