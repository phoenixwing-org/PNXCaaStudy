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

#ifndef PNXTemplateBaseCmd_H
#define PNXTemplateBaseCmd_H

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h" // Needed to derive from CATMMUIPanelStateCmd

// auto code
#include "KTCAutoDefine.h"
#include "KTCAutoHSO.h"

// Local Framework
#include "PNXTemplateBaseCore.h"
#include "PNXTemplateBaseDlg.h"
#include "PNXTemplateBaseParam.h"

// pre-declare class
class PNXITemplateBase;

// user define: do not use PNXITemplateBase_var
typedef CATISpecObject_var PNXITemplateBase_var;

/**
 * Class managing the dialog command to edit Sound Holes.
 *
 * refer to programming resources of MechanicalModelerUI framework.
 * (consult base class description).
 */
class PNXTemplateBaseCmd : public CATMMUIPanelStateCmd {

public: // base
    /** @brief Standard constructor
     * @param[in] ipInstance input instance
     */
    PNXTemplateBaseCmd();

    /** @brief Standard destructor */
    virtual ~PNXTemplateBaseCmd();

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

    /** @brief CATPathElementAgent Clear */
    void fiaAgentClear();

    /** @brief CATPathElementAgent Clear */
    void fiaAgentUpdate();

    /**
     * @brief Asks the panel to focus on an Active Field
     * @param[in] field Active Field
     */
    void SetActiveField(PNXTemplateBaseField field);

    /** @brief Update Select Mode
     */
    int UpdatefiaSelectFaces();

private: // Prevent Use function
    // Default Constructor, Copy constructor and equal operator, to prevent re-implementation
    // ----------------------------------------------------------------
    PNXTemplateBaseCmd(PNXTemplateBaseCmd&);
    PNXTemplateBaseCmd& operator=(PNXTemplateBaseCmd&);

private: // system function
    // Manage the current feature in case of ordered and linear body
    CATStatusChangeRC Activate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Cancel(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Deactivate(CATCommand* iCmd, CATNotification* iNotif);

private:
    /** @brief Manage the Element creation */
    HRESULT CreateElement();

private:
    // START KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT DECLARE

    // clang-format off
    //.............................................................................
    // @key    CmdAgentDeclare
    //.............................................................................
    KT_AUTO_CMD_AGENT_DECLARE_COMMON();
    KT_AUTO_CMD_AGENT_DECLARE_BASE(PNX, TemplateBase); 

    // Field count = 2
    KT_AUTO_CMD_AGENT_DECLARE_FIELD(MyCurve);
    KT_AUTO_CMD_AGENT_DECLARE_FIELD(MyFaces);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase CMD AGENT DECLARE

    CATISpecObject_var featurePrevious_; // previous feature
    CATISO*            catISO_;          // CATISO pointer
};

#endif
