/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterCoreData.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 */
#include "iostream.h"

// local Framework
#include "PNXV5V6AdapterCoreData.h"


//-----------------------------------------------------------------------------
PNXV5V6AdapterCoreData::PNXV5V6AdapterCoreData()
    : _code(0)
    // START KEVIN CAA WIZARD SECTION PNXV5V6AdapterCoreDataPublic PARAM
    // CONSTRUCTOR

    // clang-format off
    , feature(NULL_var) // 101
    , parameter(NULL) // 102
    , _catFrmEditor(NULL) // 103

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6AdapterCoreDataPublic PARAM
    // CONSTRUCTOR

{
}
//-----------------------------------------------------------------------------
PNXV5V6AdapterCoreData::~PNXV5V6AdapterCoreData() {

    // START KEVIN CAA WIZARD SECTION PNXV5V6AdapterCoreDataPublic PARAM
    // DESTRUCTOR

    // clang-format off
    feature = NULL_var; // 101
    parameter = NULL; // 102
    _catFrmEditor = NULL; // 103

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXV5V6AdapterCoreDataPublic PARAM
    // DESTRUCTOR

}
