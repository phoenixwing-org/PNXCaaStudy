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

#ifndef KTCBaseOperate_H
#define KTCBaseOperate_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCBaseOperate.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCBaseOperate {
public:
    /** @brief Standard constructors and destructors */
    KTCBaseOperate();
    virtual ~KTCBaseOperate();

private:
    /** @brief Copy constructor and equal operator */
    KTCBaseOperate(const KTCBaseOperate&);
    KTCBaseOperate& operator=(const KTCBaseOperate&);
};

#endif
