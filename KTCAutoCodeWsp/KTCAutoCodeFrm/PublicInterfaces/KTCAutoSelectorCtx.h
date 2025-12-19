/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @file
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef KTCAutoSelectorCtx_H
#define KTCAutoSelectorCtx_H

// Dialog Framework
#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "CATISpecObject.h"

// local
#include "KTCAutoCodeUI.h"

/** @brief KTCAutoSelectorCtx Dialog */
class ExportedByKTCAutoCodeUI KTCAutoSelectorCtx {

public:
    KTCAutoSelectorCtx(CATDlgDialog* dlg);
    virtual ~KTCAutoSelectorCtx();

public:
    void RegisterFeature(CATISpecObject_var feature);

    void set_parent(CATDlgDialog* dlg);

private:
    CATDlgDialog*      parentDialog;
    CATISpecObject_var feature;
};

#endif
