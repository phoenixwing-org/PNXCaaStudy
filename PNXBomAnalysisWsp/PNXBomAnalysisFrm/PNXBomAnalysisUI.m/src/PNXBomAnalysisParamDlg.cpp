/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisParamDlg.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef PNXBomAnalysisParamDlg_ParameterEditorInclude
#include "CATICkeParm.h"
#include "CATIParameterEditor.h"
#include "CATIParameterEditorFactory.h"
#endif

// Local Framework
#include "PNXBomAnalysisParamDlg.h"

//-------------------------------------------------------------------------
PNXBomAnalysisParamDlg::PNXBomAnalysisParamDlg(CATDialog* iParent)
    : CATDlgDialog(iParent,
                   // clang-format off
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXBomAnalysisParamDlg",CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                   // clang-format on
      ) {
    // clang-format off
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _FrameOthers = NULL;
 _LabelVersion = NULL;
 _EditorFeatureVersion = NULL;
 _LabelSag = NULL;
 _SpinnerPartCount = NULL;
 _EditorMyResult = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on
    _SpinnerForValueChange = NULL;
}
//-------------------------------------------------------------------------
PNXBomAnalysisParamDlg::~PNXBomAnalysisParamDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameOthers = NULL;
 _LabelVersion = NULL;
 _EditorFeatureVersion = NULL;
 _LabelSag = NULL;
 _SpinnerPartCount = NULL;
 _EditorMyResult = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on
    _SpinnerForValueChange = NULL; // set null
}
//---------------------------------------------------------
void PNXBomAnalysisParamDlg::Build() {
    //  TODO: This call builds your dialog from the layout declaration file
    //  -------------------------------------------------------------------

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridRowResizable(1,1);
 SetGridColumnResizable(0,1);
 _FrameOthers = new CATDlgFrame(this, "FrameOthers", CATDlgGridLayout);
_FrameOthers -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameOthers -> SetGridColumnResizable(1,1);
 _LabelVersion = new CATDlgLabel(_FrameOthers, "LabelVersion");
_LabelVersion -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _EditorFeatureVersion = new CATDlgEditor(_FrameOthers, "EditorFeatureVersion", CATDlgEdtInteger|CATDlgEdtReadOnly);
_EditorFeatureVersion -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _LabelSag = new CATDlgLabel(_FrameOthers, "LabelSag");
_LabelSag -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _SpinnerPartCount = new CATDlgSpinner(_FrameOthers, "SpinnerPartCount", CATDlgSpnEntry|CATDlgSpnDouble);
 _SpinnerPartCount -> SetMinMaxStep(0.000000, 100.000000, 0.010000);
 _SpinnerPartCount -> SetPrecision( 0 );
_SpinnerPartCount -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _EditorMyResult = new CATDlgEditor(this, "EditorMyResult", CATDlgEdtMultiline);
 _EditorMyResult -> SetVisibleTextHeight(8);
 _EditorMyResult -> SetVisibleTextWidth(30);
_EditorMyResult -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // this is only for value change agent
    _SpinnerForValueChange = new CATDlgSpinner(this, "SpinnerForValueChange", CATDlgSpnDouble);
    _SpinnerForValueChange->SetMinMaxStep(-10.0, 10.0, 1.0); // set range
    _SpinnerForValueChange->SetVisibility(CATDlgHide);       // hide

    // CAA2 WIZARD CALLBACK DECLARATION SECTION
    // END CAA2 WIZARD CALLBACK DECLARATION SECTION
    AddAnalyseNotificationCB(
        this, GetWindCloseNotification(),
        (CATCommandMethod)&PNXBomAnalysisParamDlg::OnPNXBomAnalysisParamDlgWindCloseNotification,
        NULL);
    AddAnalyseNotificationCB(
        this, GetDiaCANCELNotification(),
        (CATCommandMethod)&PNXBomAnalysisParamDlg::OnPNXBomAnalysisParamDlgDiaCANCELNotification,
        NULL);
    AddAnalyseNotificationCB(
        this, GetDiaOKNotification(),
        (CATCommandMethod)&PNXBomAnalysisParamDlg::OnPNXBomAnalysisParamDlgDiaOKNotification, NULL);
}
//-------------------------------------------------------------------------
void PNXBomAnalysisParamDlg::OnPNXBomAnalysisParamDlgDiaOKNotification(CATCommand*          cmd,
                                                                       CATNotification*     evt,
                                                                       CATCommandClientData data) {
    // Add your code here
    SetVisibility(CATDlgHide);
}
//-------------------------------------------------------------------------
void PNXBomAnalysisParamDlg::OnPNXBomAnalysisParamDlgDiaCANCELNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    SetVisibility(CATDlgHide); // hide only
}
//-------------------------------------------------------------------------
void PNXBomAnalysisParamDlg::OnPNXBomAnalysisParamDlgWindCloseNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    SetVisibility(CATDlgHide); // hide only
}
//-------------------------------------------------------------------------
void PNXBomAnalysisParamDlg::SendValueChangeNotify() {
    this->_SpinnerForValueChange->SetValue(1, 1); // send ValueChange notify
}
