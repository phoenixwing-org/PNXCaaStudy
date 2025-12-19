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

#ifndef KTCAutoBaseOpt_H
#define KTCAutoBaseOpt_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoBaseOpt.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoBaseOpt {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoBaseOpt();
    virtual ~KTCAutoBaseOpt();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoBaseOpt(const KTCAutoBaseOpt&);
    KTCAutoBaseOpt& operator=(const KTCAutoBaseOpt&);
};

#endif
