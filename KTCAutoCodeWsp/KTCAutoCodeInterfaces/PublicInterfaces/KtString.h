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

#ifndef KtString_H
#define KtString_H

#include "CATISpecObject.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KtString.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KtString {
public:
    /** @brief Standard constructors and destructors */
    KtString();
    virtual ~KtString();

    /** @brief Copy constructor and equal operator */
    KtString(const KtString&);
    KtString& operator=(const KtString&);
};

#endif
