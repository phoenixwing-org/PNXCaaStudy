#ifndef CAAEMmrCombinedCurve_H
#define CAAEMmrCombinedCurve_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * Class extending the object "CombinedCurve".
 *  
 * It implements the interface :
 *      CAAMechanicalModeler.edu.CAAIMmrCombinedCurve
 */

class CAAEMmrCombinedCurve: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    CAAEMmrCombinedCurve ();
    virtual ~CAAEMmrCombinedCurve ();
    
    /**
    * Implements the method SetFirstPoint of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.SetFirstPoint
    */
    HRESULT SetFirstPoint ( CATISpecObject *ipiValue ) ;
    
    /**
    * Implements the method GetFirstPoint of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.GetFirstPoint
    */
    HRESULT GetFirstPoint ( CATISpecObject **opiValue )  ;
    
    /**
    * Implements the method SetMainDir of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.SetMainDir
    */
    HRESULT SetMainDir ( CATISpecObject *ipiValue )  ;
    
    /**
    * Implements the method GetMainDir of the interface CAAMmrCombinedCurve.
    * see CAAMechanicalModeler.edu.CAAIMmrCombinedCurve.GetMainDir
    */
    HRESULT GetMainDir ( CATISpecObject **opiValue ) ;
    

    
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCombinedCurve (CAAEMmrCombinedCurve &);
    CAAEMmrCombinedCurve& operator=(CAAEMmrCombinedCurve&);
    
};

#endif
