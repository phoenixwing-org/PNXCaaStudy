// COPYRIGHT DASSAULT SYSTEMES 2000
//===============================================================================================
// PNXCombinedCurveCatalogCreate
//===============================================================================================
//
//  Abstract:
//  ---------
//
//  Batch program which generates a catalog for a new mechanical feature : Combined Curve.
//
//  Illustrates:
//     o -1- Creating a path to the catalog.
//     o -2- Creating the catalog.
//     o -3- Adding a client identification to the catalog.
//     o -4- Creating the new Combined Curve startup in the catalog.
//     o -5- Adding attributes to this startup.
//     o -6- Saving the catalog.
//
//===============================================================================================
//
//  Usage:
//  ------
//
//  Type:
//     o PNXCombinedCurveCatalogCreate <directory name>
//
//  Example under Windows NT :
//     o PNXCombinedCurveCatalogCreate E:\CAA2WS\PNXCombinedCurve.edu\CNext\resources\graphic
//
//  NB : to be found at run-time, catalog must be in a resources\graphic directory.
//
//===============================================================================================

// MechanicalModeler Framework
#include "CATMfDefs.h" // needed to define type MfGeom3D

// ObjectModelerBase Framework
#include "CATDocument.h"         // needed to retrieve and then save the document ( not L1 )
#include "CATDocumentServices.h" // needed to save the catalog
#include "CATSession.h"
#include "CATSessionServices.h" // needed to manage session
#include "LifeCycleObject.h"    // needed to remove the catalog from the session

// ObjectSpecsModeler Framework
#include "CATCatalogFactoryServices.h" // needed to create a catalog
#include "CATICatalog.h"               // needed to manage catalogs
#include "CATISpecAttribute.h"         // needed to add attributes to the Combined Curve startup
#include "CATISpecObject.h"  // needed to manage features such as the Combined Curve startup
#include "CATOsmSUFactory.h" // needed to create the Combined Curve startup

// System Framework
#include "CATBoolean.h"
#include "CATLib.h"           // needed to create the path to the catalog file
#include "CATUnicodeString.h" // needed to give the catalog name

// Others
#include <iostream.h> // needed for cout traces

