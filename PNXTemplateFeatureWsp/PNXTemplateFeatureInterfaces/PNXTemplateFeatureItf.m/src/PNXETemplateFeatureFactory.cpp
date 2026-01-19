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
HRESULT PNXETemplateFeatureFactory::create(PNXTemplateFeatureParam* parameter,
                                           CATISpecObject_var&      ospFeature) {
    ospFeature = NULL_var; // set NULL_var first
    if (NULL == parameter) return E_INVALIDARG;

    PNXITemplateFeature* feature            = NULL; // your feature
    HRESULT              hr                 = S_OK;
    KtString             msg                = "";
    CATUnicodeString     catalogStorageName = "PNXTemplateFeatureFeature";
    CATUnicodeString     clientId           = "PNXTemplateFeatureID";
    CATUnicodeString     partnerID          = "PNXTemplateFeature"; // for V25 or later
    CATUnicodeString     startupType        = "PNXTemplateFeature"; // for V24 or erlier

    //===============================================================================================
    //
    // -1- Retrieves a CATICkeParmFactory interface on this.
    //
    //===============================================================================================
    CATICkeParmFactory* parmFactory = NULL;
    hr = this->QueryInterface(IID_CATICkeParmFactory, (void**)&parmFactory); // query
    if (FAILED(hr) || !parmFactory)
        KTC_MESSAGE_CODE_RETURN_HR("Query CATICkeParmFactory failed.", hr, 100105);

    // 根据版本来写代码
#if defined CATIAV5R25
    //===============================
    // TODO 验证 Catia V25和后面的版本
    //===============================

    // -1- Opening the Catalog
    CATIContainer_var container(this);
    if (NULL_var == container)
        KTC_MESSAGE_CODE_RETURN_HR("CATIContainer_var  is NULL_var! ", E_POINTER, 100106);

    CATUnicodeString catalogStorageName = "PNXTemplateFeatureFeature";
    CATUnicodeString partnerID          = "PNXTemplateFeature";
    CATFmCredentials myCredentials;
    hr = myCredentials.RegisterAsApplicationBasedOn(CATFmFeatureModelerID, partnerID);
    if (SUCCEEDED(hr)) {
        hr = myCredentials.RegisterAsCatalogOwner(catalogStorageName, clientId);
    }
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("Register catalog failed.", hr, 100107);

    // 2. Get Container Facade
    CATFmContainerFacade myContainerFacade(myCredentials, this);

    // 3. Get StartUp Facade
    CATUnicodeString   startupType = "`PNXTemplateFeature`@`PNXTemplateFeatureFeature.CATfct`";
    CATFmStartUpFacade myStartUpFacade(myCredentials, startupType);

    // 4. Instance StartUp
    CATFmFeatureFacade myFeatureFacade;
    hr = myStartUpFacade.InstantiateIn(myContainerFacade, myFeatureFacade);
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("InstantiateIn() failed.", hr, 100108);

    // get PNXITemplateFeature pointer
    hr = myFeatureFacade.QueryInterfaceOnFeature(IID_PNXITemplateFeature, (void**)&feature);
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("Query PNXITemplateFeature failed.", hr, 100109);

    ospFeature = feature; // convert to CATISpecObject_var
    if (NULL_var == ospFeature)
        KTC_MESSAGE_CODE_RETURN_HR("Get CATISpecObject_var failed.", E_POINTER, 100110);

#else
    //===============================
    // Catia V24 和前面的版本
    //===============================

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
    CATISpecObject_var startupObject = NULL_var;
    CATUnicodeString   storageName   = catalogStorageName + ".CATfct";

    // Initial a CATOsmSUHandler to access the catalog
    // Provides access to a startup stored in catalogs.
    CATOsmSUHandler addOpSUHandler(startupType, clientId, storageName);

    //===============================================================================================
    //
    // -3- Retrieves startup
    //
    //===============================================================================================
    hr = addOpSUHandler.RetrieveSU(startupObject);
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("RetrieveSU(...) failed.", hr, 100111);

    //===============================================================================================
    //
    // -4- Creates a Object instance to ospFeature
    //
    //===============================================================================================
    CATIContainer_var spContainer = this; // get current factory containers
    // instanciate by CATOsmSUHandler
    hr = addOpSUHandler.Instanciate(ospFeature, spContainer, NULL_string);
    if (FAILED(hr) || !ospFeature)
        KTC_MESSAGE_CODE_RETURN_HR("Instanciate(...) failed.", hr, 100112);

    hr = ospFeature->QueryInterface(IID_PNXITemplateFeature, (void**)&feature);
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("Query PNXITemplateFeature failed.", hr, 100113);

#endif // end of high version catia catalog

    // used for auto append param on tree. kevin.
    // spListParmName，ListOnTree，spListParm等变量在自动代码里面使用，不能改名
    KtListV<CATUnicodeString> spListParmName; // 参数显示名
    KtListV<int>              ListOnTree;     // 是否放到树上
    KtListV<CATICkeParm_var>  spListParm;     // parm 列表

#if 0 // 自动代码
    // 4.1 On Tree
    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    //  START KEVIN CAA WIZARD SECTION PNXTemplateFeature FACTRY ON TREE

    // clang-format off

	// 4, MyStep,
	spListParmName.Append("MyStep");
	spListParm.Append(parmFactory->CreateReal("My Step", parameter->MyStep));
	ListOnTree.Append(true);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature FACTRY ON TREE

#else // 手动
    // KEVIN MANUAL CODE START
    // 前面的自动代码如果不满意，这里写手动代码，但是要把前面的代码屏蔽

    // MyStep,
    spListParmName.Append("MyStep");
    spListParm.Append(parmFactory->CreateReal("Step", parameter->MyStep));
    ListOnTree.Append(1);

    // KEVIN MANUAL CODE END
#endif

    // 如果有结构树的参数
    if (spListParm.size() > 0) {
        CATISpecAttrAccess* attrAccess = NULL; //
        hr = ospFeature->QueryInterface(IID_CATISpecAttrAccess, (void**)&attrAccess);
        if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("Query CATISpecAttrAccess failed", hr, 100114);

        CATISpecAttrKey* attrKey = NULL; // Key

        // put on tree initial
        for (size_t i = 0; i < spListParm.size(); i++) {
            // (1) 得到attrkey
            attrKey = attrAccess->GetAttrKey(spListParmName[ i ].ConvertToChar());
            if (!attrKey) {
                (msg = " - GetKey Error ") << spListParmName[ i ].ConvertToChar();
                cout << msg.str() << endl;
                parameter->append_message(msg);
                continue;
            }

            // (2) start=====================
            // (2.1)您的自定义代码写到这里
            //=====================

            // 或者(2.2) set all read only
            spListParm[ i ]->SetUserAccess(CATICkeParm::ReadOnly);

            // (2) end=====================

            // (3) set to access
            attrAccess->SetSpecObject(attrKey, spListParm[ i ]);

            KTCRelease(attrKey); // 手动释放
        }
        KTCRelease(attrAccess); // 手动释放

        // Show On tree
        CATIDescendants* pIDescendants = NULL; // des
        hr = ospFeature->QueryInterface(IID_CATIDescendants, (void**)&pIDescendants);
        if (FAILED(hr))
            KTC_MESSAGE_CODE_RETURN_HR("QueryInterface(IID_CATIDescendants) faild ", hr, 100115);

        for (size_t i = 0; i < spListParm.size(); i++) {
            if (!spListParm[ i ] || !ListOnTree[ i ]) continue; // not on  tree

            pIDescendants->Append((spListParm[ i ])); // on tree
        }
        KTCRelease(pIDescendants); // 手动释放
    }
    //===============================================================================================
    //
    // -5- Subscribes to repository for Configuration Data Storage
    //
    //===============================================================================================

    hr = CATMmrAlgoConfigServices::CreateConfigurationData(ospFeature);
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("CreateConfigurationData(...) failed.", hr, 100116);

    // FeatureType is not overload for voiceTransm
    //===============================================================================================
    //
    // -6- Gets Feature Type Information for BackUp / StartUp management
    //
    //===============================================================================================

    CATIInputDescription*             inputDescription = NULL;
    CATIInputDescription::FeatureType featureType      = CATIInputDescription::FeatureType_Unset;

    // 检出 InputDescription
    hr = ospFeature->QueryInterface(IID_CATIInputDescription, (void**)&inputDescription);
    if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("Query CATIInputDescription failed", hr, 100117);

    // TODO
    // 检出 FeatureType
    // hr = inputDescription->GetFeatureType(featureType);
    // KTCRelease(inputDescription); // 手动释放
    // if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("GetFeatureType(...) failed.", hr, 100118);

    // // 设置 FeatureType
    // hr = CATMmrFeatureAttributes::SetFeatureType(ospFeature, featureType);
    // if (FAILED(hr)) KTC_MESSAGE_CODE_RETURN_HR("SetFeatureType(...) failed.", hr, 100119);

    //===============================================================================================
    //
    // -7- Sets default values for the attributes of the instance
    //
    //===============================================================================================
    feature->SetParams(*parameter); // Set default value

    // initial software version
    feature->SetVersion(PNXTemplateFeatureParam::GetSoftwareVersion());

    KTCRelease(feature); // 手动释放
    return S_OK;
}
