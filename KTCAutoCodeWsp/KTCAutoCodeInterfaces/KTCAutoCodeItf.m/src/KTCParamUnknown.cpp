/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCParamUnknown.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// Local
#include "KTCParamUnknown.h"

//-----------------------------------------------------------------------------
KTCParamUnknown::KTCParamUnknown()
    : FeatureVersion(0) {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCParamUnknown::~KTCParamUnknown() {
}
//-----------------------------------------------------------------------------
KTCParamUnknown::KTCParamUnknown(const KTCParamUnknown& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCParamUnknown& KTCParamUnknown::operator=(const KTCParamUnknown& iOriginal) {
    FeatureVersion = iOriginal.FeatureVersion;
    return *this;
}
