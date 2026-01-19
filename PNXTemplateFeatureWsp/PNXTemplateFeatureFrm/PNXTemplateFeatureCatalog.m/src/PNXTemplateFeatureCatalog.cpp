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
//  Batch program which generates a catalog for a new mechanical feature : feature.
//
//  Illustrates:
//     o -1- Creating a path to the catalog.
//     o -2- Creating the catalog.
//     o -3- Adding a client identification to the catalog.
//     o -4- Creating the new feature startup in the catalog.
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
#include "CATISpecAttribute.h"         // needed to add attributes to the Phoenix Feature startup
#include "CATISpecObject.h"  // needed to manage features such as the Phoenix Feature startup
#include "CATOsmSUFactory.h" // needed to create the Phoenix Feature startup

// System Framework
#include "CATBoolean.h"
#include "CATLib.h"           // needed to create the path to the catalog file
#include "CATUnicodeString.h" // needed to give the catalog name

#endif // end high catia version

// Others
#include "CATIContainer.h"
#include "iostream.h" // needed for cout traces

// auto code
#include "KTCAutoCatalogParam.h"
#include "KTCAutoDefine.h"

// std
#include <vector> // list

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

    const char* dirName  = argv[ 1 ];
    const char* fileName = "PNXTemplateFeatureFeature.CATfct"; // argv[2];
    char        storageName[ 200 ];
    // cout << "argv[0]:" <<argv[0]<< endl << flush;
    // cout << "argv[1]:" <<argv[1]<< endl << flush;

    CATMakePath(dirName, fileName, storageName);
    cout << "Catalog whole path:" << storageName << endl << flush;

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
    const CATUnicodeString clientId           = "PNXTemplateFeatureID";
    CATUnicodeString       catalogStorageName = storageName;
    CATICatalog*           featureCatalog     = NULL;

    // try to open first

    //===============================================================================================
    //
    // -1- Do NOT Retrieves a CATIContainer interface pointer on this (CATPrtCont)
    //
    //===============================================================================================

    //===============================================================================================
    //
    // -2- Opens the Phoenix Feature catalog
    //
    //===============================================================================================
    hr = ::UpgradeCatalog(&catalogStorageName, &featureCatalog, &clientId);
    if (SUCCEEDED(hr)) {
        cout << "-2- The catalog exist. Opened OK." << endl << flush;
    }
    else {
        cout << "-2- Catalog not exist ,Creating the catalog." << endl << flush;
        hr = ::CreateCatalog(&catalogStorageName, &featureCatalog);

        if (SUCCEEDED(hr))
            cout << "    Phoenix Feature Catalog created OK." << endl << flush;
        else {
            cout << "    ERROR in creating Phoenix Feature Catalog." << endl << flush;
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

        hr = featureCatalog->SetClientId(&clientId);

        if (SUCCEEDED(hr))
            cout << "    Client Id set OK." << endl << flush;
        else {
            cout << "    ERROR in setting Client Id." << endl << flush;
            return 1;
        }
    }

    //===============================================================================================
    //
    // -3- Retrieves Phoenix Feature's startup
    //
    //===============================================================================================

    CATBaseUnknown*  startupUnknown = NULL;
    CATUnicodeString startupType    = "PNXTemplateFeature";
    CATISpecObject*  startupObject  = NULL;

    hr = featureCatalog->RetrieveSU(&startupUnknown, &startupType, "CATISpecObject");
    if (SUCCEEDED(hr)) {

        hr = startupUnknown->QueryInterface(IID_CATISpecObject, (void**)&startupObject);
        KTCRelease(startupUnknown); // 手动释放
    }
    // check
    if (NULL == startupObject) {

        //===============================================================================================
        //
        // -4- Creating the new Phoenix Feature startup in the catalog.
        //
        //     A feature is a kind of MfGeom3D, its StartUp derives from MfGeom3D's Startup.
        //     The generic factory is used to create a new feature
        //     StartUp deriving from MfGeom3D.
        //
        //===============================================================================================

        cout << "-4- Creating the new feature startup in the catalog." << endl << flush;

        CATUnicodeString featureTypeName = "PNXTemplateFeature";
        CATUnicodeString catalogName     = "CATHybridShape";
        CATUnicodeString superTypeName   = "GSMGeom";
        CATBoolean       publicSU        = TRUE;
        CATBoolean       derivableSU     = TRUE;

        hr = ::CATOsmSUFactory(&startupObject, &featureTypeName, featureCatalog, &superTypeName,
                               &catalogName, publicSU, derivableSU);

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

    hr = KTCAutoCatalogParam::add_Attributes(startupObject, itemList);
    if (FAILED(hr)) {
        cout << "    ERROR in adding params" << endl;
        return 1;
    }

    // Releasing no longer used pointer on CATISpecObject.
    //----------------------------------------------------

    KTCRelease(startupObject); // 手动释放

    //===============================================================================================
    //
    // -6- Saving the catalog.
    //
    //===============================================================================================

    cout << "-6- Saving the catalog." << endl << flush;
    // catalogStorageName = "E:/PNXTemplateFeatureFeature.CATfct";
    cout << catalogStorageName << endl;
    hr = ::SaveCatalog(&featureCatalog, &catalogStorageName);

    if (FAILED(hr)) {
        cout << "    ERROR in saving feature Catalog." << endl << flush;
        return 1;
    }

KTCRelease(    featureCatalog ); // 手动释放

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
