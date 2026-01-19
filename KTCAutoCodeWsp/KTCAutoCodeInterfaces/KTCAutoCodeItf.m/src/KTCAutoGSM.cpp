/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    KTCAutoCode
 * @file  		KTCAutoGSM.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// CAT
#include "CATFrmEditor.h"
#include "CATIGSMTool.h"
#include "CATIMechanicalRootFactory.h"
#include "CATIMmiNonOrderedGeometricalSet.h"
#include "CATIPrtPart.h"
#include "CATPathElement.h"
#include "iostream.h"

// Local
#include "KTCAutoDefine.h"
#include "KTCAutoGSM.h"

//-----------------------------------------------------------------------------
KTCAutoGSM::KTCAutoGSM() {

    // your code here:
}
//-----------------------------------------------------------------------------
KTCAutoGSM::~KTCAutoGSM() {
}
//-----------------------------------------------------------------------------
KTCAutoGSM::KTCAutoGSM(const KTCAutoGSM& iOriginal) {
    *this = iOriginal;
}
//-----------------------------------------------------------------------------
KTCAutoGSM& KTCAutoGSM::operator=(const KTCAutoGSM& iOriginal) {
    return *this;
}
//-----------------------------------------------------------------------------
bool KTCAutoGSM::IsInsideOrderedBody(CATISpecObject_var feature) {
    // TODO 实现代码
    cout << " - 没有实现 " << __FUNCTION__ << endl;
    return false;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoGSM::LookingForGeomSet(CATFrmEditor* catFrmEditor, CATIGSMTool** piGsmtool) {
    if ((NULL == piGsmtool) || (NULL == catFrmEditor)) return E_FAIL;

    HRESULT rc = E_FAIL;

    *piGsmtool = NULL;

    // Retrieves the Part feature which holds the current tool
    //
    CATIPrtPart*   pIPrtPart = NULL;
    CATPathElement PathAct   = catFrmEditor->GetUIActiveObject();
    rc                       = PathAct.Search(IID_CATIPrtPart, (void**)&pIPrtPart);

    if (SUCCEEDED(rc) && (NULL != pIPrtPart)) {
        CATBoolean ToolToCreate = TRUE;

        CATIBasicTool_var CurrentTool;
        CurrentTool = pIPrtPart->GetCurrentTool();

        if (NULL_var != CurrentTool) {
            // is it a GS ?
            CATIMmiNonOrderedGeometricalSet* pIGSOnCurrentTool = NULL;
            rc = CurrentTool->QueryInterface(IID_CATIMmiNonOrderedGeometricalSet,
                                             (void**)&pIGSOnCurrentTool);
            if (SUCCEEDED(rc)) {
                // Ok we have found a valid geometrical set
                ToolToCreate = FALSE;

                rc = pIGSOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**)piGsmtool);

                pIGSOnCurrentTool->Release();
                pIGSOnCurrentTool = NULL;
            }
        }

        if (TRUE == ToolToCreate) {
            rc = CreateTool(pIPrtPart, piGsmtool);
        }
    }

    KTCRelease(pIPrtPart); // 手动释放

    return rc;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoGSM::CreateTool(CATIPrtPart* pIPrtPart, CATIGSMTool** pIGsmTool) {
    if ((pIGsmTool == NULL) || (NULL == pIPrtPart)) {
        return E_FAIL;
    }

    *pIGsmTool = NULL;

    HRESULT rc = E_FAIL;

    CATISpecObject* pISpecOnPart = NULL;
    rc = pIPrtPart->QueryInterface(IID_CATISpecObject, (void**)&pISpecOnPart);
    if (SUCCEEDED(rc)) {

        // GetFeatContainer for a mechanical feature
        // is CATPrtCont, the specification container
        CATIContainer_var spContainer = pISpecOnPart->GetFeatContainer();
        if (NULL_var != spContainer) {
            //
            CATIMechanicalRootFactory* pMechanicalRootFactory = NULL;
            rc = spContainer->QueryInterface(IID_CATIMechanicalRootFactory,
                                             (void**)&pMechanicalRootFactory);
            if (SUCCEEDED(rc)) {
                // creates a new GS aggregated by the Part feature
                CATISpecObject_var spiSpecOnGSMTool;
                rc = pMechanicalRootFactory->CreateGeometricalSet("", pIPrtPart, spiSpecOnGSMTool);

                pMechanicalRootFactory->Release();
                pMechanicalRootFactory = NULL;

                if (NULL_var != spiSpecOnGSMTool) {
                    spiSpecOnGSMTool->QueryInterface(IID_CATIGSMTool, (void**)&(*pIGsmTool));
                }
            }
        }

        pISpecOnPart->Release();
        pISpecOnPart = NULL;
    }

    return rc;
}
