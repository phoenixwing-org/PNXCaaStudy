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
    : FeatureVersion(0)
    , code(0)
    , message()
    , previewCode()
    , feature() {
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
    code           = iOriginal.code;
    message        = iOriginal.message;
    previewCode    = iOriginal.previewCode;
    feature        = iOriginal.feature;
    return *this;
}
//-----------------------------------------------------------------------------
void KTCAutoParam::append_message(const KtString& iMessage) {
    if (message.size()) message << "\n"; // 原来有信息，就换行
    message << "[INFO] " << iMessage;    // 添加 INFO的信息
}
//-----------------------------------------------------------------------------
void KTCAutoParam::append_message(int iCode, const KtString& iMessage) {
    code = iCode; // set code

    if (message.size()) message << "\n"; // 原来有信息，就换行

    // 根据错误类型处理
    if (iCode == 0) // 没有错误
        message << "[OK] " << iMessage;

    else // 有错误，前缀ERROR
        message << "[ERROR " << code << "] " << iMessage;
}
//-----------------------------------------------------------------------------
KtString KTCAutoParam::build_message(int iCode, const KtString& iMessage) {
    KtString output;

    // 根据错误类型处理
    if (iCode == 0) // 没有错误
        output << "[OK] " << iMessage;
    else // 有错误，前缀ERROR
        output << "[ERROR " << iCode << "] " << iMessage;
    return output;
}
//-----------------------------------------------------------------------------
void KTCAutoParam::clear_error() {
    code = 0;        // set 0
    message.clear(); // clear
}
//-----------------------------------------------------------------------------
void KTCAutoParam::set_message(int iCode, const KtString& iMessage) {
    code = iCode; // set code

    // 没有错误
    if (iCode == 0)
        (message = "[OK] ") << iMessage;
    else // 有错误
        (message = "[ERROR ") << code << "] " << iMessage;
}
