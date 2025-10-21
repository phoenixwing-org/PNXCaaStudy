/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXEBomAnalysisEdit.cpp
 * @brief       Provide implementation to interface
 */

// System Framework
#include "CATCommand.h"

// Local FrameWork
#include "PNXEBomAnalysisEdit.h"
#include "PNXBomAnalysisCmd.h" // needed to return the Sound Hole edition command

CATImplementClass(PNXEBomAnalysisEdit, DataExtension, CATIEdit, PNXBomAnalysis);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, PNXEBomAnalysisEdit);

//
// To declare that PNXBomAnalysis implements CATIEdit , insert
// the following line in the interface dictionary :
//
// PNXBomAnalysis      CATIEdit    libPNXBomAnalysisUI

//-----------------------------------------------------------------------------
// PNXEBomAnalysisEdit : constructor
//-----------------------------------------------------------------------------
PNXEBomAnalysisEdit::PNXEBomAnalysisEdit() {
}

//-----------------------------------------------------------------------------
// PNXEBomAnalysisEdit : destructor
//-----------------------------------------------------------------------------
PNXEBomAnalysisEdit::~PNXEBomAnalysisEdit() {
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand* PNXEBomAnalysisEdit::Activate(CATPathElement*) {

    // creates the edition command
    CATCommand* pCommand = new PNXBomAnalysisCmd();
    return pCommand;
}
