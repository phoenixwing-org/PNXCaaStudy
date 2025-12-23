/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureParamDlg.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#include "CATApplicationFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
#ifdef PNXTemplateFeatureParamDlg_ParameterEditorInclude
#include "CATICkeParm.h"
#include "CATIParameterEditor.h"
#include "CATIParameterEditorFactory.h"
#endif

// Local Framework
#include "PNXTemplateFeatureParamDlg.h"

//-------------------------------------------------------------------------
PNXTemplateFeatureParamDlg::PNXTemplateFeatureParamDlg(CATDialog* iParent)
    : CATDlgDialog(iParent,
                   // clang-format off
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXTemplateFeatureParamDlg",CATDlgWndBtnClose|CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                   // clang-format on

      ) {

    // clang-format off
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _FrameOthers = NULL;
 _LabelVersion = NULL;
 _EditorFeatureVersion = NULL;
 _LabelMyStep = NULL;
 _SpinnerMyStep = NULL;
 _LabelUnit = NULL;
 _EditorOutputMessage = NULL;
 _LabelOutputMessage = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on
}
//-------------------------------------------------------------------------
PNXTemplateFeatureParamDlg::~PNXTemplateFeatureParamDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameOthers = NULL;
 _LabelVersion = NULL;
 _EditorFeatureVersion = NULL;
 _LabelMyStep = NULL;
 _SpinnerMyStep = NULL;
 _LabelUnit = NULL;
 _EditorOutputMessage = NULL;
 _LabelOutputMessage = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on
    _SpinnerForValueChange = NULL; // set null
}
//---------------------------------------------------------
void PNXTemplateFeatureParamDlg::Build() {
    //  TODO: This call builds your dialog from the layout declaration file
    //  -------------------------------------------------------------------

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridRowResizable(2,1);
 SetGridColumnResizable(0,1);
 _FrameOthers = new CATDlgFrame(this, "FrameOthers", CATDlgGridLayout);
_FrameOthers -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameOthers -> SetGridColumnResizable(1,1);
 _LabelVersion = new CATDlgLabel(_FrameOthers, "LabelVersion");
_LabelVersion -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _EditorFeatureVersion = new CATDlgEditor(_FrameOthers, "EditorFeatureVersion", CATDlgEdtInteger|CATDlgEdtReadOnly);
_EditorFeatureVersion -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
 _LabelMyStep = new CATDlgLabel(_FrameOthers, "LabelMyStep");
_LabelMyStep -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
 _SpinnerMyStep = new CATDlgSpinner(_FrameOthers, "SpinnerMyStep", CATDlgSpnEntry|CATDlgSpnDouble);
 _SpinnerMyStep -> SetMinMaxStep(0.000000, 1000.000000, 1.000000);
 _SpinnerMyStep -> SetPrecision( 0 );
_SpinnerMyStep -> SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES);
 _LabelUnit = new CATDlgLabel(_FrameOthers, "LabelUnit");
_LabelUnit -> SetGridConstraints(1, 2, 1, 1, CATGRID_4SIDES);
 _EditorOutputMessage = new CATDlgEditor(this, "EditorOutputMessage", CATDlgEdtMultiline);
 _EditorOutputMessage -> SetVisibleTextHeight(8);
 _EditorOutputMessage -> SetVisibleTextWidth(30);
_EditorOutputMessage -> SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES);
 _LabelOutputMessage = new CATDlgLabel(this, "LabelOutputMessage");
_LabelOutputMessage -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // this is only for value change agent
    _SpinnerForValueChange = new CATDlgSpinner(this, "SpinnerForValueChange", CATDlgSpnDouble);
    _SpinnerForValueChange->SetMinMaxStep(-10.0, 10.0, 1.0); // set range
    _SpinnerForValueChange->SetVisibility(CATDlgHide);       // hide

    // clang-format off
//CAA2 WIZARD CALLBACK DECLARATION SECTION

//END CAA2 WIZARD CALLBACK DECLARATION SECTION
    // clang-format on
    AddAnalyseNotificationCB(this, GetWindCloseNotification(),
                             (CATCommandMethod)&PNXTemplateFeatureParamDlg::
                                 OnPNXTemplateFeatureParamDlgWindCloseNotification,
                             NULL);
    AddAnalyseNotificationCB(this, GetDiaCANCELNotification(),
                             (CATCommandMethod)&PNXTemplateFeatureParamDlg::
                                 OnPNXTemplateFeatureParamDlgDiaCANCELNotification,
                             NULL);
    AddAnalyseNotificationCB(this, GetDiaOKNotification(),
                             (CATCommandMethod)&PNXTemplateFeatureParamDlg::
                                 OnPNXTemplateFeatureParamDlgDiaOKNotification,
                             NULL);
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureParamDlg::OnPNXTemplateFeatureParamDlgDiaOKNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    // Add your code here
    SetVisibility(CATDlgHide);
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureParamDlg::OnPNXTemplateFeatureParamDlgDiaCANCELNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    SetVisibility(CATDlgHide); // hide only
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureParamDlg::OnPNXTemplateFeatureParamDlgWindCloseNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    SetVisibility(CATDlgHide); // hide only
}
//-------------------------------------------------------------------------
void PNXTemplateFeatureParamDlg::SendValueChangeNotify() {
    this->_SpinnerForValueChange->SetValue(1, 1); // send ValueChange notify
}
