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

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h"

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
#include "KtCode.h"
#include "KtDump.h"
#include "KtTimer.h"
#include "ListKtMathBox.h"
#include "MatrixKtByteKit.h"

#include <time.h>

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
HRESULT PNXTemplateFeatureCore::pretreat() {
    // cout << "### " << __FUNCTION__ << endl;

    if (NULL == parameter) // param pointer check
        return E_INVALIDARG;
    parameter->MyTime.clear(); // clear time string

    if (NULL != _catISO) _catISO->Empty();

    // set _stepFace, value from dialog
    _stepFace = parameter->MyStep;
    if (_stepFace < 0.01) _stepFace = 0.01; // default

    // set _sagFace, value from dialog
    _sagFace = parameter->TessSag;
    if (_sagFace < 0.001) _sagFace = 0.001; // default

    // sag is define when initial
    _tessCurve.SetStep(_stepFace);
    _tessCurve.SetSag(_sagFace); // set sag for curve

    _ktc3DRep.ISOSet(_catISO);

    // set kit, fill boundary
    _matrixKit.k_boundary = 0;
    _matrixKit.k_fill     = 255;

    _list3DRep->release(); // release first

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateFeatureCore::calculate() {
    // cout << "### " << __FUNCTION__ << endl;

    //.............................need calculate time

    _myResult             = -1;
    parameter->FinishCalc = 0;
    HRESULT hr            = S_OK;

    return hr;
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateFeatureCore::create() {
    // cout << "### " << __FUNCTION__ << endl;

    feature = NULL_var; // clear first

    if (NULL == parameter) // param pointer check
        return E_INVALIDARG;
    if (NULL == _catFrmEditor) // editor pointer check
        return E_INVALIDARG;

    HRESULT hr = E_FAIL;

    //
    // 1- Looking for a factory to create the element
    //

    // Factory control, class for partDocument unities. initial from editor.
    KTCAutoPartDoc partDocument1;                // initial
    partDocument1._catFrmEditor = _catFrmEditor; // set editor

    // query PNXITemplateFeatureFactory factory under the part container
    PNXITemplateFeatureFactory* piTemplateFeatureFactory = NULL; // Need release.
    hr = partDocument1.CheckoutFactory(IID_PNXITemplateFeatureFactory,
                                       (void**)&piTemplateFeatureFactory);
    if (FAILED(hr)) {
        cout << ERROR_TITLE_Create << " QueryInterface(IID_PNXITemplateFeatureFactory). hr = " << hr
             << endl;
        return hr;
    }

    //
    // 2- Creating the element
    //

    hr = piTemplateFeatureFactory->CreateTemplateFeature(*parameter, feature);
    KTCRelease(piTemplateFeatureFactory);
    if (FAILED(hr)) { // already print warning
        return hr;
    }
    parameter->feature = feature; // record self Spec

    //
    // 3- Aggregating the feature in the Geometrical Set, auto put on tree
    //

    CATIGSMProceduralView_var spProceduralView = feature; // get interface for GSMProceduralView
    if (NULL_var == spProceduralView) {                   // error
        hr = E_POINTER;
        cout << ERROR_TITLE_Create << " get CATIGSMProceduralView_var.  " << hr << endl;
        return hr;
    }

    // inset in view
    spProceduralView->InsertInProceduralView();

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateFeatureCore::show_rep() {
    if (NULL == _catISO) return E_POINTER;

    CAT3DRep* pRep = NULL;

    //   KTC::RepShowCurve(&_ktc3DRep, curve); // show origin curve

    return S_OK;
}
