/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisParam.cpp
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
#include "PNXBomAnalysisParam.h"

/**
 * @brief Software version for BomAnalysis
 * @return void
 * @note This is for Kt Auto System.
 */
#define KT_VERSION_SOFTWARE_BomAnalysis 0

#pragma region KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
PNXBomAnalysisParam::PNXBomAnalysisParam()
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM CONSTRUCTOR

    // clang-format off
    : FirstProduct(NULL_var) // 1
    , FirstPartNumber() // 2
    , PartCount(0) // 3

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM CONSTRUCTOR
    , productItems(NULL) {
    productItems = new std::vector<PNXBomItem>();

    // your code here:
}
//-----------------------------------------------------------------------------
PNXBomAnalysisParam::~PNXBomAnalysisParam() {
    delete productItems;
    productItems = NULL;

    // 0A,FeatureVersion

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM DESTRUCTOR

    // clang-format off
    FirstProduct = NULL_var; // 1
    // FirstPartNumber = ""; // 2
    // PartCount = 0; // 3

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM DESTRUCTOR

    // your code here:
}
//-----------------------------------------------------------------------------
PNXBomAnalysisParam::PNXBomAnalysisParam(const PNXBomAnalysisParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
PNXBomAnalysisParam& PNXBomAnalysisParam::operator=(const PNXBomAnalysisParam& iOriginal) {
    // KEVIN_SYSTEM_CODE START
    // KEVIN_SYSTEM_CODE END

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM EQUAL

    // clang-format off
    FirstProduct = iOriginal.FirstProduct; // 1
    FirstPartNumber = iOriginal.FirstPartNumber; // 2
    PartCount = iOriginal.PartCount; // 3

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysis PARAM EQUAL

    // your code here:

    return *this;
}
//-----------------------------------------------------------------------------
int PNXBomAnalysisParam::GetSoftwareVersion() {
    return KT_VERSION_SOFTWARE_BomAnalysis;
}

#pragma endregion KEVIN_SYSTEM_CODE_FUNCTIONS
//-----------------------------------------------------------------------------
HRESULT PNXBomAnalysisParam::CheckoutAxis() {
    CATMathAxis MyAxis = CATMathOIJK; // set abs axis

    // if (NULL_var == CurrentAxis) // abs axis
    //     return S_OK;

    return S_OK;
}
