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

#ifndef KTCDlgFunctions_H
#define KTCDlgFunctions_H

#include "CATDlgSelectorList.h"
#include "CATISpecObject.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

// KTC
#include "KTCAutoCodeUI.h"

/** @brief KTC AutoCode Param */
class ExportedByKTCAutoCodeUI KTCDlgFunctions {
public:
    /** @brief Standard constructors and destructors */
    KTCDlgFunctions();
    virtual ~KTCDlgFunctions();

private:
    /** @brief Copy constructor and equal operator */
    KTCDlgFunctions(const KTCDlgFunctions&);
    KTCDlgFunctions& operator=(const KTCDlgFunctions&);

public:
    /** @brief nodoc */
    static int CATDlgSelectorListSetLine(CATDlgSelectorList*     selectorList,
                                         CATISpecObject_var      inputObject,
                                         const CATUnicodeString& noneSel = "(No Selection)");

    /** @brief nodoc */
    static int CATDlgSelectorListSetLine(CATDlgSelectorList*          selectorList,
                                         CATListValCATISpecObject_var iList,
                                         const CATUnicodeString&      noneSel = "(No Selection)");
};

#endif
