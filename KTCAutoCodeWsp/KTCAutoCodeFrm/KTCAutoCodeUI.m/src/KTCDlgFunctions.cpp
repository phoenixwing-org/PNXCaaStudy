/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCDlgFunctions.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// Local
#include "KTCDlgFunctions.h"

//-----------------------------------------------------------------------------
KTCDlgFunctions::KTCDlgFunctions() {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCDlgFunctions::~KTCDlgFunctions() {
}
//-----------------------------------------------------------------------------
KTCDlgFunctions::KTCDlgFunctions(const KTCDlgFunctions& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCDlgFunctions& KTCDlgFunctions::operator=(const KTCDlgFunctions& iOriginal) {
    return *this;
}
//-----------------------------------------------------------------------------
int KTCDlgFunctions::CATDlgSelectorListSetLine(CATDlgSelectorList*     selectorList,
                                               CATISpecObject_var      inputObject,
                                               const CATUnicodeString& noneSel) {
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
//-----------------------------------------------------------------------------
int KTCDlgFunctions::CATDlgSelectorListSetLine(CATDlgSelectorList*          selectorList,
                                               CATListValCATISpecObject_var iList,
                                               const CATUnicodeString&      noneSel) {
    if (!selectorList) return 1;                                     // return error code
    if (selectorList->GetLineCount() > 1) selectorList->ClearLine(); // clear multi line

    if (iList.Size() == 0) {
        selectorList->ClearLine(); // clear multi line
        selectorList->SetLine(noneSel, 0, CATDlgDataModify);
        return 0;
    }

    CATISpecObject_var object;
    CATUnicodeString   title;
    for (size_t i = 0; 0 < iList.Size(); i++) {
        int index = i + 1;
        object    = iList[ index ];

        if (!!object)
            title = object->GetDisplayName();
        else
            title = "(NULL Object)";
        selectorList->SetLine(title, i, CATDlgDataModify);
    }

    return iList.Size();
}