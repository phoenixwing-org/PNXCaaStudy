// COPYRIGHT DASSAULT SYSTEMES 2000
//======================================================================================
//
// PNXECombinedCurve.cpp
// Provide implementation to interface
//      PNXICombinedCurve
//======================================================================================

// Local Framework
#include "PNXECombinedCurve.h"

// ObjectSpecsModeler
#include "CATIDescendants.h"

// MecModInterfaces Framework
#include "CATIMfBRep.h"

// ObjectSpecsModeler Framework
#include "CATISpecAttrAccess.h" // needed to access feature attributes
#include "CATISpecAttrKey.h"    // needed to access to the feature attribute values
#include "CATISpecObject.h"     // needed to manage/query features

CATImplementClass(PNXECombinedCurve, DataExtension, CATBaseUnknown, CombinedCurve);

//-------------------------------------------------------------------------------------
// PNXECombinedCurve : constructor
//-------------------------------------------------------------------------------------
PNXECombinedCurve::PNXECombinedCurve()
    : CATBaseUnknown() {
}

//-------------------------------------------------------------------------------------
// PNXECombinedCurve : destructor
//-------------------------------------------------------------------------------------
PNXECombinedCurve::~PNXECombinedCurve() {
}

// Tie the implementation to its interface
// ---------------------------------------

#include "TIE_PNXICombinedCurve.h" // needed to tie the implementation to its interface
TIE_PNXICombinedCurve(PNXECombinedCurve);

// To declare that CombinedCurve implements PNXICombinedCurve, insert
// the following line in the interface dictionary:
//
// CombinedCurve  PNXICombinedCurve  libPNXCombinedCurve

