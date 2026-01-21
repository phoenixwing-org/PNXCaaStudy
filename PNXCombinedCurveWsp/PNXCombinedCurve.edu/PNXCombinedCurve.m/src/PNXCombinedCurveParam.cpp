/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCombinedCurve
 * @file  		PNXCombinedCurveParam.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// CAT
#include "CATDocument.h"
#include "CATMathTransformation.h"
#include "CATPoint.h"
#include "iostream.h"

// KTC Core
#include "KTCAutoBaseOpt.h"
#include "KTCAutoPartDoc.h"

// Local
#include "PNXCombinedCurveParam.h"

/**
 * @brief Software version for CombinedCurve
 * @return void
 * @note This is for Kt Auto System.
 */
#define KT_VERSION_SOFTWARE_CombinedCurve 0

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
PNXCombinedCurveParam::PNXCombinedCurveParam()
    : KTCAutoParam()
    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM CONSTRUCTOR

    // clang-format off
    , FirstPoint(NULL_var) // 2
    , MainDir() // 3

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM CONSTRUCTOR
{

    // your code here:
}
//-----------------------------------------------------------------------------
PNXCombinedCurveParam::~PNXCombinedCurveParam() {

    // 0A,FeatureVersion

    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM DESTRUCTOR

    // clang-format off
    FirstPoint = NULL_var; // 2
    MainDir = NULL_var; // 3

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM DESTRUCTOR

    // your code here:
}
//-----------------------------------------------------------------------------
PNXCombinedCurveParam::PNXCombinedCurveParam(const PNXCombinedCurveParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
PNXCombinedCurveParam& PNXCombinedCurveParam::operator=(const PNXCombinedCurveParam& iOriginal) {
    // KEVIN_SYSTEM_CODE START
    KTCAutoParam::operator=(iOriginal);
    // KEVIN_SYSTEM_CODE END

    // START KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM EQUAL

    // clang-format off
    FirstPoint = iOriginal.FirstPoint; // 2
    MainDir = iOriginal.MainDir; // 3

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCombinedCurve PARAM EQUAL

    // your code here:

    return *this;
}
//-----------------------------------------------------------------------------
int PNXCombinedCurveParam::GetSoftwareVersion() {
    return KT_VERSION_SOFTWARE_CombinedCurve;
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS
