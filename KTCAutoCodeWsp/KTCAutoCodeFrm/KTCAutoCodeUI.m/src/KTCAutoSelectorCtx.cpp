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

// Local Framework
#include "KTCAutoSelectorCtx.h"

//-------------------------------------------------------------------------
KTCAutoSelectorCtx::KTCAutoSelectorCtx(CATDlgDialog* dlg)
    : parentDialog(NULL)
    , feature(NULL_var) {
}
//-------------------------------------------------------------------------
KTCAutoSelectorCtx::~KTCAutoSelectorCtx() {
    parentDialog = NULL;
    feature      = NULL_var;
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::RegisterFeature(CATISpecObject_var feature) {
    this->feature = feature;
}
//-------------------------------------------------------------------------
void KTCAutoSelectorCtx::set_parent(CATDlgDialog* dlg) {
    parentDialog = dlg;
}
