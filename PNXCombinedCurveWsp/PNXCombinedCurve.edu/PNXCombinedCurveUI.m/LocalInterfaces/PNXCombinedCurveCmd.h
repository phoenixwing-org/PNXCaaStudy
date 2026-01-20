#ifndef PNXCombinedCurveCmd_H
#define PNXCombinedCurveCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h"

// auto code
#include "KTCAutoCommand.h"

class PNXCombinedCurveDlg;
class PNXICombinedCurve;
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
     * Returns the featurebeing created or edited
     * This parameter is used by CATMMUIStateCmd services.
     */
    CATISpecObject_var GiveMyFeature();

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

    /**
     * Ask the panel to update the texts in the fields.
     */
    void UpdatePanelFields();

    /**
     * Prevents the user from clicking the OK button if a entry field is not filled in.
     */
    void CheckOKSensitivity();

private:
    // Default Constructor, Copy constructor and equal operator, to prevent reimplementation
    // ----------------------------------------------------------------
    PNXCombinedCurveCmd(PNXCombinedCurveCmd&);
    PNXCombinedCurveCmd& operator=(PNXCombinedCurveCmd&);

    // Manage the combined curve creation
    //
    HRESULT CreateCombinedCurve();
    HRESULT CreateTool(CATIPrtPart* pIPrtPart, CATIGSMTool** pIGsmtool);

    HRESULT LookingForAnyTypeOfBody(CATIGSMTool** piGsmtool);
    HRESULT LookingForGeomSetOrOrderedGeomSet(CATIGSMTool** piGsmtool);
    HRESULT LookingForGeomSet(CATIGSMTool** piGsmtool);

    // Manage the current feature in case of ordered and linear body
    //
    CATStatusChangeRC Activate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Deactivate(CATCommand* iCmd, CATNotification* iNotif);
    CATStatusChangeRC Cancel(CATCommand* iCmd, CATNotification* iNotif);

private:
    PNXICombinedCurve* _piCombinedCurve;
    CATISpecObject_var feature;

    CATISpecObject_var featurePrevious_;

    CATFeatureImportAgent* _pFirstPointAgent;
    CATFeatureImportAgent* _pMainDirAgent;

    CATDialogAgent *_pFirstPointFieldAgent, *_pMainDirFieldAgent,
        *_pPushButtonSaveJsonAgent; ///< save button agent

    CATISpecObject *_piSpecOnFirstPoint, *_piSpecOnMainDir;

    PNXCombinedCurveDlg* _panel;

    CATFrmEditor* catFrmEditor_;

    CATHSO* _HSO;

    int _ActiveField;
    int mode_;
};

#endif
