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

#ifndef PNXBomAnalysisDlg_H
#define PNXBomAnalysisDlg_H

// Dialog Framework
#include "CATDlgInclude.h" // needed to use Dialog framework objects

#include "CATDialogAgent.h"

// Local Framework
#include "PNXBomAnalysisParam.h"
#include "PNXBomAnalysisParamDlg.h"

// KTC
#include "KTCAutoDialog.h"

class PNXBomAnalysisCmd;

/** @brief main Dialog */
class PNXBomAnalysisDlg : public KTCAutoDialog {
    friend class PNXBomAnalysisCmd;
    DeclareResource(PNXBomAnalysisDlg, KTCAutoDialog);

public:
    PNXBomAnalysisDlg();
    virtual ~PNXBomAnalysisDlg();

    /** @brief Builds the panel with its control */
    void Build();

    /** @brief Build more*/
    void BuildMore();

protected:
    /** @brief Param Dialog pointer define */
    PNXBomAnalysisParamDlg* dialogMore;

    /** @brief param pointer define */
    PNXBomAnalysisParam* parameter;

protected:
    /**
     * @brief Set Accept On Notify Of Value Change
     * @param[in] ipDialogAgent Value Change Agent
     */
    void SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent);

    /** @brief Set Params to Dialog */
    void UpdateDialog();

    /** @brief Update Params From Dialog */
    void UpdateInfos();

    /** @brief Update dialog Sensitivity */
    void UpdateSensitivity();

private:
    // clang-format off
//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgFrame*      _FrameParams;
 CATDlgLabel*      _LabelFirstProduct;
 CATDlgSelectorList*      _SelectorListFirstProduct;
 CATDlgEditor*      _EditorFirstPartNumber;
 CATDlgLabel*      _LabelFirstPartNumber;
 CATDlgFrame*      _FrameBom;
 CATDlgMultiList*      _MultiListPartBom;
 CATDlgFrame*      _FrameOutput;
 CATDlgPushButton*      _PushButtonJson;
 CATDlgPushButton*      _PushButtonPrintMarkdown;
 CATDlgEditor*      _EditorOutInfo;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};

#endif
