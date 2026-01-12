// COPYRIGHT DASSAULT SYSTEMES 2000

// Local FrameWork
#include "PNXCombinedCurveCatalogInstantiation.h"

// MecModInterfaces Framework
#include "CATIPartRequest.h"

// ComponentsCatalogsInterfaces Framework
#include "CATICatalogBrowser.h"
#include "CATICatalogDescription.h"
#include "CATICatalogLink.h"

// ApplicationFrame Framework
#include "CATFrmEditor.h"

// Visualization Framework
#include "CATPathElement.h"

// System Framework
#include "CATCommand.h"
#include "CATCreateExternalObject.h"
#include "CATString.h"
#include "CATUnicodeString.h"

#include "iostream.h"

CATImplementClass(PNXCombinedCurveCatalogInstantiation, DataExtension, CATBaseUnknown,
                  CombinedCurve);

//-----------------------------------------------------------------------------
// PNXCombinedCurveCatalogInstantiation : constructor
//-----------------------------------------------------------------------------
PNXCombinedCurveCatalogInstantiation::PNXCombinedCurveCatalogInstantiation() {
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCatalogInstantiation : destructor
//-----------------------------------------------------------------------------
PNXCombinedCurveCatalogInstantiation::~PNXCombinedCurveCatalogInstantiation() {
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICatalogInstantiation.h" // needed to tie the implementation to its interface
TIE_CATICatalogInstantiation(PNXCombinedCurveCatalogInstantiation);

//
// To declare that CombinedCurve implements CATICatalogInstantiation , insert
// the following line in the interface dictionary :
//
// CombinedCurve      CATICatalogInstantiation    libPNXCombinedCurveCatalog

HRESULT PNXCombinedCurveCatalogInstantiation::RunInstantiationCmd(
    const CATICatalogLink* pCatalogLink, const CATICatalogBrowser* pBrowser, int InstantiateMode,
    int RepeatMode, int& NotDone) {
    cout << "### " << __FUNCTION__ << endl;

    // The job is done by this method
    NotDone = 0;

    HRESULT rc = E_FAIL;
    if (NULL == pCatalogLink) return rc;

    // Retrieving the description
    CATICatalogDescription* pDesc = NULL;
    rc                            = pCatalogLink->GetPointedDescription(&pDesc);
    if (SUCCEEDED(rc) && (NULL != pDesc)) {
        // Testing if the UI active object is a MechanicalPart
        CATFrmEditor* pCurrentEditor = CATFrmEditor::GetCurrentEditor();
        if (NULL != pCurrentEditor) {
            CATPathElement path       = pCurrentEditor->GetUIActiveObject();
            int            nbSizePath = path.GetSize();

            rc = E_FAIL;
            if (nbSizePath > 0) {
                CATBaseUnknown* pLeaf = NULL;
                pLeaf                 = path[ nbSizePath - 1 ];
                if (NULL != pLeaf) {
                    CATIPartRequest* pInt = NULL;
                    rc = pLeaf->QueryInterface(IID_CATIPartRequest, (void**)&pInt);
                    if (SUCCEEDED(rc)) {
                        pInt->Release();
                        pInt = NULL;
                    }
                }
            }

            if (SUCCEEDED(rc)) {
                CATICatalogDescription::CATCatalogDescriptionType ComponentType;
                ComponentType = CATICatalogDescription::CATCatalogUnset;
                rc            = pDesc->GetDescriptionType(ComponentType);

                if (SUCCEEDED(rc) && (ComponentType == CATICatalogDescription::CATCatalogFeature)) {
                    // The command to create the combined curve
                    CATCommand*      newCommand  = NULL;
                    CATUnicodeString CommandName = "PNXCombinedCurveCmd";
                    CATUnicodeString CommandLib  = "PNXCombinedCurveUI";

                    // The command, a CATStateCommand, will be automatically deleted
                    newCommand = (CATCommand*)::CATCreateExternalObject(
                        CommandName.CastToCharPtr(), NULL, CommandLib.CastToCharPtr(),
                        NULL); // without argument

                    if (NULL == newCommand) {
                        rc = E_FAIL;
                    }
                }
                pDesc->Release();
                pDesc = NULL;
            }
        }
    }

    return rc;
}
