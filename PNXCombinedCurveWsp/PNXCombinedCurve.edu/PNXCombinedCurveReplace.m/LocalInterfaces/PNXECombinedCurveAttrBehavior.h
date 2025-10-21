// Copyright Dassault Systemes 2000
#ifndef PNXECombinedCurveAttrBehavior_H
#define PNXECombinedCurveAttrBehavior_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension implementing the CATIAttrBehavior interface ,
//  which describes expected behavior on object valuating an attribute.
//  This extension extends the CombineCurve Feature.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetRequestedBehavior
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h" // Base class for PNXECombinedCurveAttrBehavior

// ObjectSpecsModeler Framework
#include "CATBehaviorSpecs.h" // To return the Behavior of an Attribute

// System Framework
class CATUnicodeString; // To handle Attribute Names

class PNXECombinedCurveAttrBehavior : public CATBaseUnknown {
public:
    CATDeclareClass;

    PNXECombinedCurveAttrBehavior();
    virtual ~PNXECombinedCurveAttrBehavior();

    /**
     * Returns for a given attribute the expected behavior of its valuating objects
     * @param ipAttrName
     *        name of the concerned attribute.
     * @param oppBehavior
     *        list of lists of interfaces in the CATBehaviorSpecs format.This parameter
     *        has to be deleted by the caller.
     *        <br> this list is a combination of interfaces implemented by the object
     *         valuating the attribute.
     */
    HRESULT GetRequestedBehavior(const CATUnicodeString* ipAttrId, CATBehaviorSpecs** oppBehavior);

private:
    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    PNXECombinedCurveAttrBehavior(const PNXECombinedCurveAttrBehavior& iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    PNXECombinedCurveAttrBehavior& operator=(const PNXECombinedCurveAttrBehavior& iObjectToCopy);
};

#endif
