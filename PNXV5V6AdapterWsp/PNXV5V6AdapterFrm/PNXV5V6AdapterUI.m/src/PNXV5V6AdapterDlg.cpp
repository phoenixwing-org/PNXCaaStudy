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

// Local Framework
#include "PNXV5V6AdapterDlg.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h" // needed to get the window of the frame

// Dialog Framework
#include "CATDlgGridConstraints.h" // needed to locate dialog element on the box's grid
#include "CATDlgLabel.h"
// Visualization Framework
// #include "PNXAppFrameServicesCls.h"
#include "iostream.h"

// auto code
#include "KTCAutoIncludeUI.h"

//-------------------------------------------------------------------------
PNXV5V6AdapterDlg::PNXV5V6AdapterDlg()
    // clang-format off
    : KTCAutoDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(), NULL
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXV5V6AdapterDlg",CATDlgWndBtnOKApplyClose|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                    // clang-format on
                    )
    , dialogMore(NULL)
    , parameter(NULL) {

    // clang-format off
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _FrameParams = NULL;
 _LabelBaseCurve = NULL;
 _SelectorListBaseCurve = NULL;
 _SpinnerPointCount = NULL;
 _LabelPointCount = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on

    dialogMore = new PNXV5V6AdapterParamDlg(this); // new one
}
//-------------------------------------------------------------------------
PNXV5V6AdapterDlg::~PNXV5V6AdapterDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameParams = NULL;
 _LabelBaseCurve = NULL;
 _SelectorListBaseCurve = NULL;
 _SpinnerPointCount = NULL;
 _LabelPointCount = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on

    parameter = NULL;                         // not delete
    KTCRequestDelayedDestruction(dialogMore); // DESTRUCTOR
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterDlg::Build() {

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridColumnResizable(0,1);
 _FrameParams = new CATDlgFrame(this, "FrameParams", CATDlgFraNoFrame|CATDlgGridLayout);
_FrameParams -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameParams -> SetGridColumnResizable(1,1);
 _LabelBaseCurve = new CATDlgLabel(_FrameParams, "LabelBaseCurve");
_LabelBaseCurve -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListBaseCurve = new CATDlgSelectorList(_FrameParams, "SelectorListBaseCurve");
 _SelectorListBaseCurve -> SetVisibleTextHeight(1);
_SelectorListBaseCurve -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _SpinnerPointCount = new CATDlgSpinner(_FrameParams, "SpinnerPointCount", CATDlgSpnEntry|CATDlgSpnDouble);
 _SpinnerPointCount -> SetMinMaxStep(0.000000, 100.000000, 1.000000);
 _SpinnerPointCount -> SetPrecision( 0 );
_SpinnerPointCount -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _LabelPointCount = new CATDlgLabel(_FrameParams, "LabelPointCount");
_LabelPointCount -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // CAA2 WIZARD CALLBACK DECLARATION SECTION
    // END CAA2 WIZARD CALLBACK DECLARATION SECTION

    dialogMore->Build(); // Build

    BuildMore(); // your build
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterDlg::BuildMore() {
    // your code here

    //-----------------------------------------------------------------
    // set step and visibility
    //-----------------------------------------------------------------
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterDlg::SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) {

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter DIALOG NOTIFY

    // clang-format off

    // 1, BaseCurve, NOT SUPPORT, SelectorList, 1

    // 2, PointCount
    ipDialogAgent->AcceptOnNotify(_SpinnerPointCount, _SpinnerPointCount->GetSpinnerModifyNotification());

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter DIALOG NOTIFY

    // value change
    ipDialogAgent->AcceptOnNotify(
        dialogMore->_SpinnerForValueChange,
        dialogMore->_SpinnerForValueChange->GetSpinnerModifyNotification());
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterDlg::UpdateDialog() {
    if (!parameter) // check pointer
        return;
    // cout << "### " << __FUNCTION__ << endl;

    // KEVIN_SYSTEM_CODE START
    this->dialogMore->_EditorFeatureVersion->SetIntegerValue(0, 0); // set version
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter UPDATE DIALOG

    // clang-format off

    // 1,BaseCurve,
    KT_AUTO_FIELD_SET_LINE(_SelectorListBaseCurve, parameter->BaseCurve);

    // 2,PointCount,
    _SpinnerPointCount->SetValue(parameter->PointCount, 0);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter UPDATE DIALOG

    // Code add by user

    if (parameter->BaseCurve != NULL_var) {
        _SelectorListBaseCurve->SetLine(parameter->BaseCurve->GetDisplayName(), 0,
                                        CATDlgDataModify);
    }
    else
        _SelectorListBaseCurve->SetLine("(No Selection)", 0, CATDlgDataModify);

    this->UpdateSensitivity(); // update sensitivity
    // this->SetActiveFieldFocus(); // focus
}
//-----------------------------------------------------------------
void PNXV5V6AdapterDlg::UpdateInfos() {
    if (!parameter) // check pointer
        return;

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter UPDATE INFORS

    // clang-format off

    // 1,BaseCurve,,NO ACTION,SelectorList,1

    // 2,PointCount,
    parameter->PointCount = Kt::round(_SpinnerPointCount->GetValue());

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter UPDATE INFORS
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterDlg::UpdateSensitivity() {
    //_PushButtonMore->SetVisibility(CATDlgHide);//hide the param dialog now
    // check OK Sensitivity
    // this is Feature mode, Do not check OK sensitivity. always can press
    // this->SetOKSensitivity(dlgState); //set state
    // CATULong dlgState;
}
