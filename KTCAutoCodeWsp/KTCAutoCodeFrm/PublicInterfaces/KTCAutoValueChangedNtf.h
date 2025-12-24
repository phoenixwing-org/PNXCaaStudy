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

#ifndef KTCAutoValueChangedNtf_H
#define KTCAutoValueChangedNtf_H

// CAT
#include "CATDlgSelectorList.h"
#include "CATISpecObject.h"
#include "CATNotification.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeUI.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeUI KTCAutoValueChangedNtf : public CATNotification {
public:
    CATDeclareClass;

    /** @brief Standard constructors and destructors */
    KTCAutoValueChangedNtf();
    virtual ~KTCAutoValueChangedNtf();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoValueChangedNtf(const KTCAutoValueChangedNtf&);
    KTCAutoValueChangedNtf& operator=(const KTCAutoValueChangedNtf&);
};

#endif
