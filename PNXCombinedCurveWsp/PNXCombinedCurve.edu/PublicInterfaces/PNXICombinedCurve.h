// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef PNXICombinedCurve_H
#define PNXICombinedCurve_H

// CAA
#include "CATBaseUnknown.h"
#include "CATISpecObject.h"

// Local Framework
#include "PNXCombinedCurveParam.h"

extern ExportedByPNXCombinedCurve IID IID_PNXICombinedCurve;

/**
 * Interface to manage Combined Curves.
 *
 *  Role : use this interface to get / set the input of a Combined Curve.
 *         A Combined Curve is the intersection of two extruded surfaces.
 */

class ExportedByPNXCombinedCurve PNXICombinedCurve : public CATBaseUnknown {
    CATDeclareInterface;

public:
    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve INTERFACES HEAD GET

    // clang-format off
public: // Get
    /**
     * @brief First Point
     * @return CATISpecObject_var
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    virtual CATISpecObject_var GetFirstPoint() const = 0;

    /**
     * @brief Main Dir
     * @return CATISpecObject_var
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    virtual CATISpecObject_var GetMainDir() const = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve INTERFACES HEAD GET

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve INTERFACES HEAD SET

    // clang-format off
public: // Set
    /**
     * @brief First Point
     * @param[in] value CATISpecObject_var
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    virtual HRESULT SetFirstPoint(const CATISpecObject_var& value, const CATBoolean& checkExist = CATTrue) = 0;

    /**
     * @brief Main Dir
     * @param[in] value CATISpecObject_var
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    virtual HRESULT SetMainDir(const CATISpecObject_var& value, const CATBoolean& checkExist = CATTrue) = 0;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve INTERFACES HEAD SET
};
/** @brief Macro for Handlers  */
CATDeclareHandler(PNXICombinedCurve, CATBaseUnknown);
#endif
