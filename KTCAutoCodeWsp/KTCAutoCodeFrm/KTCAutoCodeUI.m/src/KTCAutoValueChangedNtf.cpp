/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoValueChangedNtf.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// Local
#include "KTCAutoValueChangedNtf.h"

CATImplementClass(KTCAutoValueChangedNtf, Implementation, CATNotification, CATNull);

//-----------------------------------------------------------------------------
KTCAutoValueChangedNtf::KTCAutoValueChangedNtf() {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoValueChangedNtf::~KTCAutoValueChangedNtf() {
}
//-----------------------------------------------------------------------------
KTCAutoValueChangedNtf::KTCAutoValueChangedNtf(const KTCAutoValueChangedNtf& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoValueChangedNtf& KTCAutoValueChangedNtf::operator=(const KTCAutoValueChangedNtf& iOriginal) {
    return *this;
}
