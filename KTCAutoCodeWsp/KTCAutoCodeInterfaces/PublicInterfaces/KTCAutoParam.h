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

#ifndef KTCAutoParam_H
#define KTCAutoParam_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoParam.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoParam {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoParam();
    virtual ~KTCAutoParam();

    /** @brief Copy constructor and equal operator */
    KTCAutoParam(const KTCAutoParam&);
    KTCAutoParam& operator=(const KTCAutoParam&);

public:
    int FeatureVersion;
};

#endif
