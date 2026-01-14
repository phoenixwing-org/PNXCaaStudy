/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureData.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */
// CAT
#include "iostream.h"

// KTC Core Framework
#include "KTCAutoBaseOpt.h"
#include "KTCAutoBody.h"
#include "KTCAutoDefine.h"
#include "KTCAutoGSM.h"
#include "KTCAutoPartDoc.h"

// local Framework
#include "PNXITemplateFeature.h"
#include "PNXITemplateFeatureFactory.h"
#include "PNXTemplateFeatureData.h"

//-----------------------------------------------------------------------------
PNXTemplateFeatureData::PNXTemplateFeatureData()
    : code_(0)
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM CONSTRUCTOR

    // clang-format off
    , featureCurrent_(NULL_var) // 100
    , feature(NULL_var) // 101
    , parameter(NULL) // 102
    , catFrmEditor_(NULL) // 103
    , catISO_(NULL) // 104
    , list3DRep_(NULL) // 105

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM CONSTRUCTOR

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM CONSTRUCTOR

    // clang-format off
    , myData_(0) // 200

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM CONSTRUCTOR
{
    list3DRep_ = new KtListP<CAT3DRep>(); // new
}
//-----------------------------------------------------------------------------
PNXTemplateFeatureData::~PNXTemplateFeatureData() {
    KTDelete(list3DRep_);

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM DESTRUCTOR

    // clang-format off
    featureCurrent_ = NULL_var; // 100
    feature = NULL_var; // 101
    parameter = NULL; // 102
    catFrmEditor_ = NULL; // 103
    catISO_ = NULL; // 104
    list3DRep_ = NULL; // 105

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM DESTRUCTOR

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM DESTRUCTOR

    // clang-format off
    // myData_ = 0; // 200

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM DESTRUCTOR
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureData::sample_function() const {
    int code = 0;

    return code;
}
