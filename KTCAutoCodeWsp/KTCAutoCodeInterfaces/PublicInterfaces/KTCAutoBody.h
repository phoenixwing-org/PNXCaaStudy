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

#ifndef KTCAutoBody_H
#define KTCAutoBody_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoBody.h"
#include "KTCAutoCodeItf.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoBody {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoBody();
    virtual ~KTCAutoBody();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoBody(const KTCAutoBody&);
    KTCAutoBody& operator=(const KTCAutoBody&);
};

#endif
