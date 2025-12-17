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

#ifndef KTCParamUnknown_H
#define KTCParamUnknown_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCParamUnknown.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCParamUnknown {
public:
    /** @brief Standard constructors and destructors */
    KTCParamUnknown();
    virtual ~KTCParamUnknown();

    /** @brief Copy constructor and equal operator */
    KTCParamUnknown(const KTCParamUnknown&);
    KTCParamUnknown& operator=(const KTCParamUnknown&);

public:
    int FeatureVersion;
};

#endif
