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

#ifndef PNXCurveDivisionCmd_H
#define PNXCurveDivisionCmd_H

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h" // Needed to derive from CATMMUIPanelStateCmd

// Local Framework
#include "PNXCurveDivisionCore.h"
#include "PNXCurveDivisionDlg.h"
#include "PNXCurveDivisionParam.h"

// auto code
#include "KTCAutoCode.h"

/**
 * Class managing the dialog command to edit User Features.
 *
 * refer to programming resources of MechanicalModelerUI framework.
 * (consult base class description).
 */
class PNXCurveDivisionCmd : public CATMMUIPanelStateCmd {

public: // base
    /** @brief Standard constructor
     * @param[in] ipInstance input instance
     */
    PNXCurveDivisionCmd();

    /** @brief Standard destructor */
    virtual ~PNXCurveDivisionCmd();

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
    void SetActiveField(PNXCurveDivisionField field);

private: // Prevent Use function
    // Default Constructor, Copy constructor and equal operator, to prevent
    // re-implementation
    // ----------------------------------------------------------------
    PNXCurveDivisionCmd(PNXCurveDivisionCmd&);
    PNXCurveDivisionCmd& operator=(PNXCurveDivisionCmd&);

private: // system function
    // Manage the current feature in case of ordered and linear body
    CATStatusChangeRC Activate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Cancel(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Deactivate(CATCommand* iCmd, CATNotification* iNotif);

private:
    /**
     * Method called when a curve is selected.
     */
    CATBoolean CurveSelected(void*);

    /**
     * Method called when a curve or a line is selected, to add or remove it of
     * the definition of the Combined Curve.
     */
    void ElementSelected(CATFeatureImportAgent* pAgent);

    /**
     * Method called when the field correponding to Curve.1 is selected.
     */
    CATBoolean BaseCurveFieldSelected(void*);

private:
    CATISpecObject_var     featurePrevious_; // previous feature
    CATISpecObject_var     feature;          // feature
    PNXCurveDivisionParam* parameter;        // create Default value Instance
    PNXCurveDivisionCore*  core;
    PNXCurveDivisionDlg*   dialog;

    CATFeatureImportAgent* _pBaseCurveAgent;
    CATDialogAgent*        _pBaseCurveFieldAgent; ///< save button agent

    KT_AUTO_CMD_AGENT_DECLARE_COMMON();
};

#endif
