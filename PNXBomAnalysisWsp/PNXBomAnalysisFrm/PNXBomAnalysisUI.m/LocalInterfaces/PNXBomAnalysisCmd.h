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

#ifndef PNXBomAnalysisCmd_H
#define PNXBomAnalysisCmd_H

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h" // Needed to derive from CATMMUIPanelStateCmd

// Local Framework
#include "PNXBomAnalysisCore.h"
#include "PNXBomAnalysisDlg.h"
#include "PNXBomAnalysisParam.h"

// auto code
#include "KTCAutoCode.h"
#include "KTCAutoHSO.h"

/**
 * Class managing the dialog command to edit Sound Holes.
 *
 * refer to programming resources of MechanicalModelerUI framework.
 * (consult base class description).
 */
class PNXBomAnalysisCmd : public CATMMUIPanelStateCmd {

public: // base
    /** @brief Standard constructor
     * @param[in] ipInstance input instance
     */
    PNXBomAnalysisCmd();

    /** @brief Standard destructor */
    virtual ~PNXBomAnalysisCmd();

    /** @brief Build Graph */
    void BuildGraph();

public: // system function
    /** @brief Action for Cancel */
    CATBoolean CancelAction(void*);

    /**
     * @brief Returns a different value whether the command is used to create or
     * edit. This parameter is used by CATMMUIPanelStateCmd services.
     */
    int GetMode();

    /**
     * @brief Returns the feature being created or edited
     * This parameter is used by CATMMUIStateCmd services.
     */
    CATISpecObject_var GiveMyFeature();

    /**
     * @brief Returns a pointer to the dialog panel.
     * This pointer is used by CATMMUIPanelStateCmd services.
     */
    CATDlgDialog* GiveMyPanel();

    /** @brief Action for OK */
    CATBoolean OkAction(void*);

    /** @brief Action for Preview */
    CATBoolean PreviewAction(void*);

public:
    /** @brief Method called when obj is selected */
    CATBoolean ActionSelectorListFia(void*);

    /** @brief Method called when Field is selected */
    CATBoolean ActionSelectorListPda(void*);

    /** @brief Method called when Value Change */
    CATBoolean ActionValueChange(void*);

    /** @brief called after value changed */
    void AfterValueChange(bool isUpdateObj = false);

    /** @brief CATFeatureImportAgent Clear */
    void fiaAgentClear();

    /** @brief CATFeatureImportAgent Clear */
    void fiaAgentUpdate();

    /** @brief Callback on PushBActivate of _PushButtonJson */
    void OnOutputBomCB(CATCommand*, CATNotification*, CATCommandClientData data);

    /**
     * @brief Asks the panel to focus on an Active Field
     * @param[in] field Active Field
     */
    void SetActiveField(PNXBomAnalysisField field);

private: // Prevent Use function
    // Default Constructor, Copy constructor and equal operator, to prevent
    // re-implementation
    // ----------------------------------------------------------------
    PNXBomAnalysisCmd(PNXBomAnalysisCmd&);
    PNXBomAnalysisCmd& operator=(PNXBomAnalysisCmd&);

private: // system function
    // Manage the current feature in case of ordered and linear body
    CATStatusChangeRC Activate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Cancel(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Deactivate(CATCommand* iCmd, CATNotification* iNotif);

private:
    /** @brief Manage the Element creation */
    HRESULT CreateElement();

private:
    CATISpecObject_var   _featurePrevious;   // previous feature
    CATISpecObject_var   feature;            // feature
    PNXBomAnalysisParam* parameter;          // create Default value Instance
    PNXBomAnalysisCore*  core;               // core lass
    PNXBomAnalysisDlg*   dialog;             // main dialog
    CATPathElementAgent* _pfiaElementSelect; // path element

    KT_AUTO_CMD_AGENT_DECLARE_COMMON();
};

#endif
