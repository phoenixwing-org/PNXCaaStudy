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

#ifndef KTCDlgDialog_H
#define KTCDlgDialog_H

// Dialog Framework
#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "CATString.h"

// local
#include "KTCAutoCodeUI.h"
class CATMMUIPanelStateCmd;
class CATDialogAgent;

/** @brief KTCDlgDialog Dialog */
class ExportedByKTCAutoCodeUI KTCDlgDialog : public CATDlgDialog {
    DeclareResource(KTCDlgDialog, CATDlgDialog);

public:
    KTCDlgDialog(CATDialog* iParent, CATMMUIPanelStateCmd* iFatherCmd, const CATString& iObjectName,
                 CATDlgStyle iStyle = NULL);
    virtual ~KTCDlgDialog();

public:
    /** @brief Register Parameter Dialog */
    void RegisterParameterDialog(CATDlgDialog* dlg);

    /**
     * @brief Set Accept On Notify Of Value Change
     * @param[in] ipDialogAgent Value Change Agent
     */
    virtual void SetAcceptOnNotifyOfValueChange(CATDialogAgent* ipDialogAgent) = 0;

    /** @brief Set Active Field Focus */
    void SetActiveFieldFocus();

    /** @brief Set Params to Dialog */
    virtual void UpdateDialog() = 0;

    /** @brief Update Params From Dialog */
    virtual void UpdateInfos() = 0;

    /** @brief Update dialog Sensitivity */
    virtual void UpdateSensitivity() = 0;

protected:
public:
    CATDlgDialog* _parameterDialog;
    int           _currentField;
};

#endif
