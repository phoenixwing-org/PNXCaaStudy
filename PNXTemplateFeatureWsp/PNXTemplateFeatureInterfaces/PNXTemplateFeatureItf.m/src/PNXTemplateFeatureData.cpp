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
// KTC Core Framework
#include "KTCAutoBaseOpt.h"
#include "KTCAutoBody.h"
#include "KTCAutoDefine.h"
#include "KTCAutoGSM.h"
#include "KTCAutoPartDoc.h"
#include "iostream.h"

// local Framework
#include "PNXITemplateFeature.h"
#include "PNXITemplateFeatureFactory.h"
#include "PNXTemplateFeatureData.h"

// Kt
#include "KtDump.h"
#include "ListKtMathBox.h"
#include "MatrixKtByteKit.h"

//-----------------------------------------------------------------------------
PNXTemplateFeatureData::PNXTemplateFeatureData()
    : _code(KT_S_OK)
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM CONSTRUCTOR

    // clang-format off
    , _featureCurrent(NULL_var) // 100
    , feature(NULL_var) // 101
    , parameter(NULL) // 102
    , _catFrmEditor(NULL) // 103
    , _catISO(NULL) // 104

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM CONSTRUCTOR

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM CONSTRUCTOR

    // clang-format off
    , _myData(0) // 200

// clang-format on
// END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM CONSTRUCTOR
{
    _list3DRep = new KtListP<CAT3DRep>(); // new
}
//-----------------------------------------------------------------------------
PNXTemplateFeatureData::~PNXTemplateFeatureData() {
    KTDelete(_list3DRep);

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM DESTRUCTOR

    // clang-format off
    _featureCurrent = NULL_var; // 100
    feature = NULL_var; // 101
    parameter = NULL; // 102
    _catFrmEditor = NULL; // 103
    _catISO = NULL; // 104

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataPublic PARAM DESTRUCTOR

    // START KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM DESTRUCTOR

    // clang-format off
    // _myData = 0; // 200

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeatureDataProtected PARAM DESTRUCTOR
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureData::sample_function() const {
    int code = 0;

    return code;
}
