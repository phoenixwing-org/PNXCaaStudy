/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureParam.cpp
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
#include "PNXTemplateFeatureParam.h"

/**
 * @brief Software version for TemplateFeature
 * @return void
 * @note This is for Kt Auto System.
 */
#define KT_VERSION_SOFTWARE_TemplateFeature 0

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
PNXTemplateFeatureParam::PNXTemplateFeatureParam()
    : KTCAutoParam()
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM CONSTRUCTOR

    // clang-format off
    , MyCurve(NULL_var) // 2
    , MyFaces() // 3
    , MyStep(5) // 4
    , FinishCalc(0) // 5
    , MyAxis() // 100
    , MyTime() // 101

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM CONSTRUCTOR
{

    // your code here:
}
//-----------------------------------------------------------------------------
PNXTemplateFeatureParam::~PNXTemplateFeatureParam() {

    // 0A,FeatureVersion

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM DESTRUCTOR

    // clang-format off
    MyCurve = NULL_var; // 2
    // MyFaces = ; // 3
    // MyStep = 5; // 4
    // FinishCalc = 0; // 5
    // MyAxis = ; // 100
    // MyTime = ""; // 101

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM DESTRUCTOR

    // your code here:
}
//-----------------------------------------------------------------------------
PNXTemplateFeatureParam::PNXTemplateFeatureParam(const PNXTemplateFeatureParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
PNXTemplateFeatureParam&
    PNXTemplateFeatureParam::operator=(const PNXTemplateFeatureParam& iOriginal) {
    // KEVIN_SYSTEM_CODE START
    KTCAutoParam::operator=(iOriginal);
    // KEVIN_SYSTEM_CODE END

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM EQUAL

    // clang-format off
    MyCurve = iOriginal.MyCurve; // 2
    MyFaces = iOriginal.MyFaces; // 3
    MyStep = iOriginal.MyStep; // 4
    FinishCalc = iOriginal.FinishCalc; // 5
    MyAxis = iOriginal.MyAxis; // 100
    MyTime = iOriginal.MyTime; // 101

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature PARAM EQUAL

    // your code here:

    return *this;
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureParam::GetSoftwareVersion() {
    return KT_VERSION_SOFTWARE_TemplateFeature;
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
HRESULT PNXTemplateFeatureParam::CheckoutAxis() {
    MyAxis = CATMathOIJK; // set abs axis

    return S_OK;
}
