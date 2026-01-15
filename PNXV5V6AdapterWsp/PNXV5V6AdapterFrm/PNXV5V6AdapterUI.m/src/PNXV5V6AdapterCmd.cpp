/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
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
#include "PNXV5V6AdapterCmd.h"
#include "PNXV5V6AdapterDlg.h"

#include "KTCAutoCode.h"
#include "KTCAutoDefine.h"

// PNXV5V6AdapterInterfaces Framework

CATCreateClass(PNXV5V6AdapterCmd);

//-----------------------------------------------------------------------------
// PNXV5V6AdapterCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
PNXV5V6AdapterCmd::PNXV5V6AdapterCmd()
    : CATMMUIPanelStateCmd("PNXV5V6AdapterCommand")

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD AGENT CONSTRUCTOR

    , KT_AUTO_CMD_AGENT_CONSTRUCTOR_COMMON()
    , _pBaseCurveAgent(NULL)
    , _pBaseCurveFieldAgent(NULL)

// end
{
    // cout <<"### " << __FUNCTION__ << endl;

    // create parameter
    parameter = new PNXV5V6AdapterParam(); // create Default value Instance

    // creates the dialog box
    dialog            = new PNXV5V6AdapterDlg();
    dialog->parameter = (parameter); // Pass Value

    // builds the dialog box
    // ! do not call panel->Build from the panel constructor
    dialog->Build();
    catFrmEditor_ = CATFrmEditor::GetCurrentEditor();
    // core set
    core                = new PNXV5V6AdapterCore(); // Core
    core->parameter     = parameter;                // pass value
    core->catFrmEditor_ = catFrmEditor_;            // pass value
}
//-----------------------------------------------------------------------------
PNXV5V6AdapterCmd::~PNXV5V6AdapterCmd() {
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
void PNXV5V6AdapterCmd::BuildGraph() {

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
    if (FAILED(hr)) {
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
                  Action((ActionMethod)&PNXV5V6AdapterCmd::CurveSelected));

    AddTransition(WaitForCurveState, WaitForCurveState, IsOutputSetCondition(_pBaseCurveFieldAgent),
                  Action((ActionMethod)&PNXV5V6AdapterCmd::BaseCurveFieldSelected));

    //.............................................................................
    parameter->CheckoutAxis(); // check out grid
    dialog->UpdateDialog();    // Fills in the dialog panel fields.
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXV5V6AdapterCmd::Activate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    if (NULL_var == _MyFeature) return (CATStatusChangeRCCompleted);

    // Sets the CC as the current feature
    // only in edition mode and if the CC is inside an ordered body
    //

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXV5V6AdapterCmd::Cancel(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    return CATMMUIPanelStateCmd::Cancel(iCmd, iNotif);
}
//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::CancelAction(void*) {
    // Unset Repeat mode  when cancel or close is clicked
    if (catFrmEditor_) catFrmEditor_->UnsetRepeatedCommand();
    return TRUE;
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXV5V6AdapterCmd::Deactivate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    // Restores the old current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if (0 == GetMode()) {
    }

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
void PNXV5V6AdapterCmd::ElementSelected(CATFeatureImportAgent* pAgent) {
    // cout << "### " << __FUNCTION__ << endl;

    if (NULL == pAgent || NULL == parameter) return;

    // translates the selection into the good pointer on a CATBaseUnknown model element
    CATBaseUnknown* pSelection = pAgent->GetElementValue(pAgent->GetValue());

    if (NULL != pSelection) {
        // gets a pointer on CATISpecObject for this element
        CATISpecObject_var specOnSelection = NULL_var;
        HRESULT hr = pSelection->QueryInterface(IID_CATISpecObject, (void**)&specOnSelection);
        if (FAILED(hr)) {
            cout << " hr is failed" << endl;
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
int PNXV5V6AdapterCmd::GetMode() {
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
CATDlgDialog* PNXV5V6AdapterCmd::GiveMyPanel() {
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (dialog);
}
//-----------------------------------------------------------------------------
CATISpecObject_var PNXV5V6AdapterCmd::GiveMyFeature() {
    return _MyFeature;
}
//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::OkAction(void*) {
    // cout << "### " << __FUNCTION__ << endl;

    //
    // Get infors and set to feature
    // do not use AfterValueChange()
    //

    EmptySO();                         // 0. Empty SO
    if (dialog) dialog->UpdateInfos(); // 1. update param

    if (parameter) {
        // parameter->dump();
        // cout << "TODO : create divided point objects" << endl;
    }

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::CurveSelected(void*) {
    // cout << "I am in CurveSelected(void *)" << endl;

    // checks if the selected object must be added ( not  selected yet ) or removed ( already
    // selected ) as input curve
    ElementSelected(_pBaseCurveAgent);

    // gets ready for next acquisition
    _pBaseCurveAgent->InitializeAcquisition();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::BaseCurveFieldSelected(void*) {
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
CATBoolean PNXV5V6AdapterCmd::ApplyAction(void*) {
    cout << "### " << __FUNCTION__ << endl;

    //
    // 1- information
    //
    dialog->UpdateInfos(); // refresh information

    // show rep and warning
    int code = core->adapter();

    dialog->UpdateDialog(); // updates all the param to the panel
    return TRUE;
}

#pragma endregion VirtualFunction

//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::ActionSelectorListFia(void* data) {
    // int field = CATPtrToINT32(data);
    // // cout << "### " << __FUNCTION__ << endl;

    // // endl;

    // KTC::ValueActionMode mode = dialog->GetValueMode();

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD ACTION FIA

    // clang-format off
    //.............................................................................
    // @key    CmdActionFia
    // @usage  put this code block into the function Cmd::ActionSelectorListFia()
    // @brief  Action object selected
    //.............................................................................
    // Field count = 0
    int count = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD ACTION FIA

    //.............................................................................
    // KEVIN MANUAL CODE: set next field. No action for this project
    //.............................................................................

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::ActionSelectorListPda(void* data) {
    int field = CATPtrToINT32(data);
    // cout << "### " << __FUNCTION__ << endl;

    // endl;

    bool fieldChange = 0; // (dialog->GetActiveField() != field);
    if (fieldChange) {
        // dialog->SetActiveField(field);
        // dialog->SetActiveFieldFocus();
    }

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD ACTION PDA

    // clang-format off
    //.............................................................................
    // @key    CmdActionPda
    // @usage  put this code block into the function Cmd::ActionSelectorListPda()
    // @brief  InitializeAcquisition and HSO Append
    //.............................................................................
    // Field count = 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD ACTION PDA

    if (fieldChange) fiaAgentUpdate();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXV5V6AdapterCmd::ActionValueChange(void*) {
    // gets ready for next acquisition
    _daValueChange->InitializeAcquisition();

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
void PNXV5V6AdapterCmd::AfterValueChange(bool isUpdateObj) {
    // cout << "### " << __FUNCTION__ << endl;

    dialog->UpdateInfos(); // refresh information

    // your other code here
    dialog->UpdateDialog(); // updates all the param to the panel
}
//-----------------------------------------------------------------------------
void PNXV5V6AdapterCmd::fiaAgentClear() {
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD AGENT FIA CLEAR

    // clang-format off
    //.............................................................................
    // @key    CmdAgentFiaClear
    // @usage  put this code block into the function Cmd::fiaAgentClear()
    // @brief  clear select state
    //.............................................................................

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD AGENT FIA CLEAR
}
//-----------------------------------------------------------------------------
void PNXV5V6AdapterCmd::fiaAgentUpdate() {
    int field = 0; // dialog->GetActiveField(); // get active Field

    fiaAgentClear(); // clear first

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD AGENT UPDATE STATE

    // clang-format off
    //.............................................................................
    // @key    CmdAgentUpdateState
    // @usage  put this code block into the function Cmd::fiaAgentUpdate()
    // @brief  Update select state
    //.............................................................................
    // Field count = 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD AGENT UPDATE STATE
}
//-----------------------------------------------------------------------------
void PNXV5V6AdapterCmd::SetActiveField(PNXV5V6AdapterField field) {

    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    // dialog->SetActiveField(field); // puts the focus on the Active Field is the
    //                                // User Feature edition dialog box
    // dialog->SetActiveFieldFocus(); // Focus

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD SET ACTIVE FIELD

    // clang-format off
    //.............................................................................
    // @key    CmdSetActiveField
    // @usage  put this code block into the function Cmd::SetActiveField()
    // @brief  Set Active Field, clear other field, update select agent...
    //.............................................................................
    // Field count = 0

    KT_AUTO_HSO_CLEAR();

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter CMD SET ACTIVE FIELD

    fiaAgentUpdate(); // update the Agent
}
