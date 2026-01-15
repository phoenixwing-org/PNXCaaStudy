/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXETemplateFeatureFactory.cpp
 * @brief       Provide implementation to interface PNXITemplateFeatureFactory
 */

// Local Framework
#include "PNXETemplateFeatureFactory.h"

// KTCAutoCode Framework
#include "KTCAutoAttrAccess.h"
#include "KTCAutoDefine.h"
#include "KtListV.h"

// PNXTemplateFeatureInterfaces Framework
#include "PNXITemplateFeature.h" // needed by the factory to return a pointer on this interface

// ObjectSpecsModeler Framework
#include "CATISpecObject.h" // needed to manage features

// ObjectModelerBase Framework
#include "CATIContainer.h" //

// AlgorithmConfiguration Management
#include "CATMmrAlgoConfigServices.h" //needed to subscribe to repository for AlgorithmConfiguration

// BackUp / StartUp Management
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"
#include "CATIDescendants.h"
#include "CATIInputDescription.h"
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATMmrFeatureAttributes.h"
#include "CATOsmSUHandler.h"

// System
#include "CATUnicodeString.h"
#include "iostream.h"

// #define CATIAV5R25

// fit for high version catia catalog
#if defined CATIAV5R25
#include "CATFmContainerFacade.h"
#include "CATFmCredentials.h"
#include "CATFmFeatureFacade.h"
#include "CATFmFeatureModelerID.h"
#include "CATFmStartUpFacade.h"

#else                                  // version before CATIAV5R25
#include "CATCatalogFactoryServices.h" // needed to create a catalog
#include "CATICatalog.h"
#endif

// Error title
#define ERROR_TITLE_CreateTemplateFeature \
    "     {NG}. PNXETemplateFeatureFactory::CreateTemplateFeature(...) ..."

CATImplementClass(PNXETemplateFeatureFactory, DataExtension, CATBaseUnknown, CATPrtCont);

//---------------------------------------------------------------------------------------------------
// PNXETemplateFeatureFactory : constructor
//---------------------------------------------------------------------------------------------------
PNXETemplateFeatureFactory::PNXETemplateFeatureFactory()
    : CATBaseUnknown() {
}

//---------------------------------------------------------------------------------------------------
// PNXETemplateFeatureFactory : destructor
//---------------------------------------------------------------------------------------------------
PNXETemplateFeatureFactory::~PNXETemplateFeatureFactory() {
}
//
// To declare that GSMTool implements PNXITemplateFeatureFactory, insert
// the following line in the interface dictionary:
//
// GSMTool  PNXITemplateFeatureFactory    libPNXTemplateFeatureItf
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_PNXITemplateFeatureFactory.h" // needed to tie the implementation to its interface
TIE_PNXITemplateFeatureFactory(PNXETemplateFeatureFactory);

//---------------------------------------------------------------------------------------------------
HRESULT PNXETemplateFeatureFactory::CreateTemplateFeature(
    PNXTemplateFeatureParam& ioParam, CATISpecObject_var& ospObjectOnTemplateFeature) {
    ospObjectOnTemplateFeature             = NULL_var; // set NULL_var first
    PNXITemplateFeature* pITemplateFeature = NULL;     // your feature
    HRESULT              hr                = S_OK;

    //===============================================================================================
    //
    // -1- Retrieves a CATICkeParmFactory interface on this.
    //
    //===============================================================================================

    // Get parm factory
    CATICkeParmFactory* piParmFactory = NULL;
    hr = this->QueryInterface(IID_CATICkeParmFactory, (void**)&piParmFactory); // query
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature
             << " QueryInterface(IID_CATICkeParmFactory)! hr = " << hr << endl;
        return hr; // error
    }

