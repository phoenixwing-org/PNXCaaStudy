#ifndef PNXECombinedCurve_H
#define PNXECombinedCurve_H
// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h" // needed to derive from CATBaseUnknown

// auto code
#include "KTCAutoAttrAccess.h"
#include "PNXCombinedCurveParam.h"

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

public:
    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS HEAD GET

    // clang-format off
public: // Get
    /**
     * @brief First Point
     * @return CATISpecObject_var
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    CATISpecObject_var GetFirstPoint() const;

    /**
     * @brief Main Dir
     * @return CATISpecObject_var
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    CATISpecObject_var GetMainDir() const;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS HEAD GET

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS HEAD SET

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
    HRESULT SetFirstPoint(const CATISpecObject_var& value, const CATBoolean& checkExist = CATTrue);

    /**
     * @brief Main Dir
     * @param[in] value CATISpecObject_var
     * @return HRESULT
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    HRESULT SetMainDir(const CATISpecObject_var& value, const CATBoolean& checkExist = CATTrue);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve IMPLEMENTS HEAD SET

private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    PNXECombinedCurve(PNXECombinedCurve&);
    PNXECombinedCurve& operator=(PNXECombinedCurve&);

private:
    KTCAutoAttrAccess ktcSpecRW; // for 	KTCAutoAttrAccess
};

#endif
