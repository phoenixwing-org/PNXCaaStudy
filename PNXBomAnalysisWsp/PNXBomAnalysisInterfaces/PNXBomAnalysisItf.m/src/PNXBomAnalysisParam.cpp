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
CATUnicodeString PNXBomAnalysisParam::convertJson(const PNXBomItem& item) {
    CATUnicodeString strJson;

    // clang-format off
    strJson.Append("{");
    strJson.Append("\"PartNumber\":\"");       strJson.Append(item.PartNumber);       strJson.Append("\",");
    strJson.Append("\"Revision\":\"");         strJson.Append(item.Revision);         strJson.Append("\",");
    strJson.Append("\"Source\":\"");           strJson.Append(item.Source);           strJson.Append("\",");
    strJson.Append("\"Definition\":\"");       strJson.Append(item.Definition);       strJson.Append("\",");
    strJson.Append("\"Nomenclature\":\"");     strJson.Append(item.Nomenclature);     strJson.Append("\",");
    strJson.Append("\"DscriptionRef\":\"");    strJson.Append(item.DscriptionRef);    strJson.Append("\",");
    strJson.Append("\"InstanceName\":\"");     strJson.Append(item.InstanceName);     strJson.Append("\",");
    strJson.Append("\"DescriptionInst\":\"");  strJson.Append(item.DescriptionInst);  strJson.Append("\",");
    strJson.Append("\"ActivateBOM\":\"");      strJson.Append(item.ActivateBOM);      strJson.Append("\",");
    strJson.Append("\"ProductAlias\":\"");     strJson.Append(item.ProductAlias);     strJson.Append("\",");
    strJson.Append("\"ParentPartNumber\":\""); strJson.Append(item.ParentPartNumber); strJson.Append("\"");
    strJson.Append("}");
    // clang-format on

    return strJson;
}
//-----------------------------------------------------------------------------
CATUnicodeString PNXBomAnalysisParam::ConvertErrorListToString() const {
    CATUnicodeString result;

    int size = errorMessage.Size();
    for (int i = 1; i <= size; i++) {
        result.Append(errorMessage[ i ]);
        if (i < size) {
            result.Append("\n");
        }
    }

    return result;
}