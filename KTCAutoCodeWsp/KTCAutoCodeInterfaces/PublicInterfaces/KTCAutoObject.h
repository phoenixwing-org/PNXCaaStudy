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

#ifndef KTCAutoObject_H
#define KTCAutoObject_H

#include "CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeItf.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeItf KTCAutoObject {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoObject();
    virtual ~KTCAutoObject();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoObject(const KTCAutoObject&);
    KTCAutoObject& operator=(const KTCAutoObject&);

public:
    /**
     * @brief update spec object
     */
    static HRESULT update(CATISpecObject_var object, bool isCout);
};

#endif
