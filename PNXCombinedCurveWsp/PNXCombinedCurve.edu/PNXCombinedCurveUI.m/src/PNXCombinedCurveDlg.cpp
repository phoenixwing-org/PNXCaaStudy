// COPYRIGHT DASSAULT SYSTEMES 2000

// ApplicationFrame Framework
#include "CATApplicationFrame.h" // needed to get the window of the frame

// Dialog Framework
#include "CATDlgGridConstraints.h" // needed to locate dialog element on the box's grid
#include "CATDlgLabel.h"

// auto code
#include "KTCAutoIncludeUI.h"

// Local Framework
#include "PNXCombinedCurveDlg.h"
#include "PNXSubCurveDlg.h"

//-------------------------------------------------------------------------
PNXCombinedCurveDlg::PNXCombinedCurveDlg()
    : KTCAutoDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), NULL,
                    "CombinedCurve",
                    CATDlgGridLayout | CATDlgWndOK | CATDlgWndCANCEL | CATDlgWndNoResize)
    , _selectorListFirstPoint(NULL)
    , _selectorListMainDir(NULL)
    , _pushButtonSaveJson(NULL)
    , _pushButtonDirectCallback(NULL)
    , _pushButtonSubDialog(NULL)
    , _subPanel(NULL) {
    // never call the Build method of the panel from the constructor
    // it is much better to call it from the same method that created (new) the panel
}
//-------------------------------------------------------------------------
PNXCombinedCurveDlg::~PNXCombinedCurveDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    _selectorListFirstPoint   = NULL;
    _selectorListMainDir      = NULL;
    _pushButtonSaveJson       = NULL;
    _pushButtonDirectCallback = NULL;
    _pushButtonSubDialog      = NULL;
    _subPanel                 = NULL;
}
//-------------------------------------------------------------------------
void PNXCombinedCurveDlg::Build() {
    // Creates the CATDlgLabel for the input field's names.

    CATDlgLabel* labelFirstPoint = new CATDlgLabel(this, CATString("labelFirstPoint"));

    CATDlgLabel* labelMainDir = new CATDlgLabel(this, CATString("labelMainDir"));

    // Creates the four input fields .
    CATUnicodeString Prompt_nosel = "no selection";

    _selectorListFirstPoint =
        new CATDlgSelectorList(this, CATString("selFirstPoint"), CATDlgDataModify);
    _selectorListFirstPoint->SetVisibleTextHeight(1);
    _selectorListFirstPoint->SetLine(Prompt_nosel, 0, CATDlgDataModify);

    _selectorListMainDir = new CATDlgSelectorList(this, CATString("selMainDir"), CATDlgDataModify);
    _selectorListMainDir->SetVisibleTextHeight(1);
    _selectorListMainDir->SetLine(Prompt_nosel, 0, CATDlgDataModify);

    // Creates the save json button.
    _pushButtonSaveJson = new CATDlgPushButton(this, CATString("pushButtonSaveJson"));
    _pushButtonSaveJson->SetName(CATString("Save Json With Agent"));
    // _pushButtonSaveJson->SetIconName("I_CombinedCurve");

    _pushButtonDirectCallback = new CATDlgPushButton(this, CATString("pushButtonDirectCallback"));
    _pushButtonDirectCallback->SetName(CATString("Direct Callback"));

    _pushButtonSubDialog = new CATDlgPushButton(this, CATString("pushButtonSubDialog"));
    _pushButtonSubDialog->SetName(CATString("push Button Sub Dialog"));

    // Uses the grid of the panel to position the label and the input fields.
    CATDlgGridConstraints cst;
    cst.Justification = CATGRID_4SIDES;
    cst.H_Span        = 1;
    cst.V_Span        = 1;

    // first column : labels.
    cst.Column = 0;

    cst.Row = 0;
    labelMainDir->SetGridConstraints(cst);
    cst.Row = 1;
    labelFirstPoint->SetGridConstraints(cst);

    // second column : input fields.
    cst.Column = 1;

    cst.Row = 0;
    _selectorListFirstPoint->SetGridConstraints(cst);
    cst.Row = 1;
    _selectorListMainDir->SetGridConstraints(cst);
    cst.Row = 2;
    _pushButtonSaveJson->SetGridConstraints(cst);
    cst.Row = 3;
    _pushButtonDirectCallback->SetGridConstraints(cst);
    cst.Row = 4;
    _pushButtonSubDialog->SetGridConstraints(cst);

    // Finally, makes the panel appear.
    SetVisibility(CATDlgShow);

    _subPanel = new PNXSubCurveDlg(this);
    // builds the dialog box
    _subPanel->Build();
}
//-------------------------------------------------------------------------
void PNXCombinedCurveDlg::SetActiveField(int iFieldNumber) {
    //  Deselects all others field when changing of active field ( by clicking in another one ).
    if (PNXCopyStudyFieldFirstPoint != iFieldNumber) _selectorListFirstPoint->ClearSelect();
    if (PNXCopyStudyFieldMainDir != iFieldNumber) _selectorListMainDir->ClearSelect();
    return;
}
//-------------------------------------------------------------------------
void PNXCombinedCurveDlg::SetName(int iFieldNumber, CATUnicodeString iName) {
    // Writes the name of the selected objet in the active field.
    // Replaces it if the object was already selected.

    switch (iFieldNumber) {
    case PNXCopyStudyFieldFirstPoint: {
        _selectorListFirstPoint->SetLine(iName, 0, CATDlgDataModify);
        return;
    }
    case PNXCopyStudyFieldMainDir: {
        _selectorListMainDir->SetLine(iName, 0, CATDlgDataModify);
        return;
    }
    }
    return;
}
//-------------------------------------------------------------------------
CATDlgSelectorList* PNXCombinedCurveDlg::GetField(int iFieldNumber) {
    // returns the active field ( used by the state command ).
    switch (iFieldNumber) {
    case PNXCopyStudyFieldFirstPoint:
        return _selectorListFirstPoint;
    case PNXCopyStudyFieldMainDir:
        return _selectorListMainDir;
    }
    return NULL;
}
//-------------------------------------------------------------------------
void PNXCombinedCurveDlg::SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) {

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve DIALOG NOTIFY

    // clang-format off

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve DIALOG NOTIFY
}
//-------------------------------------------------------------------------
void PNXCombinedCurveDlg::UpdateDialog() {
    // if (!parameter) return; // check pointer

    // KEVIN_SYSTEM_CODE START
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve UPDATE DIALOG

    // clang-format off

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve UPDATE DIALOG

    // Code add by user

    this->UpdateSensitivity(); // update sensitivity
    // this->SetActiveFieldFocus(); // focus
}
//-----------------------------------------------------------------
void PNXCombinedCurveDlg::UpdateInfos() {
    // if (!parameter) return; // check pointer

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve UPDATE INFORS

    // clang-format off

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve UPDATE INFORS
}
//-------------------------------------------------------------------------
void PNXCombinedCurveDlg::UpdateSensitivity() {
    //_PushButtonMore->SetVisibility(CATDlgHide);//hide the param dialog now
    // check OK Sensitivity
    // this is Feature mode, Do not check OK sensitivity. always can press
    // this->SetOKSensitivity(dlgState); //set state
    // CATULong dlgState;
}