//-------------------------------------------------------------------------------------
HRESULT PNXECombinedCurve::SetFirstPoint(CATISpecObject* ipiSpecOnCurve) {
    // Gets a pointer on CATISpecAttrAccess
    CATISpecAttrAccess* piSpecAttrAccessOnCC = NULL;
    HRESULT             rc = QueryInterface(IID_CATISpecAttrAccess, (void**)&piSpecAttrAccessOnCC);
    if (SUCCEEDED(rc)) {
        // Gets a pointer on the curve attribute
        CATISpecAttrKey* piSpecAttrKey = piSpecAttrAccessOnCC->GetAttrKey("FirstPoint");
        if (NULL == piSpecAttrKey) {
            rc = E_FAIL;
        }
        else {
            CATISpecObject_var spiSpecOnCurve(ipiSpecOnCurve);

            if (NULL_var != spiSpecOnCurve) {
                // If the feature is a Feature BRep it must be aggregated by the CC
                CATIMfBRep* pIMfBRep = NULL;
                rc = spiSpecOnCurve->QueryInterface(IID_CATIMfBRep, (void**)&pIMfBRep);
                if (SUCCEEDED(rc)) {
                    CATISpecObject* pFather = spiSpecOnCurve->GetFather();
                    if (NULL == pFather) {
                        CATIDescendants* pIDescendantsOnCC = NULL;
                        rc = QueryInterface(IID_CATIDescendants, (void**)&pIDescendantsOnCC);

                        if (SUCCEEDED(rc)) {
                            pIDescendantsOnCC->Append(spiSpecOnCurve);

                            pIDescendantsOnCC->Release();
                            pIDescendantsOnCC = NULL;
                        }
                    }
                    else {
                        pFather->Release();
                        pFather = NULL;
                        rc      = E_FAIL;
                    }

                    pIMfBRep->Release();
                    pIMfBRep = NULL;
                }
                else
                    rc = S_OK; // it's not an error

                // Sets the curve as input of the CC
                if (SUCCEEDED(rc)) {
                    piSpecAttrAccessOnCC->SetSpecObject(piSpecAttrKey, spiSpecOnCurve);
                }
            }
            else {
                // The input curve pointer is null
                piSpecAttrAccessOnCC->UnsetAttributeValue(piSpecAttrKey);
            }

            piSpecAttrKey->Release();
            piSpecAttrKey = NULL;
        }

        piSpecAttrAccessOnCC->Release();
        piSpecAttrAccessOnCC = NULL;
    }

    return rc;
}
//-------------------------------------------------------------------------------------
HRESULT PNXECombinedCurve::GetFirstPoint(CATISpecObject** opiSpecOnCurve) {
    HRESULT rc = E_FAIL;

    if (NULL == opiSpecOnCurve) return E_FAIL;

    // Gets a pointer on CATISpecObject
    CATISpecAttrAccess* piSpecAttrAccessOnCC = NULL;
    rc = QueryInterface(IID_CATISpecAttrAccess, (void**)&piSpecAttrAccessOnCC);
    if (SUCCEEDED(rc)) {
        CATISpecAttrKey* piSpecAttrKey = NULL;
        piSpecAttrKey                  = piSpecAttrAccessOnCC->GetAttrKey("FirstPoint");

        rc = E_FAIL;

        if (NULL != piSpecAttrKey) {
            // Gets the curve
            *opiSpecOnCurve = piSpecAttrAccessOnCC->GetSpecObject(piSpecAttrKey);

            if (NULL != *opiSpecOnCurve) {
                rc = S_OK;
            }

            piSpecAttrKey->Release();
            piSpecAttrKey = NULL;
        }

        piSpecAttrAccessOnCC->Release();
        piSpecAttrAccessOnCC = NULL;
    }

    return rc;
}
//-------------------------------------------------------------------------------------
HRESULT PNXECombinedCurve::SetMainDir(CATISpecObject* ipValue) {
    // Gets a pointer on CATISpecAttrAccess
    CATISpecAttrAccess* piSpecAttrAccessOnCC = NULL;
    HRESULT             rc = QueryInterface(IID_CATISpecAttrAccess, (void**)&piSpecAttrAccessOnCC);
    if (SUCCEEDED(rc)) {
        // Gets a pointer on the curve attribute
        CATISpecAttrKey* piSpecAttrKey = piSpecAttrAccessOnCC->GetAttrKey("MainDir");

        if (NULL == piSpecAttrKey) {
            rc = E_FAIL;
        }
        else {

            CATISpecObject_var spiSpecOnMainDir(ipValue);

            if (NULL_var != spiSpecOnMainDir) {
                // If the feature is a Feature BRep it must be aggregated by the CC
                CATIMfBRep* pIMfBRep = NULL;
                rc = spiSpecOnMainDir->QueryInterface(IID_CATIMfBRep, (void**)&pIMfBRep);
                if (SUCCEEDED(rc)) {
                    CATISpecObject* pFather = spiSpecOnMainDir->GetFather();
                    if (NULL == pFather) {
                        CATIDescendants* pIDescendantsOnCC = NULL;
                        rc = QueryInterface(IID_CATIDescendants, (void**)&pIDescendantsOnCC);

                        if (SUCCEEDED(rc)) {
                            pIDescendantsOnCC->Append(spiSpecOnMainDir);

                            pIDescendantsOnCC->Release();
                            pIDescendantsOnCC = NULL;
                        }
                    }
                    else {
                        pFather->Release();
                        pFather = NULL;
                        rc      = E_FAIL;
                    }

                    pIMfBRep->Release();
                    pIMfBRep = NULL;
                }
                else
                    rc = S_OK; // it's not an error

                // Sets the curve as input of the CC
                if (SUCCEEDED(rc)) {
                    piSpecAttrAccessOnCC->SetSpecObject(piSpecAttrKey, spiSpecOnMainDir);
                }
            }
            else {
                // The input curve pointer is null
                piSpecAttrAccessOnCC->UnsetAttributeValue(piSpecAttrKey);
            }

            piSpecAttrKey->Release();
            piSpecAttrKey = NULL;
        }

        piSpecAttrAccessOnCC->Release();
        piSpecAttrAccessOnCC = NULL;
    }

    return rc;
}
//-------------------------------------------------------------------------------------
HRESULT PNXECombinedCurve::GetMainDir(CATISpecObject** opiValue) {

    HRESULT rc = E_FAIL;

    if (NULL == opiValue) return E_FAIL;

    // Gets a pointer on CATISpecObject
    CATISpecAttrAccess* piSpecAttrAccessOnCC = NULL;
    rc = QueryInterface(IID_CATISpecAttrAccess, (void**)&piSpecAttrAccessOnCC);
    if (SUCCEEDED(rc)) {
        CATISpecAttrKey* piSpecAttrKey = NULL;
        piSpecAttrKey                  = piSpecAttrAccessOnCC->GetAttrKey("MainDir");
        rc                             = E_FAIL;

        if (NULL != piSpecAttrKey) {
            // Gets the curve
            *opiValue = piSpecAttrAccessOnCC->GetSpecObject(piSpecAttrKey);

            if (NULL != *opiValue) {
                rc = S_OK;
            }

            piSpecAttrKey->Release();
            piSpecAttrKey = NULL;
        }

        piSpecAttrAccessOnCC->Release();
        piSpecAttrAccessOnCC = NULL;
    }

    return rc;
}
