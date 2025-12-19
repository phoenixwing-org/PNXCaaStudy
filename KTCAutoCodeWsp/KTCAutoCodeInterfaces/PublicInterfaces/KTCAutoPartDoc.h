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

#ifndef KTCAutoPartDoc_H
#define KTCAutoPartDoc_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCAutoPartDoc.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoPartDoc {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoPartDoc();
    virtual ~KTCAutoPartDoc();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoPartDoc(const KTCAutoPartDoc&);
    KTCAutoPartDoc& operator=(const KTCAutoPartDoc&);
};

#endif
