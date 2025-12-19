/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterParamDlg.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXV5V6AdapterParamDlg_H
#define PNXV5V6AdapterParamDlg_H

#include "CATDlgInclude.h"

// Auto Code
#include "CATDlgDialog.h"

/** @brief param setting dialog */
class PNXV5V6AdapterParamDlg : public CATDlgDialog {
    // Allows customization/internationalization of command's messages
    // ---------------------------------------------------------------
    DeclareResource(PNXV5V6AdapterParamDlg, CATDlgDialog);

public:
    PNXV5V6AdapterParamDlg(CATDialog* iParent);
    virtual ~PNXV5V6AdapterParamDlg();

    void Build();

protected:
    /** @brief close  */
    virtual void OnPNXV5V6AdapterParamDlgWindCloseNotification(CATCommand*, CATNotification*,
                                                               CATCommandClientData data);

    /** @brief CANCEL  */
    virtual void OnPNXV5V6AdapterParamDlgDiaCANCELNotification(CATCommand*, CATNotification*,
                                                               CATCommandClientData data);

    /** @brief OK  */
    virtual void OnPNXV5V6AdapterParamDlgDiaOKNotification(CATCommand*, CATNotification*,
                                                           CATCommandClientData data);

public:
    /** @brief send value change notify  */
    void SendValueChangeNotify();

public:
    CATDlgSpinner* _SpinnerForValueChange; // for value change Only

    // clang-format off
//CAA2 WIZARD WIDGET DECLARATION SECTION
 CATDlgFrame*      _FrameOthers;
 CATDlgLabel*      _LabelVersion;
 CATDlgEditor*      _EditorFeatureVersion;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};
#endif
