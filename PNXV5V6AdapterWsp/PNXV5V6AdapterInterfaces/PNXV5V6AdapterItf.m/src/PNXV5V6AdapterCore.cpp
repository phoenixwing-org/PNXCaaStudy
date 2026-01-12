/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @author      Phoenix Wing
 * @checkout    PNXV5V6Adapter.git
 * @file  		PNXV5V6AdapterCore.cpp
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

// local Framework
#include "PNXUniqueCore.h"
#include "PNXV5V6AdapterCore.h"

#include <time.h>

// Error title
#define ERROR_TITLE_Create "Error : PNXV5V6AdapterCore::create(...) ..."
#define KTC_DEBUG_COUT

//-----------------------------------------------------------------------------
PNXV5V6AdapterCore::PNXV5V6AdapterCore() {
}
//-----------------------------------------------------------------------------
PNXV5V6AdapterCore::~PNXV5V6AdapterCore() {
}
//-----------------------------------------------------------------------------
int PNXV5V6AdapterCore::pretreat() {
    // cout << "### " << __FUNCTION__ << endl;

    if (NULL == parameter) return 1;

    return 0;
}
//-----------------------------------------------------------------------------
int PNXV5V6AdapterCore::calculate() {
    cout << "### " << __FUNCTION__ << endl;

    return 0;
}
//-----------------------------------------------------------------------------
int PNXV5V6AdapterCore::adapter() {
    cout << "### " << __FUNCTION__ << endl;

    cout << "##### Prepare " << endl;
    if (NULL == parameter) {
        cout << "- [error] parameter is NULL" << endl;
        return 100010;
    }

    if (NULL_var == parameter->BaseCurve) {
        cout << "- [error] Please set BaseCurve" << endl;
        return 100011;
    }

    // define uniqueCore
    PNXUniqueCore uniqueCore;
    cout << "- pass parameter->BaseCurve to uniqueCore.calculate" << endl;

    uniqueCore.feature = parameter->BaseCurve; // set curve

    cout << "### " << __FUNCTION__ << endl;

    PNXIMechanicalFeature_var out = uniqueCore.checkoutUniqueClass();
    if (!out) {
        cout << " - [error] uniqueCore.checkoutUniqueClass() is NULL_var" << endl;
    }

    cout << "### " << __FUNCTION__ << endl;

    int code = uniqueCore.calculate(parameter->BaseCurve);
    cout << " - code = " << code << endl;

    return code;
}
