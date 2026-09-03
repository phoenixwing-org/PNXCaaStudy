// Local Framework
#include "PNXECombinedCurveContSubMenu.h"

// ApplicationFrame Framework
#include "CATCreateWorkshop.h"

// MecModInterface Framework
#include "CATIMechanicalProperties.h"

// other
#include "iostream.h"

//---------------------------------------------------------------------------------------------
// To declare that this class is a data extension of CAASysPlane
//
CATImplementClass(PNXECombinedCurveContSubMenu, DataExtension, CATBaseUnknown, CombinedCurve);
//
// To declare that PNXECombinedCurveContSubMenu implements CATIContextualSubMenu,
// insert  this following line in the interface dictionary:
//
//    CAASysPCombinedCurvelane   CATIContextualSubMenu  libPNXCombinedCurveUI
//
//---------------------------------------------------------------------------------------------
#include "TIE_CATIContextualSubMenu.h"
TIE_CATIContextualSubMenu(PNXECombinedCurveContSubMenu);

//-----------------------------------------------------------------------------------------
PNXECombinedCurveContSubMenu::PNXECombinedCurveContSubMenu()
    : _pMenu(NULL)
    , _pCAAMmrSwapActiveStr(NULL)

{
    cout << "### " << __FUNCTION__ << endl;

    // Creation of the starters
    NewAccess(CATCmdStarter, pCAAMmrResetPropertiesStr, CAAMmrResetPropertiesStr);
    NewAccess(CATCmdStarter, pCAAMmrParentChildrenStr, CAAMmrParentChildrenStr);

    // Check that the combined curve implements CATIMechanicalProperties
    // This is the interface to activate / deactivate the feature to the build
    //
    CATIMechanicalProperties* pMechProp = NULL;
    HRESULT rcMechProp = QueryInterface(IID_CATIMechanicalProperties, (void**)&pMechProp);
    if (SUCCEEDED(rcMechProp)) {
        NewAccess(CATCmdStarter, pCAAMmrSwapActiveStr, CAAMmrSwapActiveStr);
        _pCAAMmrSwapActiveStr = pCAAMmrSwapActiveStr;

        pMechProp->Release();
        pMechProp = NULL;
    }

    // These starters are set in the menu
    _pMenu = pCAAMmrParentChildrenStr;
    SetAccessNext(pCAAMmrParentChildrenStr, pCAAMmrResetPropertiesStr);

    if (NULL != _pCAAMmrSwapActiveStr) {
        SetAccessNext(pCAAMmrResetPropertiesStr, _pCAAMmrSwapActiveStr);
    }

    // Associate an instance of  command header to each starter
    // except for the activate/deactivate command- it will be done
    // in the GetContextualSubMenu method
    //
    SetAccessCommand(pCAAMmrResetPropertiesStr, "CATMmrPrtResetPropHdr");
    SetAccessCommand(pCAAMmrParentChildrenStr, "CATParentChildrenHdr");
}
//-----------------------------------------------------------------------------------------

PNXECombinedCurveContSubMenu::~PNXECombinedCurveContSubMenu() {
    cout << "### " << __FUNCTION__ << endl;

    if (NULL != _pMenu) _pMenu->Release();
    _pMenu = NULL;

    _pCAAMmrSwapActiveStr = NULL;
}

//-----------------------------------------------------------------------------------------

CATCmdAccess* PNXECombinedCurveContSubMenu::GetContextualSubMenu() {
    cout << "### " << __FUNCTION__ << endl;

    // The right command header is associated with the starter named _pCAAMmrSwapActiveStr,
    // This starter has been created once time in the extension's constructor,
    //
    //
    if (NULL != _pCAAMmrSwapActiveStr) {
        CATIMechanicalProperties* pMechProp = NULL;
        HRESULT rcMechProp = QueryInterface(IID_CATIMechanicalProperties, (void**)&pMechProp);
        if (SUCCEEDED(rcMechProp)) {
            int IsFeatureDeactivate = pMechProp->IsInactive();

            if (0 == IsFeatureDeactivate) {
                // from actif -> inactif
                SetAccessCommand(_pCAAMmrSwapActiveStr, "CATPrtInactiveHdr");
            } else {
                // from inactif -> actif
                SetAccessCommand(_pCAAMmrSwapActiveStr, "CATPrtActiveHdr");
            }

            pMechProp->Release();
            pMechProp = NULL;
        }
    }

    return (_pMenu);
}
//-----------------------------------------------------------------------------------------
