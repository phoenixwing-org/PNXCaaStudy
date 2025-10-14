// COPYRIGHT DASSAULT SYSTEMES 2000

#ifndef PNXICombinedCurveFactory_H
#define PNXICombinedCurveFactory_H

// Local Framework
#include "PNXCombinedCurve.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;

extern ExportedByPNXCombinedCurve IID IID_PNXICombinedCurveFactory;

/**
 * Interface to create a Combined Curve.
 *
 * Role : use this interface to create a Combined Curve.
 *        A Combined Curve is the intersection of two extruded surfaces.
 *        Each of the two surfaces is buildt using a curve (profile) and a direction (of extrusion).
 *        Consequently, a Combined Curve has two input curves and two input directions.
 */

class ExportedByPNXCombinedCurve PNXICombinedCurveFactory : public CATBaseUnknown {
    CATDeclareInterface;

public:
    /**
     * Creates a Combined Curve.
     * param ipFirstPoint       : the FirstPoint.
     * param ipMainDir   : the MainDir.
     * param opCombinedCurve : the resulting Combined Curve.
     *
     * returns the result of the creation.
     *     Legal values : S_OK   the creation of the Combined Curve succeeded.
     *                    E_FAIL the creation of the Combined Curve failed.
     */
    virtual HRESULT CreateCombinedCurve(CATISpecObject* ipFirstPoint, CATISpecObject* ipMainDir,
                                        CATISpecObject** opCombinedCurve) = 0;
};

#endif
