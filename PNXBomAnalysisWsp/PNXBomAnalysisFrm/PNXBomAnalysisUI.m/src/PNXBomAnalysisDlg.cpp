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

// Local Framework
#include "PNXBomAnalysisDlg.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h" // needed to get the window of the frame

// Dialog Framework
#include "CATDlgGridConstraints.h" // needed to locate dialog element on the box's grid
#include "CATDlgLabel.h"

#include "CATUnicodeString.h"
#include "iostream.h"

// System Framework
#include "KTCAutoCode.h"
#include "KTCAutoPanelCommand.h"
#include "KTCCoreDefine.h"

int counterForSave = 0;
//-------------------------------------------------------------------------
PNXBomAnalysisDlg::PNXBomAnalysisDlg()
    : CATDlgDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
                   // clang-format off
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXBomAnalysisDlg",CATDlgWndBtnOKCancelPreview|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                   // clang-format on
                   )
    , dialogMore(NULL)
    , parameter(NULL) {

    // clang-format off
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _FrameParams = NULL;
 _LabelFirstProduct = NULL;
 _SelectorListFirstProduct = NULL;
 _EditorFirstPartNumber = NULL;
 _LabelFirstPartNumber = NULL;
 _FrameBom = NULL;
 _MultiListPartBom = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on

    dialogMore = new PNXBomAnalysisParamDlg(this); // new one
}
//-------------------------------------------------------------------------
PNXBomAnalysisDlg::~PNXBomAnalysisDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameParams = NULL;
 _LabelFirstProduct = NULL;
 _SelectorListFirstProduct = NULL;
 _EditorFirstPartNumber = NULL;
 _LabelFirstPartNumber = NULL;
 _FrameBom = NULL;
 _MultiListPartBom = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on

    parameter = NULL;                         // not delete
    KTCRequestDelayedDestruction(dialogMore); // DESTRUCTOR
}
//-------------------------------------------------------------------------
void PNXBomAnalysisDlg::Build() {

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridRowResizable(1,1);
 SetGridColumnResizable(0,1);
 _FrameParams = new CATDlgFrame(this, "FrameParams", CATDlgFraNoFrame|CATDlgGridLayout);
_FrameParams -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameParams -> SetGridColumnResizable(1,1);
 _LabelFirstProduct = new CATDlgLabel(_FrameParams, "LabelFirstProduct");
_LabelFirstProduct -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _SelectorListFirstProduct = new CATDlgSelectorList(_FrameParams, "SelectorListFirstProduct");
 _SelectorListFirstProduct -> SetVisibleTextHeight(1);
_SelectorListFirstProduct -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _EditorFirstPartNumber = new CATDlgEditor(_FrameParams, "EditorFirstPartNumber");
_EditorFirstPartNumber -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _LabelFirstPartNumber = new CATDlgLabel(_FrameParams, "LabelFirstPartNumber");
_LabelFirstPartNumber -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _FrameBom = new CATDlgFrame(this, "FrameBom", CATDlgGridLayout);
_FrameBom -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _FrameBom -> SetGridRowResizable(0,1);
 _FrameBom -> SetGridColumnResizable(0,1);
 _MultiListPartBom = new CATDlgMultiList(_FrameBom, "MultiListPartBom");
 CATUnicodeString MultiListPartBomTitles [ 1 ];
 MultiListPartBomTitles[0] = CATMsgCatalog::BuildMessage("PNXBomAnalysisDlg", "FrameBom.MultiListPartBom.ColumnTitle1");
 _MultiListPartBom -> SetColumnTitles(1, MultiListPartBomTitles);
 _MultiListPartBom -> SetVisibleColumnCount( 1 );
_MultiListPartBom -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // CAA2 WIZARD CALLBACK DECLARATION SECTION
    // END CAA2 WIZARD CALLBACK DECLARATION SECTION

    dialogMore->Build(); // Build

    BuildMore(); // your build
}
//-------------------------------------------------------------------------
void PNXBomAnalysisDlg::BuildMore() {
    // your code here

    //-----------------------------------------------------------------
    // set step and visibility
    //-----------------------------------------------------------------
    _EditorFirstPartNumber->SetSensitivity(CATDlgDisable);
}
//-------------------------------------------------------------------------
void PNXBomAnalysisDlg::SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) {

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis DIALOG NOTIFY

    // clang-format off

    // 1, FirstProduct, NOT SUPPORT, SelectorList, 1

    // 2, FirstPartNumber
    ipDialogAgent->AcceptOnNotify(_EditorFirstPartNumber, _EditorFirstPartNumber->GetEditModifyNotification());

    // 3, PartCount, NO ACTION, Spinner, 0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis DIALOG NOTIFY

    // value change
    ipDialogAgent->AcceptOnNotify(
        dialogMore->_SpinnerForValueChange,
        dialogMore->_SpinnerForValueChange->GetSpinnerModifyNotification());
}
//-------------------------------------------------------------------------
void PNXBomAnalysisDlg::UpdateDialog() {
    if (!parameter) // check pointer
        return;

    // KEVIN_SYSTEM_CODE START
    this->dialogMore->_EditorFeatureVersion->SetIntegerValue(0, 0); // set version
    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis UPDATE DIALOG

    // clang-format off

    // 1,FirstProduct,
    KT_AUTO_FIELD_SET_LINE(_SelectorListFirstProduct, parameter->FirstProduct);

    _EditorFirstPartNumber->SetText(parameter->FirstPartNumber, 0);

    // 3,PartCount,,NO ACTION,Spinner,0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis UPDATE DIALOG

    // Code add by user

    this->UpdateSensitivity(); // update sensitivity
    // this->SetActiveFieldFocus(); // focus
}
//-----------------------------------------------------------------
void PNXBomAnalysisDlg::UpdateInfos() {
    if (!parameter) // check pointer
        return;

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis UPDATE INFORS

    // clang-format off

    // 1,FirstProduct,,NO ACTION,SelectorList,1

    // 2,FirstPartNumber,
    parameter->FirstPartNumber = _EditorFirstPartNumber->GetText();

    // 3,PartCount,,NO ACTION, Spinner,0

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis UPDATE INFORS
}
//-------------------------------------------------------------------------
void PNXBomAnalysisDlg::UpdateSensitivity() {
    //_PushButtonMore->SetVisibility(CATDlgHide);//hide the param dialog now
    // check OK Sensitivity
    // this is Feature mode, Do not check OK sensitivity. always can press
    // this->SetOKSensitivity(dlgState); //set state
    // CATULong dlgState;
}
