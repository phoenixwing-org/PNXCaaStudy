#ifndef PNXCombinedCurveDlg_H
#define PNXCombinedCurveDlg_H

// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CATDlgInclude.h" // needed to use Dialog framework objects

// Auto Code
#include "KTCAutoDialog.h"

/**
 * Field enum for input field
 */
enum PNXCopyStudyField {
    PNXCopyStudyFieldUnkown     = 0,
    PNXCopyStudyFieldFirstPoint = 1,
    PNXCopyStudyFieldMainDir    = 2
};

/**
 * Action enum
 */
enum PNXCopyStudyAction {
    PNXCopyStudyActionDirectCallback = 0,
    PNXCopyStudyActionSubDialog      = 1
};

class PNXSubCurveDlg;

/**
 * Class managing the dialog panel used for a Combined Curve creation / edition.
 *
 * refer to programming resources of Dialog framework.
 * (consult base class description).
 */
class PNXCombinedCurveDlg : public KTCAutoDialog {

    DeclareResource(PNXCombinedCurveDlg, KTCAutoDialog);

public:
    PNXCombinedCurveDlg();
    virtual ~PNXCombinedCurveDlg();

    /**
     * Builds the panel with its control.
     */
    void Build();

public:
    /**
     * Returns the field_number-th field of the panel.
     */
    CATDlgSelectorList* GetField(int iFieldNumber);

    /**
     * Sets the focus on the active entry field
     */
    void SetActiveField(int iFieldNumber);

    /**
     * Writes name in the field_number-th field.
     */
    void SetName(int iFieldNumber, CATUnicodeString iName);

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

public:
    CATDlgSelectorList *_selectorListFirstPoint, *_selectorListMainDir;

    CATDlgPushButton* _pushButtonSaveJson;       ///< save json button
    CATDlgPushButton* _pushButtonDirectCallback; ///< Direct callback button
    CATDlgPushButton* _pushButtonSubDialog;      ///< sample
    PNXSubCurveDlg*   _subPanel;                 // sub pannel
};

#endif
