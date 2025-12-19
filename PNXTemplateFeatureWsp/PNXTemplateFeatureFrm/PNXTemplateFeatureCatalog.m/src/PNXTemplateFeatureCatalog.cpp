/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureCatalog.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 */

//===============================================================================================
//
//  Abstract:
//  ---------
//
//  Batch program which generates a catalog for a new mechanical feature : Sound Hole.
//
//  Illustrates:
//     o -1- Creating a path to the catalog.
//     o -2- Creating the catalog.
//     o -3- Adding a client identification to the catalog.
//     o -4- Creating the new Sound Hole startup in the catalog.
//     o -5- Adding attributes to this startup.
//     o -6- Saving the catalog.
//
//===============================================================================================
//
//  Usage:
//  ------
//
//  Type:
//     o PNXTemplateFeatureCatalog <directory name>
//
//  Example under Windows NT :
//     o PNXTemplateFeatureCatalog E:\MyWsp\PNXTemplateFeatureFrm\CNext\resources\graphic
//
//  NB : to be found at run-time, catalog must be in a resources\graphic directory.
//
//===============================================================================================
// fit for high version catia catalog
#ifdef CATIAV5R25
// do not do anything at high level
#else
// MechanicalModeler Framework
#include "CATMfDefs.h"           // needed to define type MfGeom3D

// ObjectModelerBase Framework
#include "CATDocument.h"         // needed to retrieve and then save the document ( not L1 )
#include "CATDocumentServices.h" // needed to save the catalog
#include "CATSession.h"
#include "CATSessionServices.h"        // needed to manage session
#include "LifeCycleObject.h"           // needed to remove the catalog from the session

// ObjectSpecsModeler Framework
#include "CATCatalogFactoryServices.h" // needed to create a catalog
#include "CATICatalog.h"               // needed to manage catalogs
#include "CATISpecAttribute.h"         // needed to add attributes to the Sound Hole startup
#include "CATISpecObject.h"            // needed to manage features such as the Sound Hole startup
#include "CATOsmSUFactory.h"           // needed to create the Sound Hole startup

// System Framework
#include "CATBoolean.h"
#include "CATLib.h"           // needed to create the path to the catalog file
#include "CATUnicodeString.h" // needed to give the catalog name

#endif // end high catia version

// Others
#include "CATIContainer.h"
#include "iostream.h" // needed for cout traces

// local Framework
#include "KTCAutoCatalogParam.h" // inlie class,header only
#include <vector>                // list

