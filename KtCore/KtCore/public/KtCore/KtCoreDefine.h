/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        KtCoreDefine.h
 * @date		2025-12-18
 * @brief       Core defines
 */
#ifndef KtCoreDefine_H_
#define KtCoreDefine_H_

#define KtUint_MAX (unsigned int)(-1) // UINT32_MAX
#define KtINT32_MAX 2147483647i32     // INT32_MAX

/**
 * @brief CAA pointer Release
 * @param[in] pCAA CAA feature pointer
 */
#define KTDelete(pointer) \
    delete pointer;       \
    pointer = NULL

namespace Kt {
inline int round(double value) {
    return int(value + 0.5);
}
}; // namespace Kt

// JSON Define
#define KT_STRING_JSON_APPEND_VALUE(NAME) "\"" #NAME "\":" << NAME
#define KT_STRING_JSON_APPEND_FLOAT(NAME) "\"" #NAME "\":" << (float)NAME
#define KT_STRING_JSON_APPEND_STRING(NAME) "\"" #NAME "\":\"" << NAME << "\""

#endif // KtCoreDefine_H_
