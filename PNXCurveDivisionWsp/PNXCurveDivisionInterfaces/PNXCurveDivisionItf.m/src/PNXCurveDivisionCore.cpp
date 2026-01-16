/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXCurveDivision.git
 * @file  		PNXCurveDivisionCore.cpp
 * @version		V1.0
 * @brief
 * @details
 * @date		2021-9-1
 * =============================================================================
 */

// ApplicationFrame Framework
#include "CATFrmEditor.h" // needed to retrieve the editor and then to highight objects

// ObjectModelerBase Framework
#include "CATIContainer.h" // needed to create a GS (Geometrical Set)

// ObjectSpecsModeler Framework
#include "CATIDescendants.h" // needed to aggregate the newly created Line Create By GSD
#include "CATISpecObject.h"  // needed to manage feature

// MechanicalModeler Framework
#include "CATIBasicTool.h" // To retrieve the current tool
#include "CATIGSMTool.h"   // GSMTool and HybridBody features

// MecModInterfaces Framework
#include "CATIPrtPart.h" // needed to look for a GSM tool

// Visualization Framework
#include "CATHSO.h"            // needed to highlight objects
#include "CATIVisProperties.h" // needed to change Line Create By GSD's graphical appearance
#include "iostream.h"          //need for CAA iostream.not c++

// System framework
#include "CATBoolean.h"
#include "CATGetEnvValue.h" // To define the type of development
#include "CATLib.h"
#include "CATMathTransformation.h"

// KTC Core Framework

// local Framework
#include "PNXCurveDivisionCore.h"

#include <time.h>

#define KTC_DEBUG_COUT

//-----------------------------------------------------------------------------
PNXCurveDivisionCore::PNXCurveDivisionCore() {
}
//-----------------------------------------------------------------------------
PNXCurveDivisionCore::~PNXCurveDivisionCore() {
}
//-----------------------------------------------------------------------------
int PNXCurveDivisionCore::pretreat() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001; // param pointer check

    return 0;
}
//-----------------------------------------------------------------------------
int PNXCurveDivisionCore::calculate() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001; // param pointer check

    HRESULT hr = E_FAIL;
    return 0;
}
//-----------------------------------------------------------------------------
int PNXCurveDivisionCore::create() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001;     // param pointer check
    if (NULL == catFrmEditor_) return 100002; // editor pointer check

    HRESULT hr = E_FAIL;

    return 0;
}
