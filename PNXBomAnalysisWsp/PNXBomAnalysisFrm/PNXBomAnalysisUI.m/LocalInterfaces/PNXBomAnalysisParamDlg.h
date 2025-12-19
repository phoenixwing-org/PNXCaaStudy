/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisParamDlg.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXBomAnalysisParamDlg_H
#define PNXBomAnalysisParamDlg_H

#include "CATDlgDialog.h"

// KTC
#include "CATDlgInclude.h"

/** @brief param setting dialog */
class PNXBomAnalysisParamDlg : public CATDlgDialog {
    // Allows customization/internationalization of command's messages
    // ---------------------------------------------------------------
    DeclareResource(PNXBomAnalysisParamDlg, CATDlgDialog);

public:
    PNXBomAnalysisParamDlg(CATDialog* iParent);
    virtual ~PNXBomAnalysisParamDlg();

    void Build();

protected:
    /** @brief close  */
    virtual void OnPNXBomAnalysisParamDlgWindCloseNotification(CATCommand*, CATNotification*,
                                                               CATCommandClientData data);

    /** @brief CANCEL  */
    virtual void OnPNXBomAnalysisParamDlgDiaCANCELNotification(CATCommand*, CATNotification*,
                                                               CATCommandClientData data);

    /** @brief OK  */
    virtual void OnPNXBomAnalysisParamDlgDiaOKNotification(CATCommand*, CATNotification*,
                                                           CATCommandClientData data);

public:
    /** @brief send value change notify  */
    void SendValueChangeNotify();

public:
    CATDlgSpinner* _SpinnerForValueChange; // for value change Only

    // clang-format off
//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgFrame*      _FrameOthers;
 CATDlgLabel*      _LabelVersion;
 CATDlgEditor*      _EditorFeatureVersion;
 CATDlgLabel*      _LabelSag;
 CATDlgSpinner*      _SpinnerPartCount;
 CATDlgEditor*      _EditorMyResult;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};
#endif
