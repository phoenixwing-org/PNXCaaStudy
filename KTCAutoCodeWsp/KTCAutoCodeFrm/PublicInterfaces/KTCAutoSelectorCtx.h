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
#include "CATLISTV_CATISpecObject.h"

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
    /**
     * @brief Clear Feature
     * @return cleared count
     */
    int clear_feature();

    /**
     * @brief Clear Select
     * @note call selector->ClearSelect
     * same name as selector->ClearSelect
     */
    void ClearSelect();

    /**
     * @brief Register Feature
     * @param feature CATISpecObject_var reference
     * @note set feature
     */
    void regitster_feature(CATISpecObject_var& feature);

    /**
     * @brief Register Feature
     * @param iList CATListValCATISpecObject_var reference
     * @note set featureList
     */
    void regitster_feature(CATListValCATISpecObject_var& iList);

    /**
     * @brief Set Dialog
     * @param dlg CATDlgDialog pointer
     * @note set dialog
     */
    void set_dialog(CATDlgDialog* dlg);

    /**
     * @brief Set Select
     * @param notify notify type, 0 for no notify, 1 for notify
     * @return the number of selected lines.
     * @note set select, call selector->SetSelect
     * same name as selector->SetSelect
     */
    int SetSelect(int notify = 0);

public:
    int                           fieldKey;
    KtString                      fieldName;
    CATDlgSelectorList*           selector;
    CATISpecObject_var*           feature;
    CATListValCATISpecObject_var* featureList;
    CATDlgDialog*                 dialog;
};

typedef std::map<int, KTCAutoSelectorCtx*> KTCAutoSelectorCtxMap;
#endif
