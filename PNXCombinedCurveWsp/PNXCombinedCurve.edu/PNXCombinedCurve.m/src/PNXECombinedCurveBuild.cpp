// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "PNXECombinedCurveBuild.h"

// PNXCombinedCurve.edu Framework
#include "PNXICombinedCurve.h" // To ask inputs curves and directions

// GeometricObjects Framework
#include "CATCGMJournalList.h"
#include "CATGeoFactory.h" // To extrude input curves along the input directions
#include "CATLine.h"       // To query a direction

// Mathematics Framework
#include "CATMathDef.h"
#include "CATMathDirection.h" // Direction of extrusion

// MechanicalModeler Framework
#include "CATIGeometricalElement.h"   // Needed for DeleteScope and GetBodyResult
#include "CATIMfProcReport.h"         // To manage the procedural report
#include "CATIUpdateError.h"          // To associate an error to a feature
#include "CATMfBRepDefs.h"            // Useful for the procedural report
#include "CATMfErrUpdate.h"           // To manage mechanical modeler update error
#include "CATMmrAlgoConfigServices.h" // Needed to subscribe to repository for AlgorithmConfiguration

// MecModInterfaces Framework
#include "CATIContainerOfDocument.h"  // To retrieve the geometrical factory
#include "CATIMechanicalProperties.h" //

// ObjectModelerBase Framework
#include "CATDocument.h" // To retrieve the result container
#include "CATIContainer.h"
#include "CATILinkableObject.h"      // To retrieve the result container
#include "CATLISTV_CATBaseUnknown.h" // To store the CATBody of the input elements to follow

// ObjectSpecsModeler Framework
#include "CATISpecObject.h" // To query the Combined Curve feature about its inputs

// NewTopologicalObjects Framework
#include "CATBody.h"    // The Topological result
#include "CATTopData.h" // Needed to create operators

// System Framework
#include "CATBoolean.h"
#include "CATError.h"
#include "CATListOfCATUnicodeString.h" // For the list of keys
#include "CATUnicodeString.h"

// TopologicalOperators Framework
#include "CATCreateTopIntersect.h" // Needed to intersect extruded surfaces
#include "CATHybIntersect.h"       // The result of the extruded surfaces's intersection
#include "CATHybOperator.h"
#include "CATTopPrism.h" // Needed to extrude curves

// Mathematics Framework
#include "CATSoftwareConfiguration.h" // Needed to create topological data

#include <iostream.h>

#include "CATDataType.h"

//-----------------------------------------------------------------------------

CATImplementClass(PNXECombinedCurveBuild, DataExtension, CATBaseUnknown, CombinedCurve);

//-----------------------------------------------------------------------------
#include "TIE_CATIBuild.h" // needed to tie the implementation to its interface
TIE_CATIBuild(PNXECombinedCurveBuild);

//
// To declare that CombinedCurve implements CATIBuild, insert
// the following line in the interface dictionary:
//
// CombinedCurve  CATIBuild            libPNXCombinedCurve
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
PNXECombinedCurveBuild::PNXECombinedCurveBuild()
    : CATBaseUnknown() {
}

//-----------------------------------------------------------------------------
PNXECombinedCurveBuild::~PNXECombinedCurveBuild() {
}

