/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateFeature
 * @file  		PNXTemplateFeatureCore.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2025-12-17
 * =============================================================================
 */

// ApplicationFrame Framework
#include "CATFrmEditor.h" // needed to retrieve the editor and then to highight objects

// ObjectModelerBase Framework
#include "CATIContainer.h" // needed to create a GS (Geometrical Set)

// ObjectSpecsModeler Framework
#include "CATIDescendants.h" // needed to aggregate the newly created Line Create By GSD
#include "CATISpecObject.h"  // needed to manage feature

// InteractiveInterfaces
#include "CATIBuildPath.h" // needed to build a path element to highlight a feature

// MechanicalModeler Framework
#include "CATIBasicTool.h"                   // To retrieve the current tool
#include "CATIGSMTool.h"                     // GSMTool and HybridBody features
#include "CATIMechanicalRootFactory.h"       // needed to create a GS
#include "CATIMmiGeometricalSet.h"           // Only for GSMTool feature
#include "CATIMmiNonOrderedGeometricalSet.h" // Only for GS feature

// MechanicalModelerUI Framework
#include "CATMmrLinearBodyServices.h" // To insert in ordered and linear body
#include "CATPrtUpdateCom.h" // needed to update the feature according to the user's update settings

// MecModInterfaces Framework
#include "CATIPrtPart.h"   // needed to look for a GSM tool
#include "CATMfBRepDefs.h" // needed to declare the modes of BRep feature creation

// Visualization Framework
#include "CATHSO.h" // needed to highlight objects
#include "CATISO.h"
#include "CATIVisProperties.h" // needed to change Line Create By GSD's graphical appearance
#include "CATPathElement.h"    // needed to highlight objects
#include "CATVisPropertiesValues.h"
#include "iostream.h" //need for CAA iostream.not c++

// System framework
#include "CATBoolean.h"
#include "CATGetEnvValue.h" // To define the type of development
#include "CATLib.h"

// rep
#include "CAT3DRep.h"

// CAA
#include "CATCreateExternalObject.h"
#include "CATIGSMProceduralView.h"
#include "CATMathTransformation.h"

// object
#include "CATBody.h"
#include "CATCrvParam.h"
#include "CATCurve.h"
#include "CATLine.h"

// KTC Core Framework
#include "KTCAutoBaseOpt.h"
#include "KTCAutoBody.h"
#include "KTCAutoDefine.h"
#include "KTCAutoGSM.h"
#include "KTCAutoPartDoc.h"

// local Framework
#include "PNXITemplateFeature.h"
#include "PNXITemplateFeatureFactory.h"
#include "PNXTemplateFeatureCore.h"

// Kt

// Error title
#define ERROR_TITLE_Create "Error : PNXTemplateFeatureCore::create(...) ..."
#define KTC_DEBUG_COUT

//-----------------------------------------------------------------------------
PNXTemplateFeatureCore::PNXTemplateFeatureCore()
    : PNXTemplateFeatureData() {
}
//-----------------------------------------------------------------------------
PNXTemplateFeatureCore::~PNXTemplateFeatureCore() {
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureCore::pretreat() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001; // param check
    parameter->MyTime.clear();            // clear time string

    if (NULL != catISO_) catISO_->Empty();

    // list3DRep_->release(); // release first

    return 0;
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureCore::calculate() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001; // param check

    //.............................need calculate time

    parameter->FinishCalc = 0;
    HRESULT hr            = S_OK;

    return 0;
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureCore::create() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001;     // param pointer check
    if (NULL == catFrmEditor_) return 100001; // editor pointer check
    feature = NULL_var;                       // clear first

    HRESULT hr = E_FAIL;

    //
    // 1- Looking for a factory to create the element
    //

    // Factory control, class for partDocument unities. initial from editor.
    KTCAutoPartDoc partDocument1;                // initial
    partDocument1.initial_editor(catFrmEditor_); // set editor

    // query PNXITemplateFeatureFactory factory under the part container
    PNXITemplateFeatureFactory* piTemplateFeatureFactory = NULL; // Need release.
    // hr = partDocument1.che(IID_PNXITemplateFeatureFactory,
    //                                    (void**)&piTemplateFeatureFactory);
    // if (FAILED(hr)) {
    //     cout << ERROR_TITLE_Create << " QueryInterface(IID_PNXITemplateFeatureFactory). hr = " <<
    //     hr
    //          << endl;
    //     return 100004;
    // }

    //
    // 2- Creating the element
    //

    hr = piTemplateFeatureFactory->CreateTemplateFeature(*parameter, feature);
    KTCRelease(piTemplateFeatureFactory);
    if (FAILED(hr)) { // already print warning
        return 100005;
    }
    parameter->feature = feature; // record self Spec

    //
    // 3- Aggregating the feature in the Geometrical Set, auto put on tree
    //

    CATIGSMProceduralView_var spProceduralView = feature; // get interface for GSMProceduralView
    if (NULL_var == spProceduralView) {                   // error
        hr = E_POINTER;
        cout << ERROR_TITLE_Create << " get CATIGSMProceduralView_var.  " << hr << endl;
        return 100006;
    }

    // inset in view
    spProceduralView->InsertInProceduralView();

    return 0;
}
//-----------------------------------------------------------------------------
int PNXTemplateFeatureCore::show_rep() {
    if (NULL == catISO_) return 100002;
    if (NULL == parameter) return 100001; // param check

    CAT3DRep* pRep = NULL;

    return 0;
}