int main(int argc, char* argv[]) {

#if defined CATIAV5R25 // high catia version
    // do not do anything at high level

    cout << KT_BLANK4 << "{NG}. Do not do anything at high level after CATIAV5R24." << endl
         << KT_BLANK4 << " Please create and update catalog at version befor CATIAV5R25 " << endl;

    return 1;
#else  // low catia version
    //===============================================================================================
    //
    // -1- Creating a path to the catalog.
    //
    //  o  "main" first argument is directory path : to use your catalog, it should be
    //     located under resources\graphic directory.
    //  o  Catalog file name is set to PNXTemplateFeatureFeature.
    //
    //     CATMakePath of CATLib.h creates an os dependant path.
    //
    //===============================================================================================

    cout << "-1- Creating a path to the catalog." << endl << flush;

    if (argc < 2) {
        cout << "    ERROR  : no directory path given." << endl;
        return 0;
    }

    const char* pDirName  = argv[ 1 ];
    const char* pFileName = "PNXTemplateFeatureFeature.CATfct"; // argv[2];
    char        StorageName[ 200 ];
    // cout << "argv[0]:" <<argv[0]<< endl << flush;
    // cout << "argv[1]:" <<argv[1]<< endl << flush;

    CATMakePath(pDirName, pFileName, StorageName);
    cout << "Catalog whole path:" << StorageName << endl << flush;

    //===============================================================================================
    // Creating a session.
    //===============================================================================================

    cout << "    Creating a session." << endl << flush;

    char*       pSessionName = "CAA2_Sample_Session";
    CATSession* pSession     = NULL;

    HRESULT hr = Create_Session(pSessionName, pSession);

    if (SUCCEEDED(hr))
        cout << "    Session creation OK." << endl << flush;
    else {
        cout << "    ERROR in creating the session." << endl << flush;
        return 1;
    }

    //===============================================================================================
    //
    // -2- Creating the catalog.
    //
    //     The ".CATfct" suffix is automatically added by CreateCatalog.
    //
    //===============================================================================================
    CATUnicodeString ClientId = "PNXTemplateFeatureID";

    CATUnicodeString TemplateFeatureCatalogStorageName = StorageName;
    CATICatalog*     piTemplateFeatureCatalog          = NULL;

    // try to open first

    //===============================================================================================
    //
    // -1- Do NOT Retrieves a CATIContainer interface pointer on this (CATPrtCont)
    //
    //===============================================================================================

    //===============================================================================================
    //
    // -2- Opens the Sound Hole catalog
    //
    //===============================================================================================

    CATUnicodeString StorageName1 = StorageName;
    hr = ::UpgradeCatalog(&TemplateFeatureCatalogStorageName, &piTemplateFeatureCatalog, &ClientId);
    if (SUCCEEDED(hr)) {
        cout << "-2- The catalog exist. Opened OK." << endl << flush;
    }
    else {
        cout << "-2- Catalog not exist ,Creating the catalog." << endl << flush;
        hr = ::CreateCatalog(&TemplateFeatureCatalogStorageName, &piTemplateFeatureCatalog);

        if (SUCCEEDED(hr))
            cout << "    Sound Hole Catalog created OK." << endl << flush;
        else {
            cout << "    ERROR in creating Sound Hole Catalog." << endl << flush;
            return 1;
        }

        //===============================================================================================
        //
        // -3- Adding a client identification to the catalog.
        //
        //     This is a mandatory step.
        //
        //===============================================================================================

        cout << "-3- Adding a client identification to the catalog." << endl << flush;

        hr = piTemplateFeatureCatalog->SetClientId(&ClientId);

        if (SUCCEEDED(hr))
            cout << "    Client Id set OK." << endl << flush;
        else {
            cout << "    ERROR in setting Client Id." << endl << flush;
            return 1;
        }
    }

    //===============================================================================================
    //
    // -3- Retrieves Sound Hole's startup
    //
    //===============================================================================================

    CATBaseUnknown*  pTemplateFeatureStartup        = NULL;
    CATUnicodeString StartupType                    = "PNXTemplateFeature";
    CATISpecObject*  piSpecOnTemplateFeatureStartUp = NULL;

    hr = piTemplateFeatureCatalog->RetrieveSU(&pTemplateFeatureStartup, &StartupType,
                                              "CATISpecObject");
    if (SUCCEEDED(hr)) {

        hr = pTemplateFeatureStartup->QueryInterface(IID_CATISpecObject,
                                                     (void**)&piSpecOnTemplateFeatureStartUp);
        pTemplateFeatureStartup->Release();
        pTemplateFeatureStartup = NULL;
    }
    // check
    if (NULL == piSpecOnTemplateFeatureStartUp) {

        //===============================================================================================
        //
        // -4- Creating the new Sound Hole startup in the catalog.
        //
        //     A Sound Hole is a kind of MfGeom3D, its StartUp derives from MfGeom3D's Startup.
        //     The generic factory is used to create a new Sound Hole
        //     StartUp deriving from MfGeom3D.
        //
        //===============================================================================================

        cout << "-4- Creating the new Sound Hole startup in the catalog." << endl << flush;

        CATUnicodeString TemplateFeatureStartUpType = "PNXTemplateFeature";
        CATUnicodeString CatalogName                = "CATHybridShape";
        CATUnicodeString SuperTypeName              = "GSMGeom";
        CATBoolean       publicSU                   = TRUE;
        CATBoolean       derivableSU                = TRUE;

        hr = ::CATOsmSUFactory(&piSpecOnTemplateFeatureStartUp, &TemplateFeatureStartUpType,
                               piTemplateFeatureCatalog, &SuperTypeName, &CatalogName, publicSU,
                               derivableSU);

        if (SUCCEEDED(hr))
            cout << "    PNXTemplateFeature StartUp created using CATOsmSUFactory Factory OK."
                 << endl
                 << flush;
        else {
            cout << "    ERROR in creating PNXTemplateFeature StartUp using CATOsmSUFactory."
                 << endl
                 << flush;
            return 1;
        }
    }

    //===============================================================================================
    //
    //  -5- Adding attributes to this startup.
    //===============================================================================================

    cout << "-5- Adding attributes to this startup." << endl << flush;

    KTCAutoCatalogParam              item;     // new param
    std::vector<KTCAutoCatalogParam> itemList; // list of param

    // KEVIN_SYSTEM_CODE START

    // 0A;	Kt Software Version;Kevin;2025-12-17
    item.SetValue("FeatureVersion", tk_integer, sp_IN);
    itemList.push_back(item);

    // KEVIN_SYSTEM_CODE END

    // DO NOT EDIT IN THE CONTROL CODE OF "KEVIN CAA WIZARD SECTION"
    // START KEVIN CAA WIZARD SECTION PNXTemplateFeature CATALOG PARAMS

    // clang-format off
    // 2; 	My Curve; Phoenix; 2025/12/17;
    item.SetValue("MyCurve", tk_specobject, sp_IN);
    itemList.push_back(item);
    // 3; 	My Faces; Phoenix; 2025/12/17;
    item.SetTKListValue("MyFaces", tk_specobject, sp_IN);
    itemList.push_back(item);
    // 4; 	My Step; Phoenix; 2025/12/17;
    item.SetValue("MyStep", tk_specobject, sp_IN);
    itemList.push_back(item);
    // 5; 	My Calc; Phoenix; 2025/12/17;
    item.SetValue("FinishCalc", tk_boolean, sp_NEUTRAL);
    itemList.push_back(item);

    // clang-format on
    // END KEVIN CAA WIZARD SECTION PNXTemplateFeature CATALOG PARAMS

    hr = KTCAutoCatalogParam::CatalogAddAttribute(piSpecOnTemplateFeatureStartUp, itemList);
    if (FAILED(hr)) {
        cout << "    ERROR in adding params" << endl;
        return 1;
    }

    // Releasing no longer used pointer on CATISpecObject.
    //----------------------------------------------------

    piSpecOnTemplateFeatureStartUp->Release();
    piSpecOnTemplateFeatureStartUp = NULL;

    //===============================================================================================
    //
    // -6- Saving the catalog.
    //
    //===============================================================================================

    cout << "-6- Saving the catalog." << endl << flush;
    // TemplateFeatureCatalogStorageName = "E:/PNXTemplateFeatureFeature.CATfct";
    cout << TemplateFeatureCatalogStorageName << endl;
    hr = ::SaveCatalog(&piTemplateFeatureCatalog, &TemplateFeatureCatalogStorageName);

    if (FAILED(hr)) {
        cout << "    ERROR in saving Sound Hole Catalog." << endl << flush;
        return 1;
    }

    piTemplateFeatureCatalog->Release();
    piTemplateFeatureCatalog = NULL;

    // Deleting session
    //------------------

    hr = Delete_Session(pSessionName);

    if (FAILED(hr)) {
        cout << "    ERROR in deleting session." << endl << flush;
        return 1;
    }
    return 0;
#endif // end of high catia version
}
//---------------------------------------------------------
