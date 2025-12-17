/**
 * @copyright   Copyright 2021 Kevin Time Toolkit
 * @license     MIT
 * @author      Phoenix Wing
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

// cat
#include "CATDialogAgent.h"
#include "CATMMUIPanelStateCmd.h"
#include "iostream.h"

// Local Framework
#include "KTCDlgDialog.h"

//-------------------------------------------------------------------------
KTCDlgDialog::KTCDlgDialog(CATDialog* iParent, CATMMUIPanelStateCmd* iFatherCmd,
                           const CATString& iObjectName, CATDlgStyle iStyle)
    // CATDialog *iParent, CATCommand *iEventMgr, const CATString& iObjectName, CATDlgStyle
    // iStyle=NULL
    : CATDlgDialog(iParent, iFatherCmd, iObjectName, iStyle)
    , _parameterDialog(NULL)
    , _currentField(0) {
}
//-------------------------------------------------------------------------
KTCDlgDialog::~KTCDlgDialog() {
    _parameterDialog = NULL;
    // _currentField = 0;
}
//-------------------------------------------------------------------------
void KTCDlgDialog::RegisterParameterDialog(CATDlgDialog* dlg) {
    _parameterDialog = dlg;
}
//-------------------------------------------------------------------------
void KTCDlgDialog::SetActiveFieldFocus() {

    // TODO KTCDlgDialog::SetActiveFieldFocus
    cout << "TODO KTCDlgDialog::SetActiveFieldFocus" << endl;
}
