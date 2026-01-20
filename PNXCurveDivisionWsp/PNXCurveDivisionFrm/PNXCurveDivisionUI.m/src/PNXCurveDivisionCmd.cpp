/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

// ApplicationFrame Framework
#include "CATFrmEditor.h" // needed to retrieve the editor and then to highight objects

// Dialog Framework
#include "CATDlgDialog.h" // needed to return the dialog box to GiveMyPanel method of
// father class CATMMUiPanelStateCommand
// DialogEngine Framework
#include "CATDialogState.h"
#include "CATFeatureImportAgent.h" // needed to be able to pick any element whatever its context is
#include "CATStateActivateNotification.h" // to distinguish begin/resume state in the command activation

#include "CATApplicationFrame.h"

// ObjectModelerBase Framework
#include "CATIContainer.h" // needed to create a GS (Geometrical Set)

// ObjectSpecsModeler Framework
#include "CATIDescendants.h" // needed to aggregate the newly created User Feature
#include "CATISpecObject.h"  // needed to manage feature

// InteractiveInterfaces
#include "CATIBuildPath.h" // needed to build a path element to highlight a feature

// MechanicalModeler Framework
#include "CATIBasicTool.h"                   // To retrieve the current tool
#include "CATIGSMTool.h"                     // GSMTool and HybridBody features
#include "CATIMechanicalRootFactory.h"       // needed to create a GS
#include "CATIMmiGeometricalSet.h"           // Only for GSMTool feature
#include "CATIMmiNonOrderedGeometricalSet.h" // Only for GS feature

// MechanicalModelerUI Framework
#include "CATMmrLinearBodyServices.h" // To insert in ordered and linear body
#include "CATPrtUpdateCom.h" // needed to update the feature according to the user's update settings

// MecModInterfaces Framework
#include "CATIPrtPart.h"   // needed to look for a GSM tool
#include "CATMfBRepDefs.h" // needed to declare the modes of BRep feature creation

// Visualization Framework
#include "CATHSO.h" // needed to highlight objects
#include "CATISO.h"
#include "CATIVisProperties.h" // needed to change User Feature's graphical appearance
#include "CATPathElement.h"    // needed to highlight objects
#include "CATVisPropertiesValues.h"
#include "iostream.h"

// System framework
#include "CATBoolean.h"
#include "CATGetEnvValue.h" // To define the type of development
#include "CATLib.h"

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h"

// Update
#include "CATError.h"
#include "CATErrorMacros.h"
#include "CATMfErrUpdate.h"

// Local  Framework
#include "PNXCurveDivisionCmd.h"
#include "PNXCurveDivisionDlg.h"

// auto code
#include "KTCAutoCode.h"
#include "KTCAutoDefine.h"

// PNXCurveDivisionInterfaces Framework

CATCreateClass(PNXCurveDivisionCmd);

//-----------------------------------------------------------------------------
// PNXCurveDivisionCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
PNXCurveDivisionCmd::PNXCurveDivisionCmd()
    : CATMMUIPanelStateCmd("PNXCurveDivisionCommand")

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD AGENT CONSTRUCTOR

    , KT_AUTO_CMD_AGENT_CONSTRUCTOR_COMMON()
    , _pBaseCurveAgent(NULL)
    , _pBaseCurveFieldAgent(NULL)

