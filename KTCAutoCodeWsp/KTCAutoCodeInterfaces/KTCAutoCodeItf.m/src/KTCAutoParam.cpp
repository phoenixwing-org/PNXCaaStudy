/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoParam.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// Local
#include "KTCAutoParam.h"

//-----------------------------------------------------------------------------
KTCAutoParam::KTCAutoParam()
    : FeatureVersion(0) {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoParam::~KTCAutoParam() {
}
//-----------------------------------------------------------------------------
KTCAutoParam::KTCAutoParam(const KTCAutoParam& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoParam& KTCAutoParam::operator=(const KTCAutoParam& iOriginal) {
    FeatureVersion = iOriginal.FeatureVersion;
    return *this;
}
