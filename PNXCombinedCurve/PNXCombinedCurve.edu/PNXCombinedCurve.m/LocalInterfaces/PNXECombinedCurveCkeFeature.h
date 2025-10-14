// COPYRIGHT Dassault Systemes 2006
//===================================================================
//
// PNXECombinedCurveCkeFeature.h
// Provide implementation to interface
//    CATKweInstanceAdapter
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// EXTENSION		: CombinedCurve
// EXTENSIONTYPE	: DataExtension
// BOA			: CATKweInstanceAdapter
//===================================================================
#ifndef PNXECombinedCurveCkeFeature_H
#define PNXECombinedCurveCkeFeature_H

#include "CATICkeType.h"
#include "CATKweInstanceAdapter.h"

//-----------------------------------------------------------------------

/**
 * Implement of CATICkeFeature
 * Usage of Knowledge adaptor : CATKweInstanceAdapter
 * Implementation reaquired to use the feature in Knowledge tools (Mesure,mdistance ,etc ... )
 */
class PNXECombinedCurveCkeFeature : public CATKweInstanceAdapter

{
    CATDeclareClass;

public:
    PNXECombinedCurveCkeFeature();
    virtual ~PNXECombinedCurveCkeFeature();

    CATICkeType_var GetType() const;

private:
    PNXECombinedCurveCkeFeature(PNXECombinedCurveCkeFeature&);
    PNXECombinedCurveCkeFeature& operator=(PNXECombinedCurveCkeFeature&);
};

//-----------------------------------------------------------------------

#endif
