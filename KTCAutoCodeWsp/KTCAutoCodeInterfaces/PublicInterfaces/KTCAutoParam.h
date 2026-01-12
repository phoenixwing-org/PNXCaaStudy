/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXAutoCode
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef KTCAutoParam_H
#define KTCAutoParam_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// auto code
#include "KTCAutoCodeItf.h"
#include "KTCAutoParam.h"
#include "KtString.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoParam {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoParam();
    virtual ~KTCAutoParam();

    /** @brief Copy constructor and equal operator */
    KTCAutoParam(const KTCAutoParam&);
    KTCAutoParam& operator=(const KTCAutoParam&);

public:
    /**
     * @brief append  message
     * @param message message
     * @note set code and set message with format "\n[INFO] {{message}}"
     */
    void append_message(const KtString& message);

    /**
     * @brief append the error code and message
     * @param code error code
     * @param message message
     * @note set code and set message with format "\n[ERROR {{code}}] {{message}}"
     */
    void append_message(int code, const KtString& message);

    /**
     * @brief build messag like [ERROR {{code}}] {{message}}
     * @param[in] code Error Code
     * @param[in] msg Kt String, Local charset
     */
    static KtString build_message(int code, const KtString& msg);

    /**
     * @brief clear the error code and message
     * @note set code 0 and set message empty
     */
    void clear_error();

    /**
     * @brief set the error code and message
     * @param code error code
     * @param message message
     * @note set code and set message with format "[ERROR {{code}}] {{message}}"
     */
    void set_message(int code, const KtString& message);

public:
    /**
     * @brief Feature Version
     * @author Phoenix
     * @date 2026/01/12
     * @id -1
     */
    int FeatureVersion;

    /**
     * @brief Error code
     * @author Phoenix
     * @date 2026/01/12
     * @id -2
     */
    int code;

    /**
     * @brief message
     * @author Phoenix
     * @date 2026/01/12
     * @id -3
     */
    KtString message;

    /**
     * @brief Preview Code
     * @author Phoenix
     * @date 2026/01/12
     * @id -4
     */
    int PreviewCode;
};

#endif
