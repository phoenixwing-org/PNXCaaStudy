#ifndef PNXCombinedCurveDlg_H
#define PNXCombinedCurveDlg_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// Dialog Framework
#include "CATDlgDialog.h"  // needed to derive from CATDlgDialog
#include "CATDlgInclude.h" // needed to use Dialog framework objects

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
    PNXCopyStudyActionSample         = 1
};

class PNXSubCurveDlg;

/**
 * Class managing the dialog panel used for a Combined Curve creation / edition.
 *
 * refer to programming resources of Dialog framework.
 * (consult base class description).
 */
class PNXCombinedCurveDlg : public CATDlgDialog {

    DeclareResource(PNXCombinedCurveDlg, CATDlgDialog);

public:
    PNXCombinedCurveDlg();
    virtual ~PNXCombinedCurveDlg();

    /**
     * Builds the panel with its control.
     */
    void Build();

    /**
     * Sets the focus on the active entry field
     */
    void SetActiveField(int iFieldNumber);

    /**
     * Writes name in the field_number-th field.
     */
    void SetName(int iFieldNumber, CATUnicodeString iName);

    /**
     * Returns the field_number-th field of the panel.
     */
    CATDlgSelectorList* GetField(int iFieldNumber);

public:
    CATDlgSelectorList *_selectorListFirstPoint, *_selectorListMainDir;

    CATDlgPushButton* _pushButtonSaveJson;       ///< save json button
    CATDlgPushButton* _pushButtonDirectCallback; ///< Direct callback button
    CATDlgPushButton* _pushButtonSample;         ///< sample
    PNXSubCurveDlg*   _subPanel;                 // sub pannel
};

#endif
