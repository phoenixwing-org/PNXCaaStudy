/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXBomAnalysisParam_H
#define PNXBomAnalysisParam_H

#include "CATISpecObject.h"
#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATUnicodeString.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"

#include "PNXBomAnalysisItf.h"

struct PNXBomItem {
    // the following in main properties
    CATUnicodeString partNumber;
    CATUnicodeString revision;
    CATUnicodeString definition;
    CATUnicodeString nonenclature;
    CATUnicodeString source;
    CATUnicodeString description;

    // mechanical

    float        volume;
    float        mass;
    float        surface;
    CATMathPoint center;
};

/** @brief Field Type */
enum PNXBomAnalysisField {
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis DLG DEFINE FIELD TYPE

    // clang-format off
    //.............................................................................
    // @key    DlgDefineFieldType
    //.............................................................................
    Field_PNXBomAnalysis_None = 0, // None
    Field_PNXBomAnalysis_FirstProduct = 1, // FirstProduct

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis DLG DEFINE FIELD TYPE
};

/** @brief KTC BomAnalysis Param */
class ExportedByPNXBomAnalysisItf PNXBomAnalysisParam {
public:
    /** @brief Standard constructors and destructors */
    PNXBomAnalysisParam();
    virtual ~PNXBomAnalysisParam();

    /** @brief Copy constructor and equal operator */
    PNXBomAnalysisParam(const PNXBomAnalysisParam&);
    PNXBomAnalysisParam& operator=(const PNXBomAnalysisParam&);

public:
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM DECLARATION

    // clang-format off

    // @app Kt Auto Code
    // @version 5.0.0, (2024)

    /**
     * @brief First Product
     * @author Phoenix
     * @date 2021/10/27
     * @id 1
     */
    CATISpecObject_var FirstProduct;

    /**
     * @brief Top Part Number
     * @author Phoenix
     * @date 2021/10/27
     * @id 2
     */
    CATUnicodeString FirstPartNumber;

    /**
     * @brief Part Count
     * @author Phoenix
     * @date 2025/10/13
     * @id 3
     */
    int PartCount;

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM DECLARATION

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
};

#endif
