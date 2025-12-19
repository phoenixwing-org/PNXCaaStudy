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

#ifndef KTCAutoHSO_H
#define KTCAutoHSO_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoHSO.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoHSO {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoHSO();
    virtual ~KTCAutoHSO();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoHSO(const KTCAutoHSO&);
    KTCAutoHSO& operator=(const KTCAutoHSO&);
};

#endif
