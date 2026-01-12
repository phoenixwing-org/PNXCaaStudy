/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXTemplateBase
 * @file  		PNXTemplateBaseCore.cpp
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
#include "PNXTemplateBaseCore.h"

#include <time.h>

// Error title
#define ERROR_TITLE_Create "Error : PNXTemplateBaseCore::create(...) ..."
#define KTC_DEBUG_COUT

//-----------------------------------------------------------------------------
PNXTemplateBaseCore::PNXTemplateBaseCore()
    : PNXTemplateBaseData() {
}
//-----------------------------------------------------------------------------
PNXTemplateBaseCore::~PNXTemplateBaseCore() {
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateBaseCore::pretreat() {
    // cout << "### " << __FUNCTION__ << endl;

    if (NULL == parameter) // param pointer check
        return E_INVALIDARG;

    if (NULL != _catISO) _catISO->Empty();

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateBaseCore::calculate() {
    // cout << "### " << __FUNCTION__ << endl;

    //.............................need calculate time

    parameter->FinishCalc = 0;
    HRESULT hr            = S_OK;

    return hr;
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateBaseCore::create() {
    // cout << "### " << __FUNCTION__ << endl;

    feature = NULL_var; // clear first

    if (NULL == parameter) // param pointer check
        return E_INVALIDARG;
    if (NULL == _catFrmEditor) // editor pointer check
        return E_INVALIDARG;

    HRESULT hr = E_FAIL;

    return S_OK;
}
//-----------------------------------------------------------------------------
HRESULT PNXTemplateBaseCore::show_rep() {
    if (NULL == _catISO) return E_POINTER;

    CAT3DRep* pRep = NULL;

    //   KTC::RepShowCurve(&_ktc3DRep, curve); // show origin curve

    return S_OK;
}
