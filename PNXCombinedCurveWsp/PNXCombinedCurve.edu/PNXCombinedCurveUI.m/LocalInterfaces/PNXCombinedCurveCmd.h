#ifndef PNXCombinedCurveCmd_H
#define PNXCombinedCurveCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h"

// auto code
#include "KTCAutoCommand.h"
#include "KTCAutoHSO.h"

// local
#include "PNXCombinedCurveParam.h"
#include "PNXICombinedCurve.h"

class PNXCombinedCurveDlg;
class CATFeatureImportAgent;
class CATIPrtPart;
class CATIGSMTool;

/**
 * Class managing the dialog command to edit Combined Curves.
 *
 * refer to programming resources of MechanicalModelerUI framework.
 * (consult base class description).
 */
class PNXCombinedCurveCmd : public CATMMUIPanelStateCmd {

public:
    // Standard constructors and destructors
    // -------------------------------------
    PNXCombinedCurveCmd(PNXICombinedCurve* pCombinedCurve = NULL);
    virtual ~PNXCombinedCurveCmd();

    /**
     * Describes the different states of the command and its transitions.
     */
    void BuildGraph();

    /**
     * Method called when pressing the OK button of the panel.
     */
    CATBoolean OkAction(void*);
    /**
     * Method called when pressing the Cancel button of the panel.
     */
    CATBoolean CancelAction(void*);

    /**
     * Returns a different value whether the command is used to create or edit a Combined Curve.
     * This parameter is used by CATMMUIPanelStateCmd services.
     */
    int GetMode();

    /**
     * Returns a pointer to the dialog panel.
     * This pointer is used by CATMMUIPanelStateCmd services.
     */
    CATDlgDialog* GiveMyPanel();

    /**
     * Method called when a curve is selected.
     */
    CATBoolean PointSelected(void*);

    /**
     * Method called when a direction is selected.
     */
    CATBoolean DirectionSelected(void*);

    /**
     * Method called when a curve or a line is selected, to add or remove it of
     * the definition of the Combined Curve.
     */
    void ElementSelected(CATFeatureImportAgent* pAgent);

    /**
     * Method called when the field correponding to Curve.1 is selected.
     */
    CATBoolean FirstPointFieldSelected(void*);

    /**
     * Method called when the field correponding to MainDir is selected.
     */
    CATBoolean MainDirFieldSelected(void*);

    /**
     * Method called when the field correponding to Curve.1 is selected.
     */
    CATBoolean OnPushButtonSaveJsonAgent(void*);

    /**
     * Method called for call back
     */
    void OnPushButtonCB(CATCommand* iCmd, CATNotification* iNotif, CATCommandClientData iData);

    /**
     * Asks the panel to focus on an Active Field
     */
    void SetActiveField(int ActiveField);

private:
    // Default Constructor, Copy constructor and equal operator, to prevent reimplementation
    // ----------------------------------------------------------------
    PNXCombinedCurveCmd(PNXCombinedCurveCmd&);
    PNXCombinedCurveCmd& operator=(PNXCombinedCurveCmd&);

private:
    // Manage the combined curve creation
    //
    HRESULT CreateCombinedCurve();
    // Manage the current feature in case of ordered and linear body
    //
    CATStatusChangeRC Activate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Deactivate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Cancel(CATCommand* iCmd, CATNotification* iNotif);

private:
    PNXICombinedCurve_var  feature;          // this feature
    PNXCombinedCurveParam* parameter;        // this parameter
    CATISpecObject_var     featurePrevious_; // previous feature
    PNXCombinedCurveDlg*   dialog;
    CATFrmEditor*          catFrmEditor_;
    CATHSO*                catHSO_;
    KTCAutoHSO             ktcHSO_;
    int                    _ActiveField;
    int                    mode_;
    CATFeatureImportAgent* _pFirstPointAgent;
    CATFeatureImportAgent* _pMainDirAgent;
    CATDialogAgent*        _pFirstPointFieldAgent;
    CATDialogAgent*        _pMainDirFieldAgent;
    CATDialogAgent*        _pPushButtonSaveJsonAgent; ///< save button agent
};

#endif
