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

#ifndef KTCSpecAttrAccess_H
#define KTCSpecAttrAccess_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCSpecAttrAccess.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCSpecAttrAccess {
public:
    /** @brief Standard constructors and destructors */
    KTCSpecAttrAccess();
    virtual ~KTCSpecAttrAccess();

private:
    /** @brief Copy constructor and equal operator */
    KTCSpecAttrAccess(const KTCSpecAttrAccess&);
    KTCSpecAttrAccess& operator=(const KTCSpecAttrAccess&);
};

#endif