// fit for high version catia catalog
#if defined CATIAV5R25

    // -1- Opening the Catalog
    CATIContainer_var spiSpecContainer(this);
    if (NULL_var == spiSpecContainer) {
        hr = E_POINTER;
        cout << ERROR_TITLE_CreateTemplateFeature << " CATIContainer_var  is NULL_var!  hr = " << hr
             << endl;
        return hr;
    }

    CATUnicodeString uCatalogStorageName = "PNXTemplateFeatureFeature";
    CATUnicodeString ClientId            = "PNXTemplateFeatureID";
    CATUnicodeString PartnerID           = "PNXTemplateFeature";
    CATFmCredentials myCredentials;
    hr = myCredentials.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, PartnerID);
    if (SUCCEEDED(hr)) {
        hr = myCredentials.RegisterAsCatalogOwner(uCatalogStorageName, ClientId);
    }
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature << " Register catalog error!  hr = " << hr
             << endl;
        return hr;
    }

    // 2. Get Container Facade
    CATFmContainerFacade myContainerFacade(myCredentials, this);

    // 3. Get StartUp Facade
    CATUnicodeString   StartupType = "`PNXTemplateFeature`@`PNXTemplateFeatureFeature.CATfct`";
    CATFmStartUpFacade myStartUpFacade(myCredentials, StartupType);

    // 4. Instance StartUp
    CATFmFeatureFacade myFeatureFacade;
    hr = myStartUpFacade.InstantiateIn(myContainerFacade, myFeatureFacade);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature << " InstantiateIn() error!  hr = " << hr << endl;
        return hr;
    }

    // get PNXITemplateFeature pointer
    hr = myFeatureFacade.QueryInterfaceOnFeature(IID_PNXITemplateFeature,
                                                 (void**)&pITemplateFeature);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature
             << " QueryInterface(IID_PNXITemplateFeature)!  hr = " << hr << endl;
        return hr;
    }

    ospObjectOnTemplateFeature = pITemplateFeature; // convert to CATISpecObject_var
    if (NULL_var == ospObjectOnTemplateFeature) {
        hr = E_POINTER;
        cout << ERROR_TITLE_CreateTemplateFeature << " Get CATISpecObject_var Error! hr = " << hr
             << endl;
        return hr;
    }

#else // low version catia before 25

    //===============================================================================================
    //
    //  What does the factory do ?
    //
    //     o -1- Retrieves a CATICkeParmFactory interface on this.
    //     o -2- Opens the User Feature catalog
    //     o -3- Retrieves User Feature's startup
    //     o -4- Creates a User Feature instance
    //     o -5- Subscribes to repository for Configuration Data Storage
    //     o -6- Gets Feature Type Information for BackUp / StartUp management
    //     o -7- Sets default values for the attributes of the instance
    //
    //
    //===============================================================================================

    //===============================================================================================
    //
    // -2- Opens the catalog
    //
    //===============================================================================================

    CATUnicodeString StartupType = "PNXTemplateFeature";
    CATUnicodeString ClientId    = "PNXTemplateFeatureID";
    CATUnicodeString StorageName = "PNXTemplateFeatureFeature.CATfct";

    // Initial a CATOsmSUHandler to access the catalog
    // Provides access to a startup stored in catalogs.
    CATOsmSUHandler addOpSUHandler(StartupType, ClientId, StorageName);

    //===============================================================================================
    //
    // -3- Retrieves startup
    //
    //===============================================================================================

    CATISpecObject_var spSpecOnStartUp = NULL_var;
    hr                                 = addOpSUHandler.RetrieveSU(spSpecOnStartUp);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature << " RetrieveSU(...)! hr = " << hr << endl;
        return hr;
    }

    //===============================================================================================
    //
    // -4- Creates a Object instance to ospObjectOnTemplateFeature
    //
    //===============================================================================================

    CATIContainer_var spContainer = this; // get current factory containers
    // instanciate by CATOsmSUHandler
    hr = addOpSUHandler.Instanciate(ospObjectOnTemplateFeature, spContainer, NULL_string);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature << " Instanciate(...)!  hr = " << hr << endl;
        return hr;
    }

    hr = ospObjectOnTemplateFeature->QueryInterface(IID_PNXITemplateFeature,
                                                    (void**)&pITemplateFeature);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature
             << " QueryInterface(IID_PNXITemplateFeature)!  hr = " << hr << endl;
        return hr;
    }

#endif // end of high version catia catalog

    // used for auto append param on tree. kevin.
    KtListV<CATUnicodeString> spListParmName;
    KtListV<bool>             ListOnTree;
    KtListV<CATICkeParm_var>  spListParm;
    PNXTemplateFeatureParam*  parameter = &ioParam;

#if 0
	//4.1 On Tree
	//DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
	// START KEVIN CAA WIZARD SECTION PNXTemplateFeature FACTRY ON TREE

	// clang-format off

	// 4, MyStep,
	spListParmName.Append("MyStep");
	spListParm.Append(piParmFactory->CreateReal("My Step", parameter->MyStep));
	ListOnTree.Append(true);

	// clang-format on
	// END KEVIN CAA WIZARD SECTION PNXTemplateFeature FACTRY ON TREE

#endif

