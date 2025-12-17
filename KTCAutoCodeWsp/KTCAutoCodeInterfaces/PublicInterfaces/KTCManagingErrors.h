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

#ifndef KTCManagingErrors_H
#define KTCManagingErrors_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCManagingErrors.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCManagingErrors {
public:
    /** @brief Standard constructors and destructors */
    KTCManagingErrors();
    virtual ~KTCManagingErrors();

private:
    /** @brief Copy constructor and equal operator */
    KTCManagingErrors(const KTCManagingErrors&);
    KTCManagingErrors& operator=(const KTCManagingErrors&);
};

#endif
