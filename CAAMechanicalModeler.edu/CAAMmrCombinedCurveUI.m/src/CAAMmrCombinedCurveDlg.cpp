// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAMmrCombinedCurveDlg.h"   

//ApplicationFrame Framework
#include "CATApplicationFrame.h"    // needed to get the window of the frame

//Dialog Framework
#include "CATDlgGridConstraints.h"  // needed to locate dialog element on the box's grid
#include "CATDlgLabel.h"

//System Framework
#include "CATUnicodeString.h"
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------

CAAMmrCombinedCurveDlg::CAAMmrCombinedCurveDlg( ) :
CATDlgDialog ( ( CATApplicationFrame::GetApplicationFrame() ) -> GetMainWindow ( ) ,
               "CombinedCurve", 
               CATDlgGridLayout | CATDlgWndOK | CATDlgWndCANCEL | CATDlgWndNoResize ),
_selectorListGuideCurve   ( NULL ),
_selectorListBaseSurface   ( NULL ),
_selectorListMainDir     ( NULL ),
_selectorListStartPoint     ( NULL )
{
    // never call the Build method of the panel from the constructor
    // it is much better to call it from the same method that created (new) the panel
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------

CAAMmrCombinedCurveDlg::~CAAMmrCombinedCurveDlg()
{
    //  Do not delete the control elements of your dialog: 
    //     this is done automatically
    //  --------------------------------------------------
    
    _selectorListGuideCurve   = NULL ;
    _selectorListBaseSurface   = NULL ;
    _selectorListMainDir     = NULL ;
    _selectorListStartPoint     = NULL ;


}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::Build()
//-------------------------------------------------------------------------

void CAAMmrCombinedCurveDlg::Build()
{
    // Creates the CATDlgLabel for the input field's names.

    CATDlgLabel * labelGuideCurve = new CATDlgLabel( this , CATString("labelGuideCurve") );
    
    CATDlgLabel * labelMainDir = new CATDlgLabel( this , CATString("labelMainDir") );
    
    CATDlgLabel * labelBaseSurface = new CATDlgLabel( this , CATString("labelBaseSurface") );
    
    CATDlgLabel * labelStartPoint = new CATDlgLabel( this , CATString("labelStartPoint") );
    
    // Creates the four input fields .
    CATUnicodeString Prompt_nosel = "no selection";

    _selectorListGuideCurve = new CATDlgSelectorList( this , CATString("selc1"),CATDlgDataModify);
    _selectorListGuideCurve->SetVisibleTextHeight(1);
    _selectorListGuideCurve->SetLine(Prompt_nosel,0,CATDlgDataModify);

    _selectorListMainDir   = new CATDlgSelectorList( this , CATString("seld1"),CATDlgDataModify);
    _selectorListMainDir->SetVisibleTextHeight(1);
    _selectorListMainDir->SetLine(Prompt_nosel,0,CATDlgDataModify);

    _selectorListBaseSurface = new CATDlgSelectorList( this , CATString("selc2"),CATDlgDataModify);
    _selectorListBaseSurface->SetVisibleTextHeight(1);
    _selectorListBaseSurface->SetLine(Prompt_nosel,0,CATDlgDataModify);
    
    _selectorListStartPoint   = new CATDlgSelectorList( this , CATString("seld2"),CATDlgDataModify);
    _selectorListStartPoint->SetVisibleTextHeight(1);
    _selectorListStartPoint->SetLine(Prompt_nosel,0,CATDlgDataModify);
        
    
    // Uses the grid of the panel to position the label and the input fields.
    CATDlgGridConstraints cst;  
    cst.Justification = CATGRID_4SIDES;
    cst.H_Span=1;     cst.V_Span=1;
    
    // first column : labels.
    cst.Column=0;     
    
    cst.Row=0; labelMainDir   -> SetGridConstraints(cst);
    cst.Row=1; labelGuideCurve -> SetGridConstraints(cst);
    cst.Row=2; labelBaseSurface -> SetGridConstraints(cst);
    cst.Row=3; labelStartPoint   -> SetGridConstraints(cst);
        
    // second column : input fields.
    cst.Column=1;     
    
    cst.Row=0; _selectorListGuideCurve -> SetGridConstraints(cst);
    cst.Row=1; _selectorListMainDir   -> SetGridConstraints(cst);
    cst.Row=2; _selectorListBaseSurface -> SetGridConstraints(cst);
    cst.Row=3; _selectorListStartPoint   -> SetGridConstraints(cst);
    
    // Finally, makes the panel appear.
    SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::SetActiveField()
//-------------------------------------------------------------------------

void CAAMmrCombinedCurveDlg::SetActiveField(int iFieldNumber)
{
    //  Deselects all others field when changing of active field ( by clicking in another one ).
    if ( PNXCopyStudyFieldGuideCurve != iFieldNumber ) _selectorListGuideCurve -> ClearSelect();
    if ( PNXCopyStudyFieldMainDir  != iFieldNumber ) _selectorListMainDir   -> ClearSelect();
    if ( PNXCopyStudyFieldBaseSurface != iFieldNumber ) _selectorListBaseSurface -> ClearSelect();
    if ( PNXCopyStudyFieldStartPoint  != iFieldNumber ) _selectorListStartPoint   -> ClearSelect();
    return ;
}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::SetName()
//-------------------------------------------------------------------------

void CAAMmrCombinedCurveDlg::SetName(int iFieldNumber , CATUnicodeString iName )
{
    // Writes the name of the selected objet in the active field.
    // Replaces it if the object was already selected.
    
    switch (iFieldNumber )
    {
    case PNXCopyStudyFieldGuideCurve  : { _selectorListGuideCurve -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case PNXCopyStudyFieldMainDir  : { _selectorListMainDir   -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case PNXCopyStudyFieldBaseSurface : { _selectorListBaseSurface -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    case PNXCopyStudyFieldStartPoint  : { _selectorListStartPoint   -> SetLine ( iName , 0 , CATDlgDataModify ); return; }
    }
    return ;
}

//-------------------------------------------------------------------------
// CAAMmrCombinedCurveDlg::GetField()
//-------------------------------------------------------------------------

CATDlgSelectorList* CAAMmrCombinedCurveDlg::GetField(int iFieldNumber)
{
    // returns the active field ( used by the state command ).
    switch (iFieldNumber )
    {   
    case PNXCopyStudyFieldGuideCurve  : return _selectorListGuideCurve;
    case PNXCopyStudyFieldMainDir  : return _selectorListMainDir ;
    case PNXCopyStudyFieldBaseSurface : return _selectorListBaseSurface;
    case PNXCopyStudyFieldStartPoint  : return _selectorListStartPoint;
    }
    return NULL ;
}

