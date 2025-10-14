#ifndef PNXCombinedCurveCatalogEnable_H
#define PNXCombinedCurveCatalogEnable_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // To derive from

/**
 * Class extending the object "CombinedCurve".
 * It implements the interface :
 *      ComponentsCatalogsInterfaces.CATICatalogEnable
 */

class PNXCombinedCurveCatalogEnable : public CATBaseUnknown {
    CATDeclareClass;

public:
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
    PNXCombinedCurveCatalogEnable();
    virtual ~PNXCombinedCurveCatalogEnable();

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXCombinedCurveCatalogEnable(PNXCombinedCurveCatalogEnable& iObjectToCopy);
    PNXCombinedCurveCatalogEnable& operator=(PNXCombinedCurveCatalogEnable& iObjectToCopy);
};

#endif