#if 0
    // KEVIN MANUAL CODE START
    // MyStep,
    spListParmName.Append("MyStep");
    spListParm.Append(piParmFactory->CreateReal("Step", parameter->MyStep));
    ListOnTree.Append(true);

    // KEVIN MANUAL CODE END

    if (spListParm.size() > 0) {
        CATISpecAttrAccess* pISpecAttrAccess = NULL; //
        hr = ospObjectOnTemplateFeature->QueryInterface(IID_CATISpecAttrAccess,
                                                        (void**)&pISpecAttrAccess);
        if (FAILED(hr)) {
            cout << ERROR_TITLE_CreateTemplateFeature
                 << " QueryInterface(IID_CATISpecAttrAccess)!  hr = " << hr << endl;
            return hr;
        }

        CATISpecAttrKey* pISpecAttrKey = NULL; // Key
        // put on tree initial
        for (size_t i = 0; i < spListParm.size(); i++) {
            pISpecAttrKey = pISpecAttrAccess->get_CATISpecAttrKey(spListParmName[ i ].ConvertToChar());
            if (!pISpecAttrKey) {
                cout << "GetKey Error" << spListParmName[ i ] << endl;
                continue;
            }

            // your code here

            // set all read only
            spListParm[ i ]->SetUserAccess(CATICkeParm::ReadOnly);

            pISpecAttrAccess->SetSpecObject(pISpecAttrKey, spListParm[ i ]); // set;

            KTCRelease(pISpecAttrKey); // release
        }
        KTCRelease(pISpecAttrAccess); // release

        // Show On tree
        CATIDescendants* pIDescendants = NULL; // des
        hr =
            ospObjectOnTemplateFeature->QueryInterface(IID_CATIDescendants, (void**)&pIDescendants);
        if (FAILED(hr)) {
            cout << ERROR_TITLE_CreateTemplateFeature
                 << " QueryInterface(IID_CATIDescendants)!  hr = " << hr << endl;
            ;
            return hr;
        }

        for (size_t i = 0; i < spListParm.size(); i++) {
            if (!spListParm[ i ] || !ListOnTree[ i ]) continue; // not on  tree

            pIDescendants->Append((spListParm[ i ])); // on tree
        }
        KTCRelease(pIDescendants); // release
    }

    //===============================================================================================
    //
    // -5- Subscribes to repository for Configuration Data Storage
    //
    //===============================================================================================

    hr = CATMmrAlgoConfigServices::CreateConfigurationData(ospObjectOnTemplateFeature);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_CreateTemplateFeature << " CreateConfigurationData(...)!  hr = " << hr
             << endl;
        return hr;
    }

#endif

#if 0 // FeatureType is not overload for voiceTransm
	//===============================================================================================
	//
	// -6- Gets Feature Type Information for BackUp / StartUp management
	//
	//===============================================================================================

	CATIInputDescription *pInputDescriptionOnTemplateFeature = NULL;
	hr = ospObjectOnTemplateFeature->QueryInterface(IID_CATIInputDescription, (void **)&pInputDescriptionOnTemplateFeature);
	if (FAILED(hr))
	{
		cout << ERROR_TITLE_CreateTemplateFeature << " QueryInterface(IID_CATIInputDescription)!  hr = " << hr << endl;
		return hr;
	}

	CATIInputDescription::FeatureType Feature_type = CATIInputDescription::FeatureType_Unset;

	hr = pInputDescriptionOnTemplateFeature->GetFeatureType(Feature_type);
	KTCRelease(pInputDescriptionOnTemplateFeature); //Release
	if (FAILED(hr))
	{
		cout << ERROR_TITLE_CreateTemplateFeature << " GetFeatureType(...)!  hr = " << hr << endl;
		return hr;
	}

	hr = CATMmrFeatureAttributes::SetFeatureType(ospObjectOnTemplateFeature, Feature_type);
	KTCRelease(pInputDescriptionOnTemplateFeature); //Release
	if (FAILED(hr))
	{
		cout << ERROR_TITLE_CreateTemplateFeature << " SetFeatureType(...)!  hr = " << hr << endl;
		return hr;
	}
#endif

    //===============================================================================================
    //
    // -7- Sets default values for the attributes of the instance
    //
    //===============================================================================================

    pITemplateFeature->SetParams(ioParam); // Set default value

    // initial software version
    pITemplateFeature->SetVersion(PNXTemplateFeatureParam::GetSoftwareVersion());

    KTCRelease(pITemplateFeature);
    return S_OK;
}
