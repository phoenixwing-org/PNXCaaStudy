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

#ifndef KTCAutoErrors_H
#define KTCAutoErrors_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoErrors.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoErrors {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoErrors();
    virtual ~KTCAutoErrors();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoErrors(const KTCAutoErrors&);
    KTCAutoErrors& operator=(const KTCAutoErrors&);
};

#endif
