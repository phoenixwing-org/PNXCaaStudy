// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// PNXECombinedCurveEdit.cpp
// Provide implementation to interface
//    CATIEdit
//
//===================================================================

// Local FrameWork
#include "PNXECombinedCurveEdit.h"
#include "PNXCombinedCurveCmd.h" // needed to return the Combined Curve edition command

// PNXCombinedCurve.edu Framework
#include "PNXICombinedCurve.h" // needed to build the command from the Combined Curve to edit

// System Framework
#include "CATCommand.h"

CATImplementClass(PNXECombinedCurveEdit, DataExtension, CATIEdit, CombinedCurve);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, PNXECombinedCurveEdit);

//
// To declare that CombinedCurve implements CATIEdit , insert
// the following line in the interface dictionary :
//
// CombinedCurve      CATIEdit    libPNXCombinedCurveUI

//-----------------------------------------------------------------------------
// PNXECombinedCurveEdit : constructor
//-----------------------------------------------------------------------------
PNXECombinedCurveEdit::PNXECombinedCurveEdit() {
}

//-----------------------------------------------------------------------------
// PNXECombinedCurveEdit : destructor
//-----------------------------------------------------------------------------
PNXECombinedCurveEdit::~PNXECombinedCurveEdit() {
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand* PNXECombinedCurveEdit::Activate(CATPathElement* ipPath) {

    // gets a pointer on PNXICombinedCurve in edition
    PNXICombinedCurve* piCombinedCurve = NULL;
    HRESULT            rc = QueryInterface(IID_PNXICombinedCurve, (void**)&piCombinedCurve);
    if (FAILED(rc)) return NULL;

    // creates the edition command
    CATCommand* pCommand = new PNXCombinedCurveCmd(piCombinedCurve);

    // releases useless pointer
    KTCRelease(piCombinedCurve); //  ÷∂Ø Õ∑≈

    return pCommand;
}
