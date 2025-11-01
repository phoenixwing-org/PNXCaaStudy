/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterParam.cpp
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
#include "PNXV5V6AdapterParam.h"

/**
 * @brief Software version for V5V6Adapter
 * @return void
 * @note This is for Kt Auto System.
 */
#define KT_VERSION_SOFTWARE_V5V6Adapter 0

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
PNXV5V6AdapterParam::PNXV5V6AdapterParam()
    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM CONSTRUCTOR

    // clang-format off
    : BaseCurve(NULL_var) // 1
    , PointCount(5) // 2

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM CONSTRUCTOR
{

    // your code here:
}
//-----------------------------------------------------------------------------
PNXV5V6AdapterParam::~PNXV5V6AdapterParam() {

    // 0A,FeatureVersion

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM DESTRUCTOR

    // clang-format off
    BaseCurve = NULL_var; // 1
    // PointCount = 5; // 2

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM DESTRUCTOR

    // your code here:
}
//-----------------------------------------------------------------------------
PNXV5V6AdapterParam::PNXV5V6AdapterParam(const PNXV5V6AdapterParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
PNXV5V6AdapterParam& PNXV5V6AdapterParam::operator=(const PNXV5V6AdapterParam& iOriginal) {
    // KEVIN_SYSTEM_CODE START
    // KEVIN_SYSTEM_CODE END

    // START KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM EQUAL

    // clang-format off
    BaseCurve = iOriginal.BaseCurve; // 1
    PointCount = iOriginal.PointCount; // 2

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6Adapter PARAM EQUAL

    // your code here:

    return *this;
}
//-----------------------------------------------------------------------------
int PNXV5V6AdapterParam::GetSoftwareVersion() {
    return KT_VERSION_SOFTWARE_V5V6Adapter;
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
HRESULT PNXV5V6AdapterParam::CheckoutAxis() {
    CATMathAxis MyAxis = CATMathOIJK; // set abs axis

    // if (NULL_var == CurrentAxis) // abs axis
    //     return S_OK;

    return S_OK;
}
//-----------------------------------------------------------------------------
void PNXV5V6AdapterParam::dump() {
    cout << "PointCount :" << PointCount << endl;
    if (!!BaseCurve) cout << "PointCount :" << BaseCurve->GetDisplayName() << endl;
}
