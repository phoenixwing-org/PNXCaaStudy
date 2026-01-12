/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXETemplateFeatureIcon.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

#include "PNXETemplateFeatureIcon.h"
#include "iostream.h" //need for CAA iostream.not c++

//-----------------------------------------------------------------------------
// To declare that the class derives is a data extension of PNXTemplateFeature
//

CATImplementClass(PNXETemplateFeatureIcon, DataExtension, CATBaseUnknown, PNXTemplateFeature);

// Tie the implementation to its interface
#include "TIE_CATIIcon.h" // needed to tie the implementation to its interface
TIE_CATIIcon(PNXETemplateFeatureIcon);

//
// To declare that PNXTemplateFeature implements CATIIcon,
// insert the following line in the interface dictionary :
// PNXTemplateFeature      CATIIcon    libPNXTemplateFeatureItf
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
PNXETemplateFeatureIcon::PNXETemplateFeatureIcon()
    : CATBaseUnknown() {
    // cout << "### " << __FUNCTION__ << endl;
}
//-----------------------------------------------------------------------------
PNXETemplateFeatureIcon::~PNXETemplateFeatureIcon() {
    // cout << "### " << __FUNCTION__ << endl;
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeatureIcon::GetIconName(CATUnicodeString& oName) {
    // cout << "### " << __FUNCTION__ << endl;

    oName = CATUnicodeString("I_PNXTemplateFeature");
    /*
    use these for get different icon if you want
    if (_name.GetLengthInChar() < 4)
        oName = CATUnicodeString("I_PNXTemplateFeature");
    else
        oName = _name;
    */
    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeatureIcon::SetIconName(const CATUnicodeString& iName) {
    /* // use these for set if you want
    cout << "### " << __FUNCTION__ << endl;

    if (iName.GetLengthInChar() < 4)
        return E_FAIL;

    _name = iName;
    return S_OK;
    */
    return E_FAIL;
}
