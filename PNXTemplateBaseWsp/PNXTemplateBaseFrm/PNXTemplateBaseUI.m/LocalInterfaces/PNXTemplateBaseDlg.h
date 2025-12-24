/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateBaseDlg_H
#define PNXTemplateBaseDlg_H

// Dialog Framework
#include "CATDialogAgent.h"
#include "CATDlgInclude.h" // needed to use Dialog framework objects
#include "CATMMUIPanelStateCmd.h"

// Auto Code
#include "KTCAutoDialog.h"

// Local Framework
#include "PNXTemplateBaseParam.h"
#include "PNXTemplateBaseParamDlg.h"

class PNXTemplateBaseCmd;

/** @brief main Dialog */
class PNXTemplateBaseDlg : public KTCAutoDialog {
    friend class PNXTemplateBaseCmd;
    DeclareResource(PNXTemplateBaseDlg, KTCAutoDialog);

public:
    PNXTemplateBaseDlg(CATMMUIPanelStateCmd* iFatherCmd);
    virtual ~PNXTemplateBaseDlg();

    /** @brief Builds the panel with its control */
    void Build();

    /** @brief Build more*/
    void BuildMore();

protected:
    /** @brief Param Dialog pointer define */
    PNXTemplateBaseParamDlg* dialogMore;

    /** @brief param pointer define */
    PNXTemplateBaseParam* parameter;

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

protected: // Inset position for THE CAA2 WIZARD
private:
    // clang-format off
//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgFrame*      _FrameParams;
 CATDlgLabel*      _LabelMyCurve;
 CATDlgSelectorList*      _SelectorListMyCurve;
 CATDlgLabel*      _LabelMyResult;
 CATDlgEditor*      _EditorMyResult;
 CATDlgFrame*      _FrameMyFaces;
 CATDlgLabel*      _LabelMyFaces;
 CATDlgPushButton*      _PushButtonOption;
 CATDlgSeparator*      _Separator003;
 CATDlgSelectorList*      _SelectorListMyFaces;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};

#endif
