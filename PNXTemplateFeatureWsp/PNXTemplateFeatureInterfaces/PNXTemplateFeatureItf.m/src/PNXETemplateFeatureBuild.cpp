/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXETemplateFeatureBuild.cpp
 * @version		V1.0
 * @date		2025-12-17
 * @brief
 */

// GeometricObjects Framework
#include "CATCGMContainerMngt.h" // Geometry factory management
#include "CATCGMJournalList.h"
#include "CATGeoFactory.h" // To extrude input curves along the input directions
#include "CATLine.h"       // To query a direction

// Mathematics Framework
#include "CATEdge.h"
#include "CATMathDef.h"
#include "CATMathDirection.h" // Direction of extrusion
// MechanicalModeler Framework
#include "CATGeometry.h"
#include "CATIGeometricalElement.h" // Needed for DeleteScope and GetBodyResult
#include "CATIMeasurableLine.h"
#include "CATIMfProcReport.h"         // To manage the procedural report
#include "CATMfBRepDefs.h"            // Useful for the procedural report
#include "CATMmrAlgoConfigServices.h" // Needed to subscribe to repository for AlgorithmConfiguration
#include "CATTopDefine.h"
#include "CATTopLineOperator.h"

// MecModInterfaces Framework
#include "CATIContainerOfDocument.h"  // To retrieve the geometrical factory
#include "CATIMechanicalProperties.h" //

// ObjectModelerBase Framework
#include "CATDocument.h" // To retrieve the result container
#include "CATIContainer.h"
#include "CATILinkableObject.h"      // To retrieve the result container
#include "CATLISTV_CATBaseUnknown.h" // To store the CATBody of the input elements to follow

// ObjectSpecsModeler Framework
#include "CATISpecObject.h" // To query the Line Command feature about its inputs

// NewTopologicalObjects Framework
#include "CATBody.h" // The Topological result
#include "CATCell.h"
#include "CATTopData.h" // Needed to create operators

// System Framework
#include "CATBoolean.h"
#include "CATListOfCATUnicodeString.h" // For the list of keys
#include "CATUnicodeString.h"

// TopologicalOperators Framework
#include "CATCreateTopIntersect.h" // Needed to intersect extruded surfaces
#include "CATDataType.h"
#include "CATHybIntersect.h" // The result of the extruded surfaces's intersection
#include "CATHybOperator.h"
#include "CATIUpdateError.h"
#include "CATSoftwareConfiguration.h"
#include "CATTopLineOperator.h"
#include "CATTopPointOperator.h"
#include "CATTopPrism.h" // Needed to extrude curves

#include <iostream.h>

// Kt
#include "KtString.h"

// KTC Core
#include "KTCAutoBody.h"
#include "KTCAutoBuildGSM.h"
#include "KTCAutoErrors.h"
#include "KTCAutoPartDoc.h"

// Local Framework
#include "PNXETemplateFeatureBuild.h"

// PNXTemplateFeatureInterfaces Framework
#include "PNXITemplateFeature.h"
#include "PNXTemplateFeatureParam.h"

//-----------------------------------------------------------------------------

CATImplementClass(PNXETemplateFeatureBuild, DataExtension, CATBaseUnknown, PNXTemplateFeature);

//-----------------------------------------------------------------------------
#include "TIE_CATIBuild.h" // needed to tie the implementation to its interface
TIE_CATIBuild(PNXETemplateFeatureBuild);

