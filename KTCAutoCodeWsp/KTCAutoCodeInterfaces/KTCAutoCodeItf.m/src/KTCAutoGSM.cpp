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
#include "CATIMmiGeometricalSet.h"
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
HRESULT KTCAutoGSM::CreateTool(CATIPrtPart* ipIPrtPart, CATIGSMTool** pIGsmTool) {
    if ((pIGsmTool == NULL) || (NULL == ipIPrtPart)) {
        return E_FAIL;
    }

    *pIGsmTool                   = NULL;
    HRESULT         rc           = E_FAIL;
    CATISpecObject* pISpecOnPart = NULL;
    rc = ipIPrtPart->QueryInterface(IID_CATISpecObject, (void**)&pISpecOnPart);
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
                rc = pMechanicalRootFactory->CreateGeometricalSet("", ipIPrtPart, spiSpecOnGSMTool);

                KTCRelease(pMechanicalRootFactory); // 手动释放

                if (NULL_var != spiSpecOnGSMTool) {
                    spiSpecOnGSMTool->QueryInterface(IID_CATIGSMTool, (void**)&(*pIGsmTool));
                }
            }
        }

        KTCRelease(pISpecOnPart); // 手动释放
    }

    return rc;
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
            if (1 == IsAnOrderedBody) oIsInsideOrderedBody = true;

            KTCRelease(piGSMToolFatherCC); // 手动释放
        }

        KTCRelease(pFatherCC); // 手动释放
    }

    return oIsInsideOrderedBody;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoGSM::LookingForAnyTypeOfBody(CATFrmEditor* iCatFrmEditor,
                                            CATIGSMTool** oppiGsmtool) {
    //===============================================================
    // 代码参考 CAA百科全书的 CombinedCurve Command里面的示例
    //===============================================================
    if (NULL == oppiGsmtool || NULL == iCatFrmEditor) return E_INVALIDARG;

    *oppiGsmtool             = NULL;
    HRESULT        rc        = E_FAIL;
    CATIPrtPart*   pIPrtPart = NULL;
    CATPathElement PathAct   = iCatFrmEditor->GetUIActiveObject();

    rc = PathAct.Search(IID_CATIPrtPart, (void**)&pIPrtPart);
    if (SUCCEEDED(rc) && (NULL != pIPrtPart)) {
        bool              ToolToCreate = true;
        CATIBasicTool_var CurrentTool;
        CurrentTool = pIPrtPart->GetCurrentTool();

        if (NULL_var != CurrentTool) {
            // is it a GSMTool or an hybrid body ?
            CATIGSMTool* pIGSMToolOnCurrentTool = NULL;
            rc = CurrentTool->QueryInterface(IID_CATIGSMTool, (void**)&pIGSMToolOnCurrentTool);
            if (SUCCEEDED(rc)) {
                // Ok we have found a valid body
                ToolToCreate = false;
                *oppiGsmtool = pIGSMToolOnCurrentTool;
            }
        }

        // 沒有检索出，进行创建
        if (ToolToCreate) rc = CreateTool(pIPrtPart, oppiGsmtool);
    }

    KTCRelease(pIPrtPart); // 手动释放

    return rc;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoGSM::LookingForGeomSet(CATFrmEditor* iCatFrmEditor, CATIGSMTool** oppiGsmtool) {
    //===============================================================
    // 代码参考 CAA百科全书的 CombinedCurve Command里面的示例
    //===============================================================
    if (NULL == oppiGsmtool || NULL == iCatFrmEditor) return E_INVALIDARG;

    HRESULT rc = E_FAIL;

    *oppiGsmtool = NULL;

    // Retrieves the Part feature which holds the current tool
    //
    CATIPrtPart*   pIPrtPart = NULL;
    CATPathElement PathAct   = iCatFrmEditor->GetUIActiveObject();
    rc                       = PathAct.Search(IID_CATIPrtPart, (void**)&pIPrtPart);

    if (SUCCEEDED(rc) && (NULL != pIPrtPart)) {
        bool ToolToCreate = true;

        CATIBasicTool_var CurrentTool;
        CurrentTool = pIPrtPart->GetCurrentTool();

        if (NULL_var != CurrentTool) {
            // is it a GS ?
            CATIMmiNonOrderedGeometricalSet* pIGSOnCurrentTool = NULL;
            rc = CurrentTool->QueryInterface(IID_CATIMmiNonOrderedGeometricalSet,
                                             (void**)&pIGSOnCurrentTool);
            if (SUCCEEDED(rc)) {
                // Ok we have found a valid geometrical set
                ToolToCreate = false;
                rc = pIGSOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**)oppiGsmtool);
                KTCRelease(pIGSOnCurrentTool); // 手动释放
            }
        }

        // 沒有检索出，进行创建
        if (ToolToCreate) rc = CreateTool(pIPrtPart, oppiGsmtool);
    }

    KTCRelease(pIPrtPart); // 手动释放

    return rc;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoGSM::LookingForGeomSetOrOrderedGeomSet(CATFrmEditor* iCatFrmEditor,
                                                      CATIGSMTool** oppiGsmtool) {
    //===============================================================
    // 代码参考 CAA百科全书的 CombinedCurve Command里面的示例
    //===============================================================
    if (NULL == oppiGsmtool || NULL == iCatFrmEditor) return E_INVALIDARG;

    *oppiGsmtool             = NULL;
    HRESULT        rc        = E_FAIL;
    CATIPrtPart*   pIPrtPart = NULL;
    CATPathElement PathAct   = iCatFrmEditor->GetUIActiveObject();

    rc = PathAct.Search(IID_CATIPrtPart, (void**)&pIPrtPart);

    if (SUCCEEDED(rc) && (NULL != pIPrtPart)) {
        bool              ToolToCreate = true;
        CATIBasicTool_var CurrentTool;
        CurrentTool = pIPrtPart->GetCurrentTool();

        if (NULL_var != CurrentTool) {
            // is it a GSMTool ?
            CATIMmiGeometricalSet* pIGSMToolOnCurrentTool = NULL;
            rc = CurrentTool->QueryInterface(IID_CATIMmiGeometricalSet,
                                             (void**)&pIGSMToolOnCurrentTool);
            if (SUCCEEDED(rc)) {
                // Ok we have found a valid geometrical set ( ordered or not )
                ToolToCreate = false;
                rc = pIGSMToolOnCurrentTool->QueryInterface(IID_CATIGSMTool, (void**)oppiGsmtool);
                KTCRelease(pIGSMToolOnCurrentTool); // 手动释放
            }
        }

        // 沒有检索出，进行创建
        if (ToolToCreate) rc = CreateTool(pIPrtPart, oppiGsmtool);
    }

    KTCRelease(pIPrtPart); // 手动释放

    return rc;
}
//-----------------------------------------------------------------------------
HRESULT KTCAutoGSM::QueryInterface(CATIGSMTool* ipiGSMTool, const IID& iIID, void** oPPV) {
    if (NULL == oPPV) return E_INVALIDARG;
    *oPPV = NULL;
    if (NULL == ipiGSMTool) return E_INVALIDARG;

    HRESULT rc = E_FAIL; // set fail

    // 获得CATIContainer_var
    CATISpecObject_var piSpecObjOnTool = ipiGSMTool;
    if (NULL_var != piSpecObjOnTool) {
        // GetFeatContainer for a mechanical feature
        // is CATPrtCont, the specification container
        CATIContainer_var spContainer = piSpecObjOnTool->GetFeatContainer();

        // checkout feature by iid
        if (NULL_var != spContainer) rc = spContainer->QueryInterface(iIID, oPPV);
    }

    return rc;
}