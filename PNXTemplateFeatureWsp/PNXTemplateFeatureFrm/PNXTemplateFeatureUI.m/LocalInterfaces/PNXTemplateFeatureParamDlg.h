/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureParamDlg.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

#ifndef PNXTemplateFeatureParamDlg_H
#define PNXTemplateFeatureParamDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"
#include "KTCAutoDefine.h"

/** @brief param setting dialog */
class PNXTemplateFeatureParamDlg : public CATDlgDialog {
    // Allows customization/internationalization of command's messages
    // ---------------------------------------------------------------
    DeclareResource(PNXTemplateFeatureParamDlg, CATDlgDialog);

public:
    PNXTemplateFeatureParamDlg(CATDialog* iParent);
    virtual ~PNXTemplateFeatureParamDlg();

    void Build();

protected:
    /** @brief close  */
    virtual void OnPNXTemplateFeatureParamDlgWindCloseNotification(CATCommand*, CATNotification*,
                                                                   CATCommandClientData data);

    /** @brief CANCEL  */
    virtual void OnPNXTemplateFeatureParamDlgDiaCANCELNotification(CATCommand*, CATNotification*,
                                                                   CATCommandClientData data);

    /** @brief OK  */
    virtual void OnPNXTemplateFeatureParamDlgDiaOKNotification(CATCommand*, CATNotification*,
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
