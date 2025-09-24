// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAMmrCombinedCurveDlg.h"

// ApplicationFrame Framework
#include "CATApplicationFrame.h" // needed to get the window of the frame

// Dialog Framework
#include "CATDlgGridConstraints.h" // needed to locate dialog element on the box's grid
#include "CATDlgLabel.h"

// System Framework
#include "CATUnicodeString.h"
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------

CAAMmrCombinedCurveDlg::CAAMmrCombinedCurveDlg() : CATDlgDialog((CATApplicationFrame::GetApplicationFrame())->GetMainWindow(),
                                                                "CombinedCurve",
                                                                CATDlgGridLayout | CATDlgWndOK | CATDlgWndCANCEL | CATDlgWndNoResize),
                                                   _selectorListFirstPoint(NULL),
                                                   _selectorListMainDir(NULL),
                                                   _pushButtonSaveJson(NULL)
{
    // never call the Build method of the panel from the constructor
    // it is much better to call it from the same method that created (new) the panel
}
//-------------------------------------------------------------------------
CAAMmrCombinedCurveDlg::~CAAMmrCombinedCurveDlg()
{
    //  Do not delete the control elements of your dialog:
    //     this is done automatically
    //  --------------------------------------------------

    _selectorListFirstPoint = NULL;
    _selectorListMainDir = NULL;
    _pushButtonSaveJson = NULL;
}
//-------------------------------------------------------------------------
void CAAMmrCombinedCurveDlg::Build()
{
    // Creates the CATDlgLabel for the input field's names.

    CATDlgLabel *labelFirstPoint = new CATDlgLabel(this, CATString("labelFirstPoint"));

    CATDlgLabel *labelMainDir = new CATDlgLabel(this, CATString("labelMainDir"));

    // Creates the four input fields .
    CATUnicodeString Prompt_nosel = "no selection";

    _selectorListFirstPoint = new CATDlgSelectorList(this, CATString("selc1"), CATDlgDataModify);
    _selectorListFirstPoint->SetVisibleTextHeight(1);
    _selectorListFirstPoint->SetLine(Prompt_nosel, 0, CATDlgDataModify);

    _selectorListMainDir = new CATDlgSelectorList(this, CATString("seld1"), CATDlgDataModify);
    _selectorListMainDir->SetVisibleTextHeight(1);
    _selectorListMainDir->SetLine(Prompt_nosel, 0, CATDlgDataModify);

    // Creates the save json button.
    _pushButtonSaveJson = new CATDlgPushButton(this, CATString("pushButtonSaveJson"));
    _pushButtonSaveJson->SetName(CATString("Save Json"));
    _pushButtonSaveJson->SetIconName("I_CombinedCurve");

    // Uses the grid of the panel to position the label and the input fields.
    CATDlgGridConstraints cst;
    cst.Justification = CATGRID_4SIDES;
    cst.H_Span = 1;
    cst.V_Span = 1;

    // first column : labels.
    cst.Column = 0;

    cst.Row = 0;
    labelMainDir->SetGridConstraints(cst);
    cst.Row = 1;
    labelFirstPoint->SetGridConstraints(cst);

    // second column : input fields.
    cst.Column = 1;

    cst.Row = 0;
    _selectorListFirstPoint->SetGridConstraints(cst);
    cst.Row = 1;
    _selectorListMainDir->SetGridConstraints(cst);

    cst.Row = 2;
    _pushButtonSaveJson->SetGridConstraints(cst);

    // Finally, makes the panel appear.
    SetVisibility(CATDlgShow);
}
//-------------------------------------------------------------------------
void CAAMmrCombinedCurveDlg::SetActiveField(int iFieldNumber)
{
    //  Deselects all others field when changing of active field ( by clicking in another one ).
    if (PNXCopyStudyFieldFirstPoint != iFieldNumber)
        _selectorListFirstPoint->ClearSelect();
    if (PNXCopyStudyFieldMainDir != iFieldNumber)
        _selectorListMainDir->ClearSelect();
    return;
}
//-------------------------------------------------------------------------
void CAAMmrCombinedCurveDlg::SetName(int iFieldNumber, CATUnicodeString iName)
{
    // Writes the name of the selected objet in the active field.
    // Replaces it if the object was already selected.

    switch (iFieldNumber)
    {
    case PNXCopyStudyFieldFirstPoint:
    {
        _selectorListFirstPoint->SetLine(iName, 0, CATDlgDataModify);
        return;
    }
    case PNXCopyStudyFieldMainDir:
    {
        _selectorListMainDir->SetLine(iName, 0, CATDlgDataModify);
        return;
    }
    }
    return;
}
//-------------------------------------------------------------------------
CATDlgSelectorList *CAAMmrCombinedCurveDlg::GetField(int iFieldNumber)
{
    // returns the active field ( used by the state command ).
    switch (iFieldNumber)
    {
    case PNXCopyStudyFieldFirstPoint:
        return _selectorListFirstPoint;
    case PNXCopyStudyFieldMainDir:
        return _selectorListMainDir;
    }
    return NULL;
}
