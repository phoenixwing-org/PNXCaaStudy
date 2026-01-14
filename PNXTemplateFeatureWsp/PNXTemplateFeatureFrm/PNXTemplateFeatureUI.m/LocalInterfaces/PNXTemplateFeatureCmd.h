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

#ifndef PNXTemplateFeatureCmd_H
#define PNXTemplateFeatureCmd_H

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h" // Needed to derive from CATMMUIPanelStateCmd

// ktc
#include "KTCAutoHSO.h"

// Local Framework
#include "PNXITemplateFeature.h"
#include "PNXTemplateFeatureCore.h"
#include "PNXTemplateFeatureDlg.h"
#include "PNXTemplateFeatureParam.h"

/**
 * Class managing the dialog command to edit Sound Holes.
 *
 * refer to programming resources of MechanicalModelerUI framework.
 * (consult base class description).
 */
class PNXTemplateFeatureCmd : public CATMMUIPanelStateCmd {

public: // base
    /** @brief Standard constructor
     * @param[in] ipInstance input instance
     */
    PNXTemplateFeatureCmd(PNXITemplateFeature* ipInstance = NULL);

    /** @brief Standard destructor */
    virtual ~PNXTemplateFeatureCmd();

    /** @brief Build Graph */
    void BuildGraph();

public: // system function
    /** @brief Action for Cancel */
    CATBoolean CancelAction(void*);

    /**
     * @brief Returns a different value whether the command is used to create or edit.
     * This parameter is used by CATMMUIPanelStateCmd services.
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

    /**
     * @brief Asks the panel to focus on an Active Field
     * @param[in] field Active Field
     */
    void SetActiveField(PNXTemplateFeatureField field);

    /** @brief Update Select Mode
     */
    int UpdatefiaSelectFaces();

private: // Prevent Use function
    // Default Constructor, Copy constructor and equal operator, to prevent re-implementation
    // ----------------------------------------------------------------
    PNXTemplateFeatureCmd(PNXTemplateFeatureCmd&);
    PNXTemplateFeatureCmd& operator=(PNXTemplateFeatureCmd&);

private: // system function
    // Manage the current feature in case of ordered and linear body
    CATStatusChangeRC Activate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Cancel(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Deactivate(CATCommand* iCmd, CATNotification* iNotif);

private:
    /** @brief Manage the Element creation */
    HRESULT CreateElement();

private:
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature CMD AGENT DECLARE

    // clang-format off
    //.............................................................................
    // @key    CmdAgentDeclare
    //.............................................................................
    KT_AUTO_CMD_AGENT_DECLARE_COMMON();
    KT_AUTO_CMD_AGENT_DECLARE_BASE(PNX, TemplateFeature);

    // Field count = 2
    KT_AUTO_CMD_AGENT_DECLARE_FIELD(MyCurve);
    KT_AUTO_CMD_AGENT_DECLARE_FIELD(MyFaces);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature CMD AGENT DECLARE

    CATISpecObject_var featurePrevious_; // previous feature
    CATISO*            catISO_;          // CATISO pointer
};

#endif