int main(int argc, char* argv[]) {
    //===============================================================================================
    //
    // -1- Creating a path to the catalog.
    //
    //  o  "main" first argument is directory path : to use your catalog, it should be
    //     located under resources\graphic directory.
    //  o  Catalog file name is set to PNXCombinedCurveCatalogCreate.
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
    const char* pFileName = "PNXCombinedCurveCatalogCreate.CATfct";
    char        StorageName[ 200 ];

    CATMakePath(pDirName, pFileName, StorageName);

    //===============================================================================================
    // Creating a session.
    //===============================================================================================

    cout << "    Creating a session." << endl << flush;

    char*       pSessionName = "CAA2_Sample_Session";
    CATSession* pSession     = NULL;

    HRESULT rc = Create_Session(pSessionName, pSession);

    if (SUCCEEDED(rc))
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

    cout << "-2- Creating the catalog." << endl << flush;

    CATUnicodeString CombinedCurveCatalogStorageName = StorageName;
    CATICatalog*     piCombinedCurveCatalog          = NULL;

    rc = ::CreateCatalog(&CombinedCurveCatalogStorageName, &piCombinedCurveCatalog);

    if (SUCCEEDED(rc))
        cout << "    Combined Curve Catalog created OK." << endl << flush;
    else {
        cout << "    ERROR in creating Combined Curve Catalog." << endl << flush;
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

    CATUnicodeString ClientId = "SAMPLES";

    rc = piCombinedCurveCatalog->SetClientId(&ClientId);

    if (SUCCEEDED(rc))
        cout << "    Client Id set OK." << endl << flush;
    else {
        cout << "    ERROR in setting Client Id." << endl << flush;
        return 1;
    }

    //===============================================================================================
    //
    // -4- Creating the new Combined Curve startup in the catalog.
    //
    //     A Combined Curve is a kind of MfGeom3D, its StartUp derives from MfGeom3D's Startup.
    //     The generic factory is used to create a new Combined Curve
    //     StartUp deriving from MfGeom3D.
    //
    //===============================================================================================

    cout << "-4- Creating the new Combined Curve startup in the catalog." << endl << flush;

    CATUnicodeString CombinedCurveStartUpType     = "CombinedCurve";
    CATUnicodeString CatalogName                  = "MechMod";
    CATUnicodeString SuperTypeName                = "GeometricalElement3D";
    CATBoolean       publicSU                     = FALSE;
    CATBoolean       derivableSU                  = FALSE;
    CATISpecObject*  piSpecOnCombinedCurveStartUp = NULL;

    rc = ::CATOsmSUFactory(&piSpecOnCombinedCurveStartUp, &CombinedCurveStartUpType,
                           piCombinedCurveCatalog, &SuperTypeName, &CatalogName, publicSU,
                           derivableSU);

    if (SUCCEEDED(rc))
        cout << "    CombinedCurve StartUp created using CATOsmSUFactory Factory OK." << endl
             << flush;
    else {
        cout << "    ERROR in creating CombinedCurve StartUp using CATOsmSUFactory." << endl
             << flush;
        return 1;
    }

    //===============================================================================================
    //
    //  -5- Adding attributes to this startup.
    //
    //      Here is a short description of the Combined Curve feature's startup.
    //
    //      StartUp        Attribute Name    Attribute type    Update
    //      ------------   --------------    --------------    ------------
    //      CombinedCurve   FirstPoint       tk_specobject     IN attribute
    //                      MainDir          tk_specobject     IN attribute
    //
    //
    //      If you wish to get more details about startup and attributes, please
    //      refer to CAAObjectSpecsModeler.edu use cases.
    //
    //===============================================================================================

    cout << "-5- Adding attributes to this startup." << endl << flush;

    // Adding first attribute : FirstPoint
    //---------------------------------------

    CATUnicodeString FirstPointName = "FirstPoint";

    CATISpecAttribute* piFirstPointSpecAttribute =
        piSpecOnCombinedCurveStartUp->AddAttribute(FirstPointName, tk_specobject, sp_IN);

    if (piFirstPointSpecAttribute != NULL)
        cout << "    FirstPoint attribute added OK." << endl << flush;
    else {
        cout << "    ERROR in adding FirstPoint attribute." << endl << flush;
        return 1;
    }
    piFirstPointSpecAttribute->Release();
    piFirstPointSpecAttribute = NULL;

    // Adding second attribute : MainDir
    //---------------------------------------

    CATUnicodeString MainDirName = "MainDir";

    CATISpecAttribute* piMainDirSpecAttribute =
        piSpecOnCombinedCurveStartUp->AddAttribute(MainDirName, tk_specobject, sp_IN);

    if (piMainDirSpecAttribute != NULL)
        cout << "    MainDir attribute added OK." << endl << flush;
    else {
        cout << "    ERROR in adding MainDir attribute." << endl << flush;
        return 1;
    }
    piMainDirSpecAttribute->Release();
    piMainDirSpecAttribute = NULL;

    // Releasing no longer used pointer on CATISpecObject.
    //----------------------------------------------------

    piSpecOnCombinedCurveStartUp->Release();
    piSpecOnCombinedCurveStartUp = NULL;

    //===============================================================================================
    //
    // -6- Saving the catalog.
    //
    //===============================================================================================

    cout << "-6- Saving the catalog." << endl << flush;

    rc = ::SaveCatalog(&piCombinedCurveCatalog, &CombinedCurveCatalogStorageName);

    if (FAILED(rc)) {
        cout << "    ERROR in saving Combined Curve Catalog." << endl << flush;
        return 1;
    }

    piCombinedCurveCatalog->Release();
    piCombinedCurveCatalog = NULL;

    // Deleting session
    //------------------

    rc = Delete_Session(pSessionName);

    if (FAILED(rc)) {
        cout << "    ERROR in deleting session." << endl << flush;
        return 1;
    }

    return 0;
}
