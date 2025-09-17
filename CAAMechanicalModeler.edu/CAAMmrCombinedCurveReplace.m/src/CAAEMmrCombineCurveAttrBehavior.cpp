// COPYRIGHT DASSAULT SYSTEMES 2000
#include <CAAEMmrCombineCurveAttrBehavior.h>

// System Framework
#include "CATUnicodeString.h"       // To handle Unicode String 
#include "CATCollec.h"

// GeometricObjects Framework
#include "CATLine.h"                // To put the CATLine IID in the CATBehaviorSpecs 

// MechanicalModeler Framework
#include "CATIMfMonoDimResult.h"    // To put the CATIMfMonoDimResult IID int the CATBehaviorSpecs

#include <iostream.h>

CATImplementClass(CAAEMmrCombineCurveAttrBehavior,CodeExtension,CATBaseUnknown,CombinedCurve);

#include "TIE_CATIAttrBehavior.h"
TIE_CATIAttrBehavior(CAAEMmrCombineCurveAttrBehavior);

// 
// To declare that CombineCurve implements CATIAttrBehavior,   
// insert these following lines in the interface dictionary:
//
//    CombinedCurve        CATIAttrBehavior    libCAAMmrCombinedCurveReplace
//
//-----------------------------------------------------------------------------


//========================================================================
// Constructor - Destructor
//========================================================================
CAAEMmrCombineCurveAttrBehavior::CAAEMmrCombineCurveAttrBehavior():CATBaseUnknown()
{
    cout << "CAAEMmrCombineCurveAttrBehavior::CAAEMmrCombineCurveAttrBehavior" << endl;
}

CAAEMmrCombineCurveAttrBehavior::~CAAEMmrCombineCurveAttrBehavior()
{
    cout << "CAAEMmrCombineCurveAttrBehavior::~CAAEMmrCombineCurveAttrBehavior" << endl;
}

//------------------------------------------------------------------------
//   GetRequestedBehavior
//------------------------------------------------------------------------
HRESULT CAAEMmrCombineCurveAttrBehavior::GetRequestedBehavior(const CATUnicodeString* ipAttrId, CATBehaviorSpecs** oppBehavior)
{
   cout << "CAAEMmrCombineCurveAttrBehavior::GetRequestedBehavior" << endl;

   HRESULT exit=E_FAIL;
   if ( (NULL != oppBehavior) && ( NULL != ipAttrId) )
   {
      *oppBehavior = new CATBehaviorSpecs;

      if ( NULL != *oppBehavior )
      {
         // If the input String is equal to "Curve1" or "Curve2" which are the name 
         // of two attributes then the Filter will be IID_CATIMfMonoDimResult
         // That is to say, we can Replace in those two attributes a Feature 
         // implementing the interface CATIMfMonoDimResult by another one 
         if (2 == ipAttrId->Compare("Curve1") || 2 == ipAttrId->Compare("Curve2"))
         {
            CATListPV* aMyFirstList = new CATListPV;
            aMyFirstList->Append((void*)&IID_CATIMfMonoDimResult);
            (*oppBehavior)->Append(aMyFirstList);
            exit = S_OK ;
         }
         // If the input String is equal to "Direction1" or "Direction2" which are the name 
         // of two attributes then the Filter will be IID_CATLine
         // That is to say, we can Replace in those two attributes a Feature 
         // implementing the interface CATLine by another one
         else if (2 == ipAttrId->Compare("Direction1") || 2 == ipAttrId->Compare("Direction2"))
         {
            CATListPV* aMyFirstList = new CATListPV;
            aMyFirstList->Append((void*)&IID_CATLine);
            (*oppBehavior)->Append(aMyFirstList);
            exit = S_OK ;
         }
      }
   }

   return exit;
}
