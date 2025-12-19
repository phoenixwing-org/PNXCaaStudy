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

#ifndef PNXV5V6AdapterDlg_H
#define PNXV5V6AdapterDlg_H

// Dialog Framework
#include "CATDlgInclude.h" // needed to use Dialog framework objects

#include "CATDialogAgent.h"

// Local Framework
#include "PNXV5V6AdapterParam.h"
#include "PNXV5V6AdapterParamDlg.h"

// Auto Code
#include "KTCAutoDialog.h"

class PNXV5V6AdapterCmd;

/** @brief main Dialog */
class PNXV5V6AdapterDlg : public KTCAutoDialog {
    friend class PNXV5V6AdapterCmd;
    DeclareResource(PNXV5V6AdapterDlg, KTCAutoDialog);

public:
    PNXV5V6AdapterDlg();
    virtual ~PNXV5V6AdapterDlg();

    /** @brief Builds the panel with its control */
    void Build();

    /** @brief Build more*/
    void BuildMore();

protected:
    /** @brief Param Dialog pointer define */
    PNXV5V6AdapterParamDlg* dialogMore;

    /** @brief param pointer define */
    PNXV5V6AdapterParam* parameter;

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
