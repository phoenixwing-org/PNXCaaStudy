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

#ifndef KTCPartDocument_H
#define KTCPartDocument_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"
#include "KTCPartDocument.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCPartDocument {
public:
    /** @brief Standard constructors and destructors */
    KTCPartDocument();
    virtual ~KTCPartDocument();

private:
    /** @brief Copy constructor and equal operator */
    KTCPartDocument(const KTCPartDocument&);
    KTCPartDocument& operator=(const KTCPartDocument&);
};

#endif
