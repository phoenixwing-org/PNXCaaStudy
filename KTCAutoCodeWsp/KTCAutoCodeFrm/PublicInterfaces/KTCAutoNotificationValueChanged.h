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

#ifndef KTCAutoNotificationValueChanged_H
#define KTCAutoNotificationValueChanged_H

#include "CATDlgSelectorList.h"
#include "CATISpecObject.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeUI.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeUI KTCAutoNotificationValueChanged {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoNotificationValueChanged();
    virtual ~KTCAutoNotificationValueChanged();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoNotificationValueChanged(const KTCAutoNotificationValueChanged&);
    KTCAutoNotificationValueChanged& operator=(const KTCAutoNotificationValueChanged&);

public:
    static const char* ClassName();
};

#endif
