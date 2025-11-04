

/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        KTCAutoPanelCommand.h
 * @note        Kt CAA Auto Code
 */
#ifndef _KTCAutoPanelCommand_H_
#define _KTCAutoPanelCommand_H_

#include "CATDlgSelectorList.h"
#include "CATISpecObject.h"
#include "CATUnicodeString.h"

// Kt CAA Auto Code
namespace KTC {
inline int CATDlgSelectorListSetLine(CATDlgSelectorList* selectorList,
                                     CATISpecObject_var  inputObject,
                                     CATUnicodeString    noneSel = "(No Selection)") {
    if (!selectorList) return 1;                                     // return error code
    if (selectorList->GetLineCount() > 1) selectorList->ClearLine(); // clear multi line

    // set diaplay name or no selection
    if (inputObject != NULL_var) {
        selectorList->SetLine(inputObject->GetDisplayName(), 0, CATDlgDataModify);
    }
    else
        selectorList->SetLine(noneSel, 0, CATDlgDataModify);

    return 0; // ok
}
} // namespace KTC

#endif //_KTCAutoPanelCommand_H_
