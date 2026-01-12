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

#ifndef KTCAutoAttrAccess_H
#define KTCAutoAttrAccess_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoAttrAccess.h"
#include "KTCAutoCodeItf.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoAttrAccess {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoAttrAccess();
    virtual ~KTCAutoAttrAccess();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoAttrAccess(const KTCAutoAttrAccess&);
    KTCAutoAttrAccess& operator=(const KTCAutoAttrAccess&);
};

#endif
