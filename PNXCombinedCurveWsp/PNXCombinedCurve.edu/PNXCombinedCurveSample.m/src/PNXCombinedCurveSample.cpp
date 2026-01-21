// COPYRIGHT DASSAULT SYSTEMES 2000
//============================================================================================
// Mission         : Creates, Queries and Builds a Combined Curve
//
// Type            : Batch program
// Inputs          : none
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
//
// Illustrates     : o Creating a Combined Curve
//                   o Querying a Combined Curve
//                   o Building a Combined Curve
//
//==========================================================================
// How to execute :
//
//   PNXCombinedCurveSample FileName
//
//   where FileName is the name (with or without CATPart extension) of the Part document created
//         and saved during this use case.
//
//
// Return code :
//   0 successful execution
//   else execution failed
//
//============================================================================================

// compiler includes
#include "CATIDescendants.h" // Added by FRG on 07/30/2002
#include <iostream.h>

// PNXCombinedCurve.edu
#include "PNXICombinedCurve.h"
#include "PNXICombinedCurveFactory.h"

// System includes
#include "CATLib.h"
#include "CATUnicodeString.h"

#include "CATBaseUnknown.h"

#include "CATIGSMFactory.h"
#include "CATIGSMSpline.h"

// ObjectModeler includes
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATInit.h"
#include "CATSession.h"
#include "CATSessionServices.h"

// ObjectSpecsModeler includes
#include "CATISpecObject.h"

// MechanicalModeler includes
#include "CATIMechanicalRootFactory.h"
#include "CATIPartRequest.h"
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

