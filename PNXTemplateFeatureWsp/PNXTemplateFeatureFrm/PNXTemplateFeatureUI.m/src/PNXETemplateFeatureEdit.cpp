/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXETemplateFeatureEdit.cpp
 * @brief       Provide implementation to interface
 */

// System Framework
#include "CATCommand.h"

// PNXTemplateFeatureFrm Framework
#include "PNXITemplateFeature.h" // needed to build the command from the User Feature to edit

// Local FrameWork
#include "PNXETemplateFeatureEdit.h"
#include "PNXTemplateFeatureCmd.h" // needed to return the User Feature edition command

CATImplementClass(PNXETemplateFeatureEdit, DataExtension, CATIEdit, PNXTemplateFeature);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, PNXETemplateFeatureEdit);

//
// To declare that PNXTemplateFeature implements CATIEdit , insert
// the following line in the interface dictionary :
//
// PNXTemplateFeature      CATIEdit    libPNXTemplateFeatureUI

//-----------------------------------------------------------------------------
// PNXETemplateFeatureEdit : constructor
//-----------------------------------------------------------------------------
PNXETemplateFeatureEdit::PNXETemplateFeatureEdit() {
}

//-----------------------------------------------------------------------------
// PNXETemplateFeatureEdit : destructor
//-----------------------------------------------------------------------------
PNXETemplateFeatureEdit::~PNXETemplateFeatureEdit() {
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand* PNXETemplateFeatureEdit::Activate(CATPathElement* ipPath) {

    // gets a pointer on PNXITemplateFeature in edition
    PNXITemplateFeature* piTemplateFeature = NULL;
    HRESULT              hr = QueryInterface(IID_PNXITemplateFeature, (void**)&piTemplateFeature);
    if (FAILED(hr) || NULL == piTemplateFeature) return NULL;

    // creates the edition command
    CATCommand* pCommand = new PNXTemplateFeatureCmd(piTemplateFeature);

    KTCRelease(piTemplateFeature); // releases useless pointer

    return pCommand;
}
