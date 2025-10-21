/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXBomAnalysis.git
 * @file  		PNXBomAnalysisCoreData.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 */
#include "iostream.h"

// local Framework
#include "PNXBomAnalysisCoreData.h"


//-----------------------------------------------------------------------------
PNXBomAnalysisCoreData::PNXBomAnalysisCoreData()
    : _code(0)
    // START KEVIN CAA WIZARD SECTION PNXBomAnalysisCoreDataPublic PARAM
    // CONSTRUCTOR

    // clang-format off
    , feature(NULL_var) // 101
    , parameter(NULL) // 102
    , _catFrmEditor(NULL) // 103

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysisCoreDataPublic PARAM
    // CONSTRUCTOR

{
}
//-----------------------------------------------------------------------------
PNXBomAnalysisCoreData::~PNXBomAnalysisCoreData() {

    // START KEVIN CAA WIZARD SECTION PNXBomAnalysisCoreDataPublic PARAM
    // DESTRUCTOR

    // clang-format off
    feature = NULL_var; // 101
    parameter = NULL; // 102
    _catFrmEditor = NULL; // 103

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXBomAnalysisCoreDataPublic PARAM
    // DESTRUCTOR

}
