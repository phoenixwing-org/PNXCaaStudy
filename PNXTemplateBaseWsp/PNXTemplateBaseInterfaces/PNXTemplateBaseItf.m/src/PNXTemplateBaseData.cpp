/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXTemplateBaseData.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */
// KTC Core Framework
#include "KTCAutoBaseOpt.h"
#include "KTCAutoBody.h"
#include "KTCAutoDefine.h"
#include "KTCAutoGSM.h"
#include "KTCAutoPartDoc.h"
#include "iostream.h"

// local Framework
#include "PNXTemplateBaseData.h"

//-----------------------------------------------------------------------------
PNXTemplateBaseData::PNXTemplateBaseData()
    : code_(0)
    // START KEVIN CAA WIZARD SECTION PNXTemplateBaseDataPublic PARAM CONSTRUCTOR

    // clang-format off
    , featureCurrent_(NULL_var) // 100
    , feature(NULL_var) // 101
    , parameter(NULL) // 102
    , catFrmEditor_(NULL) // 103
    , catISO_(NULL) // 104

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBaseDataPublic PARAM CONSTRUCTOR

    // START KEVIN CAA WIZARD SECTION PNXTemplateBaseDataProtected PARAM CONSTRUCTOR

    // clang-format off
    , _myData(0) // 200

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateBaseDataProtected PARAM CONSTRUCTOR
{
}
//-----------------------------------------------------------------------------
PNXTemplateBaseData::~PNXTemplateBaseData() {

    // START KEVIN CAA WIZARD SECTION PNXTemplateBaseDataPublic PARAM DESTRUCTOR

    // clang-format off
    featureCurrent_ = NULL_var; // 100
    feature = NULL_var; // 101
    parameter = NULL; // 102
    catFrmEditor_ = NULL; // 103
    catISO_ = NULL; // 104

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBaseDataPublic PARAM DESTRUCTOR

    // START KEVIN CAA WIZARD SECTION PNXTemplateBaseDataProtected PARAM DESTRUCTOR

    // clang-format off
    // _myData = 0; // 200

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateBaseDataProtected PARAM DESTRUCTOR
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseData::sample_function() const {
    int code = 0;

    return code;
}
