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
#include "CATApplicationFrame.h"
#include "CATDialogAgent.h"
#include "CATDlgNotify.h"
#include "CATDlgWindow.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATListOfCATUnicodeString.h"
#include "CATMMUIPanelStateCmd.h"
#include "iostream.h"

// Auto Code
#include "KTCAutoDialog.h"
#include "KTCAutoSelectorCtx.h"

//-------------------------------------------------------------------------
KTCAutoDialog::KTCAutoDialog(CATDialog* iParent, CATMMUIPanelStateCmd* iFatherCmd,
                             const CATString& iObjectName, CATDlgStyle iStyle)
    // CATDialog *iParent, CATCommand *iEventMgr, const CATString& iObjectName, CATDlgStyle
    // iStyle=NULL
    : CATDlgDialog(iParent, iFatherCmd, iObjectName, iStyle)
    , _optionDialog(NULL)
    , _activeField(0)
    , _catHSO(NULL)
    , _actionMode(KTC::ValueNormal)
    , _selectorMap(NULL)
    , _valueChangeNtf(NULL) {
    _selectorMap    = new std::map<int, KTCAutoSelectorCtx*>();
    _valueChangeNtf = new KTCAutoValueChangedNtf();
}
//-------------------------------------------------------------------------
KTCAutoDialog::~KTCAutoDialog() {
    _optionDialog = NULL;
    _catHSO       = NULL;
    // _activeField = 0;

    if (_selectorMap) {
        KTCAutoSelectorCtx* ctx;
        for (size_t i = 0; i < _selectorMap->size(); i++) {
            ctx = (*_selectorMap)[ i ]; // get
            delete ctx;                 // delete
        }
        delete _selectorMap, _selectorMap = NULL;
    }

    // TODO: delete _valueChangeNtf?
}
//-------------------------------------------------------------------------
int KTCAutoDialog::InitialMenuRightClick() {
    // TODO initial
    return 0;
}
//-------------------------------------------------------------------------
void KTCAutoDialog::on_show_option_dialog(CATCommand*, CATNotification*, CATCommandClientData) {
    if (!_optionDialog) return;

    // change state
    CATULong state = (_optionDialog->GetVisibility() == CATDlgShow) ? CATDlgHide : CATDlgShow;
    _optionDialog->SetVisibility(state);
}
//-------------------------------------------------------------------------
KTCAutoSelectorCtx* KTCAutoDialog::regitster_field(int field, CATDlgSelectorList* selector,
                                                   const KtString& name) {
    if (!selector) return NULL;
    if (!_selectorMap) _selectorMap = new KTCAutoSelectorCtxMap(); // 第一次注册时，创建map

    // C++98 需要显式指定迭代器类型
    KTCAutoSelectorCtxMap::iterator it = _selectorMap->find(field);
    if (it != _selectorMap->end()) {
        cout << "- [ERROR] Field " << field << " already registered!" << endl;
        return NULL; // 找到元素,已经注册过了
    }

    // 未找到元素，注册
    KTCAutoSelectorCtx* ctx = new KTCAutoSelectorCtx(field, selector);
    // ctx->selector        = selector;
    ctx->fieldName = name;

    (*_selectorMap)[ field ] = ctx;
    return ctx;
}
//-------------------------------------------------------------------------
void KTCAutoDialog::register_option_dialog(CATDlgDialog* dlg) {
    _optionDialog = dlg;
}
//-------------------------------------------------------------------------
void KTCAutoDialog::register_option_dialog(CATDlgDialog* dlg, CATDlgPushButton* optionBtn) {
    _optionDialog = dlg;
    // option dialog
    if (!optionBtn) return;

    AddAnalyseNotificationCB(optionBtn, optionBtn->GetPushBActivateNotification(),
                             (CATCommandMethod)&KTCAutoDialog::on_show_option_dialog, NULL);

    // close
    AddAnalyseNotificationCB(_optionDialog, _optionDialog->GetDiaCLOSENotification(),
                             (CATCommandMethod)&KTCAutoDialog::on_show_option_dialog, NULL);
}
//-------------------------------------------------------------------------
int KTCAutoDialog::ActionSubCommandReturn() {
    cout << "TODO KTCAutoDialog::ActionSubCommandReturn" << endl;
    return 0;
}
//-------------------------------------------------------------------------
void KTCAutoDialog::SetActiveField(int feild) {
    if (_selectorMap == NULL) return;
    _activeField = feild;

    // clear other field select
    for (KTCAutoSelectorCtxMap::iterator it = _selectorMap->begin(); it != _selectorMap->end();
         it++) {
        if (it->second == NULL || it->second->fieldKey == _activeField)
            continue; // 当前字段不处理，跳过

        it->second->ClearSelect(); // 清除其他字段的选择
    }
}
//-------------------------------------------------------------------------
void KTCAutoDialog::SetActiveFieldFocus() {
    if (_selectorMap == NULL) return;
    KTCAutoSelectorCtxMap::iterator it = _selectorMap->find(_activeField);
    if (it != _selectorMap->end()) it->second->SetSelect();
}

//-----------------------------------------------------------------------------
int KTCAutoDialog::selectorlist_setline(CATDlgSelectorList*     selectorList,
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
int KTCAutoDialog::selectorlist_setline(CATDlgSelectorList*                 selectorList,
                                        const CATListValCATISpecObject_var& iList,
                                        const CATUnicodeString&             noneSel) {
    if (!selectorList) return 1;                                     // return error code
    if (selectorList->GetLineCount() > 1) selectorList->ClearLine(); // clear multi line

    if (iList.Size() == 0) {
        selectorList->ClearLine(); // clear multi line
        selectorList->SetLine(noneSel, 0, CATDlgDataModify);
        return 0;
    }

    CATISpecObject_var object;
    CATUnicodeString   title;

    // loop ,list index from 1
    for (size_t i = 1; i <= iList.Size(); i++) {
        object = iList[ i ];

        if (!!object)
            title = object->GetDisplayName();
        else
            title = "(NULL Object)";

        // selector index from 0
        selectorList->SetLine(title, i - 1, CATDlgDataModify);
    }

    return iList.Size();

} //-----------------------------------------------------------------------------
void KTCAutoDialog::SendValueCHangeNotification() {
    CATCommand* cmd = GetFather();                   // get command
    if (cmd) SendNotification(cmd, _valueChangeNtf); // set notification
}
//-----------------------------------------------------------------------------
void KTCAutoDialog::ShowMessageBox(const CATUnicodeString& msg, CATDialog* dialog) {

    if (!dialog) dialog = (CATApplicationFrame::GetApplicationFrame())->GetMainWindow();

    // 创建消息通知对话框
    CATDlgNotify* notify = new CATDlgNotify(dialog, "Message", CATDlgNfyInformation);
    notify->DisplayBlocked(msg, "Warning");             // 显示对话框（模态）
    notify->RequestDelayedDestruction(), notify = NULL; // 释放资源
}
