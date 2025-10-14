#ifndef PNXECombinedCurve_H
#define PNXECombinedCurve_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

class CATISpecObject;

/**
 * Class extending the object "CombinedCurve".
 *
 * It implements the interface :
 *      PNXCombinedCurve.edu.PNXICombinedCurve
 */

class PNXECombinedCurve : public CATBaseUnknown {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXECombinedCurve();
    virtual ~PNXECombinedCurve();

    /**
     * Implements the method SetFirstPoint of the interface PNXCombinedCurve.
     * see PNXCombinedCurve.edu.PNXICombinedCurve.SetFirstPoint
     */
    HRESULT SetFirstPoint(CATISpecObject* ipiValue);

    /**
     * Implements the method GetFirstPoint of the interface PNXCombinedCurve.
     * see PNXCombinedCurve.edu.PNXICombinedCurve.GetFirstPoint
     */
    HRESULT GetFirstPoint(CATISpecObject** opiValue);

    /**
     * Implements the method SetMainDir of the interface PNXCombinedCurve.
     * see PNXCombinedCurve.edu.PNXICombinedCurve.SetMainDir
     */
    HRESULT SetMainDir(CATISpecObject* ipiValue);

    /**
     * Implements the method GetMainDir of the interface PNXCombinedCurve.
     * see PNXCombinedCurve.edu.PNXICombinedCurve.GetMainDir
     */
    HRESULT GetMainDir(CATISpecObject** opiValue);

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurve(PNXECombinedCurve&);
    PNXECombinedCurve& operator=(PNXECombinedCurve&);
};

#endif
