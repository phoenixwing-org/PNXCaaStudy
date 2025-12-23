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
KTCAutoSelectorCtx::KTCAutoSelectorCtx(int field, CATDlgSelectorList* selector)
    : fieldKey(field)
    , DlgSelector(selector)
    , feature(NULL)
    , featureList(NULL)
    , _parentDialog(NULL)
    , fieldName() {
}
//-------------------------------------------------------------------------
KTCAutoSelectorCtx::~KTCAutoSelectorCtx() {
    _parentDialog = NULL;
    feature       = NULL;
    featureList   = NULL;
    DlgSelector   = NULL;
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::RegisterFeature(CATISpecObject_var& feature) {
    this->feature     = &feature;
    this->featureList = NULL; // »¥³â
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::RegisterFeature(CATListValCATISpecObject_var& iList) {
    this->feature     = NULL; // »¥³â
    this->featureList = &iList;
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::set_parent(CATDlgDialog* dlg) {
    _parentDialog = dlg;
}
