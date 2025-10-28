/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXCurveDivisionParam.cpp
 * @version		V1.0
 * @date		2021-9-1
 * @brief
 */

// CAT
#include "CATDocument.h"
#include "CATMathTransformation.h"
#include "CATPoint.h"
#include "iostream.h"


// Local
#include "PNXCurveDivisionParam.h"

/**
 * @brief Software version for CurveDivision
 * @return void
 * @note This is for Kt Auto System.
 */
#define KT_VERSION_SOFTWARE_CurveDivision 0

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
PNXCurveDivisionParam::PNXCurveDivisionParam()
    // START KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM CONSTRUCTOR

    // clang-format off
    : BaseCurve(NULL_var) // 1
    , PointCount(5) // 2

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM CONSTRUCTOR
{

    // your code here:
}
//-----------------------------------------------------------------------------
PNXCurveDivisionParam::~PNXCurveDivisionParam() {

    // 0A,FeatureVersion

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM DESTRUCTOR

    // clang-format off
    BaseCurve = NULL_var; // 1
    // PointCount = 5; // 2

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM DESTRUCTOR

    // your code here:
}
//-----------------------------------------------------------------------------
PNXCurveDivisionParam::PNXCurveDivisionParam(const PNXCurveDivisionParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
PNXCurveDivisionParam& PNXCurveDivisionParam::operator=(const PNXCurveDivisionParam& iOriginal) {
    // KEVIN_SYSTEM_CODE START
    // KEVIN_SYSTEM_CODE END

    // START KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM EQUAL

    // clang-format off
    BaseCurve = iOriginal.BaseCurve; // 1
    PointCount = iOriginal.PointCount; // 2

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivision PARAM EQUAL

    // your code here:

    return *this;
}
//-----------------------------------------------------------------------------
int PNXCurveDivisionParam::GetSoftwareVersion() {
    return KT_VERSION_SOFTWARE_CurveDivision;
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
HRESULT PNXCurveDivisionParam::CheckoutAxis() {
    CATMathAxis MyAxis = CATMathOIJK; // set abs axis

    // if (NULL_var == CurrentAxis) // abs axis
    //     return S_OK;

    return S_OK;
}