int main(int    iArgc, // Number of arguments (0)
         char** iArgv) {
    if (2 != iArgc) {
        cout << endl;
        cout << "PNXCombinedCurveSample FileName " << endl;
        cout << "where FileName is the complete name (with or without CATPart extension)";
        cout << " of the Part created by this sample" << endl;
        cout << endl;
        return 1;
    }

    cout << "The PNXCombinedCurveSample use case begins" << endl;

    // Creates a session
    char*       pSessionName = "SampleSession";
    CATSession* pSession     = 0;
    HRESULT     rc           = SUCCEEDED(Create_Session(pSessionName, pSession));
    if (FAILED(rc)) {
        cout << "ERROR in creating the session" << endl;
        return 1;
    }

    // Creates a CATPart
    CATDocument* pDoc = NULL;
    CATDocumentServices::New("CATPart", pDoc);
    if (NULL == pDoc) {
        cout << "ERROR in creating the part" << endl;
        return 2;
    }

    // Retrieves a pointer on the CATInit interface
    CATInit* piInitOnDoc = NULL;
    rc                   = pDoc->QueryInterface(IID_CATInit, (void**)&piInitOnDoc);

    if (FAILED(rc)) {
        cout << "ERROR in initializing the part" << endl;
        return 3;
    }

    // Retrieves the root container
    CATIPrtContainer* piPrtCont =
        (CATIPrtContainer*)piInitOnDoc->GetRootContainer("CATIPrtContainer");
    if (NULL == piPrtCont) {
        cout << "ERROR in retrieving the root container" << endl;
        return 4;
    }

    piInitOnDoc->Release();
    piInitOnDoc = NULL;

    // Retrieves the MechanicalPart feature
    CATISpecObject_var spSpecOnPart(piPrtCont->GetPart());
    if (NULL_var == spSpecOnPart) {
        cout << "ERROR in retrieving the part feature" << endl;
        return 5;
    }

    // Retrieves the GSMTool factory
    CATIMechanicalRootFactory_var RootFactory(piPrtCont);
    if (NULL_var == RootFactory) {
        cout << "ERROR in creating the mechanical root factory" << endl;
        return 6;
    }

    // Retrieves the main MechanicalTool feature
    CATIPartRequest_var spPartRequest = spSpecOnPart;
    if (NULL_var == spPartRequest) {
        cout << "ERROR in querying CATIPartRequest on part " << endl;
        return 7;
    }

    CATBaseUnknown_var spBUOnMainTool;
    rc = spPartRequest->GetMainBody("", spBUOnMainTool);

    if (FAILED(rc) || (NULL_var == spBUOnMainTool)) {
        cout << "ERROR in retrieving main tool" << endl;
        return 8;
    }

    CATISpecObject_var spSpecOnMainTool = spBUOnMainTool;
    if (NULL_var == spSpecOnMainTool) {
        cout << "ERROR in retrieving main tool" << endl;
        return 8;
    }

    // Creates a GSM tool
    CATUnicodeString   GSMToolName = "GSMToolForCombinedCurve";
    CATISpecObject_var spSpecOnGSMTool;
    rc = RootFactory->CreateGeometricalSet(GSMToolName, spSpecOnMainTool, spSpecOnGSMTool);
    if (SUCCEEDED(rc) && (NULL_var == spSpecOnGSMTool)) {
        cout << "ERROR in creating the GSM tool" << endl;
        return 9;
    }
    cout << "   A Geometrical Set has been created" << endl;

    // query CATIDescendants interface to aggregate wireframe features
    CATIDescendants* pDescendantsOnGSMTool = NULL;
    rc = spSpecOnGSMTool->QueryInterface(IID_CATIDescendants, (void**)&pDescendantsOnGSMTool);

    if (FAILED(rc)) {
        cout << "ERROR in querying CATIDescendants on GSM tool" << endl;
        return 10;
    }

    // Instantiates the wireframe factory
    CATIGSMFactory* piGSMFactOnPrtCont = NULL;
    rc = piPrtCont->QueryInterface(IID_CATIGSMFactory, (void**)&piGSMFactOnPrtCont);
    if (FAILED(rc)) {
        cout << "ERROR in instantiating the wireframe factory" << endl;
        return 11;
    }

    // Creates first spline ( first input curve of the Combined Curve )
    double iPrtSpline1Point1[ 3 ], iPrtSpline1Point2[ 3 ], iPrtSpline1Point3[ 3 ];
    iPrtSpline1Point1[ 0 ] = 20.;
    iPrtSpline1Point2[ 0 ] = 5.;
    iPrtSpline1Point3[ 0 ] = -20.;
    iPrtSpline1Point1[ 1 ] = 5.;
    iPrtSpline1Point2[ 1 ] = 30.;
    iPrtSpline1Point3[ 1 ] = 5.;
    iPrtSpline1Point1[ 2 ] = 20.;
    iPrtSpline1Point2[ 2 ] = 30.;
    iPrtSpline1Point3[ 2 ] = 20.;

    cout << "   Creates three Points for the first spline" << endl;
    // @CSC-Filter UNER
    CATISpecObject_var Spline1Point1 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline1Point1);
    pDescendantsOnGSMTool->Append(Spline1Point1);

    // @CSC-Filter UNER
    CATISpecObject_var Spline1Point2 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline1Point2);
    pDescendantsOnGSMTool->Append(Spline1Point2);

    // @CSC-Filter UNER
    CATISpecObject_var Spline1Point3 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline1Point3);
    pDescendantsOnGSMTool->Append(Spline1Point3);

    CATLISTV(CATISpecObject_var) ListOfPointsSpline1;
    ListOfPointsSpline1.Append(Spline1Point1);
    ListOfPointsSpline1.Append(Spline1Point2);
    ListOfPointsSpline1.Append(Spline1Point3);

    cout << "   Creates a first spline " << endl;
    CATISpecObject_var Spline1 = piGSMFactOnPrtCont->CreateSplinePoints(ListOfPointsSpline1);
    pDescendantsOnGSMTool->Append(Spline1);

    // Creates second spline ( second input curve of the Combined Curve )
    double iPrtSpline2Point1[ 3 ], iPrtSpline2Point2[ 3 ], iPrtSpline2Point3[ 3 ],
        iPrtSpline2Point4[ 3 ];
    iPrtSpline2Point1[ 0 ] = -40.;
    iPrtSpline2Point2[ 0 ] = -10.;
    iPrtSpline2Point3[ 0 ] = 25.;
    iPrtSpline2Point4[ 0 ] = 50.;
    iPrtSpline2Point1[ 1 ] = 0.;
    iPrtSpline2Point2[ 1 ] = 0.;
    iPrtSpline2Point3[ 1 ] = 0.;
    iPrtSpline2Point4[ 1 ] = 0.;
    iPrtSpline2Point1[ 2 ] = 120.;
    iPrtSpline2Point2[ 2 ] = 80.;
    iPrtSpline2Point3[ 2 ] = 100.;
    iPrtSpline2Point4[ 2 ] = 50.;

    cout << "   Creates a four points for the second spline" << endl;
    // @CSC-Filter UNER
    CATISpecObject_var Spline2Point1 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline2Point1);
    pDescendantsOnGSMTool->Append(Spline2Point1);

    // @CSC-Filter UNER
    CATISpecObject_var Spline2Point2 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline2Point2);
    pDescendantsOnGSMTool->Append(Spline2Point2);

    // @CSC-Filter UNER
    CATISpecObject_var Spline2Point3 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline2Point3);
    pDescendantsOnGSMTool->Append(Spline2Point3);

    // @CSC-Filter UNER
    CATISpecObject_var Spline2Point4 = piGSMFactOnPrtCont->CreatePoint(iPrtSpline2Point4);
    pDescendantsOnGSMTool->Append(Spline2Point4);

    CATLISTV(CATISpecObject_var) ListOfPointsSpline2;
    ListOfPointsSpline2.Append(Spline2Point1);
    ListOfPointsSpline2.Append(Spline2Point2);
    ListOfPointsSpline2.Append(Spline2Point3);
    ListOfPointsSpline2.Append(Spline2Point4);

    cout << "   Creates a second spline " << endl;
    CATISpecObject_var Spline2 = piGSMFactOnPrtCont->CreateSplinePoints(ListOfPointsSpline2);
    pDescendantsOnGSMTool->Append(Spline2);

    // Create first and second line ( first and second input directions of the Combined Curve )

    double iPtrOriginePoint[ 3 ];
    iPtrOriginePoint[ 0 ] = 0.;
    iPtrOriginePoint[ 1 ] = 0.;
    iPtrOriginePoint[ 2 ] = 0.;

    double YVector[ 3 ];
    YVector[ 0 ] = 0.;
    YVector[ 1 ] = 1.;
    YVector[ 2 ] = 0.;

    double ZVector[ 3 ];
    ZVector[ 0 ] = 0.;
    ZVector[ 1 ] = 0.;
    ZVector[ 2 ] = 1.;

    cout << "   Creates two lines" << endl;
    // @CSC-Filter UNER
    CATISpecObject_var Line1 = piGSMFactOnPrtCont->CreateLine(iPtrOriginePoint, ZVector);
    pDescendantsOnGSMTool->Append(Line1);

    // @CSC-Filter UNER
    CATISpecObject_var Line2 = piGSMFactOnPrtCont->CreateLine(iPtrOriginePoint, YVector);
    pDescendantsOnGSMTool->Append(Line2);

    // creates Combined Curve factory- piPrtCont is the container of specifications
    PNXICombinedCurveFactory* factory = NULL;
    rc = piPrtCont->QueryInterface(IID_PNXICombinedCurveFactory, (void**)&factory);
    if (FAILED(rc)) {
        cout << "ERROR in querying PNXICombinedCurveFactory interface on CATPrtCont" << endl;
        return 12;
    }

    // The root container is unuseless
    piPrtCont->Release(), piPrtCont = NULL;

    // Updates the MechanicalPart
    int PartUpdate = spSpecOnPart->Update();
    if (PartUpdate == 0)
        cout << "   Part update OK " << endl;
    else
        cout << "   Part update KO " << endl;

    // Creates Combined Curve instance
    CATISpecObject* pSpecOnCombinedCurve = NULL;

    cout << "   Creates the combined curve" << endl;
    rc = factory->CreateCombinedCurve(Spline1, Line1, &pSpecOnCombinedCurve);

    pDescendantsOnGSMTool->Append(pSpecOnCombinedCurve);

    factory->Release(), factory = NULL;

    if (FAILED(rc)) {
        cout << "ERROR in creating Combined Curve " << endl;
        return 13;
    }

    // Udpates the Combined Curve
    int CombinedCurveUpdate = pSpecOnCombinedCurve->Update();
    if (CombinedCurveUpdate == 0)
        cout << "   Combined Curve instance's update OK " << endl;
    else
        cout << "   Combined Curve instance's update KO " << endl;

    // Queries PNXICombinedCurve interface on Combined Curve instance
    PNXICombinedCurve_var feature;
    rc = pSpecOnCombinedCurve->QueryInterface(IID_PNXICombinedCurve, (void**)&feature);
    if (FAILED(rc)) {
        cout << "ERROR in querying PNXICombinedCurve on Combined Curve " << endl;
        return 14;
    }
    pSpecOnCombinedCurve->Release(), pSpecOnCombinedCurve = NULL;

    // Retrieves first input curve
    CATISpecObject_var spFirstPoint = feature->GetFirstPoint();
    if (!spFirstPoint) {
        cout << "ERROR in retrieving FirstPoint" << endl;
        return 15;
    }

    // Retrieves first input direction
    CATISpecObject_var spMainDir = feature->GetMainDir();
    if (!spMainDir) {
        cout << "ERROR in retrieving input MainDir" << endl;
        return 16;
    }

    // displays names of Combined Curve's input curves and directions
    cout << endl;
    cout << "   CombinedCurve instance's inputs : " << endl;
    cout << "     FirstPoint     : " << spFirstPoint->GetDisplayName().ConvertToChar() << endl;
    cout << "     MainDir : " << spMainDir->GetDisplayName().ConvertToChar() << endl;
    cout << endl;

    pDescendantsOnGSMTool->Release(), pDescendantsOnGSMTool = NULL;
    piGSMFactOnPrtCont->Release(), piGSMFactOnPrtCont       = NULL;

    // Saves the Part document

    // @CSC-Filter UNER
    rc = CATDocumentServices::SaveAs(*pDoc, iArgv[ 1 ]);
    if (S_OK == rc) {
        cout << "   The " << iArgv[ 1 ] << " document ";
        cout << " has been saved" << endl;
        cout << endl;
    }
    else {
        cout << "ERROR in saving document " << iArgv[ 1 ] << endl;
        return 1;
    }

    // Closes the document
    rc = CATDocumentServices::Remove(*pDoc);
    if (FAILED(rc)) {
        cout << " ERROR in the document closing" << endl;
        return 1;
    }
    pDoc = NULL;

    // deletes session
    rc = ::Delete_Session(pSessionName);
    if (FAILED(rc)) {
        cout << "ERROR in deleting session" << endl << flush;
        return 19;
    }

    cout << "The PNXCombinedCurveSample use case is ended" << endl;

    return 0;
}
