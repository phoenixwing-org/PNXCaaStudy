/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateFeatureDlg_H
#define PNXTemplateFeatureDlg_H

// Dialog Framework
#include "CATDialogAgent.h"
#include "CATDlgInclude.h" // needed to use Dialog framework objects
#include "CATMMUIPanelStateCmd.h"

// Auto Code
#include "KTCAutoDialog.h"

// Local Framework
#include "PNXTemplateFeatureParam.h"
#include "PNXTemplateFeatureParamDlg.h"

class PNXTemplateFeatureCmd;

/** @brief main Dialog */
class PNXTemplateFeatureDlg : public KTCAutoDialog {
    friend class PNXTemplateFeatureCmd;
    DeclareResource(PNXTemplateFeatureDlg, KTCAutoDialog);

public:
    PNXTemplateFeatureDlg(CATMMUIPanelStateCmd* iFatherCmd);
    virtual ~PNXTemplateFeatureDlg();

    /** @brief Builds the panel with its control */
    void Build();

    /** @brief Build more*/
    void BuildMore();

protected:
    /** @brief Param Dialog pointer define */
    PNXTemplateFeatureParamDlg* dialogMore;

    /** @brief param pointer define */
    PNXTemplateFeatureParam* parameter;

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
CATDlgFrame*        _FrameParams;
CATDlgLabel*        _LabelMyCurve;
CATDlgSelectorList* _SelectorListMyCurve;
CATDlgLabel*        _LabelMyAxis;
CATDlgSelectorList* _SelectorListMyAxis;
CATDlgLabel*        _LabelTransmissibility;
CATDlgEditor*       _EditorTransmissibility;
CATDlgFrame*        _FrameMyFaces;
CATDlgSelectorList* _SelectorListMyFaces;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};

#endif
