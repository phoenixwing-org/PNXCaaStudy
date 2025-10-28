/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXECurveDivisionEdit.cpp
 * @brief       Provide implementation to interface
 */

// System Framework
#include "CATCommand.h"

// Local FrameWork
#include "PNXECurveDivisionEdit.h"
#include "PNXCurveDivisionCmd.h" // needed to return the Sound Hole edition command

CATImplementClass(PNXECurveDivisionEdit, DataExtension, CATIEdit, PNXCurveDivision);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, PNXECurveDivisionEdit);

//
// To declare that PNXCurveDivision implements CATIEdit , insert
// the following line in the interface dictionary :
//
// PNXCurveDivision      CATIEdit    libPNXCurveDivisionUI

//-----------------------------------------------------------------------------
// PNXECurveDivisionEdit : constructor
//-----------------------------------------------------------------------------
PNXECurveDivisionEdit::PNXECurveDivisionEdit() {
}

//-----------------------------------------------------------------------------
// PNXECurveDivisionEdit : destructor
//-----------------------------------------------------------------------------
PNXECurveDivisionEdit::~PNXECurveDivisionEdit() {
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand* PNXECurveDivisionEdit::Activate(CATPathElement*) {

    // creates the edition command
    CATCommand* pCommand = new PNXCurveDivisionCmd();
    return pCommand;
}
