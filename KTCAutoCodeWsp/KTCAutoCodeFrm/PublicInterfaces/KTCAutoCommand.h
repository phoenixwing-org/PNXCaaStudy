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

#ifndef KTCAutoCommand_H
#define KTCAutoCommand_H

#include "CATDlgSelectorList.h"
#include "CATISpecObject.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeUI.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeUI KTCAutoCommand {
public:
    /** @brief Standard constructors and destructors */
    KTCAutoCommand();
    virtual ~KTCAutoCommand();

private:
    /** @brief Copy constructor and equal operator */
    KTCAutoCommand(const KTCAutoCommand&);
    KTCAutoCommand& operator=(const KTCAutoCommand&);

public:
};

#endif
