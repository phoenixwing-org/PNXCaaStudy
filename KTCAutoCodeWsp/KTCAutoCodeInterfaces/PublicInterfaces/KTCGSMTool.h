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

#ifndef KTCGSMTool_H
#define KTCGSMTool_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCGSMTool.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCGSMTool {
public:
    /** @brief Standard constructors and destructors */
    KTCGSMTool();
    virtual ~KTCGSMTool();

private:
    /** @brief Copy constructor and equal operator */
    KTCGSMTool(const KTCGSMTool&);
    KTCGSMTool& operator=(const KTCGSMTool&);
};

#endif
