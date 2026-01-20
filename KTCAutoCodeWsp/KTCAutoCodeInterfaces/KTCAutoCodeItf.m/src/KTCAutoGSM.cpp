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
    //===============================================================
    // 代码参考 CAA百科全书的 CombinedCurve Command里面的示例
    //===============================================================
    if (!feature) return false;

    //
    // returns true if the CC is inside an ordered body
    // otherwise false
    //
    HRESULT rc = E_FAIL;

    bool oIsInsideOrderedBody = false;

    // Retrieve the father of the CC
    CATISpecObject* pFatherCC = feature->GetFather();
    if (NULL != pFatherCC) {
        // The father must be a GSMTool or an HybridBody
        CATIGSMTool* piGSMToolFatherCC = NULL;
        rc = pFatherCC->QueryInterface(IID_CATIGSMTool, (void**)&piGSMToolFatherCC);
        if (SUCCEEDED(rc)) {
            // The father can be a ordered or not
            int IsAnOrderedBody = -1;
            piGSMToolFatherCC->GetType(IsAnOrderedBody);
            if (1 == IsAnOrderedBody) {
                oIsInsideOrderedBody = true;
            }

            KTCRelease(piGSMToolFatherCC); // 手动释放
        }

        KTCRelease(pFatherCC); // 手动释放
    }

    return oIsInsideOrderedBody;
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
