/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterParamDlg.cpp
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
#ifdef PNXV5V6AdapterParamDlg_ParameterEditorInclude
#include "CATICkeParm.h"
#include "CATIParameterEditor.h"
#include "CATIParameterEditorFactory.h"
#endif

// Local Framework
#include "PNXV5V6AdapterParamDlg.h"

//-------------------------------------------------------------------------
PNXV5V6AdapterParamDlg::PNXV5V6AdapterParamDlg(CATDialog* iParent)
    : CATDlgDialog(iParent,
                   // clang-format off
//CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
"PNXV5V6AdapterParamDlg",CATDlgGridLayout
//END CAA2 WIZARD CONSTRUCTOR DECLARATION SECTION
                   // clang-format on
      ) {
    // clang-format off
//CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
 _FrameOthers = NULL;
 _LabelVersion = NULL;
 _EditorFeatureVersion = NULL;
//END CAA2 WIZARD CONSTRUCTOR INITIALIZATION SECTION
    // clang-format on
    _SpinnerForValueChange = NULL;
}
//-------------------------------------------------------------------------
PNXV5V6AdapterParamDlg::~PNXV5V6AdapterParamDlg() {
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    // clang-format off
//CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
 _FrameOthers = NULL;
 _LabelVersion = NULL;
 _EditorFeatureVersion = NULL;
//END CAA2 WIZARD DESTRUCTOR DECLARATION SECTION
    // clang-format on
    _SpinnerForValueChange = NULL; // set null
}
//---------------------------------------------------------
void PNXV5V6AdapterParamDlg::Build() {
    //  TODO: This call builds your dialog from the layout declaration file
    //  -------------------------------------------------------------------

    // clang-format off
//CAA2 WIZARD WIDGET CONSTRUCTION SECTION
 SetGridColumnResizable(0,1);
 _FrameOthers = new CATDlgFrame(this, "FrameOthers", CATDlgGridLayout);
_FrameOthers -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _FrameOthers -> SetGridColumnResizable(1,1);
 _LabelVersion = new CATDlgLabel(_FrameOthers, "LabelVersion");
_LabelVersion -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 _EditorFeatureVersion = new CATDlgEditor(_FrameOthers, "EditorFeatureVersion", CATDlgEdtInteger|CATDlgEdtReadOnly);
_EditorFeatureVersion -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);
//END CAA2 WIZARD WIDGET CONSTRUCTION SECTION
    // clang-format on

    // this is only for value change agent
    _SpinnerForValueChange = new CATDlgSpinner(this, "SpinnerForValueChange", CATDlgSpnDouble);
    _SpinnerForValueChange->SetMinMaxStep(-10.0, 10.0, 1.0); // set range
    _SpinnerForValueChange->SetVisibility(CATDlgHide);       // hide

    // CAA2 WIZARD CALLBACK DECLARATION SECTION
    // END CAA2 WIZARD CALLBACK DECLARATION SECTION
    AddAnalyseNotificationCB(this, GetWindCloseNotification(),
                             (CATCommandMethod)&PNXV5V6AdapterParamDlg::
                                 OnPNXV5V6AdapterParamDlgWindCloseNotification,
                             NULL);
    AddAnalyseNotificationCB(this, GetDiaCANCELNotification(),
                             (CATCommandMethod)&PNXV5V6AdapterParamDlg::
                                 OnPNXV5V6AdapterParamDlgDiaCANCELNotification,
                             NULL);
    AddAnalyseNotificationCB(
        this, GetDiaOKNotification(),
        (CATCommandMethod)&PNXV5V6AdapterParamDlg::OnPNXV5V6AdapterParamDlgDiaOKNotification,
        NULL);
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterParamDlg::OnPNXV5V6AdapterParamDlgDiaOKNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    // Add your code here
    SetVisibility(CATDlgHide);
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterParamDlg::OnPNXV5V6AdapterParamDlgDiaCANCELNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    SetVisibility(CATDlgHide); // hide only
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterParamDlg::OnPNXV5V6AdapterParamDlgWindCloseNotification(
    CATCommand* cmd, CATNotification* evt, CATCommandClientData data) {
    SetVisibility(CATDlgHide); // hide only
}
//-------------------------------------------------------------------------
void PNXV5V6AdapterParamDlg::SendValueChangeNotify() {
    this->_SpinnerForValueChange->SetValue(1, 1); // send ValueChange notify
}
