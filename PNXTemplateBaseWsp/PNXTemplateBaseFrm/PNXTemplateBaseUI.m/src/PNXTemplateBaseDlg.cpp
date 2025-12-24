/**
 * @copyright   Copyright 2021 Kevin Time Toolkit
 * @license      MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

// ApplicationFrame Framework
#include "CATApplicationFrame.h" // needed to get the window of the frame
// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"

// Visualization Framework
#include "iostream.h"

// auto code
#include "KTCAutoIncludeUI.h"

// Local Framework
#include "PNXTemplateBaseDlg.h"

//-------------------------------------------------------------------------
PNXTemplateBaseDlg::PNXTemplateBaseDlg(CATMMUIPanelStateCmd* iFatherCmd)
    // clang-format off
    : KTCAutoDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), iFatherCmd,
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXTemplateBaseDlg",CATDlgWndBtnOKCancelPreview|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                    // clang-format on
                    )
    , dialogMore(NULL)
    , parameter(NULL) {

    // clang-format off
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _FrameParams = NULL;
 _LabelMyCurve = NULL;
 _SelectorListMyCurve = NULL;
 _LabelMyResult = NULL;
 _EditorMyResult = NULL;
 _FrameMyFaces = NULL;
 _LabelMyFaces = NULL;
 _PushButtonOption = NULL;
 _Separator003 = NULL;
 _SelectorListMyFaces = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on

    dialogMore = new PNXTemplateBaseParamDlg(this); // new one
}
//-------------------------------------------------------------------------
PNXTemplateBaseDlg::~PNXTemplateBaseDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameParams = NULL;
 _LabelMyCurve = NULL;
 _SelectorListMyCurve = NULL;
 _LabelMyResult = NULL;
 _EditorMyResult = NULL;
 _FrameMyFaces = NULL;
 _LabelMyFaces = NULL;
 _PushButtonOption = NULL;
 _Separator003 = NULL;
 _SelectorListMyFaces = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on

    parameter = NULL;                         // not delete
    KTCRequestDelayedDestruction(dialogMore); // DESTRUCTOR
}
//-------------------------------------------------------------------------
void PNXTemplateBaseDlg::Build() {
    // Creates the menu bar with default menus
    // KTCDlgBarMenu* menuBar = KTCAutoDialog::GetMenuBarSingleton();

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridRowResizable(1,1);
 SetGridColumnResizable(0,1);
 _FrameParams = new CATDlgFrame(this, "FrameParams", CATDlgFraNoFrame|CATDlgGridLayout);
_FrameParams -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _FrameParams -> SetGridColumnResizable(1,1);
 _LabelMyCurve = new CATDlgLabel(_FrameParams, "LabelMyCurve");
_LabelMyCurve -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListMyCurve = new CATDlgSelectorList(_FrameParams, "SelectorListMyCurve");
 _SelectorListMyCurve -> SetVisibleTextHeight(1);
_SelectorListMyCurve -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _LabelMyResult = new CATDlgLabel(_FrameParams, "LabelMyResult");
_LabelMyResult -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _EditorMyResult = new CATDlgEditor(_FrameParams, "EditorMyResult", CATDlgEdtFloat|CATDlgEdtReadOnly);
 _EditorMyResult -> SetVisibleTextHeight(1);
_EditorMyResult -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _FrameMyFaces = new CATDlgFrame(this, "FrameMyFaces", CATDlgFraNoFrame|CATDlgGridLayout);
_FrameMyFaces -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameMyFaces -> SetGridColumnResizable(1,1);
 _LabelMyFaces = new CATDlgLabel(_FrameMyFaces, "LabelMyFaces");
_LabelMyFaces -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _PushButtonOption = new CATDlgPushButton(_FrameMyFaces, "PushButtonOption");
_PushButtonOption -> SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES);
 _Separator003 = new CATDlgSeparator(_FrameMyFaces, "Separator003");
_Separator003 -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES|CATGRID_CST_HEIGHT);
 _SelectorListMyFaces = new CATDlgSelectorList(this, "SelectorListMyFaces");
 _SelectorListMyFaces -> SetVisibleTextHeight(6);
_SelectorListMyFaces -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // clang-format off
//CAA2 WIZARD CALLBACK DECLARATION SECTION

//END CAA2 WIZARD CALLBACK DECLARATION SECTION
    // clang-format on

    dialogMore->Build(); // Build
    BuildMore();         // your build

    // register parameter dialog on option button
    register_option_dialog(dialogMore, _PushButtonOption);
}
//-------------------------------------------------------------------------
void PNXTemplateBaseDlg::BuildMore() {
    // your code here

    //-----------------------------------------------------------------
    // set step and visibility
    //-----------------------------------------------------------------
    dialogMore->_SpinnerMyStep->SetMinMaxStep(0.05, 1000, 1, 0); // Modify the step
}
//-------------------------------------------------------------------------
void PNXTemplateBaseDlg::SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) {

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateBase DIALOG NOTIFY

    // clang-format off

    // 2, MyCurve, NOT SUPPORT, SelectorList, 1

    // 3, MyFaces, NOT SUPPORT, SelectorList, 1

    // 4, MyStep
    ipDialogAgent->AcceptOnNotify(dialogMore->_SpinnerMyStep, dialogMore->_SpinnerMyStep->GetSpinnerModifyNotification());

    // 5, FinishCalc, NO ACTION, , 0

    // 100, MyAxis, NO ACTION, , 0

    // 101, MyTime, NO ACTION, , 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase DIALOG NOTIFY

    // value change
    ipDialogAgent->AcceptOnNotify(
        dialogMore->_SpinnerForValueChange,
        dialogMore->_SpinnerForValueChange->GetSpinnerModifyNotification());
}
//-------------------------------------------------------------------------
void PNXTemplateBaseDlg::UpdateDialog() {
    if (!parameter) // check pointer
        return;

    // KEVIN_SYSTEM_CODE START
    this->dialogMore->_EditorFeatureVersion->SetIntegerValue(parameter->FeatureVersion,
                                                             0); // set version
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateBase UPDATE DIALOG

    // clang-format off

    // 2,MyCurve,
    KT_AUTO_FIELD_SET_LINE(_SelectorListMyCurve, parameter->MyCurve);

    // 3,MyFaces,
    KT_AUTO_FIELD_SET_LINE(_SelectorListMyFaces, parameter->MyFaces);

    // 4,MyStep,
    dialogMore->_SpinnerMyStep->SetValue(parameter->MyStep, 0);

    // 5,FinishCalc,,NO ACTION,,0

    // 100,MyAxis,,NO ACTION,,0

    // 101,MyTime,,NO ACTION,,0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase UPDATE DIALOG

    // Code add by user

    // add grid range for My Axis

    this->UpdateSensitivity();   // update sensitivity
    this->SetActiveFieldFocus(); // focus
}
//-----------------------------------------------------------------
void PNXTemplateBaseDlg::UpdateInfos() {
    if (!parameter) // check pointer
        return;

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateBase UPDATE INFORS

    // clang-format off

    // 2,MyCurve,,NO ACTION,SelectorList,1

    // 3,MyFaces,,NO ACTION,SelectorList,1

    // 4,MyStep,
    parameter->MyStep = dialogMore->_SpinnerMyStep->GetValue();

    // 5,FinishCalc,,NO ACTION, ,0

    // 100,MyAxis,,NO ACTION, ,0

    // 101,MyTime,,NO ACTION, ,0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase UPDATE INFORS
}
//-------------------------------------------------------------------------
void PNXTemplateBaseDlg::UpdateSensitivity() {
    //_PushButtonMore->SetVisibility(CATDlgHide);//hide the param dialog now
    // check OK Sensitivity
    // this is Feature mode, Do not check OK sensitivity. always can press
    // this->SetOKSensitivity(dlgState); //set state
    // CATULong dlgState;
}
