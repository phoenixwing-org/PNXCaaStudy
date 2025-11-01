/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXEV5V6AdapterEdit.cpp
 * @brief       Provide implementation to interface
 */

// System Framework
#include "CATCommand.h"

// Local FrameWork
#include "PNXEV5V6AdapterEdit.h"
#include "PNXV5V6AdapterCmd.h" // needed to return the Sound Hole edition command

CATImplementClass(PNXEV5V6AdapterEdit, DataExtension, CATIEdit, PNXV5V6Adapter);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, PNXEV5V6AdapterEdit);

//
// To declare that PNXV5V6Adapter implements CATIEdit , insert
// the following line in the interface dictionary :
//
// PNXV5V6Adapter      CATIEdit    libPNXV5V6AdapterUI

//-----------------------------------------------------------------------------
// PNXEV5V6AdapterEdit : constructor
//-----------------------------------------------------------------------------
PNXEV5V6AdapterEdit::PNXEV5V6AdapterEdit() {
}

//-----------------------------------------------------------------------------
// PNXEV5V6AdapterEdit : destructor
//-----------------------------------------------------------------------------
PNXEV5V6AdapterEdit::~PNXEV5V6AdapterEdit() {
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand* PNXEV5V6AdapterEdit::Activate(CATPathElement*) {

    // creates the edition command
    CATCommand* pCommand = new PNXV5V6AdapterCmd();
    return pCommand;
}
