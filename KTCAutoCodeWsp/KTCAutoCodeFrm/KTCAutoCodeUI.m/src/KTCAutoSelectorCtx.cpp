/**
 * @copyright   Copyright 2021 Kevin Time Toolkit
 * @license     MIT
 * @author      Phoenix Wing
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

// cat
#include "CATDialogAgent.h"
#include "CATMMUIPanelStateCmd.h"
#include "iostream.h"

// auto code
#include "KTCAutoSelectorCtx.h"

//-------------------------------------------------------------------------
KTCAutoSelectorCtx::KTCAutoSelectorCtx(int iField, CATDlgSelectorList* iSelector)
    : fieldKey(iField)
    , selector(iSelector)
    , feature(NULL)
    , featureList(NULL)
    , dialog(NULL)
    , fieldName() {
}
//-------------------------------------------------------------------------
KTCAutoSelectorCtx::~KTCAutoSelectorCtx() {
    dialog      = NULL;
    feature     = NULL;
    featureList = NULL;
    selector    = NULL;
}
//-------------------------------------------------------------------------
int KTCAutoSelectorCtx::clear_feature() {
    if (feature) {
        // single feature mode
        if (NULL_var != *feature) *feature = NULL_var;
        return 1;
    }
    if (featureList) {
        // list mode
        if (featureList->Size() > 0) {
            int count = featureList->Size();
            featureList->RemoveAll();
            return count;
        }
    }
    return 0;
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::ClearSelect() {
    if (selector) selector->ClearSelect();
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::regitster_feature(CATISpecObject_var& iFeature) {
    this->feature     = &iFeature;
    this->featureList = NULL; // clear
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::regitster_feature(CATListValCATISpecObject_var& iList) {
    this->feature     = NULL; // clear
    this->featureList = &iList;
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::set_dialog(CATDlgDialog* iDialog) {
    dialog = iDialog;
}
//-------------------------------------------------------------------------
int KTCAutoSelectorCtx::SetSelect(int notify) {
    if (!selector) return 0;
    if (selector->GetSelectCount() > 0) return selector->GetSelectCount();

    // no lines
    if (selector->GetLineCount() == 0) {
        CATUnicodeString msg[ 1 ];
        msg[ 0 ] = "(No Selection)";
        selector->SetSelect(msg, 1, notify);
        return 1;
    }

    // have lines
    int row = 0;                          // first line
    selector->SetSelect(&row, 1, notify); // select row
    return 1;
}