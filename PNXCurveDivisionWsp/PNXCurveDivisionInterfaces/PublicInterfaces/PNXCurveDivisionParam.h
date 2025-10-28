/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXCurveDivisionParam_H
#define PNXCurveDivisionParam_H

#include "CATISpecObject.h"
#include "CATListOfDouble.h"
#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATUnicodeString.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"

#include "PNXCurveDivisionItf.h"

/** @brief Field Type */
enum PNXCurveDivisionField {
    // START KEVIN CAA WIZARD SECTION PNXCurveDivision DLG DEFINE FIELD TYPE

    // clang-format off
    //.............................................................................
    // @key    DlgDefineFieldType
    //.............................................................................
    Field_PNXCurveDivision_None = 0, // None
    Field_PNXCurveDivision_BaseCurve = 1, // BaseCurve

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision DLG DEFINE FIELD TYPE
};

/** @brief KTC CurveDivision Param */
class ExportedByPNXCurveDivisionItf PNXCurveDivisionParam {
public:
    /** @brief Standard constructors and destructors */
    PNXCurveDivisionParam();
    virtual ~PNXCurveDivisionParam();

    /** @brief Copy constructor and equal operator */
    PNXCurveDivisionParam(const PNXCurveDivisionParam&);
    PNXCurveDivisionParam& operator=(const PNXCurveDivisionParam&);

public:
    // START KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief Base Curve
     * @author Phoenix
     * @date 2025/10/28
     * @id 1
     */
    CATISpecObject_var BaseCurve;

    /**
     * @brief Point Count
     * @author Phoenix
     * @date 2025/10/28
     * @id 2
     */
    int PointCount;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM DECLARATION

public: // KEVIN_SYSTEM_CODE
    // KEVIN_SYSTEM_CODE START
    /**
     * @brief get the software version
     * @return software version
     * @note KEVIN_SYSTEM_CODE
     */
    static int GetSoftwareVersion();

    // KEVIN_SYSTEM_CODE END

public: // functions
    /**
     * @brief checkout
     * @return HRESULT
     */
    HRESULT CheckoutAxis();

    // dump
    void dump();
};

#endif
