#ifndef PNXECombinedCurveFactory_H
#define PNXECombinedCurveFactory_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * Class extending the CATPrtCont object: The container of specifications
 * in the Part document.
 *
 * It implements the interfaces :
 *      PNXCombinedCurve.edu.PNXICombinedCurveFactory
 */

class PNXECombinedCurveFactory : public CATBaseUnknown {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXECombinedCurveFactory();
    virtual ~PNXECombinedCurveFactory();

    /**
     * Implements the method CreateCombinedCurve of the interface PNXICombinedCurveFactory
     * see PNXCombinedCurve.edu.PNXICombinedCurveFactory.CreateCombinedCurve
     */
    HRESULT CreateCombinedCurve(CATISpecObject*  ipiSpecOnFirstPoint,
                                CATISpecObject*  ipiSpecOnMainDir,
                                CATISpecObject** opiSpecOnCombinedCurve);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurveFactory(PNXECombinedCurveFactory&);
    PNXECombinedCurveFactory& operator=(PNXECombinedCurveFactory&);
};

#endif
