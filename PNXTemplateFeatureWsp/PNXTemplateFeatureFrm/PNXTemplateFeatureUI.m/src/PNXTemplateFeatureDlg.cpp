/**
 * @copyright   Copyright 2021 Kevin Time Toolkit
 * @license      MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

// Local Framework
#include "PNXTemplateFeatureDlg.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h" // needed to get the window of the frame
#include "KtString.h"
// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"

// Visualization Framework
#include "iostream.h"

// auto code
#include "KTCAutoIncludeUI.h"

//-------------------------------------------------------------------------
PNXTemplateFeatureDlg::PNXTemplateFeatureDlg(CATMMUIPanelStateCmd* iFatherCmd)
    // clang-format off
    : KTCAutoDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), iFatherCmd,
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXTemplateFeatureDlg",CATDlgWndBtnOKCancelPreview|CATDlgGridLayout
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
 _LabelMyAxis = NULL;
 _SelectorListMyAxis = NULL;
 _LabelTransmissibility = NULL;
 _EditorTransmissibility = NULL;
 _FrameMyFaces = NULL;
 _SelectorListMyFaces = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on

    dialogMore = new PNXTemplateFeatureParamDlg(this);  // new one
    KTCAutoDialog::RegisterParameterDialog(dialogMore); // register parameter dialog
}
//-------------------------------------------------------------------------
PNXTemplateFeatureDlg::~PNXTemplateFeatureDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameParams = NULL;
 _LabelMyCurve = NULL;
 _SelectorListMyCurve = NULL;
 _LabelMyAxis = NULL;
 _SelectorListMyAxis = NULL;
 _LabelTransmissibility = NULL;
 _EditorTransmissibility = NULL;
 _FrameMyFaces = NULL;
 _SelectorListMyFaces = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on

    parameter = NULL;                         // not delete
    KTCRequestDelayedDestruction(dialogMore); // DESTRUCTOR
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureDlg::Build() {
    // Creates the menu bar with default menus
    // KTCDlgBarMenu* menuBar = KTCAutoDialog::GetMenuBarSingleton();

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridRowResizable(0,1);
 SetGridColumnResizable(0,1);
 _FrameParams = new CATDlgFrame(this, "FrameParams", CATDlgFraNoFrame|CATDlgGridLayout);
_FrameParams -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _FrameParams -> SetGridColumnResizable(1,1);
 _LabelMyCurve = new CATDlgLabel(_FrameParams, "LabelMyCurve");
_LabelMyCurve -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListMyCurve = new CATDlgSelectorList(_FrameParams, "SelectorListMyCurve");
 _SelectorListMyCurve -> SetVisibleTextHeight(1);
_SelectorListMyCurve -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _LabelMyAxis = new CATDlgLabel(_FrameParams, "LabelMyAxis");
_LabelMyAxis -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListMyAxis = new CATDlgSelectorList(_FrameParams, "SelectorListMyAxis");
 _SelectorListMyAxis -> SetVisibleTextHeight(1);
_SelectorListMyAxis -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _LabelTransmissibility = new CATDlgLabel(_FrameParams, "LabelTransmissibility");
_LabelTransmissibility -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _EditorTransmissibility = new CATDlgEditor(_FrameParams, "EditorTransmissibility", CATDlgEdtFloat|CATDlgEdtReadOnly);
 _EditorTransmissibility -> SetVisibleTextHeight(1);
_EditorTransmissibility -> SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES);
 _FrameMyFaces = new CATDlgFrame(this, "FrameMyFaces", CATDlgGridLayout);
_FrameMyFaces -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameMyFaces -> SetGridRowResizable(0,1);
 _FrameMyFaces -> SetGridColumnResizable(0,1);
 _SelectorListMyFaces = new CATDlgSelectorList(_FrameMyFaces, "SelectorListMyFaces");
 _SelectorListMyFaces -> SetVisibleTextHeight(6);
_SelectorListMyFaces -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // clang-format off
//CAA2 WIZARD CALLBACK DECLARATION SECTION

//END CAA2 WIZARD CALLBACK DECLARATION SECTION
    // clang-format on

    dialogMore->Build(); // Build

    BuildMore(); // your build
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureDlg::BuildMore() {
    // your code here

    //-----------------------------------------------------------------
    // set step and visibility
    //-----------------------------------------------------------------
    dialogMore->_SpinnerMyStep->SetMinMaxStep(0.05, 1000, 1, 0); // Modify the step
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureDlg::SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) {

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature DIALOG NOTIFY

    // clang-format off

    // 2, MyCurve, NOT SUPPORT, SelectorList, 1

    // 3, MyFaces, NOT SUPPORT, SelectorList, 1

    // 4, MyStep
    ipDialogAgent->AcceptOnNotify(dialogMore->_SpinnerMyStep, dialogMore->_SpinnerMyStep->GetSpinnerModifyNotification());

    // 5, FinishCalc, NO ACTION, , 0

    // 100, MyAxis, NO ACTION, , 0

    // 101, MyTime, NO ACTION, , 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature DIALOG NOTIFY

    // value change
    ipDialogAgent->AcceptOnNotify(
        dialogMore->_SpinnerForValueChange,
        dialogMore->_SpinnerForValueChange->GetSpinnerModifyNotification());
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureDlg::UpdateDialog() {
    if (!parameter) // check pointer
        return;

    // KEVIN_SYSTEM_CODE START
    this->dialogMore->_EditorFeatureVersion->SetIntegerValue(parameter->FeatureVersion,
                                                             0); // set version
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature UPDATE DIALOG

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
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature UPDATE DIALOG

    // Code add by user

    // add grid range for My Axis

    this->UpdateSensitivity();   // update sensitivity
    this->SetActiveFieldFocus(); // focus
}
//-----------------------------------------------------------------
void PNXTemplateFeatureDlg::UpdateInfos() {
    if (!parameter) // check pointer
        return;

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature UPDATE INFORS

    // clang-format off

    // 2,MyCurve,,NO ACTION,SelectorList,1

    // 3,MyFaces,,NO ACTION,SelectorList,1

    // 4,MyStep,
    parameter->MyStep = dialogMore->_SpinnerMyStep->GetValue();

    // 5,FinishCalc,,NO ACTION, ,0

    // 100,MyAxis,,NO ACTION, ,0

    // 101,MyTime,,NO ACTION, ,0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature UPDATE INFORS
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureDlg::UpdateSensitivity() {
    //_PushButtonMore->SetVisibility(CATDlgHide);//hide the param dialog now
    // check OK Sensitivity
    // this is Feature mode, Do not check OK sensitivity. always can press
    // this->SetOKSensitivity(dlgState); //set state
    // CATULong dlgState;
}
