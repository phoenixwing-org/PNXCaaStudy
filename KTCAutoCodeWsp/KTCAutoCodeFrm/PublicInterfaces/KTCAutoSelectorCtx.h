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

// auto code
#include "KTCAutoCodeUI.h"
#include "KtString.h"

#include <map>

/** @brief KTCAutoSelectorCtx Dialog */
class ExportedByKTCAutoCodeUI KTCAutoSelectorCtx {

public:
    KTCAutoSelectorCtx(int field, CATDlgSelectorList* selector);
    virtual ~KTCAutoSelectorCtx();

public:
    void RegisterFeature(CATISpecObject_var& feature);
    void RegisterFeature(CATListValCATISpecObject_var& iList);

    void set_parent(CATDlgDialog* dlg);

public:
    int                           fieldKey;
    KtString                      fieldName;
    CATDlgSelectorList*           DlgSelector;
    CATISpecObject_var*           feature;
    CATListValCATISpecObject_var* featureList;

private:
    CATDlgDialog* _parentDialog;
};

typedef std::map<int, KTCAutoSelectorCtx*> KTCAutoSelectorCtxMap;
#endif
