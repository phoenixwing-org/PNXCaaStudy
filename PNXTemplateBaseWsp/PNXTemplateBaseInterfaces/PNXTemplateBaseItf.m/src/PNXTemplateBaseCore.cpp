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
int PNXTemplateBaseCore::pretreat() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001;
    int&      previewCode = parameter->previewCode; // 引用预处理Code
    KtString& message     = parameter->message;     // 引用message
    message.clear();
    parameter->code        = 100010; // 没有计算
    parameter->previewCode = 0;      // 初始化为0（无错误）

    // if (NULL != _catISO) _catISO->Empty();

    // 检查输入，set previewCode
    if (!parameter->MyCurve) {
        parameter->set_message(100102, "Please select MyCurve");
        return previewCode = parameter->code;
    }
    if (!parameter->MyFaces.Size() == 0) {
        parameter->set_message(100103, "Please select MyFaces");
        return previewCode = parameter->code;
    }

    if (previewCode) return previewCode; // if error return

    return S_OK;
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseCore::calculate() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001; // param check

    int& code       = parameter->code; // 引用
    parameter->code = 100010;          // 没有计算
    parameter->message.clear();

    // if (NULL != _catISO) _catISO->Empty();

    parameter->FinishCalc = 0;

    // HRESULT hr            = S_OK;

    return code;
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseCore::create() {
    // cout << "### " << __FUNCTION__ << endl;
    if (NULL == parameter) return 100001;                       // param check
    if (NULL == _catFrmEditor) return parameter->code = 100002; // editor pointer check
    if (parameter->previewCode) return parameter->code = parameter->previewCode; // no pretreat

    feature = NULL_var; // clear first

    //=====================================================
    // 不用再查检查“结果列表”中所有草图对象都能匹配,Pretreat里面检查过了
    // do not check sketches.size again
    //=====================================================

    // 变量设定======
    KtString msg; // 临时信息
    int&     code = parameter->code;
    parameter->clear_error(); // 设置为无错误
    HRESULT hr = S_OK;

    return code;
}
//-----------------------------------------------------------------------------
int PNXTemplateBaseCore::show_rep() {
    if (NULL == _catISO) return 100003;

    CAT3DRep* pRep = NULL;

    return 0;
}
