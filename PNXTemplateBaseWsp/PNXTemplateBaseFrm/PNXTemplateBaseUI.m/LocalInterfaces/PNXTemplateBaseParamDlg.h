/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXTemplateBaseParamDlg.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateBaseParamDlg_H
#define PNXTemplateBaseParamDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"

//
#include "KTCAutoDefine.h"

/** @brief param setting dialog */
class PNXTemplateBaseParamDlg : public CATDlgDialog {
    // Allows customization/internationalization of command's messages
    // ---------------------------------------------------------------
    DeclareResource(PNXTemplateBaseParamDlg, CATDlgDialog);

public:
    PNXTemplateBaseParamDlg(CATDialog* iParent);
    virtual ~PNXTemplateBaseParamDlg();

    void Build();

protected:
    /** @brief close  */
    virtual void OnPNXTemplateBaseParamDlgWindCloseNotification(CATCommand*, CATNotification*,
                                                                CATCommandClientData data);

    /** @brief CANCEL  */
    virtual void OnPNXTemplateBaseParamDlgDiaCANCELNotification(CATCommand*, CATNotification*,
                                                                CATCommandClientData data);

    /** @brief OK  */
    virtual void OnPNXTemplateBaseParamDlgDiaOKNotification(CATCommand*, CATNotification*,
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
 CATDlgLabel*      _LabelMyStep;
 CATDlgSpinner*      _SpinnerMyStep;
 CATDlgLabel*      _LabelUnit;
 CATDlgEditor*      _EditorOutputMessage;
 CATDlgLabel*      _LabelOutputMessage;
//END CAA2 WIZARD WIDGET DECLARATION SECTION
    // clang-format on
};

#endif
