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
#include "CATIDescendants.h" // needed to aggregate the newly created Sound Hole
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
#include "CATIVisProperties.h" // needed to change Sound Hole's graphical appearance
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

// end
{
    // cout <<"PNXCurveDivisionCmd::PNXCurveDivisionCmd" << endl;

    // create parameter
    parameter = new PNXCurveDivisionParam(); // create Default value Instance

    // creates the dialog box
    dialog            = new PNXCurveDivisionDlg();
    dialog->parameter = (parameter); // Pass Value

    // builds the dialog box
    // ! do not call panel->Build from the panel constructor
    dialog->Build();
    _catFrmEditor = CATFrmEditor::GetCurrentEditor();
    // core set
    core                = new PNXCurveDivisionCore(); // Core
    core->parameter     = parameter;                // pass value
    core->_catFrmEditor = _catFrmEditor;            // pass value
}
//-----------------------------------------------------------------------------
PNXCurveDivisionCmd::~PNXCurveDivisionCmd() {
    // cout <<"PNXCurveDivisionCmd::~PNXCurveDivisionCmd" << endl;

    //.............................................................................
    // KEVIN MANUAL CODE: delete pointer before auto code
    //.............................................................................
    _featurePrevious = NULL_var;

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision CMD AGENT DESTRUCTOR
    _catFrmEditor = NULL;
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
    if (FAILED(hr)) {
        if (msg.GetLengthInChar() > 0) {
            cout << msg << endl;
            // KTC::ShowMessageBox(msg, dialog);
        }
        RequestDelayedDestruction();
        return;
    }

    //.............................................................................
    // KEVIN MANUAL CODE: Initial your PanelState use GetInitialPanelState()
    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and
    // Cancel States.
    //.............................................................................
    CATCustomizableState* _catDialogState = GetInitialPanelState("InitialPanelState");

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
    //.............................................................................
    parameter->CheckoutAxis(); // check out grid
    dialog->UpdateDialog();    // Fills in the dialog panel fields.
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCurveDivisionCmd::Activate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "PNXCurveDivisionCmd::Activate" << endl;
    if (NULL_var == _MyFeature) return (CATStatusChangeRCCompleted);

    // Sets the CC as the current feature
    // only in edition mode and if the CC is inside an ordered body
    //

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCurveDivisionCmd::Cancel(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "PNXCurveDivisionCmd::Cancel" << endl;

    return CATMMUIPanelStateCmd::Cancel(iCmd, iNotif);
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::CancelAction(void*) {
    // Unset Repeat mode  when cancel or close is clicked
    if (_catFrmEditor) _catFrmEditor->UnsetRepeatedCommand();
    return TRUE;
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCurveDivisionCmd::Deactivate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "PNXCurveDivisionCmd::Deactivate" << endl;

    // Restores the old current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if (0 == GetMode()) {
    }

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
int PNXCurveDivisionCmd::GetMode() {
    // This very simple methods checks if the user is creating or editing the
    // Sound Hole. This data is used by father command CATMMUIPanelStateCommand
    // and by CATPrtUpdateCom. They both provide standard edition command
    // behaviour : for example, it is not possible to create a sick Sound Hole ( a
    // Sound Hole generating an error )

    // CATModeCreation 1	:Creation mode
    // CATModeEdit 0		: edit mode
    return 1;
}
//-----------------------------------------------------------------------------
CATDlgDialog* PNXCurveDivisionCmd::GiveMyPanel() {
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (dialog);
}
//-----------------------------------------------------------------------------
CATISpecObject_var PNXCurveDivisionCmd::GiveMyFeature() {
    return _MyFeature;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::OkAction(void*) {
    // cout << "PNXCurveDivisionCmd::OkAction" << endl;

    //
    // Get infors and set to feature
    // do not use AfterValueChange()
    //

    EmptySO();             // 0. Empty SO
    dialog->UpdateInfos(); // 1. update param

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::PreviewAction(void*) {
    // cout << "PNXCurveDivisionCmd::PreviewAction" << endl;

    //
    // 1- information
    //
    dialog->UpdateInfos(); // refresh information

    // show rep and warning
    HRESULT hr = core->Calculate();

    dialog->UpdateDialog(); // updates all the param to the panel
    return TRUE;
}

#pragma endregion VirtualFunction

//-----------------------------------------------------------------------------
CATBoolean PNXCurveDivisionCmd::ActionSelectorListFia(void* data) {
    // int field = CATPtrToINT32(data);
    // // cout << "PNXCurveDivisionCmd::ActionSelectorListFia, Field = " << field <<
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
    // cout << "PNXCurveDivisionCmd::ActionSelectorListPda, Field = " << field <<
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
    _daValueChange->InitializeAcquisition();

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
void PNXCurveDivisionCmd::AfterValueChange(bool isUpdateObj) {
    cout << "PNXCurveDivisionCmd::AfterValueChange" << endl;
    dialog->UpdateInfos(); // refresh information

    // your other code here
    dialog->UpdateDialog(); // updates all the param to the panel
}
//-----------------------------------------------------------------------------
HRESULT PNXCurveDivisionCmd::CreateElement() {
    if (NULL_var != _MyFeature) // do not create when exist
        return S_OK;

    if (NULL == core) return E_INVALIDARG;

    HRESULT hr = core->Create(); // create
    if (FAILED(hr)) return hr;

    return S_OK;
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
    //                                // Sound Hole edition dialog box
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
