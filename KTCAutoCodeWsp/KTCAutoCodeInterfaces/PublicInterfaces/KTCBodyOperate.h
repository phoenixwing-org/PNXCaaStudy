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

#ifndef KTCBodyOperate_H
#define KTCBodyOperate_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCBodyOperate.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCBodyOperate {
public:
    /** @brief Standard constructors and destructors */
    KTCBodyOperate();
    virtual ~KTCBodyOperate();

private:
    /** @brief Copy constructor and equal operator */
    KTCBodyOperate(const KTCBodyOperate&);
    KTCBodyOperate& operator=(const KTCBodyOperate&);
};

#endif
