/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXCurveDivisionCoreData.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 */
#include "iostream.h"

// local Framework
#include "PNXCurveDivisionCoreData.h"


//-----------------------------------------------------------------------------
PNXCurveDivisionCoreData::PNXCurveDivisionCoreData()
    : _code(0)
    // START KEVIN CAA WIZARD SECTION PNXCurveDivisionCoreDataPublic PARAM
    // CONSTRUCTOR

    // clang-format off
    , feature(NULL_var) // 101
    , parameter(NULL) // 102
    , _catFrmEditor(NULL) // 103

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivisionCoreDataPublic PARAM
    // CONSTRUCTOR

{
}
//-----------------------------------------------------------------------------
PNXCurveDivisionCoreData::~PNXCurveDivisionCoreData() {

    // START KEVIN CAA WIZARD SECTION PNXCurveDivisionCoreDataPublic PARAM
    // DESTRUCTOR

    // clang-format off
    feature = NULL_var; // 101
    parameter = NULL; // 102
    _catFrmEditor = NULL; // 103

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXCurveDivisionCoreDataPublic PARAM
    // DESTRUCTOR

}
