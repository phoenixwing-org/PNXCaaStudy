// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef PNXECombinedCurveReplaceUI_H
#define PNXECombinedCurveReplaceUI_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension implementing the CATIReplaceUI interface
//  which manages the depth of a given Selection Path.

//  This extension extends the CombineCurve Feature.
//
//===========================================================================

// ObjectSpecsModeler Framework
#include "CATBaseUnknown.h"

// System Framework
class CATUnicodeString;

// Visualization Framework
class CATPathElement; // To handle Object Selection

class PNXECombinedCurveReplaceUI : public CATBaseUnknown {
    CATDeclareClass;

public:
    PNXECombinedCurveReplaceUI();
    virtual ~PNXECombinedCurveReplaceUI();

    HRESULT FindValidElementForReplace(const CATUnicodeString& iRole,
                                       const CATPathElement*   ipSelection,
                                       const CATBaseUnknown*   ipOldValue,
                                       CATBaseUnknown*&        opFoundElement);

private:
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    PNXECombinedCurveReplaceUI(const PNXECombinedCurveReplaceUI& iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    PNXECombinedCurveReplaceUI& operator=(const PNXECombinedCurveReplaceUI& iObjectToCopy);
};

#endif