//-----------------------------------------------------------------------------
HRESULT PNXECombinedCurveBuild::Build() {
    cout << " PNXECombinedCurveBuild::Build" << endl;

    HRESULT rc = E_FAIL;

    //  //========================================================================================
    //  //
    //  // The build method takes place as follows :
    //  //
    //  // CATTry
    //  //   o -0- Checking the deactivation status
    //  //   o -1- Cleaning last update error
    //  //   o -2- Retrieving data for the procedural report
    //  //   o  -2-1 Retrieving the two input curves and the two input directions
    //  //   o  -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
    //  //   o  -2-3 Retrieving the two bodies corresponding to the two input curves
    //  //   o -3- Creating the procedural report
    //  //   o  -3-1 Filling the list of specifications to follow
    //  //   o  -3-2 Creating the procedural report
    //  //   o -4- Running the topological operators
    //  //   o  -4-1 Retrieving the geometrical factory
    //  //   o  -4-2 Retrieving the topological journal
    //  //   o  -4-3 Retrieving the Algorithm Configuration
    //  //   o  -4-4 Running the topological operator - extruding curves
    //  //   o  -4-5 Running the topological operator - computing combined curve
    //  //   o -5- Storing the procedural report
    //  //   o -6- Storing the Algorithm Configuration
    //  //   o -6- Cleaning useless data
    //  // CATCatch
    //  //     o -7-1 Managing CATMfErrUpdate Error
    //  //     o -7-2 Managing other Error's types
    //  //
    //  //========================================================================================

    //  // You declare here the pointers :
    //  //  - used in the CATTry and CATThrow sections, like piUpdateErrorOnThis
    //  //  - initialized in the CATTry section, and not released before a
    //  //    method which can throw an error.
    //  //
    //  CATIUpdateError          * piUpdateErrorOnThis        = NULL;
    //  CATIGeometricalElement   * pIGeometricalElementOnThis = NULL ;
    //  CATHybOperator           * pIntersect                 = NULL;

    //  CATBody                  * pFirstPointExtrudeBody         = NULL ;

    //  CATIMfProcReport         * piProcReport               = NULL;
    //  CATGeoFactory            * piGeomFactory              = NULL;
    //  CATSoftwareConfiguration * pSoftConfig                = NULL;
    //  int                      IsConfigToStore              = NULL;

    //  CATISpecObject           * pSOCombinedCurve           = NULL;

    //  CATTry
    //  {

    //  //========================================================================================
    //  //
    //  // -0- Checking the deactivation
    //  //
    //  //========================================================================================

    //      int DeactivateState = 0 ;
    //      CATIMechanicalProperties *pMechProp = NULL ;
    //      rc = QueryInterface(IID_CATIMechanicalProperties,(void **) & pMechProp);
    //      if ( SUCCEEDED(rc) )
    //      {
    //          DeactivateState = pMechProp->IsInactive();

    //          pMechProp->Release();
    //          pMechProp = NULL ;

    //          if ( 1 == DeactivateState )
    //          {
    //             QueryInterface(IID_CATIMfProcReport,(void**) &piProcReport );
    //             if ( SUCCEEDED(rc) )
    //             {
    //                rc = piProcReport->InactivateResult();

    //                // if an error is sent by InactivateResult,
    //                // piProcReport is deleted in CATCatch sections

    //                piProcReport->Release();
    //                piProcReport = NULL ;
    //             }
    //          }
    //      }

    //  //========================================================================================
    //  //
    //  // -1- Cleaning last update error
    //  //
    //  //========================================================================================
    //     if ( DeactivateState == 0 )
    //     {

    //        rc = QueryInterface( IID_CATIUpdateError , (void**) &piUpdateErrorOnThis);
    //        if ( SUCCEEDED(rc) )
    //        {
    //           piUpdateErrorOnThis->UnsetUpdateError();
    //        }

    //        // This step will be useless in R12
    //        if ( SUCCEEDED(rc) )
    //        {
    //           rc = QueryInterface(IID_CATIGeometricalElement,(void**) &pIGeometricalElementOnThis
    //           ); if ( SUCCEEDED(rc) )
    //           {
    //              // Deletes the last result - method which can throw an error
    //              pIGeometricalElementOnThis->DeleteScope() ;

    //              // Useless pointer
    //              pIGeometricalElementOnThis->Release();
    //              pIGeometricalElementOnThis = NULL ;
    //           }
    //        }

    //     //========================================================================================
    //     //
    //     // -2- Retrieving Data for the procedural report
    //     //
    //     //========================================================================================

    //        //=====================================================================================
    //        //
    //        // -2-1 Retrieving the two input curves and the two input directions
    //        //
    //        //=====================================================================================

    //        CATISpecObject    *piSpecOnFirstPoint     = NULL;
    //        CATISpecObject    *piSpecOnMainDir = NULL;

    //        PNXICombinedCurve *piCombinedCurve = NULL;
    //        rc = QueryInterface( IID_PNXICombinedCurve , (void**) &piCombinedCurve );
    //        if ( SUCCEEDED(rc) )
    //        {
    //           // Retrieves curves and directions
    //           rc = piCombinedCurve->GetFirstPoint    (&piSpecOnFirstPoint     );
    //           if ( SUCCEEDED(rc) )
    //              rc = piCombinedCurve->GetMainDir( &piSpecOnMainDir );

    //           piCombinedCurve->Release();
    //           piCombinedCurve = NULL ;

    //           if ( FAILED(rc) )
    //           {
    //              // One of the inputs is NULL
    //              if ( NULL != piSpecOnFirstPoint )
    //              {
    //                 piSpecOnFirstPoint->Release();
    //                 piSpecOnFirstPoint = NULL;
    //              }

    //              if ( NULL != piSpecOnMainDir )
    //              {
    //                 piSpecOnMainDir->Release();
    //                 piSpecOnMainDir = NULL;
    //              }

    //              // An error is created
    //              CATMfErrUpdate *pErrorNoValidInput = new CATMfErrUpdate();
    //              CATUnicodeString Diagnostic("One of the inputs is wrong.");
    //              pErrorNoValidInput->SetDiagnostic(1,Diagnostic);

    //              CATThrow(pErrorNoValidInput);
    //           }
    //        }

    //        //=====================================================================================
    //        //
    //        // -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
    //        //
    //        //=====================================================================================

    //        CATMathDirection MathMainDir;

    //        if ( SUCCEEDED(rc) && (NULL !=piSpecOnMainDir) )
    //        {
    //           // Gets a pointer on CATline for first direction
    //           CATLine *piLine1 = NULL;

    //           rc = piSpecOnMainDir->QueryInterface( IID_CATLine , ( void**) &piLine1 );

    //           if ( SUCCEEDED(rc) )
    //           {
    //              // Gets first mathematical direction
    //              piLine1->GetMainDir(MathMainDir);

    //              // releases useless pointer
    //              piLine1->Release();
    //              piLine1 = NULL ;
    //           }
    //        }

    //        //=====================================================================================
    //        //
    //        // -2-3 Retrieving the two bodies corresponding to the two input curves
    //        //
    //        //=====================================================================================

    //        CATBody_var spiBodyOfFirstPoint;

    //        if ( SUCCEEDED(rc) && (NULL !=piSpecOnFirstPoint) )
    //        {
    //           // gets a pointer on CATIGeometricalElement on the first input curve
    //           CATIGeometricalElement *piGeometricalElementOnFirstPoint = NULL;
    //           rc = piSpecOnFirstPoint->QueryInterface ( IID_CATIGeometricalElement ,
    //                                              (void**) &piGeometricalElementOnFirstPoint );

    //           if ( SUCCEEDED(rc) )
    //           {
    //              // uses GetBodyResult to retrieve the first body
    //              spiBodyOfFirstPoint = piGeometricalElementOnFirstPoint->GetBodyResult();

    //              // releases useless pointer on CATIGeometricalElement
    //              piGeometricalElementOnFirstPoint->Release();
    //              piGeometricalElementOnFirstPoint = NULL ;
    //           }
    //        }

    //     //========================================================================================
    //     //
    //     // -3- Creating the procedural report
    //     //
    //     //========================================================================================

    //       //======================================================================================
    //       // -3-1 Filling the lists of the specifications to follow by the procedural report
    //       //
    //       //======================================================================================

    //        CATLISTV(CATBaseUnknown_var) ListSpec;
    //        CATListOfCATUnicodeString    ListKeys;
    //        if ( SUCCEEDED(rc) )
    //        {
    //              ListSpec.Append( piSpecOnFirstPoint     );
    //              ListKeys.Append( MfKeyNone          );

    //              ListSpec.Append( piSpecOnMainDir );
    //              ListKeys.Append( MfKeyNone          );

    //        }

    //        // No more need of those pointers
    //        if ( NULL != piSpecOnFirstPoint )
    //        {
    //           piSpecOnFirstPoint->Release();
    //           piSpecOnFirstPoint = NULL;
    //        }
    //        if ( NULL != piSpecOnMainDir )
    //        {
    //           piSpecOnMainDir->Release();
    //           piSpecOnMainDir = NULL;
    //        }

    //       // Once the pointers are released, Checking that the bodies of the
    //       // curve exist
    //       //
    //       if ( SUCCEEDED(rc) )
    //       {
    //          if ( (NULL_var == spiBodyOfFirstPoint ) )
    //          {
    //              // An error is created
    //              CATMfErrUpdate *pErrorNoValidInput = new CATMfErrUpdate();
    //              CATUnicodeString Diagnostic("One of the curve has no topology.");
    //              pErrorNoValidInput->SetDiagnostic(1,Diagnostic);

    //              CATThrow(pErrorNoValidInput);
    //          }
    //       }

    //       //======================================================================================
    //       // -3-2 Creating the procedural report with the list
    //       //
    //       //======================================================================================

    //        if ( SUCCEEDED(rc) )
    //        {
    //           rc = QueryInterface( IID_CATIMfProcReport , (void**) &piProcReport );
    //           if ( SUCCEEDED(rc) )
    //           {
    //              // Creates the procedural report- the result is associated with the
    //              // feature itself - so BoolOper is 0
    //              // This method can throw an error
    //              //
    //              int BoolOper = 0;
    //              piProcReport->CreateProcReport(ListSpec,ListKeys,BoolOper);
    //           }
    //        }

    //     //========================================================================================
    //     //
    //     // -4- Running the procedural report
    //     //
    //     //========================================================================================

    //        //=====================================================================================
    //        //
    //        // -4-1 Retrieving the geometrical factory
    //        //
    //        //=====================================================================================

    //        if ( SUCCEEDED(rc) )
    //        {
    //           // Gets a pointer on CATISpecObject.
    //           CATILinkableObject *piLinkableObjectOnCombinedCurve = NULL;
    //           rc = QueryInterface( IID_CATILinkableObject,
    //                                (void**)& piLinkableObjectOnCombinedCurve );

    //           if ( SUCCEEDED(rc) )
    //           {
    //              // Do not release this pointer
    //              CATDocument * pDocument = NULL ;
    //              pDocument = piLinkableObjectOnCombinedCurve->GetDocument();

    //              if ( NULL != pDocument )
    //              {
    //                 CATIContainerOfDocument * pIContainerOfDocument = NULL ;
    //                 rc = pDocument->QueryInterface(IID_CATIContainerOfDocument,
    //                                                    (void**)& pIContainerOfDocument );
    //                 if ( SUCCEEDED(rc) )
    //                 {
    //                    CATIContainer * pIContainerOnGeomContainer = NULL ;
    //                    rc =
    //                    pIContainerOfDocument->GetResultContainer(pIContainerOnGeomContainer); if
    //                    ( SUCCEEDED(rc) )
    //                    {

    //                       rc = pIContainerOnGeomContainer->QueryInterface( IID_CATGeoFactory ,
    //                                                                     (void**) &piGeomFactory
    //                                                                     );
    //                       pIContainerOnGeomContainer->Release();
    //                       pIContainerOnGeomContainer = NULL ;
    //                    }

    //                    pIContainerOfDocument->Release();
    //                    pIContainerOfDocument = NULL ;
    //                 }
    //              }
    //              piLinkableObjectOnCombinedCurve->Release();
    //              piLinkableObjectOnCombinedCurve = NULL ;
    //           }
    //        }

    //        //=====================================================================================
    //        //
    //        // -4-2 Retrieving the topological journal which contains the description
    //        //      of all basic topological operations.
    //        //
    //        //=====================================================================================

    //        CATTopData TopData ;
    //        if ( SUCCEEDED(rc) && (NULL!=piProcReport) )
    //        {
    //           // do not release this pointer
    //           // This method can throw an error
    //           CATCGMJournalList *pCGMJournalList = piProcReport->GetCGMJournalList();
    //           TopData.SetJournal(pCGMJournalList) ;

    //        //=====================================================================================
    //        //
    //        // -4-3 Retrieving the Algorithm Configuration which contains datas used to
    //        //      version features
    //        //
    //        //=====================================================================================
    //           rc = QueryInterface(IID_CATISpecObject,(void **) & pSOCombinedCurve);
    //           if(SUCCEEDED(rc)&&pSOCombinedCurve != NULL)
    //           {
    //              rc = CATMmrAlgoConfigServices::GetConfiguration(pSOCombinedCurve ,pSoftConfig
    //              ,IsConfigToStore); if(SUCCEEDED(rc))
    //              {
    // 	               // SetSoftwareConfig
    // 	               TopData.SetSoftwareConfiguration(pSoftConfig) ;
    // 	               // release pSoftConfig after the procedural report ending
    //              }
    // 	         }
    //        }

    //        //=====================================================================================
    //        //
    //        // -4-4 Running the topological operator extruding the two curves in both senses
    //        //      defined by each direction
    //        //
    //        //=====================================================================================

    //        if ( SUCCEEDED(rc) )
    //        {
    //           CATLength StartOffset = 1000;
    //           CATLength EndOffset   = -StartOffset;

    //           // First topological operator : extrudes the first curve
    //           // This method can throw an error
    //           pFirstPointExtrude = ::CATCreateTopPrism ( piGeomFactory   ,
    // 				       &TopData ,
    // 				       spiBodyOfFirstPoint  ,
    // 				       &MathMainDir ,
    // 				       StartOffset     ,
    // 				       EndOffset);

    //           if ( NULL != pFirstPointExtrude)
    //           {
    //              CATLONG32 nbError = 0 ;
    //              CATError ** pListError = NULL ;
    //              CATBoolean Check = pFirstPointExtrude->CheckOperands(nbError,pListError);
    //              if ( TRUE == Check )
    //              {
    //                 // Runs the first topological operator
    //                 pFirstPointExtrude->Run();

    //                 // Gets the first resulting extrusion
    //                 pFirstPointExtrudeBody = pFirstPointExtrude->GetResult();
    //              }
    //              else
    //              {
    //                  CATThrow(pListError[0]);
    //              }
    //           }

    //        }

    //        //=====================================================================================
    //        //
    //        // -4-5 Running the topological operator computing the intersection of
    //        //      the two surfaces
    //        //
    //        //=====================================================================================

    //        CATBody   *pResultBody = NULL ;

    //     //========================================================================================
    //     //
    //     // -5- Storing the procedural report
    //     //
    //     //========================================================================================

    //        if ( SUCCEEDED(rc) && (NULL!=piProcReport)  )
    //        {
    //           if ( NULL != pResultBody )
    //           {
    //              // This method can throw an error
    //              int BoolOper = 0 ; // same as CreateProcReport
    //              piProcReport->StoreProcReport(pResultBody,NoCopy,BoolOper);

    //              //===============================================================================
    //              //
    //              // -6- Storing the Algorithm Configuration
    //              //
    //              //===============================================================================

    //              if(IsConfigToStore == 1)
    //              {
    //                 CATMmrAlgoConfigServices::StoreConfiguration(pSOCombinedCurve ,pSoftConfig);
    //              }
    //           }
    //           else
    //           {
    //              // creates an error if the intersection failed
    //              CATMfErrUpdate *pErrorNoIntersection = new CATMfErrUpdate();
    //              CATUnicodeString Diagnostic("The two extruded curves do not intersect.");
    //              pErrorNoIntersection->SetDiagnostic(1,Diagnostic);

    //              CATThrow(pErrorNoIntersection);
    //           }
    //        }

    //     //========================================================================================
    //     //
    //     // -7- Cleaning Useless Data, the possible solutions are:
    //     //
    //     //========================================================================================

    //        // Removes the intermediates bodies from the geometric container
    //        if ( (NULL !=piGeomFactory) && (NULL != pFirstPointExtrudeBody) )
    //        {
    //           piGeomFactory->Remove(pFirstPointExtrudeBody);
    //           pFirstPointExtrudeBody = NULL ;
    //        }

    //        // Deletes the first topological operator
    //        if ( NULL != pFirstPointExtrude )
    //        {
    //            delete pFirstPointExtrude;
    //            pFirstPointExtrude = NULL ;
    //        }

    //        // Deletes the third topological operator
    //        if ( NULL != pIntersect )
    //        {
    //           delete pIntersect;
    //           pIntersect = NULL ;
    //        }

    //        // Releases the update error
    //        if(NULL != piUpdateErrorOnThis)
    //        {
    //            piUpdateErrorOnThis->Release();
    //            piUpdateErrorOnThis = NULL ;
    //        }

    //        // Releases the procedural report interface pointer
    //        if(NULL != piProcReport)
    //        {
    //            piProcReport->Release();
    //            piProcReport = NULL ;
    //        }

    //        // Releases the pointer pSOCombinedCurve
    //        if(NULL != pSOCombinedCurve)
    //        {
    //            pSOCombinedCurve->Release();
    //            pSOCombinedCurve = NULL;
    //        }

    //        // Releases the software configuration
    //        if (NULL != pSoftConfig)
    //        {
    //           pSoftConfig->Release();
    //           pSoftConfig = NULL ;
    //        }

    //        // Releases the geometrical factory
    //        if (NULL != piGeomFactory)
    //        {
    //            piGeomFactory->Release();
    //            piGeomFactory = NULL ;
    //        }

    //     }
    //  }

    //  //========================================================================================
    //  //
    //  // -7- Managing errors
    //  //
    //  //========================================================================================

    //  CATCatch ( CATMfErrUpdate , pUpdateError)
    //  {
    //      //------------------------------------------------------------------------------
    //      // Catches CATMfErrUpdate errors
    //      //------------------------------------------------------------------------------

    //      // Associates the error with the Combined Curve
    //      if(NULL != piUpdateErrorOnThis)
    //      {
    //          piUpdateErrorOnThis->SetUpdateError(pUpdateError);

    //          piUpdateErrorOnThis->Release();
    //          piUpdateErrorOnThis = NULL ;
    //      }

    //      // Releases or deletes the pointer which can be valuated
    //      // but not released before an error
    //      //
    //      if ( NULL != pIGeometricalElementOnThis)
    //      {
    //          pIGeometricalElementOnThis->Release();
    //          pIGeometricalElementOnThis = NULL ;
    //      }

    //      // Deletes the result ( proc report + pResultBody )
    //      if (NULL != piProcReport)
    //      {
    //         piProcReport->DeleteProcReport();
    //         piProcReport->Release();
    //         piProcReport = NULL ;
    //      }

    //      // Deletes the first topological operator
    //      if ( NULL != pFirstPointExtrude )
    //      {
    //         delete pFirstPointExtrude;
    //         pFirstPointExtrude = NULL ;
    //      }

    //      // Deletes the third topological operator
    //      if ( NULL != pIntersect )
    //      {
    //         delete pIntersect;
    //         pIntersect = NULL ;
    //      }

    //      // Removes the intermediate CATBody
    //      if ( (NULL !=piGeomFactory) && (NULL != pFirstPointExtrudeBody) )
    //      {
    //         piGeomFactory->Remove(pFirstPointExtrudeBody);
    //         pFirstPointExtrudeBody = NULL ;
    //      }

    //      // Deletes the pointer on the geometric container
    //      if(NULL != piGeomFactory)
    //      {
    //         piGeomFactory->Release();
    //         piGeomFactory = NULL ;
    //      }

    //      // Releases the pSOCombinedCurve
    //      if (NULL!=pSOCombinedCurve)
    //      {
    //        pSOCombinedCurve->Release();
    //        pSOCombinedCurve = NULL ;
    //      }

    //      // Releases the software configuration
    //      if (NULL!=pSoftConfig)
    //      {
    //        pSoftConfig->Release();
    //        pSoftConfig = NULL ;
    //      }

    //      // Re-dispatches the error.
    //      // In interactive mode, this errror will be caught by CATPrtUpdateCom that
    //      // knows how to handle such errors.
    //      CATRethrow ;
    //  }

    //  CATCatch ( CATError , pError)
    //  {
    //      //------------------------------------------------------------------------------
    //      // Catches other CATError errors
    //      //------------------------------------------------------------------------------

    //      CATMfErrUpdate *pErrorToThrow = new CATMfErrUpdate();
    //      pErrorToThrow->SetDiagnostic(1,pError->GetNLSMessage());

    //      ::Flush(pError);

    //      // Associates the error with the Combined Curve
    //      if(NULL != piUpdateErrorOnThis)
    //      {
    //          piUpdateErrorOnThis->SetUpdateError(pErrorToThrow);

    //          piUpdateErrorOnThis->Release();
    //          piUpdateErrorOnThis = NULL ;
    //      }

    //      // Releases or Deletes the pointer which can be valuated
    //      // ant not released due to a throw
    //      if ( NULL != pIGeometricalElementOnThis)
    //      {
    //          pIGeometricalElementOnThis->Release();
    //          pIGeometricalElementOnThis = NULL ;
    //      }

    //      // Deletes the result ( proc report + pResultBody )
    //      if (NULL != piProcReport)
    //      {
    //         piProcReport->DeleteProcReport();
    //         piProcReport->Release();
    //         piProcReport = NULL ;
    //      }

    //      // Deletes the first topological operator
    //      if ( NULL != pFirstPointExtrude )
    //      {
    //         delete pFirstPointExtrude;
    //         pFirstPointExtrude = NULL ;
    //      }

    //      // Deletes the third topological operator
    //      if ( NULL != pIntersect )
    //      {
    //         delete pIntersect;
    //         pIntersect = NULL ;
    //      }

    //      // Removes the intermediate CATBody
    //      if ( (NULL !=piGeomFactory) && (NULL != pFirstPointExtrudeBody) )
    //      {
    //         piGeomFactory->Remove(pFirstPointExtrudeBody);
    //         pFirstPointExtrudeBody = NULL ;
    //      }

    //      // Deletes the pointer on the geometric container
    //      if (NULL != piGeomFactory)
    //      {
    //         piGeomFactory->Release();
    //         piGeomFactory = NULL ;
    //      }

    //      // Releases the pSOCombinedCurve
    //      if (NULL!=pSOCombinedCurve)
    //      {
    //        pSOCombinedCurve->Release();
    //        pSOCombinedCurve = NULL ;
    //      }

    //      // Releases the software configuration
    //      if (NULL!=pSoftConfig)
    //      {
    //        pSoftConfig->Release();
    //        pSoftConfig = NULL ;
    //      }

    //      CATThrow(pErrorToThrow);
    //  }

    //  CATEndTry;

    return rc;
}
