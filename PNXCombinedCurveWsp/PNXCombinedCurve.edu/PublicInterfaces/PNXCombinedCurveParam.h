/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCombinedCurve
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXCombinedCurveParam_H
#define PNXCombinedCurveParam_H

#include "CATISpecObject.h"
#include "CATUnicodeString.h"

#include "PNXCombinedCurve.h"

// KTC
#include "KTCAutoCode.h"
#include "KTCAutoDefine.h"
#include "KTCAutoParam.h"

// Kt
#include "KtString.h"

/** @brief Field Type */
enum PNXCombinedCurveField {
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve DLG DEFINE FIELD TYPE

    // clang-format off
    //.............................................................................
    // @key    DlgDefineFieldType
    //.............................................................................
    Field_PNXCombinedCurve_None = 0, // None
    Field_PNXCombinedCurve_FirstPoint = 1, // FirstPoint
    Field_PNXCombinedCurve_MainDir = 2, // MainDir

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve DLG DEFINE FIELD TYPE
};

/** @brief KTC CombinedCurve Param */
class ExportedByPNXCombinedCurve PNXCombinedCurveParam : public KTCAutoParam {
public:
    /** @brief Standard constructors and destructors */
    PNXCombinedCurveParam();
    virtual ~PNXCombinedCurveParam();

    /** @brief Copy constructor and equal operator */
    PNXCombinedCurveParam(const PNXCombinedCurveParam&);
    PNXCombinedCurveParam& operator=(const PNXCombinedCurveParam&);

public:
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief First Point
     * @author Phoenix
     * @date 2025/12/17
     * @id 2
     */
    CATISpecObject_var FirstPoint;

    /**
     * @brief Main Dir
     * @author Phoenix
     * @date 2025/12/17
     * @id 3
     */
    CATISpecObject_var MainDir;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM DECLARATION

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
};

#endif