//
// To declare that PNXTemplateFeature implements CATIBuild, insert
// the following line in the interface dictionary:
//
// PNXTemplateFeature  CATIBuild            libPNXTemplateFeatureItf
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
PNXETemplateFeatureBuild::PNXETemplateFeatureBuild()
    : CATBaseUnknown() {
}
//-----------------------------------------------------------------------------
PNXETemplateFeatureBuild::~PNXETemplateFeatureBuild() {
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeatureBuild::Build() {
    cout << "### " << __FUNCTION__ << endl;

    PNXITemplateFeature_var feature;
    this->QueryInterface(IID_PNXITemplateFeature, (void**)&feature);
    if (NULL_var == feature) return E_FAIL;

    HRESULT hr = build_feature(feature);
    if (FAILED(hr))
        cout << __FUNCTION__ << " FAILED." << hr << endl;
    else
        cout << __FUNCTION__ << " OK." << hr << endl;

    CATBoolean finish = feature->GetFinishCalc();

    cout << "- " << __LINE__ << endl;

    // finish only used once
    if (finish) feature->SetFinishCalc(0);

    cout << "- " << __LINE__ << endl;

    return hr;
}
//-----------------------------------------------------------------------------
HRESULT PNXETemplateFeatureBuild::build_feature(PNXITemplateFeature_var feature) {
    cout << "### " << __FUNCTION__ << endl;

    if (!feature) return E_INVALIDARG;
    CATISpecObject_var featureSpec = feature;
    if (!featureSpec) return E_INVALIDARG;

    //========================================================================================
    //
    // The build method takes place as follows :
    //
    // CATTry
    //   o -0- Checking the deactivation status
    //   o -1- Cleaning last update error
    //   o -2- Retrieving data for the procedural report
    //   o  -2-1 Retrieving the two input curves and the two input directions
    //   o  -2-2 Retrieving the two CATMathDirections corresponding to the two input directions
    //   o  -2-3 Retrieving the two bodies corresponding to the two input curves
    //   o -3- Creating the procedural report
    //   o  -3-1 Filling the list of specifications to follow
    //   o  -3-2 Creating the procedural report
    //   o -4- Running the topological operators
    //   o  -4-1 Retrieving the geometrical factory
    //   o  -4-2 Retrieving the topological journal
    //   o  -4-3 Retrieving the Algorithm Configuration
    //   o  -4-4 Running the topological operator - extruding curves
    //   o  -4-5 Running the topological operator - computing feature
    //   o -5- Storing the procedural report
    //   o -6- Storing the Algorithm Configuration
    //   o -6- Cleaning useless data
    // CATCatch
    //     o -7-1 Managing CATMfErrUpdate Error
    //     o -7-2 Managing other Error's types
    //
    //========================================================================================

    // You declare here the pointers :
    //  - used in the CATTry and CATThrow sections
    //  - initialized in the CATTry section, and not released before a
    //    method which can throw an error.
    //
    // buildGSM 会收集一些变量，进行释放Release
    KTCAutoBuildGSM         buildGSM;
    int                     IsConfigToStore = NULL;
    HRESULT                 rc;
    PNXTemplateFeatureParam parameter;

    CATTry {

        //========================================================================================
        // -0 准备工作
        // -0.1- Checking the Report
        //========================================================================================
        rc = QueryInterface(IID_CATIMfProcReport, (void**)&buildGSM.procReport);
        if (FAILED(rc)) {
            cout << " - [ERROR] QueryInterface(IID_CATIMfProcReport) error" << endl;
            return rc;
        }

        // -0.2- Checking the DeactivateState
        int                       DeactivateState = 0;
        CATIMechanicalProperties* pMechProp       = NULL;
        rc = QueryInterface(IID_CATIMechanicalProperties, (void**)&pMechProp);
        if (SUCCEEDED(rc)) {
            DeactivateState = pMechProp->IsInactive();
            KTCRelease(pMechProp); // 手动释放

            // 禁用操作
            if (1 == DeactivateState) {
                if (buildGSM.procReport) {
                    rc = buildGSM.procReport->InactivateResult();
                }
            }
        }

        //========================================================================================
        // 激活状态处理
        //========================================================================================
        if (DeactivateState == 0) {

            // -0.3- 检出参数
            feature->GetParams(parameter);               // do not check rc
            const double step = parameter.MyStep * 1000; // 转为mm

            //========================================================================================
            // -1- Cleaning 工作
            //========================================================================================
            rc = QueryInterface(IID_CATIUpdateError, (void**)&buildGSM.updateError);
            if (SUCCEEDED(rc)) {
                // -1.1- 清理错误
                buildGSM.updateError->UnsetUpdateError();

                // -1.2- 检出geometricalElement
                rc = QueryInterface(IID_CATIGeometricalElement,
                                    (void**)&buildGSM.geometricalElement);
                if (SUCCEEDED(rc)) {
                    // Deletes the last result - method which can throw an error
                    buildGSM.geometricalElement->DeleteScope();
                    KTCRelease(buildGSM.geometricalElement); // 手动释放
                }
            }

            if (SUCCEEDED(rc)) {
                //========================================================================================
                // -2- Retrieving Data for the procedural report
                //========================================================================================

                //=====================================================================================
                // -2-1 Retrieving the input
                //=====================================================================================
                CATMathPoint startPoint(0, 0, 0);
                CATMathPoint endPoint(0, 0, 100 * step);

                //========================================================================================
                // -3- Creating the procedural report
                //========================================================================================

                //======================================================================================
                // -3-1 Filling the lists of the specifications to follow by the procedural report
                //======================================================================================
                CATLISTV(CATBaseUnknown_var) ListSpec;
                CATListOfCATUnicodeString ListKeys;
                if (SUCCEEDED(rc)) {
                    ListSpec.Append(parameter.MyCurve);
                    ListKeys.Append(MfKeyNone);
                }

                // No more need of those pointers

                //======================================================================================
                // -3-2 Creating the procedural report with the list
                //======================================================================================

                if (SUCCEEDED(rc)) {
                    if (buildGSM.procReport) {
                        // Creates the procedural report- the result is associated with the
                        // feature itself - so BoolOper is 0
                        // This method can throw an error
                        //
                        int BoolOper = 0;
                        buildGSM.procReport->CreateProcReport(ListSpec, ListKeys, BoolOper);
                    }
                }

                //========================================================================================
                // -4- Running the procedural report
                //========================================================================================

                // -4-1 Retrieving the geometrical factory
                rc = buildGSM.query_factory(featureSpec);

                // -4-2 Retrieving the topological journal which contains the description
                //      of all basic topological operations.
                CATTopData TopData;
                if (SUCCEEDED(rc)) {
                    // do not release this pointer
                    // This method can throw an error
                    CATCGMJournalList* pCGMJournalList = buildGSM.procReport->GetCGMJournalList();
                    TopData.SetJournal(pCGMJournalList);

                    // -4-3 Retrieving the Algorithm Configuration which contains datas used to
                    //      version features
                    rc = CATMmrAlgoConfigServices::GetConfiguration(
                        featureSpec, buildGSM.softConfig, IsConfigToStore);
                    if (SUCCEEDED(rc)) {
                        // SetSoftwareConfig
                        TopData.SetSoftwareConfiguration(buildGSM.softConfig);
                    }
                    else {
                        cout << " - [ERROR] failed to get buildGSM.softConfig" << endl;
                    }
                }

                // -4-4 Running the topological operator extruding the two curves in both senses
                //      defined by each direction
                CATBody* startPointBody = NULL;
                CATBody* endPointBody   = NULL;
                if (SUCCEEDED(rc)) {
                    // Create First Body
                    startPointBody =
                        ::CATCreateTopPointXYZ(buildGSM.geomFactory, &TopData, endPoint.GetX(),
                                               endPoint.GetY(), endPoint.GetZ());

                    if (NULL == startPointBody) {
                        cout << " - ERROR when ::CATCreateTopPointXYZ() return NULL" << endl;
                    }
                }

                // -4-5 get Result Body
                CATBody* pResultBody = NULL;

                if (startPointBody) pResultBody = startPointBody;

                startPointBody = NULL; // 不用了，不删除传递给了pResultBody

                //========================================================================================
                // -5- Storing the procedural report
                //========================================================================================

                if (SUCCEEDED(rc)) {
                    if (NULL != pResultBody) {
                        // This method can throw an error
                        int BoolOper = 0; // same as CreateProcReport
                        buildGSM.procReport->StoreProcReport(pResultBody, NoCopy, BoolOper);

                        //===============================================================================
                        // -6- Storing the Algorithm Configuration
                        //===============================================================================

                        if (IsConfigToStore == 1 && buildGSM.softConfig) {
                            CATMmrAlgoConfigServices::StoreConfiguration(featureSpec,
                                                                         buildGSM.softConfig);
                        }
                    }
                    else {
                        // creates an error if the intersection failed
                        CATMfErrUpdate*  pErrorNoIntersection = new CATMfErrUpdate();
                        CATUnicodeString Diagnostic("Reult Body is NULL. code = 100120.");
                        pErrorNoIntersection->SetDiagnostic(1, Diagnostic);

                        CATThrow(pErrorNoIntersection);
                    }
                }

                //========================================================================================
                // -7- Cleaning Useless Data, the possible solutions are:
                //========================================================================================

                // Remove Body and set NULL
                // buildGSM.remove(someBody);

                //========================================================================================
                // -7- Managing errors
                //========================================================================================

                CATCatch(CATMfErrUpdate, pUpdateError) {
                    //------------------------------------------------------------------------------
                    // Catches CATMfErrUpdate errors
                    //------------------------------------------------------------------------------

                    // Associates the error with the feature
                    if (NULL != buildGSM.updateError) {
                        buildGSM.updateError->SetUpdateError(pUpdateError);
                    }
                }

                // Remove Body and set NULL
                // buildGSM.remove(someBody);
            }
        }
        cout << "- " << __LINE__ << endl;
    }
    CATCatch(CATError, pError) {
        //------------------------------------------------------------------------------
        // Catches other CATError errors
        //------------------------------------------------------------------------------

        CATMfErrUpdate* pErrorToThrow = new CATMfErrUpdate();
        pErrorToThrow->SetDiagnostic(1, pError->GetNLSMessage());

        ::Flush(pError);

        // Associates the error with the feature
        if (NULL != buildGSM.updateError) {
            buildGSM.updateError->SetUpdateError(pErrorToThrow);
            KTCRelease(buildGSM.updateError); // 手动释放
        }

        // Deletes the result ( proc report + pResultBody )
        if (NULL != buildGSM.procReport) {
            buildGSM.procReport->DeleteProcReport();
        }

        // Remove Body and set NULL
        // buildGSM.remove(someBody);

        // Deletes the pointer on the geometric container
        CATThrow(pErrorToThrow);
    }

    CATEndTry;

    cout << "- " << __LINE__ << endl;
    return rc;
}