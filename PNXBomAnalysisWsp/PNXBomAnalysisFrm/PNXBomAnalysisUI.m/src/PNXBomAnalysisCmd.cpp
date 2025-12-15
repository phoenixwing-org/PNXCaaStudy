/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
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
#include "CATIProduct.h"
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
#include "PNXBomAnalysisCmd.h"
#include "PNXBomAnalysisDlg.h"

// PNXBomAnalysisInterfaces Framework

CATCreateClass(PNXBomAnalysisCmd);

//-----------------------------------------------------------------------------
// PNXBomAnalysisCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
PNXBomAnalysisCmd::PNXBomAnalysisCmd()
    : CATMMUIPanelStateCmd("PNXBomAnalysisCommand")

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD AGENT CONSTRUCTOR

    , KT_AUTO_CMD_AGENT_CONSTRUCTOR_COMMON()

// end
{
    // cout <<"PNXBomAnalysisCmd::PNXBomAnalysisCmd" << endl;

    // create parameter
    parameter = new PNXBomAnalysisParam(); // create Default value Instance

    // creates the dialog box
    dialog            = new PNXBomAnalysisDlg();
    dialog->parameter = (parameter); // Pass Value

    // builds the dialog box
    // ! do not call panel->Build from the panel constructor
    dialog->Build();
    _catFrmEditor = CATFrmEditor::GetCurrentEditor();
    // core set
    core                = new PNXBomAnalysisCore(); // Core
    core->parameter     = parameter;                // pass value
    core->_catFrmEditor = _catFrmEditor;            // pass value
}
//-----------------------------------------------------------------------------
PNXBomAnalysisCmd::~PNXBomAnalysisCmd() {
    // cout <<"PNXBomAnalysisCmd::~PNXBomAnalysisCmd" << endl;

    //.............................................................................
    // KEVIN MANUAL CODE: delete pointer before auto code
    //.............................................................................
    _featurePrevious = NULL_var;

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD AGENT DESTRUCTOR
    _catFrmEditor = NULL;
}
#pragma region VirtualFunction
//-----------------------------------------------------------------------------
void PNXBomAnalysisCmd::BuildGraph() {

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
    _catDialogState = GetInitialPanelState("InitialPanelState");

    //.............................................................................
    // KEVIN MANUAL CODE: User CATFeatureImportAgent set your code here
    //.............................................................................
    // _pfiaCurrentAxis to select an Axis

    // _fiaFirstProduct to select a curve // face

    _pfiaElementSelect = new CATFeatureImportAgent("Select Product"); // 创建产品选择代理
    CATLISTV(CATString) typeList1;                                    // 声明类型列表
    typeList1.Append(CATString("CATIProduct"));                       // 添加产品类型
    _pfiaElementSelect->SetOrderedTypeList(typeList1);                // 设置有序类型列表
    _pfiaElementSelect->SetBehavior(CATDlgEngWithPrevaluation |
                                    CATDlgEngWithPSOHSO | // 设置代理行为
                                    CATDlgEngWithTooltip | CATDlgEngOneShot);

    _catDialogState->AddDialogAgent(_pfiaElementSelect); // 添加对话框代理

    AddTransition(_catDialogState, _catDialogState,         // 添加状态转换
                  IsOutputSetCondition(_pfiaElementSelect), // 设置输出条件
                  Action((ActionMethod)&PNXBomAnalysisCmd::ActionSelectorListFia)); // 设置动作方法

    // print json : 1
    AddAnalyseNotificationCB(
        dialog->_PushButtonJson, dialog->_PushButtonJson->GetPushBActivateNotification(),
        (CATCommandMethod)&PNXBomAnalysisCmd::OnOutputBomCB, CATCommandClientData(1));

    // print markdown : 2
    AddAnalyseNotificationCB(dialog->_PushButtonPrintMarkdown,
                             dialog->_PushButtonPrintMarkdown->GetPushBActivateNotification(),
                             (CATCommandMethod)&PNXBomAnalysisCmd::OnOutputBomCB,
                             CATCommandClientData(2));

    //---------------------------------------------------
    // your menu set code:
    //---------------------------------------------------

    //.............................................................................
    // KEVIN MANUAL CODE: Dialog show
    // Here to add update dialog code, maybe can avoid value change agent .
    // Show Dialog here, Maybe you should use SetVisibility to show the dialog.
    // Kevin. 2021-10
    //.............................................................................

    dialog->UpdateDialog(); // Fills in the dialog panel fields.
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXBomAnalysisCmd::Activate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "PNXBomAnalysisCmd::Activate" << endl;
    if (NULL_var == _MyFeature) return (CATStatusChangeRCCompleted);

    // Sets the CC as the current feature
    // only in edition mode and if the CC is inside an ordered body
    //

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXBomAnalysisCmd::Cancel(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "PNXBomAnalysisCmd::Cancel" << endl;

    return CATMMUIPanelStateCmd::Cancel(iCmd, iNotif);
}
//-----------------------------------------------------------------------------
CATBoolean PNXBomAnalysisCmd::CancelAction(void*) {
    // Unset Repeat mode  when cancel or close is clicked
    if (_catFrmEditor) _catFrmEditor->UnsetRepeatedCommand();
    return TRUE;
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXBomAnalysisCmd::Deactivate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "PNXBomAnalysisCmd::Deactivate" << endl;

    // Restores the old current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if (0 == GetMode()) {
    }

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisCmd::GetMode() {
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
CATDlgDialog* PNXBomAnalysisCmd::GiveMyPanel() {
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (dialog);
}
//-----------------------------------------------------------------------------
CATISpecObject_var PNXBomAnalysisCmd::GiveMyFeature() {
    return _MyFeature;
}
//-----------------------------------------------------------------------------
CATBoolean PNXBomAnalysisCmd::OkAction(void*) {
    // cout << "PNXBomAnalysisCmd::OkAction" << endl;

    //
    // Get infors and set to feature
    // do not use AfterValueChange()
    //

    EmptySO();             // 0. Empty SO
    dialog->UpdateInfos(); // 1. update param

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXBomAnalysisCmd::PreviewAction(void*) {
    // cout << "PNXBomAnalysisCmd::PreviewAction" << endl;

    //
    // 1- information
    //
    dialog->UpdateInfos(); // refresh information

    // show rep and warning
    HRESULT hr = core->calculate();

    dialog->UpdateDialog(); // updates all the param to the panel
    return TRUE;
}

#pragma endregion VirtualFunction

//-----------------------------------------------------------------------------
CATBoolean PNXBomAnalysisCmd::ActionSelectorListFia(void*) {
    // cout << "- PNXBomAnalysisCmd::ActionSelectorListFia " << endl;

    if (NULL == _pfiaElementSelect) return CATFalse; // 检查路径元素代理是否有效

    // 获取路径元素
    int             code         = 0; // error code
    CATPathElement* pPathElement = NULL;
    CATBaseUnknown* pBaseUnknown = _pfiaElementSelect->GetElementValue(); // 获取选中的基础对象
    _pfiaElementSelect->InitializeAcquisition();                          // 初始化获取操作
    if (NULL == pBaseUnknown) return CATFalse;                            // 检查有效
    // cout << "- Select BASE element :" << pBaseUnknown << endl;

    if (!parameter) return CATFalse;
    if (!core) return CATFalse;

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD ACTION FIA

    // clang-format off
    //.............................................................................
    // @key    CmdActionFia
    // @usage  put this code block into the function Cmd::ActionSelectorListFia()
    // @brief  Action object selected
    //.............................................................................
    // Field count = 0
    int count = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD ACTION FIA

    //.............................................................................
    // KEVIN MANUAL CODE: set next field. No action for this project
    //.............................................................................

    // gets a pointer on CATISpecObject for this element
    CATISpecObject_var input;
    HRESULT            rc = pBaseUnknown->QueryInterface(IID_CATISpecObject, (void**)&input);
    if (FAILED(rc) || !input) {
        cout << "    - [error] " << (code = 1104) << " : change to CATISpecObject_var error!"
             << endl;
        return CATFalse;
    }

    // cout << "- the input Object->GetDisplayName(): " << input->GetDisplayName() << endl;

    // 切換object
    parameter->FirstProduct =
        parameter->FirstProduct == input ? NULL_var : (parameter->FirstProduct = input);

    // calculate bom list pretreat
    rc = core->pretreat();
    if (FAILED(rc)) {
        cout << "    - [error] " << (code = 1105) << " : core pretreat failed!" << endl;
        return CATFalse;
    }

    // calculate bom
    rc = core->calculate();
    // core->dumpJsonL();

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXBomAnalysisCmd::ActionSelectorListPda(void* data) {
    int field = CATPtrToINT32(data);
    // cout << "PNXBomAnalysisCmd::ActionSelectorListPda, Field = " << field <<
    // endl;

    bool fieldChange = 0; // (dialog->GetActiveField() != field);
    if (fieldChange) {
        // dialog->SetActiveField(field);
        // dialog->SetActiveFieldFocus();
    }

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD ACTION PDA

    // clang-format off
    //.............................................................................
    // @key    CmdActionPda
    // @usage  put this code block into the function Cmd::ActionSelectorListPda()
    // @brief  InitializeAcquisition and HSO Append
    //.............................................................................
    // Field count = 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD ACTION PDA

    if (fieldChange) fiaAgentUpdate();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXBomAnalysisCmd::ActionValueChange(void*) {
    // gets ready for next acquisition
    _daValueChange->InitializeAcquisition();

    AfterValueChange(); // action after value change
    return TRUE;
}
//-----------------------------------------------------------------------------
void PNXBomAnalysisCmd::AfterValueChange(bool isUpdateObj) {
    cout << "PNXBomAnalysisCmd::AfterValueChange" << endl;
    dialog->UpdateInfos(); // refresh information

    // your other code here
    dialog->UpdateDialog(); // updates all the param to the panel
}
//-----------------------------------------------------------------------------
HRESULT PNXBomAnalysisCmd::CreateElement() {
    if (NULL_var != _MyFeature) // do not create when exist
        return S_OK;

    if (NULL == core) return E_INVALIDARG;

    return S_OK;
}
//-----------------------------------------------------------------------------
void PNXBomAnalysisCmd::fiaAgentClear() {
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD AGENT FIA CLEAR

    // clang-format off
    //.............................................................................
    // @key    CmdAgentFiaClear
    // @usage  put this code block into the function Cmd::fiaAgentClear()
    // @brief  clear select state
    //.............................................................................

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD AGENT FIA CLEAR
}
//-----------------------------------------------------------------------------
void PNXBomAnalysisCmd::fiaAgentUpdate() {
    int field = 0; // dialog->GetActiveField(); // get active Field

    fiaAgentClear(); // clear first

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD AGENT UPDATE STATE

    // clang-format off
    //.............................................................................
    // @key    CmdAgentUpdateState
    // @usage  put this code block into the function Cmd::fiaAgentUpdate()
    // @brief  Update select state
    //.............................................................................
    // Field count = 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD AGENT UPDATE STATE
}
//-------------------------------------------------------------------------
void PNXBomAnalysisCmd::OnOutputBomCB(CATCommand* cmd, CATNotification* evt,
                                      CATCommandClientData data) {
    int value = CATPtrToINT32(data);
    cout << "- PNXBomAnalysisCmd::OnOutputBomCB " << value << endl;

    switch (value) {
    case 1: // json
		{
			core->dumpJsonL();
			CATUnicodeString JsonStr = core->OutPutJson();
			dialog->_EditorOutInfo->SetText(JsonStr);
		}
        break;
    case 2: // Markdown
        core->dumpMarkdown();
        break;
        // default:
        // core->dumpJsonL();
    }
}
//-----------------------------------------------------------------------------
void PNXBomAnalysisCmd::SetActiveField(PNXBomAnalysisField field) {

    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    // dialog->SetActiveField(field); // puts the focus on the Active Field is the
    //                                // Sound Hole edition dialog box
    // dialog->SetActiveFieldFocus(); // Focus

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD SET ACTIVE FIELD

    // clang-format off
    //.............................................................................
    // @key    CmdSetActiveField
    // @usage  put this code block into the function Cmd::SetActiveField()
    // @brief  Set Active Field, clear other field, update select agent...
    //.............................................................................
    // Field count = 0

    KT_AUTO_HSO_CLEAR();

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis CMD SET ACTIVE FIELD

    fiaAgentUpdate(); // update the Agent
}
