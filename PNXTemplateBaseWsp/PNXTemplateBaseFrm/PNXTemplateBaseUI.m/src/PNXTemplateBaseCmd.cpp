/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
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
#include "PNXTemplateBaseCmd.h"
#include "PNXTemplateBaseDlg.h"

// Auto Code
#include "KTCAutoIncludeUI.h"

CATCreateClass(PNXTemplateBaseCmd);

//-----------------------------------------------------------------------------
// PNXTemplateBaseCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
PNXTemplateBaseCmd::PNXTemplateBaseCmd()
    : CATMMUIPanelStateCmd("PNXTemplateBaseCommand")

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT CONSTRUCTOR

    // clang-format off
    //.............................................................................
    // @key    CmdAgentConstructor
    //.............................................................................
    , KT_AUTO_CMD_AGENT_CONSTRUCTOR_COMMON()
    , KT_AUTO_CMD_AGENT_CONSTRUCTOR_FIELD(MyCurve)
    , KT_AUTO_CMD_AGENT_CONSTRUCTOR_FIELD(MyFaces)

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT CONSTRUCTOR

    , _featurePrevious(NULL_var)
    , _catISO(NULL)

// end
{
    // cout <<"### " << __FUNCTION__ << endl;

    _MyFeature = NULL_var;

    // create parameter
    parameter = new PNXTemplateBaseParam(); // create Default value Instance

    if (!!feature) {
        // _mode      = 0; // Edition mode.
        _MyFeature = feature;
    }
    // creates the dialog box
    dialog            = new PNXTemplateBaseDlg(this);
    dialog->parameter = (parameter); // Pass Value

    // builds the dialog box
    // ! do not call panel->Build from the panel constructor
    dialog->Build();

    // To manage the highlight of the Sound Hole and the UI active object that
    // is used to put the Sound Hole at the right place.
    _catFrmEditor = CATFrmEditor::GetCurrentEditor();
    _catHSO       = NULL;
    if (NULL != _catFrmEditor) {
        _catHSO = _catFrmEditor->GetHSO();
        _catISO = _catFrmEditor->GetISO();

        _catISO->Empty();
    }
    else {
        _code = 1;
    }

    // core set
    core                  = new PNXTemplateBaseCore(); // Core
    core->parameter       = parameter;                 // pass value
    core->_catFrmEditor   = _catFrmEditor;             // pass value
    core->_catISO         = _catISO;                   // pass value
    core->_featureCurrent = GetCurrentFeature();       // pass value
    core->feature         = _MyFeature;                // pass value
}
//-----------------------------------------------------------------------------
PNXTemplateBaseCmd::~PNXTemplateBaseCmd() {
    // cout <<"### " << __FUNCTION__ << endl;

    //.............................................................................
    // KEVIN MANUAL CODE: delete pointer before auto code
    //.............................................................................
    _featurePrevious = NULL_var;

    KTCEmpty(_catISO); // Empty and set NULL

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT DESTRUCTOR

    // clang-format off
    //.............................................................................
    // @key    CmdAgentDestructor
    //.............................................................................
    // Field count = 2
    KT_AUTO_CMD_AGENT_DESTRUCTOR_FIELD(MyCurve);
    KT_AUTO_CMD_AGENT_DESTRUCTOR_FIELD(MyFaces);

    // place at the end
    KT_AUTO_CMD_AGENT_DESTRUCTOR_COMMON();

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT DESTRUCTOR
}
#pragma region VirtualFunction
//-----------------------------------------------------------------------------
void PNXTemplateBaseCmd::BuildGraph() {

    // declare variable
    HRESULT          hr = S_OK;
    CATUnicodeString msg;

    //.............................................................................
    // KEVIN MANUAL CODE: check Error for conductor
    //.............................................................................
    if (_code > 0) {
        msg = " Error conductor. Exit!";
        hr  = E_FAIL;
    }

    //.............................................................................
    // KEVIN MANUAL CODE: check mode, then create or update feature.
    //.............................................................................

    //.............................................................................
    // KEVIN MANUAL CODE: check feature or hr. Exit if error.
    //.............................................................................

    //.............................................................................
    // KEVIN MANUAL CODE: Initial your PanelState use GetInitialPanelState()
    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and
    // Cancel States.
    //.............................................................................
    _catDialogState = GetInitialPanelState("InitialPanelState");

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT BUILD GRAPH

    // clang-format off
    //.............................................................................
    // @key    CmdAgentBuildGraph
    // @usage  put this code block into the function Cmd::BuildGraph()
    // @brief  set agent, AddTransition
    // RegisterFiled() will set suggested menu id by input name. You can change it later
    //.............................................................................

    // Build Start .......................
    KT_AUTO_CMD_BUILD_START(PNXTemplateBase);

    // Field count = 2

    // Field 1 MyCurve .......................
    // 1.1 define fia
    KT_AUTO_CMD_BUILD_FIA_CURVE(MyCurve);
    // 1.2 others
    KT_AUTO_CMD_BUILD_FIELD(PNXTemplateBase, MyCurve); 

    // Field 2 MyFaces .......................
    // 2.1 define fia
    KT_AUTO_CMD_BUILD_FIA_FACE(MyFaces);
    // 2.2 others
    KT_AUTO_CMD_BUILD_FIELD(PNXTemplateBase, MyFaces);

    // Build End .......................
    KT_AUTO_CMD_BUILD_END(PNXTemplateBase);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT BUILD GRAPH

    //.............................................................................
    // KEVIN MANUAL CODE: User CATFeatureImportAgent set your code here
    //.............................................................................

    // _fiaMyFaces to select faces
    _fiaMyFaces->SetOrderedElementType("CATIMfBiDimResult");
    //_fiaMyCurve->AddOrderedElementType("CATSurface");
    //_fiaMyCurve->AddOrderedElementType("CATFace");
    //_fiaMyCurve->AddOrderedElementType("CATShell");

    // _fiaMyCurve to select a curve // face
    _fiaMyCurve->SetOrderedElementType("CATIMfMonoDimResult");

    UpdatefiaSelectFaces(); // to update _fiaMyFaces

    //---------------------------------------------------
    // your menu set code:
    //---------------------------------------------------

    //---------------------------------------------------
    // Setting an ID to be able to read the created import
    //---------------------------------------------------
    GUID guid = {// {795D00E4-5187-4c4f-89F0-8FD2FAD6CB3D}
                 0x795d00e4,
                 0x5187,
                 0x4c4f,
                 {0x89, 0xf0, 0x8f, 0xd2, 0xfa, 0xd6, 0xcb, 0x3d}};

    _fiaMyFaces->SetImportApplicativeId(guid);

    //.............................................................................
    // KEVIN MANUAL CODE: Dialog show
    // Here to add update dialog code, maybe can avoid value change agent .
    // Show Dialog here, Maybe you should use SetVisibility to show the dialog.
    // Kevin. 2021-10
    //.............................................................................
    parameter->CheckoutAxis(); // check out grid
    dialog->UpdateDialog();    // Fills in the dialog panel fields.

    // set active field
    if (NULL_var == parameter->MyCurve)
        SetActiveField(Field_PNXTemplateBase_MyCurve);
    else
        SetActiveField(Field_PNXTemplateBase_MyFaces);

    core->show_rep(); // show  rep
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXTemplateBaseCmd::Activate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    if (NULL_var == _MyFeature) return (CATStatusChangeRCCompleted);

    // if exist dialog
    if (dialog) {
        // teat returned sub command, 0 for no Sub Command
        int out = dialog->ActionSubCommandReturn();
        if (0 != out) {
            if (out > 0) {
                // your code here for value change.
                AfterValueChange();
            }

            // if out < 0 , means no action or failed.
            return (CATStatusChangeRCCompleted);
        }

        // if out == 0 , go on the following steps
    }

    // Sets the CC as the current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if ((NULL != iNotif) && (0 == GetMode())) {
        bool isOrdered = KTCAutoGSM::IsInsideOrderedBody(_MyFeature);
        if (isOrdered) {
            // In case of first activation, SetTemplateBaseAsCurrentFeature will
            // keep the feature to restore at the end of the command

            if (((CATStateActivateNotification*)iNotif)->GetType() ==
                CATStateActivateNotification::Begin) {
                // GetCurrentFeature is a method of CATMMUIStateCommand
                _featurePrevious = GetCurrentFeature();
            }

            // Sets the CC as current - method of CATMMUIStateCommand
            SetCurrentFeature(_MyFeature);
        }
    }
    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXTemplateBaseCmd::Cancel(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    bool isOrdered = KTCAutoGSM::IsInsideOrderedBody(_MyFeature);

    // Restores the old current feature in edition mode
    // and if the CC is inside an ordered body
    if ((0 == GetMode()) && isOrdered) {
        // method of CATMMUIStateCommand
        SetCurrentFeature(_featurePrevious);
    }

    // Set the newly CC as the current feature in creation mode
    // and if the CC is inside an ordered body
    if ((1 == GetMode()) && isOrdered && (NULL_var != _MyFeature)) {
        // Sets the CC as current - method of CATMMUIStateCommand
        SetCurrentFeature(_MyFeature);
    }

    return CATMMUIPanelStateCmd::Cancel(iCmd, iNotif);
}
//-----------------------------------------------------------------------------
CATBoolean PNXTemplateBaseCmd::CancelAction(void*) {
    // Unset Repeat mode  when cancel or close is clicked
    if (_catFrmEditor) _catFrmEditor->UnsetRepeatedCommand();
    return TRUE;
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXTemplateBaseCmd::Deactivate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    // Restores the old current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if (0 == GetMode()) {

        bool isOrdered = KTCAutoGSM::IsInsideOrderedBody(_MyFeature);
        if (isOrdered) {
            // method of CATMMUIStateCommand
            SetCurrentFeature(_featurePrevious);
        }
    }

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseCmd::GetMode() {
    // This very simple methods checks if the user is creating or editing the
    // Sound Hole. This data is used by father command CATMMUIPanelStateCommand
    // and by CATPrtUpdateCom. They both provide standard edition command
    // behaviour : for example, it is not possible to create a sick Sound Hole ( a
    // Sound Hole generating an error )

    // CATModeCreation 1	:Creation mode
    // CATModeEdit 0		: edit mode
    return _mode;
}
//-----------------------------------------------------------------------------
CATDlgDialog* PNXTemplateBaseCmd::GiveMyPanel() {
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (dialog);
}
//-----------------------------------------------------------------------------
CATISpecObject_var PNXTemplateBaseCmd::GiveMyFeature() {
    return _MyFeature;
}
//-----------------------------------------------------------------------------
CATBoolean PNXTemplateBaseCmd::OkAction(void*) {
    // cout << "### " << __FUNCTION__ << endl;

    //
    // Get infors and set to feature
    // do not use AfterValueChange()
    //

    EmptySO();             // 0. Empty SO
    dialog->UpdateInfos(); // 1. update param
    // KTCAutoObject::update(_MyFeature, false); // 3. Updates, do not warning

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXTemplateBaseCmd::PreviewAction(void*) {
    // cout << "### " << __FUNCTION__ << endl;

    //
    // 1- information
    //
    dialog->UpdateInfos(); // refresh information

    // show rep and warning
    HRESULT hr = core->calculate();

    //
    // 2- Updates
    //
    // feature->SetParams(*parameter);
    // KTCAutoObject::update(_MyFeature, false);

    dialog->UpdateDialog(); // updates all the param to the panel
    return TRUE;
}

#pragma endregion VirtualFunction

//-----------------------------------------------------------------------------
CATBoolean PNXTemplateBaseCmd::ActionSelectorListFia(void* data) {
    int field = CATPtrToINT32(data);
    // cout << "### " << __FUNCTION__ << endl;

    // << endl;

    KTC::ValueActionMode mode = dialog->GetValueMode();

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD ACTION FIA

    // clang-format off
    //.............................................................................
    // @key    CmdActionFia
    // @usage  put this code block into the function Cmd::ActionSelectorListFia()
    // @brief  Action object selected
    //.............................................................................
    // Field count = 2
    int count = 0;
    switch (field) {
    case Field_PNXTemplateBase_MyCurve:
        KT_AUTO_CMD_ACTION_FIA(MyCurve);
        break;
    case Field_PNXTemplateBase_MyFaces:
        KT_AUTO_CMD_ACTION_FIA(MyFaces);
        break;
    }
    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD ACTION FIA

    //.............................................................................
    // KEVIN MANUAL CODE: set next field. No action for this project
    //.............................................................................

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXTemplateBaseCmd::ActionSelectorListPda(void* data) {
    int field = CATPtrToINT32(data);
    // cout << "### " << __FUNCTION__ << endl;

    // << endl;

    bool fieldChange = (dialog->GetActiveField() != field);
    if (fieldChange) {
        dialog->SetActiveField(field);
        dialog->SetActiveFieldFocus();
    }

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD ACTION PDA

    // clang-format off
    //.............................................................................
    // @key    CmdActionPda
    // @usage  put this code block into the function Cmd::ActionSelectorListPda()
    // @brief  InitializeAcquisition and HSO Append
    //.............................................................................
    // Field count = 2
    if (fieldChange) KT_AUTO_HSO_CLEAR();
    switch (field) {
    case Field_PNXTemplateBase_MyCurve:
        KT_AUTO_CMD_ACTION_PDA(MyCurve);
        break;
    case Field_PNXTemplateBase_MyFaces:
        KT_AUTO_CMD_ACTION_PDA(MyFaces);
        break;
    }

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD ACTION PDA

    if (fieldChange) fiaAgentUpdate();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXTemplateBaseCmd::ActionValueChange(void*) {
    // gets ready for next acquisition
    _daValueChange->InitializeAcquisition();

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
void PNXTemplateBaseCmd::AfterValueChange(bool isUpdateObj) {
    // cout << "### " << __FUNCTION__ << endl;

    dialog->UpdateInfos();           // refresh information
    if (UpdatefiaSelectFaces() == 1) // only change Select mode
        return;

    parameter->FinishCalc = 0;

    // your other code here
    core->show_rep();       // show rep
    dialog->UpdateDialog(); // updates all the param to the panel
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateBaseCmd::CreateElement() {
    if (NULL_var != _MyFeature) // do not create when exist
        return S_OK;

    if (NULL == core) return E_INVALIDARG;

    HRESULT hr = core->create(); // create
    if (FAILED(hr)) return hr;

    if (NULL_var == core->feature) return E_FAIL;

    _MyFeature = core->feature; // get my feature;
    return S_OK;
}
//-----------------------------------------------------------------------------
void PNXTemplateBaseCmd::fiaAgentClear() {
    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT FIA CLEAR

    // clang-format off
    //.............................................................................
    // @key    CmdAgentFiaClear
    // @usage  put this code block into the function Cmd::fiaAgentClear()
    // @brief  clear select state
    //.............................................................................
    KT_AUTO_CMD_ACTION_FIA_CLEAR(MyCurve);
    KT_AUTO_CMD_ACTION_FIA_CLEAR(MyFaces);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT FIA CLEAR
}
//-----------------------------------------------------------------------------
void PNXTemplateBaseCmd::fiaAgentUpdate() {
    int field = dialog->GetActiveField(); // get active Field

    fiaAgentClear(); // clear first

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT UPDATE STATE

    // clang-format off
    //.............................................................................
    // @key    CmdAgentUpdateState
    // @usage  put this code block into the function Cmd::fiaAgentUpdate()
    // @brief  Update select state
    //.............................................................................
    // Field count = 2
    switch (field) {
    case Field_PNXTemplateBase_MyCurve:
        KT_AUTO_CMD_AGENT_UPDATE_STATE(MyCurve);
        break;
    case Field_PNXTemplateBase_MyFaces:
        KT_AUTO_CMD_AGENT_UPDATE_STATE(MyFaces);
        break;
    case 0:
        KT_AUTO_CMD_AGENT_UPDATE_STATE_ERROR();
    }

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT UPDATE STATE
}
//-----------------------------------------------------------------------------
void PNXTemplateBaseCmd::SetActiveField(PNXTemplateBaseField field) {

    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    dialog->SetActiveField(field); // puts the focus on the Active Field is the
                                   // Sound Hole edition dialog box
    dialog->SetActiveFieldFocus(); // Focus

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD SET ACTIVE FIELD

    // clang-format off
    //.............................................................................
    // @key    CmdSetActiveField
    // @usage  put this code block into the function Cmd::SetActiveField()
    // @brief  Set Active Field, clear other field, update select agent...
    //.............................................................................
    // Field count = 2

    KT_AUTO_HSO_CLEAR();
    switch (field) {
    case Field_PNXTemplateBase_MyCurve:
        KT_AUTO_HSO_ADD(MyCurve);
        break;
    case Field_PNXTemplateBase_MyFaces:
        KT_AUTO_HSO_ADD(MyFaces);
        break;
    default:
        break;
    }

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD SET ACTIVE FIELD

    fiaAgentUpdate(); // update the Agent
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseCmd::UpdatefiaSelectFaces() {
    // check, if same, nothing to do
    // KTC_UPDATE_SELECT_MODE_FACES_SOLID(parameter->SelectMode, _fiaMyFaces);
    return 0;
}
