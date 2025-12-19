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
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATMMUIPanelStateCmd.h"
#include "iostream.h"

// Auto Code
#include "KTCAutoDialog.h"

//-------------------------------------------------------------------------
KTCAutoDialog::KTCAutoDialog(CATDialog* iParent, CATMMUIPanelStateCmd* iFatherCmd,
                             const CATString& iObjectName, CATDlgStyle iStyle)
    // CATDialog *iParent, CATCommand *iEventMgr, const CATString& iObjectName, CATDlgStyle
    // iStyle=NULL
    : CATDlgDialog(iParent, iFatherCmd, iObjectName, iStyle)
    , _parameterDialog(NULL)
    , _currentField(0)
    , _catHSO(NULL)
    , _actionMode(KTC::ValueNormal) {
}
//-------------------------------------------------------------------------
KTCAutoDialog::~KTCAutoDialog() {
    _parameterDialog = NULL;
    _catHSO          = NULL;
    // _currentField = 0;
}
//-------------------------------------------------------------------------
void KTCAutoDialog::RegisterParameterDialog(CATDlgDialog* dlg) {
    _parameterDialog = dlg;

} //-------------------------------------------------------------------------
int KTCAutoDialog::ActionSubCommandReturn() {
    cout << "TODO KTCAutoDialog::ActionSubCommandReturn" << endl;
    return 0;
}
void KTCAutoDialog::SetActiveField(int feild) {
    _currentField = feild;
}
//-------------------------------------------------------------------------
void KTCAutoDialog::SetActiveFieldFocus() {

    // TODO KTCAutoDialog::SetActiveFieldFocus
    cout << "TODO KTCAutoDialog::SetActiveFieldFocus" << endl;
}

//-----------------------------------------------------------------------------
int KTCAutoDialog::selectorlist_setline(CATDlgSelectorList*     selectorList,
                                        CATISpecObject_var      inputObject,
                                        const CATUnicodeString& noneSel) {
    if (!selectorList) return 1;                                     // return error code
    if (selectorList->GetLineCount() > 1) selectorList->ClearLine(); // clear multi line

    // set diaplay name or no selection
    if (inputObject != NULL_var) {
        selectorList->SetLine(inputObject->GetDisplayName(), 0, CATDlgDataModify);
    }
    else
        selectorList->SetLine(noneSel, 0, CATDlgDataModify);

    return 0; // ok
}
//-----------------------------------------------------------------------------
int KTCAutoDialog::selectorlist_setline(CATDlgSelectorList*                 selectorList,
                                        const CATListValCATISpecObject_var& iList,
                                        const CATUnicodeString&             noneSel) {
    if (!selectorList) return 1;                                     // return error code
    if (selectorList->GetLineCount() > 1) selectorList->ClearLine(); // clear multi line

    if (iList.Size() == 0) {
        selectorList->ClearLine(); // clear multi line
        selectorList->SetLine(noneSel, 0, CATDlgDataModify);
        return 0;
    }

    CATISpecObject_var object;
    CATUnicodeString   title;
    for (size_t i = 0; 0 < iList.Size(); i++) {
        int index = i + 1;
        object    = iList[ index ];

        if (!!object)
            title = object->GetDisplayName();
        else
            title = "(NULL Object)";
        selectorList->SetLine(title, i, CATDlgDataModify);
    }

    return iList.Size();
}
//-----------------------------------------------------------------------------
void KTCAutoDialog::ShowMessageBox(const CATUnicodeString& msg, CATDlgDialog* dialog) {
    cout << "TODO KTCAutoDialog::ShowMessageBox" << msg << endl;
    // ::send_message(msg);
}