// end
{
    // cout <<"### " << __FUNCTION__ << endl;

    // create parameter
    parameter = new PNXCurveDivisionParam(); // create Default value Instance

    // creates the dialog box
    dialog            = new PNXCurveDivisionDlg();
    dialog->parameter = parameter; // Pass Value

    // builds the dialog box
    // ! do not call panel->Build from the panel constructor
    dialog->Build();
    catFrmEditor_ = CATFrmEditor::GetCurrentEditor();
    // core set
    core                = new PNXCurveDivisionCore(); // Core
    core->parameter     = parameter;                  // pass value
    core->catFrmEditor_ = catFrmEditor_;              // pass value
}
//-----------------------------------------------------------------------------
PNXCurveDivisionCmd::~PNXCurveDivisionCmd() {
    // cout <<"### " << __FUNCTION__ << endl;

    //.............................................................................
    // KEVIN MANUAL CODE: delete pointer before auto code
    //.............................................................................
    featurePrevious_ = NULL_var;

    KTCRequestDelayedDestruction(_pBaseCurveAgent);
    KTCRequestDelayedDestruction(_pBaseCurveFieldAgent);
    catFrmEditor_ = NULL;
    if (core) delete core;
    if (parameter) delete parameter;
}
#pragma region VirtualFunction
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::BuildGraph() {

    // declare variable
    HRESULT          hr = S_OK;
    CATUnicodeString msg;

    //.............................................................................
    // KEVIN MANUAL CODE: check Error for conductor
    //.............................................................................

    //.............................................................................
    // KEVIN MANUAL CODE: check mode, then create or update feature.
    //.............................................................................

    //.............................................................................
    // KEVIN MANUAL CODE: check feature or hr. Exit if error.
    //.............................................................................
    if (code_) {
        KTCAutoDialog::ShowMessageBox(code_, msg, dialog);
        RequestDelayedDestruction();
        return;
    }

    // Agent Creation
    _pBaseCurveFieldAgent = new CATDialogAgent("BaseCurveActiveFieldAgent");

    //-----------------------------------------------------------------------------
    // Selection Agents
    //-----------------------------------------------------------------------------

    // _pBaseCurveAgent to select a point
    _pBaseCurveAgent = new CATFeatureImportAgent("BaseCurveAgent", NULL, NULL);
    _pBaseCurveAgent->SetOrderedElementType("CATIMfMonoDimResult");
    _pBaseCurveAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO | CATDlgEngOneShot);

    //.............................................................................
    // KEVIN MANUAL CODE: Initial your PanelState use GetInitialPanelState()
    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and
    // Cancel States.
    //.............................................................................

    // Curve selection state
    CATDialogState* WaitForCurveState = GetInitialPanelState("Select a Curve object");
    WaitForCurveState->AddDialogAgent(_pBaseCurveFieldAgent);
    WaitForCurveState->AddDialogAgent(_pBaseCurveAgent);

    //.............................................................................
    // KEVIN MANUAL CODE: User CATFeatureImportAgent set your code here
    //.............................................................................
    // _pfiaCurrentAxis to select an Axis

    // _fiaBaseCurve to select a curve // face

    //---------------------------------------------------
    // your menu set code:
    //---------------------------------------------------

    //.............................................................................
    // KEVIN MANUAL CODE: Dialog show
    // Here to add update dialog code, maybe can avoid value change agent .
    // Show Dialog here, Maybe you should use SetVisibility to show the dialog.
    // Kevin. 2021-10

    // _pCurveFieldAgent and _pMainDirFieldAgent to change current acquisition type
    CATDlgSelectorList* pList = dialog->_SelectorListBaseCurve;
    if (pList) _pBaseCurveFieldAgent->AcceptOnNotify(pList, pList->GetListSelectNotification());

    //-----------------------------------------------------------------------------
    // Command States
    //-----------------------------------------------------------------------------

    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and Cancel States.

    //-----------------------------------------------------------------------------
    // Transitions
    //-----------------------------------------------------------------------------

    // From Curve to Curve ( click on several curves to change of curve )
    AddTransition(WaitForCurveState, WaitForCurveState, IsOutputSetCondition(_pBaseCurveAgent),
                  Action((ActionMethod)&PNXCurveDivisionCmd::CurveSelected));

    AddTransition(WaitForCurveState, WaitForCurveState, IsOutputSetCondition(_pBaseCurveFieldAgent),
                  Action((ActionMethod)&PNXCurveDivisionCmd::BaseCurveFieldSelected));

    //.............................................................................
    parameter->CheckoutAxis(); // check out grid
    dialog->UpdateDialog();    // Fills in the dialog panel fields.
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCurveDivisionCmd::Activate(CATCommand* iCmd, CATNotification* iNotif) {
    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCurveDivisionCmd::Cancel(CATCommand* iCmd, CATNotification* iNotif) {
    return CATMMUIPanelStateCmd::Cancel(iCmd, iNotif);
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::CancelAction(void*) {
    // Unset Repeat mode  when cancel or close is clicked
    if (catFrmEditor_) catFrmEditor_->UnsetRepeatedCommand();
    return TRUE;
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCurveDivisionCmd::Deactivate(CATCommand* iCmd, CATNotification* iNotif) {
    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::ElementSelected(CATFeatureImportAgent* pAgent) {
    cout << "### " << __FUNCTION__ << endl;

    if (NULL == pAgent || NULL == parameter) return;

    // translates the selection into the good pointer on a CATBaseUnknwon model element
    CATBaseUnknown* pSelection = pAgent->GetElementValue(pAgent->GetValue());

    if (NULL != pSelection) {
        // gets a pointer on CATISpecObject for this element
        CATISpecObject_var specOnSelection = NULL_var;
        HRESULT rc = pSelection->QueryInterface(IID_CATISpecObject, (void**)&specOnSelection);
        if (FAILED(rc)) {
            cout << " rc is failed" << endl;
            return;
        }

        if (parameter->BaseCurve == specOnSelection) // same one
            parameter->BaseCurve = NULL_var;         // erases the selection
        else
            parameter->BaseCurve = specOnSelection; // other one

        // updates the text corresponding to the feature names in the panel fields
        if (dialog) {
            dialog->UpdateDialog();
        }
    }

    return;
}
//-----------------------------------------------------------------------------
int PNXCurveDivisionCmd::GetMode() {
    // This very simple methods checks if the user is creating or editing the
    // User Feature. This data is used by father command CATMMUIPanelStateCommand
    // and by CATPrtUpdateCom. They both provide standard edition command
    // behaviour : for example, it is not possible to create a sick User Feature ( a
    // User Feature generating an error )

    // CATModeCreation 1	:Creation mode
    // CATModeEdit 0		: edit mode
    return 1;
}
//-----------------------------------------------------------------------------
CATDlgDialog* PNXCurveDivisionCmd::GiveMyPanel() {
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return dialog;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::OkAction(void*) {
    // cout << "### " << __FUNCTION__ << endl;

    //
    // Get infors and set to feature
    // do not use AfterValueChange()
    //

    EmptySO();                         // 0. Empty SO
    if (dialog) dialog->UpdateInfos(); // 1. update param

    cout << "- Your code here" << endl;

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::CurveSelected(void*) {
    cout << "I am in CurveSelected(void *)" << endl;

    // checks if the selected object must be added ( not  selected yet ) or removed ( already
    // selected ) as input curve
    ElementSelected(_pBaseCurveAgent);

    // gets ready for next acquisition
    _pBaseCurveAgent->InitializeAcquisition();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::BaseCurveFieldSelected(void*) {
    static int a = 0;
    cout << "I am in BaseCurveFieldSelected(void *)" << a++ << endl;
    // put the focus on the first field of the Combined Curve edition dialog box
    // ( first curve ) and highlight the corresponding geometrical element
    // SetActiveField(PNXCopyStudyFieldBaseCurve);

    // gets ready for next acquisition
    _pBaseCurveFieldAgent->InitializeAcquisition();

    return TRUE;
}

//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::PreviewAction(void*) {
    // cout << "### " << __FUNCTION__ << endl;
    if (!core || !parameter) return FALSE;

    //
    // 1- information
    //
    dialog->UpdateInfos(); // refresh information

    code_ = core->pretreat();
    if (0 == code_) code_ = core->calculate();

    dialog->UpdateDialog(); // updates all the param to the panel

    // Show error if any
    KTCAutoDialog::ShowMessageBox(code_, parameter->message, dialog);
    return TRUE;
}

#pragma endregion VirtualFunction

//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::ActionSelectorListFia(void* data) {
    // int field = CATPtrToINT32(data);
    // // cout << "### " << __FUNCTION__ << endl;

    // // endl;

    // KTC::ValueActionMode mode = dialog->GetValueMode();

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD ACTION FIA

    // clang-format off
    //.............................................................................
    // @key    CmdActionFia
    // @usage  put this code block into the function Cmd::ActionSelectorListFia()
    // @brief  Action object selected
    //.............................................................................
    // Field count = 0
    int count = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision CMD ACTION FIA

    //.............................................................................
    // KEVIN MANUAL CODE: set next field. No action for this project
    //.............................................................................

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::ActionSelectorListPda(void* data) {
    int field = CATPtrToINT32(data);
    // cout << "### " << __FUNCTION__ << endl;

    // endl;

    bool fieldChange = 0; // (dialog->GetActiveField() != field);
    if (fieldChange) {
        // dialog->SetActiveField(field);
        // dialog->SetActiveFieldFocus();
    }

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD ACTION PDA

    // clang-format off
    //.............................................................................
    // @key    CmdActionPda
    // @usage  put this code block into the function Cmd::ActionSelectorListPda()
    // @brief  InitializeAcquisition and HSO Append
    //.............................................................................
    // Field count = 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision CMD ACTION PDA

    if (fieldChange) fiaAgentUpdate();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::ActionValueChange(void*) {
    // gets ready for next acquisition
    daValueChange_->InitializeAcquisition();

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::AfterValueChange(bool isUpdateObj) {
    cout << "### " << __FUNCTION__ << endl;

    dialog->UpdateInfos(); // refresh information

    // your other code here
    dialog->UpdateDialog(); // updates all the param to the panel
}
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::fiaAgentClear() {
    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD AGENT FIA CLEAR

    // clang-format off
    //.............................................................................
    // @key    CmdAgentFiaClear
    // @usage  put this code block into the function Cmd::fiaAgentClear()
    // @brief  clear select state
    //.............................................................................

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision CMD AGENT FIA CLEAR
}
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::fiaAgentUpdate() {
    int field = 0; // dialog->GetActiveField(); // get active Field

    fiaAgentClear(); // clear first

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD AGENT UPDATE STATE

    // clang-format off
    //.............................................................................
    // @key    CmdAgentUpdateState
    // @usage  put this code block into the function Cmd::fiaAgentUpdate()
    // @brief  Update select state
    //.............................................................................
    // Field count = 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision CMD AGENT UPDATE STATE
}
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::SetActiveField(PNXCurveDivisionField field) {

    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    // dialog->SetActiveField(field); // puts the focus on the Active Field is the
    //                                // User Feature edition dialog box
    // dialog->SetActiveFieldFocus(); // Focus

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD SET ACTIVE FIELD

    // clang-format off
    //.............................................................................
    // @key    CmdSetActiveField
    // @usage  put this code block into the function Cmd::SetActiveField()
    // @brief  Set Active Field, clear other field, update select agent...
    //.............................................................................
    // Field count = 0

    KT_AUTO_HSO_CLEAR();

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision CMD SET ACTIVE FIELD

    fiaAgentUpdate(); // update the Agent
}
