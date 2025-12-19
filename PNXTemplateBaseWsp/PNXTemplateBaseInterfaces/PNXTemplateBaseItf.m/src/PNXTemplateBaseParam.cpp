/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXTemplateBaseParam.cpp
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
#include "PNXTemplateBaseParam.h"

/**
 * @brief Software version for TemplateBase
 * @return void
 * @note This is for Kt Auto System.
 */
#define KT_VERSION_SOFTWARE_TemplateBase 0

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
PNXTemplateBaseParam::PNXTemplateBaseParam()
    : KTCAutoParam()
    // START KEVIN CAA WIZARD SECTION PNXTemplateBase PARAM CONSTRUCTOR

    // clang-format off
    , MyCurve(NULL_var) // 2
    , MyFaces() // 3
    , MyStep(5) // 4
    , FinishCalc(0) // 5
    , MyAxis() // 100
    , MyTime() // 101

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateBase PARAM CONSTRUCTOR
{

    // your code here:
}
//-----------------------------------------------------------------------------
PNXTemplateBaseParam::~PNXTemplateBaseParam() {

    // 0A,FeatureVersion

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase PARAM DESTRUCTOR

    // clang-format off
    MyCurve = NULL_var; // 2
    // MyFaces = ; // 3
    // MyStep = 5; // 4
    // FinishCalc = 0; // 5
    // MyAxis = ; // 100
    // MyTime = ""; // 101

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase PARAM DESTRUCTOR

    // your code here:
}
//-----------------------------------------------------------------------------
PNXTemplateBaseParam::PNXTemplateBaseParam(const PNXTemplateBaseParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
PNXTemplateBaseParam& PNXTemplateBaseParam::operator=(const PNXTemplateBaseParam& iOriginal) {
    // KEVIN_SYSTEM_CODE START
    KTCAutoParam::operator=(iOriginal);
    // KEVIN_SYSTEM_CODE END

    // START KEVIN CAA WIZARD SECTION PNXTemplateBase PARAM EQUAL

    // clang-format off
    MyCurve = iOriginal.MyCurve; // 2
    MyFaces = iOriginal.MyFaces; // 3
    MyStep = iOriginal.MyStep; // 4
    FinishCalc = iOriginal.FinishCalc; // 5
    MyAxis = iOriginal.MyAxis; // 100
    MyTime = iOriginal.MyTime; // 101

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBase PARAM EQUAL

    // your code here:

    return *this;
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseParam::GetSoftwareVersion() {
    return KT_VERSION_SOFTWARE_TemplateBase;
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
HRESULT PNXTemplateBaseParam::CheckoutAxis() {
    MyAxis = CATMathOIJK; // set abs axis

    return S_OK;
}
