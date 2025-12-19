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

#ifndef KTCAutoDialog_H
#define KTCAutoDialog_H

// Dialog Framework
#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "CATISpecObject.h"
#include "CATString.h"

// local
#include "KTCAutoCode.h"
#include "KTCAutoCodeUI.h"
#include "KTCAutoHSO.h"

/** @brief KTCAutoDialog Dialog */
class ExportedByKTCAutoCodeUI KTCAutoDialog : public CATDlgDialog {
    DeclareResource(KTCAutoDialog, CATDlgDialog);

public:
    KTCAutoDialog(CATDialog* iParent, CATMMUIPanelStateCmd* iFatherCmd,
                  const CATString& iObjectName, CATDlgStyle iStyle = NULL);
    virtual ~KTCAutoDialog();

public:
    /** @brief nodoc
     *  returned sub command, 0 for no Sub Command
     */
    int ActionSubCommandReturn();

    /** @brief Get Active Field */
    inline int GetActiveField() const {
        return _currentField;
    };

    /** @brief Get Active Field */
    inline KTC::ValueActionMode GetValueMode() const {
        return _actionMode;
    };

    /** @brief Register Parameter Dialog */
    void RegisterParameterDialog(CATDlgDialog* dlg);

    /** @brief nodoc */
    static int selectorlist_setline(CATDlgSelectorList*     selectorList,
                                    CATISpecObject_var      inputObject,
                                    const CATUnicodeString& noneSel = "(No Selection)");

    /** @brief nodoc */
    static int selectorlist_setline(CATDlgSelectorList*                 selectorList,
                                    const CATListValCATISpecObject_var& iList,
                                    const CATUnicodeString&             noneSel = "(No Selection)");

    /**
     * @brief Set Accept On Notify Of Value Change
     * @param[in] ipDialogAgent Value Change Agent
     */
    virtual void SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) = 0;

    /** @brief Set Active Field */
    void SetActiveField(int feild);

    /** @brief Set Active Field Focus */
    void SetActiveFieldFocus();

    /** @brief nodoc */
    static void ShowMessageBox(const CATUnicodeString& msg, CATDlgDialog* dialog = NULL);

    /** @brief Set Params to Dialog */
    virtual void UpdateDialog() = 0;

    /** @brief Update Params From Dialog */
    virtual void UpdateInfos() = 0;

    /** @brief Update dialog Sensitivity */
    virtual void UpdateSensitivity() = 0;

protected:
public:
    CATDlgDialog* _parameterDialog; // sub dialog
    CATHSO*       _catHSO;          // catia HSO

private:
    int                  _currentField; // current field
    KTC::ValueActionMode _actionMode;   // action mode
};

#endif
