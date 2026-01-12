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
#include "CATHybIntersect.h"       // The result of the extruded surfaces's intersection
#include "CATHybOperator.h"
#include "CATTopPrism.h" // Needed to extrude curves

#include "CATTopLineOperator.h"
#include "CATTopPointOperator.h"

// Mathematics Framework
#include "CATSoftwareConfiguration.h" // Needed to create topological data

#include <iostream.h>

#include "CATDataType.h"

// Kt
#include "KtString.h"

// KTC Core
#include "KTCAutoBody.h"
#include "KTCAutoErrors.h"
#include "KTCAutoPartDoc.h"

// Local Framework
#include "PNXETemplateFeatureBuild.h"

// PNXTemplateFeatureInterfaces Framework
#include "PNXITemplateFeature.h" // To ask inputs curves and directions

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

    PNXITemplateFeature* piTemplateFeature = NULL;
    this->QueryInterface(IID_PNXITemplateFeature, (void**)&piTemplateFeature);
    if (NULL == piTemplateFeature) return E_FAIL;

    CATBoolean finish = piTemplateFeature->GetFinishCalc();

    // finish only used once
    if (finish) piTemplateFeature->SetFinishCalc(0);

    KTCRelease(piTemplateFeature); // must release
    return finish ? S_OK : E_FAIL;
}
