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

#ifndef KTCHSOKit_H
#define KTCHSOKit_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCHSOKit.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCHSOKit {
public:
    /** @brief Standard constructors and destructors */
    KTCHSOKit();
    virtual ~KTCHSOKit();

private:
    /** @brief Copy constructor and equal operator */
    KTCHSOKit(const KTCHSOKit&);
    KTCHSOKit& operator=(const KTCHSOKit&);
};

#endif
