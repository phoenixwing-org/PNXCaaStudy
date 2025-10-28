/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXCurveDivisionParamDlg.h
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 * @note
 * =============================================================================
 */

#ifndef PNXCurveDivisionParamDlg_H
#define PNXCurveDivisionParamDlg_H

#include "CATDlgDialog.h"
#include "CATDlgInclude.h"

/** @brief param setting dialog */
class PNXCurveDivisionParamDlg : public CATDlgDialog {
    // Allows customization/internationalization of command's messages
    // ---------------------------------------------------------------
    DeclareResource(PNXCurveDivisionParamDlg, CATDlgDialog);

public:
    PNXCurveDivisionParamDlg(CATDialog* iParent);
    virtual ~PNXCurveDivisionParamDlg();

    void Build();

protected:
    /** @brief close  */
    virtual void OnPNXCurveDivisionParamDlgWindCloseNotification(CATCommand*, CATNotification*,
                                                                  CATCommandClientData data);

    /** @brief CANCEL  */
    virtual void OnPNXCurveDivisionParamDlgDiaCANCELNotification(CATCommand*, CATNotification*,
                                                                  CATCommandClientData data);

    /** @brief OK  */
    virtual void OnPNXCurveDivisionParamDlgDiaOKNotification(CATCommand*, CATNotification*,
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
