/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXCurveDivisionDlg_H
#define PNXCurveDivisionDlg_H

// Dialog Framework
#include "CATDlgInclude.h" // needed to use Dialog framework objects

#include "CATDialogAgent.h"

// Local Framework
#include "PNXCurveDivisionParam.h"
#include "PNXCurveDivisionParamDlg.h"

class PNXCurveDivisionCmd;

/** @brief main Dialog */
class PNXCurveDivisionDlg : public CATDlgDialog {
    friend class PNXCurveDivisionCmd;
    DeclareResource(PNXCurveDivisionDlg, CATDlgDialog);

public:
    PNXCurveDivisionDlg();
    virtual ~PNXCurveDivisionDlg();

    /** @brief Builds the panel with its control */
    void Build();

    /** @brief Build more*/
    void BuildMore();

protected:
    /** @brief Param Dialog pointer define */
    PNXCurveDivisionParamDlg* dialogMore;

    /** @brief param pointer define */
    PNXCurveDivisionParam* parameter;

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

protected: // Inset position for THE CAA2 WIZARD : protected:
private:
    // clang-format off
//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgFrame*      _FrameParams;
 CATDlgLabel*      _LabelBaseCurve;
 CATDlgSelectorList*      _SelectorListBaseCurve;
 CATDlgSpinner*      _SpinnerPointCount;
 CATDlgLabel*      _LabelPointCount;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};

#endif
