/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXV5V6AdapterParam_H
#define PNXV5V6AdapterParam_H

#include "CATISpecObject.h"
#include "CATListOfDouble.h"
#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATUnicodeString.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"

#include "PNXV5V6AdapterItf.h"

/** @brief Field Type */
enum PNXV5V6AdapterField {
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter DLG DEFINE FIELD TYPE

    // clang-format off
    //.............................................................................
    // @key    DlgDefineFieldType
    //.............................................................................
    Field_PNXV5V6Adapter_None = 0, // None
    Field_PNXV5V6Adapter_BaseCurve = 1, // BaseCurve

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter DLG DEFINE FIELD TYPE
};

/** @brief KTC V5V6Adapter Param */
class ExportedByPNXV5V6AdapterItf PNXV5V6AdapterParam {
public:
    /** @brief Standard constructors and destructors */
    PNXV5V6AdapterParam();
    virtual ~PNXV5V6AdapterParam();

    /** @brief Copy constructor and equal operator */
    PNXV5V6AdapterParam(const PNXV5V6AdapterParam&);
    PNXV5V6AdapterParam& operator=(const PNXV5V6AdapterParam&);

public:
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM DECLARATION

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
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM DECLARATION

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
